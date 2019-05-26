#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "arvg.h"

TAG *cria(void)
{
	TAG *novo = (TAG *)malloc(sizeof(TAG));
	novo->prim_filho = novo->prox_irmao = NULL;
	return novo;
}

TAG *busca(TAG *a, int id)
{
	if (!a)
		return NULL;
	if (a->id == id)
		return a;
	if (!a->prim_filho && !a->prox_irmao)
		return NULL;
	if (a->prim_filho)
	{
		TAG *resp = busca(a->prim_filho, id);
		if (resp)
			return resp;
	}
	if (a->prox_irmao)
		return busca(a->prox_irmao, id);
	else
		return NULL;
}

TAG *insere(TAG *a, int id, int idPai, char *nome, float dim1, float dim2, float dim3)
{ //C acho que nao deixa parametro opcional, se nao tiver o terceiro apenas cagar p isso na main.
	if (!a)
	{
		TAG *novo = cria();
		strcpy(novo->nomeFigura, nome);
		novo->id = id;
		novo->idPai = idPai;
		//abordagem mais preguiçosa: verificar se o dado foi efetivamente passado como parâmetro. caso contrario, cravar na função que chamar a insere como 0.
		if (dim1)
			novo->dim1 = dim1;
		if (dim2)
			novo->dim2 = dim2;
		if (dim3)
			novo->dim3 = dim3;
		return novo;
	}
	//verifico se já existe algúem com meu código único
	TAG *no = busca(a, id);
	if (no)
	{
		printf("Já existe um elemento na árvore com código %d! \n", id);
		return a;
	}
	if (!idPai)
	{
		TAG *novo = cria();
		strcpy(novo->nomeFigura, nome);
		novo->id = id;
		novo->idPai = idPai;
		//abordagem mais preguiçosa: verificar se o dado foi efetivamente passado como parâmetro. caso contrario, cravar na função que chamar a insere como 0.
		if (dim1)
			novo->dim1 = dim1;
		if (dim2)
			novo->dim2 = dim2;
		if (dim3)
			novo->dim3 = dim3;
		novo->prox_irmao = a->prox_irmao;
		a->prox_irmao = novo;
		return a;
	}
	//se não for o caso, buscar o pai do nó que será inserido
	TAG *pai = busca(a, idPai);
	if (pai)
	{ //pai encontrado, vou inserir
		TAG *novo = cria();
		strcpy(novo->nomeFigura, nome);
		novo->id = id;
		novo->idPai = idPai;
		if (dim1)
			novo->dim1 = dim1;
		if (dim2)
			novo->dim2 = dim2;
		if (dim3)
			novo->dim3 = dim3;
		if (pai->prim_filho)
		{
			TAG *p = pai->prim_filho;
			while (p->prox_irmao)
				p = p->prox_irmao;
			p->prox_irmao = novo;
		}
		else
			pai->prim_filho = novo;
		return a;
	}
	//caso cntrário: pai não encontrado (nao sei se não é p inserir ou se insere em algum lugar arbitrário)
	printf("Pai com código único %d não encontrado! Não foram inseridos novos nós. \n", idPai);
	return a;
}

void libera(TAG *a)
{
	if (a->prim_filho)
		libera(a->prim_filho);
	if (a->prox_irmao)
		libera(a->prox_irmao);
	free(a);
}

int eFolha(TAG *a)
{
	if (a)
	{
		if (!a->prim_filho)
			return 0;
	}
	return 1;
}
void imprimeFigura(TAG *a)
{
	if (a)
	{
		if (!strcmp(a->nomeFigura, "TRI"))
			printf("{ cód:%d \n figura:%s \n base:%f \n altura:%f \n área: %f \n }", a->id, a->nomeFigura, a->dim1, a->dim2, ((a->dim1 * a->dim2) / 2));
		if (!strcmp(a->nomeFigura, "RET"))
			printf("{ cód:%d \n figura:%s \n base:%f \n altura:%f \n área: %f \n}", a->id, a->nomeFigura, a->dim1, a->dim2, (a->dim1 * a->dim2));
		if (!strcmp(a->nomeFigura, "TRA"))
			printf("{ cód:%d \n figura:%s \n base menor:%f \n base maior: %f \n altura:%f \n área: }", a->id, a->nomeFigura, a->dim1, a->dim2, (((a->dim1 + a->dim2) * a->dim3) / 2));
		if (!strcmp(a->nomeFigura, "CIR"))
			printf("{ cód:%d \n figura:%s \n raio:%f \n área: %f \n}", a->id, a->nomeFigura, a->dim1, (M_PI * (pow(a->dim1, 2))));
		if (!strcmp(a->nomeFigura, "QUA"))
			printf("{ cód:%d \n figura:%s \n lado:%f \n área: %f \n}", a->id, a->nomeFigura, a->dim1, (pow(a->dim1, 2)));
	}
}

