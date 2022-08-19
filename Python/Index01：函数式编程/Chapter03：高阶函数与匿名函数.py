


def call(f, *args, **kwargs):
    return f(*args, **kwargs)


lambda x, y : x + y ** 2

def all(iterable):
    for element in iterable:
        if not element:
            return False
    return True

def any(iterable):
    for element in iterable:
        if element:
            return True
    return False


def average(iterable):
    seq = tuple(iterable)
    return sum(seq) / len(seq)

print(average(map(abs, [1, 2, -3])))


names = ['John', 'Tim', 'Marry', ...]
ages = [14, 12, 13, ...]
scores = [74, 79, 86, ...]

for i in range(len(names)):
    names[i], ages[i], scores[i]
    ...
    
for name, age, score in zip(names, ages, scores):
    ...
    
def find_element(seq, target):
    for i, elem in enumerate(seq):
        if elem == target:
            return i


students = [('John', 14, 74), ('Tim', 12, 79), 
            ('Marry', 13, 86), ('Hans', 13, 81)]

seq = [2, 3, 5, 7, 8, 9, 10]
result = map(lambda elem: elem / 2 if elem % 2 == 0 else elem ** 2, seq)
# print(list(result))

from functools import reduce
from re import S

import numpy as np
space = np.arange(10 ** 4).reshape((10, 10, 10, 10))
coordinate = [1, 5, 7, 2]

elem = reduce(np.ndarray.__getitem__, [space] + coordinate)
print(elem)

print(space[1][5][7][2])