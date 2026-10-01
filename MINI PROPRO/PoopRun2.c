#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

/* =========================================================
   GAME SIZE
   ========================================================= */

#define W 120
#define H 20
#define G 15

#define MAX 12

#define FLOOR 0
#define CEILING 1

/* =========================================================
   PLAYER
   ========================================================= */

#define PLAYER_WIDTH 8
#define PLAYER_HEIGHT 3

/* =========================================================
   GAME SPEED
   ========================================================= */

#define START_SPEED 80
#define MIN_SPEED 25

/* =========================================================
   JUMP
   ========================================================= */

#define JUMP_FORCE 3.0f
#define GRAVITY 0.35f
#define AIR_TIME 8

/* =========================================================
   STRUCT
   ========================================================= */

typedef struct
{
    int x;

    /*
       y = ตำแหน่งแถวบนสุดของตัวละคร
    */
    float y;

    float vy;

    int hp;
    int score;

    int jumps;
    int side;

    int airTime;

} Player;

typedef struct
{
    int x;
    int y;

    int width;
    int height;

    int side;
    int active;

} Object;

/* =========================================================
   GLOBAL
   ========================================================= */

Player p;

Object obs[MAX];
Object coins[MAX];

HANDLE out;

/* =========================================================
   CONSOLE
   ========================================================= */

void gotoxy(int x, int y)
{
    COORD pos;

    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(out, pos);
}

void color(int c)
{
    SetConsoleTextAttribute(out, c);
}

void initConsole()
{
    out = GetStdHandle(STD_OUTPUT_HANDLE);

    /*
       ซ่อน Cursor
    */

    CONSOLE_CURSOR_INFO ci;

    ci.dwSize = 1;
    ci.bVisible = FALSE;

    SetConsoleCursorInfo(out, &ci);

    /*
       กำหนดขนาด Console
    */

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(out, &csbi);

    COORD size;

    size.X = W + 2;
    size.Y = H + 6;

    SetConsoleScreenBufferSize(out, size);
}

/* =========================================================
   RESET
   ========================================================= */

void reset()
{
    int i;

    p.x = 8;

    /*
       ตัวละครสูง 3 แถว

       พื้นอยู่ที่ G

       ดังนั้น

       G - 3 = แถวบนของตัวละคร

       ตัวอย่าง G = 8

       ตัวละคร:

       row 5
       row 6
       row 7
       ===== row 8
    */

    p.y = G - PLAYER_HEIGHT;

    p.vy = 0;

    p.hp = 10;

    p.score = 0;

    p.jumps = 0;

    p.side = FLOOR;

    p.airTime = 0;

    for (i = 0; i < MAX; i++)
    {
        obs[i].active = 0;

        coins[i].active = 0;
    }
}

/* =========================================================
   SWITCH SIDE
   ========================================================= */

void switchSide(int side)
{
    if (p.side == side)
        return;

    p.side = side;

    /*
       หยุดการเคลื่อนที่เดิม
    */

    p.vy = 0;

    p.jumps = 0;

    p.airTime = 0;

    /*
       FLOOR

       ตัวละครต้องยืนอยู่เหนือพื้น
    */

    if (side == FLOOR)
    {
        p.y = G - PLAYER_HEIGHT;
    }

    /*
       CEILING

       row 0 = เพดาน
       row 1 = ตัวละครแถวบน
    */

    else
    {
        p.y = 1;
    }
}

/* =========================================================
   JUMP
   ========================================================= */

void jump()
{
    /*
       จำกัดจำนวน Jump
    */

    if (p.jumps >= 3)
        return;

    /*
       อยู่พื้น

       กระโดดขึ้น
       y ลดลง
    */

    if (p.side == FLOOR)
    {
        p.vy = -JUMP_FORCE;
    }

    /*
       อยู่เพดาน

       กระโดดลง
       y เพิ่มขึ้น
    */

    else
    {
        p.vy = JUMP_FORCE;
    }

    p.jumps = p.jumps + 1;

    p.airTime = 0;
}

