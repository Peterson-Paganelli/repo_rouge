#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "../structs.cpp"

using namespace std;

void movePlayer(Player& player, char direction, vector<vector<int>>& map) {
    int newX = player.x, newY = player.y;

    switch (direction) {
        case 'w':
        case 72: // Up
            newX--;
            break;
        case 's':
        case 80: // Down
            newX++;
            break;
        case 'a':
        case 75: // Left
            newY--;
            break;
        case 'd':
        case 77: // Right
            newY++;
            break;
        default:
            break;
    }

    if(newX >= 0 && newX < static_cast<int>(map.size()) && newY >= 0 && newY < static_cast<int>(map[0].size())) {
        if(map[newX][newY] == WALL) {
            cout << "Voce Bateu em uma Parede\n";
            Sleep(200);
            return;
        }
    }

    // Update player position
    player.x = newX;
    player.y = newY;
}

void moveEnemies(vector<Enemy>& enemies, const vector<vector<int>>& map) {
    for (auto& enemy : enemies) {
        int newX = enemy.x, newY = enemy.y;

        // Generate random direction: 0 = up, 1 = down, 2 = left, 3 = right
        int direction = rand() % 4;
        switch (direction) {
            case 0: newX--; break; // Up
            case 1: newX++; break; // Down
            case 2: newY--; break; // Left
            case 3: newY++; break; // Right
        }

        // Check if the new position is within bounds and not a wall
        if (newX >= 0 && newX < static_cast<int>(map.size()) &&
            newY >= 0 && newY < static_cast<int>(map[0].size()) &&
            map[newX][newY] != WALL) {
            enemy.x = newX;
            enemy.y = newY;
        }
    }
}

Enemy createMonster(MonsterType type, int mapWidth, int mapHeight) {
    Enemy enemy;
    enemy.x = rand() % mapWidth;
    enemy.y = rand() % mapHeight;
    enemy.MonsterType = type;

    switch (type) {
        case GOBLIN:
            enemy.health = 10;
            enemy.strength = 3;
            enemy.level = 1;
            enemy.expReward = 5;
            enemy.displayChar = 'G'; // Goblin
            break;
        case ORC:
            enemy.health = 20;
            enemy.strength = 5;
            enemy.level = 2;
            enemy.expReward = 10;
            enemy.displayChar = 'O'; // Orc
            break;
        case TROLL:
            enemy.health = 30;
            enemy.strength = 7;
            enemy.level = 3;
            enemy.expReward = 15;
            enemy.displayChar = 'T'; // Troll
            break;
        case DRAGON:
            enemy.health = 50;
            enemy.strength = 10;
            enemy.level = 5;
            enemy.expReward = 50;
            enemy.displayChar = 'D'; // Dragon
            break;
    }

    return enemy;
}