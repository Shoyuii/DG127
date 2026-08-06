#include <stdio.h>
int main()
{
    printf("1. Triangle \n");
    for (int row = 1; row <= 5; row++)
    {
        for (int col = 1; col <= row; col++)
        {
            printf("* ");
        }
        printf("\n");
    }
    printf("2. Square \n");
    for (int row = 1; row <= 4; row++)
    {
        for (int col = 1; col <= 4; col++)
        {
            printf("* ");
        }
        printf("\n");
    }
    printf("3. Dimond \n");
    for (int row = 1; row <= 3; row++)
    {
        for (int col = 1; col <= 3 - row; col++)
        {
            printf(" ");
        }
        for (int col = 1; col <= row * 2 - 1; col++)
        {
            printf("*");
        }
        printf("\n");
    }
    for (int row = 4; row <= 5; row++)
    {
        for (int col = 1; col <= row - 3; col++)
        {
            printf(" ");
        }
        for (int col = 1; col <= (6 - row) * 2 - 1; col++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}