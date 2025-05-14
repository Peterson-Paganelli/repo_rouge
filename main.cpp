#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "structs.cpp"
#include "./functions/menu.cpp"
#include "./functions/mechanics.cpp"
#include "./maps/maps.cpp"

using namespace std;

int main()
{
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
    
    //Nome do personagem
    char charName;
    //Variavel para tecla precionada
    char tecla;

    // Escolha do mapa
    vector<vector<int>>* currentMap = &map1; // Inicialmente usa o map1

    while(menu() != 1);
    
    cout << "Nome do jogador: ";
    cin >> charName;

    system("cls");
    cout << "Jogo iniciado\n";
    Sleep(1000);
    system("cls");

    //INICIO: Inicialização do jogador
    Player player = {
        charName, //Nome do Jogador
        1, //Classe
        1, 1, //Posicionamento
        36, //Simbolo do personagem
        100, //Vida Máxima
        10, //Força
        1, //nível do personagem
        0, //Experiência
        0, //pontuação
        {} //Inventário
    };
    //FIM: Inicialização do jogador

    // Initialize enemies
    vector<Enemy> enemies;
    srand(time(0)); // Seed for random number generation
    for (int i = 0; i < 5; i++) { // Create 5 enemies
        MonsterType type = static_cast<MonsterType>(rand() % 4 + 1); // Random monster type
        Enemy enemy = createMonster(type, currentMap->size(), (*currentMap)[0].size());

        // Ensure enemy is placed on a FLOOR cell
        if ((*currentMap)[enemy.x][enemy.y] == FLOOR) {
            enemies.push_back(enemy);
        } else {
            i--; // Retry if position is invalid
        }
    }

    int enemyMoveCounter = 0; // Counter to control enemy movement

    while (true) {
        ///Posiciona a escrita no inicio do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for (size_t i = 0; i < currentMap->size(); i++) {
            for (size_t j = 0; j < (*currentMap)[i].size(); j++) {
                if (i == player.x && j == player.y) {
                    cout << char(player.character); // personagem
                } else {
                    bool isEnemy = false;
                    for (const auto& enemy : enemies) {
                        if (i == enemy.x && j == enemy.y) {
                            cout << 'E'; // Display enemy
                            isEnemy = true;
                            break;
                        }
                    }
                    if (!isEnemy) {
                        switch ((*currentMap)[i][j]) {
                            case 0: cout << " "; break; // caminho
                            case 1: cout << char(219); break; // parede
                        }
                    }
                }
            }
            cout << "\n";
        } //fim for mapa

        /// Check for player input
        if (_kbhit()) {
            tecla = getch();
            movePlayer(player, tecla, *currentMap);
        }

        /// Control enemy movement with a counter
        if (enemyMoveCounter >= 10) { // Adjust the value to control enemy speed
            moveEnemies(enemies, *currentMap);
            enemyMoveCounter = 0; // Reset the counter
        }

        /// Increment the counter
        enemyMoveCounter++;

        /// Add a small delay to control the game loop speed
        Sleep(50); // Adjust as needed
    } //fim do laco do jogo

    return 0;
} //fim main