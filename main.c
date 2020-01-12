#include <stdio.h>
#include <ctype.h>
#include "funcsAuxiliares.h"

#include "constantes.h"
#include "estruturas.h"
#include "funcsPerguntas.h"
#include "funcsEstudantes.h"
#include "funcsTreinos.h"

char menu(int nEstudantes, int nPerguntas, int nTreinosDecorrer, int nTreinosFeitos) {
	char opcao;
	printf("Numero de alunos: %d\tNumero de Perguntas: %d\n", nEstudantes, nPerguntas);
	printf("Quantidade de treinos realizados: %d\tQuantidade de treinos a decorrer: %d\n", nTreinosFeitos, nTreinosDecorrer);

	printf("Menu: \n");
	printf("P - Menu de Perguntas\n");
	printf("E - Menu de Estudantes\n");
	printf("T - Menu de Treinos\n");
	printf("G - Gravar dados\n");
	printf("L - Ler dados\n");
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
	vetorTreinos = NULL;

	int nTreinos = 0;

	tipoResposta *vetorRespostas;
	vetorRespostas = NULL;
	int nRespostas;

	int nTreinosFeitos;
	int nTreinosDecorrer;
	int i;

	char opcao;
	do {
		//Falta na funcão menu a quantidade de treinos realizados e a decorrer.
		nTreinosDecorrer =0;
		nTreinosFeitos = 0;
		if(nTreinos != 0)
		{
			for(i=0;i<nTreinos;i++)
			{
				if(vetorTreinos[i].estado == 0)
				{
					nTreinosDecorrer++;
				}
				if(vetorTreinos[i].estado == 1)
				{
					nTreinosFeitos++;
				}
			}
		}

		opcao = menu(nEstudantes,nPerguntas, nTreinosDecorrer, nTreinosFeitos);
		switch(opcao){
			case 'P': menuPerguntas(vetorPerguntas, &nPerguntas);
				break;
			case 'E': menuEstudantes(vetorEstudantes,&nEstudantes);
				break;
			case 'G': gravarFicheiroBinario(vetorEstudantes,nEstudantes,vetorPerguntas,nPerguntas);
				break;
			case 'L': lerFicheiroBinario(vetorEstudantes,&nEstudantes,vetorPerguntas,&nPerguntas);
				break;
			case 'T': vetorTreinos = menuTreinos(vetorTreinos, &nTreinos, vetorEstudantes, nEstudantes, vetorPerguntas, nPerguntas, vetorRespostas, &nRespostas);
				break;
			case 'S': break;
			default: printf("Opcao Invalida.\n");
		}
	} while(opcao!='S');
	return 0;
}
