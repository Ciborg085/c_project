#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "funcoesAuxiliares.h"

int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo)
{
    int numero;
    printf("%s (%d a %d)\n", mensagem,minimo,maximo);
    do
    {
        scanf("%d", &numero);
		limparBufferStdin();
		if (numero < minimo || numero > maximo)
		{
			printf("Numero invalido. Insira novamente\n");
		}
    }
    while(numero < minimo || numero > maximo);
    return numero;
}

void limparBufferStdin(void)
{
	char lixo;
	do
	{
		lixo = getchar();
	}
	while (lixo != '\n' && lixo != EOF);
}

void lerString(char mensagem[MAX_STRING],
		char vetorCaracteres[MAX_STRING],
		int maximoCaracteres)
{
	int tamanhoString;
	printf("%s\n",mensagem);
	fgets(vetorCaracteres, maximoCaracteres, stdin);
	tamanhoString = strlen(vetorCaracteres);
	if (tamanhoString == 1)
	{
		printf("Nao introduzui caracteres");
	}
	if (vetorCaracteres[ tamanhoString - 1 ] == '\n')
	{
		vetorCaracteres[ tamanhoString - 1 ] == '\0';
	}
	else
	{
		limparBufferStdin();
	}
}
