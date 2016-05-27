struct arv {
//aaa
	Arv* esq,
	     dir;
};

Arv* arv_inicializa() {
	
	Arv* a = (Arv*) malloc (sizeof(Arv));
	a->esq = NULL;
	a->dir = NULL;
	return a;
}

Arv* arv_libera(Arv* a) {
	
	if (a == NULL) {
		return NULL;
	}

	if (a->esq != NULL) {
		arv_libera(a->esq);
	}

	if(a->dir != NULL) {
		arv_libera(a->dir);
	}

	free(a);
	return NULL;
}

		
