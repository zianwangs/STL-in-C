#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "Node.h"
#include "helper.h"

#define DEFAULT_INT_INT_HASHMAP {0, 0, NULL, HashMap_int_int_containsKey, HashMap_int_int_emplace, \
HashMap_int_int_erase, HashMap_size, HashMap_int_int_destroy, HashMap_int_int_get}
#define DEFAULT_INT_LONG_HASHMAP {0, 0, NULL, HashMap_int_long_containsKey, HashMap_int_long_emplace, \
HashMap_int_long_erase, HashMap_size, HashMap_int_long_destroy, HashMap_int_long_get}
#define DEFAULT_INT_STRING_HASHMAP {0, 0, NULL, HashMap_int_String_containsKey, HashMap_int_String_emplace, \
HashMap_int_String_erase, HashMap_size, HashMap_int_String_destroy, HashMap_int_String_get}
#define DEFAULT_INT_PTR_HASHMAP {0, 0, NULL, HashMap_int_ptr_containsKey, HashMap_int_ptr_emplace, \
HashMap_int_ptr_erase, HashMap_size, HashMap_int_ptr_destroy, HashMap_int_ptr_get}
#define DEFAULT_LONG_INT_HASHMAP {0, 0, NULL, HashMap_long_int_containsKey, HashMap_long_int_emplace, \
HashMap_long_int_erase, HashMap_size, HashMap_long_int_destroy, HashMap_long_int_get}
#define DEFAULT_LONG_LONG_HASHMAP {0, 0, NULL, HashMap_long_long_containsKey, HashMap_long_long_emplace, \
HashMap_long_long_erase, HashMap_size, HashMap_long_long_destroy, HashMap_long_long_get}
#define DEFAULT_LONG_PTR_HASHMAP {0, 0, NULL, HashMap_long_ptr_containsKey, HashMap_long_ptr_emplace, \
HashMap_long_ptr_erase, HashMap_size, HashMap_long_ptr_destroy, HashMap_long_ptr_get}
#define DEFAULT_LONG_STRING_HASHMAP {0, 0, NULL, HashMap_long_String_containsKey, HashMap_long_String_emplace, \
HashMap_long_String_erase, HashMap_size, HashMap_long_String_destroy, HashMap_long_String_get}
#define DEFAULT_STRING_INT_HASHMAP {0, 0, NULL, HashMap_String_int_containsKey, HashMap_String_int_emplace, \
HashMap_String_int_erase, HashMap_size, HashMap_String_int_destroy, HashMap_String_int_get}
#define DEFAULT_STRING_LONG_HASHMAP {0, 0, NULL, HashMap_String_long_containsKey, HashMap_String_long_emplace, \
HashMap_String_long_erase, HashMap_size, HashMap_String_long_destroy, HashMap_String_long_get}
#define DEFAULT_STRING_PTR_HASHMAP {0, 0, NULL, HashMap_String_ptr_containsKey, HashMap_String_ptr_emplace, \
HashMap_String_ptr_erase, HashMap_size, HashMap_String_ptr_destroy, HashMap_String_ptr_get}
#define DEFAULT_STRING_STRING_HASHMAP {0, 0, NULL, HashMap_String_String_containsKey, HashMap_String_String_emplace, \
HashMap_String_String_erase, HashMap_size, HashMap_String_String_destroy, HashMap_String_String_get}
#define DEFAULT_PTR_INT_HASHMAP {0, 0, NULL, HashMap_ptr_int_containsKey, HashMap_ptr_int_emplace, \
HashMap_ptr_int_erase, HashMap_size, HashMap_ptr_int_destroy, HashMap_ptr_int_get}
#define DEFAULT_PTR_LONG_HASHMAP {0, 0, NULL, HashMap_ptr_long_containsKey, HashMap_ptr_long_emplace, \
HashMap_ptr_long_erase, HashMap_size, HashMap_ptr_long_destroy, HashMap_ptr_long_get}
#define DEFAULT_PTR_STRING_HASHMAP {0, 0, NULL, HashMap_ptr_String_containsKey, HashMap_ptr_String_emplace, \
HashMap_ptr_String_erase, HashMap_size, HashMap_ptr_String_destroy, HashMap_ptr_String_get}
#define DEFAULT_PTR_PTR_HASHMAP {0, 0, NULL, HashMap_ptr_ptr_containsKey, HashMap_ptr_ptr_emplace, \
HashMap_ptr_ptr_erase, HashMap_size, HashMap_ptr_ptr_destroy, HashMap_ptr_ptr_get}


