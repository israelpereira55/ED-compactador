#include <stdlib.h>
#include <stdio.h>

#include "arvore.h"

struct arv {
	char c;
	int peso;
	Arv *esq,
	     *dir,
	     *prox,
	     *ant;
};

//typedef struct vet_caminho VCaminho; //Estará comentado só até finalizar o teste.

struct vet_caminho{
	int *v;
	int n;
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
	a->ant = NULL;
	
	a->peso = 0;
	a->c = c;
	return a;
}

Arv* arv_inicializa_huffman(int i, Arv* esq, Arv* dir) {
	
	Arv* a = (Arv*) malloc (sizeof(Arv));
	a->esq = esq;
	a->dir = dir;
	a->prox = NULL;
	a->ant = NULL;
	
	a->peso = i;
	a->c = 'q'; //Apenas evitando um aviso de erro no valgrind. Só serão acessados os caracteres das folhas.
	return a;
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

Arv* arv_pai (Arv* a, char c) {

	if ( !arv_pertence(a, c) || a->c == c ) {
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

Arv* arv_retira (Arv* a, char c) {
	
	if( !arv_pertence(a, c) ) {
		return NULL;
	}

	Arv *pai = arv_pai(a, c);

	if (pai->esq != NULL) {
		if (pai->esq->c == c) {
			Arv* filho = pai->esq;
			pai->esq = NULL;
			
			filho->ant = NULL;
			return filho;
		}
	}

	Arv* filho = pai->dir;
	pai->dir = NULL;
	filho->ant = NULL;
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

Arv* arv_troca(Arv* a) {//Pega a primeira árvore da lista e troca de posição com a segunda, respeitando o encadeamento da lista.
			//Lembrar que para usar esse funcao, a lista precisa ter pelo menos duas arvores.
			//Se a for a primeira árvore da lista, o cliente precisará atualizar seu ponteiro com o retorno desta função, senão, não é necessário.
/*
	if (a == NULL) {
		return NULL;
	}
	
	if (a->prox == NULL) {
		return a;
	}
	
	Arv* troca = a->prox; 
				//Caso geral
	
	troca->ant = a->ant;
	a->ant->prox = troca;
	
	a->prox = troca->prox;
	
	troca->prox = a;
	a->ant = troca;                                                                                                                            
	
	a->prox = troca->prox;
	troca->prox = a;
	a->prox->ant = a;*/
	
	Arv* troca = a->prox; //Contempla o caso geral e os casos de contorno
	
	if(a->ant != NULL) {
		a->ant->prox = troca;
	}
	
	if (troca->prox != NULL) {
		troca->prox->ant = a;
	}
	
	a->prox = troca->prox;
	troca->ant = a->ant;
	troca->prox = a;
	a->ant = troca;
	
	return troca;
}
/*
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
}*/

Arv* arv_ordena(Arv* a) { //Algorítmo: Primeiro loop: Passar todos os maiores para a direita, começando do início da lista para o final. 
			  //		Segundo loop: Passar todos os menores para a esquerda, começando do final da lista para o início.
			  //Após a ordenação a lista o cliente deve colocar a lista original para que o ponteiro seja atualizado.

	Arv *aux = a;

	if(a == NULL) {
		return NULL;
	}
	
	while (aux->prox != NULL) {
		if (aux->peso > aux->prox->peso) {
		
			if (aux->ant == NULL) {
				a = arv_troca(aux);
			} else {
				arv_troca(aux);
			}
			
		} else {
			aux = aux->prox;
		}
	}
	
	//Aqui aux->prox é NULL.
	while (aux->ant != NULL) { 
		if (aux->peso < aux->ant->peso) {
		
			if (aux->ant->ant == NULL) {
				a = arv_troca(aux->ant);
			} else {
				arv_troca(aux->ant);
			}
			
		} else {
			aux = aux->ant;
		}
	}
	return a;
}	



/*
Arv* arv_ordena(Arv* a) { //Algorítmo: Primeiro loop: Passar todos os maiores para a direita, começando do início da lista para o final. 
			  //		Segundo loop: Passar todos os menores para a esquerda, começando do final da lista para o início.
                          //Após a ordenação a lista o cliente deve colocar a lista original para que o ponteiro seja atualizado.
	Arv *aux = a;
	Arv *troca = NULL;

	if(a == NULL) {
		return NULL;
	}
	
	while (aux->prox != NULL) {
		if (aux->peso > aux->prox->peso) {
		
			if (aux->ant == NULL) {
				a = arv_troca(aux);
			} else {
				  arv_troca(aux);
			}
		} else {
		aux = aux->prox;}
	}
	
	//Aqui aux->prox é NULL.
	while (aux->ant != NULL) { 
		if (aux->peso < aux->ant->peso) {
                    if (aux->ant->ant == NULL) {
                        a = arv_troca(aux->ant);
                    } else {
			arv_troca(aux->ant);
                    }
                } else{
                aux = aux->ant;
                }
        }
	
	return a;
}*/

		

Arv* arv_insere (Arv* original, Arv* adicional) { //A árvore adicional será inserida no final da ávore original.
						  //original e adicional nao podem ser NULL. TESTAR COMO VOID
	Arv* aux = original;
	
	if(aux == NULL) {
		return adicional;
	}
	
	while(aux->prox != NULL) {
		aux = aux->prox;
	}
	
	aux->prox = adicional;
	adicional->ant = aux;
	return original;
}
	
Arv* arv_huffman (Arv* lista) {

	lista = arv_ordena(lista);
	Arv *esq = NULL;
	Arv *dir = NULL;
	Arv *Tr = NULL;

	while (lista->prox != NULL) {
		esq = lista;
		lista = lista->prox;
		lista->ant = NULL;
		esq->prox = NULL;
		
		dir = lista;
		lista = lista->prox;
		if(lista != NULL) {
			lista->ant = NULL;
		}
		dir->prox = NULL;
		
		printf("p:%d\n", esq->peso + dir->peso);
		Tr =  arv_inicializa_huffman(esq->peso + dir->peso, esq, dir);
		
//		if(esq->peso + dir->peso > lista-> peso) {
			lista = arv_insere(lista, Tr); //Insere no Tr no final da lista.
			lista = arv_ordena(lista); //Provavelmente há como inserir o elemento de maneira já ordenada não precisando rodar esse algorítmo.
//		} else {
//			Tr->prox = lista;
//			lista->ant = Tr;
//		}
	}

	return lista;
}

Arv* arv_cria_lista_frequencia (int* freq) { //Cria uma lista de árvore contendo apenas raízes com itens sendo a frequencia dado o vetor freq.
	int i;
	Arv* lista = NULL;
		
	for(i=0; i<256; i++) {
		if (freq[i] != 0) {
			lista = arv_insere (lista, arv_inicializa_huffman(freq[i], NULL, NULL) ); // Cria uma árvore contendo só a raiz com o valor da frequencia sendo o item e insere na lista.
		}
	}

	return lista;
}

void arv_imprime_lista (Arv* lista) {
	Arv* aux = lista;

	while(aux != NULL) {
		printf("%d ", aux->peso);
		aux = aux->prox;
	}
	
	return;
}

int arv_elem_profundidade(Arv* a, char c) { //Necessário que c pertença a árvore.
	
	Arv *pai = arv_pai(a, c);
	
	if(pai == NULL) {
		return 0;
	}
	
	return 1 + arv_elem_profundidade(a, pai->c);
}

VCaminho* vcaminho_inicializa(int n) {
	VCaminho *vc = (VCaminho*) malloc (sizeof(VCaminho));
	
	vc->v = (int*) malloc (n * sizeof(int));
	vc->n = n;
	return vc;
}

VCaminho* vcaminho_retorna_caminho(Arv *a, char c) { // Necessário que c pertença a árvore.
						     // Int só até aprender a manipular bitmap, depois retornar bitmap.
	int profundidade = arv_elem_profundidade(a, c);
	VCaminho *vc = vcaminho_inicializa(profundidade);
	
	Arv *pai = arv_pai (a, c);
	char elem = c;
	
	while (profundidade > 0) {
	
		if (pai->esq != NULL) {
		
			if (pai->esq->c == elem) {
				vc->v[profundidade-1] = 0;
			} else {
				vc->v[profundidade-1] = 1;
			}
			
		} else {
			vc->v[profundidade-1] = 1;
		}
		
		elem = pai->c;
		pai = arv_pai (a, pai->c);
		profundidade--;
	}
	
	return vc;
}

void vcaminho_imprime(VCaminho *vc) {
	int i;
	
	for (i=0; i<vc->n; i++) {
		printf("%d ", vc->v[i]);
	}
	return;
} 
	
	
	
	