void imprime(TAG *a)
{ //Aqui só imprimimos o principal da figura.
	if (a)
	{
		printf("{ cód:%d, figura:%s }\n", a->id, a->nomeFigura);
		if (a->prim_filho)
			imprime(a->prim_filho);
		if (a->prox_irmao)
			imprime(a->prox_irmao);
	}
}

TAG *retira(TAG *a, int id)
{ //testei nao
	if (!a)
		return a;
	TAG *ret = busca(a, id);
	if (!ret)
	{
		printf("Elemento com código %d não encontrado!", id);
		return a;
	}
	TAG *pai = busca(a, ret->idPai);
	if (pai->prim_filho == ret)
	{
		//TAG *p = ret;
		pai->prim_filho = ret->prim_filho;
		TAG *p = pai->prim_filho;
		while (p->prox_irmao)
			p = p->prox_irmao;
		p->prox_irmao = ret->prox_irmao;
		free(ret);
	}
	TAG *p = pai->prim_filho;
	while (p->prox_irmao != ret)
		p = p->prox_irmao;
	if (!eFolha(ret))
	{
		TAG *q = p->prox_irmao;
		p->prox_irmao = ret->prim_filho;
		TAG *aux = ret->prim_filho;
		while (aux->prox_irmao)
			aux = aux->prox_irmao;
		aux->prox_irmao = q;
		free(ret);
	}
	return a;
}

char *init(char *string, int n)
{
	int i = 0;
	for (i; i < n; i++)
		string[i] = '\0';
	return string;
}

//faltam ajustes. faço na volta
TAG *ler_de_arquivo(char *nome1, TAG *a)
{
	FILE *f = fopen(nome1, "r");
	if (!f)
	{
		printf("Arquivo nao existente\n");
		return a;
	}
	int i, j, resp = 1;
	int tam = 32;
	float dim1 = 0, dim2 = 0, dim3 = 0;
	char k, nome[3], linha[124], aux[32];
	int id, idPai;
	while (fgets(linha, sizeof linha, f) != NULL)
	{
		init(aux, tam);
		float dim1 = 0, dim2 = 0, dim3 = 0;
		id = 0, idPai = 0;
		i = 0, j = 0;
		while (linha[i] != '/')
		{
			aux[i] = linha[i];
			i++;
		}
		id = atoi(aux);
		i++;
		init(aux, tam);
		while (linha[i] != '/')
		{
			aux[j] = linha[i];
			j++;
			i++;
		}
		idPai = atoi(aux);
		init(aux, tam);
		i++;
		j = 0;
		while (linha[i] != ' ')
		{
			nome[j] = linha[i];
			j++;
			i++;
		}
		j = 0;
		if ((!strcmp(nome, "TRI")) || ((!strcmp(nome, "RET"))))
		{
			while (linha[i] == ' ')
				i++;
			while (linha[i] != ' ')
			{
				aux[j] = linha[i];
				j++;
				i++;
			}
			dim1 = atof(aux);
			init(aux, tam);
			j = 0;
			while (linha[i] == ' ')
				i++;
			while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0')
			{
				aux[j] = linha[i];
				i++;
				j++;
			}
			dim2 = atof(aux);
			init(aux, tam);
		}
		else if ((!strcmp(nome, "CIR")) || ((!strcmp(nome, "QUA"))))
		{
			while (linha[i] == ' ')
				i++;
			j = 0;
			while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0')
			{
				aux[j] = linha[i];
				j++;
				i++;
			}
			dim1 = atof(aux);
			init(aux, tam);
		}
		else if (!strcmp(nome, "TRA"))
		{
			while (linha[i] == ' ')
				i++;
			j = 0;
			while (linha[i] != ' ')
			{
				aux[j] = linha[i];
				j++;
				i++;
			}
			dim1 = atof(aux);
			init(aux, tam);
			j = 0;
			while (linha[i] == ' ')
				i++;
			while (linha[i] != ' ')
			{
				aux[j] = linha[i];
				j++;
				i++;
			}
			dim2 = atof(aux);
			init(aux, tam);
			j = 0;
			while (linha[i] == ' ')
				i++;
			while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0')
			{
				aux[j] = linha[i];
				i++;
				j++;
			}
			dim3 = atof(aux);
			init(aux, tam);
		}
		if (strlen(linha) > 8)
		{
			a = insere(a, id, idPai, nome, dim1, dim2, dim3);
		}
	}
	printf("Arquivo lido com sucesso!\n");
	return a;
}
