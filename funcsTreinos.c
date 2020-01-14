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

void logTreino(tipoTreino treino, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas) {
	int i;

	escreverLog("Id: %d\nProva: %d\n", treino.id, treino.idProva);
	if(treino.estado==0)
	{
		escreverLog("Estado: Nao realizado.\n");
	}
	else
	{
		escreverLog("Estado: Concluido.\n");
		escreverLog("Data de realizacao: %d/%d/%d\n", treino.dataRealizacao.mes, treino.dataRealizacao.mes, treino.dataRealizacao.ano);
		escreverLog("Duracao: %d minutos\n",treino.duracao);
		escreverLog("Perguntas respondidas: %d\n", treino.nRespostas);
		escreverLog("Respostas corretas: %d\n", treino.quantRespostasCorretas);
		escreverLog("Respostas erradas: %d\n", treino.quantRespostasErradas);
		escreverLog("Classificacao: %f\n\n", treino.classificacao);
	}

	escreverLog("Perguntas:\n\n");
	for(i=0;i<treino.nRespostas;i++)
	{
		mostrarPergunta(vetorPerguntas[treino.respostas[i].idPergunta]);

		if(treino.estado == 1)
		{
			escreverLog("Resposta Escolhida: %d\n", treino.respostas[i].opcaoEscolhida);
		}
	}
	escreverLog("\n");
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
	int i;
	int nProvas[3] = {0};
	int existemProvas =0;

	char opcao;
	int invalido = 0;

	printf("DEBUG: nTreinos:", *nTreinos);
	if(nEstudantes==0) {
		printf("Nenhum estudante registado. \nInsira um estudante antes de criar uma prova.\n");
	}
	else
	{
		for(i=0;(i<nPerguntas || existemProvas == 1);i++) {
			nProvas[vetorPerguntas[i].idProva-1]++;
			if(nProvas[vetorPerguntas[i].idProva-1] == 4) {
				existemProvas=1;
			}
		}
		if(existemProvas==0) {
			printf("Nao existem provas com tamanho minimo de perguntas (%d)",MIN_RESPOSTAS);
		}
		else{
			novoVetorTreinos = realloc(vetorTreinos,sizeof(tipoTreino)*((*nTreinos)+1));
			if(novoVetorTreinos == NULL)
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
			if(vetorTreinos[posTreino].estado == 1) {
				printf("Esta prova ja foi realizada\n");
			}
			else{
				treino = &vetorTreinos[posTreino];

				printf("Insira a data de realizacao:");
				treino->dataRealizacao = lerData();

				treino->duracao = lerInteiro("Insira a duracao em minutos: ", 1, 3600);
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
				logTreino(*treino, vetorPerguntas, nPerguntas);
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
	int nTreinosDecorrer = 0;
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

void tempoMedio(tipoTreino *vetorTreinos, int nTreinos)
{
	int duracao=0, respostas=0;
	float tempoMedio;
	int i;

	//tempo_medio = duracao/ perguntas
	for(i=0;i<nTreinos;i++)
	{
		if(vetorTreinos[i].estado == 1)
		{
			duracao += vetorTreinos[i].duracao;
			respostas += vetorTreinos[i].nRespostas;
		}
	}
	if (respostas != 0)
	{
		tempoMedio = (duracao/nTreinos) / respostas;
		printf("O Tempo medio de resposta a uma pergunta e de %0.2f minutos.\n", tempoMedio);
	}
}

void nTreinosEntreDatas(tipoTreino *vetorTreinos, int nTreinos)
{
	int i;
	tipoData data1,data2;
	int nTreinosRealizadosEntreDatas=0;

	printf("\nQuantidade de treinos realizados entre duas datas:\n");
	printf("Ler primeira data\n");
	data1 = lerData();
	printf("\nLer segunda data\n");
	data2 = lerData();

	if(dataEMaior(data1,data2)==1)
	{
		printf("A primeira data e maior que a segunda data");
	}
	else
	{
		for(i=0;i<nTreinos;i++)
		{
			if(vetorTreinos[i].estado == 1)
			{
				if(dataEMaior(vetorTreinos[i].dataRealizacao, data1) == 1 && dataEMaior(data2, vetorTreinos[i].dataRealizacao))
				{
					nTreinosRealizadosEntreDatas++;
				}
			}
		}
		printf("\nForam feitos %d entre as datas que indicou\n\n", nTreinosRealizadosEntreDatas);
	}
}

void perguntaMaisErrada(tipoTreino *vetorTreinos, int nTreinos, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas, int nPerguntasErradas[MAX_PERGUNTAS])
{
	int nPerguntasNoVetor=0;
	int idPerguntaMaisErrada=0;
	int nPerguntaMaisErrada=0;
	int pos;
	int repetiu=0;
	int i,j;

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
						nPerguntasErradas[pos]++;
					}
				}
			}
		}
	}
	for(i=0;i<nPerguntas;i++)
	{
		if(nPerguntasErradas[i] > nPerguntaMaisErrada)
		{
			nPerguntaMaisErrada = nPerguntasErradas[i];
			idPerguntaMaisErrada = vetorPerguntas[i].id;
		}
	}

	pos = encontrarPergunta(vetorPerguntas, nPerguntas, idPerguntaMaisErrada);
	printf("\nA pergunta mais errada:%s\n ID) %d, Respostas erradas: %d\n\n", vetorPerguntas[pos].questao, idPerguntaMaisErrada, nPerguntaMaisErrada);
}

