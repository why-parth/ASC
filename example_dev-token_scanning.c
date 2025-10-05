#include "reader.h"
#include "buffer.h"

/* May not work properly. */

void iteration(void) {
    static var toStore = {4, 0, NULL};

    // For Strings
    if (halt == 2) halt = 3;
    else if (halt == 3) halt = 0, printf("\033[0;0m");
    
    if (CharClassIsChanged && PreviousCharClass && (!halt || halt == -1)) {

        // For Strings
        if (halt == -1) halt = 1;

        if (!(PreviousCharClass & SPACE)) {
            toStore.value.Int = raw.length;
            toStore.next = (var *)__string_of_raw(); 
            PushVar(toStore);
        }
        
        freeRaw;
    }
    
    if (CurrentCharClass) PushRaw(c);
    putchar(c);
}   
#define iter iteration

void Start(void) { printf("\t\tSTART\n"); printf("\033[0;33mCode:\n\033[;0m"); }
#define sof Start

void End(void) { printf("\033[0;33m\nTokens:\n\033[;0m"); PrintVar("\n"); printf("\n\t\t END"); }
#define eof End

// For Strings
void * toggleString (void) {
    if (halt) halt = 2;
    else halt = -1, printf("\033[0;32m");;
}

void * togglePreprocessing (void) {
    if (modeOf('<')) modeOf('<') = 0, modeOf('>') = 0;
    else modeOf('<') = 1, modeOf('>') = 1;
}

development {
    
    // For Strings
    pushMode(toggleString); // 1
    modeOf('"') = 1;

    // For Preprocessing
    pushMode(togglePreprocessing); // 2
    modeOf('#') = 2;

}