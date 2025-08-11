#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Função para exibir o estado atual das poltronas
void exibirPoltronas(const char reserva[10][6]) {
    // Formatação para exibir de maneira mais intuitiva
    printf("\n\t[A] [B] [C]\t[D] [E] [F]\n");
    for (int x = 0; x < 10; x++) {
        if (x < 9) printf("\n0%d\t", x + 1); // Formatação para exibir fileira 01 a 09
        else printf("\n%d\t", x + 1); // Exibir fileira 10

        for (int y = 0; y < 6; y++) {
            printf("[%c] ", reserva[x][y]); // Exibir o estado da poltrona (vazia ou reservada)
            if (y == 2) {
                printf("\t"); // Espaço para indicar o corredor
            }
        }
    }
    printf("\n");
}
// Verifica se a poltrona é válida para a classe
bool poltronaValida(char poltrona, int classe) {
    // Classe econômica não pode usar A e F
    if (classe == 1) {
        return poltrona >= 'B' && poltrona <= 'E'; // B, C, D, E
    }
    return poltrona >= 'A' && poltrona <= 'F'; // Classe Executiva
}

// Função para reservar uma poltrona
bool reservarPoltrona(char reserva[10][6], int classe) {
    int fileira;
    char poltrona;
    int recomendacao;

   // Escolha da classe
    while (true) {
        cout << "\nEscolha a classe\n1 - classe Economica (plano basico - sem direito a poltronas proximas a janela)\n2 - classe Executiva (plano avancado - prioridade para poltronas proximas a janela)\n3 - voltar para o menu principal\n";
        cout << "\nEscolha uma opcao: ";
        if (!(cin >> classe) || (classe < 1 || classe > 3)) {
            cout << "\nEntrada invalida. Escolha um numero entre 1 e 3.\n";
            cin.clear(); // Limpa o estado de erro do cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora o restante da entrada inválida
            continue;
        }
        if (classe == 3) {
            cout << "\nVoltando ao menu principal.\n";
            return false;
        }
        break;
    }

    exibirPoltronas(reserva);
    cout << "\nDeseja uma recomendacao de poltrona? (1 - Sim, 2 - Nao):\n ";
    cout << "\nEscolha uma opcao: ";
    if (!(cin >> recomendacao) || (recomendacao != 1 && recomendacao != 2)) {
        cout << "\nEntrada invalida. Escolha 1 ou 2.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    if (recomendacao == 1) {
        if (classe == 2) {
            cout << "\nDeseja que o assento fique proximo a janela? (1 - Sim, 2 - Nao):\n ";
            cout << "\nEscolha uma opcao: ";
            int resposta;
            if (!(cin >> resposta) || (resposta != 1 && resposta != 2)) {
                cout << "\nEntrada invalida. Escolha 1 ou 2.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return false;
            }
            bool pertoJanela = (resposta == 1);

            // Proximidade para classe executiva
            for (int fileira = 0; fileira < 10; fileira++) {
                for (int col = 0; col < 6; col++) {
                    if (reserva[fileira][col] == 'O') {
                        if ((pertoJanela && (col == 0 || col == 5)) || (!pertoJanela && (col >= 1 && col <= 4))) {
                            poltrona = 'A' + col;
                            exibirPoltronas(reserva);
                            cout << "\nRecomendacao: Fileira " << fileira + 1 << ", Poltrona " << poltrona << ".\n";
                            cout << "\nDeseja reservar essa poltrona? (1 - Sim, 2 - Nao):\n ";
                            cout << "\nEscolha uma opcao: ";
                            int aceitar;
                            if (!(cin >> aceitar) || (aceitar != 1 && aceitar != 2)) {
                                cout << "\nEntrada invalida. Escolha 1 ou 2.\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                return false;
                            }
                            if (aceitar == 1) {
                                reserva[fileira][col] = 'X'; // Marca a poltrona como reservada
                                cout << "\nPoltrona " << poltrona << " na fileira " << fileira + 1 << " reservada com sucesso!\n";
                                exibirPoltronas(reserva);
                                return true;
                            }
                        }
                    }
                }
            }
        } else {
            // Proximidade para classe econômica (não permite A e F)
            for (int fileira = 0; fileira < 10; fileira++) {
                for (int col = 1; col < 5; col++) { // B, C, D, E
                    if (reserva[fileira][col] == 'O') {
                        poltrona = 'A' + col;
                        exibirPoltronas(reserva);
                        cout << "\nRecomendacao: Fileira " << fileira + 1 << ", Poltrona " << poltrona << ".\n";
                        cout << "\nDeseja reservar essa poltrona? (1 - Sim, 2 - Nao):\n ";
                        cout << "\nEscolha uma opcao: ";
                        int aceitar;
                        if (!(cin >> aceitar) || (aceitar != 1 && aceitar != 2)) {
                            cout << "\nEntrada invalida. Escolha 1 ou 2.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            return false;
                        }
                        if (aceitar == 1) {
                            reserva[fileira][col] = 'X'; // Marca a poltrona como reservada
                            cout << "\nPoltrona " << poltrona << " na fileira " << fileira + 1 << " reservada com sucesso!\n";
                            exibirPoltronas(reserva);
                            return true;
                        }
                    }
                }
            }
        }
    }

    // Caso o usuário não queira recomendação
    while (true) {
        cout << "\nEscolha a coluna (A, B, C, D, E ou F) ou 0 para cancelar e voltar:\n ";
        cout << "\nEscolha a coluna: ";
        cin >> poltrona;

        if (poltrona == '0') {
            cout << "Reserva cancelada. Retornando ao menu principal...\n";
            return false; // Retorna ao menu principal
        }

        cout << "\nDigite a fileira (1-10) ou 0 para cancelar e voltar:\n ";
        cout << "\nEscolha a fileira: ";
        if (!(cin >> fileira) || (fileira < 0 || fileira > 10)) {
            cout << "\nEntrada invalida. Digite um numero entre 0 e 10.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (fileira == 0) {
            cout << "Reserva cancelada. Retornando ao menu principal...\n";
            return false; // Retorna ao menu principal
        }

        // Normalizando a entrada para letras maiúsculas
        poltrona = toupper(poltrona);

        // Verificar se a poltrona é válida para a classe escolhida
        if (!poltronaValida(poltrona, classe)) {
            cout << "\nPoltrona invalida para a classe economica. Escolha apenas entre B, C, D, E.\n";
            continue;
        }

        if (poltrona < 'A' || poltrona > 'F') {
            cout << "\nPoltrona invalida. Tente novamente.\n";
            continue;
        }

        int acento = poltrona - 'A'; // Calcula o índice da poltrona a partir do caractere

        if (reserva[fileira - 1][acento] == 'X') {
            cout << "\nPoltrona ja reservada. Escolha outra.\n";
            cout << "\nEscolha uma opcao valida: ";
        } else {
            reserva[fileira - 1][acento] = 'X'; // Marca a poltrona como reservada
            cout << "\nPoltrona " << poltrona << " na fileira " << fileira << " reservada com sucesso!\n";
            break;
        }
    }

    exibirPoltronas(reserva);
    return true;
}
// Verifica se a linha tem assentos disponíveis suficientes
bool verificarAssentosDisponiveis(char reserva[10][6], int linha, const int cols[], int numPessoas) {
    int contador = 0;
    for (int i = 0; cols[i] != -1; i++) {
        if (reserva[linha][cols[i]] == 'O') {
            contador++;
        }
    }
    return contador >= numPessoas; // Retorna true se houver assentos disponíveis
}

