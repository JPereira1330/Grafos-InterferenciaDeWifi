#include <stdio.h>

#include "grafo.h"

#include <g>

int main() {

    GRAF grafo = newGrafo();

    init(grafo);
    calc(grafo);
    printGrafo(grafo);
    //generateGrafo(grafo);

    return 0;
}