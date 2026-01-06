from auth import create_access_token, get_current_user
from tasks import task_created, some_celery_task


from auth import create_access_token
from tasks import task_created, some_celery_task
from main import app
from models import User

def test_celery_down(monkeypatch, client, user):
    # Патчим Celery, чтобы выбрасывал ошибку
    monkeypatch.setattr(some_celery_task, "delay",
                        lambda *a, **kw: (_ for _ in ()).throw(Exception("Celery down")))

    # Создаем валидный токен для текущего пользователя
    token = create_access_token({"sub": str(user.id)})

    # Обходим middleware проверки пользователя, чтобы токен точно был валидным
    app.dependency_overrides[get_current_user] = lambda: user

    r = client.post(
        "/tasks",
        headers={"Authorization": f"Bearer {token}"},
        json={"title": "Test", "status": "todo", "user_id": user.id}
    )

    assert r.status_code == 201  # проверяем, что задача создается даже при сбое Celery

    # Чистим переопределение
    app.dependency_overrides.clear()



def test_celery_task():
    result = task_created.run(1)
    assert result is None