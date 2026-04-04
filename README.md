# C Standard Template Library

## Usage
1. Download: go to the corresponding container folders and download the C files.
2. Include the container: a container usually requires some definitions of macro. In your C code files, first define the macros and then include the downloaded C container. 
    ```C
    #define VECTOR_TYPE_INPUT 'i'
    #include "vector.c"
    ```
3. Use the corresponding structure: then you should have a structure that you can use.
    ```C
    intVector vector;
    initializeIntVector(vector);
    intVectorAdd(vector, 5);
    ```