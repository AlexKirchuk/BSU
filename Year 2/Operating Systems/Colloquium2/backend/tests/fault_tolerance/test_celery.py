from auth import create_access_token
from tasks import task_created


def test_celery_down(monkeypatch, client):
    monkeypatch.setattr("tasks.some_celery_task.delay",
                        lambda *a, **kw: (_ for _ in ()).throw(Exception("Celery down")))

    token = create_access_token({"sub": "test_user"})
    r = client.post("/tasks", headers={"Authorization": f"Bearer {token}"}, json={"title": "Test", "status": "todo"})

    assert r.status_code == 201


def test_celery_task():
    result = task_created.run(1)
    assert result is None