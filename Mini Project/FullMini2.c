#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* =========================================================
   CONSTANTS
   ========================================================= */

#define MAX_NAME 50
#define WEAPON_COUNT 3
#define POTION_COUNT 2
#define SPELL_COUNT 4
#define INVENTORY_SIZE 20

#define SLIME_HP 100
#define SLIME_ATK 10

/* =========================================================
   STRUCTURES
   ========================================================= */

typedef struct
{
    char name[MAX_NAME];

    int hp;
    int maxHp;

    int mp;
    int maxMp;

    int atk;
    int def;

    int gold;

    int weaponLevel;

    int potions[POTION_COUNT];
    int spells[SPELL_COUNT];

} Player;

typedef struct
{
    char name[MAX_NAME];

    int hp;
    int maxHp;

    int atk;
    int def;

    int isBoss;

} Monster;

typedef struct
{
    char name[MAX_NAME];

    int price;
    int atkBonus;
    int defBonus;

} Weapon;

typedef struct
{
    char name[MAX_NAME];

    int price;
    int healHp;
    int healMp;

} Potion;

typedef struct
{
    char name[MAX_NAME];

    int price;
    int mpCost;
    int damage;
    int heal;

    int type;
    /*
        type 1 = Damage
        type 2 = Heal
    */

} Spell;

/* =========================================================
   GLOBAL ARRAYS
   ========================================================= */

Weapon weapons[WEAPON_COUNT] =
    {
        {"Poop Sword", 100, 1000, 0},
        {"Harder Poop", 100, 0, 50},
        {"Very Harder Poop", 200, 0, 150}};

Potion potions[POTION_COUNT] =
    {
        {"HP Potion", 250, 50, 0},
        {"MP Potion", 250, 0, 50}};

Spell spells[SPELL_COUNT] =
    {
        {"Fireball", 500, 20, 60, 0, 1},
        {"Ice Lance", 750, 30, 100, 0, 1},
        {"Thunder", 1200, 50, 180, 0, 1},
        {"Heal", 800, 25, 0, 100, 2}};

/* =========================================================
   FUNCTION PROTOTYPES
   ========================================================= */

void clearInput(void);
void pauseGame(void);
void clearScene(void);

void initializePlayer(Player *player);

void showTitle(void);
void mainMenu(Player *player);

void settingsMenu(void);

void story(Player *player);

void showStatus(const Player *player,
                const Monster *monster,
                int wave);

void createSlime(Monster *monster);

void createMonster(Monster *monster,
                   int wave);

void combat(Player *player,
            Monster *monster,
            int wave);

int playerAttack(Player *player,
                 Monster *monster);

int useSpell(Player *player,
             Monster *monster);

int usePotions(Player *player,
               Monster *monster);

void backpack(Player *player,
              Monster *monster);

int playerTurn(Player *player,
               Monster *monster);

void monsterAttack(Player *player,
                   const Monster *monster);

void firstSlimeBattle(Player *player);

void shop(Player *player,
          int magicUnlocked);

void weaponShop(Player *player);

void potionShop(Player *player);

void magicShop(Player *player);

void buyWeapon(Player *player,
               int index);

void buyPotion(Player *player,
               int index);

void buySpell(Player *player,
              int index);

void dungeon20(Player *player);

void infinityDungeon(Player *player);

void victoryReward(Player *player,
                   int wave);

int calculateDamage(int attack,
                    int defense);

/* =========================================================
   MAIN
   ========================================================= */

int main(void)
{
    Player player;

    srand((unsigned int)time(NULL));

    initializePlayer(&player);

    showTitle();

    pauseGame();

    mainMenu(&player);

    return 0;
}

/* =========================================================
   BASIC FUNCTIONS
   ========================================================= */

void clearInput(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear input buffer */
    }
}

/*
    Clear terminal screen.

    Windows:
        cls

    Linux / macOS:
        clear
*/

