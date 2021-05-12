# STL-in-C
Implemented some basic simple STL containers using C, probably come in handy when doing OJ

This is a **single-thread** OOP solution for C. It is a little bit ugly but to some degree gives you illusion as if you were programming in C++.

To imitate OOP, the "Object.h" header file manages a this pointer which could only point to a single object at any time, and that's why it only works in single-thread scenarios like most OJ. After initializing an **obj** and before you call any of its **method**, call **Object.load(&obj)** and then you could just program like C++.
 
 
Then the ugly part comes, **whenever you want to use another obj', you have call Object.load(&obj'). So, if your code have to switch frequently between objects, the code would probably look messy.**
 
 
Vector only supports 6 basic types (does not support unsigned) and ptr(void *).




**Vector Interface:**
```C
void  push_back(T val);     // automatically manage growing storage
void  pop_back();           // no bound check, automatically manage shrinking storage
T     at(int idx);          // no bound check
T     back();               // no bound check
int   size(); 
void  destory();            // destructor
void  set(int idx, T val);  // no bound check
```


**Sample Usage # 1: Vector**
```C
#include <stdio.h>
#include "Vector.h"

int main() {
    Vector(int) vec = DEFAULT_INT_VECTOR;  
    // all objects should initialize using this format:  Container(type) name = DEFAULT_TYPE_CONTAINER;
    
    Object.load(&vec) // switch this pointer
    
    for (int i = 0; i < 5; ++i)
        vec.push_back(i);
        
     while (vec.size()) {
         printf("%d ", vec.back());
         vec.pop_back();
     }
     
     // stdout: 4 3 2 1 0
     
     vec.destroy(); // destructor
     vec.push_back(1); // undefined behavior
     
     return 0;
}
```

**Sample Usage # 2: Vector**
```C
#include <stdio.h>
#include "Vector.h"

typedef Vector(double) Vector_double;

int main() {
    Vector(ptr) vec = DEFAULT_PTR_VECTOR;
    Vector_double d = DEFAULT_DOUBLE_VECTOR;
    Object.load(&d);
    d.push_back(2.5);
    d.push_back(3); // d = [2.5, 3]
    Object.load(&vec);
    vec.push_back(&d);
	    
     /*
     vec = [ ptr ]
               | 
                - - - - -> Vector(double) = [2.5, 3]
     */  
     
    Vector_double * ptr = vec.back();
    Object.load(ptr);
    printf("%d\n",ptr->size()); // stdout : 2
    
    return 0;
}
```

**Sample Usage # 3: String**
```C
#include <stdio.h>
#include "String.h"

int main(int argc, char const *argv[])
{
    String str = DEFAULT_STRING;
    Object.load(&str);
    str.push_back('a');
    str.concat(" nice STRING ");
    str.set(9,'?');
    for (int i = 0; i < str.size(); ++i)
        printf("%c", str.at(i));  
    // stdout:a nice ST?ING

    return 0;
}
```

**Sample Usage # 4: Queue**
```C
#include <stdio.h>
#include "Queue.h"

int main(int argc, char const *argv[])
{
	Queue(int) q = DEFAULT_INT_QUEUE;
	Object.load(&q);
	
	q.push(1), q.push(2);   // 1 -> 2
	q.pop();                // 2
	q.push(4), q.push(5);
	q.push(6), q.push(7);   // 2 -> 4 -> 5 -> 6 -> 7
	q.pop(), q.pop();       // 5 -> 6 -> 7

	while (q.size()) {
		printf("%d ", q.front());
		q.pop();  
	}
	// stdout: 5 6 7
	
    return 0;
}
```


**Note**

Vector(type) is not a type itself but a definition of struct, you could initialize all vectors of the same type together
at the very beginning like what ANSI C required. Calling Vector(type) twice is invalid, please instead use typedef like sample Usage #2.




