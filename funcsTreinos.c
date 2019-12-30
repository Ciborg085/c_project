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

void inserirIdEstudante(tipoTreino *treino, tipoEstudante estudantes[MAX_ESTUDANTES], int nEstudantes) {
	int invalido,i, idInserido;
	do {
		invalido = 0;
		idInserido = lerInteiro("Insira o id do estudante: ", 0, MAX_STRING);

		if(procurarEstudante(estudantes, nEstudantes, idInserido) == -1) {
			invalido=1;
			printf("Nao existe um estudante com esse id.\n");
		}
	} while(invalido == 1);
	treino->idEstudante = idInserido;
}

tipoTreino * criarTreino(tipoTreino *vetorTreinos, int *quantTreinos, tipoEstudante estudantes[MAX_ESTUDANTES], int nEstudantes) {
	tipoTreino *novoVetorTreinos;
	tipoTreino *novoTreino;

	if(nEstudantes==0) {
		printf("Nenhum estudante registado. Insira um estudante antes de criar uma prova.\n");
	}
	else {
		novoVetorTreinos = realloc(vetorTreinos,sizeof(tipoTreino)*((*quantTreinos)+1));
		if(novoVetorTreinos == NULL) {
			printf("Nao existe espaco suficiente para adicionar mais um treino.");
		}
		else {
			vetorTreinos = novoVetorTreinos;

			(*quantTreinos)++;
			novoTreino = &(vetorTreinos[(*quantTreinos)-1]);

			// Gerar id automatico
			if(*quantTreinos == 1) {
				novoTreino->id = 0;
			}
			else {
				novoTreino->id = novoTreino[-1].id + 1;
			}

			inserirIdEstudante(novoTreino, estudantes, nEstudantes);
			novoTreino->idProva = lerInteiro("Insira o numero de prova a que esta pergunta pertence", 1, MAX_PROVAS);
			novoTreino->estado = 0;
			printf("Treino inserido.\n\n");
		}
	}

	return vetorTreinos;
}

void listarTreinos(tipoTreino *treinos, int quantTreinos) {
	int i;

	if(quantTreinos == 0) {
		printf("Nao existem treinos para mostrar");
	}
	else {
		for(i=0; i<quantTreinos; i++) {
			mostrarTreino(treinos[i]);
			printf("\n");
		}
	}
}

int encontrarTreino(tipoTreino *treinos, int quantTreinos, int idProcura) {
	// Se nao encontrar, devolver -1
	int encontrado = -1;
	int i;

	for(i=0; i<quantTreinos && encontrado==-1;i++){
		if(treinos[i].id == idProcura) {
			encontrado = i;
		}
	}
	return encontrado;
}

void consultarTreino(tipoTreino *treinos, int quantTreinos) {
	int idProcura, posPergunta;
	idProcura = lerInteiro("Insira o id do treino a consultar ",0,1000);
	posPergunta = encontrarTreino(treinos, quantTreinos, idProcura);
	if(posPergunta == -1) {
		printf("Nao existe um treino com esse id.");
	}
	else {
		mostrarTreino(treinos[posPergunta]);
	}

	//TODO: mostrar perguntas e respostas desse treino, com a resposta correta assinalada.
}


void menuTreinos(tipoTreino *treinos, int *quantTreinos, tipoEstudante estudantes[MAX_ESTUDANTES], int nEstudantes) {
	char opcao;
	do {
		printf("\nGerir treinos:\n");
		printf("I - Inserir treinos\n");
		printf("L - Listar treinos\n");
		printf("C - Consultar treinos\n");
		printf("S - Sair para menu principal\n\n");

		opcao = toupper(lerChar("Opcao: "));
		switch(opcao) {
			case 'I': treinos = criarTreino(treinos, quantTreinos, estudantes, nEstudantes);
				break;
			case 'L': listarTreinos(treinos, *quantTreinos);
				break;
			case 'C': consultarTreino(treinos, *quantTreinos);
				break;
			case 'S': break;
			default: printf("Opcao invalida\n");
		}
	} while(opcao != 'S');
}
