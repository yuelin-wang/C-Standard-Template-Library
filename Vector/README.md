# Vector
C type generic vector

## Usage
Please first read the [usage section](../README.md#usage) of the C STL.  
For vector, there are 1 required macro and 1 optional macro you need to define.

Required:
- VECTOR_TYPE_INPUT: this defines the type of the vector. The value is one of the character listed below:
    - `'i'`: int
    - `'s'`: string
    - `'b'`: bool
    - `'c'`: character 

Optional:
- VECTOR_NO_IO: this means that the vector included will not have a printing function and will not include the `stdio.h` library. The value could be anything (including no values). As long as this macro is defined, the vector will not include the `stdio.h` library 

You need to define VECTOR_TYPE_INPUT everytime you include a vector. If you want all the vectors you included to not have a printing function, you need to define VECTOR_NO_IO everytime you include a vector.
```C
#define VECTOR_TYPE_INPUT 's'
#define VECTOR_NO_IO
#include "vector.c" // this will include a string vector with no printing function and does not include stdio.h

#define VECTOR_TYPE_INPUT 'i'
#include "vector.c" // this will include an integer vector and include stdio.h
```

## Content

### Type Support
The supported types are:
- int
- string
- bool
- character 

### Structure
The structure name is `<type>Vector`
```C
stringVector v1; // a string vector named v1
intVector v2; // an integer vector named v2
```

### Function

| Name | C++'s `std::vector` Counterpart | Functionality | Time Complexity |
| :----: | :-------------------------: | :-------------: | :---------------: |
| Index | `v[<index>]` | Returns the element at the specified index | O(1) |
| Update | `v[<index>] = <value>` | Updates the element at the specified index | O(1) |
| Add | `v.push_back(<value>)` | Adds the value at the end of the vector | (Amortized) O(1) |
| Pop | `v.pop_back()` | Removes the last element | O(1) |
| Initialize | The Constructor (but only sets the capacity, does not set the size) | Initializes the vector, specifies the capacity | O(1) |
| Free | The Destructor | Frees the allocated memory | O(1) (non-string vector)/O(n) (string vector) |
| Size | `v.size()` | Returns the size of the vector | O(1) |
| Print | N/A | Prints the elements of the vector | O(n) |

#### Index
Function name: `<type name>VectorIndex`

Syntax: 
```C
<type>  <type name>VectorIndex(<corresponding vector> * input, size_t index)
```
- returns in the corresponding type
- 2 arguments
    - a pointer of a vector in corresponding type
    - a size_t that specifies the index (first element is at index 0, same as C)
- for the index argument, a simple integer constant (such as `4`) should be fine. Although the type of the integer constant is most likely going to be int, C will perform implicit conversion to size_t

Example:
```C
int element = intVectorIndex(&v, 1); // returns the value of the second element
```

#### Update
Function name: `<type name>VectorUpdate`

Syntax: 
```C
void <type name>VectorUpdate(<corresponding vector> * input, size_t index, <corresponding type> value)
```
- 3 arguments
    - a pointer of a vector in corresponding type
    - a size_t that specifies the index
    - the value you want to update

Example:
```C
intVectorUpdate(&v, 2, 1928); // update the third element to 1928
```

#### Add
Function name: `<type name>VectorAdd`

Syntax: 
```C
void <type name>VectorAdd(<corresponding vector> * input, <corresponding type> value)
```
- 2 arguments
    - a pointer of a vector in corresponding type
    - the element to add
- same as C++, this will increase size by 1 and doesn't change capacity, adding the element at the end of the vector
- will expand the vector if the current capacity is full before the addition

Example: 
```C
intVectorAdd(&v, 239); // add the element of 239 at the end of the vector
```

#### Pop
Function name: `<type name>VectorPop`

Syntax:
```C
void <type name>VectorPop(<corresponding vector> * input)
```
- 1 argument
    - a pointer of a vector in corresponding type
- reduces the size by 1, removes the last element
- the size of the vector need to be ≥ 1

Example:
```C
intVectorPop(&v); // remove the last element
```

#### Initialize
Function name: `<type name>VectorInitialize`

Syntax:
```C
void <type name>VectorInitialize(<corresponding vector> * input, size_t capacity)
```
- 2 arguments
    - a pointer of a vector in corresponding type
    - a size_t that specifies the initial capacity
- note that this only sets the capacity, the size is stll 0. Using addition after this will increase the size to 1 and add the element to the first position. This is different from C++ STL, where `vector<int> v(10);` will set both the size and capacity to 10

Example:
```C
intVectorInitialize(&v, 10); // sets the capacity to 10, size is 0
```

#### Free
Function name: `<type name>VectorFree`

Syntax:
```C
void <type name>VectorFree(<corresponding vector> * input)
```
- 1 argument
    - a pointer of a vector in corresponding type
- calls `free()` under the hood. Thus, please ensure that you free every vector at the end to avoid memory leak

Example: 
```C
intVectorFree(&v); // frees the dynamic memory allocated for the vector
```

#### Size
Function name: `<type name>VectorSize`

Syntax:
```C
size_t <type name>VectorSize(<corresponding vector> * input)
```
- 1 argument
    - a pointer of a vector in corresponding type
- returns the number of element in the vector

Example:
```C
for (size_t i = 0; i < intVectorSize(&v); i++) {
    printf("%d ", intVectorIndex(&v, i));
}
```

#### Print
Function name: `<type name>VectorPrint`

Syntax:
```C
void <type name>VectorPrint(<corresponding vector> * input)
```
- 1 argument
    - a pointer of a vector in corresponding type
- will not exist if the macro `VECTOR_NO_IO` is defined

Printing content:
- every element
- type of vector
- current size
- current capacity

Format: `[<value 1>, <value 2>, ... <value n>], <type> vector, current size: <size>, current capacity: <capacity>\n`

Exmaple:
```C
intVectorPrint(&v1) // [15, 10, 5], int vector, current size: 3, current capacity: 4\n
```

## Library Inclusion
The following libraries will be included in this file
- `stdlib.h`: for memory allocation
- `stdio.h` (if the macro `VECTOR_NO_IO` is not defined): for printing
- `string.h` (if the vector type is string): for `strcpy()`
- `stdbool.h` (if the vector type is bool and if the standard the compiler is using is prior to C23): for macro `true` and `false`

## Notes on Boolean Vector
- when you are supplying the `value` argument in `boolVectorUpdate()`, integral value such as `1` or Boolean value such as `true` are both fine

## Example
```C
#define VECTOR_TYPE_INPUT 'i'
#include "vector.h" // includes integer vector

#define VECTOR_TYPE_INPUT 's'
#include "vector.h" // includes string vector

int main() {
    intVector v1;
    intVectorInitialize(&v1, 4);
    intVectorAdd(&v1, 10);  // [10]
    intVectorAdd(&v1, 5);   // [10, 5]
    intVectorUpdate(&v1, 1, 10);    // [10, 10]
    intVectorPop(&v1);      // [10]
    intVectorPrint(&v1);    // [10], int vector, current size: 1; current capacity: 4\n

    stringVector v2;
    stringVectorInitialize(&v2, 4);
    stringVectorAdd(&v2, "I");      // ["I"]
    stringVectorAdd(&v2, "love");   // ["I", "love"]
    stringVectorAdd(&v2, "Taylor Swift");   // ["I", "love", "Taylor Swift"]
    for (size_t i = 0; i < stringVectorSize(&v2); i++) {
        printf("%s ", stringVectorIndex(&v2, i));
    }
    printf("\n");
    // I love Taylor Swift

    stringVector v3;
    stringVectorInitialize(&v3, 4);
    stringVectorAdd(&v3, "the future is dark");  // ["the future is dark"]
    stringVectorUpdate(&v3, 0, "but trust me, hope will always by your side!"); // ["but trust me, hope will always by your side!"]

    intVectorFree(&v1);
    stringVectorFree(&v2);
    stringVectorFree(&v3);
    
    return 0;
}
```