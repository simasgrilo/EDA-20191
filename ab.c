#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include"ab.h"
#include "arvg.h"

TAB *criaAB(int t){
  TAB* novo = (TAB*)malloc(sizeof(TAB));
  novo->nchaves = 0;
  novo->figs =(TFig**)malloc(sizeof(TFig*)*((t*2)-1));
  novo->folha=1;
  novo->filho = (TAB**)malloc(sizeof(TAB*)*t*2);
  novo->t = t;
  int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  //for(i=0; i < t; i++) novo -> figs[i] = NULL; //isso provoca segfault na inserção
  return novo;
}


TAB *liberaAB(TAB *a){
  if(a){
	int i;
    if(!a->folha){     
      for(i = 0; i <= a->nchaves; i++) liberaAB(a->filho[i]);
    }	
	for(i = 0; i < ((a->t*2)-1); i++) if(a -> figs[i]){
		free(a -> figs[i]); //isso quebra em qqr situação
		printf("passou %d",i);
	}
	//liberaVetFig(a->figs,a->t);
    free(a->figs);
    free(a->filho);
    free(a);
    return NULL;
  }
}


void imprimeAB(TAB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      imprimeAB(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("{ cód:%d, figura:%s }\n",a->figs[i] ->id, a-> figs[i] -> nome);
    }
    imprimeAB(a->filho[i],andar+1);
  }
}


TAB *buscaAB(TAB* x, int ch){
  TAB *resp = NULL;
  if(!x) return resp;
  int i = 0;
  while(i < x->nchaves && ch > x->figs[i]->id) i++;
  if(i < x->nchaves && ch == x->figs[i]->id) return x;
  if(x->folha) return resp;
  return buscaAB(x->filho[i], ch);
}


TAB *inicializa(){
  return NULL;
}


TAB *divisao(TAB *x, int i, TAB* y, int t){
  TAB *z=criaAB(t);
  z->nchaves= t - 1;
  z->folha = y->folha;
  int j;
  for(j=0;j<t-1;j++) if(y->figs[j+t]) z->figs[j] = y->figs[j+t];
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) if (x->figs[j-1]) x->figs[j] = x->figs[j-1];
  x->figs[i-1] = y->figs[t-1];
  x->nchaves++;
  return x;
}


TAB *insere_nao_completo(TAB *x, int id, char *nome, float dim1, float dim2, float dim3, int t){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (x->figs[i]) && (id < x->figs[i] ->id)){
      x->figs[i+1] = x->figs[i] ;
      i--;
    }
	TFig * novo = (TFig*)malloc(sizeof(TFig));
	novo -> id = id;
	strcpy(novo -> nome, nome);
	if(dim1) novo -> dim1 = dim1;
	if(dim2) novo -> dim2 = dim2;
	if(dim3) novo -> dim3 = dim3;
    x->figs[i+1] = novo;
    x->nchaves++;
    return x;
  }
  while((i>=0) && (x->figs[i]) && (id <x->figs[i] -> id)) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = divisao(x, (i+1), x->filho[i], t);
    if(((x->figs[i])) && (id >x->figs[i] -> id)) i++;
  }
  x->filho[i] = insere_nao_completo(x->filho[i],id, nome, dim1, dim2, dim3, t);
  return x;
}


