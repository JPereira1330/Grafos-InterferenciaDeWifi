//
// Created by Nyex on 17/11/2019.
//

#include "grafo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

struct graf {
    char vertice_id[TAMANHO];
    int vertice_adj_qnt[TAMANHO];
    char adjacente[TAMANHO][TAMANHO];
    int frequencia[TAMANHO];
    char definido[TAMANHO];
};

GRAF newGrafo(){
    GRAF novo;
    novo = (GRAF) malloc(sizeof(struct graf));

    if(novo == NULL){
        printf(" [ERRO] Nao foi possivel alocar na memoria");
        return NULL;
    }

    memset(novo, 0, sizeof(struct graf));

    return novo;
}

void init(GRAF grafo){
    for(int x = 0; x < TAMANHO; x++){
        grafo->frequencia[x] = 99;
        grafo->definido[x] = 0;
    }

    memcpy(grafo->adjacente, &matrizAdj, sizeof(grafo->adjacente));
    memcpy(grafo->vertice_id, &verticesNome, sizeof(grafo->vertice_id));
}

void calcAdjacencia(GRAF grafo){
    for (int i = 0; i < TAMANHO; i++){
        for (int j = 0; j < TAMANHO; j++){
            if(grafo->adjacente[i][j]){
                grafo->vertice_adj_qnt[i]++;
            }
        }
    }
}

int calcMaiorConexao(GRAF grafo){

    int maior = 0;
    int ligacao = 0;

    for(int i = 0; i < TAMANHO; i++){
        if(!grafo->definido[i]){
            if(ligacao < grafo->vertice_adj_qnt[i]){
                ligacao = grafo->vertice_adj_qnt[i];
                maior = i;
            }
        }
    }

    return maior;
}

void calcGrafo(GRAF grafo, int contador){

    int sair = 1;
    int indice = 0;
    int problema = 0;

    indice = calcMaiorConexao(grafo);
    grafo->frequencia[indice] = frequenciaOrdem[contador];

    for(int i = 0; i < TAMANHO; i++){
        if(!grafo->adjacente[indice][i] && indice != i && !grafo->definido[i] ) {
            for(int j = 0; j < TAMANHO; j++){

                // Verifica se possui algum
                if(grafo->adjacente[i][j] && grafo->frequencia[j] == grafo->frequencia[indice]){
                    problema = 1;
                }

                if(j == TAMANHO - 1 && !problema){
                    grafo->frequencia[i] = frequenciaOrdem[contador];
                    grafo->definido[i] = 1;
                }else if(j == TAMANHO - 1){
                    problema = 0;
                }

            }
        }
    }

    grafo->definido[indice] = 1;


    // Se todos ja estao preenchidos
    for (int i = 0; i < TAMANHO; i++){
        if(!grafo->definido[i]){
            sair = 0;
        }
    }

    if(sair){
        printf(" O grafico foi todo listado\n");
        return;
    }else{
        contador++;
        calcGrafo(grafo, contador);
    }
}

void calc(GRAF grafo){
    calcAdjacencia(grafo);
    calcGrafo(grafo, 0);
}

void printGrafo(GRAF grafo){
    for (int i = 0; i < TAMANHO; ++i) {
        printf("Ponto de acesso %c no canal %d \n",grafo->vertice_id[i], grafo->frequencia[i]);
    }
}