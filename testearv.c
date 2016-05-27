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

     // retorna o numero de folhas da arvore (3)
//     int f = folhas(a);
 //    printf ("Numero de folhas da arvore: %d \n", f);

     // retorna o numero de ocorrencias de 'f' (1 vez) 
 //    int i = ocorrencias (a, 'f');
//     printf ("Numero de ocorrencias de f: %d \n", i);

     arv_libera (a);

}
