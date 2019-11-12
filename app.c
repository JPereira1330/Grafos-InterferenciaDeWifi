#include "app.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 10

struct graf {
	char vertice_id[TAMANHO];
	int vertice_nivel[TAMANHO];
	char adjacente[TAMANHO][TAMANHO];
	int frequencia[TAMANHO];
	char definido[TAMANHO];
};

char matrizAdj[TAMANHO][TAMANHO] = {
//  A B C D E F G H I J
	0,1,1,1,0,0,0,0,0,1,// A
	1,0,1,0,0,0,0,0,0,0,// B
	1,1,0,1,1,0,0,0,0,0,// C
	1,0,1,0,0,1,0,0,0,0,// D
	0,0,1,0,0,1,1,0,1,0,// E
	0,0,0,1,1,0,0,0,1,1,// F
	0,0,0,0,1,0,0,1,0,0,// G
	0,0,0,0,0,0,1,0,1,0,// H
	0,0,0,0,1,1,0,1,0,1,// I
	1,0,0,0,0,1,0,0,1,0	// J
};

int count = -1;
char problema = 0;
int quant_indice[TAMANHO];

char vertice_nome[TAMANHO] = {'A','B','C','D','E','F','G','H','I','J'};
const int frequencia[12] = { 1,6,11,4,9,12,2,7,10,3,8,5 };
const char *arquivo = "grafo.gv";

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

void desenhar(GRAF grafo){

	FILE *file;
	char buffer[4096];
	char label [1024];

	// Configurações
	char *cabec = "digraph g{\n rankdir=\"LR\"\n label=\"Grafos - Ciencia da computacao 2019\"\n node [shape=\"circle\"]\n\n";

	file = fopen(arquivo, "a");
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
		for(int j = 0; j < TAMANHO; j++){
			if(grafo->adjacente[i][j]){
				snprintf(label, sizeof(label), " %c -> %c\n",grafo->vertice_id[i], grafo->vertice_id[j], grafo->frequencia[j]);
				fprintf(file, "%s",label);
			}
		}
	}

	fprintf(file, "}");

	fclose(file);
}

void calcGrafo(GRAF grafo){

	char sair = 1;
	int maior = 0;
	int ligacao = 0;

	count++;
	
	// Capturando a quantia de indice da tabela
	if(count == 0){
		for (int i = 0; i < TAMANHO; i++){
			for (int j = 0; j < TAMANHO; j++){
				if(grafo->adjacente[i][j]){
					quant_indice[i]++;
				}
			}
		}
	}

	// Capturando o com maior conexao
	for(int i = 0; i < TAMANHO; i++){
		if(!grafo->definido[i]){
			grafo->vertice_nivel[i] = quant_indice[i];
			if(ligacao < grafo->vertice_nivel[i]){
				ligacao = grafo->vertice_nivel[i];
				maior = i;
			}
		}
	}

	grafo->frequencia[maior] = frequencia[count];
	printf("Ponto de acesso %c no canal %d \n",grafo->vertice_id[maior], grafo->frequencia[maior]);

	for(int i = 0; i < TAMANHO; i++){
		if(!grafo->adjacente[maior][i] && maior != i && !grafo->definido[i] ){
			for(int j = 0; j < TAMANHO; j++){	

				if(grafo->adjacente[i][j] && grafo->frequencia[j] == grafo->frequencia[maior]){
					problema = 1;
				}

				if(j == TAMANHO - 1 && !problema){
					grafo->frequencia[i] = frequencia[count];
					printf("Ponto de acesso %c no canal %d \n",grafo->vertice_id[i], grafo->frequencia[i]);
					grafo->definido[i] = 1;
					problema = 0;
				}else if(j == TAMANHO - 1){
					problema = 0;
				}

			}
		}
	}

	grafo->definido[maior] = 1;

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
		calcGrafo(grafo);
	}
}

int main(){

	GRAF grafo = newGrafo();
	
	// Inicializando valores
	for(int x = 0; x < TAMANHO; x++){
		grafo->frequencia[x] = 99;
		grafo->definido[x] = 0;
	}

	// Inicializando grafo
	memcpy(grafo->adjacente, &matrizAdj, sizeof(grafo->adjacente));
	memcpy(grafo->vertice_id, &vertice_nome, sizeof(grafo->vertice_id));

	calcGrafo(grafo);
	desenhar(grafo);

	return 0;
}