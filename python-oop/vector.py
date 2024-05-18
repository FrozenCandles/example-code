
from math import sqrt
from collections.abc import Sequence
from numbers import Real
from functools import singledispatchmethod
import re


class Vector3D:
    dimensions = 3
    __slots__ = ['_x', '_y', '_z']
    __format_pattern = re.compile(r'(?<!%)%([xyz])')

    def __init__(self, x: Real, y: Real, z: Real) -> None:
        self._x, self._y, self._z = x, y, z

    def __add__(self, other):
        """
        Vector3D supports the addition
        
        Example
        -------
            >>> v01 + v02
            Vector(5, 9, 4)
        """
        return Vector3D(self._x + other.x, self._y + other.y, self._z + other.z)
    def __sub__(self, other):
        return Vector3D(self._x - other.x, self._y - other.y, self._z - other.z)
    def __matmul__(self, other):
        return Vector3D(self._y * other.z - self._z * other.y,
                        self._z * other.x - self._x * other.z,
                        self._x * other.y - self._y * other.x)

    # def __mul__(self, other):
    #     if isinstance(other, Real):
    #         return Vector3D(self._x * other, self._y * other, self._z * other)
    #     elif isinstance(other, Vector3D):
    #         return self._x * other._x + self._y * other._y + self._z * other._z
    #     else:
    #         return NotImplemented

    @property
    def x(self):
        return self._x
    @property
    def y(self):
        return self._y
    @property
    def z(self):
        return self._z

    @singledispatchmethod
    def __mul__(self, other):
        return NotImplemented

    __radd__ = __add__
    __rmul__ = __mul__

    def __iadd__(self, other):
        self._x += other.x
        self._y += other.y
        self._z += other.z
        return self
    def __imul__(self, other: Real):
        self._x *= other
        self._y *= other
        self._z *= other
        return self
    def __isub__(self, other):
        self._x -= other.x
        self._y -= other.y
        self._z -= other.z
        return self

    def __abs__(self):
        return sqrt(self._x ** 2 + self._y ** 2 + self._z ** 2)
    def __pos__(self):
        return Vector3D(self._x, self._y, self._z)
    def __neg__(self):
        return Vector3D(-self._x, -self._y, -self._z)

    def __eq__(self, other):
        return self._x == other.x and self._y == other.y and self._z == other.z


    def __str__(self) -> str:
        return f'Vector({self._x}, {self._y}, {self._z})'
    __repr__ = __str__

    def __hash__(self):
        """
        __hash__ allows Vector3D be a key of dictionary
        
        Example
        -------
            >>> {v01: 10, v02: 20}
            {Vector(2, 2, -4): 10, Vector(2, 4, 3): 20}

        """
        return hash(self._x) ^ hash(self._y) ^ hash(self._z)

    def __format_getattr(self, match: re.Match):
        return str(getattr(self, match.group(1)))

    def __format__(self, format_spec='(%x, %y, %z)'):
        value_formated = self.__format_pattern.sub(self.__format_getattr, format_spec)
        return value_formated.replace('%%', '%')

    def __iter__(self):
        return (i for i in (self.x, self.y, self.z))


@Vector3D.__mul__.register
def __dispatch(self, other: Real):
    return Vector3D(self.x * other, self.y * other, self.z * other)
@Vector3D.__mul__.register
def __dispatch(self, other: Vector3D):
    return self.x * other.x + self.y * other.y + self.z * other.z
@Vector3D.__mul__.register
def __dispatch(self, other: Sequence):
    return self.x * other[0] + self.y * other[1] + self.z * other[2]





if __name__ == '__main__':

    v01 = Vector3D(3, 5, 1)
    v02 = Vector3D(2, 4, 3)
    print(f'{v01=}')
    print(f'{v02=}')

    print(f'{v01 - v02=}')
    print(f'{v01 @ v02=}')
    print(f'{v01 * v02=}')
    print(f'{v01 * 2=}')
    print(f'{v01 * [2, 3, 4]=}')
    print(f'{2 * v01=}')
    v01 *= 2
    print(f'{v01=}')
    print(f'{-v01=}')
    print(f'{abs(v01)=}')
    print(f'{Vector3D(1.0, 2.0, 3.0) == Vector3D(1, 2, 3)=}')
    print(f'{Vector3D(1.01, 2.0, 3.0) == Vector3D(1, 2, 3)=}')
    print(f'v01 = {v01:(%x, %y, %z)}')

    x, y, z = v01
    print(x, y, z)
