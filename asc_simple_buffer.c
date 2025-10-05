#include "asc_simple_buffer.h"

struct _simple_buffer_link_ * __temp_raw_link = NULL;

struct _simple_buffer_head_ raw = {0, NULL, NULL};

void __free_simple_buffer_links(struct _simple_buffer_link_ * _del) {
    if (_del->next != NULL) __free_simple_buffer_links(_del->next);
    free(_del);
}

void PushRaw(char _to_push) {
    pushRaw _to_push;
}

void PrintRaw(void) {
    printRaw;
}

char * __string_of_raw(void) {
    char * ret = (char *)malloc(1 + sizeof(char) * raw.length);
    if (!raw.first) return 0;
    struct _simple_buffer_link_ * varRaw = raw.first;
    for (int i = 0; i < raw.length; i++) {
        ret[i] = varRaw->value;
        varRaw = varRaw->next;
        if (varRaw == NULL) break;
    }
    ret[raw.length] = 0;
    return ret;
}
