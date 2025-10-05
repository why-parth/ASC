#include "buffer.h"

/* include these files at the time of compilation. */
// #include "asc_simple_buffer.c"
// #include "asc_type.c"

/* Initializing the Complex Buffers */
__initialiseComplexBuffers

//// /// // / Definitions

/* Definition of Var Buffer */
size_t Var(int p) __auto_define_buffer(Var)

/* Definitions of functions for Var Buffer */

void PushVar(var _Var) { Var Push(_Var) }

void PrintVar(char * in_between) { Var Print(in_between) }

void FreeVar(void) {
   for (struct Var * toFree = getbuffer(Var); !__buffer_exceeded, jumpbuffer(toFree))
   if (toFree->value.type == Str Type) { freestr(toFree->value); }
   __auto_free(Var);
}
