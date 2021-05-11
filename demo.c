#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Vector.h"
typedef Vector(double) Vector_double;
int main(int argc, char const *argv[])
{
	Vector(ptr) vec = DEFAULT_PTR_VECTOR;
	Vector_double d = DEFAULT_DOUBLE_VECTOR;
	Object.load(&d);
	d.push_back(2.5);
	d.push_back(3);
	Object.load(&vec);
	vec.push_back(&d);
	Vector_double * ptr = vec.back();
	Object.load(ptr);
	printf("%d\n",ptr->size());
		// v.push_back = Vector_push_back(int);
	return 0;
}