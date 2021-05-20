#ifndef _NODE_H_
#define _NODE_H_

#include "Object.h"
#include "String.h"

typedef struct Node_int Node_int;
typedef struct Node_long Node_long;
typedef struct Node_ptr Node_ptr;
typedef struct Node_String Node_String;

typedef struct Node_int_int       Node_int_int;
typedef struct Node_int_long      Node_int_long;
typedef struct Node_int_ptr       Node_int_ptr;
typedef struct Node_int_String    Node_int_String;
typedef struct Node_long_int      Node_long_int;
typedef struct Node_long_long     Node_long_long;
typedef struct Node_long_String   Node_long_String;
typedef struct Node_long_ptr      Node_long_ptr;
typedef struct Node_String_int    Node_String_int;
typedef struct Node_String_long   Node_String_long;
typedef struct Node_String_String Node_String_String;
typedef struct Node_String_ptr    Node_String_ptr;
typedef struct Node_ptr_int       Node_ptr_int;
typedef struct Node_ptr_long      Node_ptr_long;
typedef struct Node_ptr_String    Node_ptr_String;
typedef struct Node_ptr_ptr       Node_ptr_ptr;

#define UniNode(T) struct Node_##T {  \
	Node_##T * pre;  \
	Node_##T * next; \
	T value;  \
}

#define BiNode(K, V) struct Node_##K##_##V { \
	Node_##K##_##V * pre;  \
	Node_##K##_##V * next; \
	K key; \
	V value;  \
}

void Node_connect(void * father, void * son) {
	*(void**)(father + 8) = son;
	*(void**)son = father;
}

UniNode(int);
UniNode(long);
UniNode(ptr);
UniNode(String);

BiNode(int,int);
BiNode(int,long);
BiNode(int,String);
BiNode(int,ptr);
BiNode(long,int);
BiNode(long,long);
BiNode(long,String);
BiNode(long,ptr);
BiNode(String,int);
BiNode(String,long);
BiNode(String,ptr);
BiNode(String,String);
BiNode(ptr,int);
BiNode(ptr,long);
BiNode(ptr,String);
BiNode(ptr,ptr);



#endif