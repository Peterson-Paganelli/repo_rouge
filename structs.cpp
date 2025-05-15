#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>

enum CellType {
    WALL = 1,
    FLOOR = 0,
    TRAP = 3,
    STAIRS = 4
};
enum MonsterType {
    GOBLIN = 1,
    ORC,
    TROLL,
    DRAGON
};

struct Player {
    char name;
    int classType;
    int x, y;
    int character;
    int maxHealth;
    int strength;
    int level;
    int exp;
    int score;
    std::vector<std::string> inventory;
};

struct Enemy {
    int x, y;
    int MonsterType; // Type of monster
    int health;
    int strength;
    int level;
    int expReward;
    char displayChar; // Character to represent the enemy
};

struct Boss {
    int typeMonster; //Skin (ASCII)
    int health;
    int strength;
    int level;
    int expReward;
};

#endif // STRUCTS_H