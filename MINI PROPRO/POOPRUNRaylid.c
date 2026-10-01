#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define W 120
#define H 12
#define G 8
#define MAX 12

#define FLOOR 0
#define CEILING 1

#define CELL 40
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

/* Physics */
#define JUMP_FORCE 2.0f
#define GRAVITY 0.7f

typedef struct
{
    int x;

    float y;
    float vy;

    int hp;
    int score;
    int coin;

    int jumps;
    int side;

} Player;

typedef struct
{
    int x;
    int y;

    int side;
    int active;

} Object;

Player p;

Object obs[MAX];
Object coins[MAX];

/* =========================================================
   RESET
   ========================================================= */

void ResetGame(void)
{
    p.x = 8;

    p.y = G - 1;
    p.vy = 0.0f;

    p.hp = 10;
    p.score = 0;
    p.coin = 0;

    p.jumps = 0;
    p.side = FLOOR;

    for (int i = 0; i < MAX; i++)
    {
        obs[i].active = 0;
        coins[i].active = 0;
    }
}

/* =========================================================
   SWITCH FLOOR / CEILING
   ========================================================= */

void SwitchSide(int side)
{
    if (p.side == side)
        return;

    p.side = side;

    p.vy = 0.0f;

    p.jumps = 0;

    if (side == FLOOR)
    {
        p.y = G - 1;
    }
    else
    {
        p.y = 1;
    }
}

/* =========================================================
   JUMP
   ========================================================= */

void Jump(void)
{
    /*
       Maximum 3 jumps
    */

    if (p.jumps >= 3)
        return;

    if (p.side == FLOOR)
    {
        p.vy = -JUMP_FORCE;
    }
    else
    {
        p.vy = JUMP_FORCE;
    }

    p.jumps++;
}

/* =========================================================
   INPUT
   ========================================================= */

void HandleInput(void)
{
    /*
       Jump
    */

    if (IsKeyPressed(KEY_SPACE))
    {
        Jump();
    }

    /*
       Go ceiling
    */

    if (IsKeyPressed(KEY_W) ||
        IsKeyPressed(KEY_UP))
    {
        SwitchSide(CEILING);
    }

    /*
       Go floor
    */

    if (IsKeyPressed(KEY_S) ||
        IsKeyPressed(KEY_DOWN))
    {
        SwitchSide(FLOOR);
    }
}

/* =========================================================
   PHYSICS
   ========================================================= */

void UpdatePhysics(void)
{
    /*
       Move vertically
    */

    p.y += p.vy;

    /*
       FLOOR
    */

    if (p.side == FLOOR)
    {
        /*
           Gravity
        */

        p.vy += GRAVITY;

        /*
           Hit floor
        */

        if (p.y >= G - 1)
        {
            p.y = G - 1;

            p.vy = 0.0f;

            p.jumps = 0;
        }
    }

    /*
       CEILING
    */

    else
    {
        /*
           Gravity toward ceiling
        */

        p.vy -= GRAVITY;

        /*
           Hit ceiling
        */

        if (p.y <= 1)
        {
            p.y = 1;

            p.vy = 0.0f;

            p.jumps = 0;
        }
    }
}

/* =========================================================
   SPAWN OBJECTS
   ========================================================= */

void SpawnObjects(void)
{
    /*
       OBSTACLE
    */

    if (GetRandomValue(0, 19) == 0)
    {
        for (int i = 0; i < MAX; i++)
        {
            if (!obs[i].active)
            {
                obs[i].x = W - 1;

                obs[i].side =
                    GetRandomValue(0, 1);

                if (obs[i].side == FLOOR)
                {
                    obs[i].y = G - 1;
                }
                else
                {
                    obs[i].y = 1;
                }

                obs[i].active = 1;

                break;
            }
        }
    }

    /*
       COIN
    */

    if (GetRandomValue(0, 24) == 0)
    {
        for (int i = 0; i < MAX; i++)
        {
            if (!coins[i].active)
            {
                coins[i].x = W - 1;

                coins[i].side =
                    GetRandomValue(0, 1);

                if (coins[i].side == FLOOR)
                {
                    coins[i].y =
                        G - 3 -
                        GetRandomValue(0, 1);
                }
                else
                {
                    coins[i].y =
                        3 +
                        GetRandomValue(0, 1);
                }

                coins[i].active = 1;

                break;
            }
        }
    }
}

/* =========================================================
   MOVE OBJECTS
   ========================================================= */

