# generated from rosidl_generator_py/resource/_idl.py.em
# with input from cobot1_interfaces:srv/ProcessMosaic.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ProcessMosaic_Request(type):
    """Metaclass of message 'ProcessMosaic_Request'."""

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
                'cobot1_interfaces.srv.ProcessMosaic_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__process_mosaic__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__process_mosaic__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__process_mosaic__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__process_mosaic__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__process_mosaic__request

            from sensor_msgs.msg import Image
            if Image.__class__._TYPE_SUPPORT is None:
                Image.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ProcessMosaic_Request(metaclass=Metaclass_ProcessMosaic_Request):
    """Message class 'ProcessMosaic_Request'."""

    __slots__ = [
        '_input_image',
        '_grid_rows',
        '_grid_cols',
    ]

    _fields_and_field_types = {
        'input_image': 'sensor_msgs/Image',
        'grid_rows': 'uint32',
        'grid_cols': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['sensor_msgs', 'msg'], 'Image'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from sensor_msgs.msg import Image
        self.input_image = kwargs.get('input_image', Image())
        self.grid_rows = kwargs.get('grid_rows', int())
        self.grid_cols = kwargs.get('grid_cols', int())

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
        if self.input_image != other.input_image:
            return False
        if self.grid_rows != other.grid_rows:
            return False
        if self.grid_cols != other.grid_cols:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def input_image(self):
        """Message field 'input_image'."""
        return self._input_image

    @input_image.setter
    def input_image(self, value):
        if __debug__:
            from sensor_msgs.msg import Image
            assert \
                isinstance(value, Image), \
                "The 'input_image' field must be a sub message of type 'Image'"
        self._input_image = value

    @builtins.property
    def grid_rows(self):
        """Message field 'grid_rows'."""
        return self._grid_rows

    @grid_rows.setter
    def grid_rows(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'grid_rows' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'grid_rows' field must be an unsigned integer in [0, 4294967295]"
        self._grid_rows = value

    @builtins.property
    def grid_cols(self):
        """Message field 'grid_cols'."""
        return self._grid_cols

    @grid_cols.setter
    def grid_cols(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'grid_cols' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'grid_cols' field must be an unsigned integer in [0, 4294967295]"
        self._grid_cols = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ProcessMosaic_Response(type):
    """Metaclass of message 'ProcessMosaic_Response'."""

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
                'cobot1_interfaces.srv.ProcessMosaic_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__process_mosaic__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__process_mosaic__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__process_mosaic__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__process_mosaic__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__process_mosaic__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ProcessMosaic_Response(metaclass=Metaclass_ProcessMosaic_Response):
    """Message class 'ProcessMosaic_Response'."""

    __slots__ = [
        '_success',
        '_message',
        '_colors',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'message': 'string',
        'colors': 'sequence<string>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())
        self.message = kwargs.get('message', str())
        self.colors = kwargs.get('colors', [])

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
        if self.success != other.success:
            return False
        if self.message != other.message:
            return False
        if self.colors != other.colors:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value

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


class Metaclass_ProcessMosaic(type):
    """Metaclass of service 'ProcessMosaic'."""

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
                'cobot1_interfaces.srv.ProcessMosaic')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__process_mosaic

            from cobot1_interfaces.srv import _process_mosaic
            if _process_mosaic.Metaclass_ProcessMosaic_Request._TYPE_SUPPORT is None:
                _process_mosaic.Metaclass_ProcessMosaic_Request.__import_type_support__()
            if _process_mosaic.Metaclass_ProcessMosaic_Response._TYPE_SUPPORT is None:
                _process_mosaic.Metaclass_ProcessMosaic_Response.__import_type_support__()


class ProcessMosaic(metaclass=Metaclass_ProcessMosaic):
    from cobot1_interfaces.srv._process_mosaic import ProcessMosaic_Request as Request
    from cobot1_interfaces.srv._process_mosaic import ProcessMosaic_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
