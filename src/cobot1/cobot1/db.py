"""
MySQL 스텁 모듈 — 현재는 로그만 출력.

실제 연결 시 수정 방법:
    pip install mysql-connector-python

    import mysql.connector
    conn = mysql.connector.connect(
        host='localhost', user='root', password='...', database='lego_assembly')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO placements (...) VALUES (%s, %s, ...)", (...))
    conn.commit()

테이블 구조, 컬럼명, 타입 모두 자유롭게 변경 가능.
"""

import logging

logger = logging.getLogger(__name__)


def insert_placement(step: int, color: str, target: list, status: str = 'OK'):
    logger.info(f'[DB] placement: step={step} color={color} target={target} status={status}')


def insert_error(step: int, error_type: str, detail: str = ''):
    logger.info(f'[DB] error: step={step} type={error_type} detail={detail}')


def insert_verify(match_rate: float, mismatched: str = ''):
    logger.info(f'[DB] verify: match_rate={match_rate} mismatched={mismatched}')
