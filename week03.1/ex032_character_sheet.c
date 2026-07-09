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
    printf("\n========= CHARACTER SHEET =========\n");
    printf("╔════════════════════════════════╗\n");
    printf("║ %-31s║\n", Character_Name);
    printf("╠════════════════════════════════╣\n");
    printf("║ Level          : %-14d║\n", Level);
    printf("║ HP             : %d/%-10d║\n", Max_HP, Max_HP);
    printf("║ ATK            : %-14d║\n", Attack_Power);
    printf("║ DEF            : %-14d║\n", Defense);
    printf("╠════════════════════════════════╣\n");
    printf("║ HP Bar:[██████████] 100%       ║\n");
    printf("║ Total Power: %-18d║\n", (Attack_Power * 2 + Defense + Max_HP / 10));
    printf("╚════════════════════════════════╝\n");

    return 0;
}
