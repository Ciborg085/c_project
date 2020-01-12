#include "estruturas.h"
#include "constantes.h"
#include "funcsAuxiliares.h"
#include "funcsEstudantes.h"
#include "funcsPerguntas.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void mostrarTreino(tipoTreino treino)
{
	printf("Id: %d\n", treino.id);
	printf("Prova: %d\n", treino.idProva);
	if(treino.estado==0)
	{
		printf("Estado: Nao realizado.\n");
	}
	else
	{
		printf("Estado: Concluido.\n");
		printf("Data de realizacao: %d/%d/%d\n", treino.dataRealizacao.mes, treino.dataRealizacao.mes, treino.dataRealizacao.ano);
		printf("Duracao: %d minutos\n",treino.duracao);
		printf("Perguntas respondidas: %d", treino.quantPerguntas);
		printf("Respostas corretas: %d", treino.quantRespostasCorretas);
		printf("Respostas erradas: %d", treino.quantRespostasErradas);
		printf("Classificacao: %d", treino.classificacao);
	}
}

void mostrarPerguntasTreino(tipoTreino treino, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas)
{
	int i;
	printf("Perguntas:\n\n");
	for(i=0;i<treino.nRespostas;i++)
	{
		mostrarPergunta(vetorPerguntas[treino.respostas[i].idPergunta]);

		if(treino.estado == 1)
		{
			printf("Resposta Escolhida: %d\n", treino.respostas[i].opcaoEscolhida);
		}
		printf("\n");

	}
	printf("\n");
}

