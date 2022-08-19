

def series_sum(first, inc, n):
    total = 0
    for _ in range(n):
        total += first
        first += inc
    return total

print(series_sum(1, 2, 5))


# def func(a, b, /, c, d, *, e, f): 
#     pass


def func_with_args(*args):
    print(args, type(args))


def average(*data):
    return sum(data) / len(data)


def func_with_kwargs(**kwargs):
    print(kwargs, type(kwargs))


def triangle_aera(*args):
    if len(args) == 2:
        b, h = args[0], args[1]
        return b * h / 2
    elif len(args) == 3:
        a, b, c = args[0], args[1], args[2]
        s = (a + b + c) / 2
        return (s * (s - a ) * (s - b) * (s - c)) ** 0.5


def log(*values, **options):
    print(f'[{options.get("level")}]', *values)

def print_any(*args, **kwargs):
    if not set(kwargs.keys()) - {'sep', 'end', 'file', 'flush'}:
        print(*args, **kwargs)
    else:
        log(*args, **kwargs)

print_any(1, 2, ['a', 'b'])
print_any(1, 2, ['a', 'b'], sep='--')
print_any(1, 2, ['a', 'b'], level='DEBUG')



def weighted_average(data, weight=None):
    if weight is None:
        return sum(data) / len(data)
    else:
        total = 0
        for i in range(len(data)):
            total += data[i] * weight[i]
        return total / len(data)
    

def make_staggered(seq1, seq2, init=None):
    if init is None:
        init = []
    for i in range(len(seq1)):
        if len(seq2) < i + 1:
            break
        init.append(seq1[i])
        init.append(seq2[i])
    return init

ls_1 = [1, 3, 5, 7, 9]
ls_2 = [2, 4, 6, 8, 10]
make_staggered(ls_1, ls_2)
make_staggered(ls_1, ls_2, ls_1)

ls_3 = [1] * 4
ls_4 = [-1] * 4
make_staggered(ls_3, ls_4)


def f(a, b):
    """_summary_

    Args:
        a (_type_): _description_
        b (_type_): _description_
    """

def fibonacci(n):
    """Return a list containing the Fibonacci series up to n."""
    result = []
    a, b = 0, 1
    while a < n:
        result.append(a)
        a, b = b, a+b
    return result







def fibonacci(n: int) -> List[int]:
    ...

from typing import List

def scale(vector: List[float], scalar: float = 1) -> List[float]:
    result = []
    for i in vector:
        result.append(i * scalar)
    return result



