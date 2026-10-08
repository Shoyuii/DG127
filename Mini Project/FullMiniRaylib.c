#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* =========================================================
   CONSTANTS
   ========================================================= */

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 700

#define MAX_NAME 50

#define WEAPON_COUNT 3
#define POTION_COUNT 2
#define SPELL_COUNT 4

#define SLIME_HP 100
#define SLIME_ATK 10

/* =========================================================
   ENUMS
   ========================================================= */

typedef enum
{
    SCREEN_TITLE,
    SCREEN_MENU,
    SCREEN_SETTINGS,
    SCREEN_STORY,
    SCREEN_BATTLE,
    SCREEN_SHOP,
    SCREEN_WEAPON_SHOP,
    SCREEN_POTION_SHOP,
    SCREEN_MAGIC_SHOP,
    SCREEN_BACKPACK,
    SCREEN_DUNGEON,
    SCREEN_INFINITY,
    SCREEN_GAMEOVER,
    SCREEN_VICTORY
} GameScreen;

typedef enum
{
    BATTLE_FIGHT,
    BATTLE_MAGIC,
    BATTLE_BACKPACK,
    BATTLE_RUN
} BattleMenu;

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

} Spell;

/* =========================================================
   DATA
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
   GLOBAL GAME DATA
   ========================================================= */

Player player;
Monster monster;

GameScreen currentScreen = SCREEN_TITLE;

/* FIX: ใช้ตัวแปรนี้ควบคุมการออกจากเกม */
bool gameRunning = true;

int dungeonWave = 0;
int infinityWave = 21;

int magicUnlocked = 0;

int selectedMenu = 0;
int selectedShop = 0;

int storyStep = 0;

float messageTimer = 0.0f;

char gameMessage[256] = "";

/* =========================================================
   COLORS
   ========================================================= */

Color BG_COLOR = {20, 20, 30, 255};
Color PANEL_COLOR = {35, 35, 50, 255};
Color PANEL_LIGHT = {50, 50, 70, 255};

Color WHITE_COLOR = {245, 245, 245, 255};
Color GRAY_COLOR = {160, 160, 170, 255};

Color RED_COLOR = {220, 60, 60, 255};
Color GREEN_COLOR = {70, 210, 100, 255};
Color BLUE_COLOR = {70, 140, 240, 255};
Color YELLOW_COLOR = {240, 200, 60, 255};
Color PURPLE_COLOR = {170, 80, 220, 255};
Color ORANGE_COLOR = {240, 130, 50, 255};

Color PLAYER_COLOR = {80, 170, 255, 255};
Color MONSTER_COLOR = {220, 80, 80, 255};

/* =========================================================
   UTILITY
   ========================================================= */

void SetMessage(const char *message)
{
    snprintf(gameMessage,
             sizeof(gameMessage),
             "%s",
             message);

    messageTimer = 3.0f;
}

void UpdateMessage(void)
{
    if (messageTimer > 0)
    {
        messageTimer -= GetFrameTime();

        if (messageTimer < 0)
            messageTimer = 0;
    }
}

void DrawCenteredText(const char *text,
                      int y,
                      int fontSize,
                      Color color)
{
    int width = MeasureText(text, fontSize);

    DrawText(text,
             SCREEN_WIDTH / 2 - width / 2,
             y,
             fontSize,
             color);
}

void DrawButton(Rectangle rect,
                const char *text,
                bool selected)
{
    Color color = selected ? BLUE_COLOR : PANEL_COLOR;

    DrawRectangleRec(rect, color);

    DrawRectangleLinesEx(rect,
                         2,
                         selected ? WHITE_COLOR : GRAY_COLOR);

    int fontSize = 22;

    int width = MeasureText(text, fontSize);

    DrawText(text,
             (int)(rect.x + rect.width / 2 - width / 2),
             (int)(rect.y + rect.height / 2 - fontSize / 2),
             fontSize,
             WHITE_COLOR);
}

