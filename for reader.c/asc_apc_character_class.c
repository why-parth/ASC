#include "asc_apc.h"

int CharClassIsChanged = 0;
int PreviousCharClass = 0;
int CurrentCharClass = 0;

unsigned int getCharClass(char c) {
    if (c == 32) return SPACE;
    else if (47 < c && c < 58) return NUMBER;
    else if ((64 < c && c < 91) || (96 < c && c < 123)) return ALPHABET;
    else return SYMBOL;
}

/*
diff NULL 92
diff END 59
diff BRACKETS (40 41) [91 93] {123 125} 
same NUMBER 48-57
same ALPHABETS 65-90 97-122
diff OPERATORS 42-43 45-47 94
diff LOGIC 38 41 46 58 60-63 124
else same SYMBOLS
*/