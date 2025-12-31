import redis
import json

from logging_config import logger

r = redis.Redis(host="localhost", port=6379, db=0, decode_responses=True)
CACHE_TTL = 60


def get_cache(key: str):
    try:
        data = r.get(key)
        if not data:
            return None
        return json.loads(data)
    except (redis.RedisError, json.JSONDecodeError, TypeError, Exception):
        logger.warning("Cache unavailable or corrupted")
        return None


def set_cache(key: str, value, ttl=60):
    try:
        r.setex(key, ttl, json.dumps(value))
    except (redis.RedisError, TypeError, Exception):
        logger.warning("Redis unavailable")


def invalidate_cache(key: str):
    try:
        r.delete(key)
    except (redis.RedisError, TypeError, Exception):
        logger.warning("Redis unavailable")