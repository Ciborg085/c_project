#ifndef FUNCSESTUDANTES_H_INCLUDED
#define FUNCSESTUDANTES_H_INCLUDED

#include "estruturas.h"

void menuEstudantes(tipoEstudante vetorEstudantes[MAX_ESTUDANTES],int *nEstudantes,tipoTreino * vetorTreinos, int nTreinos, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas);
int procurarEstudante(tipoEstudante vetorEstudante[MAX_ESTUDANTES], int nEstudantes, int idEstudante);

#endif
