#include <stdio.h>
#include <ctype.h>
#include "funcsAuxiliares.h"

#include "constantes.h"
#include "estruturas.h"
#include "funcsPerguntas.h"
#include "funcsEstudantes.h"

char menu(void) {
	char opcao;
	printf("Numero de alunos: %i\tNumero de Perguntas: %i\n");
	printf("Quantidade de treinos realizados: \tQuantidade de treinos a decorrer: \n");

	printf("Menu: \n");
	printf("P - Menu de Perguntas\n");
	printf("E - Menu de Estudantes\n");
	printf("G - Gravar dados\n");
	printf("L - Ler dados\n");
	printf("S - Sair\n");
	opcao = toupper(lerChar("Opcao: "));
	return toupper(opcao);
}

int main() {
	tipoEstudante vetorEstudantes[MAX_ESTUDANTES]; //vetor que guarda os dados dos estudantes
	int nEstudantes;	//Numero de estudantes
	tipoPergunta vetorPerguntas[MAX_PERGUNTAS];
	int nPerguntas;

	char opcao;
	do {
		opcao = menu();
		switch(opcao){
			case 'P': menuPerguntas(vetorPerguntas, &nPerguntas);
				break;
			case 'E': menuEstudantes(vetorEstudantes,&nEstudantes);
				break;
			case 'G': gravarFicheiroBinario(vetorEstudantes,nEstudantes,vetorPerguntas,nPerguntas);
				break;
			case 'L': lerFicheiroBinario(vetorEstudantes,&nEstudantes,vetorPerguntas,&nPerguntas);
				break;
			case 'S': break;
			default: printf("Opcao Invalida.\n");
		}
	} while(opcao!='S');
	return 0;
}
