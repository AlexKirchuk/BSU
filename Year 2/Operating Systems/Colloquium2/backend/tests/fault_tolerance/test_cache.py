from cache import set_cache, get_cache

def test_cache_roundtrip():
    set_cache("key", {"a": 1})
    assert get_cache("key")["a"] == 1