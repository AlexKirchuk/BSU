from datetime import datetime

import pytest
from sqlalchemy import create_engine, Column, DateTime
from sqlalchemy.exc import IntegrityError
from sqlalchemy.orm import sessionmaker, validates

from database import Base
from models import Task


@pytest.fixture(scope="function")
def db_session():
    engine = create_engine("sqlite:///:memory:")
    Base.metadata.create_all(engine)
    Session = sessionmaker(bind=engine)
    session = Session()
    yield session
    session.close()


def test_task_default_status(db_session):
    task = Task(title="Test task")
    db_session.add(task)
    db_session.commit()

    assert task.status == "todo"


def test_invalid_status_raises(db_session):
    with pytest.raises(ValueError):
        task = Task(title="Bad", status="invalid")
        db_session.add(task)
        db_session.commit()


def test_partial_update(db_session):
    task = Task(title="Old", status="todo")
    db_session.add(task)
    db_session.commit()

    task.title = "New"
    db_session.commit()

    assert task.title == "New"
    assert task.status == "todo"


def test_id_autoincrement(db_session):
    t1 = Task(title="A")
    t2 = Task(title="B")

    db_session.add_all([t1, t2])
    db_session.commit()

    assert t2.id == t1.id + 1


def test_created_at_auto_set(db_session):
    task = Task(title="Time test")
    db_session.add(task)
    db_session.commit()

    assert task.created_at is not None


def test_rollback_on_error(db_session):
    task1 = Task(title="OK")
    db_session.add(task1)
    db_session.commit()

    try:
        task2 = Task(title="FAIL", status="invalid")
        db_session.add(task2)
        db_session.commit()
    except Exception:
        db_session.rollback()

    tasks = db_session.query(Task).all()
    assert len(tasks) == 1


def test_title_required(db_session):
    task = Task(title=None)
    db_session.add(task)

    with pytest.raises(IntegrityError):
        db_session.commit()


def test_status_stable(db_session):
    task = Task(title="Stable")
    db_session.add(task)
    db_session.commit()

    db_session.commit()
    assert task.status == "todo"


def test_status_transition(db_session):
    task = Task(title="Flow", status="todo")
    db_session.add(task)
    db_session.commit()

    task.status = "done"
    db_session.commit()

    assert task.status == "done"