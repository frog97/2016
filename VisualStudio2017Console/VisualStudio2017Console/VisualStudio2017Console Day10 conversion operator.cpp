#include <stdio.h>

struct KTest
{
};

void main()
{
    int i = 2;
    int j = 3;
    //i = i + 3;
    i += 3; // *= /=, -=
    printf("%d\r\n", i);
    //i = i + j * 5;
    i += j * 5;
    printf("%d\r\n", i);
    printf("%d,%d,%d\r\n", sizeof(i), sizeof(5.0),sizeof('a'));
    i = 2;
    j = 3;
    printf("%d,%d,%d,%d\r\n", i < 3, i >= 3, i == j, i != j ); // 관계연산자relational operator
    // 1, 0, 0, 1
    printf("%d\r\n", i == 2 && j == 3); // 논리연산자logical operator, && AND
    // 1
    printf("%d\r\n", i >= 2 && j > 3);
    // 0
    printf("%d\r\n", i >= 2 || j > 3); // || logical OR operator
    // 1
    printf("%d\r\n", (i < 100) && (-1));
    // 1
    float f = 0.1f; // 4 byte 실수형 변수
    double g = 230000.456; // 8 byte 실수형 변수
    char c = 1; // 1 byte 정수
    short s = 2; // 2 byte 정수
    int t = 3; // 4 byte 정수
    t = (int)s; // 형변환 연산자type conversion operator, casting operator
    t = s;
    t = (int)g;
    KTest t2;
    t2 = (int)t;
    printf("%d\r\n", t);
}