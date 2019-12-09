#ifndef FUNCSESTUDANTES_H_INCLUDED
#define FUNCSESTUDANTES_H_INCLUDED

#include "estruturas.h"


void menuEstudantes(void);
int procurarEstudante(tipoEstudante vetorEstudante[MAX_ESTUDANTES], int nEstudantes, int idEstudante);
void criarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int *nEstudantes);
void alterarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, int idEstudante);
void consultarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes,int pos);


#endif
