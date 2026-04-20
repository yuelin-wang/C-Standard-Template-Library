# Vector
C type generic vector

## Content

#### Structure
The structure name is `<type>Vector`
```C
stringVector v1; // a string vector named v1
intVector v2; // an integer vector named v2
```

#### Function

#### Type Support

| Type | Structure | Index | Update | 
| :----: | :---------: | :-----: | :------: | 
| int | `intVector` | `int intVectorIndex(intVector * input, int index)` | `void intVectorUpdate(intVector * input, int index, int value)` | 
| string | `stringVector` | `char * stringVectorIndex(stringVector * input, int index)` | `void stringVectorUpdate(stringVector * input, int index, char * value)` |

continue: 
| Type | Add | Pop | Initialize |
| :----: | :---: | :---: | :----------: |
| int | `void intVectorAdd(intVector * input, int value)` | `void intVectorPop(intVector * input)` |  `void intVectorInitialize(intVector * input, int size)` |
| string | `void stringVectorAdd(stringVector * input, char * value)` | `void stringVectorPop(stringVector * input)` | `void stringVectorInitialize(stringVector * input, int size)` |

continue:
| Type | Free | Expand | Print |
| :----: | :----: | :------: | :-----: |
| int | `void intVectorFree(intVector * input)` | `void intVectorExpand(intVector * input)` | `void intVectorPrint(intVector * input)` |
| string | `void stringVectorFree(stringVector * input)` | `void stringVectorExpand(stringVector * input)` | `void stringVectorPrint(stringVector * input)` |

## Usage
