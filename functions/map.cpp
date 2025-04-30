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

void updateDiscoveredMap(vector<vector<int>>& discoveredMap, const vector<vector<int>>& map, int playerX, int playerY, int radius) {
    int rows = map.size();
    int cols = map[0].size();
    for (int i = max(0, playerX - radius); i <= min(rows - 1, playerX + radius); i++) {
        for (int j = max(0, playerY - radius); j <= min(cols - 1, playerY + radius); j++) {
            double distancia = sqrt(pow(i - playerX, 2) + pow(j - playerY, 2));
            if (distancia <= radius) {
                discoveredMap[i][j] = map[i][j];
            }
        }
    }
}

// Funcao para exibir o mapa com fog-of-war
void displayMap(const vector<vector<int>>& map, const vector<vector<int>>& discoveredMap, const Player& player, const vector<Enemy>& enemies, const vector<Item>& items, HANDLE out, int visibleRadius) {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(out, coord);

    int rows = map.size();
    int cols = map[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == player.x && j == player.y) {
                cout << char(player.character);
            } else {
                bool printed = false;
                double distancia = sqrt(pow(i - player.x, 2) + pow(j - player.y, 2));
                if (distancia <= visibleRadius) {
                    for (const auto& enemy : enemies) {
                        if (i == enemy.x && j == enemy.y) {
                            cout << 'E';
                            printed = true;
                            break;
                        }
                    }
                    if (!printed) {
                        for (const auto& item : items) {
                            if (i == item.x && j == item.y) {
                                cout << 'I';
                                printed = true;
                                break;
                            }
                        }
                    }
                }
                if (!printed) {
                    if (discoveredMap[i][j] != -1) {
                        switch (discoveredMap[i][j]) {
                            case WALL: cout << char(219); break;
                            case FLOOR: cout << ' '; break;
                            case TRAP: cout << '^'; break;
                            case STAIRS: cout << '>'; break;
                            default: cout << ' ';
                        }
                    } else {
                        cout << ' ';
                    }
                }
            }
        }
        cout << "\n";
    }
    cout << "Vida: " << player.health << " | Forca: " << player.strength << " | Nivel: " << player.level
         << " | Exp: " << player.exp << " | Pontuacao: " << player.score << "\n";
    cout << "Inventario: ";
    for (const auto& item : player.inventory) cout << item << " ";
    cout << "\n";
}

// Funcao para inicializar o nivel
void initializeLevel(vector<vector<int>>& map, Player& player, vector<Enemy>& enemies, vector<Item>& items, int levelNum) {
    map = {
        {1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,1,0,0,0,1},
        {1,1,1,0,1,0,1,1,0,1,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,0,1},
        {1,0,0,0,0,1,0,0,0,0,1},
        {1,0,1,0,1,0,0,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,4,1}, // Escadas em [9][9]
        {1,1,1,1,1,1,1,1,1,1,1}
    };
    player.x = 1; player.y = 1;
    enemies.clear();
    items.clear();
    srand(time(0));
    for (int i = 0; i < levelNum + 1; i++) {
        Enemy enemy = {rand() % 9 + 1, rand() % 9 + 1, 20 + levelNum * 5, 5 + levelNum * 2, levelNum, 10 + levelNum * 5, false};
        if (map[enemy.x][enemy.y] == FLOOR) enemies.push_back(enemy);
    }
    if (levelNum == 3) {
        Enemy boss = {8, 8, 50, 15, 3, 50, true};
        enemies.push_back(boss);
    }
    items.push_back({3, 3, "Pocao de Cura"});
    items.push_back({5, 5, "Espada"});
    items.push_back({7, 7, "Totem"});
}