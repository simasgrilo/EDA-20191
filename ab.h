
#include"arvg.h"
typedef struct fig{
	int id;//, idPai;
	char nome[3];
	float dim1, dim2, dim3;
}TFig;

typedef struct ArvB{
  int nchaves, folha; 
  TFig **figs;
  struct ArvB **filho;
}TAB;
extern TAB *criaAB(int t);
extern TAB* retiraAB(TAB *a, int id);
extern TAB *liberaAB(TAB *a);
extern void imprimeAB(TAB *a, int andar);
extern TAB *buscaAB(TAB* x, int ch);
extern TAB *inicializa(void);
extern TAB *divisao(TAB *x, int i, TAB* y, int t);
extern TAB *insere_nao_completo(TAB *x, int id, char *nome, float dim1, float dim2, float dim3, int t);
extern TAB *insereAB(TAB *T, int id, char *nome, float dim1, float dim2, float dim3, int t);
extern TAB * g2AB (TAG *a, TFig **vetArvore, TAB *b,int t);
extern int conta(TAG*a); //jogando o vetArvore p fora da função geradora
void liberaVetFig(TFig **vet, int n);
//extern TAB* remover(TAB* arv, int ch, int t);