TAB *insereAB(TAB *T, int id, char *nome, float dim1, float dim2, float dim3, int t){
  if(buscaAB(T,id)) return T;
  if(!T){
	//printf("rosquinha\n");
    T=criaAB(t);
    T->figs[0] -> id = id;
	strcpy(T->figs[0] -> nome, nome);
	if(dim1) T->figs[0]-> dim1 = dim1;
	if(dim2) T->figs[0] -> dim2 = dim2;
	if(dim3) T->figs[0] -> dim3 = dim3;
    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){
	//printf("red\n");
    TAB *S = criaAB(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = divisao(S,1,T,t);
    S = insere_nao_completo(S,id, nome, dim1, dim2, dim3,t);
    return S;
  }
	//printf("corvette\n");
  T = insere_nao_completo(T,id, nome, dim1, dim2, dim3,t);
  return T;
}


/*TAB* remover(TAB* arv, int ch, int t){
  if(!arv) return arv;
  int i;
  printf("Removendo %d...\n", ch);
  for(i = 0; i<arv->nchaves && arv->chave[i] < ch; i++);
  if(i < arv->nchaves && ch == arv->chave[i]){ //CASOS 1, 2A, 2B e 2C
    if(arv->folha){ //CASO 1
      printf("\nCASO 1\n");
      int j;
      for(j=i; j<arv->nchaves-1;j++) arv->chave[j] = arv->chave[j+1];
      arv->nchaves--;
      return arv;      
    }
    if(!arv->folha && arv->filho[i]->nchaves >= t){ //CASO 2A
      printf("\nCASO 2A\n");
      TAB *y = arv->filho[i];  //Encontrar o predecessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[y->nchaves];
      int temp = y->chave[y->nchaves-1];
      arv->filho[i] = remover(arv->filho[i], temp, t); 
      //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves >= t){ //CASO 2B
      printf("\nCASO 2B\n");
      TAB *y = arv->filho[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[0];
      int temp = y->chave[0];
      y = remover(arv->filho[i+1], temp, t); //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves == t-1 && arv->filho[i]->nchaves == t-1){ //CASO 2C
      printf("\nCASO 2C\n");
      TAB *y = arv->filho[i];
      TAB *z = arv->filho[i+1];
      y->chave[y->nchaves] = ch;          //colocar ch ao final de filho[i]
      int j;
      for(j=0; j<t-1; j++)                //juntar chave[i+1] com chave[i]
        y->chave[t+j] = z->chave[j];
      for(j=0; j<=t; j++)                 //juntar filho[i+1] com filho[i]
        y->filho[t+j] = z->filho[j];
      y->nchaves = 2*t-1;
      for(j=i; j < arv->nchaves-1; j++)   //remover ch de arv
        arv->chave[j] = arv->chave[j+1];
      for(j=i+1; j <= arv->nchaves; j++)  //remover ponteiro para filho[i+1]
        arv->filho[j] = arv->filho[j+1];
      arv->filho[j] = NULL; //Campello
      arv->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;   
    }   
  }

  TAB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ //CASOS 3A e 3B
    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i menor que nchaves\n");
      z = arv->filho[i+1];
      y->chave[t-1] = arv->chave[i];   //dar a y a chave i da arv
      y->nchaves++;
      arv->chave[i] = z->chave[0];     //dar a arv uma chave de z
      int j;
      for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
        z->chave[j] = z->chave[j+1];
      //z->chave[j] = 0; Rosseti
      y->filho[y->nchaves] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
      for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
        z->filho[j] = z->filho[j+1];
      z->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;
    }
    if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i igual a nchaves\n");
      z = arv->filho[i-1];
      int j;
      for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
        y->chave[j] = y->chave[j-1];
      for(j = y->nchaves+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
        y->filho[j] = y->filho[j-1];
      y->chave[0] = arv->chave[i-1];              //dar a y a chave i da arv
      y->nchaves++;
      arv->chave[i-1] = z->chave[z->nchaves-1];   //dar a arv uma chave de z
      y->filho[0] = z->filho[z->nchaves];         //enviar ponteiro de z para o novo elemento em y
      z->nchaves--;
      arv->filho[i] = remover(y, ch, t);
      return arv;
    }
    if(!z){ //CASO 3B
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == t-1){
        printf("\nCASO 3B: i menor que nchaves\n");
        z = arv->filho[i+1];
        y->chave[t-1] = arv->chave[i];     //pegar chave [i] e coloca ao final de filho[i]
        y->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          y->chave[t+j] = z->chave[j];     //passar filho[i+1] para filho[i]
          y->nchaves++;
        }
        if(!y->folha){
          for(j=0; j<t; j++){
            y->filho[t+j] = z->filho[j];
          }
        }
        for(j=i; j < arv->nchaves-1; j++){ //limpar referências de i
          arv->chave[j] = arv->chave[j+1];
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->nchaves--;
        arv = remover(arv, ch, t);
        return arv;
      }
      if((i > 0) && (arv->filho[i-1]->nchaves == t-1)){ 
        printf("\nCASO 3B: i igual a nchaves\n");
        z = arv->filho[i-1];
        if(i == arv->nchaves)
          z->chave[t-1] = arv->chave[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
        else
          z->chave[t-1] = arv->chave[i];   //pegar chave [i] e poe ao final de filho[i-1]
        z->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          z->chave[t+j] = y->chave[j];     //passar filho[i+1] para filho[i]
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0; j<t; j++){
            z->filho[t+j] = y->filho[j];
          }
        }
        arv->nchaves--;
        arv->filho[i-1] = z;
        arv = remover(arv, ch, t);
        return arv;
      }
    }
  }  
  arv->filho[i] = remover(arv->filho[i], ch, t);
  return arv;
}


TAB* retira(TAB* arv, int k, int t){
  if(!arv || !busca(arv, k)) return arv;
  return remover(arv, k, t);
}*/

//ideia: transformo da arvore pro vetor, ordeno e do vetor p arvore, a arvore resultante fica mais balanceada assim. Basicamente o mesmo que foi implementado p árvore de busca binária

/*int conta(TAG*a){
	if(!a)
		return 0;
	else
	{
		int resp = 1;
		if (a->prim_filho)
			resp += conta(a->prim_filho);
		if (a->prox_irmao)
			resp += conta(a->prox_irmao);
		return resp;
	}
}*/

void addVetorAB(TAG *a, TFig**vetor, int i){
	if(!a || !vetor)return;
	while(vetor[i]) i++;
	TFig * novo = (TFig*)malloc(sizeof(TFig));
	novo -> id = a-> id;
	strcpy(novo -> nome, a -> nomeFigura);
	if(a -> dim1) novo -> dim1 = a -> dim1;
	if(a -> dim2) novo -> dim2 = a -> dim2;
	if(a -> dim3) novo -> dim3 = a -> dim3;
	vetor[i] = novo;
	if(a->prim_filho)
		addVetorAB(a -> prim_filho,vetor,i);
	if(a -> prox_irmao)
		addVetorAB(a -> prox_irmao,vetor,i);

}

void ordenaAB(TFig **vet, int n){
	if(!vet) return;
	int i = 0;
	for(i; i < n; i++){
		int j, menor = i;		
		for(j = i + 1; j < n; j++){
			if(vet[j] -> id < vet[menor] -> id) menor = j; 
		}
		if(menor != i){
			TFig *temp = vet[menor];
			vet[menor] = vet[i];
			vet[i] = temp;
		}
	}
}

TAB * v2ab (TFig **vet, int n,int t){
	if(n > 0){
		int i = 0;
		TAB * resp = NULL;
		for(i; i < n; i++)
			resp = insereAB(resp,vet[i] -> id, vet[i] -> nome, vet[i] -> dim1, vet[i] -> dim2,vet[i] -> dim3,t);
		return resp;
	}
	return NULL;
}

TAB * g2AB (TAG *a, TFig **vetArvore, TAB *b,int t){
	if(!a)
		return NULL;
	//versão 1: nao retiro da árvore original.
	int qteElem = conta(a);
	if(!b)
		b = criaAB(t);
	//TAG ** vetArvore = (TAG**)malloc(sizeof(TAG*) * qteElem); parametrizar esse cara p facilitar o free. replicar o mesmo p arvg.c
	int i = 0;
	for(i; i < qteElem; i++){
		vetArvore[i] = NULL;
	}
	addVetorAB(a,vetArvore,0);
	ordenaAB(vetArvore,qteElem);
	return v2ab(vetArvore,qteElem,t);
}

void liberaVetFig(TFig **vet, int n){
	int i;
	for(i = 0; i < n; i++){
		if(vet[i])free(vet[i]);
	}
	free(vet);
}




