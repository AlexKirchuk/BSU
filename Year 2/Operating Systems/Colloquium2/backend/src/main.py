from typing import List
from fastapi import FastAPI, HTTPException
from schemas import TaskCreate, TaskResponse, TaskUpdate

app = FastAPI()

tasks: list[TaskResponse] = []
task_id_counter = 1


@app.get("/tasks", response_model=List[TaskResponse])
async def get_tasks():
    return tasks


@app.post("/tasks", response_model=TaskResponse, status_code=201)
async def create_task(task: TaskCreate):
    global task_id_counter

    new_task = TaskResponse(
        id=task_id_counter,
        title=task.title,
        description=task.description,
        status=task.status,
    )

    tasks.append(new_task)
    task_id_counter += 1

    return new_task


@app.get("/tasks/{task_id}", response_model=TaskResponse)
async def get_task(task_id: int):
    for task in tasks:
        if task.id == task_id:
            return task

    raise HTTPException(status_code=404, detail="Task not found")


@app.put("/tasks/{task_id}", response_model=TaskResponse)
async def update_task(task_id: int, task_data: TaskCreate):
    for index, task in enumerate(tasks):
        if task.id == task_id:
            updated_task = TaskResponse(
                id=task_id,
                title=task_data.title,
                description=task_data.description,
                status=task_data.status,
            )
            tasks[index] = updated_task
            return updated_task

    raise HTTPException(status_code=404, detail="Task not found")


@app.patch("/tasks/{task_id}", response_model=TaskResponse)
async def partial_update_task(task_id: int, task_data: TaskUpdate):
    for index, task in enumerate(tasks):
        if task.id == task_id:
            updated_task = task.model_copy(update=task_data.model_dump(exclude_unset=True))
            tasks[index] = updated_task
            return updated_task

    raise HTTPException(status_code=404, detail="Task not found")


@app.delete("/tasks/{task_id}", status_code=200)
async def delete_task(task_id: int):
    for index, task in enumerate(tasks):
        if task.id == task_id:
            tasks.pop(index)
            return {"detail": "Task deleted"}

    raise HTTPException(status_code=404, detail="Task not found")