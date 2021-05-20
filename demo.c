#include <stdio.h>
#include "HashSet.h"
int main(int argc, char const *argv[])
{
	HashSet(int) seen = DEFAULT_INT_HASHSET;
	Object.load(&seen);
	seen.insert(1);
	seen.insert(1);
	seen.insert(2);
	seen.erase(1);
	printf("%d\n", seen.size());



	
    return 0;
}