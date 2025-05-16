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
                            cout << enemy.displayChar; // Display enemy's unique character
                            isEnemy = true;
                            break;
                        }
                    }
                    if (!isEnemy) {
                        switch ((*currentMap)[i][j]) {
                            case 0: cout << " "; break; // caminho
                            case 1: cout << char(219); break; // parede
                            case 3: cout << '^'; break; // trap icon
                            case 4: cout << '>'; break; // stairs
                            case 5: cout << '<'; break; // backward stairs
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

            // Trap logic: lose 10 health if on a trap
            if ((*currentMap)[player.x][player.y] == TRAP) {
                player.health -= 10;
                cout << "Voce caiu em uma armadilha! Vida -10\n";
                Sleep(1000);
                // Optional: remove the trap after triggering
                // (*currentMap)[player.x][player.y] = FLOOR;
            }
        }

        /// Check for player-enemy collision and initiate battle
        for (auto it = enemies.begin(); it != enemies.end(); ++it) {
            if (player.x == it->x && player.y == it->y) {
                battle(player, *it);
                // Check if this is the boss (map 3, DRAGON type, 'B' char, or by position)
                bool isBoss = (currentMap == &map3 && it->displayChar == 'B');
                enemies.erase(it); // Remove defeated enemy
                if (isBoss) {
                    system("cls");
                    cout << "Parabens! Voce derrotou o chefe final e venceu o jogo!\n";
                    Sleep(4000);
                    exit(0);
                }
                break;
            }
        }

        /// Check if player reached stairs to switch maps
        if ((*currentMap)[player.x][player.y] == STAIRS) {
            if (currentMap == &map1) {
                currentMap = &map2; // Switch to map2
                player.x = 1; // Reset player position
                player.y = 1;
                enemies.clear(); // Clear existing enemies

                // Initialize new enemies for map2
                for (int i = 0; i < 5; i++) {
                    MonsterType type = static_cast<MonsterType>(rand() % 4 + 1);
                    Enemy enemy = createMonster(type, currentMap->size(), (*currentMap)[0].size());
                    if ((*currentMap)[enemy.x][enemy.y] == FLOOR) {
                        enemies.push_back(enemy);
                    } else {
                        i--;
                    }
                }

                system("cls");
                cout << "Voce subiu as escadas para o proximo nivel!\n";
                Sleep(2000);
                system("cls");
            } else if (currentMap == &map2) {
                currentMap = &map3; // Switch to map3
                player.x = 1;
                player.y = 1;
                enemies.clear();

                // Initialize new enemies for map3
                for (int i = 0; i < 7; i++) {
                    MonsterType type = static_cast<MonsterType>(rand() % 4 + 1);
                    Enemy enemy = createMonster(type, currentMap->size(), (*currentMap)[0].size());
                    if ((*currentMap)[enemy.x][enemy.y] == FLOOR) {
                        enemies.push_back(enemy);
                    } else {
                        i--;
                    }
                }

                // Add final boss at a fixed position (e.g., [6][3])
                Enemy boss;
                boss.x = 6; // Changed from 8 to 6
                boss.y = 3; // Changed from 10 to 3
                boss.MonsterType = DRAGON;
                boss.health = 100;
                boss.strength = 20;
                boss.level = 10;
                boss.expReward = 100;
                boss.displayChar = 'B'; // 'B' for Boss
                enemies.push_back(boss);

                system("cls");
                cout << "Voce subiu as escadas para o proximo nivel!\n";
                Sleep(2000);
                system("cls");
            }
        } else if ((*currentMap)[player.x][player.y] == STAIRS_BACK) {
            if (currentMap == &map3) {
                currentMap = &map2; // Go back to map2
                player.x = 9; // Reset player position
                player.y = 10;
                enemies.clear();

                // Reinitialize enemies for map2
                for (int i = 0; i < 5; i++) {
                    MonsterType type = static_cast<MonsterType>(rand() % 4 + 1);
                    Enemy enemy = createMonster(type, currentMap->size(), (*currentMap)[0].size());
                    if ((*currentMap)[enemy.x][enemy.y] == FLOOR) {
                        enemies.push_back(enemy);
                    } else {
                        i--;
                    }
                }

                system("cls");
                cout << "Voce desceu as escadas para o nivel anterior!\n";
                Sleep(2000);
                system("cls");
            } else if (currentMap == &map2) {
                currentMap = &map1; // Go back to map1
                player.x = 7; // Reset player position
                player.y = 15;
                enemies.clear();

                // Reinitialize enemies for map1
                for (int i = 0; i < 5; i++) {
                    MonsterType type = static_cast<MonsterType>(rand() % 4 + 1);
                    Enemy enemy = createMonster(type, currentMap->size(), (*currentMap)[0].size());
                    if ((*currentMap)[enemy.x][enemy.y] == FLOOR) {
                        enemies.push_back(enemy);
                    } else {
                        i--;
                    }
                }

                system("cls");
                cout << "Voce desceu as escadas para o nivel anterior!\n";
                Sleep(2000);
                system("cls");
            }
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