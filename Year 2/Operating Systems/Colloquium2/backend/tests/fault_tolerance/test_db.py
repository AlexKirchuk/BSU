from fastapi import HTTPException

from auth import create_access_token
from main import get_db


def test_db_exception(client, app_instance):
    def fake_get_db():
        raise HTTPException(status_code=503, detail="Database unavailable")

    app_instance.dependency_overrides[get_db] = fake_get_db

    token = create_access_token({"sub": "testuser"})
    r = client.get("/tasks", headers={"Authorization": f"Bearer {token}"})

    assert r.status_code == 503

    app_instance.dependency_overrides.clear()