#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Constantes Globais
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100
#define TAM_STRING 100

// Estrutura para representar um livro

typedef struct {
    char titulo[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao ;
    int disponivel; // 1 para disponível, 0 para emprestado
} Livro;

// Estrutura para representar um empréstimo
typedef struct {
    int indiceLivro;
    char nomeUsuario[TAM_STRING];
} Emprestimo;

// Limpa o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função Principal
int main() {
    Livro *biblioteca;
    Emprestimo *emprestimos;

    biblioteca = (Livro*)calloc(MAX_LIVROS, sizeof(Livro));
    emprestimos = (Emprestimo*)malloc(MAX_EMPRESTIMOS * sizeof(Emprestimo));

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }
    int opcao, numLivros = 0, numEmprestimos = 0;

    do{
        printf("==============================\n");
        printf("  Sistema de Biblioteca\n");
        printf("==============================\n");
        printf("1. Adicionar Livro\n");
        printf("2. Listar Livros\n");
        printf("3. Emprestar Livro\n");
        printf("4. Listar Empréstimos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        printf("==============================\n");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1: //cadastrar livro
            printf("--- CADASTRO DE NOVO LIVRO ---\n\n\n");
            if (numLivros < MAX_LIVROS)
            {
                printf("Digite o título do livro: ");
                fgets(biblioteca[numLivros].titulo, TAM_STRING, stdin);
                printf("Digite o autor do livro: ");
                fgets(biblioteca[numLivros].autor, TAM_STRING, stdin);
                printf("Digite a editora do livro: ");
                fgets(biblioteca[numLivros].editora, TAM_STRING, stdin);
                printf("Digite a edição do livro: ");
                scanf("%d", &biblioteca[numLivros].edicao);
                biblioteca[numLivros].disponivel = 1; // Livro disponível
                numLivros++;
                printf("Livro cadastrado com sucesso!\n");
            } else {
                printf("Capacidade máxima de livros atingida.\n");
            }
            break;
            
        
        default:
            break;

        case 2: //listar livros
            printf("--- LISTA DE LIVROS ---\n\n\n");
            for (int i = 0; i < numLivros; i++) {
                printf("Livro %d:\n", i + 1);
                printf("Título: %s", biblioteca[i].titulo);
                printf("Autor: %s", biblioteca[i].autor);
                printf("Editora: %s", biblioteca[i].editora);
                printf("Edição: %d\n", biblioteca[i].edicao);
                printf("Status: %s\n\n", biblioteca[i].disponivel ? "Disponível" : "Emprestado");
            }
            break;
        case 3: //emprestar livro
            printf("--- EMPRÉSTIMO DE LIVRO ---\n\n\n");
            if (numEmprestimos >= MAX_EMPRESTIMOS) {
                printf("Capacidade máxima de empréstimos atingida.\n");
            }else {
                printf("Lista de Livros disponíveis:\n");
                int disponiveis = 0;
                for (int i = 0; i < numLivros; i++) {
                    if (biblioteca[i].disponivel) {
                        printf("%d. %s", i + 1, biblioteca[i].titulo);
                        disponiveis++;
            }
            break;
        }
        if (disponiveis == 0) {
            printf("Nenhum livro disponível para empréstimo.\n");
        } else {
            int escolha;
            printf("Escolha o número do livro que deseja emprestar: ");
            scanf("%d", &escolha);
            limparBuffer();
            if (escolha < 1 || escolha > numLivros || !biblioteca[escolha - 1].disponivel) {
                printf("Opção inválida ou livro indisponível.\n");
            } else {
                printf("Digite seu nome: ");
                fgets(emprestimos[numEmprestimos].nomeUsuario, TAM_STRING, stdin);
                emprestimos[numEmprestimos].indiceLivro = escolha - 1;
                biblioteca[escolha - 1].disponivel = 0; // Marca como emprestado
                numEmprestimos++;
                printf("Livro emprestado com sucesso!\n");
            }
        }

        case 4: //listar emprestimos
            printf("--- LISTA DE EMPRÉSTIMOS ---\n\n\n");
            for (int i = 0; i < numEmprestimos; i++) {
                int idx = emprestimos[i].indiceLivro;
                printf("Empréstimo %d:\n", i + 1);
                printf("Livro: %s", biblioteca[idx].titulo);
                printf("Usuário: %s\n\n", emprestimos[i].nomeUsuario);
            }
            break;
    }
    printf("Pressione Enter para continuar...");
    getchar();
    break;

        case 0:
            printf("Saindo do sistema. Até mais!\n");
            break;

}
    } while (opcao != 0);
    
    free(biblioteca);
    free(emprestimos);

    printf("Memoria Liberada com sucesso!\n");
    return 0;
}