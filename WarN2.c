#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da Struct
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Funções
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    int qtd, opAtacante, opDefensor;
    Territorio* mapa = NULL;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("--- JOGO DE GUERRA (WAR)---\n");
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Alocação Dinâmica utilizando calloc
    mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    int jogando = 1;
    while (jogando) {
        exibirMapa(mapa, qtd);
        printf("\n--- MENU DE ATAQUE ---\n");
        printf("Escolha o indice do território ATACANTE (ou -1 para sair): ");
        scanf("%d", &opAtacante);

        if (opAtacante == -1) break;

        printf("Escolha o indice do território DEFENSOR: ");
        scanf("%d", &opDefensor);

        // Validações básicas
        if (opAtacante >= 0 && opAtacante < qtd && opDefensor >= 0 && opDefensor < qtd) {
            // Regra: Não pode atacar a própria cor
            if (strcmp(mapa[opAtacante].cor, mapa[opDefensor].cor) == 0) {
                printf("\nERRO: Você não pode atacar um território da mesma cor!\n");
            } else {
                atacar(&mapa[opAtacante], &mapa[opDefensor]);
            }
        } else {
            printf("\nÍndices inválidos!\n");
        }
    }

    liberarMemoria(mapa);
    printf("Sistema encerrado. Memória liberada.\n");
    return 0;
}

// Função para cadastrar os dados iniciais
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do Exército: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe o status atual de todos os territórios usando ponteiros
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n--- MAPA ATUAL ---");
    for (int i = 0; i < quantidade; i++) {
        // Uso de aritmética de ponteiros para acessar os dados
        Territorio* t = (mapa + i);
        printf("\n[%d] %s | Cor: %s | Tropas: %d", i, t->nome, t->cor, t->tropas);
    }
    printf("\n------------------\n");
}

// Lógica de ataque utilizando ponteiros
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\nATAQUE: %s (%s) atacando %s (%s)...\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Simulação de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dados: Atacante %d vs Defensor %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITÓRIA DO ATACANTE! O território foi conquistado.\n");
        
        // Atualiza campos do defensor
        strcpy(defensor->cor, atacante->cor);
        
        // Transfere metade das tropas do atacante para o novo território
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
    } else {
        printf("DERROTA DO ATACANTE! O defensor resistiu.\n");
        // Penalidade: perde uma tropa se houver mais de uma
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    }
}

// Liberação de memória alocada
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}