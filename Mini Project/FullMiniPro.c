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

    int potions[2];
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
        {"Woodle Sword", 100, 10, 0},
        {"Woodle Shield", 100, 0, 5},
        {"Woodle Armor", 200, 0, 15}};

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

void initializePlayer(Player *player);

void showTitle(void);
void mainMenu(Player *player);

void settingsMenu(void);

void story(Player *player);

void showStatus(const Player *player, const Monster *monster, int wave);

void createSlime(Monster *monster);

void createMonster(Monster *monster, int wave);

void combat(Player *player, Monster *monster, int wave);

int playerAttack(Player *player, Monster *monster);
int useSpell(Player *player, Monster *monster);
int usePotions(Player *player, Monster *monster);

void backpack(Player *player, Monster *monster);

int playerTurn(Player *player, Monster *monster);

void monsterAttack(Player *player, const Monster *monster);

void firstSlimeBattle(Player *player);

void shop(Player *player, int magicUnlocked);

void weaponShop(Player *player);
void potionShop(Player *player);
void magicShop(Player *player);

void buyWeapon(Player *player, int index);
void buyPotion(Player *player, int index);
void buySpell(Player *player, int index);

void dungeon20(Player *player);
void infinityDungeon(Player *player);

void victoryReward(Player *player, int wave);

int calculateDamage(int attack, int defense);

int askAction(void);

/* =========================================================
   MAIN
   ========================================================= */

int main(void)
{
    Player player;

    srand((unsigned int)time(NULL));

    initializePlayer(&player);

    showTitle();

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
        /* clear input buffer */
    }
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
    printf("\n");
    printf("=============================================================\n");
    printf("                    POOP ADVENTURE\n");
    printf("=============================================================\n");
    printf("                     POOP RPG GAME\n");
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
        printf("               o---------------------o\n");
        printf("               |        Start        |\n");
        printf("               o---------------------o\n");
        printf("               o---------------------o\n");
        printf("               |       Setting       |\n");
        printf("               o---------------------o\n");
        printf("               o---------------------o\n");
        printf("               |        Exit         |\n");
        printf("               o---------------------o\n");
        printf("Press any key to continue . . . (1=Start/2=Setting/0=Exit)\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            story(player);

            /*
                First battle
            */
            firstSlimeBattle(player);

            /*
                If player dies
            */
            if (player->hp <= 0)
            {
                printf("\nGAME OVER!\n");
                return;
            }

            /*
                First shop
            */
            shop(player, 0);

            /*
                20 Wave Dungeon
            */
            dungeon20(player);

            /*
                If player dies
            */
            if (player->hp <= 0)
            {
                printf("\nGAME OVER!\n");
                return;
            }

            /*
                Second shop
                Magic unlocked
            */
            printf("\n");
            printf("=============================================================\n");
            printf("You survived the 20 Wave Dungeon!\n");
            printf("A mysterious shop appeared before you...\n");
            printf("=============================================================\n");

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
            printf("\nThank you for playing!\n");
            break;

        default:
            printf("\nInvalid choice!\n");
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
        printf("             o-----------------------o\n");
        printf("             |       Settings        |\n");
        printf("             o-----------------------o\n");
        printf("              o---------------------o\n");
        printf("              | Music :       %-6d|\n", music);
        printf("              o---------------------o\n");
        printf("              o---------------------o\n");
        printf("              | FPS   :       %-6d|\n", fps);
        printf("              o---------------------o\n");
        printf("              o---------------------o\n");
        printf("              |        Exit         |\n");
        printf("              o---------------------o\n");
        printf("Press any key to continue . . . (1=Music/2=FPS/0=Exit)\n");

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
            }
        }

    } while (choice != 0);
}

/* =========================================================
   STORY
   ========================================================= */

void story(Player *player)
{
    printf("\n");
    printf("Once upon a time, in a faraway land...\n");

    pauseGame();

    printf("\n");
    printf("There lived a young adventurer who dreamed of exploring the world.\n");
    printf("One day, the adventurer decided to travel deep into a mysterious forest.\n");

    pauseGame();

    printf("\nWhat is your name?\n");
    printf("> ");

    scanf("%49s", player->name);

    printf("\nHello, %s! Welcome to the adventure.\n", player->name);

    pauseGame();

    printf("\nYou walk through the forest for several hours.\n");
    printf("However, the deeper you go, the less familiar the path becomes.\n");

    pauseGame();

    printf("\nSuddenly, you realize something...\n");
    printf("You are completely lost.\n");

    pauseGame();

    printf("\nYou look around, trying to find a way out.\n");
    printf("Then, you hear a strange growling sound from behind the trees.\n");

    pauseGame();

    printf("\nYou slowly turn around...\n");
    printf("A huge monster jumps out from the bushes!\n");

    pauseGame();

    printf("\nThe monster looks at you and lets out a terrifying roar!\n");

    printf("\n%s, what will you do?\n", player->name);

    pauseGame();
}

