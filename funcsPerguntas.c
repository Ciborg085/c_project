#include "estruturas.h"
#include "constantes.h"
#include "funcsAuxiliares.h"
#include <stdio.h>
#include <ctype.h>

void inserirQuestao(tipoPergunta perguntas[MAX_PERGUNTAS], int quantPerguntas, tipoPergunta *pergunta) {
	int invalido,i;
	do {
		invalido = 0;
		lerString("Insira a questao da pergunta: ", pergunta->questao, MAX_STRING);

		//Verificar se existe uma pergunta com a mesma questao
		for(i=0; i<quantPerguntas;i++) {
			if(perguntas[i].questao == pergunta->questao) {
				invalido = 1;
				printf("Ja existe uma questao igual.");
			}
		}
	} while(invalido == 1);
	invalido = 0;
}

void inserirIdProva(tipoPergunta perguntas[MAX_PERGUNTAS], int quantPerguntas, tipoPergunta *pergunta){
	int idProvaInserido, i, perguntasNaProva = 0;
	int invalido = 0;
	// Nao criar mais perguntas numa prova do que o numero maximo de respostas
	do {
		invalido = 0;
		idProvaInserido = lerInteiro("Insira o numero de prova a que esta pergunta pertence", 1, MAX_PROVAS);
		for(i = 0; i<quantPerguntas; i++){
			if(perguntas[i].idProva == idProvaInserido) {
				perguntasNaProva++;
			}
		}
		if(perguntasNaProva+1>MAX_RESPOSTAS){
			printf("Nao e possivel criar mais perguntas nesta prova. Insira novamente.");
			invalido = 1;
		}
		else {
			pergunta->idProva = idProvaInserido;
		}
	} while(invalido == 1);
}

void inserirOpcoes(tipoPergunta *pergunta) {
	int i, j, invalido;
	char msgOpcoes[MAX_STRING];

	for(i=0; i<N_OPCOES;i++) {
		do {
			invalido = 0;
			sprintf(msgOpcoes, "Insira a opcao %d: ", i+1),
			lerString(
				msgOpcoes,
				pergunta->opcoes[i],
				MAX_STRING
			);
			// Verificar nao existem opcoes repetidas
			for(j=0; j<i;j++) {	//	// a prova chegou ao limite maximo de perguntas	// a prova chegou ao limite maximo de perguntas	// a prova chegou ao limite maximo de perguntas a prova chegou ao limite maximo de perguntas
				if(pergunta->opcoes[i] == pergunta->opcoes[j]) {
					invalido = 1;
					printf("Ja existe esta opcao na pergunta.");
				}
			}
		} while(invalido == 1);
	}
}

void inserirRespostaCorreta(tipoPergunta *pergunta) {
	pergunta->respostaCorreta = lerInteiro("Insira a resposta correta",1,N_OPCOES);
}

void inserirTipoPergunta(tipoPergunta *pergunta) {
	printf("Tipos de perguntas:\n");
	printf("0 - Estrutura de controlo.\n");
	printf("1 - Vetor\n");
	printf("2 - Ponteiro\n");
	pergunta->tipoPergunta = lerInteiro("\nInsira o tipo desta pergunta ",0,2);
}

void inserirPergunta(tipoPergunta perguntas[MAX_PERGUNTAS], int *quantPerguntas) {
	tipoPergunta novaPergunta;

	if(*quantPerguntas == MAX_PERGUNTAS) {
		printf("Nao existe espaco para mais perguntas.");
	}
	else {
		// Gerar id automatico
		if(*quantPerguntas == 0) {
			novaPergunta.id = 0;
		}
		else {
			novaPergunta.id = perguntas[(*quantPerguntas)-1].id + 1;
		}

		inserirIdProva(perguntas,*quantPerguntas, &novaPergunta);
		inserirQuestao(perguntas,*quantPerguntas, &novaPergunta);
		inserirOpcoes(&novaPergunta);
		inserirRespostaCorreta(&novaPergunta);
		inserirTipoPergunta(&novaPergunta);

		(*quantPerguntas)++;
		perguntas[(*quantPerguntas)-1] = novaPergunta;

		printf("\nPergunta inserida.\n\n");
	}
}

