#include "estruturas.h"
#include "constantes.h"
#include "funcoesAuxiliares.h"
#include <stdio.h>

void menuPerguntas(tipoPergunta perguntas[MAX_PERGUNTAS], int quantPerguntas) {
	char opcao;
	do {
		printf("Gerir perguntas:\n");
		printf("S - Sair para menu principal\n");
		printf("I - Inserir perguntas\n");

		opcao = toupper(lerChar("Opcao: "));
		switch(opcao) {
			case 'I': inserirPergunta(perguntas);
			case 'S': break;
			default: printf("Opcao invalida");
		}
	} while(opcao != 'S');
}

void inserirPergunta(tipoPergunta perguntas[MAX_PERGUNTAS], int *quantPerguntas) {
	// Verificacoes feitas;
	// Ja existe uma pergunta com a mesma questao
	// as opcoes sao repetidas
	// a prova chegou ao limite maximo de perguntas

	tipoPergunta novaPergunta;
	int i, j, invalido;

	// Gerar id automatico
	if(quantPerguntas == 0) {
		novaPergunta.id = 0;
	}
	else {
		novaPergunta.id = perguntas[(*quantPerguntas)-1].id + 1;
	}

	lerInteiro("Insira o numero de prova a que esta pergunta pertence: ", 1, MAX_PROVAS);

	do {
		invalido = 0;
		lerString("Insira a questao da pergunta: ", &(novaPergunta.questao), MAX_STRING);

		for(i=0; i<(*quantPerguntas);i++) {
			if(perguntas[i].questao == novaPergunta.questao) {
				invalido = 1;
				printf("Ja existe uma questao com a mesma pergunta.");
			}
		}
	} while(invalido == 1);
	invalido = 0;

	for(i=0; i<N_OPCOES;i++) {
		do {
			invalido = 0;
			lerString(
				sprintf("Insira a opcao %d: ", i+1),
				novaPergunta.opcoes[i],
				MAX_STRING
			);
			for(j=0; j<i;j++) {
				if(novaPergunta.opcoes[i] == novaPergunta.opcoes[j]) {
					invalido = 1;
					printf("Ja existe esta opcao na pergunta.");
				}
			}
		} while(invalido == 1);
	}




}
