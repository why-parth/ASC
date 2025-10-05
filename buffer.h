#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "asc_type.h"
#include "asc_simple_buffer.h"
#include "asc_complex_buffer.h"

//// /// // / Declarations

/* Declaration of Var Buffer */
__declare_buffer(Var, var);

/* Declarations of functions for Var Buffer */

// Pushes a var on to the Buffer Var
void PushVar(var _Var);

// Prints the Buffer Var
void PrintVar(char * in_between);

// Frees the Buffer Var
void FreeVar(void);

//// /// // / Initializing the Complex Buffer Command

/* Initializing the 'Push' Complex Buffer Command */
#define Push(value) (1); __auto_push(Var, value)

/* Initializing the 'Print' Complex Buffer Command */
#define Print(in_between) (1); __auto_print_custom(Var, in_between, __printedBufferLength += printf(StringOf varBuff->value.type) + print("\t%", varBuff->value))

/* Initializing the 'Free' Complex Buffer Command */
#define Free (1); forBuffer(Var) { FreeVar(); }

#endif