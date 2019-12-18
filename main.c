#include <stdio.h>
#include <ctype.h>
#include "funcsAuxiliares.h"

#include "constantes.h"
#include "estruturas.h"
#include "funcsPerguntas.h"
#include "funcsEstudantes.h"
#include "funcsTreinos.h"

char menu(void) {
	char opcao;
	printf("Menu: \n");
	printf("P - Menu de Perguntas\n");
	printf("E - Menu de Estudantes\n");
	printf("T - Menu de Treinos\n");
	printf("S - Sair\n");
	opcao = toupper(lerChar("Opcao: "));
	return toupper(opcao);
}

int main() {
	tipoEstudante vetorEstudantes[MAX_ESTUDANTES]; //vetor que guarda os dados dos estudantes
	int nEstudantes = 0;	//Numero de estudantes
	tipoPergunta vetorPerguntas[MAX_PERGUNTAS];
	int nPerguntas = 0;
	tipoTreino *vetorTreinos;
	int nTreinos = 0;


	//devemos procurar melhor maneira de fazer isto
	int idEstudantes; //Number that keeps track of the "max id" of the user

	char opcao;
	do {
		opcao = menu();
		switch(opcao){
			case 'P': menuPerguntas(vetorPerguntas, &nPerguntas);
				break;
			case 'E':	menuEstudantes(vetorEstudantes,&nEstudantes);
				break;
			case 'T': menuTreinos(vetorTreinos, &nTreinos, vetorEstudantes, nEstudantes);
				break;
			case 'S': break;
			default: printf("Opcao Invalida.\n");
		}
	} while(opcao!='S');
	return 0;
}
