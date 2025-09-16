#include "buffer.h"

/* Defining the Buffer "fvar" */
size_t Var (void) __auto_define_buffer(Var)

/* Constant Initialisation */
unsigned int __number_of_buffers = 0;
size_t __active_buffer = 0;
unsigned long long __printedBufferLength = 0;

/* Helping Utility (for buffer "Var") */
size_t __VarSetIndex = 0;

var GetVar = {0, {0}, NULL};

var __var_of_raw(void) {

    var ret;
    ret.type = Str Type;
    ret.value.Int = raw.length;
    ret.next = (var *) strRaw;

    return ret;
}

