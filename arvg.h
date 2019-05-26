#ifndef ARVG_HEADER_GUARD
#define ARVG_HEADER_GUARD
#include <stdlib.h>
#include <math.h>

typedef struct arvg
{
	char nomeFigura[3];
	int id, idPai;
	float dim1, dim2, dim3;
	struct arvg *prim_filho, *prox_irmao;
} TAG;
extern TAG *cria(void);
extern TAG *busca(TAG *a, int id);
extern TAG *insere(TAG *a, int id, int idPai, char *nome, float dim1, float dim2, float dim3);
extern void imprime(TAG *a, int altura);
extern void imprimeFigura(TAG *a);
extern TAG *ler_de_arquivo(char *nome1, TAG *a);
extern TAG *retira(TAG *a, int id);
extern void libera(TAG *a);
/*TAK *modificaNome(TAG *a, char *nome);a
TAK *modificaUmaDim(TAG *a, float dim1);
TAK *modificaDuasDim(TAG *a, float dim1,float dim2);
TAK *modificaUmaDim(TAG *a, float dim1, float dim2, float dim3); */

#endif
