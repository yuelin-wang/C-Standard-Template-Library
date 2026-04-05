# C Standard Template Library

This library provides type generic containers in C.

## Content
| ADT | Implementation | Freestanding | Minimum Standard |
| :---: | :--------------: | :------------: | :----------------:|
| Vector | Array | No (I/O, String, Memory Allocation) | C99 |
| Queue | Circular Buffer | No (I/O, String, Memory Allocation) | C99 |
| Dictionary | Hash Table | No (I/O, String, Memory Allocation) | C99 |

## Usage
1. Download: go to the corresponding container folders and download the C codes.
2. Include the container: to use a data structure, please include the downloaded C code in your file. Before including, a container from this library usually requires some definitions of macro. In your C code files, first define the macros and then include the downloaded C container. 
    ```C
    #define VECTOR_TYPE_INPUT 'i'
    #include "vector.c"
    ```
    Each type of the data structure requires an individual input macro definition and inclusion.
    ```C
    #define VECTOR_TYPE_INPUT 'i'
    #include "vector.c" // integer vector
    #define VECTOR_TYPE_INPUT 's'
    #include "vector.c" // string vector
    ```
3. Use the corresponding structure: then you should have a type definition of a structure and various functions associating with that structure that you can use.
    ```C
    intVector vector; // (the type definition of) the structure of integer vector
    initializeIntVector(&vector, 8); // the initializing function of integer vector
    intVectorAdd(&vector, 5); // the addition function of integer vector
    ```

## Example
```C
#define VECTOR_TYPE_INPUT 'i'
#include "vector.c"

#define VECTOR_TYPE_INPUT 's'
#include "vector.c"

int main() {
    intVector vector1;
    initializeIntVector(&vector1, 8);
    intVectorAdd(&vector1, 5);

    intVector vector2;
    initializeIntVector(&vector2, 8);
    intVectorAdd(&vector2, 4);
    printIntVector(vector2);

    stringVector vector3;
    initializeStringVector(&vector3, 5);
    stringVectorAdd(&vector3, "hello world");

    freeIntV(vector1);
    freeIntV(vector2);
    freeStringV(vector3);

    return 0;
}
```

## License
[C STL](https://github.com/yuelin-wang/C-Standard-Template-Library) by [Yuelin Wang (Steven)](https://github.com/yuelin-wang) is marked [CC0 1.0](https://creativecommons.org/publicdomain/zero/1.0/)![Creative Common icon](https://mirrors.creativecommons.org/presskit/icons/cc.svg)![Creative Common 0 icon](https://mirrors.creativecommons.org/presskit/icons/zero.svg)