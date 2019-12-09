#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "funcoesAuxiliares.h"
#include "estruturas.h"

// Acrescentada variavel controlo para repetir insercao se ao for inserido numero int
int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo)
{
	int numero, controlo;
	do
	{
		printf("%s (%d a %d) :", mensagem, minimo, maximo);
		controlo = scanf ("%d", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
		limpaBufferStdin();     //limpa todos os caracteres do buffer stdin (nomeadamente o \n)

		if (controlo == 0)
		{
			printf("Devera inserir um numero inteiro \n");
		}
		else
		{

			if(numero<minimo || numero>maximo)
			{
				printf("Numero invalido. Insira novamente:\n");
			}

		}
	}
	while(numero<minimo || numero>maximo || controlo ==0);

	return numero;
}

float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo)
{
	float numero;
	int controlo;
	do
	{
		printf("%s (%.2f a %.2f) :", mensagem, minimo, maximo);
		controlo = scanf ("%f", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
		limpaBufferStdin();

		if (controlo == 0)
		{
			printf("Devera inserir um numero decimal (float) \n");
		}
		else
		{

			if(numero<minimo || numero>maximo)
			{
				printf("Numero invalido. Insira novamente:\n");
			}

		}
	}
	while(numero<minimo || numero>maximo || controlo ==0);

	return numero;
}

void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres)
{
	int tamanhoString;

	do 			// Repete leitura caso sejam obtidas strings vazias
	{
		printf("%s", mensagem);
		fgets(vetorCaracteres, maximoCaracteres, stdin);

		tamanhoString = strlen(vetorCaracteres);

		if (tamanhoString == 1)
		{
			printf("Nao foram introduzidos caracteres!!! . apenas carregou no ENTER \n\n");  // apenas faz sentido limpar buffer se a ficarem caracteres
		}

	}
	while (tamanhoString == 1);

	if(vetorCaracteres[tamanhoString-1] != '\n')  // ficaram caracteres no buffer....
	{
		limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
	}
	else
	{
		vetorCaracteres[tamanhoString-1] = '\0'; 	//Elimina o \n da string armazenada em vetor
	}
}


char lerChar(char mensagem[MAX_STRING])
{
	char opcao;
	int controlo;
	do
	{
		printf("%s", mensagem);
		controlo = scanf(" %c", &opcao);
		limpaBufferStdin();

		if (controlo == 0)
		{
			printf("Apenas pode introduzir um caracter");
		}

	} while (controlo == 0);


	return opcao;
}

void limpaBufferStdin(void)
{
	char chr;
	do
	{
		chr = getchar();
	}
	while (chr != '\n' && chr != EOF);
}

tipoData lerData()
{
	tipoData data;
	int mesDias;
	data.ano = lerInteiro("Ano: ", 2000, 2020);
	data.mes = lerInteiro("Mes: ", 1, 12);
	switch(data.mes)
	{
	case 2:
		if ((data.ano % 400 == 0) || (data.ano % 4 == 0 && data.ano % 100 !=0))     //ano bissexto
		{
			mesDias = 29;
		}
		else
		{
			mesDias = 28;
		}

		break;
	case 4:
	case 6:
	case 9:
	case 11:
		mesDias = 30;
		break;
	default:
		mesDias = 31;
	}
	data.dia = lerInteiro("Dia: ", 1, mesDias);
	return data;
}

/*
   metodo = 0 => Nenhuma ordem
   metodo = 1 => Ordem Numerica
   metodo = 2 => Ordem Alfabética
*/
void listarVetor(char vetor[MAX_STRING][99], int nElementos,int metodo)
{
	int i;
	switch (metodo)
	{
		case 0:
			//simplesmente dar print ao vetor
			for(i=0;i<nElementos;i++)
			{
				printf("%s",vetor[i]);
			}
			break;
		case 1:
			for(i=0;i<nElementos;i++)
			{
				printf("%d: %s",i+1,vetor[i]);
			}
			break;
		case 2:

			break;
	}
}
