#ifndef _NODE_H_
#define _NODE_H_

#include "Object.h"
#include "String.h"

typedef struct Node_int Node_int;
typedef struct Node_long Node_long;
typedef struct Node_ptr Node_ptr;
typedef struct Node_String Node_String;

#define UniNode(T) struct Node_##T {  \
	Node_##T * pre;  \
	Node_##T * next; \
	T value;  \
}

#define BiNode(K, V) struct Node_##K_##V { \
	Node_##T * pre;  \
	Node_##T * next; \
	K key; \
	T value;  \
}

void Node_connect(void * father, void * son) {
	*(void**)(father + 8) = son;
	*(void**)son = father;
}

UniNode(int);
UniNode(long);
UniNode(ptr);
UniNode(String);



#endif