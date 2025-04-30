#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "./functions/menu.cpp"
#include "./functions/map.cpp"
#include "./functions/mechanics.cpp"

using namespace std;

int main() {
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
        //INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.
    // Menu inicial
    while (menu() != 1);

    // Inicializacao do jogador
    Player player = {1, 1, 36, 100, 10, 1, 0, {}, 0};
    vector<Enemy> enemies;
    vector<Item> items;
    vector<vector<int>> map;
    vector<vector<int>> discoveredMap;
    int currentLevel = 1;
    int visibleRadius = 3;

    initializeLevel(map, player, enemies, items, currentLevel);
    discoveredMap = vector<vector<int>>(map.size(), vector<int>(map[0].size(), -1));

    bool gameRunning = true;
    bool needsRedraw = true;
    while (gameRunning) {
        if (_kbhit()) {
            char tecla = _getch();
            if (tecla == 'q') gameRunning = false;
            else if (tecla == 'u') {
                useItem(player);
                needsRedraw = true;
            } else {
                movePlayer(player, tecla, map, enemies, items);
                updateDiscoveredMap(discoveredMap, map, player.x, player.y, visibleRadius);
                moveEnemies(enemies, map);
                needsRedraw = true;
            }
        }

        // Verifica condicoes de vitoria/derrota
        if (player.health <= 0) {
            system("cls");
            cout << "GAME OVER\nPontuacao Final: " << player.score << "\n";
            gameRunning = false;
        } else if (map[player.x][player.y] == STAIRS && currentLevel < 3) {
            if (enemies.empty()) {
                currentLevel++;
                initializeLevel(map, player, enemies, items, currentLevel);
                discoveredMap = vector<vector<int>>(map.size(), vector<int>(map[0].size(), -1));
                cout << "Subindo para o nivel " << currentLevel << "...\n";
                //Sleep(1000);
                needsRedraw = true;
            } else {
                cout << "Voce deve derrotar todos os inimigos para prosseguir.\n";
                player.x--;
                Sleep(800);
                system("cls");
            }
        } else if (currentLevel == 3 && enemies.empty()) {
            system("cls");
            cout << "VOCE VENCEU!\nPontuacao Final: " << player.score << "\n";
            gameRunning = false;
        }

        if (needsRedraw) {
            displayMap(map, discoveredMap, player, enemies, items, out, visibleRadius);
            needsRedraw = false;
        }
    }

    cout << "Pressione Enter para sair...\n";
    cin.ignore();
    cin.get();
    return 0;
}