# STL-in-C
Implemented some basic simple STL containers using C, probably come in handy when doing OJ

This is a single-thread OOP solution for C. It is a little bit ugly but to some degree gives you illusion as if you were programming in C++.

To imitate OOP, the "Object.h" header file manages a this pointer which could only point to a single object at any time, and that's why it only works in single-thread scenarios like most OJ. After initializing an <obj> and before you call any of its <method>, call Object.load(&obj) and then you could just use it like C++.
 Then the ugly part comes, whenever you want to use another <obj'>, you have call Object.load(&obj). So, if your code have to switch frequently between objects, the code would probably look messy.
 
