#ifndef __READER_H__
#define __READER_H__
#include <stdio.h>
#include "asc_apc.h"

/* This is function is NOT desingned to actually print raw form
(raw string literal.This function is desingned to provide an
understable debugging experience.

Previously,
    commands would look like this:
        <1 ;>int a = 45;<1 
        >

After this function,
    commands looks like this:
        <1 ;>int a = 45;<1 \n>

Therefore, this function only converts specific escape
sequences to their raw forms. Sequences such as color
codes are NOT taken care of.
*/
int rawChar(char _raw) {
    unsigned int len = 0;
    switch (_raw) {
    
    case '\n': len += printf("\\n") ; break ;
    case '\t': len += printf("\\t")  ; break ;
    case '\v': len += printf("\\v")   ; break ;
    case '\b': len += printf("\\b")    ; break ;
    case '\r': len += printf("\\r")     ; break ;
    case '\f': len += printf("\\f")      ; break ;
    case '\a': len += printf("\\a")      ; break ;
    case '\\': len += printf("\\\\")    ; break ;
    case '\'': len += printf("\\'")    ; break ;
    case '\"': len += printf("\\\"")  ; break ;
    case '\?': len += printf("\\?")  ; break ;
    case '\0': len += printf("\\0") ; break ;
    
    default: len++, putchar(_raw);
    }
    return len;
}

#endif