void inserirIdEstudante(tipoTreino *vetorTreinos, tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes)
{
	int invalido,i, idInserido;
	do
	{
		invalido = 0;
		idInserido = lerInteiro("Insira o id do estudante: ", 0, nEstudantes - 1);

		if(procurarEstudante(vetorEstudantes, nEstudantes, idInserido) == -1)
		{
			invalido=1;
			printf("Nao existe um estudante com esse id.\n");
		}
	} while(invalido == 1);
	vetorTreinos->idEstudante = idInserido;
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

void escolherPerguntas(tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas, tipoTreino * novoTreino)
{
	//TODO: temos de mudar os ids das respostas para a questão, e os ids das perguntas para a questão, sendo a unique key a questão ...
	char opcao;
	int filtro;
	int invalido = 1;
	int i,j;
	int perguntaEscolhida;
	int vetorIdPerguntas[MAX_RESPOSTAS];
	int nPerguntasEscolhidas = 0;
	int perguntaJaSelecionada = -1;
	int tipoDePerguntaExiste = 0;

	tipoResposta* novaResposta;

	novoTreino->nRespostas = 0;

	do
	{
		invalido =0;
		//menu principal com o que está a baixo
		printf("Selecione o tipo de perguntas.\n");
		//TODO: esconder tipos sem perguntas - DONE?
		for(i=0; i<3; i++)
		{
			tipoDePerguntaExiste = 0;
			for(j=0;j<nPerguntas;j++)
			{
				if(vetorPerguntas[j].tipoPergunta == i)
				{
					tipoDePerguntaExiste = 1;
				}
			}
			if(tipoDePerguntaExiste == 1)
			{
				printf("%d) ", i);
				switch(i)
				{
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
		if(opcao != 'C')
		{
			do
			{
				if(opcao == 'T')
				{
					filtro = -1;
					invalido = 0;
				}
				else
				{
					// conversao char para int
					filtro = opcao - '0';
					if(filtro < 0 || filtro > 2)
					{
						printf("Opcao invalida.\n");
					}
					else
					{
						invalido = 0;
					}
				}
			} while(invalido == 1);
			printf("\n");


			do
			{
				for(i=0;i<nPerguntas; i++)
				{
					if(vetorPerguntas[i].tipoPergunta == filtro || filtro == -1)
					{
						perguntaJaSelecionada = -1;
						for(j=0;j<nPerguntasEscolhidas;j++)
						{
							if(vetorIdPerguntas[j] == i)
							{
								perguntaJaSelecionada = 1;
							}
						}
						if(perguntaJaSelecionada == -1)
						{
							printf("[ ]");
						}
						else
						{
							printf("[X]");
						}
						printf("%d - %s\n", vetorPerguntas[i].id, vetorPerguntas[i].questao);
					}
				}
				//TODO: Verificar se nao ha perguntas ou nao dar allow a selecionar pergunta escondida!
				//TODO: limpar isto.
				printf("-1 - Voltar\n");

				perguntaEscolhida = lerInteiro("Opcao: ", -1, nPerguntas-1);
				if(perguntaEscolhida != -1)
				{
					if(perguntaEscolhida >= nPerguntas || perguntaEscolhida < 0)
					{
						printf("Numero invalido.");
						invalido == 1;
					}
					else
					{
						perguntaJaSelecionada = -1;
						for(i=0;i<nPerguntasEscolhidas;i++)
						{
							if(vetorIdPerguntas[i] == perguntaEscolhida)
							{
								perguntaJaSelecionada = i;
							}
						}

						if(perguntaJaSelecionada == -1)
						{
							if(nPerguntasEscolhidas == MAX_RESPOSTAS)
							{
								printf("Chegou ao limite maximo de %d perguntas. Pergunta nao selecionada\n", MAX_RESPOSTAS);
							}
							else
							{
								nPerguntasEscolhidas++;
								vetorIdPerguntas[nPerguntasEscolhidas-1] = perguntaEscolhida;
							}
						}
						else
						{
							//Remover de array
							for(i=perguntaJaSelecionada+1; i < nPerguntasEscolhidas; i++)
							{
								vetorIdPerguntas[i-1] == vetorIdPerguntas[i];
							}
							nPerguntasEscolhidas--;
						}

					}
				}
			} while(perguntaEscolhida != -1 || invalido == 1);
		}

		if(opcao == 'C' && nPerguntasEscolhidas < MIN_RESPOSTAS)
		{
			printf("Selecione pelo menos 4 perguntas.\n\n");
			invalido =1;
		}

	} while (!(opcao == 'C' && invalido == 0));

	//Adicionar as perguntas escolhidas
	for(i=0;i<nPerguntasEscolhidas;i++)
	{
		novoTreino->nRespostas++;

		novaResposta = &(novoTreino->respostas[novoTreino->nRespostas-1]);
		if(novoTreino->nRespostas == 0)
		{
			novaResposta->id = 0;
		}
		else
		{
			//novoTreino = &(vetorTreinos[(*nTreinos)-1]);
			//novoTreino->id = novoTreino[-1].id + 1;
			novaResposta->id = novaResposta[-1].id + 1;
		}
		novaResposta->idPergunta = vetorIdPerguntas[i];
	}
}

tipoTreino *criarTreino(tipoTreino *vetorTreinos, int *nTreinos, tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas)
{
	tipoTreino *novoVetorTreinos;
	tipoTreino *novoTreino;
	void *vetorNulo;

	char opcao;
	int invalido = 0;

	if(nEstudantes==0) {
		printf("Nenhum estudante registado. \nInsira um estudante antes de criar uma prova.\n");
	}
	else
	{
		novoVetorTreinos = realloc(vetorTreinos,sizeof(tipoTreino)*((*nTreinos)+1));
		if(vetorNulo == NULL)
		{
			printf("Nao existe espaco suficiente para adicionar mais um treino.");

		}
		else
		{

			//Como verificamos antes se há espaço, n é preciso verificar se é null agora
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

			escolherPerguntas(vetorPerguntas, nPerguntas, novoTreino);

			//TODO: listar as perguntas da prova
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

void consultarTreino(tipoTreino *vetorTreinos, int nTreinos, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas) {
	int idProcura, posTreino;
	idProcura = lerInteiro("Insira o id do treino a consultar ",0,nTreinos-1);
	//TODO: Isto n é posTreino em vez de posPergunta ?
	posTreino = encontrarTreino(vetorTreinos, nTreinos, idProcura);
	if(posTreino == -1) {
		printf("Nao existe um treino com esse id.");
	}
	else {
		mostrarTreino(vetorTreinos[posTreino]);
		mostrarPerguntasTreino(vetorTreinos[posTreino], vetorPerguntas, nPerguntas);
	}


	//TODO: mostrar perguntas e respostas desse treino, com a resposta correta assinalada.
}

tipoTreino * removerTreino(tipoTreino *vetorTreinos, int *nTreinos)
{
	tipoTreino *novoVetorTreinos;
	tipoTreino *novoTreino;
	int i;
	int pos;
	int opcao;
	int invalido = 0;
	int nTreinosDecorrer;
	int vetorTreinosDecorrer;

	if(*nTreinos == 0)
	{
		printf("Nao ha treinos para remover");
	}
	else
	{
		for(i=0;i<(*nTreinos);i++)
		{
			if(vetorTreinos[i].estado == 0)
			{
				nTreinosDecorrer++;
			}
		}

		if(nTreinosDecorrer == 0)
		{
			printf("Nao ha treinos a decorrer\n");
		}
		else
		{
			/*
				Y- printf a aos treinos que podem ser apagados
				Y- selecionar o treino para ser apagado
				Y- procurar o index do treino selecionado no vetor treinos
				Y- novoTreino = vetorTreinos[pos]
				Y- dar shift dos treinos que estão à frente do index (treino selecionado) para tras
				realloc
				(*nTreinos)--;
				return do novo vetor;
			*/

			for(i=0;i<(*nTreinos);i++)
			{
				if(vetorTreinos[i].estado == 0)
				{
					mostrarTreino(vetorTreinos[i]);
				}
			}
			do
			{
				printf("\n\nEscreva o id do treino que pretende eliminar\nEscreva -1 para Cancelar a operação\n");
				opcao = lerInteiro("Opcao: ",-1,(*nTreinos)-1);
				if (opcao != -1)
				{
					for(i=0;i<(*nTreinos);i++)
					{
						if(vetorTreinos[i].estado == 0)
						{
							if(opcao == vetorTreinos[i].id)
							{
								novoTreino = &vetorTreinos[i];
								pos = i;
							}
						}
					}
					if(opcao != novoTreino->id)
					{
						invalido =1;
					}
					else
					{
						novoVetorTreinos = vetorTreinos;
						invalido =0;
						/*
							for(i=perguntaJaSelecionada+1; i < nPerguntasEscolhidas; i++)
							{
								vetorIdPerguntas[i-1] == vetorIdPerguntas[i];
							}
							nPerguntasEscolhidas--;
						*/

						for(i=pos+1;i<(*nTreinos);i++)
						{
							novoVetorTreinos[i-1] = novoVetorTreinos[i];
						}
						(*nTreinos)--;
						novoVetorTreinos = realloc(vetorTreinos,sizeof(tipoTreino)*((*nTreinos)));
						vetorTreinos = novoVetorTreinos;
						printf("Treino eliminado\n");
					}
				}
				else
				{
					invalido =0;
					printf("Nenhum treino foi eliminado\n");
				}

			} while(invalido ==1);
		}
	}
	return vetorTreinos;
}

tipoTreino *menuTreinos(tipoTreino *vetorTreinos, int *nTreinos, tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas) {
	char opcao;
	do {
		printf("\nGerir treinos:\n");
		printf("I - Inserir treinos\n");
		printf("L - Listar treinos\n");
		printf("C - Consultar treinos\n");
		printf("D - Remover Treino a decorrer\n");
		printf("S - Sair para menu principal\n\n");

		opcao = toupper(lerChar("Opcao: "));
		printf("\n");
		switch(opcao) {
			case 'I': vetorTreinos = criarTreino(vetorTreinos, nTreinos, vetorEstudantes, nEstudantes, vetorPerguntas, nPerguntas);
				break;
			case 'L': listarTreinos(vetorTreinos, *nTreinos);
				break;
			case 'C': consultarTreino(vetorTreinos, *nTreinos, vetorPerguntas, nPerguntas);
				break;
			case 'D': removerTreino(vetorTreinos, nTreinos);
				break;
			case 'S': break;
			default: printf("Opcao invalida\n");
		}
	} while(opcao != 'S');
	return vetorTreinos;
}