bool ButtonPressed(Rectangle rect)
{
    return CheckCollisionPointRec(
               GetMousePosition(),
               rect) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void DrawBar(int x,
             int y,
             int width,
             int height,
             int value,
             int maxValue,
             Color color)
{
    float ratio = 0;

    if (maxValue > 0)
        ratio = (float)value / maxValue;

    if (ratio < 0)
        ratio = 0;

    if (ratio > 1)
        ratio = 1;

    DrawRectangle(x,
                  y,
                  width,
                  height,
                  (Color){50, 50, 50, 255});

    DrawRectangle(x,
                  y,
                  (int)(width * ratio),
                  height,
                  color);

    DrawRectangleLines(x,
                       y,
                       width,
                       height,
                       WHITE_COLOR);
}

void DrawPanel(Rectangle rect)
{
    DrawRectangleRec(rect, PANEL_COLOR);
    DrawRectangleLinesEx(rect,
                         2,
                         GRAY_COLOR);
}

/* =========================================================
   INITIALIZE PLAYER
   ========================================================= */

void InitializePlayer(void)
{
    memset(&player, 0, sizeof(Player));

    strcpy(player.name, "Adventurer");

    player.maxHp = 100;
    player.hp = 100;

    player.maxMp = 50;
    player.mp = 50;

    player.atk = 20;
    player.def = 5;

    player.gold = 0;

    player.weaponLevel = 0;
}

/* =========================================================
   DAMAGE
   ========================================================= */

int CalculateDamage(int attack,
                    int defense)
{
    int damage = attack - defense;

    if (damage < 1)
        damage = 1;

    return damage;
}

/* =========================================================
   MONSTER CREATION
   ========================================================= */

void CreateSlime(Monster *m)
{
    strcpy(m->name, "Slime");

    m->maxHp = SLIME_HP;
    m->hp = SLIME_HP;

    m->atk = SLIME_ATK;
    m->def = 2;

    m->isBoss = 0;
}

void CreateMonster(Monster *m,
                   int wave)
{
    if (wave == 20)
    {
        strcpy(m->name, "King Skeleton");

        m->maxHp = 500 * wave;
        m->hp = m->maxHp;

        m->atk = 50 * wave;
        m->def = 20;

        m->isBoss = 1;
    }
    else if (wave % 5 == 0)
    {
        strcpy(m->name, "Orc");

        m->maxHp = 200 * wave;
        m->hp = m->maxHp;

        m->atk = 20 * wave;
        m->def = wave;

        m->isBoss = 1;
    }
    else
    {
        strcpy(m->name, "Goblin");

        m->maxHp = 100 * wave;
        m->hp = m->maxHp;

        m->atk = 10 * wave;
        m->def = wave / 2;

        m->isBoss = 0;
    }
}

/* =========================================================
   START BATTLE
   ========================================================= */

void StartBattle(Monster m,
                 int wave)
{
    monster = m;
    dungeonWave = wave;

    currentScreen = SCREEN_BATTLE;

    selectedMenu = 0;
}

/* =========================================================
   MONSTER ATTACK
   ========================================================= */

void MonsterAttack(void)
{
    int damage;

    bool critical = rand() % 100 < 10;

    if (critical)
    {
        damage = CalculateDamage(
            monster.atk * 2,
            player.def);

        SetMessage("CRITICAL ATTACK!");
    }
    else
    {
        damage = CalculateDamage(
            monster.atk,
            player.def);

        SetMessage("Monster attacked!");
    }

    player.hp -= damage;

    if (player.hp < 0)
        player.hp = 0;
}

/* =========================================================
   PLAYER ATTACK
   ========================================================= */

void PlayerAttack(void)
{
    int damage;

    bool critical = rand() % 100 < 20;

    if (critical)
    {
        damage = CalculateDamage(
            player.atk * 2,
            monster.def);

        SetMessage("CRITICAL HIT!");
    }
    else
    {
        damage = CalculateDamage(
            player.atk,
            monster.def);

        SetMessage("You attacked!");
    }

    monster.hp -= damage;

    if (monster.hp < 0)
        monster.hp = 0;

    if (monster.hp > 0)
    {
        MonsterAttack();
    }
}

/* =========================================================
   USE SPELL
   ========================================================= */

void CastSpell(int index)
{
    if (!player.spells[index])
    {
        SetMessage("You don't own this spell!");
        return;
    }

    Spell *spell = &spells[index];

    if (player.mp < spell->mpCost)
    {
        SetMessage("Not enough MP!");
        return;
    }

    player.mp -= spell->mpCost;

    if (spell->type == 1)
    {
        int damage = CalculateDamage(
            player.atk + spell->damage,
            monster.def);

        monster.hp -= damage;

        if (monster.hp < 0)
            monster.hp = 0;

        char text[256];

        snprintf(text,
                 sizeof(text),
                 "%s dealt %d damage!",
                 spell->name,
                 damage);

        SetMessage(text);

        if (monster.hp > 0)
            MonsterAttack();
    }
    else
    {
        int oldHp = player.hp;

        player.hp += spell->heal;

        if (player.hp > player.maxHp)
            player.hp = player.maxHp;

        char text[256];

        snprintf(text,
                 sizeof(text),
                 "Heal restored %d HP!",
                 player.hp - oldHp);

        SetMessage(text);
    }
}

/* =========================================================
   USE POTION
   ========================================================= */

void UsePotion(int index)
{
    if (player.potions[index] <= 0)
    {
        SetMessage("You don't have this potion!");
        return;
    }

    player.potions[index]--;

    if (index == 0)
    {
        player.hp += potions[index].healHp;

        if (player.hp > player.maxHp)
            player.hp = player.maxHp;

        SetMessage("Recovered HP!");
    }
    else
    {
        player.mp += potions[index].healMp;

        if (player.mp > player.maxMp)
            player.mp = player.maxMp;

        SetMessage("Recovered MP!");
    }

    MonsterAttack();
}

/* =========================================================
   VICTORY REWARD
   ========================================================= */

void VictoryReward(int wave)
{
    int reward = 1000 * wave;

    if (wave == 20)
        reward += 10000;

    player.gold += reward;

    char text[256];

    snprintf(text,
             sizeof(text),
             "Victory! +%d Gold",
             reward);

    SetMessage(text);
}

/* =========================================================
   BATTLE FINISH
   ========================================================= */

void CheckBattleEnd(void)
{
    if (player.hp <= 0)
    {
        currentScreen = SCREEN_GAMEOVER;
        return;
    }

    if (monster.hp <= 0)
    {
        VictoryReward(dungeonWave);

        if (dungeonWave == 0)
        {
            player.gold += 100000;

            SetMessage("Slime defeated! +100000 Gold!");
        }

        else if (dungeonWave >= 1 &&
                 dungeonWave <= 20)
        {
            player.hp += player.maxHp / 10;

            if (player.hp > player.maxHp)
                player.hp = player.maxHp;

            player.mp += player.maxMp / 10;

            if (player.mp > player.maxMp)
                player.mp = player.maxMp;

            if (dungeonWave == 20)
            {
                magicUnlocked = 1;

                currentScreen = SCREEN_VICTORY;

                return;
            }

            currentScreen = SCREEN_DUNGEON;
        }

        else
        {
            player.hp += player.maxHp / 10;

            if (player.hp > player.maxHp)
                player.hp = player.maxHp;

            player.mp += player.maxMp / 10;

            if (player.mp > player.maxMp)
                player.mp = player.maxMp;

            infinityWave++;

            currentScreen = SCREEN_INFINITY;
        }
    }
}

/* =========================================================
   TITLE SCREEN
   ========================================================= */

void DrawTitleScreen(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "POOP ADVENTURE",
        130,
        60,
        YELLOW_COLOR);

    DrawCenteredText(
        "A Raylib Adventure",
        205,
        25,
        GRAY_COLOR);

    DrawCenteredText(
        "Presented by",
        300,
        20,
        WHITE_COLOR);

    DrawCenteredText(
        "Jittarin Panyakam | Phatpoom Inkaewsub | Ronnaranok Kongkamol",
        335,
        18,
        GRAY_COLOR);

    DrawCenteredText(
        "Press ENTER to continue",
        560,
        25,
        WHITE_COLOR);

    if (IsKeyPressed(KEY_ENTER) ||
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        currentScreen = SCREEN_MENU;
    }
}