void mostrarPergunta(tipoPergunta pergunta) {
	int i;
	printf("Id: %d\n", pergunta.id);
	printf("Prova: %d\n", pergunta.idProva);
	printf("Tipo de pergunta: ");
	switch(pergunta.tipoPergunta) {
		case 0: printf("Estrutura de controlo\n");
			break;
		case 1: printf("Vetor\n");
			break;
		case 2: printf("Ponteiro\n");
			break;
	}
	printf("Questao: %s\n", pergunta.questao);
	for(i=0; i<N_OPCOES;i++) {
		printf("Opcao %d: %s\n",i,pergunta.opcoes[i]);
	}
	printf("Resposta Correta: %d\n", pergunta.respostaCorreta);

}

void listarPerguntas(tipoPergunta perguntas[MAX_PERGUNTAS], int quantPerguntas) {
	int i;

	if(quantPerguntas == 0) {
		printf("Nao existem perguntas para mostrar");
	}
	else {
		for(i=0; i<quantPerguntas; i++) {
			mostrarPergunta(perguntas[i]);
			printf("\n");
		}
	}
}

int encontrarPergunta(tipoPergunta perguntas[MAX_PERGUNTAS], int quantPerguntas, int idProcura) {
	// Se nao encontrar, devolver -1
	int encontrado = -1;
	int i;

	for(i=0; i<quantPerguntas && encontrado==-1;i++){
		if(perguntas[i].id == idProcura) {
			encontrado = i;
		}
	}
	return encontrado;
}

void consultarPergunta(tipoPergunta perguntas[MAX_PERGUNTAS], int quantPerguntas) {
	int idProcura, posPergunta;
	if(quantPerguntas == 0) {
		printf("Nao existem perguntas para consultar.\n");
	}
	else {
		idProcura = lerInteiro("Insira o id da pergunta a consultar ",0,quantPerguntas);
		posPergunta = encontrarPergunta(perguntas, quantPerguntas, idProcura);
		if(posPergunta == -1) {
			printf("Nao existe uma pergunta com esse id.");
		}
		else {
			mostrarPergunta(perguntas[posPergunta]);
		}
	}
}

void alterarPergunta(tipoPergunta perguntas[MAX_PERGUNTAS], int quantPerguntas) {
	int idPergunta, posProcura, i;
	tipoPergunta pergunta;
	char opcao;

	idPergunta = lerInteiro("Insira o id da pergunta a alterar ",0,1000);
	posProcura = encontrarPergunta(perguntas, quantPerguntas, idPergunta);
	if(posProcura == -1) {
		printf("Nao existe uma pergunta com esse id.");
	}
	else {
		pergunta = perguntas[posProcura];
		mostrarPergunta(pergunta);
		printf("Que campo deseja alterar?\n");
		printf("Q - Questao\n");
		printf("O - Opcoes\n");
		printf("P - Prova\n");
		printf("R - Resposta correta\n");
		printf("T - Tipo de pergunta\n");
		printf("S - Sair");

		opcao = toupper(lerChar("Opcao: "));
		switch(opcao) {
			case 'Q': inserirQuestao(perguntas, quantPerguntas, &pergunta);
				break;
			case 'O': inserirOpcoes(&pergunta);
				break;
			case 'P': inserirIdProva(perguntas, quantPerguntas, &pergunta);
				break;
			case 'R': inserirRespostaCorreta(&pergunta);
				break;
			case 'T': inserirTipoPergunta(&pergunta);
				break;
			case 'S': break;
			default: printf("Opcao invalida");
		}
		// Guardar novos dados
		perguntas[posProcura] = pergunta;

	}
}

void menuPerguntas(tipoPergunta perguntas[MAX_PERGUNTAS], int *quantPerguntas) {
	char opcao;
	do {
		printf("\nGerir perguntas:\n");
		printf("I - Inserir perguntas\n");
		printf("L - Listar perguntas\n");
		printf("C - Consultar pergunta\n");
		printf("A - Alterar pergunta\n");
		printf("S - Sair para menu principal\n\n");

		opcao = toupper(lerChar("Opcao: "));
		switch(opcao) {
			case 'I': inserirPergunta(perguntas, quantPerguntas);
				break;
			case 'L': listarPerguntas(perguntas, *quantPerguntas);
				break;
			case 'C': consultarPergunta(perguntas, *quantPerguntas);
				break;
			case 'A': alterarPergunta(perguntas, *quantPerguntas);
				break;
			case 'S': break;
			default: printf("Opcao invalida\n");
		}
	} while(opcao != 'S');
}
