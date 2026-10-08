#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define W 120     // กว้าง
#define H 20      // สูง
#define G 15      // ตำแหน่งพื้น
#define MAX 12    // จำนวน Object สูงสุด
#define FLOOR 0   // พื้น
#define CEILING 1 // เพดาน
#define PLAYER_WIDTH 8
#define PLAYER_HEIGHT 3
#define HITBOX_X 1
#define HITBOX_WIDTH 6
#define JUMP_FORCE 22.0f // หน่วย = ช่อง / วินาที
#define GRAVITY 30.0f
#define START_SPEED 10.0f // ความเร็วของ Object หน่วย = ช่อง / วิ
#define MAX_SPEED 100.0f
#define SPEED_PER_SCORE 0.02f // Score 100 จะถึงความเร็วสูงสุด
#define FLASH_TIME 0.60f
#define INVINCIBLE_TIME 0.50f
#define TARGET_FPS 60.0
#define COLOR_NORMAL 6
#define COLOR_RED 12
#define COLOR_YELLOW 14
#define COLOR_CYAN 11
#define COLOR_GREEN 10
#define COLOR_MAGENTA 13
#define COLOR_WHITE 7

typedef struct
{
    int x;                 // ตำแหน่ง x ของตัวละคร
    float y;               // ตำแหน่ง y ของตัวละคร
    float vy;              // ความเร็วในแนวตั้งของตัวละคร
    int hp;                // พลังชีวิต
    int score;             // คะแนน
    int jumps;             // จำนวนครั้งที่กระโดด
    int side;              // ทิศทางของตัวละคร (1 ขวา, -1 ซ้าย)
    float flashTimer;      // ตัวจับเวลาสำหรับการเปลี่ยนสี
    float invincibleTimer; // ตัวจับเวลาสำหรับการไม่สามารถถูกโจมตีได้

} Player;

typedef struct
{
    float x;    // ตำแหน่ง x ของ Object
    int y;      // ตำแหน่ง y ของ Object
    int width;  // ความกว้างของ Object
    int height; // ความสูงของ Object
    int side;   // ทิศทางของ Object (1 ขวา, -1 ซ้าย)
    int active; // สถานะของ Object (1 เปิด, 0 ปิด)
} Object;

Player p;
Object obs[MAX];
Object coins[MAX];

LARGE_INTEGER performanceFrequency;
LARGE_INTEGER previousTime;
double deltaTime = 0.0;
float scoreTimer = 0.0f;
float obstacleSpawnTimer = 0.0f;
float coinSpawnTimer = 0.0f;