/* =========================================================
   MAIN MENU
   ========================================================= */

void DrawMainMenu(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "POOP ADVENTURE",
        80,
        55,
        YELLOW_COLOR);

    Rectangle start =
        {
            400, 220, 300, 60};

    Rectangle settings =
        {
            400, 300, 300, 60};

    Rectangle exit =
        {
            400, 380, 300, 60};

    DrawButton(start,
               "START",
               selectedMenu == 0);

    DrawButton(settings,
               "SETTINGS",
               selectedMenu == 1);

    DrawButton(exit,
               "EXIT",
               selectedMenu == 2);

    /* =====================================================
       KEYBOARD MENU CONTROL
       ===================================================== */

    if (IsKeyPressed(KEY_DOWN))
    {
        selectedMenu++;

        if (selectedMenu > 2)
            selectedMenu = 0;
    }

    if (IsKeyPressed(KEY_UP))
    {
        selectedMenu--;

        if (selectedMenu < 0)
            selectedMenu = 2;
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if (selectedMenu == 0)
        {
            InitializePlayer();

            storyStep = 0;

            currentScreen = SCREEN_STORY;
        }
        else if (selectedMenu == 1)
        {
            currentScreen = SCREEN_SETTINGS;
        }
        else if (selectedMenu == 2)
        {
            /* FIX: ไม่เรียก CloseWindow() ตรงนี้ */
            gameRunning = false;
        }
    }

    /* =====================================================
       MOUSE MENU CONTROL
       ===================================================== */

    if (ButtonPressed(start))
    {
        InitializePlayer();

        storyStep = 0;

        currentScreen = SCREEN_STORY;
    }

    if (ButtonPressed(settings))
    {
        currentScreen = SCREEN_SETTINGS;
    }

    if (ButtonPressed(exit))
    {
        /* FIX: ให้ main() เป็นคนปิด Window */
        gameRunning = false;
    }
}

/* =========================================================
   STORY
   ========================================================= */

void DrawStory(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "THE ADVENTURE BEGINS",
        70,
        40,
        YELLOW_COLOR);

    Rectangle box =
        {
            100,
            170,
            900,
            300};

    DrawPanel(box);

    const char *texts[] =
        {
            "Once upon a time, in a faraway land...",
            "There lived a young adventurer who dreamed of exploring the world.",
            "One day, the adventurer entered a mysterious forest.",
            "The deeper you go, the less familiar the path becomes.",
            "Suddenly, you realize something...",
            "You are completely lost.",
            "A strange growling sound comes from behind the trees.",
            "You slowly turn around...",
            "A huge monster jumps out from the bushes!",
            "The adventure begins!"};

    DrawText(
        texts[storyStep],
        150,
        230,
        25,
        WHITE_COLOR);

    DrawText(
        "Press ENTER / SPACE to continue",
        360,
        530,
        22,
        GRAY_COLOR);

    if (IsKeyPressed(KEY_ENTER) ||
        IsKeyPressed(KEY_SPACE))
    {
        storyStep++;

        if (storyStep >= 10)
        {
            CreateSlime(&monster);

            dungeonWave = 0;

            currentScreen = SCREEN_BATTLE;
        }
    }
}

