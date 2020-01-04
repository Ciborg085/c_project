#include "estruturas.h"
#include "constantes.h"
#include "funcsAuxiliares.h"
#include "funcsEstudantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void mostrarTreino(tipoTreino treino) {
	printf("Id: %d\n", treino.id);
	printf("Prova: %d\n", treino.idProva);
	if(treino.estado==0) {
		printf("Estado: Nao realizado.\n");
	}
	else {
		printf("Estado: Concluido.\n");
		printf("Data de realizacao: %d/%d/%d\n", treino.dataRealizacao.mes, treino.dataRealizacao.mes, treino.dataRealizacao.ano);
		printf("Duracao: %d minutos\n",treino.duracao);
		printf("Perguntas respondidas: %d", treino.quantPerguntas);
		printf("Respostas corretas: %d", treino.quantRespostasCorretas);
		printf("Respostas erradas: %d", treino.quantRespostasErradas);
		printf("Classificacao: %d", treino.classificacao);
	}
}

void inserirIdEstudante(tipoTreino *treino, tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes) {
	int invalido,i, idInserido;
	do {
		invalido = 0;
		idInserido = lerInteiro("Insira o id do estudante: ", 0, nEstudantes - 1);

		if(procurarEstudante(vetorEstudantes, nEstudantes, idInserido) == -1) {
			invalido=1;
			printf("Nao existe um estudante com esse id.\n");
		}
	} while(invalido == 1);
	treino->idEstudante = idInserido;
}

int escolherProva(tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas)
{
	int opcao;
	int idProva, i,j;
	int nProvas[MAX_PROVAS]={0};
	int invalido=1;

	//ver quais as provas que estão disponiveis
	for(i=0;i<nPerguntas;i++)
	{
		j = vetorPerguntas[i].idProva;
		nProvas[j-1]++;
	}
	//listar as disponiveis
	printf("Provas disponiveis\n");
	for(i=0;i<4;i++)
	{
		if(nProvas[i] >= 4)
		{
			printf("%d) Prova %d\n", i+1, i+1);
		}
	}
	//selecionar uma das provas disponiveis
	do
	{

		//conversão de char para int
		//opcao = codigo ascii da opcao - 489
		//ex: opcao =1 , 490-489 = 1
		opcao = lerChar("opcao: ") -'0';
		printf("\n");

		if(opcao > MAX_PROVAS || opcao < 0)
		{
			printf("Opcao invalida.\n");
		}
		else
		{
			if (nProvas[opcao-1] >= 4)
			{
				invalido = 0;
			}
			else
			{
				printf("A prova que escolheu e invalida.\n");
			}
		}
	} while(invalido == 1);
	idProva = opcao;
	return idProva;
}

tipoResposta *escolherPerguntas(tipoResposta *vetorRespostas, int *nRespostas, tipoPergunta vetorPerguntas [MAX_PERGUNTAS], int nPerguntas, int idProva, int idTreino)
{
	tipoResposta *novoVetorRespostas;
	tipoResposta *novaResposta;
	char opcao;
	int filtro;
	int invalido = 1;
	int i,j;
	int perguntaEscolhida;
	int vetorIdPerguntas[MAX_RESPOSTAS];
	int nPerguntasEscolhidas = 0;
	int perguntaJaSelecionada = -1;
	int tipoDePerguntaExiste = 0;

	novoVetorRespostas = realloc(vetorRespostas,sizeof(tipoResposta)*((*nRespostas)+1));
	if(novoVetorRespostas == NULL)
	{
		printf("Nao existe espaco suficiente para adicionar mais uma respostas\n");
	}
	else
	{
		do {
				//menu principal com o que está a baixo
			printf("Selecione o tipo de perguntas.\n");
			//TODO: esconder tipos sem perguntas
			for(i=0; i<3; i++) {
				tipoDePerguntaExiste = 0;
				for(j=0;j<nPerguntas;j++) {
					if(vetorPerguntas[j].tipoPergunta == i) {
						tipoDePerguntaExiste = 1;
					}
				}
				if(tipoDePerguntaExiste == 1) {
					printf("%d) ", i);
					switch(i) {
						case 0: printf("Estrutura de controlo\n");
							break;
						case 1: printf("Vetores\n");
							break;
						case 2: printf("Ponteiros\n");
							break;
					}
				}
			}
			printf("T) Tudo\nC) Concluir\n");

			opcao = toupper(lerChar("Opcao: "));
			if(opcao != 'C') {
				do {
					if(opcao == 'T') {
						filtro = -1;
						invalido = 0;
					}
					else {
						// conversao char para int
						filtro = opcao - '0';
						if(filtro < 0 || filtro > 2) {
							printf("Opcao invalida.\n");
						}
						else {
							invalido = 0;
						}
					}
				} while(invalido == 1);
				printf("\n");
				do {
					for(i=0;i<nPerguntas; i++){
						if(vetorPerguntas[i].tipoPergunta == filtro || filtro == -1) {
							perguntaJaSelecionada = -1;
							for(j=0;j<nPerguntasEscolhidas;j++) {
								if(vetorIdPerguntas[j] == i) {
									perguntaJaSelecionada = 1;
								}
							}
							if(perguntaJaSelecionada == -1) {
								printf("[ ]");
							}
							else {
								printf("[X]");
							}
							printf("%d - %s\n", vetorPerguntas[i].id, vetorPerguntas[i].questao);
						}
					}
					// Verificar se nao ha perguntas ou nao dar allow a selecionar pergunta escondida!
					printf("-1 - Sair do menu\n");

					perguntaEscolhida = lerInteiro("Opcao: ", -1, nPerguntas-1);
					if(perguntaEscolhida != -1) {
						if(perguntaEscolhida >= nPerguntas || perguntaEscolhida < 0){
							printf("Numero invalido.");
							invalido == 1;
						}
						else {
							perguntaJaSelecionada = -1;
							for(i=0;i<nPerguntasEscolhidas;i++) {
								if(vetorIdPerguntas[i] == perguntaEscolhida) {
									perguntaJaSelecionada = i;
								}
							}

							if(perguntaJaSelecionada == -1) {
								if(nPerguntasEscolhidas == MAX_RESPOSTAS) {
									printf("Chegou ao limite maximo de %d perguntas. Pergunta nao selecionada\n", MAX_RESPOSTAS);
								}
								else {
									nPerguntasEscolhidas++;
									vetorIdPerguntas[nPerguntasEscolhidas-1] = perguntaEscolhida;
								}
							}
							else {
								//Remover de array
								for(i=perguntaJaSelecionada+1; i < nPerguntasEscolhidas; i++) {
									vetorIdPerguntas[i-1] == vetorIdPerguntas[i];
								}
								nPerguntasEscolhidas--;
							}

						}
					}
				} while(perguntaEscolhida != -1 || invalido == 1);
			}
		} while (opcao != 'C');

		//TODO: guardar no vetorRespostas com novo tamanho
	}
	// Escrever para vetorRespostas


		//em cada uma das opções vai criar um submenu que contem as perguntas do tipo selecionado para selecionar
		//as perguntas selecionadas são guardadas no vetor de ids e só depois de se selecionar tudo e concluir é quesão guardadas as seleções no vetorRespostas.

}

