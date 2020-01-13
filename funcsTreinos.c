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
		printf("Perguntas respondidas: %d\n", treino.nRespostas);
		printf("Respostas corretas: %d\n", treino.quantRespostasCorretas);
		printf("Respostas erradas: %d\n", treino.quantRespostasErradas);
		printf("Classificacao: %f\n\n", treino.classificacao);
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
	//TODO: Verificar quando nao ha provas disponiveis
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

char menuFiltroPerguntas(tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas) {
	int tipoPerguntaExiste, i,j;

	printf("Selecione o tipo de perguntas.\n");
	for(i=0; i<3; i++)
	{
		tipoPerguntaExiste = 0;
		for(j=0;j<nPerguntas;j++)
		{
			if(vetorPerguntas[j].tipoPergunta == i)
			{
				tipoPerguntaExiste = 1;
			}
		}
		if(tipoPerguntaExiste == 1)
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
	return toupper(lerChar("Opcao: "));
}

void escolherPerguntas(tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas, tipoTreino * novoTreino)
{
	char opcao;
	int filtro;
	int invalido = 1;
	int i,j;
	int perguntaEscolhida;
	int vetorPerguntasSelecionadas[MAX_PERGUNTAS] = {0}; //0- Nao selecionada 1- Selecionada
	int nPerguntasEscolhidas = 0;
	int posPerguntaSelecionada;
	int tipoDePerguntaExiste = 0;

	tipoResposta* novaResposta;

	novoTreino->nRespostas = 0;

	do
	{
		invalido =0;

		opcao = menuFiltroPerguntas(vetorPerguntas, nPerguntas);

		// Isto acontece pois se a introducao for invalida o codigo e repetido
		if(opcao=='C'){
			if(nPerguntasEscolhidas < MIN_RESPOSTAS) {
				printf("Selecione pelo menos 4 perguntas.\n\n");
				invalido =1;
			}
		}
		else{
			//aplicar filtro escolhido
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

			//TODO: Verificar pergunta pertence a prova
			do
			{
				for(i=0;i<nPerguntas; i++)
				{
					if(vetorPerguntas[i].tipoPergunta == filtro || filtro == -1)
					{
						if(vetorPerguntasSelecionadas[i] == 0)
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
				printf("-1 - Voltar\n");

				//TODO: Verificar se nao ha perguntas ou nao dar allow a selecionar pergunta escondida!
				// Com encontrarPergunta .tipo = filtro!
				//TODO: limpar isto.

				perguntaEscolhida = lerInteiro("Opcao: ", -1, nPerguntas-1);
				if(perguntaEscolhida != -1)
				{
					posPerguntaSelecionada = encontrarPergunta(vetorPerguntas, nPerguntas, perguntaEscolhida);
					if(posPerguntaSelecionada == -1)
					{
						printf("Pergunta nao encontrada.");
						invalido == 1;
					}
					else
					{
						if(vetorPerguntasSelecionadas[posPerguntaSelecionada] == 0){
							//Selecionar pergunta
							if(nPerguntasEscolhidas == MAX_RESPOSTAS)
							{
								printf("Chegou ao limite maximo de %d perguntas. Pergunta nao selecionada\n", MAX_RESPOSTAS);
							}
							else
							{
								nPerguntasEscolhidas++;
								vetorPerguntasSelecionadas[posPerguntaSelecionada] = 1;
							}
						}
						else
						{
							//De-selecionar pergunta
							vetorPerguntasSelecionadas[posPerguntaSelecionada] = 0;
							nPerguntasEscolhidas--;
						}

					}
				}
			} while(perguntaEscolhida != -1 || invalido == 1);
		}
	} while (!(opcao == 'C' && invalido == 0));

	//Adicionar as perguntas escolhidas
	for(i=0;i<nPerguntas;i++)
	{
		if(vetorPerguntasSelecionadas[i] == 1) {

			novoTreino->nRespostas++;

			novaResposta = &(novoTreino->respostas[novoTreino->nRespostas-1]);
			if(novoTreino->nRespostas == 0)
			{
				novaResposta->id = 0;
			}
			else
			{
				//Tirar da posicao anterior
				novaResposta->id = novaResposta[-1].id + 1;
			}
			novaResposta->idPergunta = i;
		}
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
	if(nTreinos == 0) {
		printf("Nao existem treinos para consultar.\n");
	}
	else {
		idProcura = lerInteiro("Insira o id do treino a consultar ",0,nTreinos-1);
		posTreino = encontrarTreino(vetorTreinos, nTreinos, idProcura);
		if(posTreino == -1) {
			printf("Nao existe um treino com esse id.");
		}
		else {
			mostrarTreino(vetorTreinos[posTreino]);
			mostrarPerguntasTreino(vetorTreinos[posTreino], vetorPerguntas, nPerguntas);
		}
	}


	//TODO: mostrar perguntas e respostas desse treino, com a resposta correta assinalada.
}

void realizarProva(tipoTreino * vetorTreinos, int nTreinos , tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas) {
	int idProcura, posTreino, i,j;
	tipoTreino * treino;
	tipoPergunta pergunta;

	if(nTreinos == 0) {
		printf("Nao existem treinos para realizar.\n");
	}
	else {
		idProcura = lerInteiro("Insira o id do treino a realizar ",0,nTreinos-1);
		posTreino = encontrarTreino(vetorTreinos, nTreinos, idProcura);
		if(posTreino == -1) {
			printf("Nao existe um treino com esse id.\n");
		}
		else {
			printf("DEBUG -> postreino %d", posTreino);
			if(vetorTreinos[posTreino].estado == 1) {
				printf("Esta prova ja foi realizada\n");
			}
			else{
				treino = &vetorTreinos[posTreino];

				printf("Insira a data de realizacao:");
				treino->dataRealizacao = lerData();

				treino->duracao = lerInteiro("Insira a duracao em minutos: ", 1, 3600);
				printf("DEBUG->treino->nRespostas %d",treino->nRespostas);
				treino->quantRespostasCorretas = 0;
				for(i=0;i<treino->nRespostas;i++) {
					pergunta = vetorPerguntas[treino->respostas[i].idPergunta];
					printf("\n\n");
					printf("Questao: %s\n", pergunta.questao);
					printf("Opcoes:\n");
					for(j=0; j<N_OPCOES;j++) {
						printf("Opcao %d: %s\n",j+1,pergunta.opcoes[j]);
					}
					printf("\n");
					treino->respostas[i].opcaoEscolhida = lerInteiro("Opcao Escolhida: ",1,4);

					if(treino->respostas[i].opcaoEscolhida == pergunta.respostaCorreta) {
						treino->quantRespostasCorretas++;
					}
				}
				treino->estado = 1;
				treino->quantRespostasErradas = treino->nRespostas-treino->quantRespostasCorretas;
				treino->classificacao = (100.0/treino->nRespostas)*(treino->quantRespostasCorretas - treino->quantRespostasErradas*0.25);
				printf("Treino realizado.");
				mostrarTreino(*treino);
			}
		}
	}
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

/*
	• Apresentar os seguintes dados estatísticos:
		Y- a tempo médio de resposta a uma pergunta,
		Y- quantidade de treinos realizados entre duas datas (indicadas pelo utilizador),
		Y- percentagem de treinos efetuados por cada prova,
TODO:o que está a baixxooooo
		pergunta com a maior quantidade de respostas erradas,
		e o tipo de perguntas com a menor percentagem de respostas corretas.

*/

void mostrarEstatisticas(tipoTreino *vetorTreinos, int nTreinos, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas)
{
	typedef struct
	{
		int key;
		int value;
	} node;

	float tempoMedio;
	int i,j,l,pos,k;
	int provas[4]= {0};
	float percProvas[4] = {0};
	int nTreinosRealizadosEntreDatas;
	int repetiu;
	int duracao, respostas;
	int nPerguntasErradas[MAX_PERGUNTAS]= {0};
	int idPerguntasErradas[MAX_PERGUNTAS]= {0};
	int nPerguntasNoVetor=0;
	int nTreinosRealizados=0;
	node *perguntasErradas = NULL;



	tipoData data1, data2;

	for(i=0;i<nTreinos;i++)
	{
		if(vetorTreinos[i].estado ==1)
		{
			nTreinosRealizados++;
		}
	}
	if(nTreinosRealizados != 0)
	{
		//tempo medio
		//tempo_medio = duracao/ perguntas
		for(i=0;i<nTreinos;i++)
		{
			if(vetorTreinos[i].estado == 1)
			{
				duracao += vetorTreinos[i].duracao;
				respostas += vetorTreinos[i].nRespostas;
			}
		}
		tempoMedio = (duracao/(nTreinos)) / respostas;
		printf("O Tempo medio de resposta a uma pergunta e de %d minutos.\n");

		//pergunta com maior quantidade de respostas erradas
		//tenho de comparar vetorTreinos[i].respostas[j].opcaoEscolhida com VetorPerguntas[i].respostaCorreta
		for(i=0;i<nTreinos;i++)
		{
			if(vetorTreinos[i].estado == 1)
			{
				for(j=0;j<vetorTreinos[i].nRespostas;j++)
				{
					pos = encontrarPergunta(vetorPerguntas, nPerguntas, vetorTreinos[i].respostas[j].idPergunta);
					if(pos != -1)
					{
						if(vetorTreinos[i].respostas[j].opcaoEscolhida != vetorPerguntas[pos].respostaCorreta)
						{
							repetiu=0;
							for(l=0;l<nPerguntasNoVetor;l++)
							{
								if(vetorTreinos[i].respostas[j].idPergunta == idPerguntasErradas[l])
								{
									(nPerguntasErradas[l])++;
									repetiu=1;
								}
							}
							if(repetiu == 0)
							{
								idPerguntasErradas[nPerguntasNoVetor] = vetorTreinos[i].respostas[j].idPergunta;
								(nPerguntasErradas[nPerguntasNoVetor])++;
								nPerguntasNoVetor++;
							}
						}
					}
				}
			}
		}

		//sort de um dicionario

		int cmpfunc (const void * a, const void * b) {
			int i = ((const node *)a)->value;
			int j = ((const node *)b)->value;
			return (j-i);
		}



		perguntasErradas = malloc(nPerguntasNoVetor*sizeof(node));

		for(i=0;i<nPerguntasNoVetor;i++)
		{
			perguntasErradas[i].key= idPerguntasErradas[i];
			perguntasErradas[i].value = nPerguntasErradas[i];
		}

		qsort(perguntasErradas, nPerguntasNoVetor, sizeof(node), cmpfunc);

		for(i=0;i<nPerguntasNoVetor;i++)
		{
			pos = encontrarPergunta(vetorPerguntas, nPerguntas, perguntasErradas[i].key);
			printf("ID:%d) Respostas Erradas:%d, Questao: \"%s\"\n", perguntasErradas[i].key, perguntasErradas[i].value, vetorPerguntas[pos].questao);
		}

		//quantidade de treinos realizados entre duas datas
		//verificar entre anos, entre meses e entre dias
		//TODO: n está a funcionar bem
		printf("\nQuantidade de treinos realizados entre duas datas:\n");
		printf("Ler primeira data\n");
		data1 = lerData();
		printf("Ler primeira data\n");
		data2 = lerData();

		if(!(data1.ano < data2.ano))
		{
			if(!(data1.mes < data2.mes))
			{
				if(!(data1.dia < data2.dia ))
				{
					printf("Erro: A data 2 e maior que a data1\n");
				}
			}
		}
		else
		{
			for(i=0;i<nTreinos;i++)
			{
				if(vetorTreinos[i].estado == 1)
				{
					if( data1.ano <= vetorTreinos[i].dataRealizacao.ano && data2.ano >= vetorTreinos[i].dataRealizacao.ano)
					{
						if( data1.mes <= vetorTreinos[i].dataRealizacao.mes && data2.mes >= vetorTreinos[i].dataRealizacao.mes)
						{
							if( data1.dia <= vetorTreinos[i].dataRealizacao.dia && data2.dia >= vetorTreinos[i].dataRealizacao.dia)
							{
								nTreinosRealizadosEntreDatas++;
							}
						}
					}
				}
			}
			printf("Foram feitos %d entre as datas que indicou\n", nTreinosRealizadosEntreDatas);
		}

		//percentagem de treinos efetuados por cada prova,
		for(i=0;i<nTreinos;i++)
		{
			provas[(vetorTreinos[i].idProva)-1]++;
		}
		printf("Foram realizados:\n\n");

		for(i=0;i<MAX_PROVAS;i++)
		{
			percProvas[i] = ((provas[i]/nTreinos)*100);
		}


		for(i=0;i<MAX_PROVAS;i++)
		{
			printf("%0.2f da prova %d \n",percProvas[i], i+1);
		}
	}
	else
	{
		printf("Nao existe provas realizadas.\n");
	}
}

tipoTreino *menuTreinos(tipoTreino *vetorTreinos, int *nTreinos, tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas) {
	char opcao;
	do {
		printf("\n\nGerir treinos:\n");
		printf("I - Inserir treinos\n");
		printf("L - Listar treinos\n");
		printf("C - Consultar treinos\n");
		printf("R - Realizar prova\n");
		printf("D - Remover Treino a decorrer\n");
		printf("E - Estatisticas\n");
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
			case 'R': realizarProva(vetorTreinos, *nTreinos, vetorPerguntas, nPerguntas);
				break;
			case 'D': removerTreino(vetorTreinos, nTreinos);
				break;
			case 'E': mostrarEstatisticas(vetorTreinos, *nTreinos, vetorPerguntas, nPerguntas);
				break;
			case 'S': break;
			default: printf("Opcao invalida\n");
		}
	} while(opcao != 'S');
	return vetorTreinos;
}
