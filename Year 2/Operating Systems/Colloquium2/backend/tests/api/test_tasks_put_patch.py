import pytest

from auth import create_access_token


@pytest.fixture
def auth_headers():
    token = create_access_token({"sub": "testuser"})
    return {"Authorization": f"Bearer {token}"}


def create_task(client, auth_headers):
    r = client.post("/tasks", json={
        "title": "Task",
        "description": "Desc",
        "status": "todo"
    }, headers=auth_headers)
    return r.json()["id"]


def test_put_task_full_update(client, auth_headers):
    task_id = create_task(client, auth_headers)

    r = client.put(f"/tasks/{task_id}", json={
        "title": "Updated",
        "description": "New",
        "status": "done"
    }, headers=auth_headers)

    assert r.status_code == 200
    assert r.json()["status"] == "done"


def test_put_task_not_found(client, auth_headers):
    r = client.put(f"/tasks/999", json={
        "title": "X",
        "description": "Y",
        "status": "todo"
    }, headers=auth_headers)
    assert r.status_code == 404


def test_patch_task_status_only(client, auth_headers):
    task_id = create_task(client, auth_headers)

    r = client.patch(f"/tasks/{task_id}", json={
        "status": "in_progress"
    }, headers=auth_headers)

    assert r.status_code == 200
    assert r.json()["status"] == "in_progress"


def test_patch_task_empty_body(client, auth_headers):
    task_id = create_task(client, auth_headers)

    r = client.patch(f"/tasks/{task_id}", json={}, headers=auth_headers)
    assert r.status_code == 200