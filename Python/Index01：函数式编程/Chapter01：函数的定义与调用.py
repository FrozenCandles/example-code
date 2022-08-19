
ls = [2, 4, 6, 7, 4]

total = 0
for i in ls:
    total += i
     
total = sum(ls)

def print_separator():
    print('===============')

# print_separator()
# print('name: John')
# print('job: Programmer')
# print_separator()

def average(seq):
    total = length = 0
    for i in seq:
        total += i
        length += 1
    print('average: ', total / length)


# average(ls)

def triangle_aera(a, b, c):
    s = (a + b + c) / 2
    print('Aera of this triangle is',
            (s * (s - a ) * (s - b) * (s - c)) ** 0.5)
    
# triangle_aera(1, 2, 2.236)

def get_max(seq):
    if not seq:
        return
    max_value = seq[0]
    for i in seq:
        if i > max_value:
            max_value = i
    return max_value

result = get_max([2, 4, 6, 7, 4])


def length(seq):
    n = 0
    for i in seq:
        n += 1
    # del n
    # return

# print(n)

n = 1

def inc():
    n += 1

n = []

def inc():
    n.append(1)


def bubble_sort(seq):
    for i in range(1, len(seq)):
        for j in range(0, len(seq)-i):
            if seq[j] > seq[j+1]:
                seq[j], seq[j + 1] = seq[j + 1], seq[j]
    return seq

data = [5, 1, 4, 3, 10, 4, 2, 7, 7, 9]
# print(bubble_sort(data))
# print(data)

n = 3
# print(n)      # n 为定义的值
def test01(n) :
    print(n)  # n 为使用的参数
    n = 10
    print(n)  # n 为重新定义的值
# test01(5)
# print(n)      # n 仍为函数体外定义的值

# im = 1
# print(id(im))
# def modify_im(im):
#     print(id(im))
#     im = 5
#     print(id(im))
# modify_im(im)
# print(id(im))

m = [1]
# print(id(m))
def modify_m(m):
    print(id(m))
    m.append(5)
    print(id(m))
# modify_m(m)
# print(id(m))


im = 1
print(id(im))
def modify_im():
    global im    
    print(id(im))
    im = 5
    print(id(im))
modify_im()
print(id(im))


