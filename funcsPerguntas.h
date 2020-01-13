#ifndef FUNCSPERGUNTAS_H_INCLUDED
#define FUNCSPERGUNTAS_H_INCLUDED

#include "estruturas.h"

void menuPerguntas(tipoPergunta perguntas[MAX_PERGUNTAS], int *quantPerguntas);
int encontrarPergunta(tipoPergunta perguntas[MAX_PERGUNTAS], int quantPerguntas, int idProcura);

void mostrarPergunta(tipoPergunta pergunta);
int encontrarPergunta(tipoPergunta perguntas[MAX_PERGUNTAS], int quantPerguntas, int idProcura);

#endif
