def create_task(client, auth_headers, title="Task to delete"):
    r = client.post("/tasks", json={
        "title": title,
        "status": "todo"
    }, headers=auth_headers)
    return r.json()["id"]


def test_delete_task(client, auth_headers):
    task_id = create_task(client, auth_headers, "Delete me")

    r = client.delete(f"/tasks/{task_id}", headers=auth_headers)
    assert r.status_code == 200

    r = client.get(f"/tasks/{task_id}", headers=auth_headers)
    assert r.status_code == 404


def test_delete_task_not_found(client, auth_headers):
    r = client.delete("/tasks/9999", headers=auth_headers)
    assert r.status_code == 404