#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "funcsAuxiliares.h"
#include "estruturas.h"

// 0 - data e menor 1 - data e maior
int dataEMaior(tipoData data, tipoData dataComparar) {
	int maior = 1;

	if(data.ano==dataComparar.ano) {
		if(data.mes==dataComparar.mes){
			if(data.dia<dataComparar.dia){
				maior = 0;
			}
		}
		else{
			if(data.mes<dataComparar.mes){
				maior = 0;
			}
		}
	}
	else{
		if(data.ano<dataComparar.ano){
			maior = 0;
		}
	}
	return maior;
}

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

void gravarFicheiroBinario(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes,tipoPergunta vetorPerguntas[MAX_PERGUNTAS],int nPerguntas, tipoTreino * vetorTreinos, int nTreinos)
{
    FILE *ficheiro;
    int res = 0;
		int tamanhoElementos = 0;

    ficheiro = fopen("dados.bin", "wb");
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir o ficheiro dados.bin.\n");
    }
    else
    {
		//Guardar nEstudantes
		tamanhoElementos++;
		res += fwrite(&nEstudantes, sizeof(int), 1, ficheiro);

		//Guardar o vetor estudantes
		tamanhoElementos+= nEstudantes;
		res += fwrite(vetorEstudantes, sizeof(tipoEstudante), nEstudantes, ficheiro);

		//Guardar numero de perguntas
		tamanhoElementos++;
		res += fwrite(&nPerguntas, sizeof(int),1, ficheiro);

		//Guardar vetor perguntas
		tamanhoElementos+=nPerguntas;
		res += fwrite(vetorPerguntas, sizeof(tipoPergunta), nPerguntas, ficheiro);

		//Guardar treinos
		tamanhoElementos++;
		res += fwrite(&nTreinos, sizeof(int),1,ficheiro);
		tamanhoElementos+=nTreinos;
		res += fwrite(vetorTreinos, sizeof(tipoTreino),nTreinos, ficheiro);

		if(res != tamanhoElementos)
		{
			printf("Erro ao escrever o ficheiro\n");
		}
		else {
			printf("Dados gravados com sucesso.\n");
		}

		res = fclose(ficheiro);
		if(res != 0)
		{
			printf("Erro ao fechar o ficheiro.\n");
		}
    }
}

//vetorTreinos e passado no return, o resto por parametro
tipoTreino * lerFicheiroBinario(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int *nEstudantes, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int *nPerguntas, int *nTreinos)
{
	tipoTreino * vetorTreinos;
	FILE *ficheiro;
	int res;
	ficheiro = fopen("dados.bin", "rb");
	if (ficheiro == NULL)
	{
		printf("Erro ao abrir o ficheiro dados.bin.\n");
	}
	else
	{
		//Ler numero Estudantes
		res = fread(nEstudantes, sizeof(int), 1, ficheiro);
		if(res != 1)
		{
			printf("Erro a ler o ficheiro.\n");
		}
		else
		{
		//Ler vetor estudantes
			res = fread(vetorEstudantes, sizeof(tipoEstudante), *nEstudantes, ficheiro);
			if(res != *nEstudantes)
			{
					printf("Erro ao ler o ficheiro.\n");
			}else
			{
				//Ler numero de perguntas
				res = fread(nPerguntas, sizeof(int),1, ficheiro);
				if(res != 1)
				{
					printf("Erro ao ler o ficheiro");
				}
				else
				{
					//Ler vetor perguntas
					res = fread(vetorPerguntas, sizeof(tipoPergunta), *nPerguntas, ficheiro);
					if(res != *nPerguntas)
					{
						printf("Erro ao ler o ficheiro");
					}
					else
					{
						res = fread(nTreinos, sizeof(int),1,ficheiro);
						if(res != 1)
						{
							printf("Erro ao ler o ficheiro");
						}
						else
						{
							vetorTreinos = malloc(sizeof(tipoTreino)*(*nTreinos));
							if(vetorTreinos==NULL)
							{
								printf("Erro ao ler o ficheiro");
							}
							else
							{
								res = fread(vetorTreinos, sizeof(tipoTreino), *nTreinos, ficheiro);
								if(res != *nTreinos)
								{
									printf("Erro ao ler o ficheiro");
								}
								else
								{
									printf("Dados lidos com sucesso.\n");
								}
							}
						}
					}
				}
			}
		}

		res = fclose(ficheiro);
		if(res!=0) {
			printf("Erro ao fechar o ficheiro.\n");
		}
		printf("\n");
	}
	return vetorTreinos;
}

