/*
*********************************
* Programa testador do TAD Arvore
*********************************
*/
#include <stdio.h>
#include "arvore.h"

int main()
{
      //cria uma árvore para teste
       Arv* a = arv_inicializa('a',
		    arv_inicializa('b',
			 NULL,
			 arv_inicializa('d', NULL, NULL)
		    ),
		    arv_inicializa('c',
			arv_inicializa('e', NULL, NULL),
			arv_inicializa('f', NULL, NULL)
		    )
	);

	/*
//     arv_imprime(a);
     
     // Verificia se o caracter 'b' pertence a arvore
     int pertence = arv_pertence (a, 'b');
     printf ("Caracter b pertence?: %d\n", pertence);	
      

    // Verificia se o caracter 'z' pertence a arvore
     pertence = arv_pertence (a, 'z');
     printf ("Caracter z pertence?: %d\n", pertence);	


     //retorna o pai do nó c (deve ser 'a')
     Arv* pai = arv_pai (a, 'c');
     printf ("Pai do no c: %c \n", info(pai));
     
//     Arv* retirada = arv_retira(a, 'b');
//     printf ("Retirada: %c \n", info(retirada));
     
     Arv* retirada2 = arv_retira(a, 'f');
     printf ("Retirada: %c \n", info(retirada2));
     
     Arv* retirada3 = arv_retira(a, 'd');
     printf ("Retirada: %c \n", info(retirada3));
*/
     // retorna o numero de folhas da arvore (3)
//     int f = folhas(a);
 //    printf ("Numero de folhas da arvore: %d \n", f);

     // retorna o numero de ocorrencias de 'f' (1 vez) 
 //    int i = ocorrencias (a, 'f');
//     printf ("Numero de ocorrencias de f: %d \n", i);

//	Arv* folhas1 = arv_inicializa_unica( 'a');
/*	Arv* folhas2 =arv_inicializa_unica('b');
	Arv* folhas3 = arv_inicializa_unica('c');
	Arv* folhas4 = arv_inicializa_unica( 'd');
	Arv* folhas5 = arv_inicializa_unica( 'e');
	Arv* folhas6 = arv_inicializa_unica('f');
	Arv *lista = NULL;
	lista = arv_insere (lista,  folhas1);
	lista = arv_insere (lista, folhas2);
	lista = arv_insere (lista, folhas3);
	lista = arv_insere (lista, folhas4);
lista =	arv_insere (lista,  folhas5);
	lista = arv_insere (lista, folhas6);
	*/
//	arv_imprime_lista (lista);
//	Arv* folhas = NULL;
//	folhas = arv_folhas (a, a, folhas);
/*	arv_imprime_lista (folhas);
	
	VCaminho *cam = arv_retorna_vcaminho(folhas);
	vcaminho_imprime(cam);
	
	printf("\n\n");
	
	folhas = arv_prox (folhas);
	cam = arv_retorna_vcaminho(folhas);
	vcaminho_imprime(cam);
	
	printf("\n\n");
	
	folhas = arv_prox (folhas);
	cam = arv_retorna_vcaminho(folhas);
	vcaminho_imprime(cam);*/
	
//	FILE *fp = fopen("comp.comp", "w");
	
	//serializacao_folhas (fp, folhas);
	
	int x = arv_tam (a);
	printf("aaaaaa  %d\n\n", x);
	
	VCaminho *vc = vcaminho_inicializa(9);
	
	percorre (a, vc);
	vcaminho_imprime(vc);
	
	return 0;
	
	

 //    arv_libera (a);

}
