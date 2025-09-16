#include "asc_complex_buffer.h"

/* Declaring the Buffer "buff" */
__declare_buffer(buff, char) __auto_define_buffer(buff)

/* Constant Initialisation */
unsigned int __number_of_buffers = 0;
size_t __active_buffer = 0;
unsigned long long __printedBufferLength = 0;

/* Variable Initialisation */
#define __push(value)                                                                   \
              if (__active_buffer == 0) {}                                              \
              else __auto_push(buff, value)

#define __print(btw)                                                                    \
              if (__active_buffer == 0) {}                                              \
              else __auto_print_char(buff, btw)

#define __free                                                                          \
              if (__active_buffer == 0) {}                                              \
              else __auto_free(buff)

/* Implementation */
int main () {

        char string[] = "hello world";

        int _strlen = 0;
        while (string[_strlen]) { buff Push(string[_strlen++]) }

        printf("the length of the string is %d\nthe string:\n\t", _strlen);

        buff Print("");

        buff Free;

        return 0;
}

/* Output */
//the length of the string is 5
//the string:
//        hello