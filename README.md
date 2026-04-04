# C Standard Template Library

This library provides type generic containers in C.

## Usage
1. Download: go to the corresponding container folders and download the C codes.
2. Include the container: a container from this library usually requires some definitions of macro. In your C code files, first define the macros and then include the downloaded C container. 
    ```C
    #define VECTOR_TYPE_INPUT 'i'
    #include "vector.c"
    ```
3. Use the corresponding structure: then you should have a type definition of a structure that you can use.
    ```C
    intVector vector;
    initializeIntVector(&vector, 8);
    intVectorAdd(&vector, 5);
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