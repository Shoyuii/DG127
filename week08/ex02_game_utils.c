#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tryToChange(int x)
{
    x = 999; // แก้แค่สาเนา x ใน local ของ tryToChange
}
//------------------------------------------------------------
int square(int n)
{
    int result = n * n; // result มีชีวิตอยู่แค่ใน square() เท่านั้น
    return result;
}
//------------------------------------------------------------
float lerp(float a, float b, float t);
//------------------------------------------------------------
int clamp(int value, int min, int max);
//------------------------------------------------------------
float percentOf(int current, int total);
//------------------------------------------------------------
int randomRange(int min, int max);

int main(void)
{
    int number = 5;
    tryToChange(number);
    printf("%d\n", number);
    //------------------------------------------------------------
    int result = 10;           // คนละตัวแปรกับ result ใน square() แม้ชื่อเดียวกัน
    printf("%d\n", square(5)); // 25
    printf("%d\n", result);    // ยังเป็น 10 ไม่ถูกกระทบ
    //------------------------------------------------------------
    int hp = 150;
    int safeHP = clamp(hp, 0, 100);
    printf("hp เดิม = %d\n", hp);
    printf("safeHP = %d\n", safeHP);
    //------------------------------------------------------------
    float t = 0.5f;
    float pos = lerp(0, 100, t);
    printf("t ใน main = %.2f\n", t);
    printf("pos = %.2f\n", pos);
    //------------------------------------------------------------
    srand((unsigned int)time(NULL));
    int diceMin = 1;
    for (int i = 0; i < 5; i++)
    {
        printf("dice roll: %d\n", randomRange(diceMin, 6));
    }
    printf("diceMin เดิม = %d\n", diceMin);
    //------------------------------------------------------------
    int score = 35, total = 100;
    float percent = percentOf(score, total);
    printf("score/total = %d/%d\n", score, total);
    printf("percent = %.1f%%\n", percent);
    return 0;
}

int clamp(int value, int min, int max)
{
    if (value > max)
        value = max;
    if (value < min)
        value = min;
    return value;
}
//------------------------------------------------------------
float lerp(float a, float b, float t)
{
    float result = a + (b - a) * t;
    return result;
}
//------------------------------------------------------------
float percentOf(int current, int total)
{
    return (float)current / total * 100.0f;
}
//------------------------------------------------------------
int randomRange(int min, int max)
{
    return rand() % (max - min + 1) + min;
}