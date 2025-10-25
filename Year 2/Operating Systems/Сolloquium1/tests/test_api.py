import requests
import json
import sys
import time

BASE = "http://localhost:8080"

def wait_for_server(timeout=5):
    for _ in range(int(timeout * 10)):
        try:
            r = requests.get(f"{BASE}/health", timeout=0.3)
            if r.status_code == 200:
                return True
        except Exception:
            time.sleep(0.1)
    return False

def test_health():
    r = requests.get(f"{BASE}/health")
    assert r.status_code == 200
    assert r.json().get("status") == "ok"

def test_factorial():
    r = requests.get(f"{BASE}/factorial", params={"n":5})
    assert r.status_code == 200
    assert r.json()["result"] == [1, 2, 6, 24, 120]

def test_unique():
    r = requests.post(f"{BASE}/unique", json={"values":[1,2,2,3]})
    assert r.status_code == 200
    assert r.json()["result"] == [1,2,3]

def test_reverse():
    r = requests.post(f"{BASE}/reverse", json={"values":[1,2,3]})
    assert r.status_code == 200
    assert r.json()["result"] == [3,2,1]

if __name__ == "__main__":
    print("Checking server availability...")
    if not wait_for_server():
        print("Server is not responding on http://localhost:8080")
        sys.exit(1)
    print("Server is up, running API tests...\n")
    try:
        test_health()
        test_factorial()
        test_unique()
        test_reverse()
        print("All API tests passed successfully!")
    except AssertionError as e:
        print("Test failed:", e)
        sys.exit(1)