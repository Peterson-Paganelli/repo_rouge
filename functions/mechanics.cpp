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
