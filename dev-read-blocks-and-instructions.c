#include "reader.h"
/* This dev file reads blocks and instruction in c code. Change the include in reader.c to see it in action. */

/* Logic */
function(blockStarts) {
    if DEBUG ("-block starts-");

    nestExpecter(';');
}

function(blockEnds) {
    if DEBUG printf("-block ends-");

    freeRecentExpecter();
}

function(instruction) {
    char BlockEnded = 0;
    pollExpecterAs(a){
        if (c == '}' && a == '{') BlockEnded = 1;
        a = pollExpecter();
    }

    freeRecentExpecter();

    if (BlockEnded) blockEnds();
    else if DEBUG printf("-instruction-");
}

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

///////////////////////// Comment this on to see the char class seperated with '|' 
// /* iter definition */
// void toBeCalledPerIteration(void) {
//     if (CharClassIsChanged) printf("|%c", c);
//     else printf("%c", c);
// }
// #define iter toBeCalledPerIteration

/* Development */
development {

    pushMode(blockStarts); // 1

    modeOf('{') = 1;

    pushExpectation('{', '}', blockEnds);
    pushExpectation(';', ';', instruction);
    pushExpectation(';', '}', instruction);

}
