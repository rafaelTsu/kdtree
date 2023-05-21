#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcao.h"

int main(){
	tnode *node;
	muni temp;
	FILE *arq;
	int option; //option_menu;

	do{
		printf("Digite a opção:\n0 - Sair\n1 - Procurar pelos municípios mais próximos do Brasil\n2 - Procurar pelos fastfoods mais próximos\n");
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