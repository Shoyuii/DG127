#include <stdio.h>

int main()
{
    int PressAnyKey, Music = 1, FPS = 60, SettingOption, ContinueOption, Hp_slime = 100, Hp_player = 100, Attack_slime = 10, ActionChoice;
    int gold_player = 0, Atk_player = 20, Def_player = 5, mp_player = 0;
    char playerName[50], SlimeName[50] = "Slime";
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
    printf("Once upon a time, in a faraway land...(0 = Continue)\n");
    scanf("%d", &ContinueOption);

    printf("There lived a young adventurer who dreamed of exploring the world.\n");
    printf("One day, the adventurer decided to travel deep into a mysterious forest.(0 = Continue)\n");
    scanf("%d", &ContinueOption);

    printf("What is your name?\n");
    scanf("%s", playerName);

    printf("Hello, %s! Welcome to the adventure.(0 = Continue)\n", playerName);
    scanf("%d", &ContinueOption);

    printf("You walk through the forest for several hours.\n");
    printf("However, the deeper you go, the less familiar the path becomes.(0 = Continue)\n");
    scanf("%d", &ContinueOption);

    printf("Suddenly, you realize something...\n");
    printf("You are completely lost.(0 = Continue)\n");
    scanf("%d", &ContinueOption);

    printf("You look around, trying to find a way out.\n");
    printf("Then, you hear a strange growling sound from behind the trees.(0 = Continue)\n");
    scanf("%d", &ContinueOption);

    printf("You slowly turn around...\n");
    printf("A huge monster jumps out from the bushes!(0 = Continue)\n");
    scanf("%d", &ContinueOption);

    printf("The monster looks at you and lets out a terrifying roar!\n");
    printf("%s, what will you do?(0 = Continue)\n", playerName);
    scanf("%d", &ContinueOption);
    do
    {
        printf("o---------------------------------------------------------------------------------------o\n");
        printf("|                                      Tutorial                                         |\n");
        printf("o---------------------------------------------------------------------------------------o\n");
        printf("o-------------------------------------------------------------o o-----------------------o\n");
        printf("|                                                             | |        Status         |\n");
        printf("|                                                             | o-----------------------o\n");
        printf("|       %s:%-10d                  %s:%-14d  | |HP  : %-11d      |\n", playerName, Hp_player, SlimeName, Hp_slime, Hp_player);
        printf("|          +                               o                  | |ATK : %-11d      |\n", Atk_player);
        printf("|                                                             | |DEF : %-11d      |\n", Def_player);
        printf("|                                                             | |MP  : %-11d      |\n", mp_player);
        printf("|                                                             | |Gold: %-11d      |\n", gold_player);
        printf("o-------------------------------------------------------------o o-----------------------o\n");
        printf("o-------------o  o------------o  o------------o  o------------o\n");
        printf("|  1.Fight    |  |  2.Emote   |  | 3.Backpack |  |   4.Run    |\n");
        printf("o-------------o  o------------o  o------------o  o------------o\n");
        printf("What will you do? (1-4)\n");
        scanf("%d", &ActionChoice);
        if (ActionChoice == 1)
        {
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("|                                      Tutorial                                         |\n");
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("|                                                             | |        Status         |\n");
            printf("|                                                             | o-----------------------o\n");
            printf("|       %s:%-10d                  %s:%-14d  | |HP  : %-11d      |\n", playerName, Hp_player, SlimeName, Hp_slime, Hp_player);
            printf("|          +                               o                  | |ATK : %-11d      |\n", Atk_player);
            printf("|                                                             | |DEF : %-11d      |\n", Def_player);
            printf("|                                                             | |MP  : %-11d      |\n", mp_player);
            printf("|                                                             | |Gold: %-11d      |\n", gold_player);
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("|          1.Slash            |  |                            |\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("|                             |  |                            |\n");
            printf("o-----------------------------o  o----------------------------o\n");
            int FightChoice;
            printf("Choose your skill(0=Exit)\n");
            scanf("%d", &FightChoice);
            if (FightChoice == 0)
            {
                printf("You chose to exit the attack menu.\n");
                continue;
            }
            if (FightChoice == 1)
            {
                printf("You choose to slash!\n");
                if (Hp_slime > 0)
                {
                    int SlimeHit = 1;
                    if (SlimeHit % 3 == 0)
                    {
                        Hp_player -= ((Attack_slime * 2) - Def_player);
                        printf("The slime attacked you for %d damage!\n", Attack_slime);
                        Hp_slime -= Atk_player;
                    }
                    else
                    {
                        Hp_player -= (Attack_slime - Def_player);
                        printf("The slime attacked you for %d damage!\n", Attack_slime);
                        Hp_slime -= Atk_player;
                        SlimeHit++;
                    }
                }
            }
            if (FightChoice == 2)
            {
                printf("Not implemented yet.\n");
                continue;
            }
            if (FightChoice == 3)
            {
                printf("Not implemented yet.\n");
                continue;
            }
            if (FightChoice == 4)
            {
                printf("Not implemented yet.\n");
                continue;
            }
        }
        else if (ActionChoice == 2)
        {
            printf("You used an emote? (0=Continue)\n");
            scanf("%d", &ContinueOption);
            Attack_slime += 1000;
        }
        else if (ActionChoice == 3)
        {
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("|                                      Tutorial                                         |\n");
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("|                                                             | |        Status         |\n");
            printf("|                                                             | o-----------------------o\n");
            printf("|       %s:%-10d                  %s:%-14d  | |HP  : %-11d      |\n", playerName, Hp_player, SlimeName, Hp_slime, Hp_player);
            printf("|          +                               o                  | |ATK : %-11d      |\n", Atk_player);
            printf("|                                                             | |DEF : %-11d      |\n", Def_player);
            printf("|                                                             | |MP  : %-11d      |\n", mp_player);
            printf("|                                                             | |Gold: %-11d      |\n", gold_player);
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("|                             |  |                            |\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("|                             |  |                            |\n");
            printf("o-----------------------------o  o----------------------------o\n");
            int BackpackChoice;
            printf("Choose your skill(0=Exit)\n");
            scanf("%d", &BackpackChoice);
            if (BackpackChoice == 0)
            {
                printf("You chose to exit the attack menu.\n");
                continue;
            }
            if (BackpackChoice == 1)
            {
                printf("Not implemented yet.\n");
                continue;
            }
            if (BackpackChoice == 2)
            {
                printf("Not implemented yet.\n");
                continue;
            }
            if (BackpackChoice == 3)
            {
                printf("Not implemented yet.\n");
                continue;
            }
            if (BackpackChoice == 4)
            {
                printf("Not implemented yet.\n");
                continue;
            }
        }
        else if (ActionChoice == 4)
        {
            printf("You ran away from the slime.\n");
            break;
        }
        else
        {
            printf("Invalid choice. Please choose again.\n");
        }
    } while (Hp_slime > 0 && Hp_player > 0);
    while (Hp_slime <= 0)
    {
        if (Hp_player <= 0)
        {
            printf("You have been defeated by the slime.\n");
            printf("Game Over.(0=Continue)\n");
            scanf("%d", &ContinueOption);
            break;
        }
        else
        {
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("|                                      Tutorial                                         |\n");
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("|                                                             | |        Status         |\n");
            printf("|                                                             | o-----------------------o\n");
            printf("|       %s:%-10d                  %s:%-14d  | |HP  : %-11d      |\n", playerName, Hp_player, SlimeName, Hp_slime, Hp_player);
            printf("|          +                               o                  | |ATK : %-11d      |\n", Atk_player);
            printf("|                                                             | |DEF : %-11d      |\n", Def_player);
            printf("|                                                             | |MP  : %-11d      |\n", mp_player);
            printf("|                                                             | |Gold: %-11d      |\n", gold_player);
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("o-------------o  o------------o  o------------o  o------------o\n");
            printf("|  1.Fight    |  |  2.Emote   |  | 3.Backpack |  |   4.Run    |\n");
            printf("o-------------o  o------------o  o------------o  o------------o\n");
            printf("Congratulations! You have defeated the slime.(0=Continue)\n");
            scanf("%d", &ContinueOption);
            printf("You gained experience and loot!\n");
            printf("+10000 Gold(0=Continue)\n");
            scanf("%d", &ContinueOption);
            gold_player += 10000;
            printf("You now have %d Gold.(0=Continue)\n", gold_player);
            scanf("%d", &ContinueOption);
            break;
        }
    }
    printf("Look at that ! A shop is nearby!(0=Continue)\n");
    scanf("%d", &ContinueOption);
    printf("Welcome to the shop! Here you can buy items to help you on your adventure.(0=Continue)\n");
    scanf("%d", &ContinueOption);
    int ShopChoice, itemID;
    do
    {
        printf("                            o-----------------------o\n");
        printf("                            |         Shop          |\n");
        printf("                            o-----------------------o\n");
        printf("                             o---------------------o\n");
        printf("                             |       Weapons       |\n");
        printf("                             o---------------------o\n");
        printf("                             o---------------------o\n");
        printf("                             |       Potions       |\n");
        printf("                             o---------------------o\n");
        printf("                             o---------------------o\n");
        printf("                             |        Exit         |\n");
        printf("                             o---------------------o\n");
        printf("Press any key to continue . . . (1=Weapons/2=Potions/0=Exit)\n");
        scanf("%d", &ShopChoice);
        if (ShopChoice == 1)
        {
            printf("You are viewing the weapons section. (0=Continue)\n");
            scanf("%d", &ContinueOption);
            do
            {
                printf("o-------------------------------------o o-----------------------o\n");
                printf("|               Weapons               | |        Status         |\n");
                printf("o-------------------------------------o o-----------------------o\n");
                printf("| 1. Woodle sword (+10 ATK): 100 gold | |HP  : %-11d      |\n", Hp_player);
                printf("| 2. Woodle shield (+5 DEF): 100 gold | |ATK : %-11d      |\n", Atk_player);
                printf("| 3. Woodle armor (+15 DEF): 200 gold | |DEF : %-11d      |\n", Def_player);
                printf("|                                     | |MP  : %-11d      |\n", mp_player);
                printf("|                                     | |Gold: %-11d      |\n", gold_player);
                printf("o-------------------------------------o o-----------------------o\n");
                printf("Choose an item to buy (1-3) or 0 to exit:");
                int choice;
                scanf("%d", &choice);

                if (choice == 1)
                {
                    if (gold_player >= 100)
                    {
                        Atk_player += 10;
                        gold_player -= 100;
                        printf("You bought Woodle sword. Remaining gold: %d\n", gold_player);
                    }
                    else
                    {
                        printf("Not enough gold!\n");
                    }
                }
                else if (choice == 2)
                {
                    if (gold_player >= 100)
                    {
                        Def_player += 5;
                        gold_player -= 100;
                        printf("You bought Woodle shield. Remaining gold: %d\n", gold_player);
                    }
                    else
                    {
                        printf("Not enough gold!\n");
                    }
                }
                else if (choice == 2)
                {
                    if (gold_player >= 100)
                    {
                        Def_player += 5;
                        gold_player -= 100;
                        printf("You bought Woodle shield. Remaining gold: %d\n", gold_player);
                    }
                    else
                    {
                        printf("Not enough gold!\n");
                    }
                }
                else if (choice == 3)
                {
                    if (gold_player >= 200)
                    {
                        Def_player += 15;
                        gold_player -= 200;
                        printf("You bought Woodle armor. Remaining gold: %d\n", gold_player);
                    }
                    else
                    {
                        printf("Not enough gold!\n");
                    }
                }

                else if (choice == 0)
                {
                    printf("Exiting the shop. Remaining gold: %d\n", gold_player);
                    break;
                }
                else
                {
                    printf("Invalid choice! Please select a valid item.\n");
                }
            } while (gold_player != 0);
        }
        else if (ShopChoice == 2)
        {
            printf("You are viewing the potions section. (0=Continue)\n");
            scanf("%d", &ContinueOption);
            do
            {
                printf("o-------------------------------------o o-----------------------o\n");
                printf("|               Potions               | |        Status         |\n");
                printf("o-------------------------------------o o-----------------------o\n");
                printf("| 1. HP potion (+50 HP): 250 gold     | |HP  : %-11d      |\n", Hp_player);
                printf("| 2. MP potion (+50 MP): 250 gold     | |ATK : %-11d      |\n", Atk_player);
                printf("|                                     | |DEF : %-11d      |\n", Def_player);
                printf("|                                     | |MP  : %-11d      |\n", mp_player);
                printf("|                                     | |Gold: %-11d      |\n", gold_player);
                printf("o-------------------------------------o o-----------------------o\n");
                printf("Choose an item to buy (1-2) or 0 to exit:");
                int choice;
                scanf("%d", &choice);

                if (choice == 1)
                {
                    if (gold_player >= 250)
                    {
                        Hp_player += 50;
                        gold_player -= 250;
                        printf("You bought HP potion. Remaining gold: %d\n", gold_player);
                    }
                    else
                    {
                        printf("Not enough gold!\n");
                    }
                }
                else if (choice == 2)
                {
                    if (gold_player >= 250)
                    {
                        mp_player += 50;
                        gold_player -= 250;
                        printf("You bought MP potion. Remaining gold: %d\n", gold_player);
                    }
                    else
                    {
                        printf("Not enough gold!\n");
                    }
                }
                else if (choice == 0)
                {
                    printf("Exiting the shop. Remaining gold: %d\n", gold_player);
                    break;
                }
                else
                {
                    printf("Invalid choice! Please select a valid item.\n");
                }
            } while (gold_player != 0);
        }
    } while (ShopChoice != 0);
    int wave = 1, Hp_monster = 100, Attack_monster = 10, Hp_monsterMiniBoss = 200, Attack_monsterMiniBoss = 20, Hp_monsterBoss2 = 500, Attack_monsterBoss2 = 50;
    char monsterName[50] = "Goblin", monsterMiniBoss[50] = "Orc", monsterBoss2[50] = "King Skeleton";
    for (int i = 1; i <= 20; i++)
    {
        printf("o---------------------------------------------------------------------------------------o\n");
        printf("|                                      Tutorial                                         |\n");
        printf("o---------------------------------------------------------------------------------------o\n");
        printf("o-------------------------------------------------------------o o-----------------------o\n");
        printf("|                                                             | |        Status         |\n");
        printf("|                                                             | o-----------------------o\n");
        printf("|       %s:%-10d                  %s:%-14d  | |HP  : %-11d      |\n", playerName, Hp_player, SlimeName, Hp_slime, Hp_player);
        printf("|          +                               o                  | |ATK : %-11d      |\n", Atk_player);
        printf("|                                                             | |DEF : %-11d      |\n", Def_player);
        printf("|                                                             | |MP  : %-11d      |\n", mp_player);
        printf("|                                                             | |Gold: %-11d      |\n", gold_player);
        printf("o-------------------------------------------------------------o o-----------------------o\n");
        printf("o-------------o  o------------o  o------------o  o------------o\n");
        printf("|  1.Fight    |  |  2.Emote   |  | 3.Backpack |  |   4.Run    |\n");
        printf("o-------------o  o------------o  o------------o  o------------o\n");
        printf("What will you do? (1-4)\n");
        scanf("%d", &ActionChoice);
        if (ActionChoice == 1)
        {
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("|                                      Tutorial                                         |\n");
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("|                                                             | |        Status         |\n");
            printf("|                                                             | o-----------------------o\n");
            printf("|       %s:%-10d                  %s:%-14d  | |HP  : %-11d      |\n", playerName, Hp_player, SlimeName, Hp_slime, Hp_player);
            printf("|          +                               o                  | |ATK : %-11d      |\n", Atk_player);
            printf("|                                                             | |DEF : %-11d      |\n", Def_player);
            printf("|                                                             | |MP  : %-11d      |\n", mp_player);
            printf("|                                                             | |Gold: %-11d      |\n", gold_player);
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("|          1.Slash            |  |                            |\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("|                             |  |                            |\n");
            printf("o-----------------------------o  o----------------------------o\n");
            int FightChoice;
            printf("Choose your skill(0=Exit)\n");
            scanf("%d", &FightChoice);
            if (FightChoice == 0)
            {
                printf("You chose to exit the attack menu.\n");
                continue;
            }
            if (FightChoice == 1)
            {
                printf("You choose to slash!\n");
                if (Hp_slime > 0)
                {
                    int SlimeHit = 1;
                    if (SlimeHit % 3 == 0)
                    {
                        Hp_player -= ((Attack_slime * 2) - Def_player);
                        printf("The slime attacked you for %d damage!\n", Attack_slime);
                        Hp_slime -= Atk_player;
                    }
                    else
                    {
                        Hp_player -= (Attack_slime - Def_player);
                        printf("The slime attacked you for %d damage!\n", Attack_slime);
                        Hp_slime -= Atk_player;
                        SlimeHit++;
                    }
                }
            }
            if (FightChoice == 2)
            {
                printf("Not implemented yet.\n");
                continue;
            }
            if (FightChoice == 3)
            {
                printf("Not implemented yet.\n");
                continue;
            }
            if (FightChoice == 4)
            {
                printf("Not implemented yet.\n");
                continue;
            }
        }
        else if (ActionChoice == 2)
        {
            printf("You used an emote? (0=Continue)\n");
            scanf("%d", &ContinueOption);
            Attack_slime += 1000;
        }
        else if (ActionChoice == 3)
        {
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("|                                      Tutorial                                         |\n");
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("|                                                             | |        Status         |\n");
            printf("|                                                             | o-----------------------o\n");
            printf("|       %s:%-10d                  %s:%-14d  | |HP  : %-11d      |\n", playerName, Hp_player, SlimeName, Hp_slime, Hp_player);
            printf("|          +                               o                  | |ATK : %-11d      |\n", Atk_player);
            printf("|                                                             | |DEF : %-11d      |\n", Def_player);
            printf("|                                                             | |MP  : %-11d      |\n", mp_player);
            printf("|                                                             | |Gold: %-11d      |\n", gold_player);
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("|                             |  |                            |\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("o-----------------------------o  o----------------------------o\n");
            printf("|                             |  |                            |\n");
            printf("o-----------------------------o  o----------------------------o\n");
            int BackpackChoice;
            printf("Choose your skill(0=Exit)\n");
            scanf("%d", &BackpackChoice);
            if (BackpackChoice == 0)
            {
                printf("You chose to exit the attack menu.\n");
                continue;
            }
            if (BackpackChoice == 1)
            {
                printf("Not implemented yet.\n");
                continue;
            }
            if (BackpackChoice == 2)
            {
                printf("Not implemented yet.\n");
                continue;
            }
            if (BackpackChoice == 3)
            {
                printf("Not implemented yet.\n");
                continue;
            }
            if (BackpackChoice == 4)
            {
                printf("Not implemented yet.\n");
                continue;
            }
        }
        else if (ActionChoice == 4)
        {
            printf("You ran away from the slime.\n");
            break;
        }
        else
        {
            printf("Invalid choice. Please choose again.\n");
        }
    }
    while (Hp_slime > 0 && Hp_player > 0)
        ;
    while (Hp_slime <= 0)
    {
        if (Hp_player <= 0)
        {
            printf("You have been defeated by the slime.\n");
            printf("Game Over.(0=Continue)\n");
            scanf("%d", &ContinueOption);
            break;
        }
        else
        {
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("|                                      Tutorial                                         |\n");
            printf("o---------------------------------------------------------------------------------------o\n");
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("|                                                             | |        Status         |\n");
            printf("|                                                             | o-----------------------o\n");
            printf("|       %s:%-10d                  %s:%-14d  | |HP  : %-11d      |\n", playerName, Hp_player, SlimeName, Hp_slime, Hp_player);
            printf("|          +                               o                  | |ATK : %-11d      |\n", Atk_player);
            printf("|                                                             | |DEF : %-11d      |\n", Def_player);
            printf("|                                                             | |MP  : %-11d      |\n", mp_player);
            printf("|                                                             | |Gold: %-11d      |\n", gold_player);
            printf("o-------------------------------------------------------------o o-----------------------o\n");
            printf("o-------------o  o------------o  o------------o  o------------o\n");
            printf("|  1.Fight    |  |  2.Emote   |  | 3.Backpack |  |   4.Run    |\n");
            printf("o-------------o  o------------o  o------------o  o------------o\n");
            printf("Congratulations! You have defeated the slime.(0=Continue)\n");
            scanf("%d", &ContinueOption);
            printf("You gained experience and loot!\n");
            printf("+10000 Gold(0=Continue)\n");
            scanf("%d", &ContinueOption);
            gold_player += 10000;
            printf("You now have %d Gold.(0=Continue)\n", gold_player);
            scanf("%d", &ContinueOption);
            break;
        }
    }

    return 0;
}