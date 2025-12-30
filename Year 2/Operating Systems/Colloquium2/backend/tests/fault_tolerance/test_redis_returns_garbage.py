from unittest.mock import MagicMock

from auth import create_access_token


def test_redis_returns_garbage(monkeypatch, client):
    fake_redis = MagicMock()
    fake_redis.get.return_value = b"not_json"
    monkeypatch.setattr("cache.r", fake_redis)

    token = create_access_token({"sub": "testuser"})
    r = client.get("/tasks", headers={"Authorization": f"Bearer {token}"})

    assert r.status_code == 200
    assert isinstance(r.json(), list)