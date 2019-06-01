
#include "arvg.h"
#include "abb.h"
#include "ab.h"

#include <stdio.h>
#include <string.h>

int main()
{
	char nome[3] = "TRA", arq[31];
	float dim1 = 1.0;
	float dim2 = 2.0;
	float dim3 = 3.0;

	/*TAG * no = NULL;
	no = insere(no,1,0,nome,dim1,dim2,dim3);

	imprime(no); */
	TAG *a = NULL, *obj = NULL;
	TABB *b = NULL;
	TAB *c = NULL;
	int id, idPai;
	FILE *fp;
	while (!a)
	{
		printf("Digite o nome do arquivo de entrada:");
		scanf("%s", arq);
		a = ler_de_arquivo(arq, a);
		imprime(a, 0);
	}

	do
	{
		float dim1 = 0, dim2 = 0, dim3 = 0;
		char choice;
		printf("\n\n");
		printf("\nDigite 'a' para inserir um objeto na árvore\nDigite 'p' para imprimir detalhes de um objeto na arvore\nDigite 'P' para imprimir os objetos da árvore\nDigite 'm' para modificar um objeto\nDigite 'r' para remover um objeto da árvore\nDigite 't' para transformar a árvore genérica gerada em uma árvore binária de busca \nDigite 'b' para imprimir a árvore binária de busca gerada a partir da árvore genérica\nDigite 'B' para transformar a árvore genérica em uma árvore B\nDigite 'v' para imprimir a árvore B gerada a partir da árvore genérica\nDigite 's' para sair\n");
		scanf(" %c", &choice);
		if (choice == 's')
		{
			if (a)
				libera(a);
			if (b)
				liberaABB(b);
			if (c)
				liberaAB(c);
			break;
		}
		else if (choice == 'a')
		{
			printf("Insira o código único: ");
			scanf("%d", &id);
			if (busca(a, id))
			{
				printf("Id já existente.");
			}
			else
			{
				printf("Insira o código do pai deste objeto na árvore: ");
				scanf("%d", &idPai);
				printf("Insira a forma geométrica: ");
				scanf("%s", nome);
				int erro = 0;
				if (!strcmp(nome, "TRA"))
				{
					printf("Insira a base maior: \n");
					scanf("%f", &dim1);
					printf("Insira a base menor: \n ");
					scanf("%f", &dim2);
					printf("Insira a altura: \n");
					scanf("%f", &dim3);
				}
				else if (!strcmp(nome, "TRI"))
				{
					printf("Insira a base: \n ");
					scanf("%f", &dim1);
					printf("Insira a altura: \n");
					scanf("%f", &dim2);
				}
				else if (!strcmp(nome, "RET"))
				{
					printf("Insira a base: \n ");
					scanf("%f", &dim1);
					printf("Insira a altura: \n");
					scanf("%f", &dim2);
				}
				else if (!strcmp(nome, "CIR"))
				{
					printf("Insira o raio: \n ");
					scanf("%f", &dim1);
				}
				else if (!strcmp(nome, "QUA"))
				{
					printf("Insira o lado: \n ");
					scanf("%f", &dim1);
				}
				else
				{
					erro = 1;
					printf("Forma geométrica inválida!");
				}
				if (!erro)
				{
					a = insere(a, id, idPai, nome, dim1, dim2, dim3);
					printf("Objeto inserido com sucesso!");
				}
			}
		}
		else if (choice == 'm')
		{
			printf("Digite o código único do objeto: ");
			scanf("%d", &id);
			obj = busca(a, id);
			if (!obj)
				printf("objeto com código único %d não encontrado", id);
			else
			{
				char choice;
				imprimeFigura(obj);
				if (!strcmp(obj->nomeFigura, "TRA"))
				{
					//char choice;
					printf("\nO que deseja alterar:\na)base maior;\nb)base menor;\nc)Altura;\nd)Nome;\ne)pai na árvore\n");
					scanf(" %c", &choice);
					if (choice == 'a')
					{
						printf("Insira a nova base maior: \n");
						scanf("%f", &dim1);
						obj->dim1 = dim1;
					}
					else if (choice == 'b')
					{
						printf("Insira a nova base menor: \n ");
						scanf("%f", &dim2);
						obj->dim2 = dim2;
					}
					else if (choice == 'c')
					{
						printf("Insira a nova altura: \n");
						scanf("%f", &dim3);
						obj->dim3 = dim3;
					}
					else if (choice == 'd')
					{
						printf("Insira o novo nome: \n ");
						scanf("%s", nome);
						strcpy(obj->nomeFigura, nome);
						if (!strcmp(nome, "TRA"))
						{
							printf("Insira a base maior: \n");
							scanf("%f", &dim1);
							printf("Insira a base menor: \n ");
							scanf("%f", &dim2);
							printf("Insira a altura: \n");
							scanf("%f", &dim3);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = dim3;
						}
						else if (!strcmp(nome, "TRI"))
						{
							printf("Insira a base: \n ");
							scanf("%f", &dim1);
							printf("Insira a altura: \n");
							scanf("%f", &dim2);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "RET"))
						{
							printf("Insira a base: \n ");
							scanf("%f", &dim1);
							printf("Insira a altura: \n");
							scanf("%f", &dim2);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "CIR"))
						{
							printf("Insira o raio: \n ");
							scanf("%f", &dim1);
							obj->dim1 = dim1;
							obj->dim2 = 0;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "QUA"))
						{
							printf("Insira o lado: \n ");
							scanf("%f", &dim1);
							obj->dim1 = dim1;
							obj->dim2 = 0;
							obj->dim3 = 0;
						}
					}
					else if (choice == 'e')
					{
						if (obj->idPai == 0)
						{
							printf("Objeto é raiz.\n");
						}
						else
						{
							printf("Insira o código único do novo pai na árvore: \n");
							scanf("%d", &idPai);
							a = modificaPai(a, obj, idPai);
						}
					}
				}
				else if (!strcmp(obj->nomeFigura, "TRI"))
				{
					//char choice;
					printf("\nO que deseja alterar:\na)base;\nb)altura;\nc)Nome;\nd)pai na árvore\n");
					scanf(" %c", &choice);
					/*if (choice == 'a')
					{
						printf("Insira a nova base: \n");
						scanf("%f", &dim1);
						obj->dim1 = dim1;
					}
					else if (choice == 'b')
					{
						printf("Insira a nova altura: \n ");
						scanf("%f", &dim2);
						obj->dim2 = dim2;
					}*/
					if (choice == 'a')
					{
						printf("Insira a nova base: \n");
						scanf("%f", &dim1);
						obj->dim1 = dim1;
					}
					else if (choice == 'b')
					{
						printf("Insira a nova altura: \n ");
						scanf("%f", &dim2);
						obj->dim2 = dim2;
					}
					else if (choice == 'c')
					{
						printf("Insira o novo nome: \n ");
						scanf("%s", nome);
						strcpy(obj->nomeFigura, nome);
						if (!strcmp(nome, "TRA"))
						{
							printf("Insira a base maior: \n");
							scanf("%f", &dim1);
							printf("Insira a base menor: \n ");
							scanf("%f", &dim2);
							printf("Insira a altura: \n");
							scanf("%f", &dim3);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = dim3;
						}
						else if (!strcmp(nome, "TRI"))
						{
							printf("Insira a base: \n ");
							scanf("%f", &dim1);
							printf("Insira a altura: \n");
							scanf("%f", &dim2);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "RET"))
						{
							printf("Insira a base: \n ");
							scanf("%f", &dim1);
							printf("Insira a altura: \n");
							scanf("%f", &dim2);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "CIR"))
						{
							printf("Insira o raio: \n ");
							scanf("%f", &dim1);
							obj->dim1 = dim1;
							obj->dim2 = 0;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "QUA"))
						{
							printf("Insira o lado: \n ");
							scanf("%f", &dim1);
							obj->dim1 = dim1;
							obj->dim2 = 0;
							obj->dim3 = 0;
						}
					}
					else if (choice == 'd')
					{
						if (obj->idPai == 0)
						{
							printf("Objeto é raiz.\n");
						}
						else
						{
							printf("Insira o código único do novo pai na árvore: \n");
							scanf("%d", &idPai);
							a = modificaPai(a, obj, idPai);
						}
					}
				}
				else if (!strcmp(obj->nomeFigura, "RET"))
				{
					//char choice;
					printf("\nO que deseja alterar:\na)base;\nb)altura;\nc)Nome;\nd)pai na árvore\n");
					scanf(" %c", &choice);
					if (choice == 'a')
					{
						printf("Insira a nova base: \n");
						scanf("%f", &dim1);
						obj->dim1 = dim1;
					}
					else if (choice == 'b')
					{
						printf("Insira a nova altura: \n ");
						scanf("%f", &dim2);
						obj->dim2 = dim2;
					}
					else if (choice == 'c')
					{
						printf("Insira o novo nome: \n ");
						scanf("%s", nome);
						strcpy(obj->nomeFigura, nome);
						if (!strcmp(nome, "TRA"))
						{
							printf("Insira a base maior: \n");
							scanf("%f", &dim1);
							printf("Insira a base menor: \n ");
							scanf("%f", &dim2);
							printf("Insira a altura: \n");
							scanf("%f", &dim3);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = dim3;
						}
						else if (!strcmp(nome, "TRI"))
						{
							printf("Insira a base: \n ");
							scanf("%f", &dim1);
							printf("Insira a altura: \n");
							scanf("%f", &dim2);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "RET"))
						{
							printf("Insira a base: \n ");
							scanf("%f", &dim1);
							printf("Insira a altura: \n");
							scanf("%f", &dim2);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "CIR"))
						{
							printf("Insira o raio: \n ");
							scanf("%f", &dim1);
							obj->dim1 = dim1;
							obj->dim2 = 0;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "QUA"))
						{
							printf("Insira o lado: \n ");
							scanf("%f", &dim1);
							obj->dim1 = dim1;
							obj->dim2 = 0;
							obj->dim3 = 0;
						}
					}
					else if (choice == 'd')
					{
						if (obj->idPai == 0)
						{
							printf("Objeto é raiz.\n");
						}
						else
						{
							printf("Insira o código único do novo pai na árvore: \n");
							scanf("%d", &idPai);
							a = modificaPai(a, obj, idPai);
						}
					}
				}
				else if (!strcmp(obj->nomeFigura, "CIR"))
				{
					//printf("Insira o novo raio: \n ");
					printf("\nO que deseja alterar:\na)Raio\nb)Nome;\nc)Pai na árvore\n");
					scanf(" %c", &choice);

					if (choice == 'a')
					{
						printf("Insira a nova base maior: \n");
						scanf("%f", &dim1);
						obj->dim1 = dim1;
					}
					else if (choice == 'b')
					{
						printf("Insira o novo nome: \n ");
						scanf("%s", nome);
						strcpy(obj->nomeFigura, nome);
						if (!strcmp(nome, "TRA"))
						{
							printf("Insira a base maior: \n");
							scanf("%f", &dim1);
							printf("Insira a base menor: \n ");
							scanf("%f", &dim2);
							printf("Insira a altura: \n");
							scanf("%f", &dim3);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = dim3;
						}
						else if (!strcmp(nome, "TRI"))
						{
							printf("Insira a base: \n ");
							scanf("%f", &dim1);
							printf("Insira a altura: \n");
							scanf("%f", &dim2);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "RET"))
						{
							printf("Insira a base: \n ");
							scanf("%f", &dim1);
							printf("Insira a altura: \n");
							scanf("%f", &dim2);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "CIR"))
						{
							printf("Insira o raio: \n ");
							scanf("%f", &dim1);
							obj->dim1 = dim1;
							obj->dim2 = 0;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "QUA"))
						{
							printf("Insira o lado: \n ");
							scanf("%f", &dim1);
							obj->dim1 = dim1;
							obj->dim2 = 0;
							obj->dim3 = 0;
						}
					}
					else if (choice == 'c')
					{
						if (obj->idPai == 0)
						{
							printf("Objeto é raiz.\n");
						}
						else
						{
							printf("Insira o código único do novo pai na árvore: \n");
							scanf("%d", &idPai);
							a = modificaPai(a, obj, idPai);
						}
					}
				}
				else if (!strcmp(obj->nomeFigura, "QUA"))
				{
					char choice;
					printf("\nO que deseja alterar:\na)lado;\nb)Nome;\nc)pai na árvore;\n");
					scanf(" %c", &choice);
					if (choice == 'a')
					{
						printf("Insira o novo lado: \n");
						scanf("%f", &dim1);
						obj->dim1 = dim1;
					}
					else if (choice == 'b')
					{
						printf("Insira o novo nome: \n ");
						scanf("%s", nome);
						strcpy(obj->nomeFigura, nome);
						if (!strcmp(nome, "TRA"))
						{
							printf("Insira a base maior: \n");
							scanf("%f", &dim1);
							printf("Insira a base menor: \n ");
							scanf("%f", &dim2);
							printf("Insira a altura: \n");
							scanf("%f", &dim3);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = dim3;
						}
						else if (!strcmp(nome, "TRI"))
						{
							printf("Insira a base: \n ");
							scanf("%f", &dim1);
							printf("Insira a altura: \n");
							scanf("%f", &dim2);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "RET"))
						{
							printf("Insira a base: \n ");
							scanf("%f", &dim1);
							printf("Insira a altura: \n");
							scanf("%f", &dim2);
							obj->dim1 = dim1;
							obj->dim2 = dim2;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "CIR"))
						{
							printf("Insira o raio: \n ");
							scanf("%f", &dim1);
							obj->dim1 = dim1;
							obj->dim2 = 0;
							obj->dim3 = 0;
						}
						else if (!strcmp(nome, "QUA"))
						{
							printf("Insira o lado: \n ");
							scanf("%f", &dim1);
							obj->dim1 = dim1;
							obj->dim2 = 0;
							obj->dim3 = 0;
						}
					}
					else if (choice == 'c')
					{
						if (obj->idPai == 0)
						{
							printf("Objeto é raiz.\n");
						}
						else
						{
							printf("Insira o código único do novo pai na árvore: \n");
							scanf("%d", &idPai);
							a = modificaPai(a, obj, idPai);
						}
					}
				}
			}
		}
		else if (choice == 'p')
		{
			printf("Digite o código único: ");
			scanf("%d", &id);
			TAG *no = busca(a, id);
			if (no)
				imprimeFigura(no);
			else
				printf("nó com elemento %d não encontrado!", id);
			printf("\n");
		}
		else if (choice == 'r')
		{
			printf("Digite o código unico do objeto a ser removido: ");
			scanf("%d", &id);
			printf("Digite o código unico do objeto a ser o novo pai: ");
			scanf("%d", &idPai);
			a = retira(a, id, idPai);
		}
		else if (choice == 'P')
		{
			imprime(a, 0);
		}
		else if (choice == 'l')
		{
			libera(a);
			a = cria();
		}
		else if (choice == 't')
		{
			liberaABB(b);
			if (a)
			{
				b = g2b(a);
			}
			else
				printf("Árvore genérica vazia!");
			//fazer a transformação de uma em outra, liberando a ag?.
		}
		else if (choice == 'b')
		{
			if (b)
				imprimeABB(b, 1);
			else
				printf("Árvore de busca binária correspondente vazia!");
		}
		else if (choice == 'B')
		{
			printf("Insira o fator de ramificação t da Árvore B:\n");
			int t;
			scanf("%d", &t);
			if (a)
			{
				c = liberaAB(c);
				int qte = conta(a);
				TFig **vet = (TFig **)malloc(sizeof(TFig *) * qte);

				// c = criaAB(t);
				c = g2AB(a, vet, t);
				liberaVetFig(vet, qte);
			}
			else
				printf("Árvore genérica vazia!");
		}
		else if (choice == 'v')
		{
			if (c)
				imprimeAB(c, 0);
			else
				printf("Árvore B vazia!");
		}
	} while (1);
	return 0;
}
