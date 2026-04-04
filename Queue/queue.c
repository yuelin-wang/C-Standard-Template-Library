/*
Hello, thanks for using this! I can't believe that you are using this file, thank you so much :) !

There are 1 required macro and 1 optional macro
    QUEUE_TYPE_INPUT (required): a character
        'i': int
        'c': character
        's': string
        'b': bool
    QUEUE_DEFAULT: if this macro is defined, then the queue name and function doesn't contain type name

Structure and function name
    Structure:
        If not default: <type>Queue
        Default: queue
    Add:
        If not default: <type>QueueAdd
        Default: add
    Pop:
        If not default: <type>QueuePop
        Default: pop
    Element:
        If not default: <type>QueueElement
        Default: element
    Front:
        If not default: <type>QueueFront
        Default: front
    Print:
        If not default: print<type with the first letter capitalized>Queue
        Default: printQueue
    Free:
        If not default: free<type with the first letter capitalized>Q
        Default: freeQ
    Initialize:
        If not default: initialize<type with the first letter capitalized>Queue
        Default: initializeQueue

Usage
    Initialize: initializeQueue(queue * input queue, int element)
    Add: add(queue * input queue, int value)
    Pop: pop(queue * input queue)
    Element: element(queue input queue)
    Front: front(queue input queue)
    Print: printQueue(queue input queue)
    Free: freeQ(queue * input queue)
    Indexing: queue.array[i]
*/

// these are code to be included once
#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#define QUEUE_ADD_OK1(word)     ADD_OK2(QUEUE_TYPE_NAME, word)
#define QUEUE_ADD_OK2(word)     ADD_OK2(QUEUE_NAME, word)

#include <stdlib.h> // memory allocation, NULL
#include <stdio.h> // printf

#endif // end include once code


// C STL macro function include once
#ifndef C_STL_MACRO_HEADER
#define C_STL_MACRO_HEADER

#define ADD_OK1(pre, word)   pre##word
#define ADD_OK2(pre, word)   ADD_OK1(pre, word)
#define ADD_OK3(word1ok, word2ok, word3ok)   word1ok##word2ok##word3ok
#define ADD_OK4(word1ok, word2ok, word3ok)   ADD_OK3(word1ok, word2ok, word3ok) 
#define STRING1(word) #word
#define STRING2(word) STRING1(word)
#define ADD_BOOL_OK1(word)   bool##word
#define ADD_BOOL_OK2(word)   ADD_BOOL_OK1(word)

#endif // end C STL macro function include once


// type
#if QUEUE_TYPE_INPUT == 'i'
#define QUEUE_TYPE  int
#define QUEUE_TYPE_NAME int
#define QUEUE_CAPITAL_TYPE Int
#define FORMAT_STRING "%d"
#ifndef QUEUE_INT_HEADER
#define QUEUE_INT_HEADER
#else
#define QUEUE_REPETE
#endif

#elif QUEUE_TYPE_INPUT == 's'
#define QUEUE_TYPE char *
#define QUEUE_TYPE_NAME string
#define QUEUE_CAPITAL_TYPE String
#define FORMAT_STRING "%s"
#include <string.h> // strcpy
#ifndef QUEUE_STRING_HEADER
#define QUEUE_STRING_HEADER
#else
#define QUEUE_REPETE
#endif

#elif QUEUE_TYPE_INPUT =='c'
#define QUEUE_TYPE char
#define QUEUE_TYPE_NAME char
#define QUEUE_CAPITAL_TYPE Char
#define FORMAT_STRING "%c"
#ifndef QUEUE_CHAR_HEADER
#define QUEUE_CHAR_HEADER
#else
#define QUEUE_REPETE
#endif

#elif QUEUE_TYPE_INPUT == 'b'
#define QUEUE_TYPE bool
#define QUEUE_TYPE_NAME boolean
#define QUEUE_CAPITAL_TYPE Bool
#define FORMAT_STRING "%d"
#if __STDC_VERSION__ < 202311L
#include <stdbool.h> // bool
#endif
#ifndef QUEUE_BOOL_HEADER
#define QUEUE_BOOL_HEADER
#else
#define QUEUE_REPETE
#endif

#endif


// function name
// not default
#ifndef QUEUE_DEFAULT

// queue name
#if QUEUE_TYPE_INPUT != 'b' || __STDC_VERSION__ >= 202311L
#define QUEUE_NAME      QUEUE_ADD_OK1(Queue)
#else
#define QUEUE_NAME      ADD_BOOL_OK2(Queue)
#endif

#define QUEUE_INITIALIZE    ADD_OK4(initialize, QUEUE_CAPITAL_TYPE, Queue)
#define QUEUE_ELEMENT   QUEUE_ADD_OK2(Element)
#define QUEUE_ADD       QUEUE_ADD_OK2(Add)
#define QUEUE_POP       QUEUE_ADD_OK2(Pop)
#define QUEUE_FRONT     QUEUE_ADD_OK2(Front)
#define QUEUE_PRINT     ADD_OK4(print, QUEUE_CAPITAL_TYPE, Queue)
#define QUEUE_FREE      ADD_OK4(free, QUEUE_CAPITAL_TYPE, Q)

