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

/*
   G = ตำแหน่งพื้น
*/
#define G 15

#define MAX 12

#define FLOOR 0
#define CEILING 1

/* =========================================================
   PLAYER
   ========================================================= */

#define PLAYER_WIDTH 8
#define PLAYER_HEIGHT 3

/*
   Hitbox ให้แคบกว่าตัวละครเล็กน้อย
   ทำให้ชนแล้วไม่รู้สึก unfair
*/
#define HITBOX_X 1
#define HITBOX_WIDTH 6

/* =========================================================
   PHYSICS
   ========================================================= */

/*
   หน่วย = ช่อง / วินาที
*/
#define JUMP_FORCE 22.0f
#define GRAVITY 30.0f

/* =========================================================
   GAME SPEED
   ========================================================= */

/*
   ความเร็วของ Object
   หน่วย = ช่อง / วินาที
*/
#define START_SPEED 10.0f
#define MAX_SPEED 100.0f

/*
   Score 100 จะถึงความเร็วสูงสุด
*/
#define SPEED_PER_SCORE 0.02f

/* =========================================================
   DAMAGE
   ========================================================= */

#define FLASH_TIME 0.60f
#define INVINCIBLE_TIME 0.50f

/* =========================================================
   FPS
   ========================================================= */

#define TARGET_FPS 60.0

/* =========================================================
   COLORS
   ========================================================= */

#define COLOR_NORMAL 6
#define COLOR_RED 12
#define COLOR_YELLOW 14
#define COLOR_CYAN 11
#define COLOR_GREEN 10
#define COLOR_MAGENTA 13
#define COLOR_WHITE 7

/* =========================================================
   PLAYER
   ========================================================= */

typedef struct
{
    int x;

    /*
       y = ตำแหน่งบนสุดของ Player
    */
    float y;

    /*
       velocity Y
       หน่วย = ช่อง / วินาที
    */
    float vy;

    int hp;
    int score;

    int jumps;
    int side;

    /*
       Timer
       หน่วย = วินาที
    */
    float flashTimer;
    float invincibleTimer;

} Player;

/* =========================================================
   OBJECT
   ========================================================= */

typedef struct
{
    float x;

    int y;

    int width;
    int height;

    int side;

    int active;

} Object;

/* =========================================================
   GLOBAL GAME
   ========================================================= */

Player p;

Object obs[MAX];
Object coins[MAX];

/* =========================================================
   DELTA TIME
   ========================================================= */

LARGE_INTEGER performanceFrequency;
LARGE_INTEGER previousTime;

double deltaTime = 0.0;

/* =========================================================
   GAME TIMER
   ========================================================= */

float scoreTimer = 0.0f;

float obstacleSpawnTimer = 0.0f;
float coinSpawnTimer = 0.0f;

/* =========================================================
   GAME STATE
   ========================================================= */

int gameOverState = 0;
int running = 1;

/* =========================================================
   CONSOLE DOUBLE BUFFER
   ========================================================= */

HANDLE consoleFront;
HANDLE consoleBack;

#define SCREEN_W (W + 2)
#define SCREEN_H (H + 6)

CHAR_INFO frameBuffer[SCREEN_W * SCREEN_H];

COORD bufferSize =
    {
        SCREEN_W,
        SCREEN_H};

COORD bufferPosition =
    {
        0,
        0};

SMALL_RECT screenRect =
    {
        0,
        0,
        SCREEN_W - 1,
        SCREEN_H - 1};

/* =========================================================
   DELTA TIME INIT
   ========================================================= */

void initDeltaTime()
{
    QueryPerformanceFrequency(
        &performanceFrequency);

    QueryPerformanceCounter(
        &previousTime);
}

/* =========================================================
   DELTA TIME UPDATE
   ========================================================= */