void clearScene(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseGame(void)
{
    int option;

    printf("\nPress 0 to continue: ");
    scanf("%d", &option);
}

/* =========================================================
   PLAYER
   ========================================================= */

void initializePlayer(Player *player)
{
    memset(player, 0, sizeof(Player));

    strcpy(player->name, "Adventurer");

    player->maxHp = 100;
    player->hp = 100;

    player->maxMp = 50;
    player->mp = 50;

    player->atk = 20;
    player->def = 5;

    player->gold = 0;

    player->weaponLevel = 0;

    for (int i = 0; i < POTION_COUNT; i++)
    {
        player->potions[i] = 0;
    }

    for (int i = 0; i < SPELL_COUNT; i++)
    {
        player->spells[i] = 0;
    }
}

/* =========================================================
   TITLE
   ========================================================= */

void showTitle(void)
{
    clearScene();

    printf("\n");
    printf("=============================================================\n");
    printf("                      Presented by \n");
    printf("=============================================================\n");
    printf("Jittarin Panyakam | Phatpoom Inkaewsub | Ronnaranok Kongkamol\n");
    printf("=============================================================\n");
}

/* =========================================================
   MAIN MENU
   ========================================================= */

void mainMenu(Player *player)
{
    int choice;

    do
    {
        clearScene();
        printf("               o---------------------o\n");
        printf("               |   POOP ADVENTURE    |\n");
        printf("               o---------------------o\n");

        printf("               o---------------------o\n");
        printf("               |        Start        |\n");
        printf("               o---------------------o\n");

        printf("               o---------------------o\n");
        printf("               |       Setting       |\n");
        printf("               o---------------------o\n");

        printf("               o---------------------o\n");
        printf("               |        Exit         |\n");
        printf("               o---------------------o\n");

        printf("\n");
        printf("Press any key to continue . . .\n");
        printf("(1=Start/2=Setting/0=Exit)\n");

        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            story(player);

            /*
                First battle
            */

            firstSlimeBattle(player);

            if (player->hp <= 0)
            {
                clearScene();

                printf("\nGAME OVER!\n");

                pauseGame();

                return;
            }

            /*
                First shop
                Magic is LOCKED
            */

            shop(player, 0);

            /*
                20 Wave Dungeon
            */

            dungeon20(player);

            if (player->hp <= 0)
            {
                clearScene();

                printf("\nGAME OVER!\n");

                pauseGame();

                return;
            }

            /*
                Second shop
                Magic unlocked
            */

            clearScene();

            printf("\n");
            printf("=============================================================\n");
            printf("You survived the 20 Wave Dungeon!\n");
            printf("=============================================================\n");

            printf("\n");
            printf("A mysterious shop appeared before you...\n");

            printf("\n");
            printf("MAGIC SHOP UNLOCKED!\n");

            printf("\n");
            printf("You can now purchase powerful spells.\n");

            pauseGame();

            shop(player, 1);

            /*
                Infinity Dungeon
            */

            infinityDungeon(player);

            break;

        case 2:

            settingsMenu();

            break;

        case 0:

            clearScene();

            printf("\nThank you for playing!\n");

            break;

        default:

            printf("\nInvalid choice!\n");

            pauseGame();

            break;
        }

    } while (choice != 0);
}

/* =========================================================
   SETTINGS
   ========================================================= */

void settingsMenu(void)
{
    int music = 100;
    int fps = 60;

    int choice;

    do
    {
        clearScene();

        printf("             o-----------------------o\n");
        printf("             |       Settings        |\n");
        printf("             o-----------------------o\n");

        printf("              o---------------------o\n");
        printf("              | Music :       %-6d|\n",
               music);
        printf("              o---------------------o\n");

        printf("              o---------------------o\n");
        printf("              | FPS   :       %-6d|\n",
               fps);
        printf("              o---------------------o\n");

        printf("              o---------------------o\n");
        printf("              |        Exit         |\n");
        printf("              o---------------------o\n");

        printf("\n");
        printf("Press any key to continue . . .\n");
        printf("(1=Music/2=FPS/0=Exit)\n");

        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Music volume (1-100): ");
            scanf("%d", &music);

            if (music < 1 || music > 100)
            {
                printf("Invalid music value!\n");

                music = 100;

                pauseGame();
            }
        }
        else if (choice == 2)
        {
            printf("FPS (30-240): ");
            scanf("%d", &fps);

            if (fps < 30 || fps > 240)
            {
                printf("Invalid FPS!\n");

                fps = 60;

                pauseGame();
            }
        }

    } while (choice != 0);
}