/* =========================================================
   DRAW PLAYER / MONSTER
   ========================================================= */

void DrawCharacter(bool playerCharacter,
                   int x,
                   int y)
{
    Color color =
        playerCharacter ? PLAYER_COLOR : MONSTER_COLOR;

    DrawCircle(x,
               y,
               45,
               color);

    DrawCircle(x - 15,
               y - 8,
               7,
               WHITE_COLOR);

    DrawCircle(x + 15,
               y - 8,
               7,
               WHITE_COLOR);

    DrawCircle(x - 15,
               y - 8,
               3,
               BG_COLOR);

    DrawCircle(x + 15,
               y - 8,
               3,
               BG_COLOR);

    DrawLine(x - 15,
             y + 18,
             x + 15,
             y + 18,
             WHITE_COLOR);
}

/* =========================================================
   BATTLE SCREEN
   ========================================================= */

void DrawBattle(void)
{
    ClearBackground(BG_COLOR);

    char waveText[100];

    if (dungeonWave == 0)
    {
        strcpy(waveText, "FIRST BATTLE");
    }
    else
    {
        snprintf(waveText,
                 sizeof(waveText),
                 "WAVE %d",
                 dungeonWave);
    }

    DrawCenteredText(
        waveText,
        25,
        35,
        YELLOW_COLOR);

    DrawPanel((Rectangle){
        60, 100, 450, 300});

    DrawPanel((Rectangle){
        590, 100, 450, 300});

    DrawCenteredText(
        monster.name,
        115,
        28,
        RED_COLOR);

    DrawCenteredText(
        player.name,
        115,
        28,
        PLAYER_COLOR);

    DrawCharacter(
        false,
        285,
        230);

    DrawCharacter(
        true,
        815,
        230);

    DrawBar(
        120,
        315,
        330,
        25,
        monster.hp,
        monster.maxHp,
        RED_COLOR);

    DrawBar(
        650,
        315,
        330,
        25,
        player.hp,
        player.maxHp,
        GREEN_COLOR);

    char enemyHP[100];

    snprintf(enemyHP,
             sizeof(enemyHP),
             "HP: %d / %d",
             monster.hp,
             monster.maxHp);

    DrawCenteredText(
        enemyHP,
        350,
        18,
        WHITE_COLOR);

    char playerHP[100];

    snprintf(playerHP,
             sizeof(playerHP),
             "HP: %d / %d",
             player.hp,
             player.maxHp);

    DrawCenteredText(
        playerHP,
        350,
        18,
        WHITE_COLOR);

    DrawText(
        TextFormat("ATK: %d", monster.atk),
        90,
        375,
        18,
        GRAY_COLOR);

    DrawText(
        TextFormat("DEF: %d", monster.def),
        300,
        375,
        18,
        GRAY_COLOR);

    DrawText(
        TextFormat("ATK: %d", player.atk),
        620,
        375,
        18,
        GRAY_COLOR);

    DrawText(
        TextFormat("DEF: %d", player.def),
        830,
        375,
        18,
        GRAY_COLOR);

    DrawBar(
        650,
        395,
        150,
        18,
        player.mp,
        player.maxMp,
        BLUE_COLOR);

    DrawText(
        TextFormat("MP %d/%d",
                   player.mp,
                   player.maxMp),
        810,
        392,
        18,
        WHITE_COLOR);

    DrawText(
        TextFormat("Gold: %d",
                   player.gold),
        60,
        30,
        20,
        YELLOW_COLOR);

    Rectangle fight =
        {
            70, 470, 220, 60};

    Rectangle magic =
        {
            310, 470, 220, 60};

    Rectangle backpack =
        {
            550, 470, 220, 60};

    Rectangle run =
        {
            790, 470, 220, 60};

    DrawButton(fight,
               "1. FIGHT",
               false);

    DrawButton(magic,
               "2. MAGIC",
               false);

    DrawButton(backpack,
               "3. BACKPACK",
               false);

    DrawButton(run,
               "4. RUN",
               false);

    if (gameMessage[0] != '\0' &&
        messageTimer > 0)
    {
        DrawCenteredText(
            gameMessage,
            610,
            23,
            YELLOW_COLOR);
    }

    if (IsKeyPressed(KEY_ONE))
        PlayerAttack();

    if (IsKeyPressed(KEY_TWO))
        currentScreen = SCREEN_MAGIC_SHOP;

    if (IsKeyPressed(KEY_THREE))
        currentScreen = SCREEN_BACKPACK;

    if (IsKeyPressed(KEY_FOUR))
    {
        SetMessage("You ran away!");

        if (dungeonWave == 0)
            currentScreen = SCREEN_MENU;
        else if (dungeonWave <= 20)
            currentScreen = SCREEN_DUNGEON;
        else
            currentScreen = SCREEN_INFINITY;
    }

    if (ButtonPressed(fight))
        PlayerAttack();

    if (ButtonPressed(magic))
        currentScreen = SCREEN_MAGIC_SHOP;

    if (ButtonPressed(backpack))
        currentScreen = SCREEN_BACKPACK;

    if (ButtonPressed(run))
    {
        if (dungeonWave == 0)
            currentScreen = SCREEN_MENU;
        else if (dungeonWave <= 20)
            currentScreen = SCREEN_DUNGEON;
        else
            currentScreen = SCREEN_INFINITY;
    }

    CheckBattleEnd();
}