/* =========================================================
   INPUT
   ========================================================= */

void input()
{
    int key;

    if (!_kbhit())
        return;

    key = _getch();

    /*
       SPACE = Jump
    */

    if (key == ' ')
    {
        jump();

        return;
    }

    /*
       W = Ceiling
    */

    if (key == 'w' ||
        key == 'W')
    {
        switchSide(CEILING);

        return;
    }

    /*
       S = Floor
    */

    if (key == 's' ||
        key == 'S')
    {
        switchSide(FLOOR);

        return;
    }

    /*
       Arrow keys

       224 = Arrow key
    */

    if (key == 224)
    {
        key = _getch();

        /*
           UP
        */

        if (key == 72)
        {
            switchSide(CEILING);
        }

        /*
           DOWN
        */

        if (key == 80)
        {
            switchSide(FLOOR);
        }

        return;
    }

    /*
       Q = Quit
    */

    if (key == 'q' ||
        key == 'Q')
    {
        p.hp = 0;
    }
}

/* =========================================================
   PHYSICS
   ========================================================= */

void physics()
{
    /*
       เคลื่อนที่ตาม velocity
    */

    p.y += p.vy;

    /*
       =====================================================
       FLOOR
       =====================================================
    */

    if (p.side == FLOOR)
    {
        /*
           Gravity ดึงลง
        */

        p.vy += GRAVITY;

        /*
           ลดความเร็วช่วงต้นของการตก
        */

        if (p.vy > 0 &&
            p.airTime < AIR_TIME)
        {
            p.vy *= 0.88f;

            p.airTime++;
        }

        /*
           =================================================
           จำกัดด้านบน
           =================================================

           ไม่ให้ตัวละครทะลุเพดาน

           เพดาน = 0
           ตัวละครสูง 3
           ตำแหน่งสูงสุด = 1
        */

        if (p.y < 1)
        {
            p.y = 1;

            p.vy = 0;
        }

        /*
           =================================================
           Floor collision
           =================================================

           พื้น = G

           ตัวละครสูง 3

           ดังนั้น top = G - 3
        */

        if (p.y >= G - PLAYER_HEIGHT)
        {
            p.y = G - PLAYER_HEIGHT;

            p.vy = 0;

            p.jumps = 0;

            p.airTime = 0;
        }
    }

    /*
       =====================================================
       CEILING
       =====================================================
    */

    else
    {
        /*
           Gravity ดึงขึ้น
        */

        p.vy -= GRAVITY;

        /*
           ลดความเร็วช่วงต้น
        */

        if (p.vy < 0 &&
            p.airTime < AIR_TIME)
        {
            p.vy *= 0.88f;

            p.airTime++;
        }

        /*
           =================================================
           จำกัดไม่ให้กระโดดทะลุพื้น
           =================================================

           top สูงสุดที่จะลงมาได้คือ G - 3
        */

        if (p.y > G - PLAYER_HEIGHT)
        {
            p.y = G - PLAYER_HEIGHT;

            p.vy = 0;
        }

        /*
           =================================================
           Ceiling collision
           =================================================
        */

        if (p.y <= 1)
        {
            p.y = 1;

            p.vy = 0;

            p.jumps = 0;

            p.airTime = 0;
        }
    }
}

/* =========================================================
   GAME SPEED
   ========================================================= */

int getGameSpeed()
{
    int speed;

    speed =
        START_SPEED -
        (p.score / 25);

    if (speed < MIN_SPEED)
        speed = MIN_SPEED;

    return speed;
}

/* =========================================================
   SPAWN OBSTACLE
   ========================================================= */