/* =========================================================
   STORY
   ========================================================= */

void story(Player *player)
{
    clearScene();

    printf("\n");
    printf("Once upon a time, in a faraway land...\n");

    pauseGame();

    clearScene();

    printf("\n");
    printf("There lived a young adventurer who dreamed of exploring the world.\n");
    printf("One day, the adventurer decided to travel deep into a mysterious forest.\n");

    pauseGame();

    clearScene();

    printf("\nWhat is your name?\n");
    printf("> ");

    scanf("%49s", player->name);

    printf("\nHello, %s! Welcome to the adventure.\n",
           player->name);

    pauseGame();

    clearScene();

    printf("\nYou walk through the forest for several hours.\n");
    printf("However, the deeper you go, the less familiar the path becomes.\n");

    pauseGame();

    clearScene();

    printf("\nSuddenly, you realize something...\n");
    printf("You are completely lost.\n");

    pauseGame();

    clearScene();

    printf("\nYou look around, trying to find a way out.\n");
    printf("Then, you hear a strange growling sound from behind the trees.\n");

    pauseGame();

    clearScene();

    printf("\nYou slowly turn around...\n");
    printf("A huge monster jumps out from the bushes!\n");

    pauseGame();

    clearScene();

    printf("\nThe monster looks at you and lets out a terrifying roar!\n");

    printf("\n%s, what will you do?\n",
           player->name);

    pauseGame();
}

/* =========================================================
   STATUS
   ========================================================= */

void showStatus(const Player *player,
                const Monster *monster,
                int wave)
{
    printf("\n");
    printf("=========================================================================================\n");
    if (wave > 0)
    {
        printf("                                       WAVE %d\n", wave);
    }
    else
    {
        printf("                                       BATTLE\n");
    }
    printf("=========================================================================================\n");
    printf("o-------------------------------------------------------------o o-----------------------o\n");
    printf("|                                                             | |        Status         |\n");
    printf("|                                                             | o-----------------------o\n");
    printf("|       %-10s:%-15d       %-10s:%-10d| |HP  : %-11d      |\n", player->name, player->hp, monster->name, monster->hp, player->hp);
    printf("|         ( )                              [  ]               | |ATK : %-11d      |\n", player->atk);
    printf("|         / \\                              [  ]               | |DEF : %-11d      |\n", player->def);
    printf("|         | |                              [  ]               | |MP  : %-11d      |\n", player->mp);
    printf("|                                                             | |Gold: %-11d      |\n", player->gold);
    printf("o-------------------------------------------------------------o o-----------------------o\n");
    printf("=========================================================================================\n");
}

/* =========================================================
   MONSTER CREATION
   ========================================================= */

void createSlime(Monster *monster)
{
    strcpy(monster->name, "Slime");
    monster->maxHp = SLIME_HP;
    monster->hp = SLIME_HP;

    monster->atk = SLIME_ATK;
    monster->def = 2;

    monster->isBoss = 0;
}

void createMonster(Monster *monster,
                   int wave)
{
    if (wave % 5 == 0 && wave < 20)
    {
        strcpy(monster->name, "Orc");

        monster->maxHp = 200 * wave;
        monster->hp = monster->maxHp;

        monster->atk = 20 * wave;
        monster->def = wave;

        monster->isBoss = 1;
    }
    else if (wave == 20)
    {
        strcpy(monster->name, "King Skeleton");

        monster->maxHp = 500 * wave;
        monster->hp = monster->maxHp;

        monster->atk = 50 * wave;
        monster->def = 20;

        monster->isBoss = 1;
    }
    else
    {
        strcpy(monster->name, "Goblin");

        monster->maxHp = 100 * wave;
        monster->hp = monster->maxHp;

        monster->atk = 10 * wave;
        monster->def = wave / 2;

        monster->isBoss = 0;
    }
}

