#include <stdio.h>
#include <stdlib.h>

void main() {
	int (*ip)[10];
	ip = (int(*)[10])malloc(sizeof(int) * 10);
	int* ip2 = (int*)ip;
	for (int i = 0; i < 10; ++i)
	{
		ip2[i] = i;
	}
	printf("%i\r\n", (int*)(ip + 1) - (int*)ip); // 10
	free(ip);
}