/* =========================================================
   MAGIC SCREEN
   ========================================================= */

void DrawMagicScreen(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "MAGIC",
        50,
        40,
        PURPLE_COLOR);

    DrawText(
        TextFormat("MP: %d / %d",
                   player.mp,
                   player.maxMp),
        70,
        115,
        22,
        BLUE_COLOR);

    for (int i = 0; i < SPELL_COUNT; i++)
    {
        int y = 170 + i * 75;

        Rectangle r =
            {
                120,
                y,
                860,
                60};

        Color c =
            player.spells[i] ? PANEL_LIGHT : (Color){30, 30, 35, 255};

        DrawRectangleRec(r, c);

        DrawRectangleLinesEx(
            r,
            2,
            player.spells[i] ? PURPLE_COLOR : GRAY_COLOR);

        DrawText(
            TextFormat("%d. %s",
                       i + 1,
                       spells[i].name),
            145,
            y + 17,
            22,
            WHITE_COLOR);

        DrawText(
            TextFormat("MP: %d",
                       spells[i].mpCost),
            500,
            y + 17,
            20,
            BLUE_COLOR);

        if (spells[i].type == 1)
        {
            DrawText(
                TextFormat("Damage: %d",
                           spells[i].damage),
                680,
                y + 17,
                20,
                RED_COLOR);
        }
        else
        {
            DrawText(
                TextFormat("Heal: %d",
                           spells[i].heal),
                680,
                y + 17,
                20,
                GREEN_COLOR);
        }

        DrawText(
            player.spells[i] ? "OWNED" : "LOCKED",
            850,
            y + 17,
            18,
            player.spells[i] ? GREEN_COLOR : GRAY_COLOR);

        if (player.spells[i] &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(
                GetMousePosition(),
                r))
        {
            CastSpell(i);

            if (monster.hp > 0)
            {
                currentScreen = SCREEN_BATTLE;
            }
        }
    }

    DrawText(
        "Press ESC to return",
        430,
        620,
        20,
        GRAY_COLOR);

    if (IsKeyPressed(KEY_ESCAPE))
        currentScreen = SCREEN_BATTLE;

    for (int i = 0; i < SPELL_COUNT; i++)
    {
        if (player.spells[i] &&
            IsKeyPressed(KEY_ONE + i))
        {
            CastSpell(i);
            currentScreen = SCREEN_BATTLE;
        }
    }
}

/* =========================================================
   BACKPACK
   ========================================================= */

void DrawBackpack(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "BACKPACK",
        50,
        40,
        YELLOW_COLOR);

    DrawText(
        TextFormat("HP: %d/%d",
                   player.hp,
                   player.maxHp),
        100,
        120,
        25,
        GREEN_COLOR);

    DrawText(
        TextFormat("MP: %d/%d",
                   player.mp,
                   player.maxMp),
        100,
        155,
        25,
        BLUE_COLOR);

    for (int i = 0; i < POTION_COUNT; i++)
    {
        Rectangle r =
            {
                120,
                230 + i * 100,
                860,
                75};

        DrawButton(
            r,
            TextFormat(
                "%d. %s x%d",
                i + 1,
                potions[i].name,
                player.potions[i]),
            false);

        if (ButtonPressed(r))
        {
            UsePotion(i);

            currentScreen = SCREEN_BATTLE;
        }
    }

    DrawCenteredText(
        "ESC - Return",
        580,
        20,
        GRAY_COLOR);

    if (IsKeyPressed(KEY_ESCAPE))
        currentScreen = SCREEN_BATTLE;
}

/* =========================================================
   SHOP
   ========================================================= */

void DrawShop(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "SHOP",
        50,
        45,
        YELLOW_COLOR);

    DrawText(
        TextFormat("Gold: %d",
                   player.gold),
        70,
        120,
        25,
        YELLOW_COLOR);

    Rectangle weapon =
        {
            150, 210, 350, 70};

    Rectangle potion =
        {
            600, 210, 350, 70};

    Rectangle magic =
        {
            150, 320, 350, 70};

    Rectangle exit =
        {
            600, 320, 350, 70};

    DrawButton(
        weapon,
        "WEAPONS",
        false);

    DrawButton(
        potion,
        "POTIONS",
        false);

    DrawButton(
        magic,
        magicUnlocked ? "MAGIC" : "MAGIC [LOCKED]",
        false);

    DrawButton(
        exit,
        "CONTINUE",
        false);

    if (ButtonPressed(weapon))
        currentScreen = SCREEN_WEAPON_SHOP;

    if (ButtonPressed(potion))
        currentScreen = SCREEN_POTION_SHOP;

    if (ButtonPressed(magic) &&
        magicUnlocked)
        currentScreen = SCREEN_MAGIC_SHOP;

    if (ButtonPressed(exit))
    {
        if (dungeonWave <= 20)
            currentScreen = SCREEN_DUNGEON;
        else
            currentScreen = SCREEN_INFINITY;
    }
}

