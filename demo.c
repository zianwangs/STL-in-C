#include <stdio.h>

#include "Deque.h"
int main()
{
	Deque(int) q = DEFAULT_INT_DEQUE;
	Object.load(&q);
	for (int i = 0; i < 6; ++i)
		q.push_front(i);
	while (q.size()) {
		printf("%d %d\n", q.front(), q.back());
		q.pop_front();
		q.pop_back();
	}
	
    return 0;
}