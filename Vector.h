#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Object.h"

#define DEFAULT_CHAR_VECTOR {0, 0, NULL, Vector_char_at, Vector_char_push_back, Vector_char_pop_back, \
Vector_size, Vector_char_back, Vector_destroy, Vector_char_set}
#define DEFAULT_SHORT_VECTOR {0, 0, NULL, Vector_short_at, Vector_short_push_back, Vector_short_pop_back, \
Vector_size, Vector_short_back, Vector_destroy, Vector_short_set}
#define DEFAULT_INT_VECTOR {0, 0, NULL, Vector_int_at, Vector_int_push_back, Vector_int_pop_back, \
Vector_size, Vector_int_back, Vector_destroy, Vector_int_set}
#define DEFAULT_LONG_VECTOR {0, 0, NULL, Vector_long_at, Vector_long_push_back, Vector_long_pop_back, \
Vector_size, Vector_long_back, Vector_destroy, Vector_long_set}
#define DEFAULT_FLOAT_VECTOR {0, 0, NULL, Vector_float_at, Vector_float_push_back, Vector_float_pop_back, \
Vector_size, Vector_float_back, Vector_destroy, Vector_float_set}
#define DEFAULT_DOUBLE_VECTOR {0, 0, NULL, Vector_double_at, Vector_double_push_back, Vector_double_pop_back, \
Vector_size, Vector_double_back, Vector_destroy, Vector_double_set}
#define DEFAULT_PTR_VECTOR {0, 0, NULL, Vector_ptr_at, Vector_ptr_push_back, Vector_ptr_pop_back, \
Vector_size, Vector_ptr_back, Vector_destroy, Vector_ptr_set}

#define Vector(T) struct Vector_##T {  \
	int size_;  \
	int max_;  \
	T * data_;  \
	T (*at)(int);	\
	void (*push_back)(T);	\
	void (*pop_back)();  \
	int (*size)();  \
	T (*back)(); \
	void (*destroy)(); \
	void (*set)(int, T); \
}

#define Vector_push_back(T) void Vector_##T##_push_back(T val) { \
 	int * size_ptr = this; \
	int * max_ptr = this + 4; \
	void ** data_ptr = this + 8; \
	T * data = *data_ptr; \
	if (*size_ptr == *max_ptr) { \
		int max_val = *max_ptr; \
		int new_max = 2 * max_val > 16 ? 2 * max_val : 16; \
		T * new_data = malloc(new_max * sizeof(T));\
		memcpy(new_data, data, max_val * sizeof(T)); \
		*max_ptr = new_max; \
		free(data); \
		*data_ptr = new_data; \
		data = *data_ptr; \
	} \
	data[(*size_ptr)++] = val;\
};

#define Vector_back(T) T Vector_##T##_back() { \
	int idx = *(int*)this - 1; \
	T * data = *(void**)(this + 8); \
	return data[idx]; \
};

#define Vector_at(T) T Vector_##T##_at(int idx) { \
	T * data = *(void**)(this + 8);; \
	return data[idx]; \
};

#define Vector_pop_back(T) void Vector_##T##_pop_back() { \
	int * size_ptr = this; \
	int * max_ptr = this + 4; \
	void ** data_ptr = this + 8; \
	T * data = *data_ptr; \
	int size = --*size_ptr; \
	if (size < *max_ptr / 4) { \
		int max_val = *max_ptr; \
		int new_max = max_val / 2; \
		T * new_data = malloc(new_max * sizeof(T));\
		memcpy(new_data, data, size * sizeof(T)); \
		*max_ptr = new_max; \
		free(data); \
		*data_ptr = new_data; \
	} \
	data[size] = 0; \
}

int Vector_size() {
	int * size_ptr = this;
	return *size_ptr;
}

void Vector_destroy() {
	void * data = *(void**)(this + 8);
	free(data);
	int * size_ptr = this;
	int * max_ptr = this + 4;
	*size_ptr = 0;
	*max_ptr = 0;
}

#define Vector_set(T) void Vector_##T##_set(int idx, T val) { \
	T * data = *(void**)(this + 8); \
	data[idx] = val; \
}

Vector_push_back(char);
Vector_push_back(short);
Vector_push_back(int);
Vector_push_back(long);
Vector_push_back(float);
Vector_push_back(double);
Vector_push_back(ptr);
Vector_back(char);
Vector_back(short);
Vector_back(int);
Vector_back(long);
Vector_back(float);
Vector_back(double);
Vector_back(ptr);
Vector_at(char);
Vector_at(short);
Vector_at(int);
Vector_at(long);
Vector_at(float);
Vector_at(double);
Vector_at(ptr);
Vector_pop_back(char);
Vector_pop_back(short);
Vector_pop_back(int);
Vector_pop_back(long);
Vector_pop_back(float);
Vector_pop_back(double);
Vector_pop_back(ptr);
Vector_set(char);
Vector_set(short);
Vector_set(int);
Vector_set(long);
Vector_set(float);
Vector_set(double);
Vector_set(ptr);


#endif