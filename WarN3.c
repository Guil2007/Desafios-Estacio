#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char** destino, const char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador);
void liberarMemoria(Territorio* mapa, char* missao);

int main() {
    srand(time(NULL));

    int qtd, opAtacante, opDefensor;
    char* missaoJogador = NULL;
    char corJogador[10];

    // Banco de missões pré-definidas
    const char* bancoMissoes[] = {
        "Dominar 3 territorios",
        "Ter mais de 10 tropas totais",
        "Conquistar o territorio inicial do inimigo",
        "Eliminar a cor Azul",
        "Possuir 2 territorios com mais de 5 tropas"
    };
    int totalMissoesCadastradas = 5;

    printf("--- WAR ESTRATEGICO 2026: SISTEMA DE MISSOES ---\n");
    printf("Digite a cor do seu exercito: ");
    scanf("%s", corJogador);

    printf("Quantos territorios existem no mapa? ");
    scanf("%d", &qtd);

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (!mapa) return 1;

    cadastrarTerritorios(mapa, qtd);

    // Atribuição de Missão (Passagem por Referência para o ponteiro)
    atribuirMissao(&missaoJogador, bancoMissoes, totalMissoesCadastradas);
    
    printf("\n========================================\n");
    printf("SUA MISSAO SECRETA: %s\n", missaoJogador);
    printf("========================================\n");

    int jogoAtivo = 1;
    while (jogoAtivo) {
        exibirMapa(mapa, qtd);
        
        printf("\n(Ataque) Escolha Atacante e Defensor [indices] ou -1 para encerrar turno: ");
        scanf("%d", &opAtacante);
        if (opAtacante == -1) break;
        scanf("%d", &opDefensor);

        // Validação de ataque (apenas cores inimigas)
        if (strcmp(mapa[opAtacante].cor, corJogador) != 0) {
            printf("ERRO: Voce so pode atacar com tropas da sua cor (%s)!\n", corJogador);
        } else if (strcmp(mapa[opAtacante].cor, mapa[opDefensor].cor) == 0) {
            printf("ERRO: Nao pode atacar seu proprio territorio!\n");
        } else {
            atacar(&mapa[opAtacante], &mapa[opDefensor]);
        }

        // Verificação silenciosa de vitória
        if (verificarMissao(missaoJogador, mapa, qtd, corJogador)) {
            printf("\n!!! PARABENS !!!\nVoce cumpriu a missao: %s\n", missaoJogador);
            jogoAtivo = 0;
        }
    }

    liberarMemoria(mapa, missaoJogador);
    return 0;
}

// Atribui uma missão sorteada usando alocação dinâmica (malloc)
void atribuirMissao(char** destino, const char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    
    // Aloca espaço para a string da missão (+1 para o '\0')
    *destino = (char*) malloc((strlen(missoes[indiceSorteado]) + 1) * sizeof(char));
    
    if (*destino != NULL) {
        strcpy(*destino, missoes[indiceSorteado]);
    }
}

// Simula o ataque com dados
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Dados -> Atacante: %d | Defensor: %d\n", dadoAtk, dadoDef);

    if (dadoAtk > dadoDef) {
        printf("VITORIA! Territorio %s conquistado!\n", defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
    } else {
        printf("DERROTA! O atacante perdeu 1 tropa.\n");
        if (atacante->tropas > 1) atacante->tropas--;
    }
}

// Verifica se as condições de vitória foram atingidas (Lógica simplificada)
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    int contadorTerritorios = 0;
    
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            contadorTerritorios++;
        }
    }

    // Lógica exemplo: Se a missão for "Dominar 3 territorios"
    if (strstr(missao, "3 territorios") && contadorTerritorios >= 3) return 1;
    
    // Lógica padrão: Se conquistar todos os territórios do mapa
    if (contadorTerritorios == tamanho) return 1;

    return 0;
}

void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Nome do Territorio %d: ", i);
        scanf("%s", mapa[i].nome);
        printf("Cor: ");
        scanf("%s", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n--- ESTADO DO MAPA ---");
    for (int i = 0; i < quantidade; i++) {
        printf("\n[%d] %-15s | Cor: %-10s | Tropas: %d", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n----------------------\n");
}

void liberarMemoria(Territorio* mapa, char* missao) {
    if (mapa) free(mapa);
    if (missao) free(missao);
    printf("\nMemoria limpa com sucesso.\n");
}