#include <stdio.h>
#include <conio.h>
#include <windows.h>

inline void GotoXy(int x, int y)
{
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}//GotoXy()

const int g_numRows = 8;

void main()
{
    char buffer[g_numRows][100] = 
    {
        "★★★★★★★★★★",
        "+                  +",
        "+  @@@@@ @@@@      +",
        "+    @   @         +",
        "+    @   @@@@      +",
        "+    @   @         +",
        "+    @   @@@@      +",
        "++++++++++++++++++++",
    };

    for (int r = 0; r < g_numRows; ++r)
        printf("%s\r\n", buffer[r]);
    GotoXy(10, 5);
    printf("hello");
    _getch();
}