/*
Hello, thanks for using this! I can't believe that you are using this file, thank you so much :) !

There are 1 required macro and 1 optional macro
    VECTOR_TYPE_INPUT (required): a character indicating which type of vector this file will create
        'i': int
        'c': character
        's': string
        'b': bool
    VECTOR_NO_IO (optional): any value (including no value) is fine. If defined, will not include stdio.h and the print function

Structure and function syntax
    Structure: <type>Vector
    Index: <type>VectorIndex(<corresponding vector type> * input, size_t index)
    Update: <type>VectorUpdate(<corresponding vector type> * input, size_t index, <type> value)
    Add: <type>VectorAdd(<corresponding vector type> * input, <type>)
    Pop: <type>VectorPop(<corresponding vector type> * input)
    Initialize: <type>VectorInitialize(<corresponding vector type> * input, size_t capacity)
    Free: <type>VectorFree(<corresponding vector type> * input)
    Size: <type>VectorSize(<corresponding vector type> * input)
    Print: <type>VectorPrint(<corresponding vector type> * input)
    note: the type of string here will be "string," not char [] or char *

For the entire documentation, please visit https://github.com/yuelin-wang/C-Standard-Template-Library/tree/main/Vector
*/


// vector included once (if you use multiple types of vector, this section will be only included once)
#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#define VECTOR_ADD_TYPE(word)    ADD2(VECTOR_TYPE_NAME, word)   // concatenate "<vector's type>" with "<word>"
#define VECTOR_ADD_NAME(word)    ADD2(VECTOR_NAME, word)    // concatenate "<vector's type>Vector" with "<word>"

#ifndef VECTOR_NO_IO
#include <stdio.h>  // printf
#endif
#include <stdlib.h> // memory allocation, size_t

#endif // end vector include once code


// C STL macro function include once (if you use other files from C STL, this section will be only included once)
#ifndef C_STL_MACRO_HEADER
#define C_STL_MACRO_HEADER

#define ADD1(pre, word)   pre##word         // first layer of 2-word concatenation
#define ADD2(pre, word)   ADD1(pre, word)   // second layer of 2-word concatenation (note: 2 layers of word concatenation 
                                            // allows parameter expansion before concatenation)
#define STRING1(word) #word                 // first layer of stringify
#define STRING2(word) STRING1(word)         // second layer of stringify
#define ADD_BOOL1(word)   bool##word        // first layer of concatenating "bool" with "<word>"
#define ADD_BOOL2(word)   ADD_BOOL1(word)   // second layer of concatenation "bool" with "<word>"

#endif // end C STL macro function include once


// type input

// int
#if VECTOR_TYPE_INPUT == 'i'
#define VECTOR_TYPE     int     // the name of the type in C syntax
#define VECTOR_TYPE_NAME int    // the name of the type in the function name
#define FORMAT_STRING   "%d"

// inclusion guard for including the same type of vector multiple times
#ifndef VECTOR_INT_HEADER
#define VECTOR_INT_HEADER
#else
#define VECTOR_REPETE
#endif


// string
#elif VECTOR_TYPE_INPUT == 's'
#define VECTOR_TYPE     char *
#define VECTOR_TYPE_NAME string
#define FORMAT_STRING   "%s"

#include <string.h>             // strcpy

#ifndef VECTOR_STRING_HEADER
#define VECTOR_STRING_HEADER
#else
#define VECTOR_REPETE
#endif


// character
#elif VECTOR_TYPE_INPUT == 'c'
#define VECTOR_TYPE     char
#define VECTOR_TYPE_NAME char
#define FORMAT_STRING   "%c"

#ifndef VECTOR_CHAR_HEADER
#define VECTOR_CHAR_HEADER
#else
#define VECTOR_REPETE
#endif


// bool
#elif VECTOR_TYPE_INPUT == 'b'
#define VECTOR_TYPE     bool
#define VECTOR_TYPE_NAME boolean
#define FORMAT_STRING   "%d"

#if __STDC_VERSION__ < 202311L
#include <stdbool.h>            // bool
#endif

#ifndef VECTOR_BOOL_HEADER
#define VECTOR_BOOL_HEADER
#else
#define VECTOR_REPETE
#endif

#endif  // end type input


// vector name
#if VECTOR_TYPE_INPUT != 'b' || __STDC_VERSION__ >= 202311L
#define VECTOR_NAME     VECTOR_ADD_TYPE(Vector)
#else // in case Boolean type and prior to C23 (which the formal name is actuall "_Bool")
#define VECTOR_NAME     ADD_BOOL2(Vector)
#endif

// vector function name
#define VECTOR_INITIALIZE   VECTOR_ADD_NAME(Initialize)
#define VECTOR_ADD      VECTOR_ADD_NAME(Add)
#define VECTOR_POP      VECTOR_ADD_NAME(Pop)
#define VECTOR_FREE     VECTOR_ADD_NAME(Free)
#define VECTOR_EXPAND   VECTOR_ADD_NAME(Expand)
#define VECTOR_PRINT    VECTOR_ADD_NAME(Print)


// inclusion guard for including the same type of vector multiple times
#ifndef VECTOR_REPETE

// structure
typedef struct VECTOR_NAME {
    size_t size;
    size_t capacity;
    VECTOR_TYPE* array;
} VECTOR_NAME;

// Expand
// MODIFIES: the pointer to the array, the capacity
// EFFECTS: double the capacity of the vector, (deep) copy the old array to the new array, free the memory allocated for the old array
// NOTE: you, as the user, usually would not need to use this function. Addition function will handle all the expansion for you
void VECTOR_EXPAND(VECTOR_NAME * vector) {
    vector -> capacity *= 2;
    VECTOR_TYPE * temp = malloc(vector -> capacity * sizeof(VECTOR_TYPE));
    for (int i = 0; i < vector -> size; i ++) {
        #if VECTOR_TYPE_INPUT != 's'
        temp[i] = (vector -> array)[i];
        #else
        temp[i] = malloc(strlen(vector -> array[i]) + 1);
        strcpy(temp[i], vector -> array[i]);
        free(vector -> array[i]);
        #endif
    }

    free(vector -> array);
    vector -> array = temp;
}

// Add
// MODIFIES: the size, the pointer to the array (if expanding), the capacity (if expanding)
// EFFECTS: increase the size by 1, add the value at the end of the vector
void VECTOR_ADD(VECTOR_NAME * vector, VECTOR_TYPE value) {
    while ( (vector -> size + 1) > vector -> capacity) {
        VECTOR_EXPAND(vector);
    }

    #if VECTOR_TYPE_INPUT != 's'
    vector -> array[vector -> size] = value;
    #else
    vector -> array[vector -> size] = malloc(strlen(value) + 1);
    strcpy(vector -> array[vector -> size], value);
    #endif

    vector -> size ++;
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


#ifndef VECTOR_NO_IO
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
#endif


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
#endif // end inclusion guard for including the same type of vector multiple times


#undef VECTOR_REPETE

#undef VECTOR_TYPE_INPUT
#undef VECTOR_NO_IO

#undef VECTOR_TYPE
#undef VECTOR_TYPE_NAME
#undef FORMAT_STRING

#undef VECTOR_NAME
#undef VECTOR_INITIALIZE
#undef VECTOR_ADD
#undef VECTOR_POP
#undef VECTOR_PRINT
#undef VECTOR_FREE
#undef VECTOR_EXPAND

/*
int main() {

    return 0;
}
*/
