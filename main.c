#include <stdio.h>
#include <ctype.h>
#include "funcoesAuxiliares.h"

#include "constantes.h"
#include "estruturas.h"
#include "funcsPerguntas.h"

char menu(void) {
	char opcao;
	printf("Menu: \n");
	printf("P - Menu de Perguntas\n");
	printf("S - Sair\n");
	opcao = toupper(lerChar("Opcao: "));
	return toupper(opcao);
}

int main() {
	tipoEstudante vetorEstudantes[MAX_ESTUDANTES]; //vetor que guarda os dados dos estudantes
	int nEstudantes;	//Numero de estudantes

	//devemos procurar melhor maneira de fazer isto
	int idEstudantes; //Number that keeps track of the "max id" of the user


	char opcao;
	do {
		opcao = menu();
		switch(opcao){
			case 'S': break;
			case 'P': menuPerguntas();
				break;
			default: printf("Opcao Invalida.\n");
		}
	} while(opcao!='S');
	return 0;
}
