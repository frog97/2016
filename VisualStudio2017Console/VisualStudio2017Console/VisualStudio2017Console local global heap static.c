#include <stdio.h>

int i = 1; // global variable, data block

void Foo()
{
    int i = 2; // local variable, stack
}

int main()
{
    auto int i = 3;
    register int j = 4; // register variable
    auto int* ip = NULL;
    ip = (int*)malloc(sizeof(int) * 10); // heap
    free(ip);
}
