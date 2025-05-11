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

#endif // STRUCTS_H