void MoveObjects(void)
{
    static float timer = 0.0f;

    timer += GetFrameTime();

    /*
       ความเร็วเริ่มต้น
       0.08 = ช้า
       0.06 = เร็วขึ้น
       0.045 = เร็ว
       0.035 = เร็วมาก
    */

    float speed = 0.1f;

    /*
       ยิ่งคะแนนสูง เกมยิ่งเร็ว
    */

    speed -= (p.score / 50000.0f);

    /*
       จำกัดความเร็วสูงสุด
    */

    if (speed < 0.025f)
        speed = 0.025f;

    if (timer < speed)
        return;

    timer = 0.0f;

    for (int i = 0; i < MAX; i++)
    {
        if (obs[i].active)
        {
            obs[i].x--;

            if (obs[i].x < 0)
                obs[i].active = 0;
        }

        if (coins[i].active)
        {
            coins[i].x--;

            if (coins[i].x < 0)
                coins[i].active = 0;
        }
    }
}

/* =========================================================
   COLLISION
   ========================================================= */

void CheckCollisions(void)
{
    for (int i = 0; i < MAX; i++)
    {
        /*
           Obstacle collision
        */

        if (obs[i].active &&
            obs[i].x == p.x &&
            obs[i].y == (int)p.y &&
            obs[i].side == p.side)
        {
            p.hp--;

            obs[i].active = 0;
        }

        /*
           Coin collision
        */

        if (coins[i].active &&
            coins[i].x == p.x &&
            abs(coins[i].y - (int)p.y) <= 1 &&
            coins[i].side == p.side)
        {
            p.coin++;

            p.score += 100;

            coins[i].active = 0;
        }
    }

    /*
       Score over time
    */

    p.score++;
}

/* =========================================================
   DRAW BACKGROUND
   ========================================================= */

void DrawGameBackground(void)
{
    /*
       Background
    */

    ClearBackground(
        (Color){10, 10, 25, 255});

    /*
       Ceiling
    */

    DrawRectangle(
        0,
        0,
        SCREEN_WIDTH,
        CELL,
        DARKPURPLE);

    /*
       Floor
    */

    DrawRectangle(
        0,
        G * CELL,
        SCREEN_WIDTH,
        CELL,
        DARKGREEN);

    /*
       Ceiling line
    */

    DrawLine(
        0,
        CELL,
        SCREEN_WIDTH,
        CELL,
        PURPLE);

    /*
       Floor line
    */

    DrawLine(
        0,
        G * CELL,
        SCREEN_WIDTH,
        G * CELL,
        GREEN);
}

/* =========================================================
   DRAW OBJECTS
   ========================================================= */

void DrawObjects(void)
{
    /*
       Obstacles
    */

    for (int i = 0; i < MAX; i++)
    {
        if (!obs[i].active)
            continue;

        int x = obs[i].x * CELL;

        int y = obs[i].y * CELL;

        /*
           Obstacle body
        */

        DrawRectangle(
            x + 5,
            y + 5,
            CELL - 10,
            CELL - 10,
            RED);

        /*
           Spike
        */

        if (obs[i].side == FLOOR)
        {
            DrawTriangle(
                (Vector2){
                    x + CELL / 2,
                    y},

                (Vector2){
                    x + 5,
                    y + CELL},

                (Vector2){
                    x + CELL - 5,
                    y + CELL},

                MAROON);
        }
        else
        {
            DrawTriangle(
                (Vector2){
                    x + 5,
                    y},

                (Vector2){
                    x + CELL - 5,
                    y},

                (Vector2){
                    x + CELL / 2,
                    y + CELL},

                MAROON);
        }
    }

    /*
       Coins
    */

    for (int i = 0; i < MAX; i++)
    {
        if (!coins[i].active)
            continue;

        int x =
            coins[i].x * CELL +
            CELL / 2;

        int y =
            coins[i].y * CELL +
            CELL / 2;

        DrawCircle(
            x,
            y,
            CELL / 3,
            GOLD);

        DrawCircleLines(
            x,
            y,
            CELL / 3,
            ORANGE);
    }
}

/* =========================================================
   DRAW PLAYER
   ========================================================= */

void DrawPlayer(void)
{
    int x =
        p.x * CELL +
        CELL / 2;

    int y =
        (int)(p.y * CELL +
              CELL / 2);

    /*
       Body
    */

    DrawCircle(
        x,
        y,
        CELL / 2 - 4,
        SKYBLUE);

    /*
       Eyes
    */

    DrawCircle(
        x - 8,
        y - 5,
        4,
        BLACK);

    DrawCircle(
        x + 8,
        y - 5,
        4,
        BLACK);

    /*
       Mouth
    */

    DrawLine(
        x - 8,
        y + 8,
        x + 8,
        y + 8,
        BLACK);

    /*
       Jump effect
    */

    if (fabsf(p.vy) > 0.5f)
    {
        DrawCircle(
            x - 12,
            y + 15,
            3,
            WHITE);

        DrawCircle(
            x + 12,
            y + 15,
            3,
            WHITE);
    }
}

