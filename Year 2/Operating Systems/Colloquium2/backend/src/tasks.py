from tasks_queue import celery_app
import time


@celery_app.task
def some_celery_task(task_id: int):
    time.sleep(3)
    print(f"Task {task_id} processed in background")


task_created = some_celery_task