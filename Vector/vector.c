/*
Hello, thanks for using this! I can't believe that you are using this file, thank you so much :) !

There are 1 required macro and 1 optional macro
    VECTOR_TYPE_INPUT (required): a character
        'i': int
        'c': character
        's': string
        'b': bool
    VECTOR_DEFAULT (optional): if this macro is defined, then the vector name and function doesn't contain type name

Structure and function name
    Structure: 
        If not default: <type>Vector
        Default: vector
    Add:
        If not default: <type>VectorAdd
        Default: add
    Pop:
        If not default: <type>VectorPop
        Default: pop
    Print:
        If not default: print<type with the first letter capitalized>Vector
        Default: printVector
    Free:
        If not default: free<type with the first letter capitalized>V
        Default: freeV
    Initialize:
        If not default: initialize<type with the first letter capitalized>Vector
        Default: initializeVector

Usage
    Structure: if want to manually initialized, vector vector1 = {malloc(10), 10, 0, 0};
    Initialize: initializeVector(vector * input vector, int element amount)
    Add: add(vector * input vector, <type> value)
    Pop: pop(vector * input vector)
    Print: printVector(vector input vector)
    Free: freeV(vector input vector);
    Indexing: vector.array[i]
*/


// these are code to be included once
#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#define VECTOR_ADD_OK1(word)    ADD_OK2(VECTOR_TYPE_NAME, word)
#define VECTOR_ADD_OK2(word)    ADD_OK2(VECTOR_NAME, word)

#include <stdlib.h> // memory allocation
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
#if VECTOR_TYPE_INPUT == 'i'
#define VECTOR_TYPE     int
#define VECTOR_TYPE_NAME int
#define VECTOR_CAPITAL_TYPE Int
#define FORMAT_STRING   "%d"
#ifndef VECTOR_INT_HEADER
#define VECTOR_INT_HEADER
#else
#define VECTOR_REPETE
#endif

#elif VECTOR_TYPE_INPUT == 's'
#define VECTOR_TYPE     char *
#define VECTOR_TYPE_NAME string
#define VECTOR_CAPITAL_TYPE String
#define FORMAT_STRING   "%s"
#include <string.h> // strcpy
#ifndef VECTOR_STRING_HEADER
#define VECTOR_STRING_HEADER
#else
#define VECTOR_REPETE
#endif

#elif VECTOR_TYPE_INPUT == 'c'
#define VECTOR_TYPE     char
#define VECTOR_TYPE_NAME char
#define VECTOR_CAPITAL_TYPE Char
#define FORMAT_STRING   "%c"
#ifndef VECTOR_CHAR_HEADER
#define VECTOR_CHAR_HEADER
#else
#define VECTOR_REPETE
#endif

#elif VECTOR_TYPE_INPUT == 'b'
#define VECTOR_TYPE     bool
#define VECTOR_TYPE_NAME boolean
#define VECTOR_CAPITAL_TYPE Bool
#define FORMAT_STRING   "%d"
#if __STDC_VERSION__ < 202311L
#include <stdbool.h> // bool
#endif
#ifndef VECTOR_BOOL_HEADER
#define VECTOR_BOOL_HEADER
#else
#define VECTOR_REPETE
#endif

#endif


// vector function name
// not default
#ifndef VECTOR_DEFAULT

// vector name
#if VECTOR_TYPE_INPUT != 'b' || __STDC_VERSION__ >= 202311L
#define VECTOR_NAME     VECTOR_ADD_OK1(Vector)
#else // in case Boolean type and prior to C23
#define VECTOR_NAME     ADD_BOOL_OK2(Vector)
#endif

#define VECTOR_INITIALIZE   ADD_OK4(initialize, VECTOR_CAPITAL_TYPE, Vector)
#define VECTOR_ADD      VECTOR_ADD_OK2(Add)
#define VECTOR_POP      VECTOR_ADD_OK2(Pop)
#define VECTOR_PRINT    ADD_OK4(print, VECTOR_CAPITAL_TYPE, Vector)
#define VECTOR_FREE     ADD_OK4(free, VECTOR_CAPITAL_TYPE, V)
#define VECTOR_EXPAND   VECTOR_ADD_OK2(Expand)

