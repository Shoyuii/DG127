#include <stdio.h>
int main()
{
    int Score;
    printf("Enter your score: ");
    scanf("%d", &Score);
    if (Score >= 80)
    {
        printf("Grade: A (4.0) -- Pass\n");
    }
    else if (Score >= 75)
    {
        printf("Grade: B+ (3.5) -- Pass\n");
    }
    else if (Score >= 70)
    {
        printf("Grade: B (3.0) -- Pass\n");
    }
    else if (Score >= 65)
    {
        printf("Grade: C+ (2.5) -- Pass\n");
    }
    else if (Score >= 60)
    {
        printf("Grade: C (2.0) -- Pass\n");
    }
    else if (Score >= 55)
    {
        printf("Grade: D+ (1.5) -- Pass\n");
    }
    else if (Score >= 50)
    {
        printf("Grade: D (1.0) -- Pass\n");
    }
    else
    {
        printf("Grade: F (0.0) -- Fail\n");
    }
    return 0;
}