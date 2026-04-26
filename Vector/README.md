# Vector
C type generic vector

## Usage

Please first read the [usage section](https://github.com/yuelin-wang/C-Standard-Template-Library#usage) of the C STL.  
For vector, there are 1 required macro and 1 optional macro you need to define.

Required:
- VECTOR_TYPE_INPUT: this defines the type of the vector. The value is one of the character listed below:
    - `'i'`: int
    - `'s'`: string
    - `'b'`: bool
    - `'c'`: character 

Optional:
- VECTOR_NO_IO: this means that the vector included will not have a printing function and will not include `stdio.h` library. The value could be anything (including no values). As long as this macro is defined, the vector will not include `stdio.h` library 

You need to define VECTOR_TYPE_INPUT everytime you include a vector. If you want all the vectors you included to not have a printing function, you need to define VECTOR_NO_IO everytime you include a vector.
```C
#define VECTOR_TYPE_INPUT 's'
#define VECTOR_NO_IO
#include "vector.c" // this will include a string vector with no printing function and does not include stdio.h

#define VECTOR_TYPE_INPUT 'i'
#include "vector.c" // this will include an integer vector and include stdio.h
```

## Content
Each inclusion of a vector will introduce (a type definition of) a structure and various global functions. These global functions is equal to the member function of C++'s `std::vector`. Say you want to index the second element of an int vector, in C++ that's `v[1]` and in this library that's `intVectorIndex(&v, 1)`.

### Structure
The structure name is `<type>Vector`
```C
stringVector v1; // a string vector named v1
intVector v2; // an integer vector named v2
```
The names of the types are
| General Name | Name Used in This Library | C type |
| :----: | :----: | :------: |
| int/signed int | int | `int` |
| string | string | `char *`/`char []` |
| boolean/logical | bool | `_Bool`/`bool` |
| character | char | `char` |

### Function

| Name | `std::vector` counterpart | Functionality | Time Complexity |
| :----: | :-------------------------: | :-------------: | :---------------: |
| Index | `v[<index>]` | Returns the element at the specified index | O(1) |
| Update | `v[<index>] = <value>` | Updates the element at the specified index | O(1) |
| Add | `v.push_back(<value>)` | Adds the value at the end of the vector | (Amortized) O(1) |
| Pop | `v.pop_back(<value>)` | Removes the last element | O(1) |
| Initialize | The Constructor | Initializes the vector, specifies the capacity | O(1) |
| Free | The Destructor | Frees the allocated memory | O(1) (non-string vector)/O(n) (string vector) |
| Size | `v.size()` | Returns the size of the vector | O(1) |
| Expand | `v.reserve(<the current capacity * 2>)` | Doubles the capacity | O(n) |
| Print | N/A | Prints the elements of the vector | O(n) |

#### Index
Syntax: `<type>  <type name>VectorIndex(<corresponding vector> * input, int index)`
- returns in the corresponding type
- 2 arguments
    - a pointer of a vector in corresponding
    - an int that specifies the index (first element is at index 0, same as C)

### Type Support
The supported types are:
- int
- string
- bool
- character 

| Type | Structure | Index | Update | 
| :----: | :---------: | :-----: | :------: | 
| int | `intVector` | `int intVectorIndex(intVector * input, int index)` | `void intVectorUpdate(intVector * input, int index, int value)` | 
| string | `stringVector` | `char * stringVectorIndex(stringVector * input, int index)` | `void stringVectorUpdate(stringVector * input, int index, char * value)` |

continue: 
| Type | Add | Pop |
| :----: | :---: | :---: |
| int | `void intVectorAdd(intVector * input, int value)` | `void intVectorPop(intVector * input)` |
| string | `void stringVectorAdd(stringVector * input, char * value)` | `void stringVectorPop(stringVector * input)` |

continue: 
| Type | Initialize | Free |
| :----: | :----------: | :----: |
| int | `void intVectorInitialize(intVector * input, int size)` | `void intVectorFree(intVector * input)` |
| string | `void stringVectorInitialize(stringVector * input, int size)` | `void stringVectorFree(stringVector * input)` |

continue:
| Type | Size | Expand | Print |
| :----: | :----: | :------: | :-----: |
| int | `size_t intVectorSize(intVector * input)` | `void intVectorExpand(intVector * input)` | `void intVectorPrint(intVector * input)` |
| string | `size_t stringVectorSize(stringVector * input)` | `void stringVectorExpand(stringVector * input)` | `void stringVectorPrint(stringVector * input)` |
