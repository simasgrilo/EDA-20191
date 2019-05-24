
#include<stdlib.h>
#include<math.h>

typedef struct arvk {
	char nomeFigura[3];
	int id;
	float dim1, dim2, dim3;
	struct arvk** filhos; //abordagem 1: cada nó tem um array de ponteiros como filho. Se achar algo melhor..
}TAK;
extern TAK* cria (void);
extern TAK *busca (TAK*a, int idPai);
extern TAK *insere(TAK* ak, int id, int idPai, char* nome, float dim1, float dim2, float dim3);
extern void imprime(TAK *a, int cont);
/*TAK *modificaNome(TAK *a, char *nome);
TAK *modificaUmaDim(TAK *a, float dim1);
TAK *modificaDuasDim(TAK *a, float dim1,float dim2);
TAK *modificaUmaDim(TAK *a, float dim1, float dim2, float dim3); */
