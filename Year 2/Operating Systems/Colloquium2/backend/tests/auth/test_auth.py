import pytest
from auth import create_access_token
from models import User
from main import app, get_db


# ---------------------------
# Fixtures
# ---------------------------

@pytest.fixture
def auth_headers(user):
    token = create_access_token({"sub": str(user.id)})
    return {"Authorization": f"Bearer {token}"}


# ---------------------------
# Register tests
# ---------------------------

def test_register_success(client):
    data = {"username": "newuser", "password": "pass1234"}
    r = client.post("/register", json=data)
    assert r.status_code == 200


def test_register_invalid_data(client):
    data = {"username": "", "password": ""}
    r = client.post("/register", json=data)
    assert r.status_code == 422


# ---------------------------
# Protected endpoint tests
# ---------------------------

def test_protected_no_token(client):
    r = client.get("/tasks")
    assert r.status_code == 401


def test_protected_invalid_token(client):
    r = client.get("/tasks", headers={"Authorization": "Bearer invalidtoken"})
    assert r.status_code == 401