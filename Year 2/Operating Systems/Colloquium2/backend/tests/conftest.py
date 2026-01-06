import pytest
from fastapi.testclient import TestClient
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

import main
import auth
from database import Base
from models import User
from auth import create_access_token
from main import app

SQLALCHEMY_DATABASE_URL = "sqlite:///./test.db"

engine = create_engine(
    SQLALCHEMY_DATABASE_URL,
    connect_args={"check_same_thread": False},
)

TestingSessionLocal = sessionmaker(
    autocommit=False,
    autoflush=False,
    bind=engine,
)


@pytest.fixture
def app_instance():
    return app


@pytest.fixture(scope="function")
def db_session():
    engine = create_engine("sqlite:///:memory:")
    Base.metadata.create_all(engine)
    Session = sessionmaker(bind=engine)
    session = Session()
    yield session
    session.close()


@pytest.fixture
def user(db_session):
    user = User(
        username="testuser",
        hashed_password="hashed"
    )
    db_session.add(user)
    db_session.commit()
    return user


@pytest.fixture(scope="session")
def setup_database():
    Base.metadata.drop_all(bind=engine)
    Base.metadata.create_all(bind=engine)
    yield
    Base.metadata.drop_all(bind=engine)


@pytest.fixture
def db(setup_database):
    connection = engine.connect()
    transaction = connection.begin()

    session = TestingSessionLocal(bind=connection)

    try:
        yield session
    finally:
        session.close()
        transaction.rollback()
        connection.close()


def override_get_db():
    try:
        yield pytest.db
    finally:
        pass


@pytest.fixture(autouse=True)
def override_dependencies(db):
    pytest.db = db

    main.app.dependency_overrides[main.get_db] = override_get_db
    main.app.dependency_overrides[auth.get_db] = override_get_db

    yield

    main.app.dependency_overrides.clear()


@pytest.fixture
def client(monkeypatch):
    # Redis
    monkeypatch.setattr("main.get_cache", lambda *a, **kw: None)
    monkeypatch.setattr("main.set_cache", lambda *a, **kw: None)
    monkeypatch.setattr("main.invalidate_cache", lambda *a, **kw: None)

    # Celery
    class DummyTask:
        def delay(self, *a, **kw):
            return None

    monkeypatch.setattr("main.some_celery_task", DummyTask())

    with TestClient(main.app) as c:
        yield c


@pytest.fixture
def test_user(db):
    user = User(
        username="testuser",
        hashed_password="fake_hash"
    )
    db.add(user)
    db.commit()
    db.refresh(user)
    return user


@pytest.fixture
def auth_token(test_user):
    return create_access_token({"sub": str(test_user.id)})


@pytest.fixture
def auth_headers(auth_token):
    return {
        "Authorization": f"Bearer {auth_token}"
    }