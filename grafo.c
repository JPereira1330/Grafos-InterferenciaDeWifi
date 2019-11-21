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

int calcMaiorDistancia(GRAF grafo, int indice){
    int maiorDistancia = 0;

    for(int j = 0; j < TAMANHO; j++){
        if(grafo->adjacente[indice][j] > maiorDistancia){
            maiorDistancia = j;
        }
    }

    return maiorDistancia;
}

void calcGrafo(GRAF grafo, int contador){

    int maior = 0;
    int sair = 1;
    int indice = 0;
    int problema = 0;
    int maiorDistancia = 0;

    indice = calcMaiorConexao(grafo);
    grafo->frequencia[indice] = frequenciaOrdem[contador];

    for(int i = 0; i < TAMANHO; i++){
        if(!grafo->adjacente[indice][i] && indice != i && !grafo->definido[i] ) {
        if(!grafo->adjacente[indice][i] && indice != i && !grafo->definido[i]) {
            for(int j = 0; j < TAMANHO; j++){

                // Verifica se possui algum
                if(grafo->adjacente[i][j] && grafo->frequencia[j] == grafo->frequencia[indice]){
                    problema = 1;
                }

                if(j == TAMANHO - 1 && !problema){

                    for(int k = 0; k < TAMANHO - 1; k++){
                        if( grafo->adjacente[i][k] > maior){
                            maior = k;
                        }
                    }

                    if(grafo->definido[maior]){
                        if( grafo->frequencia[maior] < 6){
                            grafo->frequencia[i] = frequenciaAlta[contador];
                        }else{
                            grafo->frequencia[i] = frequenciaBaixa[contador];
                        }  
                    }

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

void printMatriz(GRAF grafo){
    for (int i = 0; i < TAMANHO; ++i) {
    printf(" %c ", grafo->vertice_id[i]);
    for (int j = 0; j < TAMANHO; ++j) {
        printf(" [%2.0d] ", grafo->adjacente[i][j]);
    }
    printf("\n");
    }
}

void desenhar(GRAF grafo){
    
	FILE *file;
	char buffer[4096];
    char label [1024];

	// Configurações
	char *cabec = "graph g{\n rankdir=\"LR\"\n label=\"Grafos - Ciencia da computacao 2019\"\n node [shape=\"circle\"]\n\n";

	file = fopen(ARQUIVO, "w");
	if(file == NULL){
		printf("Ocorreu um erro ao abrir o arquivo");
		return;
	}

	// Printando cabeçalho
	snprintf(buffer, strlen(cabec), "%s", cabec);
	fprintf(file, "%s",buffer);

	// Printando label
	for(int x = 0; x < TAMANHO; x++){
		switch(grafo->frequencia[x]){
			case 1:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#FFFF00\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;
			case 2:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#99CC32\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;
			case 3:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#70DB93\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;			
			case 4:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#32CD99\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;			
			case 5:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#0000FF\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;			
			case 6:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#007FFF\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;			
			case 7:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#6B238E\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;			
			case 8:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#C0D9D9\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;			
			case 9:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#3299CC\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;
			case 10:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#5F9F9F\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;
			case 11:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#42426F\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;
			case 12:	
				snprintf(label, sizeof(label), " %c [label=\"%c - %d\", style=filled, fillcolor=\"#00009C\"]\n",grafo->vertice_id[x], grafo->vertice_id[x], grafo->frequencia[x]);
				break;
		}
		fprintf(file, "%s",label);
	}

	fprintf(file, "\n");

	// Printando grafo
	for(int i = 0; i < TAMANHO; i++){
		for(int j = i; j < TAMANHO; j++){
			if(grafo->adjacente[i][j]){
				snprintf(label, sizeof(label), " %c -- %c [ label = \"%d\" ]\n",grafo->vertice_id[i], grafo->vertice_id[j], grafo->adjacente[i][j]);
				fprintf(file, "%s",label);
			}
		}
	}

	fprintf(file, "}");

	fclose(file);
}