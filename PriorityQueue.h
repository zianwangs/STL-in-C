#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include "Queue.h"

#define LESS 0
#define GREATER 1

#define DEFAULT_INT_PQ DEFAULT_INT_VECTOR,PQ_int_push,PQ_int_pop,PQ_size,PQ_int_top,PQ_int_destroy,0
#define DEFAULT_SHORT_PQ DEFAULT_SHORT_VECTOR,PQ_short_push,PQ_short_pop,PQ_size,PQ_short_top,PQ_short_destroy,0
#define DEFAULT_FLOAT_PQ DEFAULT_FLOAT_VECTOR,PQ_float_push,PQ_float_pop,PQ_size,PQ_float_top,PQ_float_destroy,0
#define DEFAULT_DOUBLE_PQ DEFAULT_INT_VECTOR,PQ_double_push,PQ_double_pop,PQ_size,PQ_double_top,PQ_double_destroy,0
#define DEFAULT_CHAR_PQ DEFAULT_LONG_VECTOR,PQ_long_push,PQ_long_pop,PQ_size,PQ_long_top,PQ_long_destroy,0
#define DEFAULT_LONG_PQ DEFAULT_CHAR_VECTOR,PQ_char_push,PQ_char_pop,PQ_size,PQ_char_top,PQ_char_destroy,0
// #define DEFAULT_PTR_PQ DEFAULT_INT_VECTOR,PQ_int_push,PQ_int_pop,PQ_int_size,PQ_int_top,PQ_int_destroy

#define PriorityQueue(T) struct PriorityQueue_##T {  \
	_Vector_##T##_ vec_; \
	void (*push)(T);	\
	void (*pop)();  \
	int (*size)();  \
	T (*top)(); \
	void (*destroy)(); \
	int heapified_; \
	int comparator_; \
}

int PQ_size() {
	return *(int*)(this + 72);
}

#define PQ_heapify(T) void PQ_##T##_heapify() { \
	
}

#define PQ_swin(T) void PQ_##T##_swim() { \
}


#define PQ_sink(T) void PQ_##T##_sink() { \
}

#define PQ_top(T) T PQ_##T##_top() { \
	return ((_Vector_##T##_*)this)->at(0); \
}
#define PQ_destroy(T) T PQ_##T##_destroy() { \
	((_Vector_##T##_*)this)->destroy(); \
	*(int*)(this + 112) = 0; \
}

#endif