#include <stdio.h>
#include <stdlib.h>

void main() {
	int** ppa = nullptr;
	ppa = (int**)malloc(sizeof(int*) * 2);
	for (int i = 0; i < 2; ++i)
	{
		ppa[i] = (int*)malloc(sizeof(int) * 5);
		for (int j = 0; j < 5; ++j)
		{
			//ppa[i][j] = i * 5 + j;
			//*(ppa[i]+j) = i * 5 + j;
			*(*(ppa + i) + j) = i * 5 + j;
		}
	}
	for (int r = 0; r < 2; ++r)
	{
		for (int c = 0; c < 5; ++c)
		{
			printf("%i,", ppa[r][c]);
		}
		printf("\r\n");
	}
	for (int i = 0; i < 2; ++i)
	{
		free(ppa[i]);
	}
	free(ppa);
	/**
	0,1,2,3,4,
	5,6,7,8,9,
	*/
}