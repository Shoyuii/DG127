#include <stdio.h>
int main()
{
    int PressAnyKey, Music = 1, FPS = 60, SettingOption, ContinueOption, Hp_slime = 100, Hp_player = 100, Attack_slime = 10, ActionChoice;
    int gold_player = 0, Atk_player = 20, Def_player = 5, mp_player = 0, wave = 1;
    char playerName[50] = "Yoooo", SlimeName[50] = "Slime";
    printf("o---------------------------------------------------------------------------------------o\n");
    printf("|                                      Wave : %-7d                                   |\n", wave);
    printf("o---------------------------------------------------------------------------------------o\n");
    printf("o-------------------------------------------------------------o o-----------------------o\n");
    printf("|                                                             | |        Status         |\n");
    printf("|                                                             | o-----------------------o\n");
    printf("|       %-10s:%-15d       %-10s:%-8d  | |HP  : %-11d      |\n", playerName, Hp_player, SlimeName, Hp_slime, Hp_player);
    printf("|          +                               o                  | |ATK : %-11d      |\n", Atk_player);
    printf("|                                                             | |DEF : %-11d      |\n", Def_player);
    printf("|                                                             | |MP  : %-11d      |\n", mp_player);
    printf("|                                                             | |Gold: %-11d      |\n", gold_player);
    printf("o-------------------------------------------------------------o o-----------------------o\n");
    printf("o-------------o  o------------o  o------------o  o------------o\n");
    printf("|  1.Fight    |  |  2.Emote   |  | 3.Backpack |  |   4.Run    |\n");
    printf("o-------------o  o------------o  o------------o  o------------o\n");
    printf("What will you do? (1-4)\n");
    return 0;
}