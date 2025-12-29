from auth import create_access_token


def test_no_token(client):
    r = client.get("/tasks", headers={})
    assert r.status_code == 401


def test_invalid_token(client):
    r = client.get(
        "/tasks",
        headers={"Authorization": "Bearer invalid.token.here"}
    )
    assert r.status_code == 401


def test_post_without_auth(client):
    r = client.post("/tasks", json={"title": "X", "status": "todo"})
    assert r.status_code == 401


def test_put_without_auth(client):
    r = client.put("/tasks/1", json={"title": "X", "status": "done"})
    assert r.status_code == 401


def test_patch_without_auth(client):
    r = client.patch("/tasks/1", json={"title": "X"})
    assert r.status_code == 401


def test_delete_without_auth(client):
    r = client.delete("/tasks/1")
    assert r.status_code == 401