#include <stdio.h>
int main()
{
    int numbur = 1;
    for (int row = 1; row <= 7; row++)
    {

        for (int col = 1; col <= 8; col++)
        {
            if (row % 2 != 0 && col % 2 != 0 && col != 8)
            {
                printf("+ ---");
            }
            else if (row % 2 != 0 && col % 2 == 0)
            {
                printf(" ");
            }
            else if (row % 2 == 0 && col % 2 != 0)
            {
                printf("| %2d", numbur++);
            }
            else if (col == 8)
            {
                printf("  |");
            }
            else
            {
                printf("  ");
            }
            if (col == 8 && row % 2 != 0)
            {
                printf("+");
            }
        }
        printf("\n");
    }
    return 0;
}