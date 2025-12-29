def test_get_tasks_empty(client):
    r = client.get("/tasks")
    assert r.status_code == 200
    assert r.json() == []


def test_get_tasks_with_data(client):
    client.post("/tasks", json={
        "title": "Task 1",
        "description": "Desc",
        "status": "todo"
    })

    r = client.get("/tasks")
    data = r.json()

    assert len(data) == 1
    assert data[0]["title"] == "Task 1"


def test_get_task_by_id(client):
    r = client.post("/tasks", json={
        "title": "Task 2",
        "description": None,
        "status": "todo"
    })
    task_id = r.json()["id"]

    r = client.get(f"/tasks/{task_id}")
    assert r.status_code == 200
    assert r.json()["id"] == task_id


def test_get_task_not_found(client):
    r = client.get("/tasks/9999")
    assert r.status_code == 404