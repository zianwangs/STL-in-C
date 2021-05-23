#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include "Queue.h"

#define LESS 0
#define GREATER 1

#define DEFAULT_INT_PQ DEFAULT_INT_VECTOR,PQ_int_push,PQ_int_pop,PQ_size,PQ_int_top,PQ_int_destroy
#define DEFAULT_SHORT_PQ DEFAULT_SHORT_VECTOR,PQ_short_push,PQ_short_pop,PQ_size,PQ_short_top,PQ_short_destroy
#define DEFAULT_FLOAT_PQ DEFAULT_FLOAT_VECTOR,PQ_float_push,PQ_float_pop,PQ_size,PQ_float_top,PQ_float_destroy
#define DEFAULT_DOUBLE_PQ DEFAULT_INT_VECTOR,PQ_double_push,PQ_double_pop,PQ_size,PQ_double_top,PQ_double_destroy
#define DEFAULT_CHAR_PQ DEFAULT_LONG_VECTOR,PQ_long_push,PQ_long_pop,PQ_size,PQ_long_top,PQ_long_destroy
#define DEFAULT_LONG_PQ DEFAULT_CHAR_VECTOR,PQ_char_push,PQ_char_pop,PQ_size,PQ_char_top,PQ_char_destroy
// #define DEFAULT_PTR_PQ DEFAULT_INT_VECTOR,PQ_int_push,PQ_int_pop,PQ_int_size,PQ_int_top,PQ_int_destroy

#define PriorityQueue(T) struct PriorityQueue_##T {  \
	_Vector_##T##_ vec_; \
	void (*push)(T);	\
	void (*pop)();  \
	int (*size)();  \
	T (*top)(); \
	void (*destroy)(); \
	int comparator_; \
}

int PQ_size() {
	return *(int*)this;
}

#define PQ_push(T) void PQ_##T##_push(T val) { \
	_Vector_##T##_ * vec_ptr = this; \
	vec_ptr->push_back(val); \
	int i = *(int*)this - 1; \
	int min_heap = *(int*)(this + 112); \
	while ((i - 1) / 2 >= 0) { \
		int j = (i - 1) / 2; \
		if (min_heap && vec_ptr->at(i) < vec_ptr->at(j) || !min_heap && vec_ptr->at(i) > vec_ptr->at(j)) { \
			T temp = vec_ptr->at(i); \
			vec_ptr->set(i, vec_ptr->at(j)); \
			vec_ptr->set(j, temp); \
			i = j; \
		} else { \
			break; \
		} \
	} \
}

#define PQ_pop(T) void PQ_##T##_pop() { \
	_Vector_##T##_ * vec_ptr = this; \
	int last = *(int*)this - 1; \
	T temp = vec_ptr->at(0); \
	vec_ptr->set(0, vec_ptr->at(last)); \
	vec_ptr->set(last, temp); \
	vec_ptr->pop_back(); \
	int min_heap = *(int*)(this + 112); \
	int i = 0; \
	while (2 * i + 1 < last) { \
		int j = 2 * i + 1; \
		int k = j + 1 < last ? j + 1 : j; \
		if (min_heap) { \
			if (vec_ptr->at(k) < vec_ptr->at(j)) \
				j = k; \
			if (vec_ptr->at(i) > vec_ptr->at(j)) { \
				T temp = vec_ptr->at(i); \
				vec_ptr->set(i, vec_ptr->at(j)); \
				vec_ptr->set(j, temp); \
				i = j; \
			} else { \
				break; \
			} \
		} else { \
			if (vec_ptr->at(k) > vec_ptr->at(j)) \
				j = k; \
			if (vec_ptr->at(i) > vec_ptr->at(j)) { \
				T temp = vec_ptr->at(i); \
				vec_ptr->set(i, vec_ptr->at(j)); \
				vec_ptr->set(j, temp); \
				i = j; \
			} else { \
				break; \
			} \
		} \
	} \
}


#define PQ_top(T) T PQ_##T##_top() { \
	return ((_Vector_##T##_*)this)->at(0); \
}
#define PQ_destroy(T) void PQ_##T##_destroy() { \
	((_Vector_##T##_*)this)->destroy(); \
	*(int*)(this + 112) = 0; \
}

PQ_push(int);
PQ_push(long);
PQ_push(char);
PQ_push(short);
PQ_push(float);
PQ_push(double);
PQ_pop(int);
PQ_pop(long);
PQ_pop(char);
PQ_pop(short);
PQ_pop(float);
PQ_pop(double);
PQ_top(int);
PQ_top(long);
PQ_top(short);
PQ_top(char);
PQ_top(float);
PQ_top(double);
PQ_destroy(int);
PQ_destroy(long);
PQ_destroy(float);
PQ_destroy(double);
PQ_destroy(char);
PQ_destroy(short);

#endif