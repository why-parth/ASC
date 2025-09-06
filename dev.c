#include "reader.h"

/* sof and eof definition */
void enteringTheMainFunction(void) {
    printf("Your file \"%s\" is going to be read:\n", _filename);
}

void exitingTheMainFunction(void) {
    printf("\nYour file has been read!\n");
    printExpecters("~");
}

#define sof enteringTheMainFunction
#define eof exitingTheMainFunction

/* iter definition */
void iterationFunction(void) {
    putchar(c);
}

#define iter iterationFunction

development{

}