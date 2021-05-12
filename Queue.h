#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Object.h"
#include "Vector.h"

/* implement queue using two stacks :) */

#define DEFAULT_CHAR_QUEUE {DEFAULT_CHAR_VECTOR, DEFAULT_CHAR_VECTOR, \
Queue_char_push, Queue_char_pop, Queue_size, Queue_char_front, Queue_char_destroy}
#define DEFAULT_SHORT_QUEUE {DEFAULT_SHORT_VECTOR, DEFAULT_SHORT_VECTOR, \
Queue_short_push, Queue_short_pop, Queue_size, Queue_short_front, Queue_short_destroy}
#define DEFAULT_INT_QUEUE {DEFAULT_INT_VECTOR, DEFAULT_INT_VECTOR, \
Queue_int_push, Queue_int_pop, Queue_size, Queue_int_front, Queue_int_destroy}
#define DEFAULT_LONG_QUEUE {DEFAULT_LONG_VECTOR, DEFAULT_LONG_VECTOR, \
Queue_long_push, Queue_long_pop, Queue_size, Queue_long_front, Queue_long_destroy}
#define DEFAULT_FLOAT_QUEUE {DEFAULT_FLOAT_VECTOR, DEFAULT_FLOAT_VECTOR, \
Queue_float_push, Queue_float_pop, Queue_size, Queue_float_front, Queue_float_destroy}
#define DEFAULT_DOUBLE_QUEUE {DEFAULT_DOUBLE_VECTOR, DEFAULT_DOUBLE_VECTOR, \
Queue_double_push, Queue_double_pop, Queue_size, Queue_double_front, Queue_double_destroy}
#define DEFAULT_PTR_QUEUE {DEFAULT_PTR_VECTOR, DEFAULT_PTR_VECTOR, \
Queue_ptr_push, Queue_ptr_pop, Queue_size, Queue_ptr_front, Queue_ptr_destroy}
typedef Vector(_char_)    _Vector_char_;
typedef Vector(_short_)   _Vector_short_;
typedef Vector(_int_)     _Vector_int_;
typedef Vector(_long_)    _Vector_long_;
typedef Vector(_float_)   _Vector_float_;
typedef Vector(_double_)  _Vector_double_;
typedef Vector(_ptr_)     _Vector_ptr_;

#define Queue(T) struct Queue_##T {  \
	_Vector_##T##_ stack_in_; \
	_Vector_##T##_ stack_out_; \
	void (*push)(T);	\
	void (*pop)();  \
	int (*size)();  \
	T (*front)(); \
	void (*destroy)(); \
}

#define Queue_push(T) void Queue_##T##_push(T val) { \
	_Vector_##T##_ * stack_in_ptr = this; \
	stack_in_ptr->push_back(val); \
}

#define Queue_pop(T) void Queue_##T##_pop() { \
	_Vector_##T##_ * stack_in_ptr = this; \
	_Vector_##T##_ * stack_out_ptr = this + 72; \
	Object.load(stack_out_ptr); \
	if (stack_out_ptr->size() == 0) { \
		Object.load(stack_in_ptr); \
		while (stack_in_ptr->size()) { \
			T back = stack_in_ptr->back(); \
			stack_in_ptr->pop_back(); \
			Object.load(stack_out_ptr); \
			stack_out_ptr->push_back(back); \
			Object.load(stack_in_ptr); \
		} \
	} \
	Object.load(stack_out_ptr); \
	stack_out_ptr->pop_back(); \
	Object.load(stack_in_ptr); \
}

int Queue_size() {
	int * stack_in_size_ptr = this;
	int * stack_out_size_ptr = this + 72;
	return *stack_in_size_ptr + *stack_out_size_ptr;
}

#define Queue_front(T) T Queue_##T##_front() { \
	_Vector_##T##_ * stack_in_ptr = this; \
	_Vector_##T##_ * stack_out_ptr = this + 72; \
	T val; \
	Object.load(stack_out_ptr); \
	if (stack_out_ptr->size() == 0) { \
		Object.load(stack_in_ptr); \
		while (stack_in_ptr->size()) { \
			T back = stack_in_ptr->back(); \
			stack_in_ptr->pop_back(); \
			Object.load(stack_out_ptr); \
			stack_out_ptr->push_back(back); \
			Object.load(stack_in_ptr); \
		} \
	} \
	Object.load(stack_out_ptr); \
	val = stack_out_ptr->back(); \
	Object.load(stack_in_ptr); \
	return val; \
}

#define Queue_destroy(T) void Queue_##T##_destroy() { \
	_Vector_##T##_ * stack_in_ptr = this; \
	stack_in_ptr->destroy(); \
	_Vector_##T##_ * stack_out_ptr = this + 72; \
	Object.load(stack_out_ptr); \
	stack_out_ptr->destroy(); \
}

Queue_push(char);
Queue_push(short);
Queue_push(int);
Queue_push(long);
Queue_push(float);
Queue_push(double);
Queue_push(ptr);
Queue_pop(char);
Queue_pop(short);
Queue_pop(int);
Queue_pop(long);
Queue_pop(float);
Queue_pop(double);
Queue_pop(ptr);
Queue_front(char);
Queue_front(short);
Queue_front(int);
Queue_front(long);
Queue_front(float);
Queue_front(double);
Queue_front(ptr);
Queue_destroy(char);
Queue_destroy(short);
Queue_destroy(int);
Queue_destroy(long);
Queue_destroy(float);
Queue_destroy(double);
Queue_destroy(ptr);

#endif