//
// Created by Nyex on 17/11/2019.
//

#ifndef GRAFOS_GRAFO_H
#define GRAFOS_GRAFO_H

    typedef struct graf *GRAF;

    GRAF newGrafo();
    void init(GRAF grafo);
    void calc(GRAF grafo);
    void printGrafo(GRAF grafo);
    void desenhar(GRAF grafo);
    void printMatriz(GRAF grafo);

#endif //GRAFOS_GRAFO_H
