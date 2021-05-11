#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Vector.h"

int main(int argc, char const *argv[])
{
	Vector(int) vec = DEFAULT_INT_VECTOR;
	Object.load(&vec);
	for (int i = 0; i < 30; ++i) {
		vec.push_back(i);
		printf("%d ", vec.back());
	}
	for (int i = 7; i < 15; ++i) {
		printf("%d \n", vec.at(i));
	}


		// v.push_back = Vector_push_back(int);
	return 0;
}