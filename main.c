#include <stdio.h>
#include <ctype.h>
#include "funcoesAuxiliares.h"

char menu(void) {
	char opcao;
	printf("Menu: ");


	scanf(" %c", &opcao);
	limpaBufferStdin();
	return toupper(opcao);
}

int main() {
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
