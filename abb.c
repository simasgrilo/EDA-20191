#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "abb.h"

TABB *criaABB()
{
	TABB *novo = (TABB *)malloc(sizeof(TABB));
	novo->esq = novo->dir = NULL;
	return novo;
}

TABB *buscaABB(TABB *a, int id)
{
	if (!a)
		return NULL;
	if (a->id == id)
		return a;
	if (a->id < id)
		return buscaABB(a->dir, id);
	return buscaABB(a->esq, id);
}

TABB *insereABB(TABB *a, int id, char *nome, float dim1, float dim2, float dim3)
{
	if (!a)
	{
		TABB *resp = criaABB();
		resp->id = id;
		strcpy(resp->nomeFigura, nome);
		if (dim1)
			resp->dim1 = dim1;
		if (dim2)
			resp->dim2 = dim2;
		if (dim3)
			resp->dim3 = dim3;
		return resp;
	}
	if (a->id > id)
		a->esq = insereABB(a->esq, id, nome, dim1, dim2, dim3);
	else if (a->id < id)
		insereABB(a->dir, id, nome, dim1, dim2, dim3);
	return a;
}
