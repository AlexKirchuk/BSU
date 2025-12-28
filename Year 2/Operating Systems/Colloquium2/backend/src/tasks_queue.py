from celery import Celery

celery_app = Celery(
    "tasks",
    broker="redis://localhost:6379/1",
    backend="redis://localhost:6379/2",
)

celery_app.conf.task_serializer = "json"
celery_app.conf.result_serializer = "json"
celery_app.conf.accept_content = ["json"]