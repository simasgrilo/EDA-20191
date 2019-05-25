#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include"abb.h"


TABB *cria(){
	TABB * novo = (TABB*)malloc(sizeof(TABB));
	novo -> esq = novo -> dir = NULL;
	return novo;
}


TABB* busca (TABB*a, int id){
	if(!a) return NULL;
	if(a -> id == id) return a;
	if(a -> id < id) return busca(a->dir, id);
	return busca(a -> esq, id);  
}

TABB *insere(TABB* a, int id, char* nome, float dim1, float dim2, float dim3){
	if(!a){
		TABB *resp = cria();
		resp -> id = id;
		strcpy(resp -> nomeFigura,nome);
		if(dim1) resp -> dim1 = dim1;
		if(dim2) resp -> dim2 = dim2;
		if(dim3) resp -> dim3 = dim3;
		return resp;
	}
	if(a-> id > id)a -> esq = insere(a -> esq, id, nome, dim1, dim2, dim3);
	else if( a-> id < id) insere(a -> dir, id, nome, dim1, dim2, dim3);
	return a;
}
