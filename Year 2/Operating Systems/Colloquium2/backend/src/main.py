from typing import List
from fastapi import FastAPI, Depends, HTTPException, Response, Request
from fastapi.responses import JSONResponse
from sqlalchemy.orm import Session
from gateway import APIGatewayMiddleware
from prometheus_client import generate_latest, CONTENT_TYPE_LATEST

from database import Base, engine, session_local
from models import Task
from schemas import TaskCreate, TaskResponse, TaskUpdate
from cache import get_cache, set_cache, invalidate_cache
from tasks import task_created
from logging_config import logger
from middleware import LoggingMiddleware, MetricsMiddleware

app = FastAPI()
app.add_middleware(APIGatewayMiddleware)
app.add_middleware(LoggingMiddleware)
app.add_middleware(MetricsMiddleware)

Base.metadata.create_all(bind=engine)


def get_db():
    db = session_local()
    try:
        yield db
    finally:
        db.close()


def get_task_or_404(task_id: int, db: Session) -> type[Task]:
    task = db.query(Task).filter(Task.id == task_id).first()
    if task is None:
        raise HTTPException(status_code=404, detail="Task not found")
    return task


@app.get("/tasks", response_model=List[TaskResponse])
async def get_tasks(db: Session = Depends(get_db)):
    cache_key = "tasks:all"
    cached = get_cache(cache_key)
    if cached:
        return cached

    tasks = db.query(Task).all()
    result = [TaskResponse.model_validate(task).model_dump() for task in tasks]
    set_cache(cache_key, result)
    return result


@app.post("/tasks", response_model=TaskResponse, status_code=201)
async def create_task(task: TaskCreate, db: Session = Depends(get_db)):
    db_task = Task(title=task.title, description=task.description, status=task.status)
    db.add(db_task)
    db.commit()
    db.refresh(db_task)

    invalidate_cache("tasks:all")
    task_created.delay(db_task.id)
    return TaskResponse.model_validate(db_task)


@app.get("/tasks/{task_id}", response_model=TaskResponse)
async def get_task(task_id: int, db: Session = Depends(get_db)):
    cache_key = f"tasks:{task_id}"
    cached = get_cache(cache_key)
    if cached:
        return cached

    task = get_task_or_404(task_id, db)
    result = TaskResponse.model_validate(task).model_dump()
    set_cache(cache_key, result)
    return result


@app.put("/tasks/{task_id}", response_model=TaskResponse)
async def update_task(
    task_id: int,
    task_data: TaskCreate,
    db: Session = Depends(get_db)
):
    task = get_task_or_404(task_id, db)

    task.title = task_data.title
    task.description = task_data.description
    task.status = task_data.status

    db.commit()
    db.refresh(task)

    invalidate_cache("tasks:all")
    invalidate_cache(f"tasks:{task_id}")

    return TaskResponse.model_validate(task)


@app.patch("/tasks/{task_id}", response_model=TaskResponse)
async def partial_update_task(
    task_id: int,
    task_data: TaskUpdate,
    db: Session = Depends(get_db)
):
    task = get_task_or_404(task_id, db)

    if task_data.title is not None:
        task.title = task_data.title
    if task_data.description is not None:
        task.description = task_data.description
    if task_data.status is not None:
        task.status = task_data.status

    db.commit()
    db.refresh(task)

    invalidate_cache("tasks:all")
    invalidate_cache(f"tasks:{task_id}")

    return TaskResponse.model_validate(task)


@app.delete("/tasks/{task_id}", status_code=200)
async def delete_task(task_id: int, db: Session = Depends(get_db)):
    task = get_task_or_404(task_id, db)

    db.delete(task)
    db.commit()

    invalidate_cache("tasks:all")
    invalidate_cache(f"tasks:{task_id}")

    return {"detail": "Task deleted"}


@app.get("/metrics")
def metrics():
    return Response(
        generate_latest(),
        media_type=CONTENT_TYPE_LATEST
    )


@app.exception_handler(Exception)
async def global_exception_handler(request: Request, exc: Exception):
    logger.exception(f"Unhandled error on {request.url.path}")
    return JSONResponse(
        status_code=500,
        content={"detail": "Internal Server Error"},
    )