/* =========================================================
   STATUS
   ========================================================= */

void showStatus(const Player *player, const Monster *monster, int wave)
{
    printf("\n");
    printf("=============================================================\n");

    if (wave > 0)
    {
        printf("                        WAVE %d\n", wave);
    }
    else
    {
        printf("                       BATTLE\n");
    }

    printf("=============================================================\n");

    printf("%-20s HP: %d/%d\n",
           player->name,
           player->hp,
           player->maxHp);

    printf("%-20s MP: %d/%d\n",
           player->name,
           player->mp,
           player->maxMp);

    printf("ATK: %-5d DEF: %-5d GOLD: %-8d\n",
           player->atk,
           player->def,
           player->gold);

    printf("\n");

    printf("%-20s HP: %d/%d\n",
           monster->name,
           monster->hp,
           monster->maxHp);

    printf("%-20s ATK: %d DEF: %d\n",
           monster->name,
           monster->atk,
           monster->def);

    printf("=============================================================\n");
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

/*
    Wave scaling:

    Wave 1:
        Goblin
        HP = 100
        ATK = 10

    Wave 5:
        Orc
        HP = 1000
        ATK = 100

    Wave 10:
        Orc
        HP = 2000
        ATK = 200

    Wave 15:
        Orc
        HP = 3000
        ATK = 300

    Wave 20:
        King Skeleton
        HP = 10000
        ATK = 1000

    This follows your original formula:
        Orc HP  = 200 * wave
        Orc ATK = 20 * wave

        Goblin HP  = 100 * wave
        Goblin ATK = 10 * wave

        King Skeleton HP  = 500 * wave
        King Skeleton ATK = 50 * wave
*/

void createMonster(Monster *monster, int wave)
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

int calculateDamage(int attack, int defense)
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

    printf("\n");
    printf("=============================================================\n");
    printf("                    SLIME BATTLE\n");
    printf("=============================================================\n");

    combat(player, &slime, 0);

    if (player->hp > 0 && slime.hp <= 0)
    {
        printf("\nCongratulations! You defeated the slime!\n");

        printf("You gained 100000 Gold!\n");

        player->gold += 100000;

        printf("Current Gold: %d\n", player->gold);

        pauseGame();
    }
}

/* =========================================================
   COMBAT
   ========================================================= */

void combat(Player *player, Monster *monster, int wave)
{
    int result;

    while (player->hp > 0 && monster->hp > 0)
    {
        showStatus(player, monster, wave);

        result = playerTurn(player, monster);

        /*
            0 = run
            1 = continue
        */

        if (result == 0)
        {
            printf("\nYou ran away!\n");
            break;
        }

        if (monster->hp <= 0)
        {
            break;
        }

        /*
            Monster attacks after player's action
        */
        monsterAttack(player, monster);

        if (player->hp <= 0)
        {
            printf("\n%s defeated you!\n", monster->name);
            break;
        }
    }
}

/* =========================================================
   PLAYER TURN
   ========================================================= */

int playerTurn(Player *player, Monster *monster)
{
    int choice;

    printf("\n");
    printf("o-------------o  o------------o  o------------o  o------------o\n");
    printf("|  1.Fight    |  |  2.Magic   |  | 3.Backpack |  |   4.Run    |\n");
    printf("o-------------o  o------------o  o------------o  o------------o\n");

    printf("What will you do? ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        return playerAttack(player, monster);
    }

    else if (choice == 2)
    {
        useSpell(player, monster);
        return 1;
    }

    else if (choice == 3)
    {
        backpack(player, monster);
        return 1;
    }

    else if (choice == 4)
    {
        return 0;
    }

    else
    {
        printf("Invalid choice!\n");
        return 1;
    }
}

/* =========================================================
   NORMAL ATTACK
   ========================================================= */

