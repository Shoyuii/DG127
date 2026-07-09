#include <stdio.h>

int main()
{
    int Max_HP, Attack_Power, Defense, Level;
    char Character_Name[50];
    printf("=== CREATE CHARACTER ===\n");
    printf("Character Name : ");
    scanf("%s", Character_Name);
    printf("Max HP         : ");
    scanf("%d", &Max_HP);
    printf("Attack Power   : ");
    scanf("%d", &Attack_Power);
    printf("Defense        : ");
    scanf("%d", &Defense);
    printf("Level          : ");
    scanf("%d", &Level);
    //---------------------------------------------------------------------------
    printf("\n=== CHARACTER SUMMARY ===\n");
    printf("Name           : %s\n", Character_Name);
    printf("Level          : %d\n", Level);
    printf("HP             : %d\n", Max_HP);
    printf("ATK            : %d\n", Attack_Power);
    printf("DEF            : %d\n", Defense);
    return 0;
}