#include <stdio.h>
#include "util.h"

// A tal Função de Limpeza 
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}