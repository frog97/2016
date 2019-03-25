#include <stdio.h>
#include <stdlib.h>

void f(int* x) {
	*x += 1;
}

void Alloc(int** pp)
{
	*pp = (int*)malloc(sizeof(int));
}

void main() {
	int i = 2;
	int j = 1;
	f(&i);
	printf("%i, %i\r\n", i, j); // 3,1

	int* ip;
	Alloc(&ip);
	*ip = 99;
	printf("%i\r\n", *ip); // 99
	free(ip);
}
