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


// Funcao de combate
void combat(Player& player, Enemy& enemy) {
    system("cls");
    cout << "Combate iniciado contra " << (enemy.isBoss ? "Chefe" : "Inimigo") << " (Nivel " << enemy.level << ")!\n";
    while (player.health > 0 && enemy.health > 0) {
        enemy.health -= player.strength;
        if (enemy.health > 0) player.health -= enemy.strength;
        cout << "Sua vida: " << player.health << " | Vida do inimigo: " << enemy.health << "\n";
        Sleep(500);
    }
    if (player.health > 0) {
        cout << "Inimigo derrotado!\n";
    } else {
        cout << "Voce foi derrotado...\n";
    }
    Sleep(1000);
    system("cls");
}

// Funcao para mover o jogador
void movePlayer(Player& player, char direction, vector<vector<int>>& map, vector<Enemy>& enemies, vector<Item>& items) {
    int newX = player.x, newY = player.y;

    if (direction == 'w') newX--; /// Cima
    else if (direction == 's') newX++; ///Baixo
    else if (direction == 'a') newY--; ///Esquerda
    else if (direction == 'd') newY++; ///Direita

    if (newX >= 0 && newX < static_cast<int>(map.size()) && newY >= 0 && newY < static_cast<int>(map[0].size())) {
        if (map[newX][newY] == WALL) {
            cout << "Voce bateu em uma parede!\n";
            Sleep(200);
            return;
        }
        // Coleta itens
        for (auto it = items.begin(); it != items.end(); ) {
            if (newX == it->x && newY == it->y) {
                cout << "Item coletado: " << it->type << "\n";
                Sleep(700);
                system("cls");
                player.inventory.push_back(it->type);
                player.score += 5;
                it = items.erase(it);
            } else {
                ++it;
            }
        }
        // Combate com inimigos
        for (auto it = enemies.begin(); it != enemies.end(); ) {
            if (newX == it->x && newY == it->y) {
                combat(player, *it);
                if (it->health <= 0) {
                    player.exp += it->expReward;
                    player.score += it->level * 10;
                    it = enemies.erase(it);
                } else {
                    ++it;
                }
                return;
            } else {
                ++it;
            }
        }
        // Verifica armadilhas
        if (map[newX][newY] == TRAP) {
            player.health -= 10;
            cout << "Voce pisou em uma armadilha! Vida -10\n";
            Sleep(1000);
        }
        player.x = newX;
        player.y = newY;
    }
}

// Funcao para usar itens
void useItem(Player& player) {
    if (player.inventory.empty()) {
        system("cls");
        cout << "Inventario vazio!\n";
        cout << "Pressione Enter para continuar...\n";
        cin.ignore();
        cin.get();
        system("cls");
        return;
    }
    system("cls");
    cout << "Usar qual item? (Digite o numero)\n";
    for (size_t i = 0; i < player.inventory.size(); i++) {
        cout << i << ": " << player.inventory[i] << "\n";
    }
    int choice;
    cin >> choice;
    if (choice >= 0 && choice < static_cast<int>(player.inventory.size())) {
        string item = player.inventory[choice];
        if (item == "Pocao de Cura") {
            player.health += 15;
            cout << "Pocao de Cura usada! Vida +15\n";
        } else if (item == "Espada") {
            player.strength += 5;
            cout << "Espada equipada! Forca +5\n";
        } else if (item == "Totem") {
            player.score += 5;
            cout << "Totem usado! Pontuacao +5\n";
        }
        player.inventory.erase(player.inventory.begin() + choice);
        cout << "Pressione Enter para continuar...\n";
        cin.ignore();
        cin.get();
    } else {
        cout << "Escolha invalida!\n";
        cout << "Pressione Enter para continuar...\n";
        cin.ignore();
        cin.get();
    }
    system("cls");
}

// Funcao para mover inimigos
void moveEnemies(vector<Enemy>& enemies, const vector<vector<int>>& map) {
    for (auto& enemy : enemies) {
        int attempts = 0;
        while (attempts < 10) {
            int dir = rand() % 4;
            int newX = enemy.x;
            int newY = enemy.y;
            if (dir == 0) newX--; // cima
            else if (dir == 1) newX++; // baixo
            else if (dir == 2) newY--; // esquerda
            else if (dir == 3) newY++; // direita
            if (newX >= 0 && newX < static_cast<int>(map.size()) && newY >= 0 && newY < static_cast<int>(map[0].size()) && map[newX][newY] != WALL) {
                enemy.x = newX;
                enemy.y = newY;
                break;
            }
            attempts++;
        }
    }
}