void spawnObstacle()
{
    int i;

    /*
       โอกาสเกิด obstacle
    */

    if (rand() % 80 != 0)
        return;

    for (i = 0; i < MAX; i++)
    {
        if (!obs[i].active)
        {
            /*
               เริ่มจากขวาสุด
            */

            obs[i].x = W - 1;

            /*
               สุ่มพื้น / เพดาน
            */

            obs[i].side = rand() % 2;

            /*
               ขนาด
            */

            obs[i].width =
                1 + rand() % 4;

            obs[i].height =
                1 + rand() % 3;

            /*
               จำกัดความสูง
            */

            if (obs[i].height > 3)
                obs[i].height = 3;

            /*
               FLOOR

               ตัว obstacle ติดพื้น
            */

            if (obs[i].side == FLOOR)
            {
                obs[i].y =
                    G - obs[i].height;
            }

            /*
               CEILING

               ตัว obstacle ติดเพดาน
            */

            else
            {
                obs[i].y = 1;
            }

            obs[i].active = 1;

            break;
        }
    }
}

/* =========================================================
   SPAWN COIN
   ========================================================= */

void spawnCoin()
{
    int i;

    if (rand() % 10 != 0)
        return;

    for (i = 0; i < MAX; i++)
    {
        if (!coins[i].active)
        {
            coins[i].x = W - 1;

            coins[i].side =
                rand() % 2;

            /*
               FLOOR

               ไม่ให้ Coin อยู่ติดพื้นเกินไป
            */

            if (coins[i].side == FLOOR)
            {
                coins[i].y =
                    G - 3 -
                    rand() % 3;
            }

            /*
               CEILING
            */

            else
            {
                coins[i].y =
                    3 +
                    rand() % 3;
            }

            coins[i].active = 1;

            break;
        }
    }
}

/* =========================================================
   SPAWN
   ========================================================= */

void spawn()
{
    spawnObstacle();

    spawnCoin();
}

/* =========================================================
   MOVE OBJECTS
   ========================================================= */

void moveObjects()
{
    static DWORD lastMove = 0;

    DWORD now;

    int speed;

    now = GetTickCount();

    speed = getGameSpeed();

    /*
       ยังไม่ถึงเวลาเคลื่อนที่
    */

    if (now - lastMove < (DWORD)speed)
        return;

    lastMove = now;

    /*
       =====================================================
       Obstacles
       =====================================================
    */

    for (int i = 0; i < MAX; i++)
    {
        if (obs[i].active)
        {
            obs[i].x--;

            if (obs[i].x +
                    obs[i].width <
                0)
            {
                obs[i].active = 0;
            }
        }

        /*
           =================================================
           Coins
           =================================================
        */

        if (coins[i].active)
        {
            coins[i].x--;

            if (coins[i].x < 0)
            {
                coins[i].active = 0;
            }
        }
    }
}

/* =========================================================
   COLLISION - OBSTACLE
   ========================================================= */

int hitObstacle(Object *o)
{
    int playerLeft;
    int playerRight;

    int playerTop;
    int playerBottom;

    int objectLeft;
    int objectRight;

    int objectTop;
    int objectBottom;

    /*
       =====================================================
       PLAYER X
       =====================================================
    */

    playerLeft = p.x;

    playerRight =
        p.x + PLAYER_WIDTH - 1;

    /*
       =====================================================
       OBJECT X
       =====================================================
    */

    objectLeft = o->x;

    objectRight =
        o->x + o->width - 1;

    /*
       ถ้าไม่ทับกันในแนว X
    */

    if (playerRight < objectLeft)
        return 0;

    if (playerLeft > objectRight)
        return 0;

    /*
       =====================================================
       PLAYER Y
       =====================================================
    */

    playerTop =
        (int)p.y;

    playerBottom =
        (int)p.y + PLAYER_HEIGHT - 1;

    /*
       =====================================================
       OBJECT Y
       =====================================================
    */

    objectTop =
        o->y;

    objectBottom =
        o->y + o->height - 1;

    /*
       ถ้าไม่ทับกันในแนว Y
    */

    if (playerBottom < objectTop)
        return 0;

    if (playerTop > objectBottom)
        return 0;

    /*
       ชน
    */

    return 1;
}

