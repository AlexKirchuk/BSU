import os
from celery import Celery

REDIS_HOST = os.getenv("REDIS_HOST", "localhost")

celery_app = Celery(
    "tasks",
    broker=f"redis://{REDIS_HOST}:6379/1",
    backend=f"redis://{REDIS_HOST}:6379/2",
)

celery_app.conf.task_serializer = "json"
celery_app.conf.result_serializer = "json"
celery_app.conf.accept_content = ["json"]