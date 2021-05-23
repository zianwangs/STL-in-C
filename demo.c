#include <stdio.h>

#include "PriorityQueue.h"
int main()
{
	PriorityQueue(int) heap = {DEFAULT_INT_PQ, GREATER};
	Object.load(&heap);

	heap.push(1);
	heap.push(1);
	heap.push(10);
	heap.push(6);
	heap.push(5);
	heap.push(0);

	while (heap.size()) {
		printf("%d\n", heap.top());
		heap.pop();
	}
	
    return 0;
}