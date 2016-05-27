#include <stdio.h>
#include <stdlib.h>

int* vet_inicializa() {

	int *v = (int*) malloc (256*sizeof(int));
	int i;

	for(i = 0; i < 256; i++) {
		v[i] = 0;
	}

	return v;
}

int* arquivo_frequencia(char *nome) {

	FILE* fp = (FILE*) fopen (nome, "r");
	char c = fgetc(fp);

	int *v = vet_inicializa();
	int valor_asc = -1;

	while (c != EOF) { //Testar se o acesso no vetor usando o indice c funciona.
		valor_asc = c;
		v[valor_asc]++;
		c = fgetc(c);
	}

	return v;
}
