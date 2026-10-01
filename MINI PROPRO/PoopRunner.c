#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define W 120
#define H 20
#define G 17
#define MAX 10

typedef struct
{
    int x, y, vy, hp, score, coin, jumps;
} Player;

typedef struct
{
    int x, y, active;
} Object;

Player p;
Object obs[MAX], coins[MAX];
HANDLE out;

/* ---------- Console ---------- */

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(out, pos);
}

void color(int c)
{
    SetConsoleTextAttribute(out, c);
}

void initConsole()
{
    out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorInfo(out, &ci);
}

/* ---------- Game ---------- */

void reset()
{
    int i;

    p.x = 8;
    p.y = G - 1;
    p.vy = 0;
    p.hp = 3;
    p.score = 0;
    p.coin = 0;
    p.jumps = 0;

    for (i = 0; i < MAX; i++)
        obs[i].active = coins[i].active = 0;
}

void jump()
{
    /* Double jump */
    if (p.jumps < 10)
    {
        p.vy = -2;
        p.jumps++;
    }
}

void input()
{
    if (!_kbhit())
        return;

    switch (_getch())
    {
    case ' ':
        jump();
        break;

    case 'q':
    case 'Q':
        p.hp = 0;
        break;
    }
}

void physics()
{
    p.y += p.vy;
    p.vy++;

    if (p.y >= G - 1)
    {
        p.y = G - 1;
        p.vy = 0;
        p.jumps = 0;
    }
}

void spawn()
{
    int i;

    if (rand() % 35 == 0)
        for (i = 0; i < MAX; i++)
            if (!obs[i].active)
            {
                obs[i].x = W - 1;
                obs[i].y = G - 1;
                obs[i].active = 1;
                break;
            }

    if (rand() % 25 == 0)
        for (i = 0; i < MAX; i++)
            if (!coins[i].active)
            {
                coins[i].x = W - 1;
                coins[i].y = G - 4 - rand() % 4;
                coins[i].active = 1;
                break;
            }
}

void move()
{
    int i;

    for (i = 0; i < MAX; i++)
    {
        if (obs[i].active && --obs[i].x < 0)
            obs[i].active = 0;

        if (coins[i].active && --coins[i].x < 0)
            coins[i].active = 0;
    }
}

void collision()
{
    int i;

    for (i = 0; i < MAX; i++)
    {
        /* Obstacle */
        if (obs[i].active &&
            obs[i].x == p.x &&
            p.y >= G - 2)
        {
            p.hp--;
            obs[i].active = 0;
        }

        /* Coin */
        if (coins[i].active &&
            abs(coins[i].x - p.x) <= 1 &&
            abs(coins[i].y - p.y) <= 1)
        {
            p.coin++;
            p.score += 100;
            coins[i].active = 0;
        }
    }

    p.score++;
}

void draw()
{
    char screen[H][W + 1];
    int x, y, i;

    /* Clear buffer */
    for (y = 0; y < H; y++)
    {
        for (x = 0; x < W; x++)
            screen[y][x] = ' ';

        screen[y][W] = '\0';
    }

    /* Ground */
    for (x = 0; x < W; x++)
        screen[G][x] = '=';

    /* Obstacles */
    for (i = 0; i < MAX; i++)
        if (obs[i].active &&
            obs[i].x >= 0 &&
            obs[i].x < W)
            screen[G - 1][obs[i].x] = '#';

    /* Coins */
    for (i = 0; i < MAX; i++)
        if (coins[i].active &&
            coins[i].x >= 0 &&
            coins[i].x < W &&
            coins[i].y >= 0 &&
            coins[i].y < H)
            screen[coins[i].y][coins[i].x] = '$';

    /* Player */
    if (p.x >= 0 && p.x < W &&
        p.y >= 0 && p.y < H)
        screen[p.y][p.x] = '@';

    /* Draw */
    gotoxy(0, 0);

    color(14);
    printf("POOP RUNNER   ");

    color(11);
    printf("Score:%d ", p.score);

    color(14);
    printf("Coin:%d ", p.coin);

    color(12);
    printf("HP:%d\n\n", p.hp);

    color(7);

    for (y = 0; y < H; y++)
        printf("%s\n", screen[y]);

    printf("\nSPACE = Double Jump | Q = Quit");
}

void gameOver()
{
    gotoxy(0, 0);

    color(12);

    printf("\n\n");
    printf("       GAME OVER!\n\n");

    color(14);

    printf("       Score: %d\n", p.score);
    printf("       Coin : %d\n\n", p.coin);

    color(11);

    printf("       R = Restart\n");
    printf("       Q = Quit\n");

    while (1)
    {
        char c = _getch();

        if (c == 'r' || c == 'R')
        {
            reset();
            return;
        }

        if (c == 'q' || c == 'Q')
        {
            exit(0);
        }
    }
}

/* ---------- Main ---------- */

int main()
{
    srand((unsigned)time(NULL));

    initConsole();
    reset();

    while (1)
    {
        input();

        if (p.hp <= 0)
            gameOver();

        physics();
        spawn();
        move();
        collision();
        draw();

        Sleep(35); /* ~28 FPS */
    }

    return 0;
}
