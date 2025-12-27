from fastapi import HTTPException, Header, Request
import time

from database import session_local
from auth import decode_token


# ---------- DB ----------
def get_db():
    db = session_local()
    try:
        yield db
    finally:
        db.close()


# ---------- AUTH ----------
def get_current_user(authorization: str = Header(...)):
    if not authorization.startswith("Bearer "):
        raise HTTPException(status_code=401, detail="Invalid Authorization header")

    token = authorization.split(" ")[1]
    payload = decode_token(token)

    if payload is None:
        raise HTTPException(status_code=401, detail="Invalid token")

    return payload


# ---------- RATE LIMIT ----------
RATE_LIMIT = 10
WINDOW = 60
clients = {}

def rate_limiter(request: Request):
    ip = request.client.host
    now = time.time()

    requests = clients.get(ip, [])
    requests = [t for t in requests if t > now - WINDOW]

    if len(requests) >= RATE_LIMIT:
        raise HTTPException(status_code=429, detail="Too many requests")

    requests.append(now)
    clients[ip] = requests