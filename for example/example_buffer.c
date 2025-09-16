#include "buffer.h" // compiled with asc_simple_buffer.c , buffer.c and asc_type.c

int main () {

    char * text = "45.67";

    while (*text) { pushRaw *(text++); }

    var to_push = varRaw;

    to_push = toFloat(to_push) clearstr;

    Var Push(to_push);
    Var Push(Float(0.33));

    var to_print = NoValue;

    to_print.type = Float Type;
    to_print.next = NULL;

    SetVar(0);
    to_print.value.Float += GetVar.value.Float;

    SetVar(1);
    to_print.value.Float += GetVar.value.Float;

    if (to_print.type == Float Type) {
        to_print.value.Int = to_print.value.Float;
        to_print.type = Int Type;
    }

    print("<-%->", to_print);

    freeRaw;
    Var Free;

    return 0;
}