def test_logging(client, caplog):
    client.get("/tasks")
    assert "GET /tasks" in caplog.text


def test_logging_logs(client, caplog):
    client.get("/tasks")

    logs = [r.message for r in caplog.records]
    assert any("GET /tasks" in m for m in logs)