// Aloca os assentos na linha correta
void alocarAssentos(char reserva[10][6], int linha, const int cols[], int numPessoas, char membros[][20]) {
    for (int i = 0, j = 0; cols[i] != -1 && j < numPessoas; i++) {
        if (reserva[linha][cols[i]] == 'O') {
            reserva[linha][cols[i]] = 'X'; // Marca como reservada
            cout << "Assento " << char('A' + cols[i]) << (linha + 1) << " reservado para " << membros[j] << endl;
            j++;
        }
    }
}

// Função para o plano familiar
bool planoFamiliar(char reserva[10][6]) {
    int numPessoas, classe;
    char familia[20];
    char membros[5][20];

    // Escolha da classe
    while (true) {
        cout << "\nEscolha a classe:\n1 - Classe Economica (plano basico - sem direito a poltronas proximas a janela)\n2 - Classe Executiva (plano avancado - prioridade para poltronas proximas a janela)\n3 - Voltar para o menu principal\n";
        cout << "\nEscolha uma opcao: ";
        cin >> classe;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEntrada invalida. Por favor, insira um numero valido.\n";
        } else if (classe == 3) {
            cout << "Voltando ao menu principal.\n";
            return false;
        } else if (classe != 1 && classe != 2) {
            cout << "\nClasse invalida. Escolha 1, 2 ou 3 para sair.\n";
        } else {
            break;
        }
    }

    cout << "Digite o nome da familia: ";
    cin >> familia;

    while (true) {
        cout << "\nDigite o numero de pessoas (3, 4 ou 5) ou digite 0 para cancelar: ";
        cin >> numPessoas;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEntrada invalida. Por favor, insira um numero valido.\n";
        } else if (numPessoas == 0) {
            cout << "Reserva cancelada.\n";
            return false;
        } else if (numPessoas < 3 || numPessoas > 5) {
            cout << "\nNumero de pessoas invalido. Escolha entre 3, 4 ou 5 ou digite 0 para cancelar.\n";
        } else {
            break;
        }
    }

    for (int i = 0; i < numPessoas; i++) {
        cout << "Digite o nome do membro " << (i + 1) << ": ";
        cin >> membros[i];
    }

    cout << "\nVoce escolheu " << numPessoas << " pessoas na classe " << (classe == 1 ? "Economica" : "Executiva") << " para a familia " << familia << ".\n";

    // Classe Econômica
    if (classe == 1) {
        exibirPoltronas(reserva);
        cout << "\nPreferem:\n"
             << "1 - Deixar o sistema decidir as poltronas (sem proximidade a janela)\n"
             << "2 - Escolher manualmente as poltronas:\n"
             << "3 - Cancelar a reserva\n"
             << "\nEscolha uma opcao: ";
        
        int opcaoEscolha;
        cin >> opcaoEscolha;

        if (opcaoEscolha == 1) {
            // Deixar o sistema decidir
            bool reservado = false;

            for (int linha = 0; linha < 10 && !reservado; linha++) {
                if (numPessoas == 3 && reserva[linha][1] == 'O' && reserva[linha][2] == 'O' && reserva[linha][3] == 'O') {
                    reserva[linha][1] = 'X'; // B
                    reserva[linha][2] = 'X'; // C
                    reserva[linha][3] = 'X'; // D
                    reservado = true;

                    exibirPoltronas(reserva);
                    cout << "\nReservada para 3 pessoas as seguintes Poltronas:\n";
                    cout << "\nPoltrona B" << (linha + 1) << " reservada";
                    cout << "\nPoltrona C" << (linha + 1) << " reservada";
                    cout << "\nPoltrona D" << (linha + 1) << " reservada\n";

                } else if (numPessoas == 4 && reserva[linha][1] == 'O' && reserva[linha][2] == 'O' && 
                           reserva[linha][3] == 'O' && reserva[linha][4] == 'O') {
                    reserva[linha][1] = 'X';
                    reserva[linha][2] = 'X';
                    reserva[linha][3] = 'X';
                    reserva[linha][4] = 'X';
                    reservado = true;

                    exibirPoltronas(reserva);
                    cout << "\nReservada para 4 pessoas as seguintes Poltronas:\n";
                    cout << "\nPoltrona B" << (linha + 1) << " reservada";
                    cout << "\nPoltrona C" << (linha + 1) << " reservada";
                    cout << "\nPoltrona D" << (linha + 1) << " reservada";
                    cout << "\nPoltrona E" << (linha + 1) << " reservada\n";

                } else if (numPessoas == 5 && reserva[linha][1] == 'O' && reserva[linha][2] == 'O' && 
                           reserva[linha][3] == 'O' && reserva[linha][4] == 'O') {
                    reserva[linha][1] = 'X';
                    reserva[linha][2] = 'X';
                    reserva[linha][3] = 'X';
                    reserva[linha][4] = 'X';

                    if (linha + 1 < 10 && reserva[linha + 1][2] == 'O') {
                        reserva[linha + 1][2] = 'X'; // Reserva um assento na linha de trás
                    }
                    reservado = true;

                    exibirPoltronas(reserva);
                    cout << "\nReservada para 5 pessoas as seguintes Poltronas:\n";
                    cout << "\nPoltrona B" << (linha + 1) << " reservada";
                    cout << "\nPoltrona C" << (linha + 1) << " reservada";
                    cout << "\nPoltrona D" << (linha + 1) << " reservada";
                    cout << "\nPoltrona E" << (linha + 1) << " reservada";
                    cout << "\nPoltrona C" << (linha + 2) << " reservada\n";
                }
            }
            
            if (!reservado) {
                cout << "Nao foi possivel encontrar assentos suficientes na classe economica.\n";
            }
        } else if (opcaoEscolha == 2) {
            // Escolher manualmente as poltronas
            for (int i = 0; i < numPessoas; i++) {
                char coluna;
                int linha;

                cout << "Escolha a coluna (B, C, D ou E) para " << membros[i] << ": ";
                cin >> coluna;

                int colunaIndex = 0;
                if (coluna == 'B' || coluna == 'b') {
                    colunaIndex = 1;
                } else if (coluna == 'C' || coluna == 'c') {
                    colunaIndex = 2;
                } else if (coluna == 'D' || coluna == 'd') {
                    colunaIndex = 3;
                } else if (coluna == 'E' || coluna == 'e') {
                    colunaIndex = 4;
                } else {
                    cout << "Coluna inválida. Tente novamente.\n";
                    i--;
                    continue;
                }

                cout << "Digite a linha (1-10) para " << membros[i] << ": ";
                cin >> linha;

                linha -= 1;

                if (linha < 0 || linha >= 10 || colunaIndex < 1 || colunaIndex > 4 || reserva[linha][colunaIndex] != 'O') {
                    cout << "Poltrona inválida. Tente novamente.\n";
                    i--;
                } else {
                    reserva[linha][colunaIndex] = 'X'; // Marca a poltrona como reservada
                }
            }
            cout << "Reservada as seguintes poltronas escolhidas manualmente.\n";
            exibirPoltronas(reserva);
        }
    } else if (classe == 2) {
        // Classe Executiva
    exibirPoltronas(reserva);
        cout << "\nPreferem:\n1 - Ficar separados, ambos proximos a janela\n2 - Ficar proximos um do outro, proximo a janela\n3 - Ficar proximos um ao outro, longe da janela\n4 - Escolher manualmente as poltronas\n\nEscolha uma opcao: ";
int escolhaProximidade;
if (!(cin >> escolhaProximidade) || (escolhaProximidade < 1 || escolhaProximidade > 4)) {
    cout << "\nEntrada inválida. Escolha um número entre 1 e 4.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

bool reservado = false;  // Variável para controlar se a reserva foi feita

if (escolhaProximidade == 1) {
    // Separados, todos próximos à janela
    for (int i = 0; i < numPessoas; i++) {
        char fileira = (i % 2 == 0) ? 'A' : 'F'; // Alterna entre A e F
        for (int linha = 0; linha < 10; linha++) {
            if (reserva[linha][fileira - 'A'] == 'O') {
                reserva[linha][fileira - 'A'] = 'X';
                cout << "\nPoltrona " << fileira << (linha + 1) << " reservada para o usuario " << (i + 1) << ".\n";
                reservado = true;
                break;
            }
        }
    }
} else if (escolhaProximidade == 2) {
    // Próximos um do outro, um próximo à janela
    for (int linha = 0; linha < 10 && !reservado; linha++) {
        if (reserva[linha][0] == 'O' && reserva[linha][1] == 'O' && reserva[linha][2] == 'O') {
            for (int i = 0; i < numPessoas && i < 3; i++) {
                reserva[linha][i] = 'X';
                cout << "\nPoltrona " << (char)('A' + i) << (linha + 1) << " reservada para o usuario " << (i + 1) << ".\n";
            }
            if (numPessoas > 3) {
                reserva[linha + 1][0] = 'X';  // Reservar a próxima linha para os outros
                cout << "\nPoltrona A" << (linha + 2) << " reservada para o usuario 4.\n";
            }
            if (numPessoas == 5) {
                reserva[linha + 1][1] = 'X';
                cout << "\nPoltrona B" << (linha + 2) << " reservada para o usuario 5.\n";
            }
            reservado = true;
        }
    }

} else if (escolhaProximidade == 3) {
    // Próximos um ao outro, longe da janela
    for (int linha = 0; linha < 10 && !reservado; linha++) {
        for (int col = 1; col < 4; col++) {
            // Verificar se há espaço para todas as pessoas na mesma fileira
            bool espacoSuficiente = true;
            for (int i = 0; i < numPessoas; i++) {
                if (col + i >= 6 || reserva[linha][col + i] != 'O') {  // Garantir que não ultrapassa a fileira F
                    espacoSuficiente = false;
                    break;
                }
            }

            // Se houver espaço suficiente, reservar as poltronas na mesma fileira
            if (espacoSuficiente) {
                for (int i = 0; i < numPessoas; i++) {
                    reserva[linha][col + i] = 'X';
                    cout << "\nPoltrona " << (char)('A' + col + i) << (linha + 1) << " reservada para o usuario " << (i + 1) << ".\n";
                }
                reservado = true;
                break;
            }
        }
    }

} else if (escolhaProximidade == 4) {
    // Escolher manualmente as poltronas
    for (int i = 0; i < numPessoas; i++) {
        char fileira;
        int coluna;
        while (true) {
            exibirPoltronas(reserva);
            cout << "\nEscolha a coluna (A, B, C, D, E ou F) para o usuario " << (i + 1) << ": ";
            cin >> fileira;
            cout << "Digite o numero da fileira (1-10) para o usuario " << (i + 1) << ": ";
            cin >> coluna;
            int fileiraIndex = fileira - 'A';
            int colunaIndex = coluna - 1;
            if (fileiraIndex >= 0 && fileiraIndex < 6 && colunaIndex >= 0 && colunaIndex < 10 && reserva[colunaIndex][fileiraIndex] == 'O') {
                reserva[colunaIndex][fileiraIndex] = 'X';
                cout << "\nPoltrona " << fileira << coluna << " reservada para o usuario " << (i + 1) << ".\n";
                break;
            } else {
                cout << "\nPoltrona invalida. Tente novamente.\n";
            }
        }
    }
}

// Exibir as poltronas reservadas apenas uma vez no final
if (reservado) {
    exibirPoltronas(reserva);
    }
}
return true; // Sucesso na reserva
    }