/* =========================================================
   DAMAGE SYSTEM
   ========================================================= */

int calculateDamage(int attack,
                    int defense)
{
    int damage;

    damage = attack - defense;

    if (damage < 1)
    {
        damage = 1;
    }

    return damage;
}

/* =========================================================
   SLIME BATTLE
   ========================================================= */

void firstSlimeBattle(Player *player)
{
    Monster slime;

    createSlime(&slime);

    clearScene();

    printf("\n");
    printf("=============================================================\n");
    printf("                    SLIME BATTLE\n");
    printf("=============================================================\n");

    pauseGame();

    combat(player, &slime, 0);

    if (player->hp > 0 && slime.hp <= 0)
    {
        clearScene();

        printf("\nCongratulations! You defeated the slime!\n");

        printf("\nYou gained 100000 Gold!\n");

        player->gold += 100000;

        printf("Current Gold: %d\n",
               player->gold);

        pauseGame();
    }
}

/* =========================================================
   COMBAT
   ========================================================= */

void combat(Player *player,
            Monster *monster,
            int wave)
{
    int result;

    while (player->hp > 0 && monster->hp > 0)
    {
        clearScene();

        showStatus(player,
                   monster,
                   wave);

        result = playerTurn(player,
                            monster);

        /*
            0 = run
            1 = continue
        */

        if (result == 0)
        {
            clearScene();

            printf("\nYou ran away!\n");

            pauseGame();

            break;
        }

        if (monster->hp <= 0)
        {
            break;
        }

        monsterAttack(player,
                      monster);

        if (player->hp <= 0)
        {
            printf("\n%s defeated you!\n",
                   monster->name);

            pauseGame();

            break;
        }

        pauseGame();
    }
}

/* =========================================================
   PLAYER TURN
   ========================================================= */

int playerTurn(Player *player,
               Monster *monster)
{
    int choice;

    printf("\n");
    printf("o-------------o  o------------o  o------------o  o------------o\n");
    printf("|  1.Fight    |  |  2.Magic   |  | 3.Backpack |  |   4.Run    |\n");
    printf("o-------------o  o------------o  o------------o  o------------o\n");

    printf("\nWhat will you do? ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        return playerAttack(player,
                            monster);
    }
    else if (choice == 2)
    {
        return useSpell(player,
                        monster);
    }
    else if (choice == 3)
    {
        backpack(player,
                 monster);

        return 1;
    }
    else if (choice == 4)
    {
        return 0;
    }
    else
    {
        printf("Invalid choice!\n");

        pauseGame();

        return 1;
    }
}

/* =========================================================
   NORMAL ATTACK
   ========================================================= */

int playerAttack(Player *player,
                 Monster *monster)
{
    int damage;

    printf("\n%s uses Slash!\n",
           player->name);

    /*
        Critical chance = 20%
    */

    if (rand() % 100 < 20)
    {
        damage = player->atk * 2;

        damage = calculateDamage(
            damage,
            monster->def);

        printf("CRITICAL HIT!\n");
    }
    else
    {
        damage = calculateDamage(
            player->atk,
            monster->def);
    }

    monster->hp -= damage;

    if (monster->hp < 0)
    {
        monster->hp = 0;
    }

    printf("%s takes %d damage!\n",
           monster->name,
           damage);

    return 1;
}

/* =========================================================
   MONSTER ATTACK
   ========================================================= */

void monsterAttack(Player *player,
                   const Monster *monster)
{
    int damage;

    /*
        10% critical attack
    */

    if (rand() % 100 < 10)
    {
        damage = monster->atk * 2;

        damage = calculateDamage(
            damage,
            player->def);

        printf("\n%s uses a CRITICAL ATTACK!\n",
               monster->name);
    }
    else
    {
        damage = calculateDamage(
            monster->atk,
            player->def);

        printf("\n%s attacks!\n",
               monster->name);
    }

    player->hp -= damage;

    if (player->hp < 0)
    {
        player->hp = 0;
    }

    printf("%s takes %d damage!\n",
           player->name,
           damage);
}

