#ifndef FUNCSESTUDANTES_H_INCLUDED
#define FUNCSESTUDANTES_H_INCLUDED


void criarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int *nEstudantes, int *idEstudantes);
void alterarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, int idEstudante);
void consultarEstudante(tipoEstudante vetorEstudante[MAX_ESTUDANTES], int nEstudantes);
void procurarEstudante(tipoEstudante vetorEstudante[MAX_ESTUDANTES], int nEstudantes, int idEstudante);



#endif
