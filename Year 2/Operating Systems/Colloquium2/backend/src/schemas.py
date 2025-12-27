from pydantic import BaseModel
from typing import Literal, Optional


class TaskBase(BaseModel):
    title: str
    description: Optional[str] = None
    status: Literal["todo", "in_progress", "done"]


class TaskCreate(TaskBase):
    pass


class TaskUpdate(BaseModel):
    title: Optional[str] = None
    description: Optional[str] = None
    status: Optional[Literal["todo", "in_progress", "done"]] = None


class TaskResponse(TaskBase):
    id: int