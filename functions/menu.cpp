#include <iostream>
#include <windows.h>

using namespace std;

int menu() {
    int op = 0;
    system("cls");
    cout << "--------------------------------\n";
    cout << "1 - Iniciar\n2 - Ajuda\n3 - Creditos\n";
    cout << "--------------------------------\n";
    cin >> op;
    switch (op) {
        case 1:
            cout << "Jogo iniciado\n";
            Sleep(1000);
            system("cls");
            return op;
        case 2: {
            int auxMenu = 0;
            do {
                system("cls");
                cout << "Ajuda\n";
                cout << "1 - Funcionamento\n2 - Itens\n3 - Movimentacao\n4 - Voltar\n";
                cout << "Escolha uma opcao: ";
                cin >> auxMenu;
                switch (auxMenu) {
                    case 1:
                        system("cls");
                        cout << "Funcionamento\n";
                        cout << "Explore as masmorras, colete itens, lute contra inimigos e avance de nivel utilizando as escadas.\n";
                        cout << "Cuidado com armadilhas que reduzem sua vida.\n";
                        cout << "Derrote todos os inimigos para avancar de nivel.\n";
                        cout << "\nPressione Enter para continuar...\n";
                        cin.ignore();
                        cin.get();
                        break;
                    case 2:
                        system("cls");
                        cout << "Itens\n";
                        cout << "Espada: Aumenta a forca em 5 pontos\n";
                        cout << "Pocao de Cura: Recupera 15 de vida\n";
                        cout << "Totem: Aumenta a pontuacao em 5 pontos\n";
                        cout << "Use itens pressionando 'u' durante o jogo.\n";
                        cout << "\nPressione Enter para continuar...\n";
                        cin.ignore();
                        cin.get();
                        break;
                    case 3:
                        system("cls");
                        cout << "Movimentacao\n";
                        cout << "Use as teclas:\n";
                        cout << "'w' - Mover para cima\n";
                        cout << "'s' - Mover para baixo\n";
                        cout << "'a' - Mover para esquerda\n";
                        cout << "'d' - Mover para direita\n";
                        cout << "'u' - Usar um item\n";
                        cout << "'q' - Sair do jogo\n";
                        cout << "\nPressione Enter para continuar...\n";
                        cin.ignore();
                        cin.get();
                        break;
                }
            } while (auxMenu != 4);
            break;
        }
        case 3:
            system("cls");
            cout << "Creditos\n";
            cout << "Um jogo criado por: Davi, Pedro, Peterson\n";
            cout << "Programacao: Davi, Pedro, Peterson\n";
            cout <<"Ambientação: Davi, Pedro, Peterson\n";
            cout << "Agradecimentos: Prof. Alex Luciano Roesler Rese\n";
            cout << "\nPressione Enter para continuar...\n";
            cin.ignore();
            cin.get();
            break;
    }
    return 0;
}