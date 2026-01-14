

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constantes globais
#define MAX_TERRITORIOS 5

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;


// Limpa buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função Principal
int main() {
    Territorio territorios[MAX_TERRITORIOS];
    int numTerritorios = 0;
    int escolha;

    printf("Bem-vindo ao WarNovato!\n\n\n");

    // Cadastro de territórios
    do {
        if (numTerritorios >= MAX_TERRITORIOS) {
            printf("Número máximo de territórios atingido.\n");
            break;
        }

        printf("Digite o nome do território: ");
        fgets(territorios[numTerritorios].nome, sizeof(territorios[numTerritorios].nome), stdin);
        territorios[numTerritorios].nome[strcspn(territorios[numTerritorios].nome, "\n")] = 0; 

        printf("Digite a cor do território: ");
        fgets(territorios[numTerritorios].cor, sizeof(territorios[numTerritorios].cor), stdin);
        territorios[numTerritorios].cor[strcspn(territorios[numTerritorios].cor, "\n")] = 0; 

        printf("Digite o número de tropas no território: ");
        scanf("%d", &territorios[numTerritorios].tropas);
        limparBufferEntrada();

        numTerritorios++;

        printf("Deseja adicionar outro território? (1 - Sim, 0 - Não): ");
        scanf("%d", &escolha);
        limparBufferEntrada();
    } while (escolha == 1);

    // Exibição dos territórios cadastrados
    printf("\n\n### MAPA DO MUNDO ATUAL ###\n\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("Território %d:\n Nome: %s\n Cor: %s\n Tropas: %d\n\n", 
               i + 1, 
               territorios[i].nome, 
               territorios[i].cor,
               territorios[i].tropas);
    }

    return 0;
}

