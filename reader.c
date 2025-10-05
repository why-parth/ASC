/* Source file that completely determines the behaviour of the reader. */
#define src "dev.c" // name of the source file, a file of this name must be present in the scope of this .c file.
/*
 * There is a specefic way of writting the source file,
 * the functions defined in the headers asc_expect.h and asc_buffer.h are used
 * in a well defined manner to come up with a successful source file.
 * 
 * Read the official documents of FACE to understand the way of development of such source files.
 * 
 * The document "APC Mechanism" of the "FACE Standard Documents" features:
        - pushing modes
        - setting modes
        - pushing expectations
        - polling expectations ----------------------------------------------------------------- (not yet added)
        - pushing expccters -------------------------------------------------------------------- (not yet added)
        - polling expecters
        - halting 
        - dynamic nest control (DNC) --- working of the reader
        - declaring classes
        - nesting of classes (sub-classes) ----------------------------------------------------- (not yet added)
        - interperating class configuration changes (Keyword Logic) --- working of the reader -- (not yet added)
        - defining sof and eof
        - defining iter
 * 
 */

#include "reader.h"

char * _filename;

#include src

int main(int argc, char ** argv){
    if (argc == 1) { printf("no file provided to the reader"); return 0; }
    else {
        _filename = argv[1];
    }
    enterMain;
    #ifdef sof
    sof();
    #endif

    // char c = 0; // variable input char
    struct expected_call * varExpect = NULL; // variable expected call
    struct mode * varMode = NULL; // variable expected call

    /* Development Space */ //----\------------/-------------------\--------------------------/---------------
    // If you wish to manually develop this file, this area is safe for any definition                                           
                                                                                                                                 
    __reader_development__();                                                                                                    
                                                                                                                                 
    //-----------\---------------------------/---------------------------\---------------------------\--------

    // opening the read loop
    startReadingFile(c) {
        readFromFile(c); // updating the variable char
        // if (halt > 0) halt--; // do this in the iteration function

        /* Char Class Flag Handler */

        updateCharClassFlags(c);  

        /* DEBUG */ 
        if DEBUG putchar(c);

        /* Expectation Handler */ //-----\----------/-----------------\-----------/-----------------\---------
        if (getRecentExpecter()->val != 0 && !halt) {
            varExpect = expect[getRecentExpecter()->val].list;
            while (varExpect->next != NULL) {
                if (varExpect->init == c) break;
                varExpect = varExpect->next;
            }
            if (varExpect->init == c) {

                /* DEBUG */
                if DEBUG printf("\033[0;92m<\033[0;93m%d\033[0;92m ", nestLen()), rawChar(getRecentExpecter()->val), printf(">\033[0m");

                if DEBUG printf("\033[0;91m<");
                varExpect->call();
                if DEBUG printf(">\033[0m");
            }
        }
        
        if (expect[c].list != NULL && !halt) {

            nestExpecter(c); // setting the expector equal to variable char if the variable char expects something

        }

        /* Mode Handler */ //-----\--------------/---------------------------\--------------------/-----------
        varMode = getMode(expect[c].mode);
        if (varMode != NULL) {

            /* DEBUG */
            if DEBUG printf("\033[0;91m<");
            varMode->func();
            if DEBUG printf("\033[0;91m>\033[0m");
        }
        
        /* Iteration Function */
        #ifdef iter
        iter();
        #endif

    }

    /* Development Space */ //----\------------/-------------------\--------------------------/---------------
    // If you wish to manually develop this file, this area is safe for any definition

    //-----------\---------------------------/---------------------------\---------------------------\--------

    #ifdef eof
    eof();
    #endif
    exitMain;
    return 0;
}