/* =========================================================
   MAGIC
   ========================================================= */

int useSpell(Player *player,
             Monster *monster)
{
    int choice;
    int index;

    clearScene();

    printf("\n");
    printf("=============================================================\n");
    printf("                         MAGIC\n");
    printf("=============================================================\n");

    printf("Your MP: %d/%d\n",
           player->mp,
           player->maxMp);

    printf("\n");

    for (int i = 0; i < SPELL_COUNT; i++)
    {
        printf("%d. %-15s MP:%-3d",
               i + 1,
               spells[i].name,
               spells[i].mpCost);

        if (player->spells[i])
        {
            printf(" [OWNED]");
        }
        else
        {
            printf(" [LOCKED]");
        }

        printf("\n");
    }

    printf("0. Exit\n");

    printf("\nChoose magic: ");
    scanf("%d", &choice);

    if (choice == 0)
    {
        return 1;
    }

    if (choice < 1 || choice > SPELL_COUNT)
    {
        printf("Invalid magic!\n");

        pauseGame();

        return 1;
    }

    index = choice - 1;

    if (!player->spells[index])
    {
        printf("\nYou don't own this spell!\n");

        pauseGame();

        return 1;
    }

    Spell *spell = &spells[index];

    if (player->mp < spell->mpCost)
    {
        printf("\nNot enough MP!\n");

        pauseGame();

        return 1;
    }

    player->mp -= spell->mpCost;

    printf("\nYou cast %s!\n",
           spell->name);

    if (spell->type == 1)
    {
        int damage;

        damage = calculateDamage(
            player->atk + spell->damage,
            monster->def);

        monster->hp -= damage;

        if (monster->hp < 0)
        {
            monster->hp = 0;
        }

        printf("%s takes %d magic damage!\n",
               monster->name,
               damage);
    }
    else if (spell->type == 2)
    {
        int oldHp;

        oldHp = player->hp;

        player->hp += spell->heal;

        if (player->hp > player->maxHp)
        {
            player->hp = player->maxHp;
        }

        printf("You healed %d HP!\n",
               player->hp - oldHp);
    }

    return 1;
}

/* =========================================================
   BACKPACK
   ========================================================= */

void backpack(Player *player,
              Monster *monster)
{
    int choice;

    do
    {
        clearScene();

        printf("\n");
        printf("=============================================================\n");
        printf("                       BACKPACK\n");
        printf("=============================================================\n");

        printf("HP: %d/%d\n",
               player->hp,
               player->maxHp);

        printf("MP: %d/%d\n",
               player->mp,
               player->maxMp);

        printf("\n");

        printf("1. HP Potion x%d\n",
               player->potions[0]);

        printf("2. MP Potion x%d\n",
               player->potions[1]);

        printf("0. Exit\n");

        printf("\nChoose item: ");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2)
        {
            usePotions(player,
                       monster);

            pauseGame();
        }
        else if (choice != 0)
        {
            printf("Invalid choice!\n");

            pauseGame();
        }

    } while (choice != 0);
}

/* =========================================================
   POTION USE
   ========================================================= */

int usePotions(Player *player,
               Monster *monster)
{
    int choice;

    (void)monster;

    clearScene();

    printf("\n");
    printf("=============================================================\n");
    printf("                         POTIONS\n");
    printf("=============================================================\n");

    printf("1. HP Potion x%d\n",
           player->potions[0]);

    printf("2. MP Potion x%d\n",
           player->potions[1]);

    printf("0. Exit\n");

    printf("\nChoose potion: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        if (player->potions[0] <= 0)
        {
            printf("\nYou don't have HP Potion!\n");

            return 0;
        }

        player->potions[0]--;

        player->hp += potions[0].healHp;

        if (player->hp > player->maxHp)
        {
            player->hp = player->maxHp;
        }

        printf("\nYou recovered 50 HP!\n");

        return 1;
    }
    else if (choice == 2)
    {
        if (player->potions[1] <= 0)
        {
            printf("\nYou don't have MP Potion!\n");

            return 0;
        }

        player->potions[1]--;

        player->mp += potions[1].healMp;

        if (player->mp > player->maxMp)
        {
            player->mp = player->maxMp;
        }

        printf("\nYou recovered 50 MP!\n");

        return 1;
    }

    return 0;
}

