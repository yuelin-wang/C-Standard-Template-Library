# Vector
C type generic vector

## Content

#### Type Support

| Type | Structure | Index | Update | 
| :----: | :---------: | :-----: | :------: | 
| int | `intVector` | `int intVectorIndex(intVector * input, int index)` | `void intVectorUpdate(intVector * input, int index, int value)` | 
| string | `stringVector` | `char * stringVectorIndex(stringVector * input, int index)` | `void stringVectorUpdate(stringVector * input, int index, char * value)` |

continue: 
| Type | Add | Pop | Initialize |
| :----: | :---: | :---: | :----------: |
| int | `void intVectorAdd(intVector * input, int value)` | `void intVectorPop(intVector * input)` |  `void initializeIntVector(intVector * input, int size)` |
| string | `void stringVectorAdd(stringVector * input, char * value)` | `void stringVectorPop(stringVector * input)` | `void initializeStringVector(stringVector * input, int size)` |

## Usage