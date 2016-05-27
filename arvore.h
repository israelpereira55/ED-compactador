#ifndef ARV_H
#define ARV_H

typedef struct arv Arv;

Arv* arv_inicializa_unica(char c);

Arv* arv_inicializa(char c, Arv* esq, Arv* dir);

Arv* arv_pai (Arv* a, char c);
	
int arv_pertence (Arv* a, char c);

Arv* arv_retira (Arv* a, char c);

Arv* arv_busca(Arv* a, char c);

Arv* arv_libera(Arv* a);

char info (Arv* a);

#endif 
