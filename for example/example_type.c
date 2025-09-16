#include "asc_type.h" // compiled with asc_type.c

/* Implementation */
int main(int argc, char ** argv) {

    // declaring a variable
    var a;
        /* var is the datatype that stores ALL your data in this interface. */

    // defining a variable
    a = Int(45);
        /* var is the datatype that stores ALL your data in this interface.
        and whenever you store data, you must specify the datatype as Datatype(data). */
    
    // declaring and defining in the same line
    var b = Char('c');

    // printing
    print("The value of a is %.", a);
        /* The print function is exactly like the printf function,
        but, you do not have to specify the type. */

    // Conditionals
    if (a.type == Int Type) print("\nThe type of a is Int.");
        /* a.type return the type of a,
        and, Int Type returns the type if Int. */

    /* There are 3 primary datatypes in this interface (Int, Char, Float),
    but we also have a non-primary inbuilt datatype, Str (string). */
    var c = Str("hello world");
    
    /* Strings are dynamically allocated and (pointers) are stored in the 'next' of a 'var'.
    and 'value' of the string stores the length of the string. */
    printf("\n\nthe lenght of the string is %d\n", c.value);
    print("the string:\n\t%", c);
    
    /* Since these strings are dynamically allocated, we have to free them as well. */
    freestr(c);

    // (!) Be exreamly carefull with how you use Str, memory leaks can be fatal. (!)
    
    return 0;
}

/* Output */
//The value of a is 45.
//The type of a is Int.

//the lenght of the string is 11
//the string:
//        hello world