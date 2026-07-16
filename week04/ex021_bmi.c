#include <math.h>
#include <stdio.h>

int main()
{
    int weight, height_cm;
    float height_m, BMI = 0.0;

    printf("weight (kg) : ");
    scanf("%d", &weight);
    printf("height (cm) : ");
    scanf("%d", &height_cm);
    height_m = (float)height_cm / 100;

    BMI = weight / (height_m * height_m);
    printf("BMI = %.2f\n", BMI);
    if (BMI < 18.5)
    {
        printf("Underweight\n");
    }
    else if (18.5 <= BMI && BMI < 24.9)
    {
        printf("Normal weight\n");
    }
    else if (25 <= BMI && BMI < 30)
    {
        printf("Overweight\n");
    }
    else if (BMI >= 30)
    {
        printf("Obese\n");
    }

    return 0;
}