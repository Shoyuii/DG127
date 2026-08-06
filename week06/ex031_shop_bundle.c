#include <stdio.h>

int main()
{
    int gold;
    printf("Your gold :");
    scanf("%d", &gold);
    printf("Enter your stats ATK:");
    int atk;
    scanf("%d", &atk);
    printf("Enter your stats DEF:");
    int def;
    scanf("%d", &def);
    printf("Enter your stats HP:");
    int hp;
    scanf("%d", &hp);
    printf("Enter your stats MP:");
    int mp;
    scanf("%d", &mp);

    printf("=== Stats ===\n");
    printf("ATK     : %d\n", atk);
    printf("DEF     : %d\n", def);
    printf("HP      : %d\n", hp);
    printf("MP      : %d\n", mp);

    printf("=== Shop Bundle ===\n");
    printf("1.Woodle sword     (+10 ATK): 100 gold  \n");
    printf("2.Woodle shield    (+10 DEF): 150 gold  \n");
    printf("3.Woodle armor     (+10 DEF): 200 gold  \n");
    printf("4.HP potion        (+50 HP) : 250 gold  \n");
    printf("5.MP potion        (+50 MP) : 250 gold  \n");

    do
    {
        printf("Choose an item (6 to exit):");
        int choice;
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (gold >= 100)
            {
                atk += 10;
                gold -= 100;
                printf("You bought Woodle sword. Remaining gold: %d\n", gold);
            }
            else
            {
                printf("Not enough gold!\n");
            }
        }
        else if (choice == 2)
        {
            if (gold >= 150)
            {
                def += 10;
                gold -= 150;
                printf("You bought Woodle shield. Remaining gold: %d\n", gold);
            }
            else
            {
                printf("Not enough gold!\n");
            }
        }
        else if (choice == 3)
        {
            if (gold >= 200)
            {
                def += 10;
                gold -= 200;
                printf("You bought Woodle armor. Remaining gold: %d\n", gold);
            }
            else
            {
                printf("Not enough gold!\n");
            }
        }
        else if (choice == 4)
        {
            if (gold >= 250)
            {
                hp += 50;
                gold -= 250;
                printf("You bought HP potion. Remaining gold: %d\n", gold);
            }
            else
            {
                printf("Not enough gold!\n");
            }
        }
        else if (choice == 5)
        {
            if (gold >= 250)
            {
                mp += 50;
                gold -= 250;
                printf("You bought MP potion. Remaining gold: %d\n", gold);
            }
            else
            {
                printf("Not enough gold!\n");
            }
        }
        else if (choice == 6)
        {
            printf("Exiting the shop. Remaining gold: %d\n", gold);
            break;
        }
        else
        {
            printf("Invalid choice! Please select a valid item.\n");
        }

    } while (gold > 0);

    printf("Thank you for shopping!\n");
    printf("\n");
    printf("=== Your final stats ===\n");
    printf("ATK            : %d\n", atk);
    printf("DEF            : %d\n", def);
    printf("HP             : %d\n", hp);
    printf("MP             : %d\n", mp);
    printf("Remaining gold : %d\n", gold);

    return 0;
}