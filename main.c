#include <stdio.h>
#include <ctype.h>
#include "funcoesAuxiliares.h"

#include "constantes.h"
#include "estruturas.h"

char menu(void) {
	char opcao;
	printf("Menu: ");


	scanf(" %c", &opcao);
	limpaBufferStdin();
	return toupper(opcao);

}

int main() {
	tipoEstudante vetorEstudantes[MAX_ESTUDANTES]; //vetor que guarda os dados dos estudantes
	int nEstudantes;	//Numero de estudantes

	//devemos procurar melhor maneira de fazer isto
	int idEstudantes; //Number that keeps track of the "max id" of the user
	return 0;


	char opcao;
	do {
		opcao = menu();
		switch(opcao){
			case 'S': break;
			default: printf("Opcao Invalida.\n");
		}
	} while(opcao!='S');
	return 0;
}
