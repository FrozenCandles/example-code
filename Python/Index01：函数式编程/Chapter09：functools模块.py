
from functools import *



def fibonacci(n):
    if n < 2:
        return n
    else:
        return fibonacci(n - 1) + fibonacci(n - 2)

@lru_cache(maxsize=1024)
def fibonacci_cached(n):
    if n < 2:
        return n
    else:
        return fibonacci_cached(n - 1) + fibonacci_cached(n - 2)
        
from time import perf_counter

def timer(func):
    def wrapper(*args, **kwargs):
        start = perf_counter()
        result = func(*args, **kwargs)
        print(f'{func.__name__} execs {perf_counter() - start} second(s)')
        return result
    return wrapper

@timer
def fibonacci_without_cache():
    return fibonacci(40)

@timer
def fibonacci_with_cache():
    fibonacci_cached.cache_clear()
    return fibonacci_cached(40)


# print(fibonacci_with_cache())
# print(fibonacci_without_cache())


uopen = partial(open, encoding='utf8')
with uopen('demo.txt', 'w') as f:
    f.write('🙁✯⛈⚝☂☁︎😶')


from operator import add, mul

sum = partial(reduce, add) 
prod = partial(reduce, mul) 


@singledispatch
def scale(data, scalar):
    ...
    
@scale.register(float)
def _scale(data: float, scalar):
    return data * scalar



@scale.register(tuple)
@scale.register(list)
def _scale(data, scalar):
    ...
    return list(map(lambda x: x * scalar, data))


print(scale(0.7, 2))
print(scale(list(range(10)), 0.3))
