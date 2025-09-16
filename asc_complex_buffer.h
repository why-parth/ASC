#ifndef __ASC_COMPLEX_BUFFER_H__
#define __ASC_COMPLEX_BUFFER_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* This is a standalone header (it doesn't have a .c file that contain its logic).
 * This header allows you to declare, define, push, print and free "Complex Buffers".
 *
 * This is allows you to declare a complex buffer:
       __declare_buffer(name, type) __auto_define_buffer(name)
 * 
 * Use of this header requires you to define:
 * 
       ...
 *
 * "buffer.h" and "buffer.c" is the full implementation of all the buffer headers and their utilities.
 */

/* Stores the number of buffers that are declared. */
extern unsigned int __number_of_buffers;

/* Declares a buffer */
#define __declare_buffer(name, type)                                                                                   \
       struct name {                                                                                                   \
              type value;                                                                                              \
              struct name * next;                                                                                      \
       };                                                                                                              \
       size_t name(void)

/* To be able to globally set an active buffer (buffer in use). */
extern size_t __active_buffer;

/* Used in declaring a buffer. */
#define __end_buffer_declaration return __number_of_buffers

/* Used in declaring a buffer. */
#define __alloc_buffer_ptr(name)                                                                                       \
       static size_t ptr = 0;                                                                                          \
       if (!ptr) {                                                                                                     \
              __number_of_buffers++;                                                                                   \
              ptr = (size_t)malloc(sizeof(struct name));                                                               \
              ((struct name *)ptr)->next = NULL;                                                                       \
       }

/* Automates your buffer declaration process. */
#define __auto_define_buffer(name)                                                                                     \
       {                                                                                                               \
              __alloc_buffer_ptr(name);                                                                                \
              __active_buffer = ptr;                                                                                   \
              return ptr;                                                                                              \
       }

/* Takes in a buffer and returns the dynamically allocated linked list that it corresponds to. */
#define getbuffer(name) ((struct name *)(name()))->next

/* Function that pushes onto the acitve buffer. */
// void __push(size_t value);

/* Macro that is used to form a complete independent instruction. */
#define Push(value) (); __push(value)

/* Automates your pushing logic. */
#define __auto_push(name, val)                                                                                         \
       if (__active_buffer == name()) {                                                                                \
              struct name * varBuff = (struct name *) __active_buffer;                                                 \
              while (varBuff->next != NULL) varBuff = varBuff->next;                                                   \
              varBuff->next = malloc(sizeof(struct name));                                                             \
              varBuff->next->next = NULL;                                                                              \
              varBuff->next->value = val;                                                                              \
       }

/* Function that prints the acitve buffer. */
// size_t __print(char * in_between);

/* To store the length of the printed buffer. */
extern unsigned long long __printedBufferLength;

/* Macro that is used to form a complete independent instruction. */
#define Print(btw) (); __print(btw)

/* Automates your printing logic (prints the integer equivalent). */
#define __auto_print_int(name, btw)                                                                                    \
       if (__active_buffer == name()) {                                                                                \
              struct name * varBuff = (struct name *) __active_buffer;                                                 \
              varBuff = varBuff->next;                                                                                 \
              while (varBuff->next != NULL) {                                                                          \
                     __printedBufferLength += printf("%d", varBuff->value);                                            \
                     varBuff = varBuff->next;                                                                          \
                     __printedBufferLength += printf(btw);                                                             \
              }                                                                                                        \
              __printedBufferLength += printf("%d", varBuff->value);                                                   \
       }

/* Automates your printing logic (prints the character equivalent). */
#define __auto_print_char(name, btw)                                                                                   \
       if (__active_buffer == name()) {                                                                                \
              struct name * varBuff = (struct name *) __active_buffer;                                                 \
              varBuff = varBuff->next;                                                                                 \
              while (varBuff->next != NULL) {                                                                          \
                     __printedBufferLength++; putchar(varBuff->value);                                                 \
                     varBuff = varBuff->next;                                                                          \
                     __printedBufferLength += printf(btw);                                                             \
              }                                                                                                        \
              __printedBufferLength++; putchar(varBuff->value);                                                        \
       }

/* Automates your printing logic (uses a custom instruction for printing). */
#define __auto_print_custom(name, btw, custom)                                                                         \
       if (__active_buffer == name()) {                                                                                \
              struct name * varBuff = (struct name *) __active_buffer;                                                 \
              varBuff = varBuff->next;                                                                                 \
              while (varBuff->next != NULL) {                                                                          \
                     custom;                                                                                           \
                     varBuff = varBuff->next;                                                                          \
                     __printedBufferLength += printf(btw);                                                             \
              }                                                                                                        \
              custom;                                                                                                  \
       }

/* Function that prints the acitve buffer. */
// void __free(void);

/* Macro that is used to form a complete independent instruction. */
#define Free (); __free

/* Frees the first link of the buffer. */
#define freebuffer(name) free((void *)name())

/* Automates the freeing logic. */
#define __auto_free(name)                                                                                                    \
       if ((__active_buffer == name())) {                                                                              \
              struct name * prevBuff = NULL;                                                                           \
              struct name * currBuff = NULL;                                                                           \
              currBuff = (struct name *)__active_buffer;                                                               \
              currBuff = currBuff->next;                                                                               \
              while (currBuff != NULL) {                                                                               \
                     prevBuff = currBuff;                                                                              \
                     currBuff = currBuff->next;                                                                        \
                     free(prevBuff);                                                                                   \
              }                                                                                                        \
              free((void *)name());                                                                                    \
       }


/* Theory
 * 
 * APC Mechanism allows you to keep track of the characters a, p and c.
 * Although this process is a little complicated, the idea is still the same.
 * 
 * As per the values of a, p and c, you tell the reader to call specific functions.
 * Those functions will a lot of times require parameters and for the major part,
 * you will want those parameters to be the text that you read from the file.
 * 
 * Buffer(s) is the way you store the text that you read.
 * Functions can grab the buffer data as per their needs and even change that data.
 * 
 * Buffers are of types:
        - raw (a Simple Buffer)
        - c buffer (linked list of char *) (a Complex Buffer)
        - f buffer (linked list of var) (a Complex Buffer)
 * 
 */

#endif