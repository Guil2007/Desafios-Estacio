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

//Prototipos de Funções
void limparBuffer();
void exibirMenu();
void adicionarLivro(Livro* biblioteca, int* numLivros);
void listarLivros(Livro* biblioteca, int numLivros);
void emprestarLivro(Livro* biblioteca, Emprestimo* emprestimos, int* numEmprestimos, int numLivros);
void listarEmprestimos(Emprestimo* emprestimos, int numEmprestimos);
void liberarMemoria(Livro* biblioteca, Emprestimo* emprestimos);

int main() {
    Livro* biblioteca = (Livro*) calloc(MAX_LIVROS, sizeof(Livro));
    Emprestimo* emprestimos = (Emprestimo*) calloc(MAX_EMPRESTIMOS, sizeof(Emprestimo));
    
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    
    int numLivros = 0;
    int numEmprestimos = 0;
    int opcao;
    
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                adicionarLivro(biblioteca, &numLivros);
                break;
            case 2:
                listarLivros(biblioteca, numLivros);
                break;
            case 3:
                emprestarLivro(biblioteca, emprestimos, &numEmprestimos, numLivros);
                break;
            case 4:
                listarEmprestimos(emprestimos, numEmprestimos);
                break;
            case 5:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    liberarMemoria(biblioteca, emprestimos);
    return 0;
}
// Implementação das Funções
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void exibirMenu() {
    printf("\n--- Sistema de Biblioteca ---\n");
    printf("1. Adicionar Livro\n");
    printf("2. Listar Livros\n");
    printf("3. Emprestar Livro\n");
    printf("4. Listar Empréstimos\n");
    printf("5. Sair\n");
}

void adicionarLivro(Livro* biblioteca, int* numLivros) {
    if (*numLivros >= MAX_LIVROS) {
        printf("Capacidade máxima de livros atingida!\n");
        return;
    }
    
    Livro* novoLivro = &biblioteca[*numLivros];
    
    printf("Digite o título do livro: ");
    fgets(novoLivro->titulo, TAM_STRING, stdin);
    novoLivro->titulo[strcspn(novoLivro->titulo, "\n")] = 0; // Remove newline

    printf("Digite o autor do livro: ");
    fgets(novoLivro->autor, TAM_STRING, stdin);
    novoLivro->autor[strcspn(novoLivro->autor, "\n")] = 0; // Remove newline

    printf("Digite a editora do livro: ");
    fgets(novoLivro->editora, TAM_STRING, stdin);
    novoLivro->editora[strcspn(novoLivro->editora, "\n")] = 0; // Remove newline

    printf("Digite a edição do livro: ");
    scanf("%d", &novoLivro->edicao);
    limparBuffer();

    novoLivro->disponivel = 1; // Livro está disponível
    (*numLivros)++;
    
    printf("Livro adicionado com sucesso!\n");
}

void listarLivros(Livro* biblioteca, int numLivros) {
    if (numLivros == 0) {
        printf("Nenhum livro cadastrado na biblioteca.\n");
        return;
    }
    
    printf("\n--- Lista de Livros ---\n");
    for (int i = 0; i < numLivros; i++) {
        Livro* livro = &biblioteca[i];
        printf("[%d] Título: %s | Autor: %s | Editora: %s | Edição: %d | Status: %s\n", 
               i + 1, 
               livro->titulo, 
               livro->autor, 
               livro->editora, 
               livro->edicao, 
               livro->disponivel ? "Disponível" : "Emprestado");
    }
}

void emprestarLivro(Livro* biblioteca, Emprestimo* emprestimos, int* numEmprestimos, int numLivros) {
    if (*numEmprestimos >= MAX_EMPRESTIMOS) {
        printf("Capacidade máxima de empréstimos atingida!\n");
        return;
    }
    
    int indiceLivro;
    printf("Digite o número do livro que deseja emprestar: ");
    scanf("%d", &indiceLivro);
    limparBuffer();
    
    if (indiceLivro < 1 || indiceLivro > numLivros) {
        printf("Índice de livro inválido!\n");
        return;
    }
    
    Livro* livroSelecionado = &biblioteca[indiceLivro - 1];
    
    if (!livroSelecionado->disponivel) {
        printf("O livro '%s' já está emprestado.\n", livroSelecionado->titulo);
        return;
    }
    
    Emprestimo* novoEmprestimo = &emprestimos[*numEmprestimos];
    novoEmprestimo->indiceLivro = indiceLivro - 1;
    
    printf("Digite o nome do usuário que está emprestando o livro: ");
    fgets(novoEmprestimo->nomeUsuario, TAM_STRING, stdin);
    novoEmprestimo->nomeUsuario[strcspn(novoEmprestimo->nomeUsuario, "\n")] = 0; // Remove newline
    
    livroSelecionado->disponivel = 0; // Marca o livro como emprestado
    (*numEmprestimos)++;
    
    printf("Livro '%s' emprestado com sucesso para %s!\n", livroSelecionado->titulo, novoEmprestimo->nomeUsuario);
}

void listarEmprestimos(Emprestimo* emprestimos, int numEmprestimos) {
    if (numEmprestimos == 0) {
        printf("Nenhum empréstimo registrado.\n");
        return;
    }
    
    printf("\n--- Lista de Empréstimos ---\n");
    for (int i = 0; i < numEmprestimos; i++) {
        Emprestimo* emprestimo = &emprestimos[i];
        printf("[%d] Livro Índice: %d | Usuário: %s\n", 
               i + 1, 
               emprestimo->indiceLivro + 1, 
               emprestimo->nomeUsuario);
    }
}

void liberarMemoria(Livro* biblioteca, Emprestimo* emprestimos) {
    free(biblioteca);
    free(emprestimos);
    printf("Memória liberada com sucesso!\n");
}
