import asyncio

from gateway import APIGatewayMiddleware


def test_gateway_exception(monkeypatch, client):
    async def broken_call_next(request):
        raise Exception("Gateway exploded")

    middleware = APIGatewayMiddleware(app=None)

    response = asyncio.run(
        middleware.dispatch(None, broken_call_next)
    )

    assert response.status_code == 500
    assert response.body


def test_gateway_timeout():
    async def slow_call_next(request):
        await asyncio.sleep(10)

    middleware = APIGatewayMiddleware(app=None)

    response = asyncio.run(
        middleware.dispatch(None, slow_call_next)
    )

    assert response.status_code == 504


def test_gateway_timeout_http(client, monkeypatch):
    async def slow_call_next(request):
        await asyncio.sleep(10)

    middleware = APIGatewayMiddleware(app=None)

    response = asyncio.run(
        middleware.dispatch(None, slow_call_next)
    )

    assert response.status_code == 504


def test_gateway_allows_normal_request(client):
    r = client.get("/tasks")
    assert r.status_code in (200, 401)