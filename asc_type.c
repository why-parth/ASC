#include "asc_type.h"


/* --------------------------------------| Standard Declaratons |-------------------------------------- */

char * __nameOfType = "None\0-\0Int\0--\0Char\0-\0Float\0\0Str\0--";

union _val_ __tempVal;
struct _var_ *__handleStr = NULL;
var NoValue = {0, {0}, NULL};

/* --------------------------------------| Standard Datatypes |-------------------------------------- */

struct _var_ Int(long int _int) {
    struct _var_ ret;
    ret.type = 1;
    ret.value.Int = _int;
    ret.next = NULL;
    return ret;
}

struct _var_ Char(char _char) {
    struct _var_ ret;
    ret.type = 2;
    ret.value.Char = _char;
    ret.next = NULL;
    return ret;
}

struct _var_ Float(double _float) {
    struct _var_ ret;
    ret.type = 3;
    ret.value.Float = _float;
    ret.next = NULL;
    return ret;
}

/* --------------------------------------| Included Datatypes |-------------------------------------- */

/* Dayatype : Str (String) (Dynamically Allocated) */

struct _var_ Str(char * _str) {

    struct _var_ ret;
    ret.type = 4;
    if (_str == 0) return ret;

    unsigned long int len = 0;
    while (_str[len] != '\0') len++;
    ret.value.Int = len;

    char * mallocStr = (char *)malloc(sizeof(char) * (len + 1));
    strcpy(mallocStr, _str);

    ret.next = (struct _var_ *)mallocStr;
    return ret;
}

unsigned long int __printLinkedVars(struct _var_ * _linkedVar) {
    if (_linkedVar->next == NULL) return putchar(_linkedVar->value.Char);
    else return putchar(_linkedVar->value.Char) + __printLinkedVars(_linkedVar->next);
}

unsigned long int __printStr(struct _var_ _str) {
    unsigned long int len = _str.value.Int;
    char * strPtr = (char *)(_str.next); 
    for (unsigned int i = 0; i < len; i++) {
        putchar(strPtr[i]);
    }
    return len;
}

/* -----------------| Standard Functions and DOS(s) for Above Defined Datatypes |----------------- */

struct _var_ __toInt(var * _str) {
    __handleStr = _str;
    struct _var_ ret = * _str;
    long int value = 0;

    int negate = 1;
    if (getstr(ret)[0] =='-') {
        negate = -1;
        ret.next = (var *)(getstr(ret) + 1);
        ret.value.Int--;
    }

    for (int i = 0; i < ret.value.Int; i++) {
        value *= 10;
        value += (getstr(ret)[i] - 48); 
    }
    value *= negate;

    ret.type = Int Type;
    ret.value.Int = value;

    return ret;
}

struct _var_ __toFloat(var * _str) {
    __handleStr = _str;
    struct _var_ ret = * _str;
    
    var a, b;
    typeofFloat least = 1.0;

    a = ret;
    a.value.Int = 0;
    while (getstr(a)[a.value.Int] != '.' && a.value.Int < ret.value.Int) a.value.Int++;
    
    b = ret;
    b.value.Int = ret.value.Int - a.value.Int - 1;
    b.next = (var *)((char *)b.next + a.value.Int + 1);
    
    for (int i = 0; i < b.value.Int; i++) least *= 10;
    
    a = __toInt(&a);
    b = __toInt(&b);

    if (ret.value.Int == a.value.Int) {
        ret.type = Int Type;
        ret.value.Int = a.value.Int;
    } else {
        ret.type = Float Type;
        ret.value.Float = (typeofFloat)a.value.Int + (typeofFloat)b.value.Int/least;
    }
    
    return ret;
}

unsigned long int print(const char * _format, ...) {
    unsigned long int ret = 0;
    int ret_delta = 0;

    char curr = _format[ret];
    char prev;
    char read = 0;

    var arg;
    va_list args;
    va_start(args, _format);

    while (curr != '\0' || read) {

        if (curr == __printFormatSpecifier && read == 0) read = 1;

        else if (curr != __printFormatSpecifier && read) {
            read = 0;

            arg = va_arg(args, struct _var_);

            if      (arg.type == Int Type)      ret_delta += printf("%ld", arg.value.Int);
            else if (arg.type == Char Type)     ret_delta += printf("%c", arg.value.Char);
            else if (arg.type == Float Type)    ret_delta += printf("%lf", arg.value.Float);
            else if (arg.type == Str Type)      ret_delta += __printStr(arg);

            ret_delta--, putchar(curr);
        }

        else if (curr == __printFormatSpecifier && read) read = 0, ret_delta--, putchar(curr);

        else putchar(curr);

        if (curr != '\0') prev = curr, curr = _format[++ret];
    }

    return ret + ret_delta;
}

struct _var_ istream = {4, {0}, NULL};
