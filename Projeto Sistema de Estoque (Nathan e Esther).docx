#ifndef PRODUTO_H
#define PRODUTO_H

#define CAPACIDADE 50 // Capacidade máxima da lista de produtos

// Tal Estrutura Estoque
typedef struct { //estrutura que cria um grupo de variáveis. typedef = Type Definition. 
    int codigo;
    char nome[50];
    char prateleira;
    float preco;
    int quantidade;
    int disponivel; // 1 = Sim, 0 = Não
} Produto;

// FUNÇÕES 

// Exibir os dados de um único produto (recebe uma struct Produto).
void exibirProduto(Produto prod);

// 1. Buscar um produto pelo código (devolve a posição dele na lista, ou -1 se não achar).
int buscarPorCodigo(Produto lista[], int total, int codigo);

// 2. Buscar um produto pelo nome (mesma ideia: devolve a posição na lista, ou -1 se não achar).
int buscarPorNome(Produto lista[], int total, const char *nome);

// 3. Cadastrar um produto na lista.
int cadastrarProduto(Produto lista[], int total);

// Listar todos os produtos da lista.
void listarProdutos(Produto lista[], int total);

// Função auxiliar para o sub-menu de pesquisa
void pesquisarProduto(Produto lista[], int total);

#endif