#ifndef __ASC_COMPLEX_BUFFER_H__
#define __ASC_COMPLEX_BUFFER_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* This is a standalone header (it doesn't have a .c file that contain its logic).
 * This header allows you to declare, define, push, print and free "Complex Buffers".
       You have to initialise these commands, you can proceed to add you own commands.
 *
 * This is allows you to declare a complex buffer:
       __declare_buffer(name, type) __auto_define_buffer(name)
 * 
 * Required initialization, this is how you do it:
       __initialiseComplexBuffers
 *
 * "buffer.h" and "buffer.c" is the full implementation of all the buffer headers and their utilities.
 * 
 * DO NOT USE THIS HEADER CARELESSLY:
       This header does not have functions, all it has is macros and variables.
       If you use the macros in the main function, the final executable will be of a great size.
       Instead,
              make functions that use these macros and call those functions.
              Use a functional approach.
 */

#define __initialiseComplexBuffers unsigned int __number_of_buffers = 0; unsigned long long __printedBufferLength = 0; size_t __active_buffer = 0; int __buffer_exceeded = 0;


/* Stores the number of buffers that are declared. */
extern unsigned int __number_of_buffers;

/* Declares a buffer */
#define __declare_buffer(name, type)                                                                                   \
       struct name {                                                                                                   \
              type value;                                                                                              \
              struct name * next;                                                                                      \
       };                                                                                                              \
       size_t name(int p)

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

/* Automates your buffer definition process. */
#define __auto_define_buffer(name)                                                                                     \
       {                                                                                                               \
              __alloc_buffer_ptr(name);                                                                                \
              if (p) __active_buffer = ptr;                                                                            \
              return ptr;                                                                                              \
       }

/* Takes in a buffer and returns the dynamically allocated linked list that it corresponds to. */
#define getbuffer(name) ((struct name *)(name(0)))->next

/* Used for jumping forward in a linked list */
extern int __buffer_exceeded;
#define jumpbuffer(store) __buffer_exceeded = !store->next; store = store->next

/* Automates your pushing logic. */
#define __auto_push(name, val)                                                                                         \
       if (__active_buffer == name(0)) {                                                                               \
              struct name * varBuff = (struct name *) __active_buffer;                                                 \
              while (varBuff->next != NULL) varBuff = varBuff->next;                                                   \
              varBuff->next = malloc(sizeof(struct name));                                                             \
              varBuff->next->next = NULL;                                                                              \
              varBuff->next->value = val;                                                                              \
       }

/* To store the length of the printed buffer. */
extern unsigned long long __printedBufferLength;

/* Automates your printing logic (prints the integer equivalent). */
#define __auto_print_int(name, btw)                                                                                    \
       if (__active_buffer == name(0)) {                                                                               \
              struct name * varBuff = (struct name *) __active_buffer;                                                 \
              varBuff = varBuff->next;                                                                                 \
              if (varBuff == NULL) printf(btw);                                                                        \
              else {                                                                                                   \
                     while (varBuff->next != NULL) {                                                                   \
                            __printedBufferLength += printf("%d", varBuff->value);                                     \
                            varBuff = varBuff->next;                                                                   \
                            __printedBufferLength += printf(btw);                                                      \
                     }                                                                                                 \
                     __printedBufferLength += printf("%d", varBuff->value);                                            \
              }                                                                                                        \
       }

/* Automates your printing logic (prints the character equivalent). */
#define __auto_print_char(name, btw)                                                                                   \
       if (__active_buffer == name(0)) {                                                                               \
              struct name * varBuff = (struct name *) __active_buffer;                                                 \
              varBuff = varBuff->next;                                                                                 \
              if (varBuff == NULL) printf(btw);                                                                        \
              else {                                                                                                   \
                     while (varBuff->next != NULL) {                                                                   \
                            __printedBufferLength++; putchar(varBuff->value);                                          \
                            varBuff = varBuff->next;                                                                   \
                            __printedBufferLength += printf(btw);                                                      \
                     }                                                                                                 \
                     __printedBufferLength++; putchar(varBuff->value);                                                 \
              }                                                                                                        \
       }

/* Automates your printing logic (uses a custom instruction for printing). */
#define __auto_print_custom(name, btw, custom)                                                                         \
       if (__active_buffer == name(0)) {                                                                               \
              struct name * varBuff = (struct name *) __active_buffer;                                                 \
              varBuff = varBuff->next;                                                                                 \
              if (varBuff == NULL) printf(btw);                                                                        \
              else {                                                                                                   \
                     while (varBuff->next != NULL) {                                                                   \
                            custom;                                                                                    \
                            varBuff = varBuff->next;                                                                   \
                            __printedBufferLength += printf(btw);                                                      \
                     }                                                                                                 \
                     custom;                                                                                           \
              }                                                                                                        \
       }

/* Frees the first link of the buffer. */
#define freebuffer(name) free((void *)name(0))

/* Automates the freeing logic. */
#define __auto_free(name)                                                                                              \
       if (__active_buffer == name(0)) {                                                                               \
              struct name * prevBuff = NULL;                                                                           \
              struct name * currBuff = NULL;                                                                           \
              currBuff = (struct name *)__active_buffer;                                                               \
              currBuff = currBuff->next;                                                                               \
              while (currBuff != NULL) {                                                                               \
                     prevBuff = currBuff;                                                                              \
                     currBuff = currBuff->next;                                                                        \
                     free(prevBuff);                                                                                   \
              }                                                                                                        \
              free((void *)name(0));                                                                                   \
       }

/* For Custom Complex Buffer Commands */
#define forBuffer(name) if (__active_buffer == name(0))

/*
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