#include <stdio.h>
#define ROWS 10
#define COLS 12
int tilemap[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 3, 0, 0, 0, 2, 2, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
void draw(int playerCol, int playerRow)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (i == playerRow && j == playerCol)
                printf("@");
            else if (tilemap[i][j] == 1)
                printf("#");
            else if (tilemap[i][j] == 2)
                printf("~");
            else
                printf(".");
        }
        printf("\n");
    }
}
int main()
{
    char move;
    int playerCol = 1, playerRow = 1;
    while (1)
    {
        draw(playerCol, playerRow);
        printf("Move [wasd] or Quit [q]: ");
        scanf(" %c", &move);
        if (move == 'q')
            break;

        int nextCol = playerCol, nextRow = playerRow;
        if (move == 'w')
            nextRow--;

        if (move == 's')
            nextRow++;

        if (move == 'a')
            nextCol--;

        if (move == 'd')
            nextCol++;

        if (tilemap[nextRow][nextCol] != 1)
        {
            playerCol = nextCol;
            playerRow = nextRow;
        }
    }
    return 0;
}