/* =========================================================
   DRAW UI
   ========================================================= */

void DrawUI(void)
{
    DrawRectangle(
        0,
        G * CELL + CELL,
        SCREEN_WIDTH,
        100,
        (Color){20, 20, 35, 255});

    /*
       Title
    */

    DrawText(
        "POOP RUNNER",
        20,
        G * CELL + CELL + 15,
        28,
        YELLOW);

    char text[128];

    /*
       Score
    */

    sprintf(
        text,
        "Score: %d",
        p.score);

    DrawText(
        text,
        270,
        G * CELL + CELL + 18,
        22,
        SKYBLUE);

    /*
       Coins
    */

    sprintf(
        text,
        "Coins: %d",
        p.coin);

    DrawText(
        text,
        430,
        G * CELL + CELL + 18,
        22,
        GOLD);

    /*
       HP
    */

    sprintf(
        text,
        "HP: %d",
        p.hp);

    DrawText(
        text,
        600,
        G * CELL + CELL + 18,
        22,
        RED);

    /*
       Side
    */

    sprintf(
        text,
        "Side: %s",
        p.side == FLOOR
            ? "DOWN"
            : "UP");

    DrawText(
        text,
        720,
        G * CELL + CELL + 18,
        22,
        GREEN);

    /*
       Controls
    */

    DrawText(
        "SPACE: Jump    "
        "W/UP: Ceiling    "
        "S/DOWN: Floor    "
        "ESC: Quit",

        20,
        G * CELL + CELL + 55,

        18,

        LIGHTGRAY);
}

/* =========================================================
   DRAW GAME
   ========================================================= */

void DrawGame(void)
{
    BeginDrawing();

    DrawGameBackground();

    DrawObjects();

    DrawPlayer();

    DrawUI();

    EndDrawing();
}

/* =========================================================
   GAME OVER
   ========================================================= */

int GameOverScreen(void)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(
            (Color){10, 10, 20, 255});

        /*
           Title
        */

        DrawText(
            "GAME OVER!",
            430,
            150,
            55,
            RED);

        char text[100];

        /*
           Score
        */

        sprintf(
            text,
            "Score: %d",
            p.score);

        DrawText(
            text,
            490,
            240,
            30,
            WHITE);

        /*
           Coins
        */

        sprintf(
            text,
            "Coins: %d",
            p.coin);

        DrawText(
            text,
            490,
            280,
            30,
            GOLD);

        /*
           Restart
        */

        DrawText(
            "R = Restart",
            475,
            360,
            25,
            SKYBLUE);

        /*
           Quit
        */

        DrawText(
            "ESC = Quit",
            480,
            400,
            25,
            LIGHTGRAY);

        EndDrawing();

        /*
           Restart
        */

        if (IsKeyPressed(KEY_R))
        {
            ResetGame();

            return 1;
        }

        /*
           Quit
        */

        if (WindowShouldClose() ||
            IsKeyPressed(KEY_ESCAPE))
        {
            return 0;
        }
    }

    return 0;
}

/* =========================================================
   MAIN
   ========================================================= */

int main(void)
{
    /*
       Random
    */

    srand(
        (unsigned int)time(NULL));

    /*
       Raylib window
    */

    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "POOP RUNNER - Raylib");

    /*
       60 FPS
    */

    SetTargetFPS(60);

    /*
       Reset game
    */

    ResetGame();

    /*
       Main loop
    */

    while (!WindowShouldClose())
    {
        /*
           Input
        */

        HandleInput();

        /*
           ESC
        */

        if (IsKeyPressed(KEY_ESCAPE))
            break;

        /*
           Game over
        */

        if (p.hp <= 0)
        {
            if (!GameOverScreen())
                break;

            continue;
        }

        /*
           Physics
        */

        UpdatePhysics();

        /*
           Spawn
        */

        SpawnObjects();

        /*
           Move
        */

        MoveObjects();

        /*
           Collision
        */

        CheckCollisions();

        /*
           Draw
        */

        DrawGame();
    }

    /*
       Close
    */

    CloseWindow();

    return 0;
}
