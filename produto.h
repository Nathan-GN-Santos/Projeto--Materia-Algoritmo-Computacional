#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "produto.h"
#include "util.h" // Modificação: Necessário incluir para usar a função limparBuffer() nas validações de cadastro

// Exibir os dados de um único produto (recebe uma struct Produto).
void exibirProduto(Produto prod) {
    printf("\n====================================\n");
    printf("Codigo:               %d\n", prod.codigo);
    printf("Nome:                 %s\n", prod.nome);
    printf("Prateleira:           %c\n", prod.prateleira);
    printf("Preco Unitario:       R$ %.2f\n", prod.preco);
    printf("Qtd em Estoque:       %d\n", prod.quantidade);
    printf("Disponivel P/ Venda: %s (%d)\n", 
            prod.disponivel == 1 ? "SIM" : "NAO", prod.disponivel);
    printf("====================================\n");
}

// 1. Buscar um produto pelo código (devolve a posição dele na lista, ou -1 se não achar).
int buscarPorCodigo(Produto lista[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) {
            return i; // Retorna o índice onde o produto foi encontrado
        }
    }
    return -1; // Retorna -1 indicando que não foi encontrado
}

// 2. Buscar um produto pelo nome (mesma ideia: devolve a posição na lista, ou -1 se não achar).
int buscarPorNome(Produto lista[], int total, const char *nome) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].nome, nome) == 0) {
            return i; // Retorna o índice do produto encontrado
        }
    }
    return -1; // Retorna -1 se não encontrar
}

// 3. Cadastrar um produto na lista.
int cadastrarProduto(Produto lista[], int total) {
    if (total >= CAPACIDADE) {
        printf("\n[ERRO] A lista de produtos esta cheia (limite de 50 produtos)!\n");
        return total;
    }

    Produto prod;

    printf("\n--- CADASTRO DE PRODUTO ---\n");

    //4. Validacao do Código
    do {
        printf("Digite o Codigo do produto (inteiro positivo): ");
        scanf("%d", &prod.codigo);
        limparBuffer();
        if (prod.codigo <= 0) {
            printf("[ERRO] Codigo invalido! Deve ser um numero maior que zero.\n");
        } else if (buscarPorCodigo(lista, total, prod.codigo) != -1) {
            printf("[ERRO] Codigo ja cadastrado! Digite um codigo diferente.\n");
        }
    } while (prod.codigo <= 0 || buscarPorCodigo(lista, total, prod.codigo) != -1);

    //Validação do Nome 
    do {
        printf("Digite o Nome do produto: ");
        fgets(prod.nome, sizeof(prod.nome), stdin);
        // Remove a quebra de linha '\n' capturada pelo fgets
        prod.nome[strcspn(prod.nome, "\n")] = '\0';

        if (strlen(prod.nome) == 0) {
            printf("[ERRO] O nome nao pode ficar em branco!\n");
        }
    } while (strlen(prod.nome) == 0);

    //Validação da Prateleira ('A', 'B', 'C' ou 'D')
    do {
        printf("Digite a Prateleira ('A', 'B', 'C' ou 'D'): ");
        scanf(" %c", &prod.prateleira);
        prod.prateleira = toupper(prod.prateleira); // Converte para maiúscula
        limparBuffer();

        if (prod.prateleira != 'A' && prod.prateleira != 'B' && 
            prod.prateleira != 'C' && prod.prateleira != 'D') {
            printf("[ERRO] Prateleira invalida! Escolha apenas A, B, C ou D.\n");
        }
    } while (prod.prateleira != 'A' && prod.prateleira != 'B' && 
             prod.prateleira != 'C' && prod.prateleira != 'D');

    //Validação do Preço Unitário
    do {
        printf("Digite o Preco Unitario (R$)(use . em vez de , se centavos): ");
        scanf("%f", &prod.preco);
        limparBuffer();

        if (prod.preco <= 0.0f) {
            printf("[ERRO] Preco deve ser maior que zero!\n");
        }
    } while (prod.preco <= 0.0f);

    //Validação da Quantidade em Estoque 
    do {
        printf("Digite a Quantidade em Estoque: ");
        scanf("%d", &prod.quantidade);
        limparBuffer();

        if (prod.quantidade < 0) {
            printf("[ERRO] Quantidade nao pode ser negativa!\n");
        }
    } while (prod.quantidade < 0);

    // --- Regra de Negócio: Cálculo automático de disponibilidade ---
    if (prod.quantidade > 0) {
        prod.disponivel = 1;
    } else {
        prod.disponivel = 0;
    }

    // Guarda o produto na próxima posição livre do vetor
    lista[total] = prod;
    total++;

    // --- Resumo do Cadastro ---
    printf("\n====================================\n");
    printf("    PRODUTO CADASTRADO COM SUCESSO! \n");
    exibirProduto(prod);

    return total; // Retorna o novo total de produtos cadastrados
}

// Listar todos os produtos da lista.
void listarProdutos(Produto lista[], int total) {
    if (total == 0) {
        printf("\n[AVISO] Nenhum produto foi cadastrado ainda.\n");
        return;
    }

    printf("\n=== LISTA DE PRODUTOS CADASTRADOS (%d) ===\n", total);
    for (int i = 0; i < total; i++) {
        printf("\n--- Produto %d de %d ---", i + 1, total);
        exibirProduto(lista[i]);
    }
}

// Função auxiliar para o sub-menu de pesquisa
void pesquisarProduto(Produto lista[], int total) {
    if (total == 0) {
        printf("\n[AVISO] Nenhum produto cadastrado para pesquisar.\n");
        return;
    }

    int opcaoBusca = 0;
    printf("\n--- PESQUISAR PRODUTO ---\n");
    printf("1 - Por codigo\n");
    printf("2 - Por nome\n");
    printf("Escolha uma opcao de busca: ");
    scanf("%d", &opcaoBusca);
    limparBuffer();

    if (opcaoBusca == 1) {
        int codigoBusca;
        printf("Digite o codigo do produto: ");
        scanf("%d", &codigoBusca);
        limparBuffer();

        int pos = buscarPorCodigo(lista, total, codigoBusca);
        if (pos != -1) {
            printf("\n[SUCESSO] Produto encontrado!");
            exibirProduto(lista[pos]);
        } else {
            printf("\n[ERRO] Nenhum produto encontrado com o codigo informado.\n");
        }
    } else if (opcaoBusca == 2) {
        char nomeBusca[50];
        printf("Digite o nome do produto: ");
        fgets(nomeBusca, sizeof(nomeBusca), stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

        int pos = buscarPorNome(lista, total, nomeBusca);
        if (pos != -1) {
            printf("\n[SUCESSO] Produto encontrado!");
            exibirProduto(lista[pos]);
        } else {
            printf("\n[ERRO] Nenhum produto encontrado com o nome informado.\n");
        }
    } else {
        printf("\n[ERRO] Opcao de busca invalida!\n");
    }
}