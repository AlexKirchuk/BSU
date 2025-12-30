import asyncio

from gateway import APIGatewayMiddleware


def test_gateway_timeout_http(client, monkeypatch):
    async def slow_call_next(request):
        await asyncio.sleep(10)

    middleware = APIGatewayMiddleware(app=None)

    response = asyncio.run(
        middleware.dispatch(None, slow_call_next)
    )

    assert response.status_code == 504