void updateDeltaTime()
{
    LARGE_INTEGER currentTime;

    QueryPerformanceCounter(
        &currentTime);

    deltaTime =
        (double)(currentTime.QuadPart -
                 previousTime.QuadPart) /
        (double)
            performanceFrequency.QuadPart;

    previousTime = currentTime;

    /*
       ป้องกัน Delta Time ใหญ่เกินไป

       เช่น:
       - โปรแกรมถูกพัก
       - Debugger
       - ลากหน้าต่าง
       - Windows ค้างชั่วคราว
    */

    if (deltaTime > 0.05)
        deltaTime = 0.05;

    if (deltaTime < 0.0)
        deltaTime = 0.0;
}

/* =========================================================
   FRAME LIMITER
   ========================================================= */

void limitFrameRate()
{
    static LARGE_INTEGER frameStart;
    static int initialized = 0;

    LARGE_INTEGER now;

    double elapsed;

    double targetTime =
        1.0 / TARGET_FPS;

    if (!initialized)
    {
        QueryPerformanceCounter(
            &frameStart);

        initialized = 1;

        return;
    }

    QueryPerformanceCounter(
        &now);

    elapsed =
        (double)(now.QuadPart -
                 frameStart.QuadPart) /
        (double)
            performanceFrequency.QuadPart;

    /*
       รอจนกว่าจะครบ 1/60 วินาที
    */

    while (elapsed < targetTime)
    {
        Sleep(1);

        QueryPerformanceCounter(
            &now);

        elapsed =
            (double)(now.QuadPart -
                     frameStart.QuadPart) /
            (double)
                performanceFrequency.QuadPart;
    }

    frameStart = now;
}

/* =========================================================
   CONSOLE
   ========================================================= */

void initConsole()
{
    CONSOLE_CURSOR_INFO cursorInfo;

    consoleFront =
        GetStdHandle(
            STD_OUTPUT_HANDLE);

    /*
       =====================================================
       Cursor
       =====================================================
    */

    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(
        consoleFront,
        &cursorInfo);

    /*
       =====================================================
       Create second buffer
       =====================================================
    */

    consoleBack =
        CreateConsoleScreenBuffer(
            GENERIC_READ |
                GENERIC_WRITE,
            FILE_SHARE_READ |
                FILE_SHARE_WRITE,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL);

    if (consoleBack ==
        INVALID_HANDLE_VALUE)
    {
        exit(1);
    }

    /*
       =====================================================
       Buffer size
       =====================================================
    */

    SetConsoleScreenBufferSize(
        consoleFront,
        bufferSize);

    SetConsoleScreenBufferSize(
        consoleBack,
        bufferSize);

    /*
       =====================================================
       Window size
       =====================================================
    */

    SetConsoleWindowInfo(
        consoleFront,
        TRUE,
        &screenRect);

    SetConsoleWindowInfo(
        consoleBack,
        TRUE,
        &screenRect);

    /*
       =====================================================
       Active buffer
       =====================================================
    */

    SetConsoleActiveScreenBuffer(
        consoleFront);

    SetConsoleTitleA(
        "POOP RUNNER");
}

/* =========================================================
   SHUTDOWN CONSOLE
   ========================================================= */

void shutdownConsole()
{
    /*
       กลับไปใช้ Front Buffer
    */

    SetConsoleActiveScreenBuffer(
        consoleFront);

    /*
       แสดง Cursor กลับ
    */

    CONSOLE_CURSOR_INFO cursorInfo;

    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = TRUE;

    SetConsoleCursorInfo(
        consoleFront,
        &cursorInfo);

    if (consoleBack !=
        INVALID_HANDLE_VALUE)
    {
        CloseHandle(
            consoleBack);
    }
}

/* =========================================================
   COLOR HELPER
   ========================================================= */

WORD makeColor(int color)
{
    return (WORD)color;
}

/* =========================================================
   FRAME BUFFER CLEAR
   ========================================================= */

void clearFrame()
{
    int i;

    for (i = 0;
         i < SCREEN_W * SCREEN_H;
         i++)
    {
        frameBuffer[i]
            .Char
            .AsciiChar = ' ';

        frameBuffer[i]
            .Attributes =
            COLOR_WHITE;
    }
}

/* =========================================================
   PUT CHAR
   ========================================================= */

