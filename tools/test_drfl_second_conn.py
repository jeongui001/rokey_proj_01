#!/usr/bin/env python3
"""
DRFL 두 번째 연결 가능 여부 테스트.
bringup이 실행 중인 상태에서 실행하세요.
가상 모드: python3 test_drfl_second_conn.py
실제 모드: python3 test_drfl_second_conn.py 192.168.1.100
"""
import ctypes
import sys
import time

LIBPATH = (
    '/home/hwangjeongui/ws_cobot_pjt/ws_edu/'
    'install/dsr_hardware2/lib/libdsr_hardware2.so'
)
IP   = sys.argv[1].encode() if len(sys.argv) > 1 else b'127.0.0.1'
PORT = int(sys.argv[2]) if len(sys.argv) > 2 else 12345


class ROBOT_FORCE(ctypes.Structure):
    _fields_ = [('_fForce', ctypes.c_float * 6)]


def main():
    lib = ctypes.CDLL(LIBPATH)

    lib._CreateRobotControl.restype  = ctypes.c_void_p
    lib._CreateRobotControl.argtypes = []

    lib._DestroyRobotControl.restype  = None
    lib._DestroyRobotControl.argtypes = [ctypes.c_void_p]

    lib._open_connection.restype  = ctypes.c_bool
    lib._open_connection.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint]

    lib._close_connection.restype  = ctypes.c_bool
    lib._close_connection.argtypes = [ctypes.c_void_p]

    lib._get_external_torque.restype  = ctypes.POINTER(ROBOT_FORCE)
    lib._get_external_torque.argtypes = [ctypes.c_void_p]

    print(f'[1] 핸들 생성...')
    ctrl = lib._CreateRobotControl()
    print(f'    핸들: {ctrl}')

    print(f'[2] 연결 시도: {IP.decode()}:{PORT}')
    ok = lib._open_connection(ctrl, IP, PORT)
    print(f'    결과: {"성공" if ok else "실패"}')

    if not ok:
        lib._DestroyRobotControl(ctrl)
        print('[!] 연결 실패 — 기존 연결에는 영향 없음')
        return

    print('[3] 1초 대기 (모니터링 데이터 수신 대기)...')
    time.sleep(1.0)

    print('[4] 외력 토크 10회 읽기:')
    for i in range(10):
        ptr = lib._get_external_torque(ctrl)
        if ptr:
            vals = list(ptr.contents._fForce)
            print(f'    [{i}] {[f"{v:+.3f}" for v in vals]}  max={max(abs(v) for v in vals):.3f} Nm')
        else:
            print(f'    [{i}] None 반환')
        time.sleep(0.1)

    print('[5] 연결 종료...')
    lib._close_connection(ctrl)
    lib._DestroyRobotControl(ctrl)
    print('완료. 기존 bringup 정상 동작 여부를 확인하세요.')


if __name__ == '__main__':
    main()
