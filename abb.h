
#ifndef ABB_HEADER_GUARD
#define ABB_HEADER_GUARD
#include <stdlib.h>
#include <math.h>

typedef struct abb
{
	char nomeFigura[3];
	int id;
	float dim1, dim2, dim3;
	struct abb *esq, *dir;
} TABB;
extern TABB *criaABB(void);
extern TABB *buscaABB(TABB *a, int idPai);
extern TABB *insereABB(TABB *a, int id, char *nome, float dim1, float dim2, float dim3);
extern void imprimeABB(TABB *a);
//extern void imprimeFigura(TABB *a);
//extern TABB *retira(TABB *a, int id);
extern void liberaABB(TABB *a);

#endif
