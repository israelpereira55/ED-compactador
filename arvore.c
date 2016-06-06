#include <stdlib.h>
#include <stdio.h>

#include "bitmap.h"
#include "arvore.h"

struct arv {
	char c;
	int peso;
	VCaminho *vc;
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
	a->ant = NULL;
	a->peso = 0;
	a->c = c;
	a->vc = NULL;
	return a;
}

Arv* arv_inicializa(char c, Arv* esq, Arv* dir) {
	
	Arv* a = (Arv*) malloc (sizeof(Arv));
	a->esq = esq;
	a->dir = dir;
	a->prox = NULL;
	a->ant = NULL;
	
	a->vc = NULL;
	
	a->c = c;
	a->peso = 0;
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

		
/*
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
}*/

Arv* arv_insere (Arv* original, Arv* adicional) { //A árvore adicional será inserida no final da ávore original.
						  //original e adicional nao podem ser NULL. TESTAR COMO VOID
	Arv* aux = original;
	
	if(original == NULL) {
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
			arv_ordena(lista); //Provavelmente há como inserir o elemento de maneira já ordenada não precisando rodar esse algorítmo.
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
		printf("%c ", aux->c);
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

VCaminho* vcaminho_inicializa(int n) { //MUDEI O N PARA ZERO!!
	VCaminho *vc = (VCaminho*) malloc (sizeof(VCaminho));
	
	vc->v = (int*) malloc (n * sizeof(int));
	vc->n = 0;
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

VCaminho* arv_retorna_vcaminho(Arv* a) { // A diferente de null
	return a->vc;
}

Arv* arv_prox (Arv *a) { //Absolutamente só para testes
	return a->prox;
}

/*
Arv* arv_folhas (Arv* a) { // Da p retirar essa arvore folhas da entrada
	Arv* nova = NULL;
	Arv* folhas = NULL;
	Arv* p, *verifica = NULL;;
	
	if (a == NULL) {
		return NULL; //PARECE QUE VAI DAR PROBLEMA
	}
	
	if (a->esq == NULL && a->dir == NULL){
		Arv *nova = arv_inicializa_unica(a->c);
		folhas = arv_insere (folhas, nova);
		return folhas;
	}
	
	for (p=a; p!=NULL; p=p->prox) {
		verifica = arv_folhas(a->esq);
		if (verifica!= NULL) {
			arv_insere(folhas, verifica);
		}
		verifica = arv_folhas(a->dir);
		
		if (verifica != NULL) {
			folhas = arv_insere(folhas, verifica);
		}
	}
	
	return folhas;
}*/


Arv* arv_folhas (Arv* original, Arv* percorre, Arv* folhas) {
	Arv* nova = NULL;
	Arv* p;
			
	if (percorre == NULL) {
		return NULL; //PARECE QUE VAI DAR PROBLEMA
	}
								
	if (percorre->esq == NULL && percorre->dir == NULL){
		Arv *nova = arv_inicializa_unica(percorre->c);
		nova->vc = vcaminho_retorna_caminho(original, percorre->c);
		folhas = arv_insere (folhas, nova);
		return folhas;
	}
																	
	for (p=percorre; p!=NULL; p=p->prox) {
		folhas = arv_folhas(original, percorre->esq, folhas);
		folhas = arv_folhas(original, percorre->dir, folhas);
	}
																								
	return folhas;
}

VCaminho* vcaminho_escreve_chap (VCaminho *vc){ //# = 0x23

	//vc->v[8] = {0,0,1,0,0,0,1,1}; // Testar
	vc->v[0] = 0;
	vc->v[1] = 0;
	vc->v[2] = 1;
	vc->v[3] = 0;
	vc->v[4] = 0;
	vc->v[5] = 0;
	vc->v[6] = 1;
	vc->v[7] = 1;
	
	vc->n = 0; 
	return vc;
}
//A partir daqui será usado o bitmap

//A Serelização será da forma, caractere, Código criptografado do caractere, # finalizando que acabou.
//Exemplo a100# (Vale lembrar que será salvo em binario.
/*
void serializacao (FILE *compactado, Arv* otima) {
	Arv* folhas = arv_folhas(otima, otima, folhas);
	int i = 0; int j = 0; int tam = 0; //tam é o tamanho do char completo, quando chegar a 8 indica que o char estará cheio
	char completo; int elem = 0;
	
	VCaminho *chap = vcaminho_inicializa(8);
	chap = vcaminho_escreve_chap(chap); //Testar como void
	
	bitmap bm = bitmapInit(8);	
	
	if(folhas != NULL) {//Faz o primeiro elemento da serialização
		fprintf(compactado, "%c", folhas->c);
		while (i < folhas->vc->n ){
				bitmapAppendLeastSignificantBit(&bm, folhas->vc->v[i]); //Adiciona o primeiro bit criptografado ao bitmap
				tam++;
				i++;
		}
	}
	
	if (tam == 8) { //Não compactou nada e estou continuando a serialização. Verificar em possibilidades para salvar o arquivo sem a serialização se a compactação não foi efetiva
		completo = bitmapGetContents(bm)[0];
		tam = 0;
		fprintf(compactado, "%c#", completo); // Talvez seja u e tenha que usar um unsigned char
	} else { //Precisará completar o char com um pedaço de # e em outro char terminar a #. # = 0x23
		//suponha tam = 3 
		
		while (tam < 8){
			bitmapAppendLeastSignificantBit(&bm, chap->v[j]);
			j++; 
			chap->n++;
			tam++;
		}
	}
	
	folhas = folhas->prox;
	
	//Agora bm estará cheio 
	//tam é a quantidade de bits que o bitmap possui
	
	while (folhas != NULL) {
	
	//	if (tam == 8) {
	//		completo = bitmapGetContents(bm)[0];
	//		tam = 0;
	//		fprintf(compactado, "%c#", completo); // Talvez seja u e tenha que usar um unsigned char
	//		folhas = folhas->prox;
			
		if (chap->n != 0) { //Então falta completar chap
			while (tam < 8 && chap->n < 8) {
				elem = chap->v[chap->n]; //Talvez chap->n seja isso -1. O mesmo se aplica a tam
				if (elem == 1) {
					bitmapSetBit(&bm, tam, 1);
				} else {
					bitmapSetBitZero4(&bm, tam);
				}
				
				tam++;
				chap->n++;
			}
		}
		
		if(chap->n == 0 ) { //Entao é folha (duvida) "to sem interrogacao"
			
			if (tam == 0) { //Entao o primeiro digito será um char de uma folha //!! Aparentemente comparação desnecessária
				fprintf(compactado, "%c#", folhas->c);
				
				while (i < folhas->vc->n ){ //Adiciona o primeiro bit criptografado ao bitmap. Certeza que todo o criptografado será pego.
					
					elem = bitmapGetBit(bm, folhas->vc->v[i]); //Talvez chap->n seja isso -1. O mesmo se aplica a tam
					if (elem == 1) {
						bitmapSetBit(&bm, tam, 1);
					} else {
						bitmapSetBitZero4(&bm, tam);
					}
					
					tam++;
				}
			} else { //Pode ser que não haja espaço para todo o criptografado
				
				while(tam < 8) {
					elem = pega_bit (folhas->c, tam);
					if (elem == 1) {
						bitmapSetBit(&bm, tam, 1);
					} else {
						bitmapSetBitZero4(&bm, tam);
					}
					tam++;
				}
			}
		}
		
		if (tam == 8) {
			completo = bitmapGetContents(bm)[0];
			tam = 0;
			fprintf(compactado, "%c#", completo); // Talvez seja u e tenha que usar um unsigned char
			folhas = folhas->prox;
		} else { //Precisará completar o char com um pedaço de # e em outro char terminar a #. # = 0x23
			//suponha tam = 3 
			j = 0;
			while (tam<8) {
				elem = chap->v[j];
				if (elem == 1) {
					bitmapSetBit(&bm, tam, 1);
				} else {
					bitmapSetBitZero4(&bm, tam);
				}
				j++;
				chap->n++;
				tam++;
			}
		}
		
		
	}
	
	j = chap->n;
	while (j > 0) {
		elem = chap->v[j];
		if (elem == 1) {
			bitmapSetBit(&bm, tam, 1);
		} else {
			bitmapSetBitZero4(&bm, tam);
		}
		j++;
		chap->n++;
	
	return; //ACABOOOOOOOOOOOOOOOOOU, ou não né, vai que dá mil falhas seg.
}*/
		/*
void serializacao_folhas (FILE *compactado, Arv* folhas) {
	//Arv* folhas = arv_folhas(otima, otima, folhas);

	int i = 0; int j = 0; int tam = 0; //tam é o tamanho do char completo, quando chegar a 8 indica que o char estará cheio
	char completo; int elem = 0;
	
	VCaminho *chap = vcaminho_inicializa(8);
	chap = vcaminho_escreve_chap(chap); //Testar como void
	
	bitmap bm = bitmapInit(8);	
	
	if(folhas != NULL) {//Faz o primeiro elemento da serialização
		fprintf(compactado, "%c", folhas->c);
		while (i < folhas->vc->n ){
				bitmapAppendLeastSignificantBit(&bm, folhas->vc->v[i]); //Adiciona o primeiro bit criptografado ao bitmap
				tam++;
				i++;
		}
	}
	
	if (tam == 8) { //Não compactou nada e estou continuando a serialização. Verificar em possibilidades para salvar o arquivo sem a serialização se a compactação não foi efetiva
		completo = bitmapGetContents(bm)[0];
		tam = 0;
		fprintf(compactado, "%c#", completo); // Talvez seja u e tenha que usar um unsigned char
	} else { //Precisará completar o char com um pedaço de # e em outro char terminar a #. # = 0x23
		//suponha tam = 3 
		
		while (tam < 8){
			bitmapAppendLeastSignificantBit(&bm, chap->v[j]);
			j++; 
			chap->n++;
			tam++;
		}
	}
	
	folhas = folhas->prox;
	
	//Agora bm estará cheio 
	//tam é a quantidade de bits que o bitmap possui
	
	while (folhas != NULL) {
	
	//	if (tam == 8) {
	//		completo = bitmapGetContents(bm)[0];
	//		tam = 0;
	//		fprintf(compactado, "%c#", completo); // Talvez seja u e tenha que usar um unsigned char
	//		folhas = folhas->prox;
			
		if (chap->n != 0) { //Então falta completar chap
			while (tam < 8 && chap->n < 8) {
				elem = chap->v[chap->n]; //Talvez chap->n seja isso -1. O mesmo se aplica a tam
				if (elem == 1) {
					bitmapSetBit(&bm, tam, 1);
				} else {
					bitmapSetBitZero4(&bm, tam);
				}
				
				tam++;
				chap->n++;
			}
		}
		
		if(chap->n == 0 ) { //Entao é folha (duvida) "to sem interrogacao"
			
			if (tam == 0) { //Entao o primeiro digito será um char de uma folha //!! Aparentemente comparação desnecessária
				fprintf(compactado, "%c#", folhas->c);
				
				while (i < folhas->vc->n ){ //Adiciona o primeiro bit criptografado ao bitmap. Certeza que todo o criptografado será pego.
					
					elem = bitmapGetBit(bm, folhas->vc->v[i]); //Talvez chap->n seja isso -1. O mesmo se aplica a tam
					if (elem == 1) {
						bitmapSetBit(&bm, tam, 1);
					} else {
						bitmapSetBitZero4(&bm, tam);
					}
					
					tam++;
				}
			} else { //Pode ser que não haja espaço para todo o criptografado
				
				while(tam < 8) {
					elem = pega_bit (folhas->c, tam);
					if (elem == 1) {
						bitmapSetBit(&bm, tam, 1);
					} else {
						bitmapSetBitZero4(&bm, tam);
					}
					tam++;
				}
			}
		}
		
		if (tam == 8) {
			completo = bitmapGetContents(bm)[0];
			tam = 0;
			fprintf(compactado, "%c#", completo); // Talvez seja u e tenha que usar um unsigned char
			folhas = folhas->prox;
		} else { //Precisará completar o char com um pedaço de # e em outro char terminar a #. # = 0x23
			//suponha tam = 3 
			j = 0;
			while (tam<8) {
				elem = chap->v[j];
				if (elem == 1) {
					bitmapSetBit(&bm, tam, 1);
				} else {
					bitmapSetBitZero4(&bm, tam);
				}
				j++;
				chap->n++;
				tam++;
			}
		}
		
		
	}
	
//	j = chap->n;
//	while (j > 0) {
//		elem = chap->v[j];
//		if (elem == 1) {
//			bitmapSetBit(&bm, tam, 1);
//		} else {
//			bitmapSetBitZero4(&bm, tam);
//		}
//		j++;
//		chap->n++;
	
	return; //ACABOOOOOOOOOOOOOOOOOU, ou não né, vai que dá mil falhas seg.
}

void bitmap_setbit2 (bitmap *bm, int posicao, unsigned int bit) {

	if (bit == 1) {
		bitmapSetBit(&bm, tam, 1);
		return;
	}
		
	bitmapSetBitZero4(&bm, tam);
	return;
}*/


/*
void serializacao_folhas2 (FILE *compactado, Arv* folhas) {
	//Arv* folhas = arv_folhas(otima, otima, folhas);

	int i = 0; int j = 0; int tam = 0; //tam é o tamanho do char completo, quando chegar a 8 indica que o char estará cheio
	char completo; int elem = 0;
	
	VCaminho *chap = vcaminho_inicializa(8);
	chap = vcaminho_escreve_chap(chap); //Testar como void
	
	bitmap bm = bitmapInit(8);	
	
	if(folhas != NULL) {//Faz o primeiro elemento da serialização
		fprintf(compactado, "%c", folhas->c);
		while (i < folhas->vc->n ){
				bitmapAppendLeastSignificantBit(&bm, folhas->vc->v[i]); //Adiciona o primeiro bit criptografado ao bitmap
				tam++;
				i++;
		}
	}
	
	if (tam == 8) { //Não compactou nada e estou continuando a serialização. Verificar em possibilidades para salvar o arquivo sem a serialização se a compactação não foi efetiva
		completo = bitmapGetContents(bm)[0];
		tam = 0;
		fprintf(compactado, "%c#", completo); // Talvez seja u e tenha que usar um unsigned char
	} else { //Precisará completar o char com um pedaço de # e em outro char terminar a #. # = 0x23
		//suponha tam = 3 
		
		while (tam < 8){
			bitmapAppendLeastSignificantBit(&bm, chap->v[j]);
			j++; 
			chap->n++;
			tam++;
		}
	}
	
	folhas = folhas->prox;
	
	//Agora bm estará cheio 
	//tam é a quantidade de bits que o bitmap possui
	
	while (folhas != NULL) {
	
		if (tam == 8) {
			completo = bitmapGetContents(bm)[0];
			tam = 0;
			fprintf(compactado, "%c", completo); // Talvez seja u e tenha que usar um unsigned char
	//		folhas = folhas->prox;
	}
			
		if (chap->n != 0) { //Então falta completar chap
			while (tam < 8 && chap->n < 8) {
				elem = chap->v[chap->n]; //Talvez chap->n seja isso -1. O mesmo se aplica a tam
				if (elem == 1) {
					bitmapSetBit(&bm, tam, 1);
				} else {
					bitmapSetBitZero4(&bm, tam);
				}
				
				tam++;
				chap->n++;
			}
		} 
 
		if(chap->n == 8) { //Pode ser desnecessário
			chap->n = 0;
		}
		
		if(chap->n == 0 ) { //Entao é folha (duvida) "to sem interrogacao"
			
			if (tam == 0) { //Entao o primeiro digito será um char de uma folha //!! Aparentemente comparação desnecessária
				fprintf(compactado, "%c#", folhas->c);
				
				while (i < folhas->vc->n ){ //Adiciona o primeiro bit criptografado ao bitmap. Certeza que todo o criptografado será pego.
					
					elem = bitmapGetBit(bm, folhas->vc->v[i]); //Talvez chap->n seja isso -1. O mesmo se aplica a tam
					bitmap_setbit2 (&bm, tam, elem);
					tam++;
					i++;
				}
			}
		} else { //Pode ser que não haja espaço para todo o criptografado
			j = 0;	
			while(tam < 8) {
				elem = pega_bit (folhas->c, j);
				bitmap_setbit2 (bm, tam, elem);
				
				tam++;
				j++;
			}
		}
	
		
		if (tam == 8) {
			completo = bitmapGetContents(bm)[0];
			tam = 0;
			fprintf(compactado, "%c", completo); // Talvez seja u e tenha que usar um unsigned char
		//	folhas = folhas->prox;
		}  //Precisará completar o char com um pedaço de # e em outro char terminar a #. # = 0x23
			//suponha tam = 3 
			if(chap->n != 0) { //Falta completar a chap
			j = 0;
			while (tam<8) {

				elem = chap->v[j];
				bitmap_setbit2 (&bm, tam, elem);
				j++;
				chap->n++;
				tam++;
			} 
			if (chap->n == 8){//Acho que isso é desnecessário
				chap->n = 0;
			}
			} else { //Falta completar um caracter

			while (tam<8) {
				elem = pega_bit (folhas->c, tam);
				bitmap_setbit2 (&bm, tam, elem);
				tam++;

			}

			folhas = folhas->prox;
		}

		
		
	}
	
//	j = chap->n;
//	while (j > 0) {
//		elem = chap->v[j];
//		if (elem == 1) {
//			bitmapSetBit(&bm, tam, 1);
//		} else {
//			bitmapSetBitZero4(&bm, tam);
//		}
//		j++;
//		chap->n++;
	
	return; //ACABOOOOOOOOOOOOOOOOOU, ou não né, vai que dá mil falhas seg.
}
// compacta (Arv* otima){
*/


/*
//NECESSÁRIO QUE FOLHAS NAO TENHA DUPLICADOS
void serelizacao2_folhas (FILE* compactado, Arv* folhas) {
	unsigned char   criptografado = 0, //Servirá para verificar se todos os bits criptografados do caracter foram salvos
			caracter = 0;
	int tam = 0; //Servirá para verificar se todo o bitmap foi utilizado.
	int i = 0, j = 0; //Servirão de suporte para loops.
	
	
	VCaminho *chap = vcaminho_inicializa(8);
	chap = vcaminho_escreve_chap(chap);


	if(folhas != NULL) {//Faz o primeiro elemento da serialização
		fprintf(compactado, "%c", folhas->c);
		while (i < folhas->vc->n ){
				bitmapAppendLeastSignificantBit(&bm, folhas->vc->v[i]); //Adiciona o primeiro bit criptografado ao bitmap
				tam++;
				i++;
		}
	}
	
	if (tam == 8) { //Não compactou nada e estou continuando a serialização. Verificar em possibilidades para salvar o arquivo sem a serialização se a compactação não foi efetiva
		completo = bitmapGetContents(bm)[0];
		tam = 0;
		fprintf(compactado, "%c#", completo); // Talvez seja u e tenha que usar um unsigned char
	} else { //Precisará completar o compactado com um pedaço de # e em outro char terminar a #. # = 0x23
		
		while (tam < 8){
			bitmapAppendLeastSignificantBit(&bm, chap->v[j]);
			j++; 
			chap->n++;
			tam++;
		}
	}
	
	folhas = folhas->prox;


	while (folhas != NULL) {
	
		if(chap->n !=0) {
			while (tam < 8 && chap->n < 8) {
				elem = chap->v[chap->n]; //Talvez chap->n seja isso -1. O mesmo se aplica a tam
				if (elem == 1) {
					bitmapSetBit(&bm, tam, 1);
				} else {
					bitmapSetBitZero4(&bm, tam);
				}
				
				tam++;
				chap->n++;
			}
		} 


*/

VCaminho* percorre (Arv* a, VCaminho *vc) {
	
	if (a == NULL) {
		return vc;
	}
	
	if (a->esq != NULL) { //não-folhas
		vc->v[vc->n] = 0;
		vc->n++;
		percorre (a->esq, vc);
	}

	if(a->dir != NULL) {
		vc->v[vc->n] = 1;
		vc->n++;
		percorre (a->dir, vc);
	}
	
	if (a->esq == NULL && a->dir == NULL) {
		vc->v[vc->n] = a->c;
		vc->n++;
	}

	return vc;
}
	
int arv_tam (Arv *a) { //Nao leva a raiz em consideraçao.
	
	if (a == NULL) {
		return -1;
	}
	
	int i = 1 + arv_tam(a->esq);
	int j = 1 + arv_tam(a->dir);
	return i+j;
}


/*

void serializacao (FILE *fp, Arv *otima) {
	int tam = 0; //tam é o tamanho do char completo, quando chegar a 8 indica que o char estará cheio
	int tam_caminho = 0;
	Arv* percorre = NULL;
	
	tam_caminho = arv_tam (otima) + arv_qtd_folhas(a) + 1; //+1 porque o tamanho da arvore ótima não considera a raiz.
	
	if(tam != 1) { //TESTAR SE FOR 1
		VCaminho *vcam_serelizado = vcaminho_inicializa(tam_caminho);
		vcam_serelizado->v[0] = 0;
		vcam_serelizado->n++;
	} // falta escrever o else
	
	VCaminho *vcam_serializacao = arv_tam (otima) + arv_qtd_folhas (a) + 1; //+1 porque o tamanho da arvore ótima não considera a raiz.
	if(



*/


