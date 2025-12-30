from datetime import timedelta
from unittest.mock import MagicMock

from auth import create_access_token
from cache import r


def test_redis_down(monkeypatch, client):
    fake_redis = MagicMock()
    fake_redis.get.side_effect = Exception("Redis down")
    fake_redis.setex.side_effect = Exception("Redis down")
    fake_redis.delete.side_effect = Exception("Redis down")
    monkeypatch.setattr("cache.r", fake_redis)

    token = create_access_token({"sub": "test_user"}, expires_delta=timedelta(minutes=5))
    r = client.get("/tasks", headers={"Authorization": f"Bearer {token}"})

    assert r.status_code == 200