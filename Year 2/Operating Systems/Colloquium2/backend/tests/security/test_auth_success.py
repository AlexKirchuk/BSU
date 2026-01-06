from auth import create_access_token


def test_valid_token(client, db_session):
    r = client.post("/register", json={
        "username": "testuser",
        "password": "secret"
    })
    assert r.status_code == 200

    r = client.post("/login", data={
        "username": "testuser",
        "password": "secret"
    })
    assert r.status_code == 200
    token = r.json()["access_token"]

    r = client.get(
        "/tasks",
        headers={"Authorization": f"Bearer {token}"}
    )
    assert r.status_code == 200