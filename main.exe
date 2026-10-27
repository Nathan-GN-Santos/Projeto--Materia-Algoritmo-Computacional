//EXECUTAT
//.\main.exe

//Dicionário
//Funções Nativas do C:
// scanf = scan formatted, função que lê dados do teclado e  salva em uma variável.
// fgets = file get string ,função que lê uma linha de texto do teclado e salva em uma variável do tipo string.

//Especificadores:
// %d = inteiro decimal

//CÓDIGO
#include <stdio.h>
#include "produto.h" // Modificação: Inclui produto.h para acessar a struct Produto, CAPACIDADE e as funções do sistema
#include "util.h"    // Modificação: Inclui util.h para ter acesso ao limparBuffer() após a leitura da opção do menu no scanf

int main() {
    // Configura a saída e entrada do console do Windows para a página de código UTF-8 (65001)
    //SetConsoleOutputCP(CPAGE_UTF8);
   // SetConsoleCP(CPAGE_UTF8);

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
        printf("4 - Sair\n");
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
                printf("\nSaindo do sistema... \n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Escolha entre 1 e 4.\n");
                break;
        }

    } while (opcao != 4);

    return 0;
}