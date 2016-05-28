/*
*********************************
* Programa testador do TAD Arvore
*********************************
*/
#include <stdio.h>
#include "arquivo.h"
#include "arvore.h"

int main() {
	
	int *v = arquivo_frequencia("teste.txt");
	vet_imprime(v);

	int *x = vet_inicializa();
	x[0] = 10; x[1] = 1; x[2] = 3;
	printf("\n\n\n");
	
	Arv* lista = arv_cria_lista_frequencia(x);
	arv_imprime_lista (lista);
	
	printf("\n\n\ntroca:");
	Arv* troca = arv_troca(lista);
	arv_imprime_lista (troca);
	
	printf("\n\n\nordenada:");
	Arv* ordenada = arv_ordena(troca);
	arv_imprime_lista (ordenada);
/*
	printf("\n\n\n");
	Arv* ordenada = arv_ordena(lista);
	arv_imprime_lista (ordenada);*/
	
//	Arv* huff = arv_huffman (lista);
//	arv_imprime_lista (huff);
	
	
	return 0;
}
