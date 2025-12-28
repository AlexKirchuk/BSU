from tasks_queue import celery_app

celery_app.worker_main()