#ifndef __ASC_TYPE_H__
#define __ASC_TYPE_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/// // / Errors are not handled, but are reduced to a great extent. Follow the proper grammer to prevent any error. / // ///

/* --------------------------------------| Standard Declaratons |-------------------------------------- */

/* These two macros are used in type related logic,
 *
 * for example, 
        var a = Int(45)
        
        if (a.type == Int Type) {
            print("The value of the integer a is %.", a);
        } 
 * 
 * When a variable is declared, { var a; }, it's type is undefined.
                undefined type is NOT as same as NONE
 * 
 * This is beacuse var (struct _var_) is defined as {
                                                    unsigned int type;
                                                    ...
                                                    },
 * and when var a is declared { var a; }, var a is given a garbage value.
 * 
 * So, it is safe for us to declare var(s) as:
        var a = NoValue;
 *
 * And this notation allows us to even do logic:
        var a = NoValue;

        if (a.type == None) {
            print("The type of a is None");
        }
 *
 */
#define None 0
#define Type (0).type

/* ... */
#define typeofInt long int
#define typeofFloat double
#define typeofChar char

/* To store Integers, Floating Points and Characters all using only datatype (union). */
union _val_ {
    typeofInt Int;
    typeofChar Char;
    typeofFloat Float;
};

/* To store all the information of a variable, that are:
    - type (unsigned int)
    - value (union _val_)
    - next (struct _var_ *)
 *
 * The pointer-to struct _var_ exists to serve these purposes:
    - Just in case is there is ever a need to make a linked list, that pointer can be used.
    - Although that pointer is a pointer-to struct _var_, you can store pointers-any type.
        But you will have to type cast next to pointer-to (whatever type you want to store).
        You can assign pointer-to various types and structures to attatch information to the var(s).
 * 
 */

typedef struct _var_ {
    unsigned int type;
    union _val_  value;
    struct _var_ * next;
} var;

/* --------------------------------------| Standard Datatypes |--------------------------------------
 * 
 * These Datatypes are extremely simple and have inbuilt support of DOSs (Datatype Operation Set).
 * 
 * There are Standard Datatypes:
        - Int (Integer)
        - Char (Character)
        - Float (Floating Points)
 * 
 * Declarion and Definition:
        var $name = $datatype($value);
 * 
 * for example,
        var a = Int(45);
        / * This declares a var a that stores the Int 45 inside it. * /
        
        a = Char('c);
        / * This re-defines the var a to store the Char 'c' * /
        
        var b;
        / * A declaration without a definition can also be made. * /
 *
 */

/* Datatype : Int (Integer) */
struct _var_ Int(long int _int);

/* Datatype : Char (Character) */
struct _var_ Char(char _char);

/* Datatype : Float (Floating Points) */
struct _var_ Float(double _float);

/* --------------------------------------| Included Datatypes |--------------------------------------
 * 
 * These Datatypes are little complex and can have varying syntax.
 * These have inbuilt support of DOSs (Datatype Operation Set).
 *
 */

/* Dayatype : Str (String) (Dynamically Allocated)
 *
 * Declarion and Definition:
        var $name = $Str($value);
        / * The $value must be in enclosed between " and ". * /
 * 
 * for example,
        var a = Str("Hey");
        / * This declares a variable a that stores the string "Hey" inside it. * /

        a = Char('c);
        / * This re-defines the variable a to store the character 'c',
            but the initial string that we initialsed was dynamically allocated,
            so its "our responsibility" to free the string stored in a before we do anything.

            ONCE YOU CHANGE FROM A STRING, YOU LOSE IT COMPLETELY AND IT STAYS IN THE HEAP (NO RECOVERY)!
        * / 
        free String(a);
        / * This is how you free a string. * /
        freestr(a)
        / * This is another way of freeing a string. * /
 * 
 * Also, 
        You can not copy a Str into another varible like this,
            var a = Str("Hey");
            var b = a;
  
        No, becuase,
            variable a holds the value of the pointer-to char (char array) that is dynamically allocated.
            Copying variable a into variable b, thus,
            copies the pointer of the same dynamically allocated array to b that is stores in a.
        
        To solve this issue, Copy function ('cpy') is used (defined below). This is how it looks in action,
            var a = Str("Hey");
            var b = cpy(a);
 *
 */

/* Datatype : Str (String) (Dynamically Allocated) */
struct _var_ Str(char * _str);

/* Function : Prints all the var(s) that are linked (all var(s) that are next to the passed var). */
unsigned long int __printLinkedVars(struct _var_ * _linkedVar);

/* Function for Datatype Str : Prints the string strored inside the passed var. */
unsigned long int __printStr(struct _var_ _str);

/* Macros for handling the freeing of strings. */
#define getstr(a)           ((char *)a.next)
#define freestr(a)          free(a.next); a.type = None; a.value.Int = None; a.next = NULL
extern struct _var_ * __handleStr;
#define clear               free(
#define string              .next)
#define clearstr            ; free(__handleStr->next); __handleStr->next = NULL

/* -----------------| Standard Functions and DOS(s) for Above Defeined Datatypes |-----------------
 *
 * These are the DOS(s) (Data Operation Sets) that allow you to change the value for the datas
        - str to int/float (toRat)
        - int/float to str (toStr)
        - 
 * 
 * These are the Standard Functions that allow you to:
        - input
        - output
        - scan (is 'input' function does not work)
        -
 *
 */

/* Function for Datatype Str : Converts a Str into an Int
 *
 * Parameter:
    var _str (Str) -> A string that is numeric (0-9, -)
 * 
 * Returns: The integer that the string stores.
 * 
 */
#define toInt(_str) __toInt(&_str)
struct _var_ __toInt(var * _str);

/* Function for Datatype Str : Converts a Str into a Float
 *
 * Parameter:
    var _str (Str) -> A string that is numeric (0-9, -, .)
 * 
 * Returns: The floating point number that the string stores.
 * 
 * NOTE:
    If the string stores an integer, it will return an Int.
    You will have to attatch '.' followed by zeroes to make this function return a Float.
 * 
 * For example,
        var a = Str("45");

        a = toFloat(a); // a stores an Int 45

        clean a string; // freeing the string that was dynamically allocated and was previously stored in var a
 * and,
        var a = Str("45.0");

        a = toFloat(a); // a stores a Float 45

        clean a string;
 *
 * Since Str is a dynamically allocated datatype, you have to be careful with conversions like these.
 * Explained in an official document of FACE called ASC.
 */
#define toFloat(_str) __toFloat(&_str) 
struct _var_ __toFloat(var * _str);

#define __printFormatSpecifier      '%'
/* Function : Prints the formatted string. 
 * 
 * Parameters:
    const char * _format -> This is the string that is printed.
    ... -> Any number of inputs can be passed (generally of var(s)).
 *
 * Returns: Length of the entire string that is printed (total number of characters that are printed.)
 * 
 * Where ever in the string _format, char '%' is present,
 * it will be replaced with the value (var(s) passed after _format.
 * respctively, all the char(s) '%' will be replaced.
 * 
 * If you wish to print char '%', type '%' twice.
 * 
 * For example,
        Printing a variable:
            var a = Int(45);

            print("The value of a is %.", a);

            >>> The value of a is 45.

        Printing the char '%':
            var a = Int(45);

            print("The value of a is %%.", a); // var a will be ignored as there will be no call for it

            >>> The value of a is %.
 * 
 */
unsigned long int print(const char * _format, ...);

/* Function */
unsigned long int scan(const char * _format, ...);

/* Function */
unsigned long int input(const char * _format, ...);

#endif
