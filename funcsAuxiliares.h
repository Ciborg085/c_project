#ifndef FUNCS_AUXILIARES_H_INCLUDED
#define FUNCS_AUXILIARES_H_INCLUDED

#include "constantes.h"
#include "estruturas.h"

int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo);
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo);
void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres);
char lerChar(char mensagem[MAX_STRING]);
void limpaBufferStdin(void);
tipoData lerData();
void listarVetor(char vetor[MAX_STRING][99], int nElementos,int metodo);

void gravarFicheiroBinario(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes,tipoPergunta vetorPerguntas[MAX_PERGUNTAS],int nPerguntas);
void lerFicheiroBinario(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int *nEstudantes, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int *nPerguntas);




#endif // FUNCS_AUXILIARES_H_INCLUDED
