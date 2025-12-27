import time
from fastapi import Request
from starlette.middleware.base import BaseHTTPMiddleware


class APIGatewayMiddleware(BaseHTTPMiddleware):
    async def dispatch(self, request: Request, call_next):
        start = time.time()

        response = await call_next(request)

        response.headers["X-Process-Time"] = str(time.time() - start)
        response.headers["X-Gateway"] = "FastAPI-Gateway"

        return response