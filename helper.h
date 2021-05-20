#ifndef _HELPER_H
#define _HELPER_H

#include "Object.h"
#include "String.h"


#define equals(T) int equals_##T(T a, T b) { return a == b; }
#define hash(T) long hash_##T(T a) { return (long)a; }


int equals_String(String a, String b) {
	int size_a = *(int*)&a;
	int size_b = *(int*)&b;
	if (size_a != size_b)
		return 0;
	void * cur_this = this;
	int flag = 1;
	Object.load(&a);
	while (size_a--) {
		char c = a.at(size_a);
		Object.load(&b);
		if (c != b.at(size_a)) {
			flag = 0;
			break;
		}
		Object.load(&a);
	}
	this = cur_this;
	return flag;
}

int hash_String(String s) {
	void * cur_this = this;
	long ans = 0;
	long exp = 1;
	long mask = (1L << 32) - 1;
	Object.load(&s);
	int size = s.size();
	for (int i = 0; i < size; ++i) {
		ans = (ans + s.at(i) * exp) & mask;
		exp = (exp * 31) & mask;
	}
	this = cur_this;
	return ans;
}

equals(int);
equals(long);
equals(ptr);
hash(int);
hash(long);
hash(ptr);

#endif