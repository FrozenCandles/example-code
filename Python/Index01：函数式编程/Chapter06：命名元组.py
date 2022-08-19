
{(3, 8, 1): 'hello'}

[('a', 1, True), ('c', 2, False), ('k', 3, True)]

from collections import namedtuple

Point = namedtuple('Point', ['x', 'y', 'z'])
p01 = Point(3, 4, 8)
print(p01)

# print(p01[0], p01.y)

# OneTuple = namedtuple('OneTuple', ['abc', 'def', 'ghi', 'abc'], defaults=['1', '2', '3'], rename=True)
# print(OneTuple._fields) 

p02 = p01._replace(x=10, z=12)
p02


from typing import NamedTuple

class Student(NamedTuple):
    name: str
    age: int
    score: float

s = Student('Peter', 21, 62.0)


print(dir(Student))





# for cls in object.__subclasses__():
#     if '__set__' in dir(cls):
#         print(cls)
        


# <class 'property'>
# <class 'getset_descriptor'>
# <class 'member_descriptor'>
# <class 'types.DynamicClassAttribute'>
# <class '_collections._tuplegetter'>