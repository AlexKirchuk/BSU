def test_metrics_available(client):
    r = client.get("/metrics")
    assert r.status_code == 200
    assert "http_requests_total" in r.text


def test_metrics_increment(client):
    r1 = client.get("/metrics")
    before = r1.text

    client.get("/tasks")

    r2 = client.get("/metrics")
    after = r2.text

    assert before != after