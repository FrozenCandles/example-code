

def fibonacci(n):
    result = []
    a, b = 0, 1
    while a < n:
        result.append(a)
        a, b = b, a + b
    return result

from math import sqrt
def issqare(n):
    s = int((sqrt(n)))
    return s * s == n

for i in fibonacci(1000):
    if issqare(i):
        # do something
        break





def func():
    yield 3
        
# print(func)


def fibonacci():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b

for i in fibonacci():
    ...
    if issqare(i):
        # do something
        break

for i in fibonacci():
    # print(i, end=' ')
    if i > 30:
        break


def odd():
    i = 0
    while True:
        yield i * 2 + 1
        i += 1

g1 = odd()


for i in g1:
    # print(i, end=' ')
    if i > 15:
        break

for i in g1:
    # print(i, end=' ')
    if i > 30:
        break


def average(l):
    return sum(l) / len(tuple(l))


# 1
g2 = odd()
for i in g2:
    ...
    break
for i in g2:
    ...
    break
# 2
for i in odd():
    ...
    break
for i in odd():
    ...
    break


import os

def get_files(dir):
    for f in os.listdir(dir):
        path = os.path.join(dir, f)
        if os.path.isfile(path):
            yield path
        else:
            yield from get_files(path)







HEADERS = { 
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                  'AppleWebKit/537.36 (KHTML, like Gecko) '
                  'Chrome/91.0.4472.124 Safari/537.36',
    'referer': 'https://www.kuaidaili.com/',
    'content-type': 'text/html;charset:utf-8'
}



# def get_image_links(url):
#     base_url = get_base_url(url)
#     html = requests.get(url, headers=HEADERS, verify=False).text
#     print(base_url)
#     yield from re.finditer(r'src="(https://[-\w\.\/\d].(?:jpg|png|jpeg))"', html)
#     yield from get_image_links(base_url + re.search(r'id="pageNext".+?href="(.+?)"', html).group(1))


# for p in get_image_links('https://sj.zol.com.cn/bizhi/detail_11654_127188.html'):
#     print(p)


ls = ['1', [2, 'a', [['hello'], 'w'], 6], [[['o']], 7, 9], 'd']

def flatten(nest):
    for i in nest:
        if not isinstance(i, list):
            yield i
        else:
            ...
            # for k in flatten(i):
            #     yield k
            yield from flatten(i)




import re
import requests
from lxml import etree

from requests.packages import urllib3
urllib3.disable_warnings()

def get_base_url(url):
    return re.match('(https?://[\d\w\.]+)/', url).group(1)

def get_image_links(url):
    base_url = get_base_url(url)
    html = etree.HTML(requests.get(url, headers=HEADERS, verify=False).text)
    
    yield from html.xpath('.//a[@id="1080x1920"]/@href')
    yield from get_image_links(base_url + html.xpath('.//a[@id="pageNext"]/@href')[0])

# html = etree.HTML(requests.get('https://sj.zol.com.cn/bizhi/detail_11654_127188.html', headers=HEADERS, verify=False).text)

for i in get_image_links('https://sj.zol.com.cn/bizhi/detail_11654_127188.html'):
    print(i)


def xpath(): ...
def xpath_all(): ...
    
def get_images(url):
    ...
    yield from xpath_all('.//div[@class="image"]/img/@href')
    ...
    yield from get_images(get_base_url(url) + xpath('.//a[@id="next-page"]/@href'))


def isprime(i): ...

g = (i ** 2 for i in range(1000) if isprime(i))