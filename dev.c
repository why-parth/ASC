#include "reader.h"

/* Logic */
function(blockStarts) {
    printf ( "block starts");

    nestExpecter(';');
}

function(blockEnds) {
    printf("-block ends-");

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
    else printf("-instruction-");
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

/* Development */
development {

    pushMode(blockStarts); // 1

    modeOf('{') = 1;

    pushExpectation('{', '}', blockEnds);
    pushExpectation(';', ';', instruction);
    pushExpectation(';', '}', instruction);

}