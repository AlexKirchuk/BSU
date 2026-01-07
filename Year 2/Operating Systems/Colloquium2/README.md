# Colloquium No. 2 – Industrial-Grade REST API Development

## Topic: Full-Stack REST API with Fault Tolerance, Authentication, and Monitoring

This project implements a **full-stack REST API** for task management with robust **backend** and a minimal **frontend**. The solution emphasizes **production-level quality**, including:

* CRUD logic for tasks
* Standard HTTP methods and correct status codes
* JSON-based request/response format
* Authentication & authorization
* Fault tolerance (DB, cache, gateway, worker queue)
* Metrics and logging
* Optional frontend interface

Technologies used include **Python + FastAPI** for backend, **SQLite + Redis** for persistence and caching, **Celery** for task queues, and **Vue 3 + Vite** for frontend.

---

## Requirements

* Implement a REST API supporting CRUD operations
* Use correct HTTP codes (200, 201, 404)
* Use JSON format for communication
* Optional: database, API gateway, caching, message queue, logging, metrics, fault tolerance
* Dockerized for local deployment

---

## Project Structure

```
Colloquium2/
├── docker-compose.yml
├── prometheus.yml
├── backend/
│   ├── Dockerfile
│   ├── requirements.txt
│   ├── src/
│   │   ├── auth.py
│   │   ├── cache.py
│   │   ├── database.py
│   │   ├── gateway.py
│   │   ├── logging_config.py
│   │   ├── main.py
│   │   ├── metrics.py
│   │   ├── middleware.py
│   │   ├── models.py
│   │   ├── schemas.py
│   │   ├── tasks.py
│   │   ├── tasks_queue.py
│   │   └── worker.py
│   └── tests/
│       ├── api/
│       │   ├── test_tasks_delete.py
│       │   ├── test_tasks_get.py
│       │   ├── test_tasks_post.py
│       │   └── test_tasks_put_patch.py
│       ├── auth/
│       │   └── test_auth.py
│       ├── fault_tolerance/
│       │   ├── test_cache.py
│       │   ├── test_celery.py
│       │   ├── test_db.py
│       │   ├── test_gateway.py
│       │   └── test_redis.py
│       ├── logic/
│       │   └── test_tasks_logic.py
│       ├── middleware/
│       │   ├── test_logging.py
│       │   └── test_metrics.py
│       └── security/
│           ├── test_auth_errors.py
│           └── test_auth_success.py
└── frontend/
    ├── Dockerfile
    ├── index.html
    ├── nginx.conf
    ├── package.json
    ├── vite.config.js
    └── src/
        ├── api.js
        ├── App.vue
        ├── main.js
        ├── router.js
        └── components/
            ├── Login.vue
            ├── Register.vue
            └── Tasks.vue
```

---

## Backend Features

* **CRUD endpoints**: `/tasks` with GET, POST, PUT, PATCH, DELETE
* **Authentication**: JWT-based with `/auth/register` and `/auth/login`
* **Fault tolerance**: DB/Redis/Celery errors handled gracefully
* **Metrics & Logging**: Prometheus-compatible metrics and structured logging
* **Task Queue**: Celery worker for asynchronous jobs

## Frontend Features

* Vue 3 + Vite SPA
* Components: Login, Register, Tasks
* Communicates with backend via REST API

---

## Build & Run

### Docker Compose

```bash
docker-compose up --build
```

This will start backend, frontend, Redis, and Prometheus.

### Backend Only

```bash
cd backend
pip install -r requirements.txt
uvicorn src.main:app --reload
```

### Frontend Only

```bash
cd frontend
npm install
npm run dev
```

---

## Testing

### Backend Tests

```bash
cd backend
pip install -r requirements.txt
$env:PYTHONPATH = ".\src"
pytest
```

### Frontend Manual Test

Open the SPA in the browser at `http://localhost:5173` (default Vite dev server)

---

## API Example

**Create Task:**

```http
POST /tasks
Authorization: Bearer <token>
Content-Type: application/json

{
  "title": "New Task",
  "status": "todo",
  "user_id": 1
}
```

**Get Tasks:**

```http
GET /tasks
Authorization: Bearer <token>
```

---

## License

Educational project for Colloquium 2 – REST API and full-stack development.