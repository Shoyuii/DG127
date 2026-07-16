#include <math.h>
#include <stdio.h>

int main()
{
    int x = 5, y = 10.0, z = 3;
    // 1
    printf("%d\n", (int)y / (int)z);
    printf("%f\n", (float)y / (int)z);
    printf("%f\n", (float)y / (int)z);
    printf("------------------------------------\n");
    // 2
    printf("x++ = %d\n", x++);
    printf("x = %d\n", x);
    printf("++x = %d\n", ++x);
    printf("x = %d\n", x);
    printf("------------------------------------\n");
    // 3
    printf("2 + 3 * 4 = %d\n", 2 + 3 * 4);
    printf("(2 + 3) * 4 = %d\n", (2 + 3) * 4);
    printf("10 - 2 - 3 = %d\n", 10 - 2 - 3);
    printf("2*3 + 4*5 = %d\n", 2 * 3 + 4 * 5);

    return 0;
}