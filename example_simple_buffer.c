#include "asc_simple_buffer.h" // compiled with asc_simple_buffer.c

/* Simple Buffer require no initialisation (just make sure that that the .c files are all compiled) */

/* Implementation */
int main(int argc, char ** argv) {

    char string[] = "hello world";

    int _strlen = 0;
    while (string[_strlen]) { pushRaw string[_strlen++]; }

    printf("the length of the string is %d\nthe string:\n\t", raw.length);

    printRaw;

    printf("\nWe can also convert our raw buffer into a string!\n\t(printed using the string conversion)\n\t");

    char * string_from_raw_buffer = strRaw;

    freeRaw;

    printf(string_from_raw_buffer);

    return 0;
}

/* Output */
//the length of the string is 11
//the string:
//        hello world
//We can also convert our raw buffer into a string!
//        (printed using the string conversion)
//        hello world