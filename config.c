//
// Created by Nyex on 17/11/2019.
// CODIGO FONTE PARA CONFIGURAÇÃO DO GRAFO
//

#include "config.h"

char matrizAdj[TAMANHO][TAMANHO] = {
    //   A  B  C  D  E  F  G  H  I  J
         0, 1, 2, 3, 0, 0, 0, 0, 0,10,// A
         1, 0, 4, 0, 0, 0, 0, 0, 0, 0,// B
         2, 4, 0, 5, 6, 0, 0, 0, 0, 0,// C
         3, 0, 5, 0, 0, 7, 0, 0, 0, 0,// D
         0, 0, 6, 0, 0, 8, 9, 0, 1, 0,// E
         0, 0, 0, 7, 8, 0, 0, 0, 1, 1,// F
         0, 0, 0, 0, 9, 0, 0, 1, 0, 0,// G
         0, 0, 0, 0, 0, 0, 1, 0, 1, 0,// H
         0, 0, 0, 0, 1, 1, 0, 1, 0, 1,// I
        10, 0, 0, 0, 0, 1, 0, 0, 1, 0	// J
};

char verticesNome[TAMANHO] = {'A','B','C','D','E','F','G','H','I','J'};
int frequenciaOrdem[12] = { 1,6,11,4,9,12,2,7,10,3,8,5 };