/* =========================================================
   WEAPON SHOP
   ========================================================= */

void BuyWeapon(int index)
{
    Weapon *w = &weapons[index];

    if (player.gold < w->price)
    {
        SetMessage("Not enough gold!");
        return;
    }

    player.gold -= w->price;

    player.atk += w->atkBonus;
    player.def += w->defBonus;

    player.weaponLevel++;

    SetMessage("Weapon purchased!");
}

void DrawWeaponShop(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "WEAPON SHOP",
        45,
        40,
        YELLOW_COLOR);

    DrawText(
        TextFormat("Gold: %d",
                   player.gold),
        70,
        100,
        24,
        YELLOW_COLOR);

    for (int i = 0; i < WEAPON_COUNT; i++)
    {
        int y = 160 + i * 120;

        Rectangle r =
            {
                100,
                y,
                900,
                95};

        DrawPanel(r);

        DrawText(
            TextFormat("%d. %s",
                       i + 1,
                       weapons[i].name),
            130,
            y + 15,
            24,
            WHITE_COLOR);

        DrawText(
            TextFormat(
                "Price: %d | ATK +%d | DEF +%d",
                weapons[i].price,
                weapons[i].atkBonus,
                weapons[i].defBonus),
            130,
            y + 55,
            19,
            GRAY_COLOR);

        if (ButtonPressed(
                (Rectangle){800, y + 20, 150, 55}))
        {
            BuyWeapon(i);
        }

        DrawButton(
            (Rectangle){800, y + 20, 150, 55},
            "BUY",
            false);
    }

    DrawText(
        "ESC - Back",
        500,
        620,
        20,
        GRAY_COLOR);

    if (IsKeyPressed(KEY_ESCAPE))
        currentScreen = SCREEN_SHOP;
}

/* =========================================================
   POTION SHOP
   ========================================================= */

void BuyPotion(int index)
{
    Potion *p = &potions[index];

    if (player.gold < p->price)
    {
        SetMessage("Not enough gold!");
        return;
    }

    player.gold -= p->price;

    player.potions[index]++;

    SetMessage("Potion purchased!");
}

void DrawPotionShop(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "POTION SHOP",
        45,
        40,
        GREEN_COLOR);

    DrawText(
        TextFormat("Gold: %d",
                   player.gold),
        70,
        100,
        24,
        YELLOW_COLOR);

    for (int i = 0; i < POTION_COUNT; i++)
    {
        int y = 190 + i * 130;

        Rectangle r =
            {
                150,
                y,
                800,
                90};

        DrawPanel(r);

        DrawText(
            potions[i].name,
            180,
            y + 15,
            25,
            WHITE_COLOR);

        DrawText(
            TextFormat(
                "Price: %d | Owned: %d",
                potions[i].price,
                player.potions[i]),
            180,
            y + 52,
            19,
            GRAY_COLOR);

        Rectangle buy =
            {
                790,
                y + 17,
                130,
                55};

        DrawButton(
            buy,
            "BUY",
            false);

        if (ButtonPressed(buy))
            BuyPotion(i);
    }

    if (IsKeyPressed(KEY_ESCAPE))
        currentScreen = SCREEN_SHOP;
}

/* =========================================================
   MAGIC SHOP
   ========================================================= */

void BuySpell(int index)
{
    Spell *spell = &spells[index];

    if (player.spells[index])
    {
        SetMessage("Already owned!");
        return;
    }

    if (player.gold < spell->price)
    {
        SetMessage("Not enough gold!");
        return;
    }

    player.gold -= spell->price;

    player.spells[index] = 1;

    SetMessage("Magic learned!");
}

void DrawMagicShop(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "MAGIC SHOP",
        40,
        40,
        PURPLE_COLOR);

    DrawText(
        TextFormat("Gold: %d",
                   player.gold),
        70,
        100,
        24,
        YELLOW_COLOR);

    for (int i = 0; i < SPELL_COUNT; i++)
    {
        int y = 145 + i * 105;

        Rectangle r =
            {
                80,
                y,
                940,
                85};

        DrawPanel(r);

        DrawText(
            TextFormat(
                "%d. %s",
                i + 1,
                spells[i].name),
            105,
            y + 12,
            23,
            WHITE_COLOR);

        DrawText(
            TextFormat(
                "Price: %d | MP: %d",
                spells[i].price,
                spells[i].mpCost),
            105,
            y + 48,
            18,
            GRAY_COLOR);

        if (spells[i].type == 1)
        {
            DrawText(
                TextFormat(
                    "Damage: %d",
                    spells[i].damage),
                400,
                y + 30,
                19,
                RED_COLOR);
        }
        else
        {
            DrawText(
                TextFormat(
                    "Heal: %d",
                    spells[i].heal),
                400,
                y + 30,
                19,
                GREEN_COLOR);
        }

        Rectangle buy =
            {
                820,
                y + 15,
                150,
                55};

        DrawButton(
            buy,
            player.spells[i] ? "OWNED" : "BUY",
            false);

        if (ButtonPressed(buy))
            BuySpell(i);
    }

    if (IsKeyPressed(KEY_ESCAPE))
        currentScreen = SCREEN_SHOP;
}

