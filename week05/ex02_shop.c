#include <stdio.h>
int main()
{
    int Gold = 1000;
    printf("=== ITEM SHOP ===\n");
    printf("Gold : %d\n", Gold);
    printf("\n");
    printf("1.Health Potion - 50 Gold (+50 HP)\n");
    printf("2.Mana Potion - 80 Gold (+30 MP)\n");
    printf("3.Wooden Sword - 250 Gold (+10 ATK)\n");
    printf("4.Leather Armor - 300 Gold (+10 DEF)\n");
    printf("5.Exit\n");
    printf("\n");

    int choice;
    printf("Choose Item (1-5) **Select Order Number Low to High EX. 12 , 123 , 234 , 1234**\n");
    printf("Select Number : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        Gold -= 50;
        break;
    case 2:
        Gold -= 80;
        break;
    case 3:
        Gold -= 250;
        break;
    case 4:
        Gold -= 300;
        break;
    case 5:
        break;
    case 12:
        Gold -= 50 + 80;
        break;
    case 13:
        Gold -= 50 + 250;
        break;
    case 14:
        Gold -= 50 + 300;
        break;
    case 23:
        Gold -= 80 + 250;
        break;
    case 24:
        Gold -= 80 + 300;
        break;
    case 34:
        Gold -= 250 + 300;
        break;
    case 123:
        Gold -= 50 + 80 + 250;
        break;
    case 124:
        Gold -= 50 + 80 + 300;
        break;
    case 134:
        Gold -= 50 + 250 + 300;
        break;
    case 234:
        Gold -= 80 + 250 + 300;
        break;
    case 1234:
        Gold -= 50 + 80 + 250 + 300;
        break;
    default:
        break;
    }

    printf("\n");
    printf("=== Purchase ===\n");
    switch (choice)
    {
    case 1:
        printf("Health Potion : 50 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Health : +50 HP\n");
        break;
    case 2:
        printf("Mana Potion : 80 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Mana : +30 MP\n");
        break;
    case 3:
        printf("Wooden Sword : 250 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Attack : +10 ATK\n");
        break;
    case 4:
        printf("Leather Armor : 300 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Defense : +10 DEF\n");
        break;
    case 5:
        printf("Exit the shop.\n");
        break;
    case 12:
        printf("Health Potion : 50 Gold\n");
        printf("Mana Potion : 80 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Health : +50 HP\n");
        printf("Mana : +30 MP\n");
        break;
    case 13:
        printf("Health Potion : 50 Gold\n");
        printf("Wooden Sword : 250 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Health : +50 HP\n");
        printf("Attack : +10 ATK\n");
        break;
    case 14:
        printf("Health Potion : 50 Gold\n");
        printf("Leather Armor : 300 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Health : +50 HP\n");
        printf("Defense : +10 DEF\n");
        break;
    case 23:
        printf("Mana Potion : 80 Gold\n");
        printf("Wooden Sword : 250 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Mana : +30 MP\n");
        printf("Attack : +10 ATK\n");
        break;
    case 24:
        printf("Mana Potion : 80 Gold\n");
        printf("Leather Armor : 300 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Mana : +30 MP\n");
        printf("Defense : +10 DEF\n");
        break;
    case 34:
        printf("Wooden Sword : 250 Gold\n");
        printf("Leather Armor : 300 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Attack : +10 ATK\n");
        printf("Defense : +10 DEF\n");
        break;
    case 123:
        printf("Health Potion : 50 Gold\n");
        printf("Mana Potion : 80 Gold\n");
        printf("Wooden Sword : 250 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Health : +50 HP\n");
        printf("Mana : +30 MP\n");
        printf("Attack : +10 ATK\n");
        break;
    case 124:
        printf("Health Potion : 50 Gold\n");
        printf("Mana Potion : 80 Gold\n");
        printf("Leather Armor : 300 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Health : +50 HP\n");
        printf("Mana : +30 MP\n");
        printf("Defense : +10 DEF\n");
        break;
    case 134:
        printf("Health Potion : 50 Gold\n");
        printf("Wooden Sword : 250 Gold\n");
        printf("Leather Armor : 300 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Health : +50 HP\n");
        printf("Attack : +10 ATK\n");
        printf("Defense : +10 DEF\n");
        break;
    case 234:
        printf("Mana Potion : 80 Gold\n");
        printf("Wooden Sword : 250 Gold\n");
        printf("Leather Armor : 300 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Mana : +30 MP\n");
        printf("Attack : +10 ATK\n");
        printf("Defense : +10 DEF\n");
        break;
    case 1234:
        printf("Health Potion : 50 Gold\n");
        printf("Mana Potion : 80 Gold\n");
        printf("Wooden Sword : 250 Gold\n");
        printf("Leather Armor : 300 Gold\n");
        printf("\n");
        printf("=== Bonus Stats ===\n");
        printf("Health : +50 HP\n");
        printf("Mana : +30 MP\n");
        printf("Attack : +10 ATK\n");
        printf("Defense : +10 DEF\n");
        break;
    default:
        printf("No item purchased.\n");
    }
    printf("Remaining Gold : %d\n", Gold);
    return 0;
}