void putChar(
    int x,
    int y,
    char c,
    int colorValue)
{
    int index;

    if (x < 0 ||
        x >= SCREEN_W ||
        y < 0 ||
        y >= SCREEN_H)
    {
        return;
    }

    index =
        y * SCREEN_W + x;

    frameBuffer[index]
        .Char
        .AsciiChar = c;

    frameBuffer[index]
        .Attributes =
        makeColor(colorValue);
}

/* =========================================================
   PUT TEXT
   ========================================================= */

void putText(
    int x,
    int y,
    const char *text,
    int colorValue)
{
    int i = 0;

    while (text[i] != '\0')
    {
        putChar(
            x + i,
            y,
            text[i],
            colorValue);

        i++;
    }
}

/* =========================================================
   PRESENT FRAME
   ========================================================= */

void presentFrame()
{
    /*
       เขียน Frame ทั้งหมดลง Back Buffer
    */

    WriteConsoleOutputA(
        consoleBack,
        frameBuffer,
        bufferSize,
        bufferPosition,
        &screenRect);

    /*
       สลับ Back Buffer
       ให้กลายเป็นหน้าจอที่แสดงอยู่
    */

    SetConsoleActiveScreenBuffer(
        consoleBack);

    /*
       Swap Handle
    */

    {
        HANDLE temp;

        temp = consoleFront;

        consoleFront = consoleBack;

        consoleBack = temp;
    }
}

/* =========================================================
   RESET OBJECTS
   ========================================================= */

void clearObjects()
{
    int i;

    for (i = 0;
         i < MAX;
         i++)
    {
        obs[i].active = 0;
        coins[i].active = 0;
    }
}

/* =========================================================
   RESET GAME
   ========================================================= */

void resetGame()
{
    p.x = 8;

    /*
       พื้น = G
       Player สูง 3

       ดังนั้น Player top:
       G - PLAYER_HEIGHT
    */

    p.y =
        (float)(G - PLAYER_HEIGHT);

    p.vy = 0.0f;

    p.hp = 10;

    p.score = 0;

    p.jumps = 0;

    p.side = FLOOR;

    p.flashTimer = 0.0f;

    p.invincibleTimer = 0.0f;

    /*
       Timer
    */

    scoreTimer = 0.0f;

    obstacleSpawnTimer = 0.8f;

    coinSpawnTimer = 0.3f;

    gameOverState = 0;

    clearObjects();
}

/* =========================================================
   GAME SPEED
   ========================================================= */

float getGameSpeed()
{
    float speed;

    /*
       ตัวอย่าง:

       Score 0    = 10
       Score 25   = 15
       Score 50   = 20
       Score 75   = 25
       Score 100  = 30
    */

    speed =
        START_SPEED +
        p.score * SPEED_PER_SCORE;

    if (speed > MAX_SPEED)
    {
        speed = MAX_SPEED;
    }

    return speed;
}

/* =========================================================
   INPUT
   ========================================================= */

void switchSide(int side)
{
    /*
       ถ้าอยู่ด้านเดียวกันอยู่แล้ว
       ไม่ต้องทำอะไร
    */

    if (p.side == side)
    {
        return;
    }

    p.side = side;

    /*
       ยกเลิก Momentum เดิม
    */

    p.vy = 0.0f;

    p.jumps = 0;

    /*
       =====================================================
       FLOOR
       =====================================================
    */

    if (side == FLOOR)
    {
        p.y =
            (float)(G - PLAYER_HEIGHT);
    }

    /*
       =====================================================
       CEILING
       =====================================================
    */

    else
    {
        p.y = 1.0f;
    }
}

/* =========================================================
   JUMP
   ========================================================= */

void jump()
{
    /*
       กระโดดได้สูงสุด 3 ครั้ง
    */

    if (p.jumps >= 3)
    {
        return;
    }

    /*
       FLOOR

       กระโดดขึ้น
       y ลดลง
    */

    if (p.side == FLOOR)
    {
        p.vy = -JUMP_FORCE;
    }

    /*
       CEILING

       กระโดดลง
       y เพิ่มขึ้น
    */

    else
    {
        p.vy = JUMP_FORCE;
    }

    p.jumps++;
}

/* =========================================================
   INPUT HANDLER
   ========================================================= */