tipoTreino * criarTreino(tipoTreino *vetorTreinos, int *nTreinos, tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas, tipoResposta *vetorRespostas, int *nRespostas)
{
	tipoTreino *novoVetorTreinos;
	tipoTreino *novoTreino;
	void *vetorNulo;

	char opcao;
	int invalido = 0;

	if(nEstudantes==0) {
		printf("Nenhum estudante registado. Insira um estudante antes de criar uma prova.\n");
	}
	else
	{
		//Verificar se há memoria para criar um treino e 10 perguntas
		vetorNulo = malloc(sizeof(tipoTreino) + sizeof(tipoResposta)*10);
		if(vetorNulo == NULL)
		{
			printf("Nao existe espaco suficiente para adicionar mais um treino.");

		}
		else
		{

			//Como verificamos antes se há espaço, n é preciso verificar se é null agora
			novoVetorTreinos = realloc(vetorTreinos,sizeof(tipoTreino)*((*nTreinos)+1));
			vetorTreinos = novoVetorTreinos;

			(*nTreinos)++;
			novoTreino = &(vetorTreinos[(*nTreinos)-1]);

			// Gerar id automatico
			if(*nTreinos == 1)
			{
				novoTreino->id = 0;
			}
			else
			{
				novoTreino->id = novoTreino[-1].id + 1;
			}


			inserirIdEstudante(novoTreino, vetorEstudantes, nEstudantes);
			novoTreino->idProva = escolherProva(vetorPerguntas, nPerguntas);
			//tipo de perguntas (0,1,2 ou none)
			vetorRespostas = escolherPerguntas(vetorRespostas, nRespostas, vetorPerguntas, nPerguntas, novoTreino->idProva, novoTreino->id);

			//listar as perguntas da prova
			novoTreino->estado = 0;
			printf("Treino inserido.\n\n");
		}
	}

	return vetorTreinos;
}

void listarTreinos(tipoTreino *vetorTreinos, int nTreinos) {
	int i;

	if(nTreinos == 0) {
		printf("Nao existem treinos para mostrar");
	}
	else {
		for(i=0; i<nTreinos; i++) {
			mostrarTreino(vetorTreinos[i]);
			printf("\n");
		}
	}
}

int encontrarTreino(tipoTreino *vetorTreinos, int nTreinos, int idProcura) {
	// Se nao encontrar, devolver -1
	int encontrado = -1;
	int i;

	for(i=0; i<nTreinos && encontrado==-1;i++){
		if(vetorTreinos[i].id == idProcura) {
			encontrado = i;
		}
	}
	return encontrado;
}

void consultarTreino(tipoTreino *vetorTreinos, int nTreinos) {
	int idProcura, posPergunta;
	idProcura = lerInteiro("Insira o id do treino a consultar ",0,nTreinos);
	posPergunta = encontrarTreino(vetorTreinos, nTreinos, idProcura);
	if(posPergunta == -1) {
		printf("Nao existe um treino com esse id.");
	}
	else {
		mostrarTreino(vetorTreinos[posPergunta]);
	}

	//TODO: mostrar perguntas e respostas desse treino, com a resposta correta assinalada.
}


void menuTreinos(tipoTreino *vetorTreinos, int *nTreinos, tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas, tipoResposta *vetorRespostas, int *nRespostas) {
	char opcao;
	do {
		printf("\nGerir treinos:\n");
		printf("I - Inserir treinos\n");
		printf("L - Listar treinos\n");
		printf("C - Consultar treinos\n");
		printf("S - Sair para menu principal\n\n");

		opcao = toupper(lerChar("Opcao: "));
		printf("\n");
		switch(opcao) {
			case 'I': vetorTreinos = criarTreino(vetorTreinos, nTreinos, vetorEstudantes, nEstudantes, vetorPerguntas, nPerguntas, vetorRespostas, nRespostas);
				break;
			case 'L': listarTreinos(vetorTreinos, *nTreinos);
				break;
			case 'C': consultarTreino(vetorTreinos, *nTreinos);
				break;
			case 'S': break;
			default: printf("Opcao invalida\n");
		}
	} while(opcao != 'S');
}
