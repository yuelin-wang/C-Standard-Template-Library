# Queue
C type generic queue

## Usage
Please first read the [usage section](../README.md#usage) of the C STL.  
For queue, there are 1 required macro and 1 optional macro you need to define.

Required:
- QUEUE_TYPE_INPUT: this defines the type of the queue. The value is one of the character listed below:
    - `'i'`: int
    - `'s'`: string
    - `'b'`: bool
    - `'c'`: character 

Optional:
- QUEUE_NO_IO: this means that the queue included will not have a printing function and will not include the `stdio.h` library. The value could be anything (including no values). As long as this macro is defined, the queue will not include the `stdio.h` library 

You need to define QUEUE_TYPE_INPUT everytime you include a queue. If you want all the queues you included to not have a printing function, you need to define VECTOR_NO_IO everytime you include a queue.
```C
#define QUEUE_TYPE_INPUT 's'
#define QUEUE_NO_IO
#include "queue.c" // this will include a string queue with no printing function and does not include stdio.h

#define QUEUE_TYPE_INPUT 'i'
#include "queue.c" // this will include an integer queue and include stdio.h
```

## Content

### Type Support
The supported types are:
- int
- string
- bool
- character 

### Structure
The structure name is `<type>Queue`
```C
stringQueue q1; // a string queue named q1
intQueue q2; // an integer queue named q2
```

### Function
| Name | `std::queue` counterpart | Functionality | Time Complexity |
| :----: | :-------------------------: | :-------------: | :---------------: |
| Front | `q.front()` | Returns a copy of the front element | O(1)
| Add | `q.push(<value>)` | Adds the value at the end of the queue | (Amortized) O(1) |
| Pop | `q.pop()` | Removes the last element | O(1) |
| Initialize | The Constructor (but could set the capacity) | Initializes the queue, specifies the capacity | O(1) |
| Free | The Destructor | Frees the allocated memory | O(1) (non-string queue)/O(n) (string queue) |
| Size | `q.size()` | Returns the size of the queue | O(1) |
| Print | N/A | Prints the elements of the queue | O(n) |