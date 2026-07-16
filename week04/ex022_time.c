#include <stdio.h>
#include <math.h>
int main()
{
    int hour, minute, second;
    printf("Enter time (second): ");
    scanf("%d", &second);
    hour = second / 3600;
    minute = (second % 3600) / 60;
    second = second % 60;
    printf("Time: %02d:%02d:%02d\n", hour, minute, second);
    return 0;
}
