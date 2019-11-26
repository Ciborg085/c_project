#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "consts.h"
#include <time.h>


typedef struct Perguntas
{
	int id;
	char questao[MAX_STRING];
	char opcoes[MAX_STRING][3]; //4 opcoes
	int idProva;
	int respostaCorreta;
	int tipoPergunta;	//0 - Estrutura de controlo,1 - vetor,2 - ponteiro

} tipoPergunta;

typedef struct Estudante
{
	int id;
	char none[MAX_STRING];
	int tipo;	//0 - normal, 1 - trabalhador, 2 - extraordinario
	int regime;	//0 - diurno, 1 - pos-laboral
	int turno;
} tipoEstudante;

typedef struct Resposta
{
	int id;
	char texto[MAX_STRING];
	int idPergunta;
	int opcaoEscolhida;
	int idTreino;
} tipoResposta;

typedef struct Treinos
{
	int id;		//auto-increment
	int idEstudante;
	int idProva;

	tm realizacao;
	int duracao; //segundos
	int estado; //0 - criado, 1 - concluido

	int quantPerguntas;
	int quantRespostasCorretas;
	int quantRespostasErradas;
	int classificacao;
} tipoTreinos;


#endif
