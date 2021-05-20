#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include "Object.h"
#include "Vector.h"

#define DEFAULT_STRING {DEFAULT_CHAR_VECTOR, String_size, String_at, String_push_back, String_pop_back, \
String_concat, String_append, String_c_str, String_destroy, String_set, String_copy}

typedef struct String String;
typedef Vector(_char_) _basic_string_;
struct String {
	_basic_string_ vec_;
	int (*size)();
	char (*at)(int);
	void (*push_back)(char);
	void (*pop_back)();
	void (*concat)(char *);
	void (*append)(String);
	char* (*c_str)();
	void (*destroy)();
	void (*set)(int, char);
	String (*copy)();
};

int String_size() {
	return ((_basic_string_*)this)->size();
}

char String_at(int idx) {
	return ((_basic_string_*)this)->at(idx);
}

void String_push_back(char c) {
	return ((_basic_string_*)this)->push_back(c);
}

void String_pop_back() {
	return ((_basic_string_*)this)->pop_back();
}

void String_concat(char * s) {
	_basic_string_ * vec_ptr = this;
	char cur;
	while ((cur = (*s++)))
		vec_ptr->push_back(cur);
}

void String_append(String str) {
	String * _this = this;
	_basic_string_ * vec_ptr = (void*)&str;
	Object.load(vec_ptr);
	char *  s = *(void**)((void*)vec_ptr + 8);
	int size = vec_ptr->size();
	Object.load(_this);
	while (size--)
		_this->push_back(*s++);
}

char* String_c_str() {
	return *(void**)((void*)this + 8);
}

void String_destroy() {
	((_basic_string_*)this)->destroy();
}
	
void String_set(int idx, char c) {
	((_basic_string_*)this)->set(idx, c);
}

String String_copy() {
	String ans = DEFAULT_STRING;
	_basic_string_ * copy = (void*)&ans;
	_basic_string_ * str = this;
	int size = copy->size_ = str->size_;
	int max = copy->max_ = str->max_;
	copy->data_ = malloc(max * sizeof(char));
	for (int i = 0; i < size; ++i)
		copy->data_[i] = str->data_[i];
	return ans;
}

#endif