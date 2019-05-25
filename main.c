
#include"arvg.h"

#include<stdio.h>
#include<string.h>

//amanhã faço o input p arquivo e p coisa simples. To com preguiça de testar agoraa.
int main(){
	char nome[3] = "TRA", arq[31];
	float dim1 = 1.0;
	float dim2 = 2.0;
	float dim3 = 3.0;

	/*TAG * no = NULL;
	no = insere(no,1,0,nome,dim1,dim2,dim3);

	imprime(no); */
	TAG *a, *obj;
	int id, idPai;
	char choice;
	FILE * fp;
	do{
		float dim1 = 0, dim2 = 0, dim3 = 0;
		printf("\n\n");
		printf("\nDigite 'a' para inserir um objeto na árvore, digite 'p' para imprimir um detalhes de um objeto na arvore, digite 'f' para inserir um arquivo contendo objetos na arvore, digite 'P' para imprimir os objetos da árvore, digite 'm' para modificar um objeto na árvore, digite 'c' para alterar a forma de impressão da árvore, digite 'r' para remover um objeto da árvore, digite 't' para transformar a árvore genérica gerada em uma árvore binária de busca \n");
		scanf(" %c",&choice);
		if (choice == 's') break;
		else if (choice == 'a'){
			printf("Insira o código único: ");
			scanf("%d",&id);
			printf("Insira o código do pai deste objeto na árvore: ");
			scanf("%d",&idPai);
			printf("Insira a forma geométrica: ");
			scanf("%s",nome);
			int erro = 0;
			if(!strcmp(nome,"TRA")){
				printf("Insira a base maior: \n");
				scanf("%f",&dim1);
				printf("Insira a base menor: \n ");
				scanf("%f",&dim2);
				printf("Insira a altura: \n");
				scanf("%f",&dim3);
			}
			else if(!strcmp(nome,"TRI")){
				printf("Insira a base: \n ");
				scanf("%f",&dim1);
				printf("Insira a altura: \n");
				scanf("%f",&dim2);
			}
			else if(!strcmp(nome,"RET")){
				printf("Insira a base: \n ");
				scanf("%f",&dim1);
				printf("Insira a altura: \n");
				scanf("%f",&dim2);
			}
			else if(!strcmp(nome,"CIR")){
				printf("Insira o raio: \n ");
				scanf("%f",&dim1);
			}
			else if(!strcmp(nome,"QUA")){
				printf("Insira o lado: \n ");
				scanf("%f",&dim1);
			}
			else{
				erro = 1;
				printf("Forma geométrica inválida!");
			}			
			if(!erro) a = insere(a,id, idPai, nome, dim1, dim2, dim3);
		}//arquivo tá la embaixo
		else if (choice == 'm'){
			printf("Digite o código único do objeto: ");
			scanf("%d",&id);
			obj=busca(a,id);
			if(!obj)printf("objeto com código único %d não encontrado",id);
			else{
				imprimeFigura(obj);
				if(!strcmp(obj -> nomeFigura,"TRA")){
					printf("\nO que deseja alterar:\na)base maior;\nb)base menor;\nc)Altura;");
					scanf(" %c",&choice);
					if(choice == 'a'){
						printf("Insira a nova base maior: \n");
						scanf("%f",&dim1);
						obj -> dim1 = dim1;
					}
					else if(choice == 'b'){
						printf("Insira a nova base menor: \n ");
						scanf("%f",&dim2);
						obj -> dim2 = dim2;
					}
				    else if(choice =='c'){
						printf("Insira a nova altura: \n");
						scanf("%f",&dim3);
						obj -> dim3 = dim3;
					}

				}
				else if(!strcmp(obj -> nomeFigura,"TRI")){
					printf("\nO que deseja alterar:\na)base;\nb)altura;");
					scanf(" %c",&choice);
					if(choice == 'a'){
						printf("Insira a nova base: \n");
						scanf("%f",&dim1);
						obj -> dim1 = dim1;
					}
					else if(choice == 'b'){
						printf("Insira a nova altura: \n ");
						scanf("%f",&dim2);
						obj -> dim2 = dim2;
					}

				}
				else if(!strcmp(obj -> nomeFigura,"RET")){
					printf("\nO que deseja alterar:\na)base;\nb)altura;");
					scanf(" %c",&choice);
					if(choice == 'a'){
						printf("Insira a nova base: \n");
						scanf("%f",&dim1);
						obj -> dim1 = dim1;
					}
					else if(choice == 'b'){
						printf("Insira a nova altura: \n ");
						scanf("%f",&dim2);
						obj -> dim2 = dim2;
					}

				}
				else if(!strcmp(obj -> nomeFigura,"cir")){
					printf("Insira o novo raio: \n ");
					scanf("%f",&dim1);
					obj -> dim1 = dim1;
				}
				else if(!strcmp(obj -> nomeFigura,"QUA")){
					printf("Insira o nov lado: \n ");
					scanf("%f",&dim1);
					obj -> dim1 = dim1;
				}
			}
		}
		else if (choice == 'p'){
			printf("Digite o código único: ");
			scanf("%d",&id);
			imprimeFigura(busca(a,id));
			printf("\n");
		}
		else if (choice == 'r'){
			printf("Digite o código unico do objeto a ser removido: ");
			scanf("%d",&id);
			a = retira(a,id);
		}
		else if (choice == 'P'){
			imprime(a);
		}
		else if (choice == 'l'){
			libera(a);
			a = cria();
		}
		else if (choice == 'f'){
			printf("Digite o nome do arquivo de entrada:");
			scanf("%s", arq);
			a = ler_de_arquivo(arq, a);
		}
		else if (choice == 't'){
			printf("oi");
			//fazer a transformação de uma em outra, liberando a ag.
		}
	}while(1);

	return 0;
}
