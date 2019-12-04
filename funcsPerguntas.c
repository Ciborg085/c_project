#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "funcoesAuxiliares.h"
#include "estruturas.h"

void menuPerguntas(void) {
	char opcao;
	do {
		printf("Gerir perguntas:\n");
		printf("S - Sair para menu principal\n");
		printf("I - Inserir perguntas\n");

		opcao = toupper(lerChar("Opcao: "));
		switch(opcao) {
			case 'I':
			case 'S': break;
			default: printf("Opcao invalida");
		}
	} while(opcao != 'S');
}
