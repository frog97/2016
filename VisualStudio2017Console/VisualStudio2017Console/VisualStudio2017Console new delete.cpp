#include <stdio.h>
#include <conio.h>
#include <windows.h>

// 매크로 상수macro constant
#define TWO     2
#define PI      3.141592f

void main()
{
    int* ip = NULL;

    ip = new int;
    *ip = 3;
    (*ip) += 1;
    printf("%d\r\n", *ip);
    delete ip; // memory leak
}