// default
#else
#define VECTOR_NAME     vector
#define VECTOR_INITIALIZE   initializeVector
#define VECTOR_ADD      add
#define VECTOR_POP      pop
#define VECTOR_PRINT    printVector
#define VECTOR_FREE     freeV
#define VECTOR_EXPAND   expand
#endif

// same type of vector include once
#ifndef VECTOR_REPETE
typedef struct VECTOR_NAME {
    VECTOR_TYPE* array;
    int memoryAmount;
    int element;
} VECTOR_NAME;

void VECTOR_EXPAND(VECTOR_NAME * vector) {
    vector -> memoryAmount *= 2;
    VECTOR_TYPE * ok = malloc(vector -> memoryAmount);
    for (int i = 0; i < vector -> element; i ++) {
        #if VECTOR_TYPE_INPUT != 's'
        ok[i] = (vector -> array)[i];
        #else
        ok[i] = malloc(strlen(vector -> array[i]) + 1);
        strcpy(ok[i], vector -> array[i]);
        free(vector -> array[i]);
        #endif
    }

    free(vector -> array);
    vector -> array = ok;
}

void VECTOR_ADD(VECTOR_NAME * vector, VECTOR_TYPE value) {
    while ( (vector -> element + 1) * sizeof(VECTOR_TYPE) > vector -> memoryAmount) {
        VECTOR_EXPAND(vector);
    }

    #if VECTOR_TYPE_INPUT != 's'
    vector -> array[vector -> element] = value;
    #else
    vector -> array[vector -> element] = malloc(strlen(value) + 1);
    strcpy(vector -> array[vector -> element], value);
    #endif

    vector -> element ++;
}

void VECTOR_POP(VECTOR_NAME * vector) {
    if (vector -> element <= 0 ) {
        printf("vector is empty\n");
        return;
    }

    #if VECTOR_TYPE_INPUT == 's'
    free(vector -> array[vector -> element]);
    #endif

    vector -> element --;
}

void VECTOR_PRINT(VECTOR_NAME vector) {
    int currentElement = 0;
    printf("[");
    while (currentElement < vector.element) {
        printf(FORMAT_STRING, vector.array[currentElement]);
        currentElement++;
        if (currentElement < vector.element) {
            printf(", ");
        }
    }

    printf("], %s vector,", STRING2(VECTOR_TYPE_NAME));
    printf(" current element number: %d, current memory amount: %lu, memory amount: %d\n", 
    vector.element, vector.element * sizeof(VECTOR_TYPE), vector.memoryAmount);
}

void VECTOR_FREE(VECTOR_NAME vector) {
    #if VECTOR_TYPE_INPUT == 's'
    for (int i = 0; i < vector.element; i++) {
        free(vector.array[i]);
    }
    #endif

    free(vector.array);
}

void VECTOR_INITIALIZE(VECTOR_NAME * vector, int elementAmount) {
    int memory = elementAmount * sizeof(VECTOR_TYPE);

    vector -> array = malloc(memory);
    vector -> memoryAmount = memory;
    vector -> element = 0;
}
#endif // end same type of vector include once

#undef VECTOR_REPETE
#undef VECTOR_TYPE_INPUT
#undef VECTOR_TYPE
#undef VECTOR_TYPE_NAME
#undef VECTOR_CAPITAL_TYPE
#undef FORMAT_STRING
#undef VECTOR_DEFAULT
#undef VECTOR_NAME
#undef VECTOR_INITIALIZE
#undef VECTOR_ADD
#undef VECTOR_POP
#undef VECTOR_PRINT
#undef VECTOR_FREE
#undef VECTOR_EXPAND

/*
int main() {
    vector vector1;
    initializeVector(vector1);
    add(&vector1, 1);
    printVector(vector1);
    add(&vector1, 2);
    printVector(vector1);
    add(&vector1, 3);
    printVector(vector1);
    pop(&vector1);
    printVector(vector1);
    
    freeV(vector1);
}
*/