void handleInput()
{
    int key;

    /*
       รับ Input ได้หลายปุ่มใน Frame เดียว
    */

    while (_kbhit())
    {
        key = _getch();

        /*
           =================================================
           GAME OVER
           =================================================
        */

        if (gameOverState)
        {
            if (key == 'r' ||
                key == 'R')
            {
                resetGame();

                /*
                   Reset QPC
                   ป้องกัน dt กระโดด
                */

                QueryPerformanceCounter(
                    &previousTime);

                return;
            }

            if (key == 'q' ||
                key == 'Q' ||
                key == 27)
            {
                running = 0;

                return;
            }

            continue;
        }

        /*
           =================================================
           SPACE
           =================================================
        */

        if (key == ' ')
        {
            jump();

            continue;
        }

        /*
           =================================================
           W
           =================================================
        */

        if (key == 'w' ||
            key == 'W')
        {
            switchSide(CEILING);

            continue;
        }

        /*
           =================================================
           S
           =================================================
        */

        if (key == 's' ||
            key == 'S')
        {
            switchSide(FLOOR);

            continue;
        }

        /*
           =================================================
           Arrow Keys
           =================================================
        */

        if (key == 0 ||
            key == 224)
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

            else if (key == 80)
            {
                switchSide(FLOOR);
            }

            continue;
        }

        /*
           =================================================
           Q
           =================================================
        */

        if (key == 'q' ||
            key == 'Q' ||
            key == 27)
        {
            running = 0;

            return;
        }
    }
}

/* =========================================================
   PHYSICS
   ========================================================= */

void updatePhysics()
{
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

        p.vy +=
            GRAVITY *
            (float)deltaTime;

        /*
           Position
        */

        p.y +=
            p.vy *
            (float)deltaTime;

        /*
           ป้องกันทะลุเพดาน
        */

        if (p.y < 1.0f)
        {
            p.y = 1.0f;

            p.vy = 0.0f;
        }

        /*
           พื้น
        */

        if (p.y >=
            (float)(G - PLAYER_HEIGHT))
        {
            p.y =
                (float)(G - PLAYER_HEIGHT);

            p.vy = 0.0f;

            p.jumps = 0;
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

           เพราะตัวละครกลับด้าน
        */

        p.vy -=
            GRAVITY *
            (float)deltaTime;

        /*
           Position
        */

        p.y +=
            p.vy *
            (float)deltaTime;

        /*
           เพดาน
        */

        if (p.y <= 1.0f)
        {
            p.y = 1.0f;

            p.vy = 0.0f;

            p.jumps = 0;
        }

        /*
           ป้องกันทะลุพื้น
        */

        if (p.y >
            (float)(G - PLAYER_HEIGHT))
        {
            p.y =
                (float)(G - PLAYER_HEIGHT);

            p.vy = 0.0f;
        }
    }
}

/* =========================================================
   UPDATE DAMAGE TIMER
   ========================================================= */

void updateTimers()
{
    if (p.flashTimer > 0.0f)
    {
        p.flashTimer -=
            (float)deltaTime;

        if (p.flashTimer < 0.0f)
        {
            p.flashTimer = 0.0f;
        }
    }

    if (p.invincibleTimer > 0.0f)
    {
        p.invincibleTimer -=
            (float)deltaTime;

        if (p.invincibleTimer < 0.0f)
        {
            p.invincibleTimer = 0.0f;
        }
    }
}

/* =========================================================
   IS FLASHING
   ========================================================= */

int isPlayerFlashing()
{
    if (p.flashTimer <= 0.0f)
    {
        return 0;
    }

    /*
       เปลี่ยนสีทุก 0.08 sec
    */

    int phase =
        (int)(p.flashTimer * 12.5f);

    return phase % 2 == 0;
}

/* =========================================================
   IS INVINCIBLE
   ========================================================= */

int isPlayerInvincible()
{
    return p.invincibleTimer > 0.0f;
}

/* =========================================================
   SPAWN OBSTACLE
   ========================================================= */

