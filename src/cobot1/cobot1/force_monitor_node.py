"""
force_monitor_node.py
DRFL 직접 연결(ctypes)로 외력을 100Hz로 감지하고 /robot/force_detected를 발행한다.
ROS2 executor와 완전 독립이므로 movel 실행 중에도 실시간 감지 가능하다.
외력 감지 시 현재 동작 완료 후 정지(_step()에서 pause_event 체크).
"""
from __future__ import annotations

import ctypes
import time
from threading import Thread

import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool

_LIBPATH = (
    '/home/hwangjeongui/ws_cobot_pjt/ws_edu/'
    'install/dsr_hardware2/lib/libdsr_hardware2.so'
)
_DEFAULT_IP   = '192.168.1.100'
_DEFAULT_PORT = 12345


class _RobotForce(ctypes.Structure):
    _fields_ = [('_fForce', ctypes.c_float * 6)]


class ForceMonitorNode(Node):

    def __init__(self) -> None:
        super().__init__('force_monitor')

        self.declare_parameter('robot_ip',            _DEFAULT_IP)
        self.declare_parameter('robot_port',          _DEFAULT_PORT)
        self.declare_parameter('torque_threshold_nm', 7.3)
        self.declare_parameter('poll_hz',             100.0)
        self.declare_parameter('reset_below_count',   20)

        robot_ip        = self.get_parameter('robot_ip').value.encode()
        robot_port      = int(self.get_parameter('robot_port').value)
        self._threshold = float(self.get_parameter('torque_threshold_nm').value)
        poll_hz         = float(self.get_parameter('poll_hz').value)
        self._reset_n   = int(self.get_parameter('reset_below_count').value)
        self._interval  = 1.0 / poll_hz

        self._pub = self.create_publisher(Bool, '/robot/force_detected', 1)

        lib = ctypes.CDLL(_LIBPATH)
        lib._CreateRobotControl.restype  = ctypes.c_void_p
        lib._CreateRobotControl.argtypes = []
        lib._DestroyRobotControl.restype  = None
        lib._DestroyRobotControl.argtypes = [ctypes.c_void_p]
        lib._open_connection.restype  = ctypes.c_bool
        lib._open_connection.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint]
        lib._close_connection.restype  = ctypes.c_bool
        lib._close_connection.argtypes = [ctypes.c_void_p]
        lib._get_external_torque.restype  = ctypes.POINTER(_RobotForce)
        lib._get_external_torque.argtypes = [ctypes.c_void_p]
        self._lib = lib

        ctrl = lib._CreateRobotControl()
        ok   = lib._open_connection(ctrl, robot_ip, robot_port)

        if ok:
            self._ctrl = ctrl
            Thread(target=self._poll_loop, daemon=True).start()
            self.get_logger().info(
                f'ForceMonitor 시작: {robot_ip.decode()}:{robot_port}, '
                f'threshold={self._threshold:.1f} Nm, {poll_hz:.0f} Hz'
            )
        else:
            self._ctrl = None
            self.get_logger().error(
                f'DRFL 연결 실패: {robot_ip.decode()}:{robot_port}'
            )

    def _poll_loop(self) -> None:
        triggered   = False
        below_count = 0

        while True:
            time.sleep(self._interval)

            ptr = self._lib._get_external_torque(self._ctrl)
            if not ptr:
                continue

            torques    = list(ptr.contents._fForce)
            max_torque = max(abs(t) for t in torques)

            if max_torque > self._threshold:
                below_count = 0
                if not triggered:
                    triggered = True
                    msg       = Bool()
                    msg.data  = True
                    self._pub.publish(msg)
                    self.get_logger().warn(
                        f'외력 감지: max={max_torque:.2f} Nm > {self._threshold:.1f} Nm'
                    )
            else:
                if triggered:
                    below_count += 1
                    if below_count >= self._reset_n:
                        triggered   = False
                        below_count = 0

    def destroy_node(self) -> None:
        if self._ctrl is not None:
            self._lib._close_connection(self._ctrl)
            self._lib._DestroyRobotControl(self._ctrl)
        super().destroy_node()


def main(args=None) -> None:
    rclpy.init(args=args)
    node = ForceMonitorNode()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()
