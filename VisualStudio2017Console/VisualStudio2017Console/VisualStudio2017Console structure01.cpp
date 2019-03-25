#include <stdio.h>
#include <string.h>

char g_name[10][20];
int  g_age[10];

void SetAge(int id, int age)
{
    g_age[id] = age;
}

void SetName(int id, const char* name)
{
    strcpy(g_name[id], name);
}

void Print(int id)
{
    printf("%s, age=%d\r\n", g_name[id], g_age[id]);
}

void main()
{
    SetAge(0, 50);
    SetName(0, "Jintaek");
    SetAge(1, 27);
    SetName(1, "Cheon");
    Print(0);
    Print(1);
}