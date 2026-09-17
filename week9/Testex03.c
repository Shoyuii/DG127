#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

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
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

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

    printf("\nWASD = Move | Q = Quit\n");
}

int main()
{
    char move;

    int playerCol = 1;
    int playerRow = 1;

    while (1)
    {
        draw(playerCol, playerRow);

        // รับปุ่มทันที ไม่ต้องกด Enter
        move = _getch();

        // กด q เพื่อออก
        if (move == 'q')
            break;

        int nextCol = playerCol;
        int nextRow = playerRow;

        // ตรวจสอบการเคลื่อนที่
        if (move == 'w')
            nextRow--;
        else if (move == 's')
            nextRow++;
        else if (move == 'a')
            nextCol--;
        else if (move == 'd')
            nextCol++;

        // ตรวจสอบว่าอยู่ในขอบเขต และไม่ใช่กำแพง
        if (nextRow >= 0 && nextRow < ROWS &&
            nextCol >= 0 && nextCol < COLS &&
            tilemap[nextRow][nextCol] != 1)
        {
            playerCol = nextCol;
            playerRow = nextRow;
        }
    }

    return 0;
}
