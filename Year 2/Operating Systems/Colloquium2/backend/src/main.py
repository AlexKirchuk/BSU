from typing import List
from fastapi import FastAPI, Depends, HTTPException, Response, Request
from fastapi.responses import JSONResponse
from fastapi.security import OAuth2PasswordRequestForm
from sqlalchemy.exc import SQLAlchemyError
from sqlalchemy.orm import Session
from starlette.middleware.cors import CORSMiddleware
from prometheus_client import generate_latest, CONTENT_TYPE_LATEST

from gateway import APIGatewayMiddleware
from database import Base, engine, session_local
from models import Task, User
from schemas import TaskCreate, TaskResponse, TaskUpdate, UserCreate, Token
from cache import get_cache, set_cache, invalidate_cache
from tasks import some_celery_task
from logging_config import logger
from middleware import LoggingMiddleware, MetricsMiddleware
from auth import get_current_user, create_access_token, hash_password, verify_password

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
app.add_middleware(APIGatewayMiddleware)
app.add_middleware(LoggingMiddleware)
app.add_middleware(MetricsMiddleware)

Base.metadata.create_all(bind=engine)


def get_db():
    db = session_local()
    try:
        yield db
    except SQLAlchemyError:
        logger.error("Database unavailable")
        raise HTTPException(status_code=503, detail="Database unavailable")
    except Exception:
        logger.error("Unknown DB error")
        raise HTTPException(status_code=503, detail="Database unavailable")
    finally:
        db.close()


def get_task_or_404(task_id: int, db: Session, user) -> type[Task]:
    task = db.query(Task).filter(Task.id == task_id, Task.user_id == user.id).first()
    if task is None:
        raise HTTPException(status_code=404, detail="Task not found")
    return task


@app.get("/tasks", response_model=List[TaskResponse])
async def get_tasks(
    db: Session = Depends(get_db),
    user=Depends(get_current_user)
):
    try:
        cache_key = f"tasks:user:{user.id}"
        cached = get_cache(cache_key)
        if cached:
            return cached

        tasks = db.query(Task).filter(Task.user_id == user.id).all()
        result = [TaskResponse.model_validate(task).model_dump() for task in tasks]
        set_cache(cache_key, result)
        return result
    except (SQLAlchemyError, Exception):
        raise HTTPException(status_code=503, detail="Database unavailable")


@app.post("/tasks", response_model=TaskResponse, status_code=201)
async def create_task(
    task: TaskCreate,
    db: Session = Depends(get_db),
    user=Depends(get_current_user)
):
    db_task = Task(title=task.title, description=task.description, status=task.status, user_id=user.id)
    db.add(db_task)
    db.commit()
    db.refresh(db_task)

    invalidate_cache(f"tasks:user:{user.id}")

    try:
        some_celery_task.delay(db_task.id)
    except Exception as e:
        logger.warning(f"Celery unavailable: {e}")

    return TaskResponse.model_validate(db_task)


@app.get("/tasks/{task_id}", response_model=TaskResponse)
async def get_task(
    task_id: int,
    db: Session = Depends(get_db),
    user=Depends(get_current_user)
):
    cache_key = f"tasks:{task_id}"
    cached = get_cache(cache_key)
    if cached:
        return cached

    task = get_task_or_404(task_id, db, user)
    result = TaskResponse.model_validate(task).model_dump()
    set_cache(cache_key, result)
    return result


@app.put("/tasks/{task_id}", response_model=TaskResponse)
async def update_task(
    task_id: int,
    task_data: TaskCreate,
    db: Session = Depends(get_db),
    user=Depends(get_current_user)

):
    task = get_task_or_404(task_id, db, user)

    task.title = task_data.title
    task.description = task_data.description
    task.status = task_data.status

    db.commit()
    db.refresh(task)

    invalidate_cache(f"tasks:user:{user.id}")
    invalidate_cache(f"tasks:{task_id}")

    return TaskResponse.model_validate(task)


@app.patch("/tasks/{task_id}", response_model=TaskResponse)
async def partial_update_task(
    task_id: int,
    task_data: TaskUpdate,
    db: Session = Depends(get_db),
    user=Depends(get_current_user)
):
    task = get_task_or_404(task_id, db, user)

    if task_data.title is not None:
        task.title = task_data.title
    if task_data.description is not None:
        task.description = task_data.description
    if task_data.status is not None:
        task.status = task_data.status

    db.commit()
    db.refresh(task)

    invalidate_cache(f"tasks:user:{user.id}")
    invalidate_cache(f"tasks:{task_id}")

    return TaskResponse.model_validate(task)


@app.delete("/tasks/{task_id}", status_code=200)
async def delete_task(
    task_id: int,
    db: Session = Depends(get_db),
    user=Depends(get_current_user)
):
    task = get_task_or_404(task_id, db, user)

    db.delete(task)
    db.commit()

    invalidate_cache(f"tasks:user:{user.id}")
    invalidate_cache(f"tasks:{task_id}")

    return {"detail": "Task deleted"}


@app.get("/metrics")
def metrics():
    return Response(
        generate_latest(),
        media_type=CONTENT_TYPE_LATEST
    )


@app.exception_handler(Exception)
async def global_exception_handler(request: Request):
    logger.exception(f"Unhandled error on {request.url.path}")
    return JSONResponse(
        status_code=500,
        content={"detail": "Internal Server Error"},
    )


@app.post("/register")
def register(user: UserCreate, db: Session = Depends(get_db)):
    if db.query(User).filter(User.username == user.username).first():
        raise HTTPException(status_code=400, detail="User already exists")

    try:
        hashed = hash_password(user.password)
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))

    db_user = User(
        username=user.username,
        hashed_password=hashed
    )
    db.add(db_user)
    db.commit()

    return {"detail": "User created"}


@app.post("/login", response_model=Token)
def login(
    form_data: OAuth2PasswordRequestForm = Depends(),
    db: Session = Depends(get_db)
):
    user = db.query(User).filter(User.username == form_data.username).first()

    if not user or not verify_password(form_data.password, user.hashed_password):
        raise HTTPException(status_code=401, detail="Invalid credentials")

    token = create_access_token({"sub": str(user.id)})

    return {
        "access_token": token,
        "token_type": "bearer"
    }


@app.get("/me")
def me(user=Depends(get_current_user)):
    return {
        "id": user.id,
        "username": user.username,
    }