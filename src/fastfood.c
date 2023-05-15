#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"

int compara_fastfood(const void *a, const void *b, int index){
	return (*(fast *)a).coord[index] - (*(fast *)b).coord[index];
}

int main(){
	
}