// default
#else 
#define QUEUE_NAME      queue
#define QUEUE_INITIALIZE    initializeQueue
#define QUEUE_ELEMENT   element
#define QUEUE_ADD       add
#define QUEUE_POP       pop
#define QUEUE_FRONT     front
#define QUEUE_PRINT     printQueue
#define QUEUE_FREE      freeQ
#endif


// same queue type include once
#ifndef QUEUE_REPETE

typedef struct QUEUE_NAME {
    QUEUE_TYPE * array;
    QUEUE_TYPE * front;
    QUEUE_TYPE * back;
    int memoryAmount;
} QUEUE_NAME;

void QUEUE_INITIALIZE(QUEUE_NAME * queue, int element) {
    int memory = element * sizeof(QUEUE_TYPE);

    queue -> array = malloc(memory);
    queue -> memoryAmount = memory;

    queue -> front = queue -> array;
    queue -> back = queue -> array;
}

int QUEUE_ELEMENT(QUEUE_NAME queue) {
    if (queue.back >= queue.front) {
        return queue.back - queue.front;
    } else {
        return queue.memoryAmount / sizeof(QUEUE_TYPE) - (queue.front - queue.back);
    }
}

void QUEUE_ADD(QUEUE_NAME * queue, QUEUE_TYPE value) {
    #if QUEUE_TYPE_INPUT != 's'
    * queue -> back = value;
    #else
    * queue -> back = malloc(strlen(value) + 1);
    strcpy(* queue -> back, value);
    #endif

    if ( queue -> back - queue -> array + 1 == queue -> memoryAmount / sizeof(QUEUE_TYPE)) {
        // back pointer is at the last element, wrap to the first element
        queue -> back = queue -> array;
    } else {
        queue -> back ++;
    }

    if (queue -> back == queue -> front) {
        QUEUE_TYPE * ok = malloc(queue -> memoryAmount * 2);

        QUEUE_TYPE * ok2 = queue -> front;
        for (int i = 0; i < queue -> memoryAmount / sizeof(QUEUE_TYPE); i++) {
            #if QUEUE_TYPE_INPUT != 's'
            ok[i] = *ok2;
            #else
            ok[i] = malloc(strlen(*ok2) + 1); 
            strcpy(ok[i], *ok2);
            free(*ok2);
            #endif

            ok2 ++;
            if (ok2 == queue -> array + queue -> memoryAmount / sizeof(QUEUE_TYPE) ) {
                ok2 = queue -> array;
            }
        }

        queue -> front = ok;
        queue -> back = ok + queue -> memoryAmount / sizeof(QUEUE_TYPE);

        free(queue -> array);
        queue -> array = ok;
        
        queue -> memoryAmount *= 2;
    }
}

void QUEUE_POP(QUEUE_NAME * queue) {
    #if QUEUE_TYPE_INPUT == 's'
    free(* queue -> front);
    #endif
    queue -> front ++;
    if (queue -> front >= queue -> array + queue -> memoryAmount / sizeof(QUEUE_TYPE)) {
        queue -> front = queue -> array;
    }
}

QUEUE_TYPE QUEUE_FRONT(QUEUE_NAME queue) {
    return * queue.front;
}

void QUEUE_PRINT(QUEUE_NAME queue) {
    printf("[");
    for (QUEUE_TYPE * i = queue.front; i != queue.back; i++) {
        printf(FORMAT_STRING, *i);

        if (i >= queue.array + queue.memoryAmount / sizeof(QUEUE_TYPE) - 1) {
            i = queue.array - 1;
        }
        if (i != queue.back - 1) {
            printf(", ");
        }
    }
    printf("], %s queue, ", STRING2(QUEUE_TYPE_NAME));
    printf("front pointer position: %ld, back pointer position: %ld, current element: %d, memory amount: %d\n", 
    queue.front - queue.array, queue.back - queue.array, QUEUE_ELEMENT(queue), queue.memoryAmount);
}

void QUEUE_FREE(QUEUE_NAME * queue) {
    #if QUEUE_TYPE_INPUT == 's'
    for (QUEUE_TYPE * i = queue -> front; i != queue -> back; i++) {
        free(*i);

        if (i >= queue -> array + queue -> memoryAmount / sizeof(QUEUE_TYPE) - 1) {
            i = queue -> array - 1;
        }
    }
    #endif

    queue -> front = NULL;
    queue -> back = NULL;
    
    free(queue -> array);
}

#endif // end same queue type include once

#undef QUEUE_REPETE
#undef QUEUE_TYPE_INPUT
#undef QUEUE_TYPE
#undef QUEUE_TYPE_NAME
#undef QUEUE_CAPITAL_TYPE
#undef FORMAT_STRING
#undef QUEUE_DEFAULT
#undef QUEUE_NAME
#undef QUEUE_INITIALIZE
#undef QUEUE_ADD
#undef QUEUE_POP
#undef QUEUE_ELEMENT
#undef QUEUE_FRONT
#undef QUEUE_FREE
#undef QUEUE_PRINT
