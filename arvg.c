#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>

#include"arvg.h"


TAG* cria (void){
	TAG * novo = (TAG*)malloc(sizeof(TAG));
	novo -> prim_filho = novo -> prox_irmao = NULL;
	return novo;
}


TAG *busca (TAG*a, int id){
	if(!a) return NULL;
	if(a -> id == id) return a;
	if(!a -> prim_filho || !a -> prox_irmao) return NULL;
	TAG * resp = NULL;
	if(a -> prim_filho){
		resp = busca(a -> prim_filho,id);
		if(resp) return resp;
		else resp = busca(a -> prox_irmao,id);
	}
	return resp;

}



TAG *insere(TAG* a, int id, int idPai, char* nome, float dim1, float dim2, float dim3){//C acho que nao deixa parametro opcional, se nao tiver o terceiro apenas cagar p isso na main.
	if(!a){
		TAG *novo = cria();
		strcpy(novo -> nomeFigura,nome);
		novo -> id = id;
		novo -> idPai = idPai;
		//abordagem mais preguiçosa: verificar se o dado foi efetivamente passado como parâmetro. caso contrario, cravar na função que chamar a insere como 0.
		if (dim1) novo -> dim1 = dim1;
		if (dim2) novo -> dim2 = dim2;
		if (dim3) novo -> dim3 = dim3;
		return novo;		
	}
	//verifico se já existe algúem com meu código único
	TAG * no = busca(a,id);
	if(no){
		printf("Já existe um elemento na árvore com código %d! \n",id);
		return a;
	}
	//se não for o caso, buscar o pai do nó que será inserido
	TAG *pai = busca(a, idPai);
	if(pai){ //pai encontrado, vou inserir
		TAG *novo = cria();
		strcpy(novo -> nomeFigura,nome);
		novo -> id = id;
		novo -> idPai = idPai;
		if (dim1) novo -> dim1 = dim1;
		if (dim2) novo -> dim2 = dim2;
		if (dim3) novo -> dim3 = dim3;
		if(pai -> prim_filho){
			TAG * p = pai -> prim_filho;
			while(p -> prox_irmao) p = p -> prox_irmao;
			p -> prox_irmao = novo;
		
		}
		else pai -> prim_filho = novo;
		return a;		
	}	
	//caso cntrário: pai não encontrado (nao sei se não é p inserir ou se insere em algum lugar arbitrário)
	printf("Pai com código único %d não encontrado! Não foram inseridos novos nós. \n",idPai);
	return a;
}

void libera(TAG * a){
	if(a->prim_filho) libera(a -> prim_filho);
	if(a -> prox_irmao) libera(a -> prox_irmao);
	free(a);

}

int eFolha(TAG *a){
	if(a){
		if(!a->prim_filho) return 0;
	}
	return 1;
}
void imprimeFigura(TAG *a){
	if(a){
		if(strcmp(a-> nomeFigura,"TRI")) printf("{ cód:%d \n figura:%s \n base:%f \n altura:%f \n área: %f \n }",a->id,a->nomeFigura,a->dim1,a->dim2,((a->dim1 * a->dim2)/2));
		if(strcmp(a-> nomeFigura,"RET")) printf("{ cód:%d \n figura:%s \n base:%f \n altura:%f \n área: %f \n}",a->id,a->nomeFigura,a->dim1,a->dim2,(a->dim1 * a->dim2));
		if(strcmp(a-> nomeFigura,"TRA")) printf("{ cód:%d \n figura:%s \n base menor:%f \n base maior: %f \n altura:%f \n área: }",a->id,a->nomeFigura,a->dim1,a->dim2,(((a->dim1 + a->dim2)*a->dim3)/2));
		if(strcmp(a-> nomeFigura,"CIR")) printf("{ cód:%d \n figura:%s \n raio:%f \n área: %f \n}",a->id,a->nomeFigura,a->dim1,(M_PI * (pow(a->dim1,2))));
		if(strcmp(a-> nomeFigura,"QUA")) printf("{ cód:%d \n figura:%s \n lado:%f \n área: %f \n}",a->id,a->nomeFigura,a->dim1,(pow(a->dim1, 2)));
	}
}


void imprime(TAG *a){ //Aqui só imprimimos o principal da figura.
	if(a){
		printf("{ cód:%d, figura:%s }\n", a -> id, a -> nomeFigura);
		if(a -> prim_filho) imprime(a -> prim_filho);
		if(a -> prox_irmao) imprime(a -> prox_irmao);
	}
}

TAG *retira(TAG *a, int id){//testei nao
	if(!a) return a;
	TAG *ret = busca(a, id);
	if(!ret){
		printf("Elemento com código %d não encontrado!",id);
		return a;
	}
	TAG * pai = busca(a, ret -> idPai);
	if(pai -> prim_filho == ret){
		//TAG *p = ret; 
		pai -> prim_filho = ret -> prim_filho;
		TAG *p = pai -> prim_filho;
		while(p -> prox_irmao) p = p -> prox_irmao;
		p -> prox_irmao = ret -> prox_irmao;
		free(ret);
	}
	TAG *p = pai -> prim_filho;
	while(p -> prox_irmao != ret) p = p -> prox_irmao;
	if(!eFolha(ret)){
		TAG *q = p -> prox_irmao;
		p -> prox_irmao = ret -> prim_filho;
		TAG *aux = ret -> prim_filho;
		while(aux -> prox_irmao) aux = aux -> prox_irmao;
		aux -> prox_irmao = q;
		free(ret);
	}
	return a;
}
//faltam ajustes. faço na volta
TAG* ler_de_arquivo(char *nome1, TAG *a){
	FILE *f = fopen(nome1, "rt");
	if(!f){
		printf("Arquivo nao existente\n");
		return a;
	}
	int id=-1, idPai, tam = 32,i,j;
	float dim1, dim2, dim3;
	char k,nome[3], *linha;
	while(tam = getline(&linha, &tam, f) != -1){
		i = 0, j =0;
		//while(linha[i] != '\n'){
		//a leitura tá bem esquisita, acho que tem a ver com o tipo de linha que o getline traz
	    id = linha[i++];
		printf("%d",id);
		i++;
		idPai = linha[i++];
		printf("%d ",idPai);
		i++;
		while(linha[i] != ' ') nome[j++] = linha[i++];
		printf("%s ",nome);
		if((!strcmp(nome,"TRI")) || ((!strcmp(nome,"RET")))){
			while(linha[i] == ' ') i++;
			dim1 = linha[i];
			while(linha[i] == ' ') i++;
			dim2 = linha[i];
			printf("%f ", dim1);
			printf("%f ", dim2);
		}
		else if ((!strcmp(nome,"CIR")) || ((!strcmp(nome,"QUA")))){
			while(linha[i] == ' ') i++;
			dim1 = linha[i];
			printf("%f ", dim1);
		}
		else if (!strcmp(nome,"TRA")){
			while(linha[i] == ' ') i++;
			dim1 = linha[i];
			while(linha[i] == ' ') i++;
			dim2 = linha[i];
			while(linha[i] == ' ') i++;
			dim3 = linha[i];
			printf("%f ", dim1);
			printf("%f ", dim2);
			printf("%f ", dim3);
			printf("\n");
		}
		//}
		printf("%s",linha);// se apagar essa linha da segfault. se printar \n também. investigo mais tarde.
	}
	fclose(f);
	printf("Arquivo lido com sucesso!\n");
	return NULL;
}




