#include <stdio.h>
#include "Queue.h"

int main(int argc, char const *argv[])
{
	Queue(int) q = DEFAULT_INT_QUEUE;
	Object.load(&q);
	
	q.push(1), q.push(2);
	q.pop();
	q.push(4), q.push(5), q.push(6), q.push(7);
	q.pop(), q.pop();

	while (q.size()) {
		printf("%d ", q.front());
		q.pop();
	}
	
    return 0;
}