
from itertools import *

count(10)        # => 10 11 12 13 14 ...
count(2.5, 0.5)  # => 2.5 3.0 3.5 ...

cycle('ABC')  # => A B C A B C A B C ...

repeat(10, 3)  # => 10 10 10

accumulate([1, 2, 3, 4, 5])  # => 1 3 6 10 15

chain(range(5), range(10, 20, 2))  # => 0 1 2 3 4 10 12 14 16 18

chain.from_iterable(['ABC', 'DEF'])  # => A B C D E F


from typing import NamedTuple

class Point(NamedTuple):
    x: float
    y: float
    

def cross_product(a, b):
    return a.x * b.y - a.y * b.x

from random import randint
target = filter(lambda _: randint(0, 1), range(50))
for i in groupby(target, key=lambda x: x // 10):
    # print(i[0], list(i[1]))
    ...

compress('ABCDEF', [1, 0, 1, 0, 1, 0])  # => A C E

islice('ABCDEFG', 2)           # => C D E F G
islice('ABCDEFG', 1, None, 2)  # => B D F

dropwhile(lambda x: x < 5, [1, 4, 6, 4, 1])  # => 6 4 1
takewhile(lambda x: x < 5, [1, 4, 6, 4, 1])  # => 1 4

with open('header.csv', 'r') as f:
    data = dropwhile(lambda row: not row[0].isdigit(), f)
    for i in map(lambda row: row.replace('\n', '').split(','), data):
        # print(i)
        ...
        
        
zip_longest('ABCD', 'xy', fillvalue='*')  # => Ax By C* D*

filter(lambda x: x % 2, range(10))       # => 1 3 5 7 9
filterfalse(lambda x: x % 2, range(10))  # => 0 2 4 6 8


starmap(pow, [(2,5), (3,2), (10,3)])  # => 32 9 1000

def starmap(function, *iterables):
    return map(function, zip(iterables))



product(range(3), range(3))  # => 00 01 02 10 11 12 20 21 22
product('AB', repeat=2)      # => AA AB BA BB

from random import choice

list(product(range(1, 14), '♣♦♥♠'))


product(range(10), range(10))


permutations(range(3))   # => 012 021 102 120 201 210
permutations('ABCD', 2)  # => AB AC AD BA BC BD CA CB CD DA DB DC

combinations('ABCD', 2)    # => AB AC AD BC BD CD
combinations(range(4), 3)  # => 012 013 023 123

combinations('ABC', 2)                   # => AB AC BC
combinations_with_replacement('ABC', 2)  # => AA AB AC BB BC CC
