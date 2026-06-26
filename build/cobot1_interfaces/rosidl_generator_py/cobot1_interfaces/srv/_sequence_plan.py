# generated from rosidl_generator_py/resource/_idl.py.em
# with input from cobot1_interfaces:srv/SequencePlan.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SequencePlan_Request(type):
    """Metaclass of message 'SequencePlan_Request'."""

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
                'cobot1_interfaces.srv.SequencePlan_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__sequence_plan__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__sequence_plan__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__sequence_plan__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__sequence_plan__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__sequence_plan__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SequencePlan_Request(metaclass=Metaclass_SequencePlan_Request):
    """Message class 'SequencePlan_Request'."""

    __slots__ = [
        '_colors',
        '_grid_width',
        '_grid_height',
    ]

    _fields_and_field_types = {
        'colors': 'sequence<string>',
        'grid_width': 'uint32',
        'grid_height': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.colors = kwargs.get('colors', [])
        self.grid_width = kwargs.get('grid_width', int())
        self.grid_height = kwargs.get('grid_height', int())

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
        if self.colors != other.colors:
            return False
        if self.grid_width != other.grid_width:
            return False
        if self.grid_height != other.grid_height:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def colors(self):
        """Message field 'colors'."""
        return self._colors

    @colors.setter
    def colors(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'colors' field must be a set or sequence and each value of type 'str'"
        self._colors = value

    @builtins.property
    def grid_width(self):
        """Message field 'grid_width'."""
        return self._grid_width

    @grid_width.setter
    def grid_width(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'grid_width' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'grid_width' field must be an unsigned integer in [0, 4294967295]"
        self._grid_width = value

    @builtins.property
    def grid_height(self):
        """Message field 'grid_height'."""
        return self._grid_height

    @grid_height.setter
    def grid_height(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'grid_height' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'grid_height' field must be an unsigned integer in [0, 4294967295]"
        self._grid_height = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SequencePlan_Response(type):
    """Metaclass of message 'SequencePlan_Response'."""

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
                'cobot1_interfaces.srv.SequencePlan_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__sequence_plan__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__sequence_plan__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__sequence_plan__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__sequence_plan__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__sequence_plan__response

            from cobot1_interfaces.msg import BlockTask
            if BlockTask.__class__._TYPE_SUPPORT is None:
                BlockTask.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SequencePlan_Response(metaclass=Metaclass_SequencePlan_Response):
    """Message class 'SequencePlan_Response'."""

    __slots__ = [
        '_error_message',
        '_tasks',
    ]

    _fields_and_field_types = {
        'error_message': 'string',
        'tasks': 'sequence<cobot1_interfaces/BlockTask>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['cobot1_interfaces', 'msg'], 'BlockTask')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.error_message = kwargs.get('error_message', str())
        self.tasks = kwargs.get('tasks', [])

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
        if self.error_message != other.error_message:
            return False
        if self.tasks != other.tasks:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def error_message(self):
        """Message field 'error_message'."""
        return self._error_message

    @error_message.setter
    def error_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'error_message' field must be of type 'str'"
        self._error_message = value

    @builtins.property
    def tasks(self):
        """Message field 'tasks'."""
        return self._tasks

    @tasks.setter
    def tasks(self, value):
        if __debug__:
            from cobot1_interfaces.msg import BlockTask
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, BlockTask) for v in value) and
                 True), \
                "The 'tasks' field must be a set or sequence and each value of type 'BlockTask'"
        self._tasks = value


class Metaclass_SequencePlan(type):
    """Metaclass of service 'SequencePlan'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('cobot1_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'cobot1_interfaces.srv.SequencePlan')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__sequence_plan

            from cobot1_interfaces.srv import _sequence_plan
            if _sequence_plan.Metaclass_SequencePlan_Request._TYPE_SUPPORT is None:
                _sequence_plan.Metaclass_SequencePlan_Request.__import_type_support__()
            if _sequence_plan.Metaclass_SequencePlan_Response._TYPE_SUPPORT is None:
                _sequence_plan.Metaclass_SequencePlan_Response.__import_type_support__()


class SequencePlan(metaclass=Metaclass_SequencePlan):
    from cobot1_interfaces.srv._sequence_plan import SequencePlan_Request as Request
    from cobot1_interfaces.srv._sequence_plan import SequencePlan_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
