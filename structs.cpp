#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

enum CellType {
    WALL = 1,
    FLOOR = 0,
    TRAP = 3,
    STAIRS = 4
};

struct Player {
    int x, y;         // Posicao
    int character;    // Skin (ASCII)
    int health;       // Vida
    int strength;     // Forca
    int level;        // Nivel
    int exp;          // Experiencia
    vector<string> inventory; // Inventario
    int score;        // Pontuacao
};

struct Enemy {
    int x, y;         // Posicao
    int health;       // Vida
    int strength;     // Forca
    int level;        // Nivel
    int expReward;    // Experiencia dada ao jogador
    bool isBoss;      // Indica se e o chefe final
};

struct Item {
    int x, y;
    string type;
};