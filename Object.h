#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <stdlib.h>
#include <string.h>

#define CHAR   0
#define SHORT  1
#define INT    2
#define LONG   3
#define FLOAT  4
#define DOUBLE 5
#define PTR    6
typedef void * ptr;
typedef char _char_;
typedef short _short_;
typedef int _int_;
typedef long _long_;
typedef float _float_;
typedef double _double_;
typedef ptr _ptr_;

void * this;

struct _wrapper_ {
	void (*load)(void*);
};

static void callMethod(void * obj) { this = obj; }

struct _wrapper_ Object = { callMethod };

#endif
