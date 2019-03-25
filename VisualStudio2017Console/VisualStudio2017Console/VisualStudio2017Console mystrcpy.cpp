#include <stdio.h>
#include <string.h>

struct People
{
    char name[20];
    int age;
};

void mystrcpy(char* dest, const char* src)
{
    while (*src != 0)
    {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = 0;
}

void main()
{
    People i; // People 구조체 타입 이름, i: 변수
    mystrcpy(i.name, "Jintaeks");
    i.age = 50;
    printf("%s, age=%i\r\n", i.name, i.age);
}