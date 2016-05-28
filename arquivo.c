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
	char valor_asc = fgetc(fp);

	int *v = vet_inicializa();

	while (valor_asc != EOF) {
		v[valor_asc]++; //Mesmo declarado como char, o conteudo que "valor_asc" carrega também é inteiro. Assim o acesso no vetor funciona da mesma forma que uma variavel declarada como int.
		valor_asc = fgetc(fp);
	}
	
	fclose(fp);
	
	return v;
}

void vet_imprime(int *v) {
	int i, j;

	for(i=0, j= 0; i < 256; i++, j++) {
		printf("%d ", v[i]);

		if (j%20 == 0) {
			printf("\n");
		}
	}

	return;
}
