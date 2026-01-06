import asyncio
from starlette.requests import Request
from starlette.responses import Response

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


def test_gateway_timeout(client, monkeypatch):
    async def slow_call_next(request):
        await asyncio.sleep(10)
        return Response("ok", status_code=200)

    scope = {
        "type": "http",
        "method": "GET",
        "path": "/tasks",
        "headers": [],
        "query_string": b"",
        "client": ("127.0.0.1", 8000),
        "server": ("127.0.0.1", 8000),
    }

    request = Request(scope)

    middleware = APIGatewayMiddleware(app=None)
    response = asyncio.run(middleware.dispatch(request, slow_call_next))

    assert response.status_code == 504


def test_gateway_allows_normal_request(client):
    r = client.get("/tasks")
    assert r.status_code in (200, 401)