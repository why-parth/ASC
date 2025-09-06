#include "asc_apc.h"

char c = 0;

struct mode * modeList;

void initModeList(void){ modeList = (struct mode *)malloc(sizeof(struct mode)); modeList->func = NULL; modeList->next = NULL; }

struct expectations expect[128];

void initExpectations(void){ for (int i = 0; i < 128; i++) expect[i].mode = 0, expect[i].list = NULL, expect[i].last = NULL; }

struct nest * expecter;

void initExpecter(void){ expecter = (struct nest *)malloc(sizeof(struct nest)); expecter->val = 0; expecter->prev = NULL; }

void * tempFunc(void){
    printf("-tempFunc is called-");
    freeRecentExpecter();
}

int halt = 0;

int printExpectations(char a, const char * s) {
    struct expected_call * e = expect[a].list;
    if (e == NULL) return  0;
    int len = 0;
    while (e->next != NULL) {
        putchar(e->init); len++;
        printf("%s", s);
        e = e->next;
    }
    putchar(e->init); len++;
    return len;
}

struct expected_call * pushExpectation(char a, char e, buffer_function f) {
    struct expected_call * varExpect = expect[a].list;
    if (varExpect == NULL) {
        expect[a].list = (struct expected_call *)malloc(sizeof(struct expected_call));
        varExpect = expect[a].list;
    }
    else {
        while (varExpect->next != NULL) varExpect = varExpect->next;
            varExpect->next = (struct expected_call *)malloc(sizeof(struct expected_call));
            varExpect = varExpect->next;
    }
    varExpect->init = e;
    varExpect->call = f;
    varExpect->next = NULL;
    return varExpect;
}

struct nest * nestExpecter(char a) {
    struct nest * varNest = expecter;
    while (varNest->prev != NULL) varNest = varNest->prev;
    varNest->prev = (struct nest *)malloc(sizeof(struct nest));
    varNest = varNest->prev;
    varNest->val = a;
    varNest->prev = NULL;

    /* DEBUG */ 
    if DEBUG printf("\033[0;94m<\033[0;93m%d\033[0;94m ", nestLen(), getRecentExpecter()->val),
    printExpectations(getRecentExpecter()->val, " "),
    printf(">\033[0m");

    return varNest;
}
struct nest * freeRecentExpecter(void) {
    struct nest * varNest = expecter;
    struct nest * varPrev = expecter;
    while (varNest->prev != NULL) varPrev = varNest, varNest = varNest->prev;
    free(varNest);
    varPrev->prev = NULL;
    return varPrev;
}

struct nest * getRecentExpecter(void){
    struct nest * varNest = expecter;
    while (varNest->prev != NULL) varNest = varNest->prev;
    return varNest;
}

unsigned long int nestLen(void) {
    int len = 0;
    struct nest * varNest = expecter;
    while (varNest->prev != NULL) len++, varNest = varNest->prev;
    return len;
}

unsigned long int __polledExpecterIndex = 0;
char pollExpecter(void) {
    static struct nest * varNest = NULL; if (varNest == NULL) varNest = expecter;

    if (varNest->prev == NULL) varNest = expecter, __polledExpecterIndex = 0;
    else varNest = varNest->prev, __polledExpecterIndex++;

    return varNest->val;
}

unsigned long int printExpecters(const char * s) {
    unsigned long int ret = 0;
    char a = pollExpecter();
    if (a == 0) printf("%s", s);
    else while (1) {
        ret++, putchar(a);
        a = pollExpecter();
        if (a == 0) break;
        ret += printf("%s", s);
    }
    return ret;
} 

struct mode * pushMode(buffer_function f) {
    struct mode * varMode = modeList;
    while (varMode->next != NULL) varMode = varMode->next;
    varMode->next = (struct mode *)malloc(sizeof(struct mode));
    varMode = varMode->next;
    varMode->func = f;
    varMode->next = NULL; 
    return varMode;
}

struct mode * getMode(int m) {
    if (!m) return NULL;
    struct mode * varMode = modeList;
    for (; m > 0; m--) {
        if (varMode->next != NULL) varMode = varMode->next;
        else break;
    }
    if (m && varMode->next == NULL) return NULL;
    return varMode;
}