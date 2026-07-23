#include <stdio.h>
int main()
{
    int max_hp, dmg, is_poisoned, atk_count;

    printf("=== Enter Status ===\n");
    printf("Max HP : ");
    scanf("%d", &max_hp);
    printf("Damage Taken : ");
    scanf("%d", &dmg);
    printf("Poisoned (1 for yes, 0 for no) : ");
    scanf("%d", &is_poisoned);
    printf("Attack Count : ");
    scanf("%d", &atk_count);
    int atk_count_ultimate = atk_count % 5;
    _Bool at_ultimate_ready = (atk_count_ultimate == 1) ? 1 : 0;

    if (max_hp == dmg)
    {
        printf("\n");
        printf("=== Character Status ===\n");
        printf("HP : %d/%d\n", max_hp - dmg, max_hp);
        printf("Status: DEAD!\n");
    }
    else if (max_hp > dmg && atk_count == 0 && is_poisoned == 0)
    {
        printf("\n");
        printf("=== Character Status ===\n");
        printf("HP : %d/%d ** critical **\n", max_hp - dmg, max_hp);
        printf("Status: Critical\n");
    }
    else if (max_hp > dmg && atk_count == 0 && is_poisoned == 1)
    {
        printf("\n");
        printf("=== Character Status ===\n");
        printf("HP : %d/%d ** poisoned **\n", max_hp - dmg, max_hp);
        printf("Status: Poisoned\n");
    }

    else if (max_hp > dmg && at_ultimate_ready == 0 && is_poisoned == 0)
    {
        printf("\n");
        printf("=== Character Status ===\n");
        printf("HP : %d/%d ** ultimate attack **\n", max_hp - dmg, max_hp);
        printf("Status: Ultimate Ready\n");
    }
    else
    {
        printf("\n");
        printf("=== Character Status ===\n");
        printf("HP : %d/%d ** ultimate attack and poisoned **\n", max_hp - dmg, max_hp);
        printf("Status: Ultimate Ready and Poisoned\n");
    }
    return 0;
}