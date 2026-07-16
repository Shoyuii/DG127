#include <stdio.h>
#include <math.h>

int main()
{
    int Player_Attack, Enemy_Defense, Hit_Number, Base_Damage, Critical_Damage, HP_Enemy;

    printf("Enter Player Attack: ");
    scanf("%d", &Player_Attack);
    printf("Enter Enemy Defense: ");
    scanf("%d", &Enemy_Defense);
    printf("Enter Hit Number: ");
    scanf("%d", &Hit_Number);
    printf("Enter Enemy HP: ");
    scanf("%d", &HP_Enemy);
    Base_Damage = Player_Attack - Enemy_Defense;
    Critical_Damage = (int)ceil((float)Base_Damage * 1.5);
    if (Hit_Number == 5)
    {
        printf("=== COMBAT SIMULATOR===\n");
        printf("Player Attack : %d\n", Player_Attack);
        printf("Enemy Defense : %d\n", Enemy_Defense);
        printf("Hit Number : %d\n", Hit_Number);
        printf("Damage : %d", Critical_Damage);
        printf(" *** Critical Hit! x1.5 ***\n");
        printf("=== Total Damage : %d ===\n", Critical_Damage * Hit_Number);
        printf("|Enemy HP : %d/%d HP|\n", HP_Enemy - (Critical_Damage * Hit_Number), HP_Enemy);
    }
    else
    {
        printf("=== COMBAT SIMULATOR===\n");
        printf("Player Attack : %d\n", Player_Attack);
        printf("Enemy Defense : %d\n", Enemy_Defense);
        printf("Hit Number : %d\n", Hit_Number);
        printf("Damage : %d", Base_Damage);
        printf(" Normal Hit\n");
        printf("=== Total Damage : %d ===\n", Base_Damage * Hit_Number);
        printf("|Enemy HP : %d/%d HP|\n", HP_Enemy - (Base_Damage * Hit_Number), HP_Enemy);
    }

    return 0;
}
