import redis
import json

from logging_config import logger

r = redis.Redis(host="localhost", port=6379, db=0, decode_responses=True)

CACHE_TTL = 60


def get_cache(key: str):
    try:
        data = r.get(key)
        return json.loads(data) if data else None
    except redis.RedisError:
        logger.warning("Redis unavailable")
        return None


def set_cache(key: str, value, ttl=60):
    try:
        r.setex(key, ttl, json.dumps(value))
    except redis.RedisError:
        logger.warning("Redis unavailable")


def invalidate_cache(key: str):
    r.delete(key)