# STL-in-C
Implemented some basic simple STL containers using C, probably come in handy when doing OJ

This is a single-thread OOP solution for C. It is a little bit ugly but to some degree gives you illusion as if you were programming in C++.

To imitate OOP, the "Object.h" header file manages a this pointer which could only point to a single object at any time, and that's why it only works in single-thread scenarios like most OJ. After initializing an #obj and before you call any of its #method, call Object.load(&obj) and then you could just program like C++.
 
 
 Then the ugly part comes, whenever you want to use another <obj'>, you have call Object.load(&obj). So, if your code have to switch frequently between objects, the code would probably look messy.
 
 
Vector only supports 6 basic types (does not support unsigned) and ptr(void *).

Sample Usage #1:
```C
#include <stdio.h>
#include "Vector.h"

int main() {
    Vector(int) vec = DEFAULT_INT_VECTOR;  
    // all objects should initialize using this format:  Container(type) name = DEFAULT_TYPE_CONTAINER;
    
    Object.load(&vec) // switch this pointer
    
    for (int i = 0; i < 5; ++i)
        vec.push_back(i)
        
     while (vec.size()) {
         printf("%d ", vec.back());
         vec.pop_back();
     }
     
     // stdout: 4 3 2 1 0
     
     vec.destroy() // destructor
     vec.push_back(1) // undefined behavior
     
}
```

Sample Usage #1:
```C
#include "stdio.h"
#include "Vector.h"

typedef Vector(double) Vector_double;

int main() {
     Vector(ptr) vec = DEFAULT_PTR_VECTOR;
	    Vector_double d = DEFAULT_DOUBLE_VECTOR;
	    Object.load(&d);
	    d.push_back(2.5);
	    d.push_back(3);
	    Object.load(&vec);
	    vec.push_back(&d);
	    Vector_double * ptr = vec.back();
	    
     /*
     Vector(ptr) -> [(void*)]
                        | 
                        - - - - -> Vector(double) -> [2.5, 3]
     */  
     
     Object.load(ptr);
	    printf("%d\n",ptr->size()); // stdout : 2
	    return 0;
}
     
}
```


Note Vector(type) is not a type itself but a definition of struct, you could initialize all vectors of the same type together
at the very beginning like what ANSI C required. If you do not want this, use typedef.