/* =========================================================
   SHOP
   ========================================================= */

void shop(Player *player,
          int magicUnlocked)
{
    int choice;

    do
    {
        clearScene();

        printf("\n");
        printf("=============================================================\n");
        printf("                         SHOP\n");
        printf("=============================================================\n");

        printf("Gold: %d\n",
               player->gold);

        printf("\n");

        printf("1. Weapons\n");
        printf("2. Potions\n");

        if (magicUnlocked)
        {
            printf("3. Magic\n");
        }
        else
        {
            printf("3. Magic [LOCKED]\n");
        }

        printf("0. Exit\n");

        printf("\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            weaponShop(player);
        }
        else if (choice == 2)
        {
            potionShop(player);
        }
        else if (choice == 3)
        {
            if (magicUnlocked)
            {
                magicShop(player);
            }
            else
            {
                printf("\n");
                printf("=============================================================\n");
                printf("                       MAGIC LOCKED\n");
                printf("=============================================================\n");

                printf("\nClear the 20 Wave Dungeon first!\n");

                pauseGame();
            }
        }
        else if (choice != 0)
        {
            printf("\nInvalid choice!\n");

            pauseGame();
        }

    } while (choice != 0);
}

/* =========================================================
   WEAPON SHOP
   ========================================================= */

void weaponShop(Player *player)
{
    int choice;

    do
    {
        clearScene();

        printf("\n");
        printf("=============================================================\n");
        printf("                        WEAPONS\n");
        printf("=============================================================\n");

        for (int i = 0; i < WEAPON_COUNT; i++)
        {
            printf("%d. %-15s Price:%-5d\n",
                   i + 1,
                   weapons[i].name,
                   weapons[i].price);

            printf("   ATK +%d DEF +%d\n",
                   weapons[i].atkBonus,
                   weapons[i].defBonus);
        }

        printf("0. Exit\n");

        printf("\nYour Gold: %d\n",
               player->gold);

        printf("Choose: ");
        scanf("%d", &choice);

        if (choice >= 1 &&
            choice <= WEAPON_COUNT)
        {
            buyWeapon(player,
                      choice - 1);

            pauseGame();
        }
        else if (choice != 0)
        {
            printf("Invalid choice!\n");

            pauseGame();
        }

    } while (choice != 0);
}

/* =========================================================
   BUY WEAPON
   ========================================================= */

void buyWeapon(Player *player,
               int index)
{
    Weapon *weapon = &weapons[index];

    if (player->gold < weapon->price)
    {
        printf("\nNot enough gold!\n");

        return;
    }

    player->gold -= weapon->price;

    player->atk += weapon->atkBonus;
    player->def += weapon->defBonus;

    player->weaponLevel++;

    printf("\nYou bought %s!\n",
           weapon->name);

    printf("ATK: %d\n",
           player->atk);

    printf("DEF: %d\n",
           player->def);

    printf("Gold: %d\n",
           player->gold);
}

/* =========================================================
   POTION SHOP
   ========================================================= */

void potionShop(Player *player)
{
    int choice;

    do
    {
        clearScene();

        printf("\n");
        printf("=============================================================\n");
        printf("                        POTIONS\n");
        printf("=============================================================\n");

        for (int i = 0; i < POTION_COUNT; i++)
        {
            printf("%d. %-15s Price: %d\n",
                   i + 1,
                   potions[i].name,
                   potions[i].price);
        }

        printf("0. Exit\n");

        printf("\nGold: %d\n",
               player->gold);

        printf("Choose: ");
        scanf("%d", &choice);

        if (choice >= 1 &&
            choice <= POTION_COUNT)
        {
            buyPotion(player,
                      choice - 1);

            pauseGame();
        }
        else if (choice != 0)
        {
            printf("Invalid choice!\n");

            pauseGame();
        }

    } while (choice != 0);
}