#define HashMap(K,V) struct HashMap_##K##_##V {  \
	int size_;  \
	int max_;  \
	Node_##K##_##V ** data_;  \
	int (*containsKey)(K);	\
	void (*emplace)(K,V);  \
	void (*erase)(K); \
	int (*size)();  \
	void (*destroy)(); \
	V (*get)(K); \
}

int HashMap_size() {
	return *(int*)this;
}

#define HashMap_emplace(K,V) void HashMap_##K##_##V##_emplace(K key, V val) {  \
	int * size_ptr = this; \
	int * max_ptr = this + 4; \
	void ** data_ptr = this + 8; \
	Node_##K##_##V ** data = *(data_ptr); \
	if (*size_ptr == *max_ptr / 4 * 3) { \
		int max = *max_ptr; \
		int new_max = 2 * max > 16 ? 2 * max : 16; \
		Node_##K##_##V ** new_data = malloc(new_max * sizeof(ptr)); \
		for (int i = 0; i < new_max; ++i) \
			new_data[i] = NULL; \
		if (data != NULL) { \
			for (int i = 0; i < max; ++i) { \
				Node_##K##_##V * head = data[i]; \
				while (head) { \
					Node_##K##_##V * next = head->next; \
					int bucket = hash_##K(head->key) & (new_max - 1); \
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
	int bucket = hash_##K(key) & (*max_ptr - 1); \
	Node_##K##_##V * head = data[bucket]; \
	while (head) { \
		if (equals_##K(head->key, key)) { \
			head->value = val; \
			return; \
		} \
		head = head->next; \
	} \
	Node_##K##_##V * node = malloc(sizeof(Node_##K##_##V)); \
	node->pre = NULL; \
	node->key = key;  \
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

#define HashMap_containsKey(K,V) int HashMap_##K##_##V##_containsKey(K key) { \
	int mask = *(int*)(this + 4) - 1; \
	Node_##K##_##V ** data = *(void**)(this + 8); \
	int flag = 0; \
	if (data == NULL) \
		return 0; \
	int bucket = hash_##K(key) & mask; \
	Node_##K##_##V * head = data[bucket]; \
	while (head != NULL) { \
		if (equals_##K(head->key, key)) { \
			flag = 1; \
			break; \
		} \
		head = head->next; \
	} \
	return flag; \
}

#define HashMap_get(K,V) V HashMap_##K##_##V##_get(K key) { \
	int mask = *(int*)(this + 4) - 1; \
	Node_##K##_##V ** data = *(void**)(this + 8); \
	int flag = 0; \
	if (data == NULL) \
		return (V){0}; \
	int bucket = hash_##K(key) & mask; \
	Node_##K##_##V * head = data[bucket]; \
	while (head != NULL) { \
		if (equals_##K(head->key, key)) { \
			return head->value; \
		} \
		head = head->next; \
	} \
	return (V){0}; \
}

#define HashMap_erase(K,V) void HashMap_##K##_##V##_erase(K key) { \
	int mask = *(int*)(this + 4) - 1; \
	Node_##K##_##V ** data = *(void**)(this + 8); \
	if (data == NULL) \
		return; \
	int bucket = hash_##K(key) & mask; \
	Node_##K##_##V * head = data[bucket]; \
	while (head != NULL) { \
		if (equals_##K(head->key, key)) { \
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


#define HashMap_destroy(K,V) void HashMap_##K##_##V##_destroy() { \
	int * size_ptr = this; \
	int * max_ptr = this + 4; \
	void ** data_ptr = this + 8; \
	Node_##K##_##V ** data = *(data_ptr); \
	int max = *max_ptr; \
	for (int i = 0; i < max; ++i) { \
		Node_##K##_##V * head = data[i]; \
		while (head) { \
			Node_##K##_##V * next = head->next; \
			free(head); \
			head = next; \
		} \
	} \
	free(data); \
	*data_ptr = NULL; \
	*max_ptr = *size_ptr = 0; \
}

#define HashMap_K_String_erase(K) void HashMap_##K##_String_erase(K key) { \
	void * cur_this = this; \
	int mask = *(int*)(this + 4) - 1; \
	Node_##K##_String ** data = *(void**)(this + 8); \
	if (data == NULL) \
		return; \
	int bucket = hash_##K(key) & mask; \
	Node_##K##_String * head = data[bucket]; \
	while (head != NULL) { \
		if (equals_##K(head->key, key)) { \
			if (head->pre == NULL) { \
				data[bucket] = head->next; \
			} else if (head->next == NULL) { \
				head->pre->next = NULL; \
			} else { \
				head->pre->next = head->next; \
				head->next->pre = head->pre; \
			} \
			Object.load(&head->value); \
			head->value.destroy(); \
			free(head); \
			this = cur_this; \
			--(*(int*)this); \
			break; \
		} \
		head = head->next; \
	} \
}

#define HashMap_String_V_erase(V) void HashMap_String_##V##_erase(String s) { \
	void * cur_this = this; \
	int mask = *(int*)(this + 4) - 1; \
	Node_String_##V ** data = *(void**)(this + 8); \
	if (data == NULL) \
		return; \
	int bucket = hash_String(s) & mask; \
	Node_String_##V * head = data[bucket]; \
	while (head != NULL) { \
		if (equals_String(head->key, s)) { \
			if (head->pre == NULL) { \
				data[bucket] = head->next; \
			} else if (head->next == NULL) { \
				head->pre->next = NULL; \
			} else { \
				head->pre->next = head->next; \
				head->next->pre = head->pre; \
			} \
			Object.load(&head->key); \
			head->key.destroy(); \
			free(head); \
			this = cur_this; \
			--(*(int*)this); \
			break; \
		} \
		head = head->next; \
	} \
}

#define HashMap_K_String_destroy(K) void HashMap_##K##_String_destroy() { \
	void * cur_this = this; \
	int * size_ptr = this; \
	int * max_ptr = this + 4; \
	void ** data_ptr = this + 8; \
	Node_##K##_String ** data = *(data_ptr); \
	int max = *max_ptr; \
	for (int i = 0; i < max; ++i) { \
		Node_##K##_String * head = data[i]; \
		while (head) { \
			Node_##K##_String * next = head->next; \
			Object.load(&head->value); \
			head->value.destroy(); \
			free(head); \
			head = next; \
		} \
	} \
	free(data); \
	*data_ptr = NULL; \
	*max_ptr = *size_ptr = 0; \
	this = cur_this; \
}

