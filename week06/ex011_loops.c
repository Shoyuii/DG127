#include <stdio.h>
int main()
{
    printf("1. === Print 1 to 10 ===\n");
    for (int i = 1; i <= 10; i++)
    {
        printf("%d\n", i);
    }
    printf("\n2. === Print 1 to 10 ===\n");
    int i = 1;
    while (i <= 10)
    {
        printf("%d\n", i);
        i++;
    }
    printf("\n3. === Print 1 to 10 ===\n");
    int I = 1;
    do
    {
        printf("%d\n", I);
        I++;
    } while (I <= 10);

    return 0;
}