int playerAttack(Player *player, Monster *monster)
{
    int damage;

    printf("\n%s uses Slash!\n", player->name);

    /*
        Critical chance = 20%
    */

    if (rand() % 100 < 20)
    {
        damage = player->atk * 2;

        damage = calculateDamage(damage, monster->def);

        printf("CRITICAL HIT!\n");
    }
    else
    {
        damage = calculateDamage(player->atk, monster->def);
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

void monsterAttack(Player *player, const Monster *monster)
{
    int damage;

    /*
        10% chance critical attack
    */

    if (rand() % 100 < 10)
    {
        damage = monster->atk * 2;

        damage = calculateDamage(damage, player->def);

        printf("\n%s uses a CRITICAL ATTACK!\n",
               monster->name);
    }
    else
    {
        damage = calculateDamage(monster->atk, player->def);

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

int useSpell(Player *player, Monster *monster)
{
    int choice;

    printf("\n");
    printf("=============================================================\n");
    printf("                         MAGIC\n");
    printf("=============================================================\n");

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

    printf("Choose magic: ");
    scanf("%d", &choice);

    if (choice == 0)
    {
        return 0;
    }

    if (choice < 1 || choice > SPELL_COUNT)
    {
        printf("Invalid magic!\n");
        return 0;
    }

    int index = choice - 1;

    if (!player->spells[index])
    {
        printf("You don't own this spell!\n");
        return 0;
    }

    Spell *spell = &spells[index];

    if (player->mp < spell->mpCost)
    {
        printf("Not enough MP!\n");
        return 0;
    }

    player->mp -= spell->mpCost;

    printf("\nYou cast %s!\n", spell->name);

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
        player->hp += spell->heal;

        if (player->hp > player->maxHp)
        {
            player->hp = player->maxHp;
        }

        printf("You healed %d HP!\n",
               spell->heal);
    }

    return 1;
}

/* =========================================================
   BACKPACK
   ========================================================= */

void backpack(Player *player, Monster *monster)
{
    int choice;

    printf("\n");
    printf("=============================================================\n");
    printf("                       BACKPACK\n");
    printf("=============================================================\n");

    printf("1. HP Potion x%d\n",
           player->potions[0]);

    printf("2. MP Potion x%d\n",
           player->potions[1]);

    printf("0. Exit\n");

    printf("Choose item: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        usePotions(player, monster);
    }
    else if (choice == 2)
    {
        usePotions(player, monster);
    }
}

/* =========================================================
   POTION USE
   ========================================================= */

int usePotions(Player *player, Monster *monster)
{
    int choice;

    (void)monster;

    printf("\n");
    printf("1. HP Potion x%d\n",
           player->potions[0]);

    printf("2. MP Potion x%d\n",
           player->potions[1]);

    printf("0. Exit\n");

    printf("Choose potion: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        if (player->potions[0] <= 0)
        {
            printf("You don't have HP Potion!\n");
            return 0;
        }

        player->potions[0]--;

        player->hp += potions[0].healHp;

        if (player->hp > player->maxHp)
        {
            player->hp = player->maxHp;
        }

        printf("You recovered 50 HP!\n");

        return 1;
    }

    else if (choice == 2)
    {
        if (player->potions[1] <= 0)
        {
            printf("You don't have MP Potion!\n");
            return 0;
        }

        player->potions[1]--;

        player->mp += potions[1].healMp;

        if (player->mp > player->maxMp)
        {
            player->mp = player->maxMp;
        }

        printf("You recovered 50 MP!\n");

        return 1;
    }

    return 0;
}

/* =========================================================
   SHOP
   ========================================================= */

void shop(Player *player, int magicUnlocked)
{
    int choice;

    do
    {
        printf("\n");
        printf("=============================================================\n");
        printf("                         SHOP\n");
        printf("=============================================================\n");

        printf("Gold: %d\n", player->gold);

        printf("\n");
        printf("1. Weapons\n");
        printf("2. Potions\n");

        if (magicUnlocked)
        {
            printf("3. Magic\n");
        }

        printf("0. Exit\n");

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

        else if (choice == 3 && magicUnlocked)
        {
            magicShop(player);
        }

        else if (choice != 0)
        {
            printf("Invalid choice!\n");
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

        if (choice >= 1 && choice <= WEAPON_COUNT)
        {
            buyWeapon(player, choice - 1);
        }

    } while (choice != 0);
}

/* =========================================================
   BUY WEAPON
   ========================================================= */

void buyWeapon(Player *player, int index)
{
    Weapon *weapon = &weapons[index];

    if (player->gold < weapon->price)
    {
        printf("Not enough gold!\n");
        return;
    }

    player->gold -= weapon->price;

    player->atk += weapon->atkBonus;
    player->def += weapon->defBonus;

    player->weaponLevel++;

    printf("\nYou bought %s!\n",
           weapon->name);

    printf("ATK: %d\n", player->atk);
    printf("DEF: %d\n", player->def);
    printf("Gold: %d\n", player->gold);
}

/* =========================================================
   POTION SHOP
   ========================================================= */

void potionShop(Player *player)
{
    int choice;

    do
    {
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

        if (choice >= 1 && choice <= POTION_COUNT)
        {
            buyPotion(player, choice - 1);
        }

    } while (choice != 0);
}

/* =========================================================
   BUY POTION
   ========================================================= */

void buyPotion(Player *player, int index)
{
    Potion *potion = &potions[index];

    if (player->gold < potion->price)
    {
        printf("Not enough gold!\n");
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
        printf("\n");
        printf("=============================================================\n");
        printf("                      MAGIC SHOP\n");
        printf("=============================================================\n");

        for (int i = 0; i < SPELL_COUNT; i++)
        {
            printf("%d. %-15s Price:%-5d MP:%-3d\n",
                   i + 1,
                   spells[i].name,
                   spells[i].price,
                   spells[i].mpCost);
        }

        printf("0. Exit\n");

        printf("\nGold: %d\n",
               player->gold);

        printf("Choose spell: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= SPELL_COUNT)
        {
            buySpell(player, choice - 1);
        }

    } while (choice != 0);
}

/* =========================================================
   BUY SPELL
   ========================================================= */

void buySpell(Player *player, int index)
{
    Spell *spell = &spells[index];

    if (player->spells[index])
    {
        printf("You already own %s!\n",
               spell->name);

        return;
    }

    if (player->gold < spell->price)
    {
        printf("Not enough gold!\n");
        return;
    }

    player->gold -= spell->price;

    player->spells[index] = 1;

    printf("\nYou learned %s!\n",
           spell->name);

    printf("Gold remaining: %d\n",
           player->gold);
}

/* =========================================================
   20 WAVE DUNGEON
   ========================================================= */

void dungeon20(Player *player)
{
    printf("\n");
    printf("=============================================================\n");
    printf("                    20 WAVE DUNGEON\n");
    printf("=============================================================\n");

    pauseGame();

    for (int wave = 1; wave <= 20; wave++)
    {
        Monster monster;

        createMonster(&monster, wave);

        printf("\n");
        printf("=============================================================\n");
        printf("                       WAVE %d\n", wave);
        printf("                       %s\n", monster.name);
        printf("=============================================================\n");

        combat(player, &monster, wave);

        /*
            Player ran away
            In this version, running ends the dungeon.
        */
        if (monster.hp > 0)
        {
            printf("\nYou escaped from Wave %d.\n",
                   wave);

            return;
        }

        if (player->hp <= 0)
        {
            printf("\nYou died at Wave %d.\n",
                   wave);

            return;
        }

        victoryReward(player, wave);

        /*
            Recover a little after each wave
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

        printf("\nYou recover after the wave.\n");
        printf("HP: %d/%d\n",
               player->hp,
               player->maxHp);

        printf("MP: %d/%d\n",
               player->mp,
               player->maxMp);

        pauseGame();
    }

    printf("\n");
    printf("=============================================================\n");
    printf("              CONGRATULATIONS!\n");
    printf("              YOU CLEARED 20 WAVES!\n");
    printf("=============================================================\n");

    pauseGame();
}

/* =========================================================
   INFINITY DUNGEON
   ========================================================= */

void infinityDungeon(Player *player)
{
    int wave = 21;

    printf("\n");
    printf("=============================================================\n");
    printf("                     INFINITY DUNGEON\n");
    printf("=============================================================\n");

    printf("There is no end...\n");
    printf("The monsters will continue getting stronger.\n");

    pauseGame();

    while (player->hp > 0)
    {
        Monster monster;

        createMonster(&monster, wave);

        /*
            Infinity scaling after wave 20
        */

        if (wave % 5 == 0)
        {
            /*
                Every 5 waves = Orc/Boss
            */

            strcpy(monster.name, "Infinity Orc");

            monster.maxHp = 200 * wave;
            monster.hp = monster.maxHp;

            monster.atk = 20 * wave;
            monster.def = wave / 2;

            monster.isBoss = 1;
        }
        else
        {
            strcpy(monster.name, "Infinity Goblin");

            monster.maxHp = 100 * wave;
            monster.hp = monster.maxHp;

            monster.atk = 10 * wave;
            monster.def = wave / 2;

            monster.isBoss = 0;
        }

        /*
            Every 10 waves becomes stronger
        */

        if (wave % 10 == 0)
        {
            monster.maxHp *= 2;
            monster.hp = monster.maxHp;

            monster.atk *= 2;

            printf("\n");
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("                  SPECIAL INFINITY BOSS\n");
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }

        printf("\n");
        printf("=============================================================\n");
        printf("                  INFINITY WAVE %d\n", wave);
        printf("                  %s\n", monster.name);
        printf("=============================================================\n");

        combat(player, &monster, wave);

        if (player->hp <= 0)
        {
            printf("\n");
            printf("=============================================================\n");
            printf("                 INFINITY DUNGEON END\n");
            printf("=============================================================\n");

            printf("%s reached Wave %d!\n",
                   player->name,
                   wave);

            printf("You have been defeated.\n");

            break;
        }

        if (monster.hp > 0)
        {
            printf("\nYou escaped from the dungeon.\n");
            break;
        }

        /*
            Reward
        */

        victoryReward(player, wave);

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

        /*
            Increase wave
        */

        wave++;

        pauseGame();
    }
}

/* =========================================================
   REWARD
   ========================================================= */

void victoryReward(Player *player, int wave)
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