#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>

#include"arvk.h"

#define tam_filhos 4

/*estrutura de árvore
typedef struct arvk {
	char[3] nomeFigura;
	int dim1, int dim2, int dim3, int id;
	struct arvk** filhos; //abordagem 1: cada nó tem um array de ponteiros como filho. Se achar algo melhor..
}TAK;*/

TAK* cria (void){ //(int qteFilhos){ pensei em parametrizar mas ia ficar uma bosta
	TAK *novo = (TAK*)malloc(sizeof(TAK));
	novo -> filhos = (TAK**) malloc(sizeof(TAK*) *tam_filhos);
	int i ;
	for (i = 0; i < tam_filhos; i++) novo -> filhos[i] = NULL;
	return novo;
}


TAK *busca (TAK*a, int idPai){
	if(!a) return NULL;
	if(a -> id == idPai) return a;
	int i;
	TAK *resp = NULL;
	for(i = 0; i < tam_filhos; i++) resp = busca(a->filhos[i],idPai);
	return resp;

}

TAK *insere(TAK* a, int id, int idPai, char* nome, float dim1, float dim2, float dim3){//C acho que nao deixa parametro opcional, se nao tiver o terceiro apenas cagar p isso na main.
	if(!a){
		TAK *novo = cria();
		strcpy(novo -> nomeFigura,nome);
		novo -> id = id;
		//abordagem mais preguiçosa: verificar se o dado foi efetivamente passado como parâmetro. caso contrario, cravar na função que chamar a insere como 0.
		if (dim1) novo -> dim1 = dim1;
		if (dim2) novo -> dim2 = dim2;
		if (dim3) novo -> dim3 = dim3;
		return novo;		
	}
	//verifico se já existe algúem com meu código único
	TAK * no = busca(a,id);
	if(no){
		printf("Já existe um elemento na árvore com código %d! \n",id);
		return a;
	}
	//se não for o caso, buscar o pai do nó que será inserido
	TAK *pai = busca(a, idPai);
	if(pai){ //pai encontrado, vou inserir
		TAK *novo = cria();
		strcpy(novo -> nomeFigura,nome);
		novo -> id = id;
		if (dim1) novo -> dim1 = dim1;
		if (dim2) novo -> dim2 = dim2;
		if (dim3) novo -> dim3 = dim3;
		int i;
		for(i = 0; i < tam_filhos; i++){
			if(pai -> filhos[i] == NULL){//achei uma posição válida
				pai -> filhos[i] = novo;
				break;
			}
		}
		if(i == tam_filhos){ //pais cheios, não sei ao certo o que fazer.
		//opção A: tiro arbitrariamente o primeiro elemento, adiciono o novo nele e quem tava lá passa a ser filho dele. Feio, mas parece dar certo.
			TAK *filhoSubs = pai -> filhos[0];
			pai -> filhos[0] = novo;
			novo -> filhos[0] = filhoSubs;					
		}
		return a;		
	}	
	//caso cntrário: pai não encontrado (nao sei se não é p inserir ou se insere em algum lugar arbitrário)
	printf("Pai com código único %d não encontrado! \n",idPai);
	return a;
}

int eFolha(TAK *a){
	if(a){
		int i = 0;
		for (i; i < tam_filhos; i++){
			if(a->filhos[i] != NULL) return 1;
		}
		return 0;
	}
	return 1;
}
void imprimeFigura(TAK *a){
	if(a){
		if(strcmp(a-> nomeFigura,"TRI")) printf("{ cód:%d \n figura:%s \n base:%f \n altura:%f \n área: %f \n }",a->id,a->nomeFigura,a->dim1,a->dim2,((a->dim1 * a->dim2)/2));
		if(strcmp(a-> nomeFigura,"RET")) printf("{ cód:%d \n figura:%s \n base:%f \n altura:%f \n área: %f \n}",a->id,a->nomeFigura,a->dim1,a->dim2,(a->dim1 * a->dim2));
		if(strcmp(a-> nomeFigura,"TRA")) printf("{ cód:%d \n figura:%s \n base menor:%f \n base maior: %f \n altura:%f \n área: }",a->id,a->nomeFigura,a->dim1,a->dim2,((a->dim1 * a->dim2)/2));
		if(strcmp(a-> nomeFigura,"CIR")) printf("{ cód:%d \n figura:%s \n raio:%f \n área: %f \n}",a->id,a->nomeFigura,a->dim1,(M_PI * (pow(a->dim1,2))));
		if(strcmp(a-> nomeFigura,"QUA")) printf("{ cód:%d \n figura:%s \n lado:%f \n área: %f \n}",a->id,a->nomeFigura,a->dim1,(pow(a->dim1, 2)));
	}
}


void imprime(TAK *a, int cont){ //Aqui só imprimimos o principal da figura. Essa parada tá quebrada tranquilamente
	if(a){
		int i,j;
		if(!eFolha(a)){
			int k;
			for (k=0; k < tam_filhos; k++)imprime(a->filhos[k],cont+1);
			for(j=0;j<cont;j++)printf("\t");
			if(eFolha(a))printf("{ cód:%d, figura:%s", a->id,a->nomeFigura);
			printf("\n");
			if(!eFolha(a))imprime(a->filhos[i],cont+1);
		}
		if(eFolha(a))printf("{ cód:%d, figura:%s", a->id,a->nomeFigura);
	}
}