// Função para o plano de casal
bool planoCasal(char reserva[10][6]) {
    int classe;
    char pessoa1[20], pessoa2[20];

    // Escolha da classe
    while (true) {
        cout << "\nEscolha a classe\n1 - classe Economica (plano basico - sem direito a poltronas proximas a janela)\n2 - classe Executiva (plano avancado - prioridade para poltronas proximas a janela)\n3 - voltar para o menu principal\n";
        cout << "\nEscolha uma opcao: ";
        if (!(cin >> classe) || (classe < 1 || classe > 3)) {
            cout << "\nEntrada invalida. Escolha um numero entre 1 e 3.\n";
            cin.clear(); // Limpa o estado de erro do cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora o restante da entrada inválida
            continue;
        }
        if (classe == 3) {
            cout << "Voltando ao menu principal.\n";
            return false;
        }
        break;
    }

    cout << "Digite o nome da primeira pessoa: ";
    cin >> pessoa1;
    cout << "Digite o nome da segunda pessoa: ";
    cin >> pessoa2;

    cout << "\nVoce escolheu a classe " << (classe == 1 ? "Economica" : "Executiva") << " para o casal " << pessoa1 << " e " << pessoa2 << ".\n";

    if (classe == 1) {
        // Classe Econômica: duas opções
        cout << "\nPreferem:\n1 - Deixar o sistema decidir as poltronas (sem proximidade a janela)\n2 - Escolher manualmente as poltronas:\n ";
        cout << "\nEscolha uma opcao: ";
        int escolhaEconomica;
        if (!(cin >> escolhaEconomica) || (escolhaEconomica != 1 && escolhaEconomica != 2)) {
            cout << "\nEntrada invalida. Escolha 1 ou 2.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }

        if (escolhaEconomica == 1) {
            // Deixar o sistema decidir (assentos próximos, longe da janela)
            bool reservado = false;
            for (int linha = 0; linha < 10 && !reservado; linha++) {
                for (int col = 1; col < 5; col++) {
                    if (reserva[linha][col] == 'O' && reserva[linha][col + 1] == 'O') {
                        reserva[linha][col] = 'X';
                        reserva[linha][col + 1] = 'X';
                        exibirPoltronas(reserva);
                        cout << "\nPoltrona " << (char)('A' + col) << (linha + 1) << " reservada para " << pessoa1 << ".\n";
                        cout << "Poltrona " << (char)('A' + col + 1) << (linha + 1) << " reservada para " << pessoa2 << ".\n";
                        reservado = true;
                        break;
                    }
                }
            }
        } else if (escolhaEconomica == 2) {
            // Escolher manualmente as poltronas
            for (int i = 0; i < 2; i++) {
                char fileira;
                int coluna;
                while (true) {
                    cout << "Escolha a coluna (B, C, D ou E) para o usuario " << (i == 0 ? pessoa1 : pessoa2) << ": ";
                    cout << "\nEscolha a poltrona: ";
                    cin >> fileira;

                    cout << "\nDigite o numero da fileira (1-10) para usuario " << (i == 0 ? pessoa1 : pessoa2) << ": ";
                    cout << "\nEscolha a fileira: ";
                    if (!(cin >> coluna) || coluna < 1 || coluna > 10) {
                        cout << "\nEntrada invalida. Escolha um numero entre 1 e 10.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    int fileiraIndex = fileira - 'A';
                    int colunaIndex = coluna - 1;

                    if (fileiraIndex >= 1 && fileiraIndex <= 4 && colunaIndex >= 0 && colunaIndex < 10 && reserva[colunaIndex][fileiraIndex] == 'O') {
                        reserva[colunaIndex][fileiraIndex] = 'X';
                        exibirPoltronas(reserva);
                        cout << "\nPoltrona " << fileira << coluna << " reservada para " << (i == 0 ? pessoa1 : pessoa2) << ".\n\n";
                        break;
                    } else {
                        cout << "Poltrona invalida ou ja ocupada. Tente novamente.\n";
                    }
                }
            }
        } else {
            cout << "\nOpcao invalida. Tente novamente.\n";
            return false;
        }
    } else {
        // Classe Executiva: opções avançadas
        cout << "\nPreferem:\n1 - Ficar separados, ambos proximos a janela\n2 - Ficar proximos um do outro, um proximo a janela\n3 - Ficar proximos um ao outro, longe da janela\n4 - Escolher manualmente as poltronas\n\nEscolha uma opcao: ";
        int escolhaProximidade;
        if (!(cin >> escolhaProximidade) || (escolhaProximidade < 1 || escolhaProximidade > 4)) {
            cout << "\nEntrada invalida. Escolha um numero entre 1 e 4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }

        if (escolhaProximidade == 1) {
            // Separados, ambos próximos à janela
            for (int i = 0; i < 2; i++) {
                char fileira = (i == 0) ? 'A' : 'F'; // Reservar em A e F
                for (int linha = 0; linha < 10; linha++) {
                    if (reserva[linha][fileira - 'A'] == 'O') {
                        reserva[linha][fileira - 'A'] = 'X';
                        exibirPoltronas(reserva);
                        cout << "\nPoltrona " << fileira << (linha + 1) << " reservada para " << (i == 0 ? pessoa1 : pessoa2) << ".\n";
                        break;
                    }
                }
            }
        } else if (escolhaProximidade == 2) {
            // Próximos um do outro, um próximo à janela
            bool reservado = false;
            for (int linha = 0; linha < 10 && !reservado; linha++) {
                if (reserva[linha][0] == 'O' && reserva[linha][1] == 'O') {
                    reserva[linha][0] = 'X';
                    reserva[linha][1] = 'X';
                    exibirPoltronas(reserva);
                    cout << "\nPoltrona A" << (linha + 1) << " reservada para " << pessoa1 << ".\n";
                    cout << "\nPoltrona B" << (linha + 1) << " reservada para " << pessoa2 << ".\n";
                    reservado = true;
                } else if (reserva[linha][5] == 'O' && reserva[linha][4] == 'O') {
                    reserva[linha][5] = 'X';
                    reserva[linha][4] = 'X';
                    exibirPoltronas(reserva);
                    cout << "\nPoltrona F" << (linha + 1) << " reservada para " << pessoa1 << ".\n";
                    cout << "\nPoltrona E" << (linha + 1) << " reservada para " << pessoa2 << ".\n";
                    reservado = true;
                }
            }
        } else if (escolhaProximidade == 3) {
            // Próximos um ao outro, longe da janela
            bool reservado = false;
            for (int linha = 0; linha < 10 && !reservado; linha++) {
                for (int col = 1; col < 5; col++) {
                    if (reserva[linha][col] == 'O' && reserva[linha][col + 1] == 'O') {
                        reserva[linha][col] = 'X';
                        reserva[linha][col + 1] = 'X';
                        exibirPoltronas(reserva);
                        cout << "\nPoltrona " << (char)('A' + col) << (linha + 1) << " reservada para " << pessoa1 << ".\n";
                        cout << "\nPoltrona " << (char)('A' + col + 1) << (linha + 1) << " reservada para " << pessoa2 << ".\n";
                        reservado = true;
                        break;
                    }
                }
            }
        } else if (escolhaProximidade == 4) {
            // Escolher manualmente as poltronas
            for (int i = 0; i < 2; i++) {
                char fileira;
                int coluna;
                while (true) {
                    exibirPoltronas(reserva);
                    cout << "\nEscolha a coluna (A, B, C, D, E ou F) para o usuario " << (i == 0 ? pessoa1 : pessoa2) << ": ";
                    cin >> fileira;
                    cout << "Digite o numero da fileira (1-10) para usuario " << (i == 0 ? pessoa1 : pessoa2) << ": ";
                    cin >> coluna;
                    int fileiraIndex = fileira - 'A';
                    int colunaIndex = coluna - 1;
                    if (fileiraIndex >= 0 && fileiraIndex < 6 && colunaIndex >= 0 && colunaIndex < 10 && reserva[colunaIndex][fileiraIndex] == 'O') {
                        reserva[colunaIndex][fileiraIndex] = 'X';
                        exibirPoltronas(reserva);
                        cout << "\nPoltrona " << fileira << coluna << " reservada para " << (i == 0 ? pessoa1 : pessoa2) << ".\n";
                        break;

                while (true) {
                    cout << "\nEscolha a coluna (A, B, C, D, E ou F) para o usuario " << (i == 0 ? pessoa2 : pessoa1) << ": ";
                    cin >> fileira;
                    cout << "\nDigite o numero da fileira (1-10) para o usuario " << (i == 0 ? pessoa2 : pessoa1) << ": ";
                    cin >> coluna;
                    int fileiraIndex = fileira - 'A';
                    int colunaIndex = coluna - 1;

                    if (fileiraIndex >= 0 && fileiraIndex < 6 && colunaIndex >= 0 && colunaIndex < 10 && reserva[colunaIndex][fileiraIndex] == 'O') {
                        reserva[colunaIndex][fileiraIndex] = 'X';
                        exibirPoltronas(reserva);
                        cout << "\nPoltrona " << fileira << coluna << " reservada para " << (i == 0 ? pessoa1 : pessoa2) << ".\n";
                        break;
                    } else {
                        cout << "Poltrona invalida ou ja ocupada. Tente novamente.\n";
                            }
                        }
                    }
                }
            }
        } else {
            cout << "\nOpcao invalida. Tente novamente.\n";
            return false;
        }
    }

    return true; // Todas as reservas foram realizadas com sucesso
}

int main() {
    char reserva[10][6]; // Reserva das poltronas
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            reserva[i][j] = 'O'; // Inicializa todas as poltronas como livres
        }
    }
    exibirPoltronas(reserva);

    int opcao;
    do {
        cout << "\n==== Sistema de Reserva de Poltronas ====\n\n";
        cout << "1. Fazer o plano indivual\n2. Fazer o plano familia\n3. Fazer o plano casal\n4. Exibir sistema de poltronas\n5. Sair do sistema\n";
        cout << "\nEscolha uma opcao: ";
        cin >> opcao;

        // Verifica se a entrada é válida
        if (cin.fail()) {
            cin.clear(); // Limpa o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a entrada inválida
            cout << "Entrada invalida. Tente novamente.\n";
            continue; // Retorna ao início do loop
        }
        switch (opcao) {
            case 1:
                reservarPoltrona(reserva, 2); // Por padrão, escolha a classe executiva
                break;
            case 2:
                planoFamiliar(reserva);
                break;
            case 3:
                planoCasal(reserva);
                break;
            case 4:
                exibirPoltronas(reserva);
                break;
            case 5:
                cout << "Saindo do sistema...\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
                break;
        }
    } while (opcao != 5);

    return 0;
}