/* =========================================================
   SETTINGS
   ========================================================= */

int musicVolume = 100;
int fpsLimit = 60;

void DrawSettings(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "SETTINGS",
        60,
        45,
        YELLOW_COLOR);

    DrawText(
        TextFormat(
            "Music Volume: %d",
            musicVolume),
        250,
        190,
        25,
        WHITE_COLOR);

    DrawText(
        TextFormat(
            "FPS: %d",
            fpsLimit),
        250,
        300,
        25,
        WHITE_COLOR);

    Rectangle musicDown =
        {
            700, 180, 60, 50};

    Rectangle musicUp =
        {
            770, 180, 60, 50};

    Rectangle fpsDown =
        {
            700, 290, 60, 50};

    Rectangle fpsUp =
        {
            770, 290, 60, 50};

    DrawButton(
        musicDown,
        "-",
        false);

    DrawButton(
        musicUp,
        "+",
        false);

    DrawButton(
        fpsDown,
        "-",
        false);

    DrawButton(
        fpsUp,
        "+",
        false);

    DrawCenteredText(
        "Press ESC to return",
        550,
        22,
        GRAY_COLOR);

    if (ButtonPressed(musicDown))
    {
        musicVolume -= 10;

        if (musicVolume < 0)
            musicVolume = 0;
    }

    if (ButtonPressed(musicUp))
    {
        musicVolume += 10;

        if (musicVolume > 100)
            musicVolume = 100;
    }

    if (ButtonPressed(fpsDown))
    {
        fpsLimit -= 10;

        if (fpsLimit < 30)
            fpsLimit = 30;
    }

    if (ButtonPressed(fpsUp))
    {
        fpsLimit += 10;

        if (fpsLimit > 240)
            fpsLimit = 240;
    }

    if (IsKeyPressed(KEY_ESCAPE))
        currentScreen = SCREEN_MENU;
}

/* =========================================================
   DUNGEON
   ========================================================= */

void DrawDungeon(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "20 WAVE DUNGEON",
        60,
        45,
        YELLOW_COLOR);

    if (dungeonWave == 0)
        dungeonWave = 1;

    DrawCenteredText(
        TextFormat(
            "Next Wave: %d / 20",
            dungeonWave),
        160,
        30,
        WHITE_COLOR);

    DrawText(
        TextFormat(
            "HP: %d/%d",
            player.hp,
            player.maxHp),
        150,
        250,
        25,
        GREEN_COLOR);

    DrawText(
        TextFormat(
            "MP: %d/%d",
            player.mp,
            player.maxMp),
        150,
        290,
        25,
        BLUE_COLOR);

    DrawText(
        TextFormat(
            "Gold: %d",
            player.gold),
        150,
        330,
        25,
        YELLOW_COLOR);

    Rectangle battle =
        {
            350,
            430,
            400,
            70};

    Rectangle shop =
        {
            350,
            520,
            400,
            70};

    DrawButton(
        battle,
        TextFormat(
            "START WAVE %d",
            dungeonWave),
        false);

    DrawButton(
        shop,
        "SHOP",
        false);

    if (ButtonPressed(battle))
    {
        Monster m;

        CreateMonster(
            &m,
            dungeonWave);

        StartBattle(
            m,
            dungeonWave);
    }

    if (ButtonPressed(shop))
        currentScreen = SCREEN_SHOP;
}

/* =========================================================
   INFINITY DUNGEON
   ========================================================= */

void CreateInfinityMonster(Monster *m,
                           int wave)
{
    if (wave % 5 == 0)
    {
        strcpy(m->name,
               "Infinity Orc");

        m->maxHp = 200 * wave;
        m->hp = m->maxHp;

        m->atk = 20 * wave;
        m->def = wave / 2;

        m->isBoss = 1;
    }
    else
    {
        strcpy(m->name,
               "Infinity Goblin");

        m->maxHp = 100 * wave;
        m->hp = m->maxHp;

        m->atk = 10 * wave;
        m->def = wave / 2;

        m->isBoss = 0;
    }

    if (wave % 10 == 0)
    {
        m->maxHp *= 2;
        m->hp = m->maxHp;

        m->atk *= 2;
    }
}

