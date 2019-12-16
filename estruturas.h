#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#include "constantes.h"

typedef struct Data
{
	int dia, mes, ano;
} tipoData;

typedef struct Perguntas
{
	int id; //a designação tem que ser uma string
	char questao[MAX_STRING];
	char opcoes[N_OPCOES][MAX_STRING]; //4 opcoes
	int idProva;
	int respostaCorreta; //[1-4]
	int tipoPergunta;	//0 - Estrutura de controlo,1 - vetor,2 - ponteiro

} tipoPergunta;

typedef struct Estudante
{
	int id;
	char nome[MAX_STRING];
	int tipo;	//0 - normal, 1 - trabalhador, 2 - extraordinario
	int regime;	//0 - diurno, 1 - pos-laboral
	int turno;
} tipoEstudante;

typedef struct Resposta
{
	int id;
	char texto[MAX_STRING]; //em principio n é preciso
	int idPergunta;
	int opcaoEscolhida;
	int idTreino;
} tipoResposta;

typedef struct Treinos
{
	int id;		//auto-increment
	int idEstudante;
	int idProva;

	tipoData realizacao;
	int duracao; //segundos
	int estado; //0 - criado, 1 - concluido

	int quantPerguntas;
	int quantRespostasCorretas;
	int quantRespostasErradas;
	int classificacao;
} tipoTreinos;

#endif
