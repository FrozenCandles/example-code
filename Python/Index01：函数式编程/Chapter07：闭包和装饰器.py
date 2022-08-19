
def func():
    n = 10
    def inner_n():
        return n
    return inner_n

inner_func = func()
del func
# print(inner_func())

from itertools import starmap

def polinomial(*coeffs):
    def inner(x):
        return sum(starmap(lambda i, coeff: coeff * x ** i,
                           enumerate(reversed(coeffs)))
                   )
    return inner

regr01 = polinomial(2, 1)
regr02 = polinomial(4, 3, 7, 2)



def func():
    n = 10
    def inner_n():
        n += 1
        return n
    return inner_n

inner = func()
print(inner())
print(inner())




# decorators

def demo01():
    print('hello')

def demo02():
    return 'hello'


from time import localtime, strftime



def log(func):
    result = func()
    print(f'[{strftime("%H:%M:%S", localtime())}]'
          f' {func.__name__} returns {result}')
    return result

log(demo01)
type(log(demo02))



double = polinomial(2, 0)
triple = polinomial(3, 0)

def log(func):
    def inner_func(*args, **kwargs):
        result = func(*args, **kwargs)
        print(f'[{strftime("%H:%M:%S", localtime())}]'
            f' {func.__name__} returns {result}')
        return result
    return inner_func

double = log(double)
triple = log(triple)

triple(3) * 8

@log
def four_times(x):
    return x * 4




from time import perf_counter

def timer(func):
    def wrapper(*args, **kwargs):
        start = perf_counter()
        result = func(*args, **kwargs)
        print(f'{func.__name__} execs {perf_counter() - start} second(s)')
        return result
    return wrapper


def log(time=True, check_arg=False):
    def outer_wrapper(func):
        def inner_wrapper(*args, **kwargs):
            result = func(*args, **kwargs)
            if time:
                print(f'[{strftime("%H:%M:%S", localtime())}]', end=' ')
            print(func.__name__, end='')
            if check_arg:
                print('(', *args, *[f'{k}={v}' for k, v in kwargs.items()], ')', end='')
            print(f' returns {result}')

            return result
        return inner_wrapper
    return outer_wrapper

@log(check_arg=True)
def isprime(number: int):
    for i in range(2, number // 2):
        if number % i == 0:
            return False
    return True

def prime_factorization(number: int):
    factors = []
    while not isprime(number):
        for i in range(2, number // 2):
            if number % i == 0:
                factors.append(i)
                number //= i
                break
    factors.append(number)
    return factors

# print(prime_factorization(6108984))


def locals_cache(func):
    def inner_func(*args, **kwargs):
        result = func(*args, **kwargs)

        return result
    return inner_func


@log(time=False)
def func(*args, **kwargs):
    n = 10
    cached_locals = locals()
    def _locals():
        return cached_locals
    func.locals = _locals
    ...
    return args

func(10, 20, length=2)
# print(func.locals())



def html_tag(tag: str, **attrs):
    def outer_func(func):
        def inner_func(contain: str):
            attr = ''.join([f' {k}="{v}"' for k, v in attrs.items()])
            return '<{0}{1}>{2}</{0}>'.format(tag, attr, func(contain))
        return inner_func
    return outer_func





def html_tag(tag: str, **attrs):
    def outer_func(func):
        def inner_func(contain: str):
            ...
        inner_func.__name__ = func.__name__
        inner_func.__doc__ = func.__doc__
        # many attributes need to update
        return inner_func
    return outer_func


from functools import wraps

def html_tag(tag: str, **attrs):
    def outer_func(func):
        @wraps(func)
        def inner_func(contain: str):
            ...
        return inner_func
    return outer_func




from re import sub

@html_tag('p')
@html_tag('a', href='javascript: upload(this);')
def legalize(string):
    """Make the string a valid filename"""
    return sub(r'[\\\/:*?"<>|]', ' ', string)

# print(legalize('<User>: name'))

print(help(legalize))





from flask import Flask, render_template

app = Flask(__name__)

@app.route('/', methods=['GET'])
def main():
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)





def decorator(func): ...

@decorator
def function():
    ...