def test_create_task_success(client, auth_headers):
    r = client.post("/tasks", json={
        "title": "New task",
        "description": "Test",
        "status": "todo"
    }, headers=auth_headers)

    assert r.status_code == 201
    body = r.json()
    assert body["title"] == "New task"
    assert body["status"] == "todo"


def test_create_task_without_title(client, auth_headers):
    r = client.post("/tasks", json={
        "description": "No title",
        "status": "todo"
    }, headers=auth_headers)
    assert r.status_code == 422


def test_create_task_invalid_status(client, auth_headers):
    r = client.post("/tasks", json={
        "title": "Bad",
        "status": "invalid"
    }, headers=auth_headers)
    assert r.status_code == 422