#include <stdio.h>
#include "produto.h" // Modificação: Inclui produto.h para acessar a struct Produto, CAPACIDADE e as funções do sistema
#include "util.h"    // Modificação: Inclui util.h para ter acesso ao limparBuffer() após a leitura da opção do menu no scanf

int main() {
    int opcao = 0;
    Produto listaProdutos[CAPACIDADE]; // Vetor com capacidade para 50 produtos
    int totalProdutos = 0;             // Contador de produtos cadastrados

    do {
        // Exibição do Menu Principal
        printf("\n====================================\n");
        printf("       SISTEMA DE ESTOQUE - MENU    \n");
        printf("====================================\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Pesquisar Produto\n");
        printf("4 - Atualizar Produto\n");
        printf("5 - Remover Produto\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                totalProdutos = cadastrarProduto(listaProdutos, totalProdutos);
                break;

            case 2:
                listarProdutos(listaProdutos, totalProdutos);
                break;

            case 3:
                pesquisarProduto(listaProdutos, totalProdutos);
                break;

            case 4:
                atualizarProduto(listaProdutos, totalProdutos);
                break;

            case 5:
                totalProdutos = removerProduto(listaProdutos, totalProdutos);
                break;

            case 6:
                printf("\nSaindo do sistema... \n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Escolha entre 1 e 6.\n");
                break;
        }

    } while (opcao != 6);

    return 0;
}