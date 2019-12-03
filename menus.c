#include "funcoesAuxiliares.h"

char menu(void) {
	char opcao;
	printf("Menu: ");
	opcao = toupper(lerChar("Opcao: "));
	return toupper(opcao);
}

char menuPerguntas(void) {
	char opcao;
	do {
		printf("Gerir perguntas:\n");
		printf("S - Sair para menu principal");
		opcao = toupper(lerChar("Opcao: "));
		switch(opcao) {
			case 'S': break;
			default: printf("Opcao invalida");
		}
	} while(opcao != 'S');
	return toupper(opcao);
}