/* =========================================================
   BUY POTION
   ========================================================= */

void buyPotion(Player *player,
               int index)
{
    Potion *potion = &potions[index];

    if (player->gold < potion->price)
    {
        printf("\nNot enough gold!\n");

        return;
    }

    player->gold -= potion->price;

    player->potions[index]++;

    printf("\nYou bought %s!\n",
           potion->name);

    printf("You now have %d.\n",
           player->potions[index]);

    printf("Gold remaining: %d\n",
           player->gold);
}

/* =========================================================
   MAGIC SHOP
   ========================================================= */

void magicShop(Player *player)
{
    int choice;

    do
    {
        clearScene();

        printf("\n");
        printf("=============================================================\n");
        printf("                      MAGIC SHOP\n");
        printf("=============================================================\n");

        printf("Gold: %d\n",
               player->gold);

        printf("\n");

        for (int i = 0; i < SPELL_COUNT; i++)
        {
            printf("%d. %-15s Price:%-5d MP:%-3d",
                   i + 1,
                   spells[i].name,
                   spells[i].price,
                   spells[i].mpCost);

            if (player->spells[i])
            {
                printf(" [OWNED]");
            }
            else
            {
                printf(" [BUY]");
            }

            printf("\n");
        }

        printf("0. Exit\n");

        printf("\nChoose spell: ");
        scanf("%d", &choice);

        if (choice >= 1 &&
            choice <= SPELL_COUNT)
        {
            buySpell(player,
                     choice - 1);

            pauseGame();
        }
        else if (choice != 0)
        {
            printf("Invalid choice!\n");

            pauseGame();
        }

    } while (choice != 0);
}

/* =========================================================
   BUY SPELL
   ========================================================= */

void buySpell(Player *player,
              int index)
{
    Spell *spell = &spells[index];

    if (player->spells[index])
    {
        printf("\nYou already own %s!\n",
               spell->name);

        return;
    }

    if (player->gold < spell->price)
    {
        printf("\nNot enough gold!\n");

        printf("Required: %d Gold\n",
               spell->price);

        printf("Your Gold: %d\n",
               player->gold);

        return;
    }

    player->gold -= spell->price;

    player->spells[index] = 1;

    printf("\n");
    printf("=============================================================\n");
    printf("                    MAGIC LEARNED!\n");
    printf("=============================================================\n");

    printf("\nYou learned: %s\n",
           spell->name);

    printf("MP Cost: %d\n",
           spell->mpCost);

    if (spell->type == 1)
    {
        printf("Damage: %d\n",
               spell->damage);
    }
    else if (spell->type == 2)
    {
        printf("Heal: %d HP\n",
               spell->heal);
    }

    printf("Gold remaining: %d\n",
           player->gold);
}

/* =========================================================
   20 WAVE DUNGEON
   ========================================================= */

void dungeon20(Player *player)
{
    clearScene();

    printf("\n");
    printf("=============================================================\n");
    printf("                    20 WAVE DUNGEON\n");
    printf("=============================================================\n");

    printf("\nSurvive all 20 waves!\n");

    pauseGame();

    for (int wave = 1; wave <= 20; wave++)
    {
        Monster monster;

        createMonster(&monster,
                      wave);

        clearScene();

        printf("\n");
        printf("=============================================================\n");
        printf("                       WAVE %d\n",
               wave);
        printf("                       %s\n",
               monster.name);
        printf("=============================================================\n");

        pauseGame();

        combat(player,
               &monster,
               wave);

        /*
            Player ran away
        */

        if (monster.hp > 0)
        {
            clearScene();

            printf("\nYou escaped from Wave %d.\n",
                   wave);

            pauseGame();

            return;
        }

        if (player->hp <= 0)
        {
            clearScene();

            printf("\nYou died at Wave %d.\n",
                   wave);

            pauseGame();

            return;
        }

        victoryReward(player,
                      wave);

        /*
            Recover HP
        */

        player->hp += player->maxHp / 10;

        if (player->hp > player->maxHp)
        {
            player->hp = player->maxHp;
        }

        /*
            Recover MP
        */

        player->mp += player->maxMp / 10;

        if (player->mp > player->maxMp)
        {
            player->mp = player->maxMp;
        }

        printf("\nYou recover after the wave.\n");

        printf("HP: %d/%d\n",
               player->hp,
               player->maxHp);

        printf("MP: %d/%d\n",
               player->mp,
               player->maxMp);

        pauseGame();
    }

    clearScene();

    printf("\n");
    printf("=============================================================\n");
    printf("              CONGRATULATIONS!\n");
    printf("              YOU CLEARED 20 WAVES!\n");
    printf("=============================================================\n");

    printf("\nMagic Shop has been unlocked!\n");

    pauseGame();
}

