#include <stdio.h>
#include <string.h>

class People
{
private:
    char name[20]; // data member
    int age;

public:
    void SetName(People* p, const char* n)
    {
        strcpy((*p).name, n);
    }

    void SetAge(People* p, int a)
    {
        (*p).age = a;
    }

    void Print(People* p)
    {
        printf("%s, age=%i\r\n", (*p).name, (*p).age);
    }
};


void main()
{
    People i;
    i.SetName(&i, "Jintaeks");
    i.SetAge(&i, 50);
    i.Print(&i);
}