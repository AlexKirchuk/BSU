from unittest.mock import MagicMock
from auth import create_access_token, get_current_user
from main import app
from models import User
from cache import r as redis_client

def test_redis_returns_garbage(monkeypatch, client, user):
    # Патчим Redis, чтобы возвращал "битые" данные
    fake_redis = MagicMock()
    fake_redis.get.return_value = b"not_json"
    monkeypatch.setattr("cache.r", fake_redis)

    # Валидный токен
    token = create_access_token({"sub": str(user.id)})

    # Обходим get_current_user, чтобы не было 401
    app.dependency_overrides[get_current_user] = lambda: user

    r = client.get(
        "/tasks",
        headers={"Authorization": f"Bearer {token}"}
    )

    assert r.status_code == 200  # проверяем, что сервер устойчив к "битым" данным

    # Чистим переопределение
    app.dependency_overrides.clear()
