def test_delete_task(client):
    r = client.post("/tasks", json={
        "title": "Delete me",
        "status": "todo"
    })
    task_id = r.json()["id"]

    r = client.delete(f"/tasks/{task_id}")
    assert r.status_code == 200

    r = client.get(f"/tasks/{task_id}")
    assert r.status_code == 404


def test_delete_task_not_found(client):
    r = client.delete("/tasks/9999")
    assert r.status_code == 404