/* =========================================================
   INFINITY DUNGEON
   ========================================================= */

void infinityDungeon(Player *player)
{
    int wave = 21;

    clearScene();

    printf("\n");
    printf("=============================================================\n");
    printf("                     INFINITY DUNGEON\n");
    printf("=============================================================\n");

    printf("\nThere is no end...\n");
    printf("The monsters will continue getting stronger.\n");

    pauseGame();

    while (player->hp > 0)
    {
        Monster monster;

        createMonster(&monster,
                      wave);

        /*
            Infinity scaling
        */

        if (wave % 5 == 0)
        {
            strcpy(monster.name,
                   "Infinity Orc");

            monster.maxHp = 200 * wave;
            monster.hp = monster.maxHp;

            monster.atk = 20 * wave;
            monster.def = wave / 2;

            monster.isBoss = 1;
        }
        else
        {
            strcpy(monster.name,
                   "Infinity Goblin");

            monster.maxHp = 100 * wave;
            monster.hp = monster.maxHp;

            monster.atk = 10 * wave;
            monster.def = wave / 2;

            monster.isBoss = 0;
        }

        /*
            Every 10 waves
        */

        if (wave % 10 == 0)
        {
            monster.maxHp *= 2;

            monster.hp = monster.maxHp;

            monster.atk *= 2;
        }

        clearScene();

        printf("\n");
        printf("=============================================================\n");
        printf("                  INFINITY WAVE %d\n",
               wave);
        printf("                  %s\n",
               monster.name);
        printf("=============================================================\n");

        if (wave % 10 == 0)
        {
            printf("\n");
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("                  SPECIAL INFINITY BOSS\n");
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }

        pauseGame();

        combat(player,
               &monster,
               wave);

        if (player->hp <= 0)
        {
            clearScene();

            printf("\n");
            printf("=============================================================\n");
            printf("                 INFINITY DUNGEON END\n");
            printf("=============================================================\n");

            printf("\n%s reached Wave %d!\n",
                   player->name,
                   wave);

            printf("\nYou have been defeated.\n");

            pauseGame();

            break;
        }

        if (monster.hp > 0)
        {
            clearScene();

            printf("\nYou escaped from the dungeon.\n");

            pauseGame();

            break;
        }

        victoryReward(player,
                      wave);

        /*
            Recovery
        */

        player->hp += player->maxHp / 10;

        if (player->hp > player->maxHp)
        {
            player->hp = player->maxHp;
        }

        player->mp += player->maxMp / 10;

        if (player->mp > player->maxMp)
        {
            player->mp = player->maxMp;
        }

        wave++;

        pauseGame();
    }
}

/* =========================================================
   REWARD
   ========================================================= */

void victoryReward(Player *player,
                   int wave)
{
    int reward;

    /*
        Reward increases with wave
    */

    reward = 1000 * wave;

    if (wave == 20)
    {
        reward += 10000;
    }

    player->gold += reward;

    printf("\n");
    printf("You defeated the monster!\n");

    printf("Reward: +%d Gold\n",
           reward);

    printf("Current Gold: %d\n",
           player->gold);
}