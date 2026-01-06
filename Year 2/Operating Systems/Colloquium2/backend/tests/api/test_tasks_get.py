def test_get_tasks_empty(client, auth_headers):
    r = client.get("/tasks", headers=auth_headers)
    assert r.status_code == 200
    assert r.json() == []


def test_get_tasks_with_data(client, auth_headers):
    client.post("/tasks", json={
        "title": "Task 1",
        "description": "Desc",
        "status": "todo"
    }, headers=auth_headers)

    r = client.get("/tasks", headers=auth_headers)
    data = r.json()

    assert len(data) == 1
    assert data[0]["title"] == "Task 1"


def test_get_task_by_id(client, auth_headers):
    r = client.post("/tasks", json={
        "title": "Task 2",
        "description": None,
        "status": "todo"
    }, headers=auth_headers)
    task_id = r.json()["id"]

    r = client.get(f"/tasks/{task_id}", headers=auth_headers)
    assert r.status_code == 200
    assert r.json()["id"] == task_id


def test_get_task_not_found(client, auth_headers):
    r = client.get("/tasks/9999", headers=auth_headers)
    assert r.status_code == 404