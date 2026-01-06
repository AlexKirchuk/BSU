import asyncio
from fastapi import Request, HTTPException
from fastapi.exceptions import RequestValidationError
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
            logger.warning(f"Request timeout: {request.method} {request.url}")
            return JSONResponse(
                status_code=504,
                content={"detail": "Gateway timeout"}
            )
        except RequestValidationError as e:
            logger.warning(f"Validation error: {e}")
            return JSONResponse(
                status_code=422,
                content={"detail": str(e)}
            )
        except HTTPException as e:
            logger.warning(f"HTTP exception: {e.status_code} - {e.detail}")
            return JSONResponse(
                status_code=e.status_code,
                content={"detail": e.detail}
            )
        except ConnectionError as e:
            logger.error(f"Connection error: {e}")
            return JSONResponse(
                status_code=503,
                content={"detail": "Service unavailable"}
            )
        except Exception as e:
            logger.exception(f"Unexpected error in gateway: {type(e).__name__}")
            return JSONResponse(
                status_code=500,
                content={"detail": "Internal server error"}
            )