#include <iostream>
#include <windows.h>
#include <conio.h>

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

    while(true){
        ///Posiciona a escrita no inicio do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);



        
        ///Imprime o jogo: mapa e personagem.
        for (size_t i = 0; i < currentMap->size(); i++) {
            for (size_t j = 0; j < (*currentMap)[i].size(); j++) {
                if (i == player.x && j == player.y) {
                    cout << char(player.character); // personagem
                } else {
                    switch ((*currentMap)[i][j]) {
                        case 0: cout << " "; break; // caminho
                        case 1: cout << char(219); break; // parede
                    }
                }
            }
            cout << "\n";
        } //fim for mapa

        ///executa os movimentos
        if ( _kbhit() ){
            tecla = getch();
            movePlayer(player, tecla, *currentMap);
        }

    } //fim do laco do jogo

    return 0;
} //fim main