#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "util.h"

void exibirCategoria(Categoria cat) {
    printf("\n------------------------------------\n");
    printf("Codigo da Categoria: %d\n", cat.codigo);
    printf("Nome da Categoria:   %s\n", cat.nome);
    printf("------------------------------------\n");
}

int buscarCategoriaPorCodigo(Categoria lista[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscarCategoriaPorNome(Categoria lista[], int total, const char *nome) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

int cadastrarCategoria(Categoria lista[], int total) {
    if (total >= CAPACIDADE_CATEGORIAS) {
        printf("\n[ERRO] A lista de categorias esta cheia (limite de 20)!\n");
        return total;
    }

    Categoria cat;
    printf("\n--- CADASTRO DE CATEGORIA ---\n");

    // Validação do Código da Categoria
    do {
        printf("Digite o Codigo da categoria (inteiro positivo): ");
        scanf("%d", &cat.codigo);
        limparBuffer();
        if (cat.codigo <= 0) {
            printf("[ERRO] Codigo invalido! Deve ser maior que zero.\n");
        } else if (buscarCategoriaPorCodigo(lista, total, cat.codigo) != -1) {
            printf("[ERRO] Codigo de categoria ja cadastrado!\n");
        }
    } while (cat.codigo <= 0 || buscarCategoriaPorCodigo(lista, total, cat.codigo) != -1);

    // Validação do Nome da Categoria
    do {
        printf("Digite o Nome da categoria: ");
        fgets(cat.nome, sizeof(cat.nome), stdin);
        cat.nome[strcspn(cat.nome, "\n")] = '\0';
        if (strlen(cat.nome) == 0) {
            printf("[ERRO] O nome da categoria nao pode ficar em branco!\n");
        }
    } while (strlen(cat.nome) == 0);

    lista[total] = cat;
    printf("\n[SUCESSO] Categoria cadastrada com sucesso!\n");
    exibirCategoria(cat);

    return total + 1;
}

void listarCategorias(Categoria lista[], int total) {
    if (total == 0) {
        printf("\n[AVISO] Nenhuma categoria cadastrada.\n");
        return;
    }

    printf("\n=== LISTA DE CATEGORIAS ===\n");
    for (int i = 0; i < total; i++) {
        exibirCategoria(lista[i]);
    }
}

// Persistência: Salvar categorias em arquivo de texto
void salvarCategoriasArquivo(Categoria lista[], int total) {
    FILE *file = fopen("categorias.txt", "w");
    if (file == NULL) {
        return;
    }
    fprintf(file, "%d\n", total);
    for (int i = 0; i < total; i++) {
        fprintf(file, "%d\n%s\n", lista[i].codigo, lista[i].nome);
    }
    fclose(file);
}

// Persistência: Carregar categorias do arquivo de texto
int carregarCategoriasArquivo(Categoria lista[]) {
    FILE *file = fopen("categorias.txt", "r");
    if (file == NULL) {
        return 0;
    }
    int total = 0;
    if (fscanf(file, "%d", &total) != 1) {
        fclose(file);
        return 0;
    }
    for (int i = 0; i < total; i++) {
        fscanf(file, "%d", &lista[i].codigo);
        fgetc(file);
        fgets(lista[i].nome, sizeof(lista[i].nome), file);
        lista[i].nome[strcspn(lista[i].nome, "\n")] = '\0';
    }
    fclose(file);
    return total;
}