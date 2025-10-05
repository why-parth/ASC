#ifndef __ASC_APC_H__
#define __ASC_APC_H__
#include <stdio.h>
#include <stdlib.h>

/* This header is stable, and complete, this is how you use it:
 * For better understanding of how this file is written, refer to the official documents of FACE.
 *
 * function(n) {
       / * code * /
   } // declares a function named n and of the type that is of the 'buffer function'
        / * Buffer Functions
            They return (void *) and take (void), if you wish to give them parameters then you must use
            expectations to store data in buffers and then grab the buffers using the buffer pointers.
            -- more on buffers in the header asc_buffer.h --
            -- more on buffer functions in the header asc_buffer.h --
        * /
 * 
 * pushExpectation(a, e, f); // attatches an expectation e to the char a and the function f will be called when that expectation e is met
        / * All ascii characters store a linked list of all of its expectations via the array expect,
        the function pushExpectation pushes a new expectation on that linked list
        i.e. appends the end of the linked list. * /
 *
 * pushMode(f); // pushed a function to the mode list
        / * Mode refers to the functions that are linked via the linked list modeList.
        to call a mode function use a function called getMode(int m) that takes the index m,
        the modeList is iterated m times and then the function (of the index is m) is returned. * /
 * 
 * modeOf(a) = i; // assigns a mode of index i to the char a
        / * Modes are stored in a linked list and can be grabbed only and only by iterating that linked list.
        Assigning an index other than 0 to triggers the Mode Handler to call the corresponding mode. * /
 * 
 */

/* 0 for no debugging, 1 for debugging. */
#define DEBUG (0)
#define debug if DEBUG

/* For Development */
#define            development          void __reader_development__ (void)
#define               function(n)       void * n (void)
extern char * _filename;

#define              enterMain          initExpectations(); initExpecter(); initModeList(); FILE * _file = fopen(_filename, "r")
#define               exitMain          (modeList); free(expecter); fclose(_file)

#define                 modeOf(a)       expect[a].mode
#define       startReadingFile(c)       while (c != EOF)
#define           readFromFile(c)       c = fgetc(_file)
#define         pollExpecterAs(c)       char c = pollExpecter(); if (c != 0) while (c != 0)

#define   updateCharClassFlags(c)       PreviousCharClass = CurrentCharClass;                                       \
                                        CurrentCharClass = getCharClass(c);                                         \
                                        if (PreviousCharClass != CurrentCharClass) CharClassIsChanged = 1;          \
                                        else CharClassIsChanged = 0

#define                  SPACE          0x01
#define                 NUMBER          0x02
#define               ALPHABET          0x04   
#define                 SYMBOL          0x08
#define                   OPEN          0x10
#define                  CLOSE          0x20
#define                   PARA          0x02 // BRACKET must be checked first
#define                   CURL          0x04 // BRACKET must be checked first
#define                    BOX          0x08 // BRACKET must be checked first
#define                NULLIFY          0x40
#define              TERMINATE          0x80
  
/* APC Variables (char(s)) */
extern char c;

/* Datatype that stores the buffer functions. */
typedef void * (* buffer_function)(void);

/* Datatype that stores the list of expectations along with various parameters. */
struct expectations {
       int mode;
       struct expected_call * list;
       struct expected_call * last;
};

/* Datatype that stores an expectation and it's associated function. */
struct expected_call {
    char init;
	buffer_function call;
	struct expected_call * next;
};

/* Linked List stores the modes.
Function initModeList must be called at the beginiing of the main function.
Freeing of modeList mustn't be ignored. */
struct mode {
    buffer_function func;
    struct mode * next;
};
extern struct mode * modeList; 

void initModeList(void);

extern int __pushedModeIndex;
struct mode * pushMode(buffer_function f); // Pushes a mode into the modeList
struct mode * getMode(int m); // Returns the mode of index index

/* Array stores all the expectations for all the characters.
Function initExpectation must be called at the beginiing of the main function.*/
extern struct expectations expect[128];

void initExpectations(void);

/* Datatype nest allows the nesting of expectation.
Function initExpectater must be called at the beginiing of the main function.
Freeing of expector mustn't be ignored. */
struct nest{
    char val;
    struct nest * prev;
};
extern struct nest * expecter;

void initExpecter(void);

struct nest * nestExpecter(char a); // Nests (pushes) a char onto the queue (list) of existing expecters (chars)
struct nest * freeRecentExpecter(void); // Frees the recent most expecter
struct nest * getRecentExpecter(void); // Returns the recent most expecter
char pollExpecter(void); // Returns the next expecter on every next call and rounds back to start when none to return
extern unsigned long int __polledExpecterIndex; // pollExpecter returns the expecter char but its index is stored in this variable
unsigned long int printExpecters(const char * s); // prints all the expecters (places the string s bewteen consecutive expecters)
unsigned long int nestLen(void); // Returns the number of expecters

/* Temporary function for de-bugging purposes. */
void * tempFunc(void);

extern int halt;

/* This function prints all the expectaions for a char a and prints the string s in between two consecutive chars. */
int printExpectations(char a, const char * s);

/* Pushes the expectation e on the char a and attatches the function f to e. */
struct expected_call * pushExpectation(char a, char e, buffer_function f);


/* Character Class Flags */
extern int CharClassIsChanged;
extern int PreviousCharClass;
extern int CurrentCharClass;

unsigned int getCharClass(char c);

#endif