void spawnObstacle()
{
    int i;

    /*
       Timer หมดแล้วจึง Spawn
    */

    for (i = 0;
         i < MAX;
         i++)
    {
        if (!obs[i].active)
        {
            obs[i].x =
                (float)(W - 1);

            obs[i].side =
                rand() % 2;

            /*
               Width
            */

            obs[i].width =
                1 + rand() % 4;

            /*
               Height
            */

            obs[i].height =
                1 + rand() % 3;

            /*
               =================================================
               FLOOR
               =================================================
            */

            if (obs[i].side == FLOOR)
            {
                obs[i].y =
                    G -
                    obs[i].height;
            }

            /*
               =================================================
               CEILING
               =================================================
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

    for (i = 0;
         i < MAX;
         i++)
    {
        if (!coins[i].active)
        {
            coins[i].x =
                (float)(W - 1);

            coins[i].side =
                rand() % 2;

            /*
               FLOOR
            */

            if (coins[i].side == FLOOR)
            {
                coins[i].y =
                    G -
                    3 -
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
   SPAWN UPDATE
   ========================================================= */

void updateSpawning()
{
    /*
       =====================================================
       OBSTACLE
       =====================================================
    */

    obstacleSpawnTimer -=
        (float)deltaTime;

    if (obstacleSpawnTimer <= 0.0f)
    {
        spawnObstacle();

        /*
           ความเร็วสูงขึ้น
           Spawn ถี่ขึ้นเล็กน้อย
        */

        float difficulty =
            getGameSpeed() /
            MAX_SPEED;

        float minTime =
            0.55f -
            difficulty * 0.20f;

        float maxTime =
            1.10f -
            difficulty * 0.25f;

        if (minTime < 0.35f)
            minTime = 0.35f;

        if (maxTime < 0.60f)
            maxTime = 0.60f;

        float random01 =
            (float)rand() /
            (float)RAND_MAX;

        obstacleSpawnTimer =
            minTime +
            random01 *
                (maxTime - minTime);
    }

    /*
       =====================================================
       COIN
       =====================================================
    */

    coinSpawnTimer -=
        (float)deltaTime;

    if (coinSpawnTimer <= 0.0f)
    {
        spawnCoin();

        coinSpawnTimer =
            0.45f +
            ((float)rand() /
             (float)RAND_MAX) *
                0.50f;
    }
}

/* =========================================================
   MOVE OBJECTS
   ========================================================= */

void updateObjects()
{
    int i;

    float speed =
        getGameSpeed();

    /*
       =====================================================
       MOVE
       =====================================================
    */

    for (i = 0;
         i < MAX;
         i++)
    {
        /*
           OBSTACLE
        */

        if (obs[i].active)
        {
            obs[i].x -=
                speed *
                (float)deltaTime;

            /*
               ลบเมื่อออกจากจอ
            */

            if (obs[i].x +
                    obs[i].width <
                0.0f)
            {
                obs[i].active = 0;
            }
        }

        /*
           COIN
        */

        if (coins[i].active)
        {
            coins[i].x -=
                speed *
                (float)deltaTime;

            if (coins[i].x < 0.0f)
            {
                coins[i].active = 0;
            }
        }
    }
}

/* =========================================================
   RECTANGLE COLLISION
   ========================================================= */

int rectangleCollision(
    int ax,
    int ay,
    int aw,
    int ah,

    int bx,
    int by,
    int bw,
    int bh)
{
    if (ax + aw <= bx)
        return 0;

    if (ax >= bx + bw)
        return 0;

    if (ay + ah <= by)
        return 0;

    if (ay >= by + bh)
        return 0;

    return 1;
}

/* =========================================================
   PLAYER / OBSTACLE COLLISION
   ========================================================= */

int playerHitObstacle(
    Object *o)
{
    int playerX;
    int playerY;

    int objectX;
    int objectY;

    playerX =
        p.x +
        HITBOX_X;

    playerY =
        (int)p.y;

    objectX =
        (int)o->x;

    objectY =
        o->y;

    return rectangleCollision(
        playerX,
        playerY,
        HITBOX_WIDTH,
        PLAYER_HEIGHT,

        objectX,
        objectY,
        o->width,
        o->height);
}

/* =========================================================
   PLAYER / COIN COLLISION
   ========================================================= */

int playerHitCoin(
    Object *coin)
{
    int coinX =
        (int)coin->x;

    int coinY =
        coin->y;

    return rectangleCollision(
        p.x,
        (int)p.y,
        PLAYER_WIDTH,
        PLAYER_HEIGHT,

        coinX,
        coinY,
        1,
        1);
}

/* =========================================================
   COLLISION UPDATE
   ========================================================= */

void updateCollision()
{
    int i;

    /*
       =====================================================
       OBSTACLE
       =====================================================
    */

    if (!isPlayerInvincible())
    {
        for (i = 0;
             i < MAX;
             i++)
        {
            if (!obs[i].active)
                continue;

            /*
               คนละด้านไม่ชน
            */

            if (obs[i].side !=
                p.side)
            {
                continue;
            }

            if (playerHitObstacle(
                    &obs[i]))
            {
                /*
                   Damage
                */

                p.hp--;

                /*
                   Flash
                */

                p.flashTimer =
                    FLASH_TIME;

                /*
                   Invincible
                */

                p.invincibleTimer =
                    INVINCIBLE_TIME;

                /*
                   ลบ Object
                */

                obs[i].active = 0;

                /*
                   ถ้า HP หมด
                */

                if (p.hp <= 0)
                {
                    gameOverState = 1;
                }

                /*
                   ชนครั้งเดียวต่อ Frame
                */

                break;
            }
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

        if (coins[i].side !=
            p.side)
        {
            continue;
        }

        if (playerHitCoin(
                &coins[i]))
        {
            /*
               Coin = +100
            */

            p.score += 100;

            coins[i].active = 0;
        }
    }
}

/* =========================================================
   SCORE
   ========================================================= */

void updateScore()
{
    scoreTimer +=
        (float)deltaTime;

    /*
       ทุก 1 วินาที
       Score +1
    */

    while (scoreTimer >= 1.0f)
    {
        scoreTimer -= 1.0f;

        p.score++;
    }
}

/* =========================================================
   DRAW OBSTACLE
   ========================================================= */

void drawObstacle(
    Object *o)
{
    int xx;
    int yy;

    int ox =
        (int)o->x;

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
            int x =
                ox + xx;

            int y =
                o->y + yy;

            if (x >= 0 &&
                x < W &&
                y >= 0 &&
                y < H)
            {
                putChar(
                    x,
                    y,
                    '#',
                    COLOR_RED);
            }
        }
    }

    /*
       =====================================================
       FLOOR SPIKES
       =====================================================
    */

    if (o->side == FLOOR)
    {
        for (xx = 0;
             xx < o->width;
             xx++)
        {
            int x =
                ox + xx;

            int y =
                o->y - 1;

            if (x >= 0 &&
                x < W &&
                y >= 0 &&
                y < H)
            {
                putChar(
                    x,
                    y,
                    '^',
                    COLOR_MAGENTA);
            }
        }
    }

    /*
       =====================================================
       CEILING SPIKES
       =====================================================
    */

    else
    {
        for (xx = 0;
             xx < o->width;
             xx++)
        {
            int x =
                ox + xx;

            int y =
                o->y +
                o->height;

            if (x >= 0 &&
                x < W &&
                y >= 0 &&
                y < H)
            {
                putChar(
                    x,
                    y,
                    'v',
                    COLOR_MAGENTA);
            }
        }
    }
}

/* =========================================================
   DRAW COIN
   ========================================================= */

void drawCoin(
    Object *coin)
{
    int x =
        (int)coin->x;

    int y =
        coin->y;

    if (x >= 0 &&
        x < W &&
        y >= 0 &&
        y < H)
    {
        putChar(
            x,
            y,
            '$',
            COLOR_YELLOW);
    }
}

/* =========================================================
   PLAYER CHARACTER
   ========================================================= */

void drawPlayerFloor()
{
    int px =
        p.x;

    int py =
        (int)p.y;

    int playerColor =
        isPlayerFlashing()
            ? COLOR_RED
            : COLOR_NORMAL;

    /*
          /\
         (0w0)
        (______)
    */

    putChar(
        px + 2,
        py,
        '/',
        playerColor);

    putChar(
        px + 5,
        py,
        '\\',
        playerColor);

    putChar(
        px + 1,
        py + 1,
        '(',
        playerColor);

    putChar(
        px + 3,
        py + 1,
        '0',
        playerColor);

    putChar(
        px + 4,
        py + 1,
        'w',
        playerColor);

    putChar(
        px + 5,
        py + 1,
        '0',
        playerColor);

    putChar(
        px + 6,
        py + 1,
        ')',
        playerColor);

    putChar(
        px,
        py + 2,
        '(',
        playerColor);

    putChar(
        px + 1,
        py + 2,
        '_',
        playerColor);

    putChar(
        px + 2,
        py + 2,
        '_',
        playerColor);

    putChar(
        px + 3,
        py + 2,
        '_',
        playerColor);

    putChar(
        px + 4,
        py + 2,
        '_',
        playerColor);

    putChar(
        px + 5,
        py + 2,
        '_',
        playerColor);

    putChar(
        px + 6,
        py + 2,
        '_',
        playerColor);

    putChar(
        px + 7,
        py + 2,
        ')',
        playerColor);
}

/* =========================================================
   PLAYER CEILING
   ========================================================= */

void drawPlayerCeiling()
{
    int px =
        p.x;

    int py =
        (int)p.y;

    int playerColor =
        isPlayerFlashing()
            ? COLOR_RED
            : COLOR_NORMAL;

    /*
       (______)
        (0w0)
          \/
    */

    putChar(
        px,
        py,
        '(',
        playerColor);

    putChar(
        px + 1,
        py,
        '_',
        playerColor);

    putChar(
        px + 2,
        py,
        '_',
        playerColor);

    putChar(
        px + 3,
        py,
        '_',
        playerColor);

    putChar(
        px + 4,
        py,
        '_',
        playerColor);

    putChar(
        px + 5,
        py,
        '_',
        playerColor);

    putChar(
        px + 6,
        py,
        '_',
        playerColor);

    putChar(
        px + 7,
        py,
        ')',
        playerColor);

    putChar(
        px + 1,
        py + 1,
        '(',
        playerColor);

    putChar(
        px + 3,
        py + 1,
        '0',
        playerColor);

    putChar(
        px + 4,
        py + 1,
        'w',
        playerColor);

    putChar(
        px + 5,
        py + 1,
        '0',
        playerColor);

    putChar(
        px + 6,
        py + 1,
        ')',
        playerColor);

    putChar(
        px + 2,
        py + 2,
        '\\',
        playerColor);

    putChar(
        px + 5,
        py + 2,
        '/',
        playerColor);
}

/* =========================================================
   DRAW PLAYER
   ========================================================= */

void drawPlayer()
{
    if (p.side == FLOOR)
    {
        drawPlayerFloor();
    }
    else
    {
        drawPlayerCeiling();
    }
}

/* =========================================================
   DRAW MAP
   ========================================================= */

void drawMap()
{
    int x;

    /*
       TOP
    */

    for (x = 0;
         x < W;
         x++)
    {
        putChar(
            x,
            0,
            '=',
            COLOR_WHITE);
    }

    /*
       FLOOR
    */

    for (x = 0;
         x < W;
         x++)
    {
        putChar(
            x,
            G,
            '=',
            COLOR_WHITE);
    }
}

/* =========================================================
   DRAW UI
   ========================================================= */

void drawUI()
{
    char text[256];

    /*
       =====================================================
       HEADER
       =====================================================
    */

    putText(
        0,
        H + 1,
        "POOP RUNNER",
        COLOR_YELLOW);

    sprintf(
        text,
        "Score:%d",
        p.score);

    putText(
        13,
        H + 1,
        text,
        COLOR_CYAN);

    sprintf(
        text,
        "HP:%d",
        p.hp);

    putText(
        25,
        H + 1,
        text,
        COLOR_RED);

    sprintf(
        text,
        "Speed:%.1f",
        getGameSpeed());

    putText(
        34,
        H + 1,
        text,
        COLOR_MAGENTA);

    if (p.side == FLOOR)
    {
        putText(
            50,
            H + 1,
            "DOWN",
            COLOR_GREEN);
    }
    else
    {
        putText(
            50,
            H + 1,
            "UP",
            COLOR_GREEN);
    }

    /*
       =====================================================
       CONTROLS
       =====================================================
    */

    putText(
        0,
        H + 3,
        "SPACE = Jump | W/UP = UP | S/DOWN = DOWN | Q = Quit",
        COLOR_WHITE);

    putText(
        0,
        H + 4,
        "Collect $ = +100 Score | Speed increases with Score",
        COLOR_WHITE);

    /*
       =====================================================
       HIT
       =====================================================
    */

    if (isPlayerFlashing())
    {
        putText(
            65,
            H + 1,
            "!!! HIT !!!",
            COLOR_RED);
    }

    /*
       =====================================================
       INVINCIBLE
       =====================================================
    */

    if (isPlayerInvincible())
    {
        putText(
            65,
            H + 2,
            "INVINCIBLE",
            COLOR_GREEN);
    }
}

/* =========================================================
   GAME OVER SCREEN
   ========================================================= */

void drawGameOver()
{
    int centerX = 50;

    putText(
        centerX,
        7,
        "===== GAME OVER =====",
        COLOR_RED);

    {
        char scoreText[64];

        sprintf(
            scoreText,
            "Score : %d",
            p.score);

        putText(
            centerX + 5,
            9,
            scoreText,
            COLOR_YELLOW);
    }

    putText(
        centerX + 5,
        11,
        "R = Restart",
        COLOR_CYAN);

    putText(
        centerX + 5,
        12,
        "Q = Quit",
        COLOR_WHITE);
}

/* =========================================================
   DRAW EVERYTHING
   ========================================================= */

void draw()
{
    int i;

    /*
       =====================================================
       CLEAR
       =====================================================
    */

    clearFrame();

    /*
       =====================================================
       MAP
       =====================================================
    */

    drawMap();

    /*
       =====================================================
       OBJECTS
       =====================================================
    */

    for (i = 0;
         i < MAX;
         i++)
    {
        if (obs[i].active)
        {
            drawObstacle(
                &obs[i]);
        }

        if (coins[i].active)
        {
            drawCoin(
                &coins[i]);
        }
    }

    /*
       =====================================================
       PLAYER
       =====================================================
    */

    if (!gameOverState)
    {
        drawPlayer();
    }

    /*
       =====================================================
       UI
       =====================================================
    */

    drawUI();

    /*
       =====================================================
       GAME OVER
       =====================================================
    */

    if (gameOverState)
    {
        drawGameOver();
    }

    /*
       =====================================================
       PRESENT
       =====================================================
    */

    presentFrame();
}

/* =========================================================
   UPDATE GAME
   ========================================================= */

void updateGame()
{
    if (gameOverState)
    {
        return;
    }

    /*
       Input
    */

    handleInput();

    if (!running ||
        gameOverState)
    {
        return;
    }

    /*
       Physics
    */

    updatePhysics();

    /*
       Object movement
    */

    updateObjects();

    /*
       Spawn
    */

    updateSpawning();

    /*
       Collision
    */

    updateCollision();

    /*
       Score
    */

    updateScore();

    /*
       Damage timers
    */

    updateTimers();
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
       Delta Time
    */

    initDeltaTime();

    /*
       Game
    */

    resetGame();

    /*
       =====================================================
       MAIN LOOP
       =====================================================
    */

    while (running)
    {
        /*
           =================================================
           DELTA TIME
           =================================================
        */

        updateDeltaTime();

        /*
           =================================================
           UPDATE
           =================================================
        */

        updateGame();

        /*
           =================================================
           DRAW
           =================================================
        */

        draw();

        /*
           =================================================
           FRAME LIMIT
           =================================================
        */

        limitFrameRate();
    }

    /*
       =====================================================
       EXIT
       =====================================================
    */

    shutdownConsole();

    return 0;
}