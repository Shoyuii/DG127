#include <stdio.h>

int main()
{
    int PressAnyKey, Music = 1, FPS = 60, SettingOption, ContinueOption, Hp_slime = 100, Hp_player = 100, Attack_player = 10, Attack_slime = 5, attackChoice;
    char playerName[50];
    do
    {
        printf("                            o-----------------------o\n");
        printf("                            |     ShopAdventure     |\n");
        printf("                            o-----------------------o\n");
        printf("                             o---------------------o\n");
        printf("                             |        Start        |\n");
        printf("                             o---------------------o\n");
        printf("                             o---------------------o\n");
        printf("                             |       Setting       |\n");
        printf("                             o---------------------o\n");
        printf("                             o---------------------o\n");
        printf("                             |        Exit         |\n");
        printf("                             o---------------------o\n");
        printf("Press any key to continue . . . (1=Start/2=Setting/0=Exit)\n");
        scanf("%d", &PressAnyKey);
        if (PressAnyKey == 1)
        {
            printf("You are starting the game. (0=Continue)\n");
            scanf("%d", &PressAnyKey);
        }
        else if (PressAnyKey == 2)
        {
            do
            {
                printf("                            o-----------------------o\n");
                printf("                            |       Settings        |\n");
                printf("                            o-----------------------o\n");
                printf("                             o---------------------o\n");
                printf("                             | Music :       %-6d|\n", Music);
                printf("                             o---------------------o\n");
                printf("                             o---------------------o\n");
                printf("                             | FPS   :       %-6d|\n", FPS);
                printf("                             o---------------------o\n");
                printf("                             o---------------------o\n");
                printf("                             |        Exit         |\n");
                printf("                             o---------------------o\n");
                printf("Press any key to continue . . . (1=Music/2=FPS/0=Exit)\n");
                scanf("%d", &SettingOption);
                do
                {
                    if (SettingOption == 1)
                    {
                        printf("Volume Music (1-100): ");
                        scanf("%d", &Music);
                    }
                    else if (SettingOption == 2)
                    {
                        printf("Set FPS (30-240): ");
                        scanf("%d", &FPS);
                        if (FPS < 30 || FPS > 240)
                        {
                            printf("Invalid FPS value. Please enter a value between 30 and 240.\n");
                            FPS = 60; // Reset to default if invalid
                        }
                    }
                } while (Music < 1 || Music > 100 || FPS < 30 || FPS > 240);
            } while (SettingOption != 0);
        }
    } while (PressAnyKey != 0);
    printf("Once upon a time in a faraway land...\n");
    scanf("%d", &ContinueOption);
    printf("What is your name?\n");
    scanf("%s", playerName);
    printf("Hello, %s! Welcome to the game.\n", playerName);
    for (int i = 0; i <= 10; i++)
    {
        printf(".\n");
    }
    printf("You found a slime !\n");
    do
    {
        printf("o-----------------------------------------------------------------------------------o\n");
        printf("| Player HP: %-3d | Slime HP: %-3d | Player Attack: %-3d | Slime Attack: %-3d |\n", Hp_player, Hp_slime, Attack_player, Attack_slime);
        printf("o-----------------------------------------------------------------------------------o\n");
        printf("What will you do?\n");
        printf("1. Attack\n");
        printf("2. Run Away\n");
        scanf("%d", &attackChoice);
        if (attackChoice == 1)
        {
            Hp_slime -= Attack_player;
            printf("You attacked the slime for %d damage!\n", Attack_player);
            if (Hp_slime > 0)
            {
                Hp_player -= Attack_slime;
                printf("The slime attacked you for %d damage!\n", Attack_slime);
            }
        }
        else if (attackChoice == 2)
        {
            printf("You ran away from the slime.\n");
            break;
        }
        else
        {
            printf("Invalid choice. Please choose again.\n");
        }
    } while (Hp_slime > 0 && Hp_player > 0);
    if (Hp_player <= 0)
    {
        printf("You have been defeated by the slime.\n");
    }
    else if (Hp_slime <= 0)
    {
        printf("Congratulations! You have defeated the slime.\n");
    }

    return 0;
}