#define HashMap_String_V_destroy(V) void HashMap_String_##V##_destroy() { \
	void * cur_this = this; \
	int * size_ptr = this; \
	int * max_ptr = this + 4; \
	void ** data_ptr = this + 8; \
	Node_String_##V ** data = *(data_ptr); \
	int max = *max_ptr; \
	for (int i = 0; i < max; ++i) { \
		Node_String_##V * head = data[i]; \
		while (head) { \
			Node_String_##V * next = head->next; \
			Object.load(&head->key); \
			head->key.destroy(); \
			free(head); \
			head = next; \
		} \
	} \
	free(data); \
	*data_ptr = NULL; \
	*max_ptr = *size_ptr = 0; \
	this = cur_this; \
}


void HashMap_String_String_erase(String s) {
	void * cur_this = this;
	int mask = *(int*)(this + 4) - 1;
	Node_String_String ** data = *(void**)(this + 8);
	if (data == NULL)
		return;
	int bucket = hash_String(s) & mask;
	Node_String_String * head = data[bucket];
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
			Object.load(&head->key);
			head->key.destroy();
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

void HashMap_String_String_destroy()  {
	void * cur_this = this;
	int * size_ptr = this;
	int * max_ptr = this + 4;
	void ** data_ptr = this + 8;
	Node_String_String ** data = *(data_ptr);
	int max = *max_ptr;
	for (int i = 0; i < max; ++i) {
		Node_String_String * head = data[i];
		while (head) {
			Node_String_String * next = head->next;
			Object.load(&head->key);
			head->key.destroy();
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

HashMap_containsKey(int,int);
HashMap_containsKey(int,long);
HashMap_containsKey(int,ptr);
HashMap_containsKey(int,String);
HashMap_containsKey(long,int);
HashMap_containsKey(long,long);
HashMap_containsKey(long,ptr);
HashMap_containsKey(long,String);
HashMap_containsKey(String,int);
HashMap_containsKey(String,long);
HashMap_containsKey(String,ptr);
HashMap_containsKey(String,String);
HashMap_containsKey(ptr,int);
HashMap_containsKey(ptr,long);
HashMap_containsKey(ptr,ptr);
HashMap_containsKey(ptr,String);

HashMap_emplace(int,int);
HashMap_emplace(int,long);
HashMap_emplace(int,String);
HashMap_emplace(int,ptr);
HashMap_emplace(long,int);
HashMap_emplace(long,long);
HashMap_emplace(long,String);
HashMap_emplace(long,ptr);
HashMap_emplace(String,int);
HashMap_emplace(String,long);
HashMap_emplace(String,String);
HashMap_emplace(String,ptr);
HashMap_emplace(ptr,int);
HashMap_emplace(ptr,long);
HashMap_emplace(ptr,String);
HashMap_emplace(ptr,ptr);

HashMap_get(int,int);
HashMap_get(int,long);
HashMap_get(int,String);
HashMap_get(int,ptr);
HashMap_get(long,int);
HashMap_get(long,long);
HashMap_get(long,String);
HashMap_get(long,ptr);
HashMap_get(String,int);
HashMap_get(String,long);
HashMap_get(String,String);
HashMap_get(String,ptr);
HashMap_get(ptr,int);
HashMap_get(ptr,long);
HashMap_get(ptr,String);
HashMap_get(ptr,ptr);


HashMap_erase(int,int);
HashMap_erase(int,long);
HashMap_erase(int,ptr);
HashMap_erase(long,int);
HashMap_erase(long,long);
HashMap_erase(long,ptr);
HashMap_erase(ptr,int);
HashMap_erase(ptr,long);
HashMap_erase(ptr,ptr);
HashMap_K_String_erase(int);
HashMap_K_String_erase(long);
HashMap_K_String_erase(ptr);
HashMap_String_V_erase(int);
HashMap_String_V_erase(long);
HashMap_String_V_erase(ptr);

HashMap_destroy(int,int);
HashMap_destroy(int,long);
HashMap_destroy(int,ptr);
HashMap_destroy(long,int);
HashMap_destroy(long,long);
HashMap_destroy(long,ptr);
HashMap_destroy(ptr,int);
HashMap_destroy(ptr,long);
HashMap_destroy(ptr,ptr);
HashMap_K_String_destroy(int);
HashMap_K_String_destroy(long);
HashMap_K_String_destroy(ptr);
HashMap_String_V_destroy(int);
HashMap_String_V_destroy(long);
HashMap_String_V_destroy(ptr);

#endif