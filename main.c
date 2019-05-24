
#include"arvk.h"


//amanhã faço o input p arquivo e p coisa simples. To com preguiça de testar agora.
int main(){
	char nome[3] = "TRA";
	float dim1 = 1.0;
	float dim2 = 2.0;
	float dim3 = 3.0;

	TAK * no = NULL;
	no = insere(no,1,0,nome,dim1,dim2,dim3);

	imprime(no,0);

	return 0;
}