/* =========================================================
   COLLISION
   ========================================================= */

void collision()
{
    int i;

    for (i = 0; i < MAX; i++)
    {
        /*
           =================================================
           OBSTACLE
           =================================================
        */

        if (obs[i].active &&
            obs[i].side == p.side)
        {
            if (hitObstacle(&obs[i]))
            {
                p.hp--;

                obs[i].active = 0;
            }
        }

        /*
           =================================================
           COIN
           =================================================
        */

        if (coins[i].active &&
            coins[i].side == p.side)
        {
            /*
               ตรวจ X

               Coin มีขนาด 1
            */

            if (coins[i].x >= p.x &&
                coins[i].x < p.x + PLAYER_WIDTH)
            {
                /*
                   ตรวจ Y
                */

                if (coins[i].y >= (int)p.y &&
                    coins[i].y <=
                        (int)p.y + PLAYER_HEIGHT - 1)
                {
                    /*
                       Coin = +100
                    */

                    p.score += 100;

                    coins[i].active = 0;
                }
            }
        }
    }

    /*
       Score จากเวลา
    */

    p.score++;
}

/* =========================================================
   DRAW OBSTACLE
   ========================================================= */

void drawObstacle(
    Object *o,
    char screen[H][W + 1])
{
    int xx;
    int yy;

    /*
       =====================================================
       BODY
       =====================================================
    */

    for (xx = 0;
         xx < o->width;
         xx++)
    {
        for (yy = 0;
             yy < o->height;
             yy++)
        {
            int x;
            int y;

            x = o->x + xx;

            y = o->y + yy;

            if (x >= 0 &&
                x < W &&
                y >= 0 &&
                y < H)
            {
                screen[y][x] = '#';
            }
        }
    }

    /*
       =====================================================
       FLOOR OBSTACLE
       =====================================================

          ^
         ###
         ###
    */

    if (o->side == FLOOR)
    {
        for (xx = 0;
             xx < o->width;
             xx++)
        {
            int x;
            int y;

            x = o->x + xx;

            y = o->y - 1;

            if (x >= 0 &&
                x < W &&
                y >= 0 &&
                y < H)
            {
                screen[y][x] = '^';
            }
        }
    }

    /*
       =====================================================
       CEILING OBSTACLE
       =====================================================

         ###
         ###
          v
    */

    else
    {
        for (xx = 0;
             xx < o->width;
             xx++)
        {
            int x;
            int y;

            x = o->x + xx;

            y =
                o->y +
                o->height;

            if (x >= 0 &&
                x < W &&
                y >= 0 &&
                y < H)
            {
                screen[y][x] = 'v';
            }
        }
    }
}

/* =========================================================
   DRAW PLAYER - FLOOR
   ========================================================= */

void drawPlayerFloor(
    int px,
    int py,
    char screen[H][W + 1])
{
    /*
           /\
          (0w0)
         (______)
    */

    /*
       =====================================================
       แถวบน
       =====================================================
    */

    if (py >= 0 &&
        py < H)
    {
        if (px + 2 >= 0 &&
            px + 2 < W)
        {
            screen[py][px + 2] = '/';
        }

        if (px + 5 >= 0 &&
            px + 5 < W)
        {
            screen[py][px + 5] = '\\';
        }
    }

    /*
       =====================================================
       แถวกลาง
       =====================================================
    */

    if (py + 1 >= 0 &&
        py + 1 < H)
    {
        if (px >= 0 &&
            px < W)
        {
            screen[py + 1][px + 1] = '(';
        }

        if (px + 3 >= 0 &&
            px + 3 < W)
        {
            screen[py + 1][px + 3] = '0';
        }

        if (px + 4 >= 0 &&
            px + 4 < W)
        {
            screen[py + 1][px + 4] = 'w';
        }

        if (px + 5 >= 0 &&
            px + 5 < W)
        {
            screen[py + 1][px + 5] = '0';
        }

        if (px + 6 >= 0 &&
            px + 6 < W)
        {
            screen[py + 1][px + 6] = ')';
        }
    }

    /*
       =====================================================
       แถวล่าง
       =====================================================
    */

    if (py + 2 >= 0 &&
        py + 2 < H)
    {
        if (px >= 0 &&
            px < W)
        {
            screen[py + 2][px] = '(';
        }

        for (int i = 1; i <= 6; i++)
        {
            if (px + i >= 0 &&
                px + i < W)
            {
                screen[py + 2][px + i] = '_';
            }
        }

        if (px + 7 >= 0 &&
            px + 7 < W)
        {
            screen[py + 2][px + 7] = ')';
        }
    }
}

