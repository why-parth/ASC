#include <stdio.h>
#include <stdlib.h>

// [header]-{link}-{link}-{link}-{link}-{link}-{link}-{link} ...
//     \__ length, list, last link, (functions) ...      |
// header is stored in the stack                         | 
// links are stored in the heap                          |
//       ______________________________________________ /
//     /
// value, next, prev

unsigned int __autoMakeFlag = 0;
size_t __autoMakePointer = 0;
size_t __autoMakeFunction();

struct _linkOfLinkedList_ {
    int value;
    struct _linkOfLinkedList_ * prev;
    struct _linkOfLinkedList_ * next;
};

typedef struct linkOfLinkedList * (* ptr_linkOfLinkedList_int)(int i);

// let __autoMakeFlag be 1
struct _headOfLinkedList_ {
    unsigned int length;
    struct linkOfLinkedList * first;
    struct linkOfLinkedList * last;
    ptr_linkOfLinkedList_int get;
};

#define list __autoMakeFlag = 1; struct _headOfLinkedList_



size_t __autoMakeFunction() {
    size_t ret = 0;
    switch (__autoMakeFlag) {
    case 1:
        __autoMakePointer = malloc(sizeof(struct _headOfLinkedList_));
        ((struct _headOfLinkedList_ *) __autoMakePointer)->first = NULL;
        ((struct _headOfLinkedList_ *) __autoMakePointer)->last = NULL;
        ((struct _headOfLinkedList_ *) __autoMakePointer)->get = NULL;
        ((struct _headOfLinkedList_ *) __autoMakePointer)->length = 0;
        break;
    return ret;
    }
}


int main(int argc, char ** argv) {



    return 0;
}