#ifndef _HASHSET_H_ 
#define _HASHSET_H_

#include "Node.h"
#include "helper.h"

#define DEFAULT_INT_HASHSET {0, 0, NULL, HashSet_int_contains, HashSet_int_insert, \
HashSet_int_erase, HashSet_size, HashSet_int_destroy}
#define DEFAULT_LONG_HASHSET {0, 0, NULL, HashSet_long_contains, HashSet_long_insert, \
HashSet_long_erase, HashSet_size, HashSet_long_destroy}
#define DEFAULT_STRING_HASHSET {0, 0, NULL, HashSet_String_contains, HashSet_String_insert, \
HashSet_String_erase, HashSet_size, HashSet_String_destroy}
#define DEFAULT_PTR_HASHSET {0, 0, NULL, HashSet_ptr_contains, HashSet_ptr_insert, \
HashSet_ptr_erase, HashSet_size, HashSet_ptr_destroy}


#define HashSet(T) struct HashSet_##T {  \
	int size_;  \
	int max_;  \
	Node_##T ** data_;  \
	int (*contains)(T);	\
	void (*insert)(T);  \
	void (*erase)(T); \
	int (*size)();  \
	void (*destroy)(); \
}

int HashSet_size() {
	return *(int*)this;
}

#define HashSet_insert(T) void HashSet_##T##_insert(T val) {  \
	int * size_ptr = this; \
	int * max_ptr = this + 4; \
	void ** data_ptr = this + 8; \
	Node_##T ** data = *(data_ptr); \
	if (*size_ptr == *max_ptr / 4 * 3) { \
		int max = *max_ptr; \
		int new_max = 2 * max > 16 ? 2 * max : 16; \
		Node_##T ** new_data = malloc(new_max * sizeof(ptr)); \
		for (int i = 0; i < new_max; ++i) \
			new_data[i] = NULL; \
		if (data != NULL) { \
			for (int i = 0; i < max; ++i) { \
				Node_##T * head = data[i]; \
				while (head) { \
					Node_##T * next = head->next; \
					int bucket = hash_##T(head->value) & (new_max - 1); \
					if (data[bucket] == NULL) { \
						data[bucket] = head; \
						head->pre = NULL; \
						head->next = NULL; \
					} else { \
						head->next = data[bucket]; \
						head->pre = NULL; \
						data[bucket]->pre = head; \
						data[bucket] = head; \
					} \
					head = next; \
				} \
			} \
			free(data); \
		} \
		*data_ptr = new_data; \
		data = new_data; \
		*max_ptr = new_max; \
	} \
	int bucket = hash_##T(val) & (*max_ptr - 1); \
	Node_##T * head = data[bucket]; \
	while (head) { \
		if (equals_##T(head->value, val)) return; \
		head = head->next; \
	} \
	Node_##T * node = malloc(sizeof(Node_##T)); \
	node->pre = NULL; \
	node->value = val; \
	if (data[bucket] == NULL) { \
		data[bucket] = node; \
		node->next = NULL; \
	} else { \
		node->next = data[bucket]; \
		data[bucket]->pre = node; \
		data[bucket] = node; \
	} \
	++(*size_ptr); \
}

#define HashSet_contains(T) int HashSet_##T##_contains(T val) { \
	int mask = *(int*)(this + 4) - 1; \
	Node_##T ** data = *(void**)(this + 8); \
	int flag = 0; \
	if (data == NULL) \
		return 0; \
	int bucket = hash_##T(val) & mask; \
	Node_##T * head = data[bucket]; \
	while (head != NULL) { \
		if (equals_##T(head->value, val)) { \
			flag = 1; \
			break; \
		} \
		head = head->next; \
	} \
	return flag; \
}

#define HashSet_erase(T) void HashSet_##T##_erase(T val) { \
	int mask = *(int*)(this + 4) - 1; \
	Node_##T ** data = *(void**)(this + 8); \
	if (data == NULL) \
		return; \
	int bucket = hash_##T(val) & mask; \
	Node_##T * head = data[bucket]; \
	while (head != NULL) { \
		if (equals_##T(head->value, val)) { \
			if (head->pre == NULL) { \
				data[bucket] = head->next; \
			} else if (head->next == NULL) { \
				head->pre->next = NULL; \
			} else { \
				head->pre->next = head->next; \
				head->next->pre = head->pre; \
			} \
			free(head); \
			--(*(int*)this); \
			break; \
		} \
		head = head->next; \
	} \
	return; \
}


#define HashSet_destroy(T) void HashSet_##T##_destroy() { \
	int * size_ptr = this; \
	int * max_ptr = this + 4; \
	void ** data_ptr = this + 8; \
	Node_##T ** data = *(data_ptr); \
	int max = *max_ptr; \
	for (int i = 0; i < max; ++i) { \
		Node_##T * head = data[i]; \
		while (head) { \
			Node_##T * next = head->next; \
			free(head); \
			head = next; \
		} \
	} \
	free(data); \
	*data_ptr = NULL; \
	*max_ptr = *size_ptr = 0; \
}



void HashSet_String_erase(String s) {
	void * cur_this = this;
	int mask = *(int*)(this + 4) - 1;
	Node_String ** data = *(void**)(this + 8);
	if (data == NULL)
		return;
	int bucket = hash_String(s) & mask;
	Node_String * head = data[bucket];
	while (head != NULL) {
		if (equals_String(head->value, s)) {
			if (head->pre == NULL) {
				data[bucket] = head->next; 
			} else if (head->next == NULL) {
				head->pre->next = NULL;
			} else {
				head->pre->next = head->next;
				head->next->pre = head->pre;
			}
			Object.load(&head->value);
			head->value.destroy();
			this = cur_this;
			free(head);
			--(*(int*)this);
			break;
		}
		head = head->next;
	}
	return;
}

void HashSet_String_destroy()  {
	void * cur_this = this;
	int * size_ptr = this;
	int * max_ptr = this + 4;
	void ** data_ptr = this + 8;
	Node_String ** data = *(data_ptr);
	int max = *max_ptr;
	for (int i = 0; i < max; ++i) {
		Node_String * head = data[i];
		while (head) {
			Node_String * next = head->next;
			Object.load(&head->value);
			head->value.destroy();
			free(head);
			head = next;
		}
	}
	free(data);
	*data_ptr = NULL;
	*max_ptr = *size_ptr = 0;
	this = cur_this;
}

HashSet_contains(int);
HashSet_contains(long);
HashSet_contains(ptr);
HashSet_insert(int);
HashSet_insert(long);
HashSet_insert(ptr);
HashSet_erase(int);
HashSet_erase(long);
HashSet_erase(ptr);
HashSet_destroy(int);
HashSet_destroy(long);
HashSet_destroy(ptr);

#endif