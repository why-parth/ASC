#ifndef __ASC_SIMPLE_BUFFER_H__
#define __ASC_SIMPLE_BUFFER_H__
#include <stdio.h>
#include <stdlib.h>

/* This header allows you to push, print and free a pre_initialised Simple Buffer. */

/* Link of the Simple Buffer */
struct _simple_buffer_link_ {
    char value;
    struct _simple_buffer_link_ * next;
};

/* Temporary Simple Buffer Link */
extern struct _simple_buffer_link_ * __temp_raw_link;

/* Head of the Simple Buffer */
struct _simple_buffer_head_ {
    size_t length;
    struct _simple_buffer_link_ * first;
    struct _simple_buffer_link_ * last;
};

/* Simple Buffer (Raw) */
extern struct _simple_buffer_head_ raw;

/* Macro that pushes onto Raw */
#define pushRaw                                                                                                         \
        raw.length++;                                                                                                   \
        if (raw.first == NULL) {                                                                                        \
            raw.first = (struct _simple_buffer_link_ *)malloc(sizeof(struct _simple_buffer_link_));                     \
            raw.last = raw.first; }                                                                                     \
        else {                                                                                                          \
            raw.last->next = (struct _simple_buffer_link_ *)malloc(sizeof(struct _simple_buffer_link_));                \
            raw.last = raw.last->next;                                                                                  \
        }                                                                                                               \
        raw.last->next = NULL;                                                                                          \
        raw.last->value = 

/* Function that pushes onto Raw */
void PushRaw(char _to_push);

/* Macro that prints Raw */
#define printRaw                                                                                                        \
        if (raw.first) {                                                                                                \
            __temp_raw_link = raw.first;                                                                                \
            while (__temp_raw_link != NULL) putchar(__temp_raw_link->value), __temp_raw_link = __temp_raw_link->next;   \
        }

/* Function that prints Raw */
void PrintRaw(void);

/* Function that frees Raw */
void __free_simple_buffer_links(struct _simple_buffer_link_ * _del);

/* Macro that free Raw */
#define freeRaw                                                                                                         \
        __free_simple_buffer_links(raw.first);                                                                          \
        raw.length = 0;                                                                                                 \
        raw.first = NULL;                                                                                               \
        raw.last = raw.first                                                                                            \

/* Function that returns the string of Raw */
char * __string_of_raw(void);

/* Macro that returns the string of Raw */
#define strRaw __string_of_raw()

#endif