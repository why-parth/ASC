#include "asc_apc.h"

int CharClassIsChanged = 0;
int PreviousCharClass = 0;
int CurrentCharClass = 0;

unsigned int getCharClass(char c) {
    if          (c == 32)                                   return SPACE;
    else if     (47 < c && c < 58)                          return NUMBER;
    else if     ((64 < c && c < 91) || (96 < c && c < 123)) return ALPHABET;
    else if     (c > 31) switch (c)
    {
        case 40:    return OPEN + PARA; // ( 
        case 41:    return CLOSE + PARA; // ) 
        case 91:    return OPEN + BOX; // [ 
        case 93:    return CLOSE + BOX; // ] 
        case 123:   return OPEN + CURL; // { 
        case 125:   return CLOSE + CURL; // } 
        case 92:    return NULLIFY; // \ 
        case 59:    return TERMINATE; // ;
        default:    return SYMBOL;
    }
    return 0;
}

/*
same ALPHABETS 65-90 97-122
same NUMBER 48-57

diff NULL 92
diff END 59

diff BRACKETS (40 41) [91 93] {123 125} 

diff OPERATORS 42-43 45-47 94

diff LOGIC 38 41 46 58 60-63 124

else same SYMBOLS
*/


