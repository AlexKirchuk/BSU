from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

SQL_DB_URL = "sqlite:///tasks.db"
engine = create_engine(
    SQL_DB_URL,
    pool_pre_ping=True,
    pool_recycle=300
)

session_local = sessionmaker(
    autocommit=False,
    autoflush=False,
    bind=engine
)

Base = declarative_base()