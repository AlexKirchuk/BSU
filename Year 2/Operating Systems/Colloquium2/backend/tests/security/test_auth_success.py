from auth import create_access_token


def test_valid_token(client):
    token = create_access_token({"sub": "test"})
    r = client.get(
        "/tasks",
        headers={"Authorization": f"Bearer {token}"}
    )
    assert r.status_code == 200