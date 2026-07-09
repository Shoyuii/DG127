#include <stdio.h>

int main()
{

    char name[50], Favorite_Subject[50];
    int age;
    float GPA;

    printf("=== Enter Date ===\n");
    printf("Name            : ");
    scanf("%s", name);
    printf("Age             : ");
    scanf("%d", &age);
    printf("GPA             : ");
    scanf("%f", &GPA);
    printf("Favorite Subject: ");
    scanf("%s", Favorite_Subject);

    //---------------------------------------------------------------------------
    printf("\n=== PERSONAL CARD ===\n");
    printf("┌───────────────────────────────────┐\n");
    printf("│ Name              : %-14s│\n", name);
    printf("│ Age               : %-3d", age);
    printf(" years old │\n");
    printf("│ GPA               : %-14.2f│\n", GPA);
    printf("│ Favorite Subject  : %-14s│\n", Favorite_Subject);
    printf("└───────────────────────────────────┘\n");
    // Ex.Answer : Name=Sho Age=18 GPA=4.00 Favorite Subject=ComPro
    return 0;
}