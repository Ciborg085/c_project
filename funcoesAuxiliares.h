#ifndef FUNCOESAUXILIARES_H_INCLUDED
#define FUNCOESAUXILIARES_H_INCLUDED

#define MAX_STRING 50

void limparBufferStdin(void);
int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo);

void lerString(char mensagem[MAX_STRING],char vetorCaracteres[MAX_STRING],int maximoCaracteres);
#endif // FUNCOESAUXILIARES_H_INCLUDED
