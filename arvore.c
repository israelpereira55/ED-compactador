#include <stdlib.h>
#include <stdio.h>

#include "arvore.h"

struct arv {
	char c;
	int peso;
	Arv *esq,
	     *dir,
	     *prox;
};

Arv* arv_inicializa_unica(char c) {
	
	Arv* a = (Arv*) malloc (sizeof(Arv));
	a->esq = NULL;
	a->dir = NULL;
	a->prox = NULL;
	a->c = c;
	return a;
}

Arv* arv_inicializa(char c, Arv* esq, Arv* dir) {
	
	Arv* a = (Arv*) malloc (sizeof(Arv));
	a->esq = esq;
	a->dir = dir;
	a->prox = NULL;
	
	a->peso = 0;
	a->c = c;
	return a;
}

Arv* arv_inicializa_huffman(int i, Arv* esq, Arv* dir) {
	
	Arv* a = (Arv*) malloc (sizeof(Arv));
	a->esq = esq;
	a->dir = dir;
	a->prox = NULL;
	
	a->peso = i;
	a->c = "q";
	return a;
}

Arv* arv_pai (Arv* a, char c) {

	if ( !arv_pertence(a, c) ) {
		return NULL;
	}

	//No teste acima já sabemos que nossa arvore não está vazia caso as instruções abaixo forem executadas, então, o teste a == null não é necessário.
	
	if(a->esq != NULL) {
		if (a->esq->c == c) {
			return a;
		}
	}

	if(a->dir != NULL) {
		if (a->dir->c == c) {
			return a;
		}
	}

	Arv* teste = arv_pai(a->esq, c);

	if (teste != NULL) {
		return teste;
	}

	return arv_pai(a->dir, c);
}

int arv_pertence (Arv* a, char c) {
	
	if(a == NULL) {
		return 0;
	}

	if (a->c == c) {
		return 1;
	}

	return arv_pertence(a->esq, c) || arv_pertence(a->dir, c);
}

Arv* arv_retira (Arv* a, char c) {
	
	if( !arv_pertence(a, c) ) {
		return NULL;
	}

	Arv *pai = arv_pai(a, c);

	if (pai->esq != NULL) {
		if (pai->esq->c == c) {
			Arv* filho = pai->esq;
			pai->esq = NULL;
			return filho;
		}
	}

	Arv* filho = pai->dir;
	pai->dir = NULL;
	return filho;
}
/*
Arv* arv_busca(Arv* a, char c) {

	if (a == NULL) {
		return NULL;
	}

	if(a->c == c) {
		return a;
	}*/

Arv* arv_libera(Arv* a) {
	
	if (a == NULL) {
		return NULL;
	}

	if (a->esq != NULL) {
		a->esq = arv_libera(a->esq);
	}

	if(a->dir != NULL) {
		a->dir = arv_libera(a->dir);
	}

	free(a);
	return NULL;
}

char info (Arv* a) { //Cuidado com falhas seg.
	return a->c;
}

Arv* arv_ordena(Arv* a) {

	Arv *aux = a;
	Arv *troca = NULL;

	if(a == NULL) {
		return NULL;
	}
	
	while (aux->prox != NULL) {
		if (aux->peso > aux->prox->peso) {
			troca = aux;
			aux->prox = aux->prox->prox;
			aux->prox->prox = troca;
		}
		aux = aux->prox;
	}
	
	return aux;
}
				
Arv* arv_troca(Arv* a) { //Lembrar que para usar esse funcao, a lista precisa ter pelo menos duas arvores.
/*
	if (a == NULL) {
		return NULL;
	}
	
	if (a->prox == NULL) {
		return a;
	}*/
	
	Arv* troca = a->prox;
	
	a->prox = troca->prox;
	troca->prox = a;
	
	return troca;
}

Arv* arv_insere (Arv* original, Arv* adicional) { //A árvore adicional será inserida no final da ávore original.
						  //original e adicional nao podem ser NULL. TESTAR COMO VOID
	Arv* aux = original;
	
	if(aux->prox == NULL) {
		aux->prox = adicional;
		return original;
	}
	
	while(aux->prox != NULL) { //da p descer um nivel
		aux = aux->prox;
	}
	
	aux->prox = adicional;
	return original;
}
	
Arv* arv_huffman (Arv* lista) {

	lista = arv_ordena(lista);
	Arv *esq = NULL;
	Arv *dir = NULL;
	Arv *Tr = NULL;

	while (lista->prox != NULL) {
	
//		if (lista->peso > lista->prox->peso) {
//			troca = lista->prox;
//			lista->prox = lista->prox->prox;
//			troca->prox = lista;
			
//			lista = arv_troca(lista);
//		}
		
		esq = lista;
		lista = a->prox;
		esq->prox = NULL;
		
		dir = lista;
		lista = a->prox->prox;
		dir->prox = NULL;
		
		Tr =  arv_inicializa_huffman(esq->peso + dir->peso, esq, dir);
		lista = arv_insere(lista, Tr);
	}

	return lista;
}







