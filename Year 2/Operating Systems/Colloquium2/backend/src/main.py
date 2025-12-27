from typing import List
from fastapi import FastAPI, Depends, HTTPException
from sqlalchemy.orm import Session

from database import Base, engine, session_local
from models import Task
from schemas import TaskCreate, TaskResponse, TaskUpdate

app = FastAPI()

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
    return db.query(Task).all()


@app.post("/tasks", response_model=TaskResponse, status_code=201)
async def create_task(task: TaskCreate, db: Session = Depends(get_db)):
    db_task = Task(
        title=task.title,
        description=task.description,
        status=task.status
    )
    db.add(db_task)
    db.commit()
    db.refresh(db_task)
    return db_task


@app.get("/tasks/{task_id}", response_model=TaskResponse)
async def get_task(task_id: int, db: Session = Depends(get_db)):
    return get_task_or_404(task_id, db)


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
    return task


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
    return task


@app.delete("/tasks/{task_id}", status_code=200)
async def delete_task(task_id: int, db: Session = Depends(get_db)):
    task = get_task_or_404(task_id, db)

    db.delete(task)
    db.commit()
    return {"detail": "Task deleted"}