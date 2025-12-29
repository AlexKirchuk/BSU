def test_create_task_success(client):
    r = client.post("/tasks", json={
        "title": "New task",
        "description": "Test",
        "status": "todo"
    })

    assert r.status_code == 201
    body = r.json()
    assert body["title"] == "New task"
    assert body["status"] == "todo"


def test_create_task_without_title(client):
    r = client.post("/tasks", json={
        "description": "No title",
        "status": "todo"
    })
    assert r.status_code == 422


def test_create_task_invalid_status(client):
    r = client.post("/tasks", json={
        "title": "Bad",
        "status": "invalid"
    })
    assert r.status_code == 422