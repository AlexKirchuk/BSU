import asyncio
from fastapi import Request
from starlette.middleware.base import BaseHTTPMiddleware
from starlette.responses import JSONResponse

from logging_config import logger


class APIGatewayMiddleware(BaseHTTPMiddleware):
    async def dispatch(self, request: Request, call_next):
        try:
            response = await asyncio.wait_for(
                call_next(request),
                timeout=5
            )
            return response
        except asyncio.TimeoutError:
            return JSONResponse(
                status_code=504,
                content={"detail": "Gateway timeout"}
            )
        except Exception as e:
            logger.exception("Gateway error")
            return JSONResponse(
                status_code=500,
                content={"detail": "Internal gateway error"}
            )