#include <iostream>
#include <limits> // Para std::numeric_limits

// Função para exibir o estado atual das poltronas
void exibirPoltronas(const char reserva[10][6]) {
    // Formatação para exibir de maneira mais intuitiva
    printf("\n\t\t[A] [B] [C]\t[D] [E] [F]\n");
    for (int x = 0; x < 10; x++) {
        if (x < 9) printf("\n\t0%d\t", x + 1); // Formatação para exibir fileira 01 a 09
        else printf("\n\t%d\t", x + 1); // Exibir fileira 10

        for (int y = 0; y < 6; y++) {
            printf("[%c] ", reserva[x][y]); // Exibir o estado da poltrona (vazia ou reservada)
            if (y == 2) {
                printf("\t"); // Espaço para indicar o corredor
            }
        }
    }
    printf("\n");
}

// Função para verificar se uma poltrona é válida na classe econômica
bool poltronaValida(char poltrona, int classe) {
    // Restrição de classe econômica às poltronas B, C, D, E
    if (classe == 1 && (poltrona == 'A' || poltrona == 'F')) {
        return false;
    }
    return true;
}

// Função para reservar uma poltrona individual
bool reservarPoltrona(char reserva[10][6]) {
    int fileira, classe;
    char poltrona;

    // Escolha da classe
    while (true) {
        printf("\nEscolha a classe\n1 - classe Economica (plano basico sem direito a poltronas proximas a janela)\n2 - classe Executiva (prioridade para poltronas proximas a janela)\n3 - Cancelar reserva e voltar: ");
        if (!(std::cin >> classe) || (classe != 1 && classe != 2 && classe != 3)) {
            printf("\nClasse invalida. Tente novamente.\n");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (classe == 3) {
            printf("Reserva cancelada. Retornando ao menu principal...\n");
            return false; // Retorna ao menu principal
        }
        if (classe == 2) {
            printf("\nAviso: Classe executiva tem prioridade para escolher poltronas proximas a janela (A ou F).\n");
        }
        break;
    }

    // Verificar se o usuário quer uma recomendação
    printf("Deseja uma recomendacao de poltrona? (1 - Sim, 2 - Nao, 3 - Cancelar e voltar): ");
    int recomendacao;
    std::cin >> recomendacao;

    // Se o usuário deseja uma recomendação, vamos buscar uma poltrona disponível
    if (recomendacao == 1) {
        for (fileira = 0; fileira < 10; fileira++) {
            for (int col = 0; col < 6; col++) {
                // Prioridade para janelas se for classe executiva
                if (classe == 2 && (col == 0 || col == 5) && reserva[fileira][col] == 'O') {
                    poltrona = 'A' + col;
                    printf("\nRecomendacao: Fileira %d, Poltrona %c (Proxima a janela).\n", fileira + 1, poltrona);
                    printf("Deseja reservar essa poltrona? (1 - Sim, 2 - Nao, 3 - Cancelar e voltar): ");
                    int aceitar;
                    std::cin >> aceitar;
                    if (aceitar == 3) {
                        printf("Reserva cancelada. Retornando ao menu principal...\n");
                        return false; // Retorna ao menu principal
                    }
                    if (aceitar == 1) {
                        reserva[fileira][col] = 'X'; // Marca a poltrona como reservada
                        printf("\nPoltrona %c na fileira %d reservada com sucesso!\n", poltrona, fileira + 1);
                        exibirPoltronas(reserva);
                        return true; // Retorna após a reserva
                    }
                }
            }
        }
        // Se não encontrou poltrona na janela, busca qualquer uma disponível
        for (fileira = 0; fileira < 10; fileira++) {
            for (int col = 0; col < 6; col++) {
                if (reserva[fileira][col] == 'O' && poltronaValida('A' + col, classe)) {
                    poltrona = 'A' + col; // A primeira poltrona disponível
                    printf("\nRecomendacao: Fileira %d, Poltrona %c.\n", fileira + 1, poltrona);
                    printf("Deseja reservar essa poltrona? (1 - Sim, 2 - Nao, 3 - Cancelar e voltar): ");
                    int aceitar;
                    std::cin >> aceitar;
                    if (aceitar == 3) {
                        printf("Reserva cancelada. Retornando ao menu principal...\n");
                        return false; // Retorna ao menu principal
                    }
                    if (aceitar == 1) {
                        reserva[fileira][col] = 'X'; // Marca a poltrona como reservada
                        printf("\nPoltrona %c na fileira %d reservada com sucesso!\n", poltrona, fileira + 1);
                        exibirPoltronas(reserva);
                        return true; // Retorna após a reserva
                    }
                    else {
                        printf("Continuando com a escolha manual da poltrona...\n");
                        break; // Interrompe o loop e permite a escolha manual
                    }
                }
            }
        }
        printf("\nNao ha poltronas livres. Tente escolher manualmente ou consulte o suporte.\n");
        return false; // Retorna se não houver poltronas disponíveis
    }

    // Caso o usuário não queira recomendação
    while (true) {
        printf("\nDigite a fileira (1-10) ou 0 para cancelar e voltar: ");
        if (!(std::cin >> fileira) || (fileira < 0 || fileira > 10)) {
            printf("\nEntrada invalida. Digite um numero entre 0 e 10.\n");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (fileira == 0) {
            printf("Reserva cancelada. Retornando ao menu principal...\n");
            return false; // Retorna ao menu principal
        }

        printf("Digite a poltrona [A-F] ou 0 para cancelar e voltar: ");
        std::cin >> poltrona;

        if (poltrona == '0') {
            printf("Reserva cancelada. Retornando ao menu principal...\n");
            return false; // Retorna ao menu principal
        }

        // Normalizando a entrada para letras maiúsculas
        poltrona = toupper(poltrona);

        // Verificar se a poltrona é válida para a classe escolhida
        if (!poltronaValida(poltrona, classe)) {
            printf("\nPoltrona invalida para a classe economica. Escolha entre B, C, D, E.\n");
            continue;
        }

        if (poltrona < 'A' || poltrona > 'F') {
            printf("\nPoltrona invalida. Tente novamente.\n");
            continue;
        }

        int acento = poltrona - 'A'; // Calcula o índice da poltrona a partir do caractere

        if (reserva[fileira - 1][acento] == 'X') {
            printf("\nPoltrona ja reservada. Escolha outra.\n");
        } else {
            reserva[fileira - 1][acento] = 'X'; // Marca a poltrona como reservada
            printf("\nPoltrona %c na fileira %d reservada com sucesso!\n", poltrona, fileira);
            break;
        }
    }

    exibirPoltronas(reserva);
    return true;
}

// Função para fazer planos familiares
bool planoFamiliar(char reserva[10][6]) {
    int numPessoas, classe;

    // Escolha da classe
    while (true) {
        printf("\nEscolha a classe\n1 - classe Economica (plano basico sem direito a poltronas proximas a janela)\n2 - classe Executiva (prioridade para poltronas proximas a janela)\n3 - Cancelar reserva e voltar: ");
        if (!(std::cin >> classe) || (classe != 3 && classe != 1 && classe != 2)) {
            printf("\nClasse invalida. Tente novamente.\n");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (classe == 3) {
            printf("Reserva cancelada. Retornando ao menu principal...\n");
            return false; // Retorna ao menu principal
        }
        if (classe == 2) {
            printf("\nAviso: Classe executiva tem prioridade para escolher poltronas proximas a janela (A ou F).\n");
        }
        break;
    }

    // Solicitar número de pessoas no plano
    while (true) {
        printf("\nDigite o numero de pessoas (2, 3, 4 ou 5) ou digite 0 para cancelar: ");
        std::cin >> numPessoas;

        if (numPessoas == 0) {
            printf("Reserva cancelada. Retornando ao menu principal...\n");
            return false; // Retorna ao menu principal
        }

        if (numPessoas < 2 || numPessoas > 5) {
            printf("\nNumero de pessoas invalido para o plano. Tente novamente.\n");
            continue;
        }
        break;
    }

    // Realiza a reserva para o número de pessoas
    for (int i = 0; i < numPessoas; i++) {
        printf("\nReserva para a pessoa %d:\n", i + 1);
        if (!reservarPoltrona(reserva)) {
            return false; // Se a reserva falhar, retorna ao menu
        }
    }

    return true; // Todas as reservas foram feitas com sucesso
}

// Função principal
int main() {
    char reserva[10][6];

    // Inicializa as poltronas como livres
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 6; y++) {
            reserva[x][y] = 'O'; // 'O' para poltrona livre
        }
    }

    // Exibir poltronas inicialmente
    exibirPoltronas(reserva);

    // Opções do menu
    while (true) {
        printf("\n          Sistema de reservas de poltronas:\n\n1 - Reservar poltrona individual\n2 - Reservar plano de poltrona familiar\n3 - Sair do sistema\nEscolha uma opcao: "); 
        int opcao;
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                reservarPoltrona(reserva);
                break;
            case 2:
                planoFamiliar(reserva);
                break;
            case 3:
                printf("Saindo do sistema...\n");
                return 0; // Finaliza o programa
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0; // Finaliza o programa
}