void DrawInfinity(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "INFINITY DUNGEON",
        50,
        45,
        PURPLE_COLOR);

    DrawCenteredText(
        TextFormat(
            "Wave %d",
            infinityWave),
        140,
        35,
        YELLOW_COLOR);

    DrawText(
        "There is no end.",
        400,
        220,
        28,
        WHITE_COLOR);

    DrawText(
        "Every wave becomes stronger.",
        330,
        265,
        22,
        GRAY_COLOR);

    DrawText(
        TextFormat(
            "HP: %d/%d",
            player.hp,
            player.maxHp),
        150,
        350,
        25,
        GREEN_COLOR);

    DrawText(
        TextFormat(
            "Gold: %d",
            player.gold),
        150,
        390,
        25,
        YELLOW_COLOR);

    Rectangle battle =
        {
            300,
            470,
            500,
            75};

    Rectangle shop =
        {
            300,
            565,
            500,
            60};

    DrawButton(
        battle,
        TextFormat(
            "FIGHT WAVE %d",
            infinityWave),
        false);

    DrawButton(
        shop,
        "SHOP",
        false);

    if (ButtonPressed(battle))
    {
        Monster m;

        CreateInfinityMonster(
            &m,
            infinityWave);

        StartBattle(
            m,
            infinityWave);
    }

    if (ButtonPressed(shop))
        currentScreen = SCREEN_SHOP;
}

/* =========================================================
   VICTORY SCREEN
   ========================================================= */

void DrawVictory(void)
{
    ClearBackground(BG_COLOR);

    DrawCenteredText(
        "CONGRATULATIONS!",
        120,
        55,
        YELLOW_COLOR);

    DrawCenteredText(
        "YOU CLEARED 20 WAVES!",
        200,
        35,
        GREEN_COLOR);

    DrawCenteredText(
        "MAGIC SHOP UNLOCKED!",
        270,
        30,
        PURPLE_COLOR);

    DrawCenteredText(
        "Prepare yourself for the Infinity Dungeon.",
        340,
        22,
        WHITE_COLOR);

    Rectangle button =
        {
            350,
            470,
            400,
            70};

    DrawButton(
        button,
        "CONTINUE",
        false);

    if (ButtonPressed(button) ||
        IsKeyPressed(KEY_ENTER))
    {
        currentScreen = SCREEN_SHOP;
    }
}

/* =========================================================
   GAME OVER
   ========================================================= */

void DrawGameOver(void)
{
    ClearBackground((Color){35, 10, 15, 255});

    DrawCenteredText(
        "GAME OVER",
        180,
        70,
        RED_COLOR);

    DrawCenteredText(
        "Your adventure has ended.",
        290,
        25,
        WHITE_COLOR);

    Rectangle retry =
        {
            350,
            410,
            400,
            65};

    Rectangle menu =
        {
            350,
            500,
            400,
            65};

    DrawButton(
        retry,
        "RETRY",
        false);

    DrawButton(
        menu,
        "MAIN MENU",
        false);

    if (ButtonPressed(retry))
    {
        InitializePlayer();

        magicUnlocked = 0;

        dungeonWave = 0;

        infinityWave = 21;

        storyStep = 0;

        currentScreen = SCREEN_STORY;
    }

    if (ButtonPressed(menu))
    {
        InitializePlayer();

        currentScreen = SCREEN_MENU;
    }
}

/* =========================================================
   DRAW DISPATCH
   ========================================================= */

void DrawGame(void)
{
    BeginDrawing();

    switch (currentScreen)
    {
    case SCREEN_TITLE:
        DrawTitleScreen();
        break;

    case SCREEN_MENU:
        DrawMainMenu();
        break;

    case SCREEN_SETTINGS:
        DrawSettings();
        break;

    case SCREEN_STORY:
        DrawStory();
        break;

    case SCREEN_BATTLE:
        DrawBattle();
        break;

    case SCREEN_SHOP:
        DrawShop();
        break;

    case SCREEN_WEAPON_SHOP:
        DrawWeaponShop();
        break;

    case SCREEN_POTION_SHOP:
        DrawPotionShop();
        break;

    case SCREEN_MAGIC_SHOP:
        DrawMagicShop();
        break;

    case SCREEN_BACKPACK:
        DrawBackpack();
        break;

    case SCREEN_DUNGEON:
        DrawDungeon();
        break;

    case SCREEN_INFINITY:
        DrawInfinity();
        break;

    case SCREEN_VICTORY:
        DrawVictory();
        break;

    case SCREEN_GAMEOVER:
        DrawGameOver();
        break;
    }

    if (gameMessage[0] != '\0' &&
        messageTimer > 0 &&
        currentScreen != SCREEN_BATTLE)
    {
        DrawRectangle(
            250,
            630,
            600,
            45,
            (Color){10, 10, 15, 230});

        DrawCenteredText(
            gameMessage,
            640,
            20,
            YELLOW_COLOR);
    }

    EndDrawing();
}

/* =========================================================
   MAIN
   ========================================================= */

int main(void)
{
    srand((unsigned int)time(NULL));

    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Poop Adventure - Raylib");

    SetTargetFPS(60);

    InitializePlayer();

    /* =====================================================
       FIX: ใช้ gameRunning ควบคุมการออกจากเกม
       ===================================================== */

    gameRunning = true;

    while (!WindowShouldClose() && gameRunning)
    {
        UpdateMessage();

        DrawGame();
    }

    /* ปิด Window ที่นี่เพียงครั้งเดียว */
    CloseWindow();

    return 0;
}