void percTreinosPorProva(tipoTreino *vetorTreinos, int nTreinos)
{
	int provas[4]= {0};
	float percProvas[4] = {0};
	int i;

	for(i=0;i<nTreinos;i++)
	{
		//tenho de colocar o -1 por que as provas sao de 1 a 4 e o array provas vai de 0 a 3
		provas[(vetorTreinos[i].idProva)-1]++;
	}
	printf("Foram realizados:\n\n");
	for(i=0;i<MAX_PROVAS;i++)
	{
		percProvas[i] = ((provas[i]/nTreinos)*100);
		printf("%0.2f da prova %d \n",percProvas[i], i+1);
	}
}

void mostrarEstatisticas(tipoTreino *vetorTreinos, int nTreinos, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas)
{
	int i,j,pos;
	int nTreinosRealizados=0;


	int totalTipoPerguntas[3] = {0};
	int tipoPerguntasCertas[3] = {0};
	int tipoPerguntasErradas[3] = {0};

	int nPerguntasErradas[MAX_PERGUNTAS] = {0};
	float menorPercTipoPerguntaRespostasCorretas;
	int tipoPerguntaMenorRespostasCorretas;


	for(i=0;i<nTreinos;i++)
	{
		if(vetorTreinos[i].estado == 1)
		{
			nTreinosRealizados++;
		}
	}
	if(nTreinosRealizados !=0)
	{

		//tempo médio de resposta a uma pergunta
		tempoMedio(vetorTreinos, nTreinos);


		//quantidade de treinos realizados entre duas datas
		nTreinosEntreDatas(vetorTreinos,nTreinos);

		//pergunta com maior quantidade de respostas erradas
		//tenho de comparar vetorTreinos[i].respostas[j].opcaoEscolhida com VetorPerguntas[i].respostaCorreta

		//pergunta com a maior quantidade de respostas erradas
 		perguntaMaisErrada(vetorTreinos, nTreinos, vetorPerguntas, nPerguntas, nPerguntasErradas);

		//percentagem de treinos efetuados por cada prova,
		percTreinosPorProva(vetorTreinos,nTreinos);

		/*
			o tipo de perguntas com a menor percentagem de respostas corretas.
			vou reutilizador os arrays idPerguntasErradas para agora guardar o tipo de pergunta que é, sendo esse tipo um integer.
			e o nPerguntasErradas vai ser utilizado para guardar o numero de perguntas erradas para um tipo
		*/

		// o tipo de pergunta com a menor percentagem de respostas corretas.

		for(i=0;i<nTreinos;i++)
		{
			for(j=0;i<vetorTreinos[i].nRespostas;i++)
			{
				pos = encontrarPergunta(vetorPerguntas, nPerguntas, vetorTreinos[i].respostas[j].idPergunta);
				totalTipoPerguntas[vetorPerguntas[pos].tipoPergunta]++;
			}
		}
		for(i=0;i<nPerguntas;i++)
		{
			//Agrupa as respostas erradas por tipo de pergunta no vetor tipoPerguntasErradas
			tipoPerguntasErradas[vetorPerguntas[i].tipoPergunta] += nPerguntasErradas[i];
		}
		for(i=0;i<3;i++)
		{
			if(totalTipoPerguntas[i] != nPerguntasErradas[i])
			{
				tipoPerguntasCertas[i] = totalTipoPerguntas[i] - nPerguntasErradas[i];
			}
		}
		for(i=0;i<3;i++)
		{
			if(totalTipoPerguntas != 0)
			{
				if(i==0)
				{
					menorPercTipoPerguntaRespostasCorretas = ((float)tipoPerguntasCertas[i]/(float)totalTipoPerguntas[i])*100;
				}
				if(menorPercTipoPerguntaRespostasCorretas > ((float)tipoPerguntasCertas[i]/(float)totalTipoPerguntas[i])*100)
				{
					menorPercTipoPerguntaRespostasCorretas = ((float)tipoPerguntasCertas[i]/totalTipoPerguntas[i])*100;
					tipoPerguntaMenorRespostasCorretas = i;
				}
			}
			//Como pode dar numeros negativos coloquei if.
			if(menorPercTipoPerguntaRespostasCorretas < 0)
			{
				menorPercTipoPerguntaRespostasCorretas = 0.0;
			}
		}
		switch(tipoPerguntaMenorRespostasCorretas)
		{
			case 0:
				printf("O tipo de pergunta com menor percentagem de respostas corretas e a Estrutura de controlo com : %0.2f %% de respostas corretas.\n", menorPercTipoPerguntaRespostasCorretas);
				break;
			case 1:
				printf("O tipo de pergunta com menor percentagem de respostas corretas e o Vetor com : %0.2f %% de respostas corretas.\n", menorPercTipoPerguntaRespostasCorretas);
				break;
			case 2:
				printf("O tipo de pergunta com menor percentagem de respostas corretas e o Ponteiro com : %0.2f %% de respostas corretas.\n", menorPercTipoPerguntaRespostasCorretas);
				break;
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
