//
// Created by Hello on 2022-05-05.
//

#include "stack.h"

#include <string.h>


static char Symbol_GetBefore(char c) {
    switch (c) {
        case ']':
            return '[';
        case '}':
            return '{';
        case ')':
            return '(';
        case '>':
            return '<';
        default:
            return '\0';
    }
}

status Symbol_IsBalanced(const char* code_segment) {
    stack* buf_balance = Stack_New(64);
    for (int i = 0; i < strlen(code_segment); i++) {
        switch (code_segment[i]) {
            case '[':
            case '(':
            case '{':
            case '<':
                Stack_Push(code_segment[i], buf_balance);
                break;
            case ']':
            case ')':
            case '}':
            case '>':
                if (Stack_Top(buf_balance) == Symbol_GetBefore(code_segment[i]))
                    Stack_Pop(buf_balance);
                else {
                    printf("Syntax error near %d", i);
                    return 1;
                }
                break;
        }
    }
    if (!Stack_IsEmpty(buf_balance)) {
        printf("Syntax error, not closed");
        return 2;
    }
    puts("Checked");
    return 0;
}