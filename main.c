#include <stdio.h>

#include "grafo.h"

int main() {

    GRAF grafo = newGrafo();

    init(grafo);
    calc(grafo);
    printGrafo(grafo);
    desenhar(grafo);
    printMatriz(grafo);
    
    return 0;
}