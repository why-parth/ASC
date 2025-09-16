#ifndef __READER_H__
#define __READER_H__
#include <stdio.h>

#include "asc_type.h"
#include "asc_simple_buffer.h"
#include "asc_complex_buffer.h"

/* Declaring the Buffer "fvar" */
__declare_buffer(Var, var);

/* Automates your printing logic (prints the var equivalent). */
#define __auto_print_var(name, btw)                                                                             \
       if (__active_buffer == name()) {                                                                         \
              struct name * varBuff = (struct name *) __active_buffer;                                          \
              varBuff = varBuff->next;                                                                          \
              while (varBuff->next != NULL) {                                                                   \
                     __printedBufferLength += print("%", varBuff->value);                                       \
                     varBuff = varBuff->next;                                                                   \
                     __printedBufferLength += printf(btw);                                                      \
              }                                                                                                 \
              __printedBufferLength += print("%", varBuff->value);                                              \
       }

/* Variable Initialisation */
#define __push(value)                                                                                           \
              if (__active_buffer == 0) {}                                                                      \
              else __auto_push(Var, value)

#define __print(btw)                                                                                            \
              if (__active_buffer == 0) {}                                                                      \
              else __auto_print_var(Var, btw)

#define __free                                                                                                  \
              if (__active_buffer == 0) {}                                                                      \
              else __auto_free(Var)

/* Helping Utility (for tne buffer "Var") */
extern size_t __VarSetIndex;
extern var GetVar;

#define SetVar(i)                                                                                               \
       {                                                                                                        \
              struct Var * varBuff = (struct Var *) __active_buffer;                                            \
              varBuff = varBuff->next;                                                                          \
              for (__VarSetIndex = 0; (varBuff->next != NULL) && (__VarSetIndex < i); __VarSetIndex++) {        \
                     varBuff = varBuff->next;                                                                   \
              }                                                                                                 \
              GetVar = varBuff->value;                                                                          \
       }

/* Function that returns the var storing the string of the simple buffer */
var __var_of_raw(void);

/* Macro that returns the var storing the string of the simple buffer */
#define varRaw __var_of_raw()

#endif