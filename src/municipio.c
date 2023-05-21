#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcao.h"

int main(){
	vizinho *neighbors;
	tnode *node;
	muni temp;
	FILE *arq;
	point aux;
	int size;
	int option; //option_menu;

	do{
		printf("0 - Sair\n1 - Procurar pelos municípios mais próximos do Brasil\n2 - Procurar pelos fastfoods mais próximos\nDigite a opção: ");
		scanf("%d",&option);

		if(option == 1){
			arq = fopen("csv/municipios.csv","r");

			if(arq == NULL){
				printf("Erro ao abrir o arquivo.");
				exit(1);
			}
			else{
				initialize(&node);

				while(feof(arq) == 0){
					fscanf(arq, "%d, %[^,],%lf,%lf,%d,%d, %[^,],%d, %[^\n]", 
					&temp.cod_ibge, temp.nome, &temp.coord[0], &temp.coord[1], 
					&temp.capital, &temp.codigo_uf, temp.siafi_id, &temp.ddd,
					temp.fuso_horario);

					inserir(&node, aloca_muni(temp.cod_ibge, temp.nome, temp.coord[0], temp.coord[1], 
					temp.capital, temp.codigo_uf, temp.siafi_id, temp.ddd,
					temp.fuso_horario), 0);
				}
			}
			printf("\nDigite quantos vizinhos mais próximos deseja buscar:\n");
			scanf("%d", &size);
			printf("\nDigite as coordenadas: \n");
			scanf("%lf %lf", &aux.coord[0], &aux.coord[1]);

			neighbors = malloc(size * sizeof(vizinho));
			initialize_neighbors(neighbors, size);

			searchNeighbors(node, aux, neighbors, size, 0);

			for(int i = 0; i<size; i++){
				muni *municipios = (muni *)neighbors[i].vizin;
				printf("\n%d° cidade mais perto:\n", i+1);
				printf("Código IBGE: %d\nNome do município: %s\nLatitude: %f\nLongitude: %f\nCapital: %d\nCódigo UF: %d\nSiafi ID: %s\nDDD: %d\nFuso horário: %s\nRegião: %s\nUF: %s\n\n", 
					municipios->cod_ibge, municipios->nome, municipios->coord[0], municipios->coord[1], 
					municipios->capital, municipios->codigo_uf, municipios->siafi_id, municipios->ddd,
					municipios->fuso_horario, municipios->regiao, municipios->uf);
			}
			printf("\n\n");

			free(neighbors);
			freeNode(node);
		}

		/*else if(option == 2){
			arq = fopen("csv/Fast_Food_Restaurants_US.csv","r");

			if(arq == NULL){
				printf("Erro ao abrir o arquivo.");
				exit(1);
			}
			else{
				initialize(&node);

				while(feof(arq) == 0){
					fscanf(arq, "%d, %[^,], %[^,], %[^,], %[^,],%lf")
				}
			}
		}*/

		fclose(arq);	
	}while(option!=0);


	return EXIT_SUCCESS;
}