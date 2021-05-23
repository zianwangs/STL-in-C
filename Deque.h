#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "Node.h"

#define DEFAULT_INT_DEQUE {0, 0, NULL, Deque_int_push_front, Deque_int_pop_front, Deque_int_push_back, \
Deque_int_pop_back, Deque_size, Deque_int_front, Deque_int_back, Deque_int_destroy}
#define DEFAULT_LONG_DEQUE {0, 0, NULL, Deque_long_push_front, Deque_long_pop_front, Deque_long_push_back, \
Deque_long_pop_back, Deque_size, Deque_long_front, Deque_long_back, Deque_long_destroy}
#define DEFAULT_FLOAT_DEQUE {0, 0, NULL, Deque_float_push_front, Deque_float_pop_front, Deque_float_push_back, \
Deque_float_pop_back, Deque_size, Deque_float_front, Deque_float_back, Deque_float_destroy}
#define DEFAULT_DOUBLE_DEQUE {0, 0, NULL, Deque_double_push_front, Deque_double_pop_front, Deque_double_push_back, \
Deque_double_pop_back, Deque_size, Deque_double_front, Deque_double_back, Deque_double_destroy}
#define DEFAULT_CHAR_DEQUE {0, 0, NULL, Deque_char_push_front, Deque_char_pop_front, Deque_char_push_back, \
Deque_char_pop_back, Deque_size, Deque_char_front, Deque_char_back, Deque_char_destroy}
#define DEFAULT_SHORT_DEQUE {0, 0, NULL, Deque_short_push_front, Deque_short_pop_front, Deque_short_push_back, \
Deque_short_pop_back, Deque_size, Deque_short_front, Deque_short_back, Deque_short_destroy}
#define DEFAULT_PTR_DEQUE {0, 0, NULL, Deque_ptr_push_front, Deque_ptr_pop_front, Deque_ptr_push_back, \
Deque_ptr_pop_back, Deque_size, Deque_ptr_front, Deque_ptr_back, Deque_ptr_destroy}

#define Deque(T) struct Deque_##T {  \
	int size_; \
	int _padding_; \
	Node_##T * sentinel; \
	void (*push_front)(T);	\
	void (*pop_front)();  \
	void (*push_back)(T);	\
	void (*pop_back)();  \
	int (*size)();  \
	T (*front)(); \
	T (*back)(); \
	void (*destroy)(); \
}

int Deque_size() {
	return *(int*)this;
}

#define Deque_push_front(T) void Deque_##T##_push_front(T val) { \
	Node_##T ** sentinel_ptr = this + 8; \
	Node_##T * sentinel = *sentinel_ptr; \
	if (sentinel == NULL) { \
		sentinel = malloc(sizeof(Node_##T)); \
		sentinel->value = 0; \
		Node_connect(sentinel, sentinel); \
		*sentinel_ptr = sentinel; \
	} \
	Node_##T * cur = malloc(sizeof(Node_##T)); \
	cur->value = val; \
	Node_##T * front = sentinel->next; \
	Node_connect(sentinel, cur); \
	Node_connect(cur, front); \
	++*(int*)this; \
}

#define Deque_push_back(T) void Deque_##T##_push_back(T val) { \
	Node_##T ** sentinel_ptr = this + 8; \
	Node_##T * sentinel = *sentinel_ptr; \
	if (sentinel == NULL) { \
		sentinel = malloc(sizeof(Node_##T)); \
		sentinel->value = 0; \
		Node_connect(sentinel, sentinel); \
		*sentinel_ptr = sentinel; \
	} \
	Node_##T * cur = malloc(sizeof(Node_##T)); \
	cur->value = val; \
	Node_##T * back = sentinel->pre; \
	Node_connect(back, cur); \
	Node_connect(cur, sentinel); \
	++*(int*)this; \
}

#define Deque_pop_front(T) void Deque_##T##_pop_front() { \
	if (*(int*)this == 0) \
		return; \
	Node_##T ** sentinel_ptr = this + 8; \
	Node_##T * sentinel = *sentinel_ptr; \
	Node_##T * front = sentinel->next; \
	Node_connect(sentinel, front->next); \
	free(front); \
	--*(int*)this; \
}

#define Deque_pop_back(T) void Deque_##T##_pop_back() { \
	if (*(int*)this == 0) \
		return; \
	Node_##T ** sentinel_ptr = this + 8; \
	Node_##T * sentinel = *sentinel_ptr; \
	Node_##T * back = sentinel->pre; \
	Node_connect(back->pre, sentinel); \
	free(back); \
	--*(int*)this; \
}

#define Deque_front(T) T Deque_##T##_front() { \
	return (*(Node_##T**)(this + 8))->next->value; \
}

#define Deque_back(T) T Deque_##T##_back() { \
	return (*(Node_##T**)(this + 8))->pre->value; \
}

#define Deque_destroy(T) void Deque_##T##_destroy() { \
	Node_##T ** sentinel_ptr = this + 8; \
	Node_##T * sentinel = *sentinel_ptr; \
	if (sentinel == NULL) \
		return; \
	Node_##T * head = sentinel->next; \
	while (head != sentinel) { \
		Node_##T * next = head->next; \
		free(head); \
		head = next; \
	} \
	free(sentinel); \
	*(int*)this = 0; \
	*sentinel_ptr = 0; \
}

Deque_push_front(int);
Deque_push_front(long);
Deque_push_front(char);
Deque_push_front(short);
Deque_push_front(float);
Deque_push_front(double);
Deque_push_front(ptr);
Deque_push_back(int);
Deque_push_back(long);
Deque_push_back(float);
Deque_push_back(double);
Deque_push_back(char);
Deque_push_back(short);
Deque_push_back(ptr);
Deque_pop_front(int);
Deque_pop_front(long);
Deque_pop_front(float);
Deque_pop_front(double);
Deque_pop_front(char);
Deque_pop_front(short);
Deque_pop_front(ptr);
Deque_pop_back(int);
Deque_pop_back(long);
Deque_pop_back(float);
Deque_pop_back(double);
Deque_pop_back(char);
Deque_pop_back(short);
Deque_pop_back(ptr);
Deque_front(int);
Deque_front(long);
Deque_front(float);
Deque_front(double);
Deque_front(char);
Deque_front(short);
Deque_front(ptr);
Deque_back(int);
Deque_back(long);
Deque_back(float);
Deque_back(double);
Deque_back(char);
Deque_back(short);
Deque_back(ptr);
Deque_destroy(int);
Deque_destroy(long);
Deque_destroy(float);
Deque_destroy(double);
Deque_destroy(char);
Deque_destroy(short);
Deque_destroy(ptr);

#endif