/* =========================================================
   DRAW PLAYER - CEILING
   ========================================================= */

void drawPlayerCeiling(
    int px,
    int py,
    char screen[H][W + 1])
{
    /*
         (______)
          (0w0)
            \/
    */

    /*
       =====================================================
       แถวบน
       =====================================================
    */

    if (py >= 0 &&
        py < H)
    {
        if (px >= 0 &&
            px < W)
        {
            screen[py][px] = '(';
        }

        for (int i = 1; i <= 6; i++)
        {
            if (px + i >= 0 &&
                px + i < W)
            {
                screen[py][px + i] = '-';
            }
        }

        if (px + 7 >= 0 &&
            px + 7 < W)
        {
            screen[py][px + 7] = ')';
        }
    }

    /*
       =====================================================
       แถวกลาง
       =====================================================
    */

    if (py + 1 >= 0 &&
        py + 1 < H)
    {
        if (px + 1 >= 0 &&
            px + 1 < W)
        {
            screen[py + 1][px + 1] = '(';
        }

        if (px + 3 >= 0 &&
            px + 3 < W)
        {
            screen[py + 1][px + 3] = '0';
        }

        if (px + 4 >= 0 &&
            px + 4 < W)
        {
            screen[py + 1][px + 4] = 'm';
        }

        if (px + 5 >= 0 &&
            px + 5 < W)
        {
            screen[py + 1][px + 5] = '0';
        }

        if (px + 6 >= 0 &&
            px + 6 < W)
        {
            screen[py + 1][px + 6] = ')';
        }
    }

    /*
       =====================================================
       แถวล่าง
       =====================================================
    */

    if (py + 2 >= 0 &&
        py + 2 < H)
    {
        if (px + 2 >= 0 &&
            px + 2 < W)
        {
            screen[py + 2][px + 2] = '\\';
        }

        if (px + 5 >= 0 &&
            px + 5 < W)
        {
            screen[py + 2][px + 5] = '/';
        }
    }
}

/* =========================================================
   DRAW
   ========================================================= */

