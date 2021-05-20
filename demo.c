#include <stdio.h>

#include "HashMap.h"
int main(int argc, char const *argv[])
{
	HashMap(int,int) map = DEFAULT_INT_INT_HASHMAP;
	Object.load(&map);
	map.emplace(1, 3);
	map.emplace(1, 4);
	printf("%d\n", map.size()); // stdout: 1
	map.emplace(3, 5);
	map.erase(1);
	map.erase(2);
	map.erase(3);
	printf("%d\n", map.get(3)); // stdout: 0  (0 returned for key which does not exist)
	
    return 0;
}