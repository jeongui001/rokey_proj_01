# generated from rosidl_generator_py/resource/_idl.py.em
# with input from cobot1_interfaces:msg/BlockTask.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_BlockTask(type):
    """Metaclass of message 'BlockTask'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('cobot1_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'cobot1_interfaces.msg.BlockTask')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__block_task
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__block_task
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__block_task
            cls._TYPE_SUPPORT = module.type_support_msg__msg__block_task
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__block_task

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class BlockTask(metaclass=Metaclass_BlockTask):
    """Message class 'BlockTask'."""

    __slots__ = [
        '_y_position',
        '_color',
        '_block_type',
    ]

    _fields_and_field_types = {
        'y_position': 'double',
        'color': 'string',
        'block_type': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.y_position = kwargs.get('y_position', float())
        self.color = kwargs.get('color', str())
        self.block_type = kwargs.get('block_type', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.y_position != other.y_position:
            return False
        if self.color != other.color:
            return False
        if self.block_type != other.block_type:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def y_position(self):
        """Message field 'y_position'."""
        return self._y_position

    @y_position.setter
    def y_position(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'y_position' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'y_position' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._y_position = value

    @builtins.property
    def color(self):
        """Message field 'color'."""
        return self._color

    @color.setter
    def color(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'color' field must be of type 'str'"
        self._color = value

    @builtins.property
    def block_type(self):
        """Message field 'block_type'."""
        return self._block_type

    @block_type.setter
    def block_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'block_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'block_type' field must be an unsigned integer in [0, 255]"
        self._block_type = value
