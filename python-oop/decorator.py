

from functools import wraps
from functools import update_wrapper
from time import sleep




class CumulativeAverage:
    def __init__(self):
        self.history_count = 0
        self.history_sum = 0
    def __call__(self, *new_data):
        self.history_count += len(new_data)
        self.history_sum += sum(new_data)
        return self.history_sum / self.history_count


class Trace:
    def __init__(self, func):
        self.func = func
        update_wrapper(self, self.func)
    def __call__(self, *args, **kwargs):
        result = None
        try:
            result = self.func(*args, **kwargs)
        except Exception as e:
            result = e
        print(f'{self.func.__name__}{args, kwargs!r} -> {result!r}')
        return result


class Cache:
    def __init__(self, func):
        self.func = func
        update_wrapper(self, self.func)
        self.cache = {}
    def __call__(self, *args, **kwargs):
        try:
            params = (args, frozenset(kwargs.items()))
            return self.cache[params]
        except KeyError:
            result = self.func(*args, **kwargs)
            self.cache[params] = result
            return result
        except TypeError:  # unhashable params
            return self.func(*args, **kwargs)


class Retry:
    def __init__(self, maxnum=5, interval=1.0):
        self.maxnum = maxnum
        self.interval = interval
    def __call__(self, func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            retries = 0
            while retries < self.maxnum:
                try:
                    result = func(*args, **kwargs)
                    return result
                except Exception as e:
                    retries += 1
                    print(f"Exception caught: {e}. Retrying ({retries}/{self.maxnum})...")
                    sleep(self.interval)
            raise RuntimeError(f"Failed after {self.maxnum} retries")
        return wrapper


def trace(cls):
    def traced_func(func):
        if hasattr(func, 'tracing'):  # Only decorate once
            return func
        @wraps(func)
        def wrapper(*args, **kwargs):
            result = None
            try:
                result = func(*args, **kwargs)
            except Exception as e:
                result = e
            print(f'{func.__name__}{args, kwargs!r} -> {result!r}')
            return result
        setattr(wrapper, 'tracing', True)
        return wrapper
    for attr_name in dir(cls):
        attr = getattr(cls, attr_name)
        if not attr_name.startswith('_') and callable(attr):
            setattr(cls, attr_name, traced_func(attr))
    return cls


def trace_to(fp):
    def trace(cls):
        def trace_func(func):
            if hasattr(func, 'tracing'):  # Only decorate once
                return func
            @wraps(func)
            def wrapper(*args, **kwargs):
                result = None
                try:
                    result = func(*args, **kwargs)
                except Exception as e:
                    result = e
                fp.write(f'{func.__name__}{args, kwargs!r} -> {result!r}\n')
                return result
            setattr(wrapper, 'tracing', True)
            return wrapper
        for attr_name in dir(cls):
            attr = getattr(cls, attr_name)
            if not attr_name.startswith('_') and callable(attr):
                setattr(cls, attr_name, trace_func(attr))
        return cls
    return trace




if __name__ == '__main__':

    avg = CumulativeAverage()
    avg(15, 10, 12, 18, 13)  # 13.6
    avg(16, 21, 17, 19)  # 15.66666666
    avg(11, 9, 10)  # 14.25

    @Trace
    def calc(x, y, z):
        return x + y / z

    calc(1, 3, 2)
    calc(1, z=0, y=3)


    @Cache
    def huge_add(a, b):
        """Perform complex addition operations"""
        sleep(2)
        return a + b

    huge_add(1, 2)  # wait for a moment and print result
    huge_add(1, 2)  # immediately print result
    huge_add(a='hello', b=' world')  # wait for a moment and print result
    huge_add(b=' world', a='hello')  # immediately print result
    huge_add('hello', b=' world')  # wait for a moment and print result
    huge_add([1, 2], [2, 3])  # wait for a moment and print result
    huge_add([1, 2], [2, 3])  # wait for a moment and print result

    from random import random

    @Retry(maxnum=3, interval=0.5)
    def send_message():
        if random() < 0.8:
            raise ValueError("Network failure")
        return "Success"

    status = send_message()
    print("Status:", status)


    log_file = open('trace.log', 'a', encoding='utf8')

    @trace_to(log_file)
    class TracedList(list):
        pass

    ls = TracedList(range(5))
    ls.append(10)
    ls.extend(ls.copy())
    ls.pop()
    ls.sort(key=lambda e: abs(e-5), reverse=True)

    log_file.close()
