#ifndef ARV_H
#define ARV_H

typedef struct arv Arv;

typedef struct vet_caminho VCaminho; //Ficará aqui apenas para teste

Arv* arv_inicializa_unica(char c);

Arv* arv_inicializa(char c, Arv* esq, Arv* dir);

Arv* arv_inicializa_huffman(int i, Arv* esq, Arv* dir);
	
int arv_pertence (Arv* a, char c);

Arv* arv_pai (Arv* a, char c);

Arv* arv_retira (Arv* a, char c);

Arv* arv_busca(Arv* a, char c);

Arv* arv_libera(Arv* a);

char info (Arv* a);

Arv* arv_troca(Arv* a);

Arv* arv_ordena(Arv* a);

Arv* arv_insere (Arv* original, Arv* adicional);

Arv* arv_huffman (Arv* lista);

Arv* arv_cria_lista_frequencia (int* freq);

void arv_imprime_lista (Arv* lista);

int arv_elem_profundidade(Arv* a, char c);

VCaminho* vcaminho_inicializa(int profundidade); //Ficará aqui apenas para teste

VCaminho* vcaminho_retorna_caminho(Arv *a, char c); //Ficará aqui apenas para teste

void vcaminho_imprime(VCaminho *vc); //Ficará aqui apenas para teste

Arv* arv_folhas (Arv* original, Arv* percorre, Arv* folhas);

VCaminho* arv_retorna_vcaminho(Arv* a); // So para teste, provavelmente

Arv* arv_prox (Arv *a); //Absolutamente só para testes

VCaminho* vcaminho_escreve_chap (VCaminho *vc);

void serializacao (FILE *compactado, Arv* otima);

void serializacao_folhas (FILE *compactado, Arv* folhas);

int arv_tam (Arv *a);

VCaminho* percorre (Arv* a, VCaminho *vc);

#endif 
