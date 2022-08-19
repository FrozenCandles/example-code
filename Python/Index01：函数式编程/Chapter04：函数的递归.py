

def up_and_down(n):
    print('floor', n)  # 1
    if n < 3:
        up_and_down(n + 1);
    print('floor', n)  # 2

# up_and_down(1)


def factorial(n):
    if n == 1:
        return n
    else:
        return n * factorial(n-1)



def binary_search(seq, left, right, value): 
    if right >= left:
        mid = int(left + (right - left) / 2)
        if seq[mid] < value: 
            return binary_search(seq, mid + 1, right, value) 
        elif seq[mid] > value: 
            return binary_search(seq, left, mid - 1, value) 
        else: 
            return mid 
    else: 
        return -1
  




def tobinary(n):
    if n < 2:
        return str(n)
    else:
        return tobinary(n // 2) + str(n % 2)
    
# print(tobinary(3508))


def fibonacci(n):
    if n > 2:
        return fibonacci(n-1) + fibonacci(n-2);
    else:
        return 1;

def factorial(n, t):
    if (n == 0): 
        return t
    else:
        return factorial(n - 1, t * n)
