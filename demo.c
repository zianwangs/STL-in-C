#include <stdio.h>
#include "String.h"

//typedef Vector(double) Vector_double;
int main(int argc, char const *argv[])
{
    String str = DEFAULT_STRING;
    Object.load(&str);
    str.push_back('a');
    str.concat(" nice STRING ");
    str.set(9,'?');
    for (int i = 0; i < str.size(); ++i)
        printf("%c", str.at(i));

    return 0;
}