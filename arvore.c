struct arv {
	char c;
	Arv* esq,
	     dir;
};

Arv* arv_inicializa_unica(char c) {
	
	Arv* a = (Arv*) malloc (sizeof(Arv));
	a->esq = NULL;
	a->dir = NULL;
	a->c = c;
	return a;
}

Arv* arv_inicializa(Arv* esq, Arv* dir) {
	
	Arv* a = (Arv*) malloc (sizeof(Arv));
	a->esq = esq;
	a->dir = dir;
	return a;
}

Arv* arv_retorna_pai (Arv* a, char c) {

	if ( !arv_pertence(a, c) ) {
		return ;
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

	Arv* teste = arv_retorna_pai(a->esq, c);

	if (teste != NULL) {
		return teste;
	}

	return arv_retorna_pai(a->dir);
}
Arv* arv_pertence (Arv* a, char c) {
	
	if(a == NULL) {
		return 0;
	}

	if (a->c == c) {
		return 1;
	}

	return arv_pertence(a->esq) || arv_pertence(a->dir);
}

Arv* arv_retira (Arv* a, char c) {
	
	if( !arv_pertence(a, c) ) {
		return NULL;
	}

	Arv *pai = arv_retorna_pai(a, c);

	if (pai->esq->c == c) {
		Arv* filho = pai->esq;
		pai->esq = NULL;
		return filho;
	}

	Arv* filho = pai->dir;
	pai->dir = NULL;
	return filho;
}

Arv* arv_busca(Arv* a, char c) {

	if (a == NULL) {
		return NULL;
	}

	if(a->c == c) {
		return a;
	}

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
