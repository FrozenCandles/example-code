//
// Created by Hello on 2022-05-08.
//

#ifndef DATASTRUCTURE_PUBDEF_H
#define DATASTRUCTURE_PUBDEF_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef int elemtype;
typedef uint16_t status;

#define __VA_ARGS_N(_9, _8, _7, _6, _5, _4, _3, _2, _1, _0, N, ...) N
#define VA_ARGS_N(...) __VA_ARGS_N(0, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define __range_1(var, n) (int var = 0; var < n; var++)
#define __range_2(var, a, b) (int var = a; var < b; var++)
#define __range_3(var, start, stop, step) (int var = start; var < stop; var += step)
#define __range_n_cat(a, b) a ## b
#define __range_n(n) __range_n_cat(__range_, n)
#define __range(...) __range_n(VA_ARGS_N(__VA_ARGS__))
#define range(var, ...)  __range(__VA_ARGS__)(var, __VA_ARGS__)


#define BUFSIZE 1024
#define TYPESIGNAL(X) _Generic((X),\
    int: "%d", float : "%f", double: "%f", char: "%c", char*: "%s", default: "%d")
#define printv(var) do {                                                          \
        char __print_buf[BUFSIZE], __format_buf[BUFSIZE] = "val of " #var ": ";   \
        sprintf(__print_buf, strcat(__format_buf, TYPESIGNAL(var)), var);         \
        puts(__print_buf);                                                        \
} while(0)


#endif //DATASTRUCTURE_PUBDEF_H