void draw()
{
    char screen[H][W + 1];

    int x;
    int y;
    int i;

    /*
       =====================================================
       CLEAR SCREEN ARRAY
       =====================================================
    */

    for (y = 0;
         y < H;
         y++)
    {
        for (x = 0;
             x < W;
             x++)
        {
            screen[y][x] = ' ';
        }

        screen[y][W] = '\0';
    }

    /*
       =====================================================
       TOP
       =====================================================
    */

    for (x = 0;
         x < W;
         x++)
    {
        screen[0][x] = '=';
    }

    /*
       =====================================================
       FLOOR
       =====================================================
    */

    for (x = 0;
         x < W;
         x++)
    {
        screen[G][x] = '=';
    }

    /*
       =====================================================
       OBSTACLES
       =====================================================
    */

    for (i = 0;
         i < MAX;
         i++)
    {
        if (obs[i].active)
        {
            drawObstacle(
                &obs[i],
                screen);
        }
    }

    /*
       =====================================================
       COINS
       =====================================================
    */

    for (i = 0;
         i < MAX;
         i++)
    {
        if (!coins[i].active)
            continue;

        if (coins[i].x >= 0 &&
            coins[i].x < W &&
            coins[i].y >= 0 &&
            coins[i].y < H)
        {
            screen
                [coins[i].y]
                [coins[i].x] = '$';
        }
    }

    /*
       =====================================================
       PLAYER
       =====================================================
    */

    if (p.x >= 0 &&
        p.x < W &&
        (int)p.y >= 0 &&
        (int)p.y < H)
    {
        int px;
        int py;

        px = p.x;
        py = (int)p.y;

        /*
           FLOOR

              /\
             (0w0)
            (______)
        */

        if (p.side == FLOOR)
        {
            drawPlayerFloor(
                px,
                py,
                screen);
        }

        /*
           CEILING

            (______)
             (0w0)
               \/
        */

        else
        {
            drawPlayerCeiling(
                px,
                py,
                screen);
        }
    }

    /*
       =====================================================
       OUTPUT
       =====================================================
    */

    gotoxy(0, 0);

    /*
       TITLE
    */

    color(14);

    printf("POOP RUNNER ");

    /*
       SCORE
    */

    color(11);

    printf(
        "Score:%d ",
        p.score);

    /*
       HP
    */

    color(12);

    printf(
        "HP:%d ",
        p.hp);

    /*
       SPEED
    */

    color(13);

    printf(
        "Speed:%d ",
        getGameSpeed());

    /*
       SIDE
    */

    color(10);

    if (p.side == FLOOR)
    {
        printf("DOWN");
    }
    else
    {
        printf("UP");
    }

    color(7);

    printf("\n\n");

    /*
       =====================================================
       GAME SCREEN
       =====================================================
    */

    for (y = 0;
         y < H;
         y++)
    {
        printf(
            "%s\n",
            screen[y]);
    }

    printf("\n");

    /*
       =====================================================
       CONTROLS
       =====================================================
    */

    printf(
        "SPACE = Jump | "
        "W/UP = UP | "
        "S/DOWN = DOWN | "
        "Q = Quit");

    printf(
        "\nSpeed increases as score increases!");
}

/* =========================================================
   GAME OVER
   ========================================================= */

void gameOver()
{
    char key;

    system("cls");

    /*
       GAME OVER
    */

    color(12);

    gotoxy(25, 6);

    printf("GAME OVER!");

    /*
       SCORE
    */

    color(14);

    gotoxy(22, 8);

    printf(
        "Score : %d",
        p.score);

    /*
       RESTART
    */

    color(11);

    gotoxy(22, 10);

    printf("R = Restart");

    /*
       QUIT
    */

    gotoxy(22, 11);

    printf("Q = Quit");

    color(7);

    /*
       =====================================================
       WAIT INPUT
       =====================================================
    */

    while (1)
    {
        key = _getch();

        /*
           Restart
        */

        if (key == 'r' ||
            key == 'R')
        {
            reset();

            return;
        }

        /*
           Quit
        */

        if (key == 'q' ||
            key == 'Q')
        {
            exit(0);
        }
    }
}

/* =========================================================
   MAIN
   ========================================================= */

int main()
{
    /*
       Random seed
    */

    srand(
        (unsigned)time(NULL));

    /*
       Console
    */

    initConsole();

    /*
       Reset game
    */

    reset();

    /*
       =====================================================
       GAME LOOP
       =====================================================
    */

    while (1)
    {
        /*
           INPUT
        */

        input();

        /*
           =================================================
           GAME OVER
           =================================================
        */

        if (p.hp <= 0)
        {
            gameOver();

            continue;
        }

        /*
           =================================================
           PHYSICS
           =================================================
        */

        physics();

        /*
           =================================================
           SPAWN
           =================================================
        */

        spawn();

        /*
           =================================================
           MOVE
           =================================================
        */

        moveObjects();

        /*
           =================================================
           COLLISION
           =================================================
        */

        collision();

        /*
           =================================================
           DRAW
           =================================================
        */

        draw();

        /*
           =================================================
           GAME LOOP DELAY
           =================================================
        */

        Sleep(10);
    }

    return 0;
}