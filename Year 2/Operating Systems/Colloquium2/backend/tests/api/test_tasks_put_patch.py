def create_task(client):
    r = client.post("/tasks", json={
        "title": "Task",
        "description": "Desc",
        "status": "todo"
    })
    return r.json()["id"]


def test_put_task_full_update(client):
    task_id = create_task(client)

    r = client.put(f"/tasks/{task_id}", json={
        "title": "Updated",
        "description": "New",
        "status": "done"
    })

    assert r.status_code == 200
    assert r.json()["status"] == "done"


def test_put_task_not_found(client):
    r = client.put("/tasks/999", json={
        "title": "X",
        "description": "Y",
        "status": "todo"
    })
    assert r.status_code == 404


def test_patch_task_status_only(client):
    task_id = create_task(client)

    r = client.patch(f"/tasks/{task_id}", json={
        "status": "in_progress"
    })

    assert r.status_code == 200
    assert r.json()["status"] == "in_progress"


def test_patch_task_empty_body(client):
    task_id = create_task(client)

    r = client.patch(f"/tasks/{task_id}", json={})
    assert r.status_code == 200