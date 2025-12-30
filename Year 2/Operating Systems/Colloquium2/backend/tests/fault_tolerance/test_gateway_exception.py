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