# C Standard Template Library

This library provides type generic containers in C.

## Content
| ADT | Implementation | Freestanding | Minimum Standard |
| :---: | :--------------: | :------------: | :----------------:|
| Vector | Array | No (Memory Allocation) | C99 |
| Queue | Circular Buffer | No (Memory Allocation) | C99 |
| Dictionary | Hash Table | No (Memory Allocation, Random) | C99 |

## Usage
1. Download: go to the corresponding container folders and download the C codes.
2. Include the container: to use a data structure, please include the downloaded C code in your file. Before including, a container from this library usually requires some definitions of macro. In your C code files, first define the macros and then include the downloaded C container. 
    ```C
    #define VECTOR_TYPE_INPUT 'i'
    #include "vector.c"
    ```
    An inclusion will usually introduce a (type definition of a) structure and various global functions. The structure is the corresponding container, while global functions resemble the member function of a container. In C++, if you want to declare an `std::vector`, initialize it, and push back an element of `4`, you would write 
    ```C++
    std::vector<int> v;
    v.reserve(10);
    v.push_back(4);
    ```
    while in this library, you would write
    ```C
    intVector v;    // v is an instance of a structure named intVector
    intVectorInitialize(&v, 10); // intVectorInitialize is a global function. 
                                 // Here it reserves 10 element for the vector
    intVectorAdd(&v, 4); // adds an element of 4 at the end of the vector
    ```
3. Each different type requires separate input macro definitions and inclusion.
    ```C
    #define VECTOR_TYPE_INPUT 'i'
    #include "vector.c" // integer vector

    #define VECTOR_TYPE_INPUT 's'
    #include "vector.c" // string vector
    ```
4. Free the allocated memory: in this library, the data structure will allocate dynamic memory. So please free the allocated memory for each instance at the end of the main function
    ```C
    intVectorFree(v); // frees the dynamic memory allocated for the instance v
    ```

## Example
```C
// includes integer vector
#define VECTOR_TYPE_INPUT 'i'
#include "vector.c"

// includes string vector
#define VECTOR_TYPE_INPUT 's'
#include "vector.c"

// includes dictionary with string key and integer value
#define DICTIONARY_KEY_TYPE_INPUT 's'
#define DICTIONARY_VALUE_TYPE_INPUT 'i'
#include "dictionary.c"

int main() {
    intVector vector1;
    intVectorInitialize(&vector1, 10);
    intVectorAdd(&vector1, 5);

    intVector vector2;
    intVectorInitialize(&vector2, 5);
    intVectorAdd(&vector2, 4);
    intVectorPrint(&vector2);

    stringVector vector3;
    stringVectorInitialize(&vector3, 5);
    stringVectorAdd(&vector3, "hello world");

    SIDictionary dictionary1;
    SIDictionaryInitialize(&dictionary, 4);
    SIDictionaryAdd(&dictionary, "key 1", 1);

    intVectorFree(&vector1);
    intVectorFree(&vector2);
    stringVectorFree(&vector3);
    SIDictionaryFree(&dictionary);

    return 0;
}
```

## License
C STL by Yuelin Wang (Steven) is marked [CC0 1.0](https://creativecommons.org/publicdomain/zero/1.0/)![Creative Common icon](https://mirrors.creativecommons.org/presskit/icons/cc.svg)![Creative Common 0 icon](https://mirrors.creativecommons.org/presskit/icons/zero.svg)