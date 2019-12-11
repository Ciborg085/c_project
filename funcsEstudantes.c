#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "funcoesAuxiliares.h"
#include "constantes.h"
#include "estruturas.h"
#include "funcsEstudantes.h"

/*PRECISO DE REVER ESTE FICHEIRO PARA VER O QUE FALTA
	Suspeito que no alterarEstudante() está alguma coisa mal com os loops,etc


	Relembrando que depois de o utilizador alterar dados, o programa deveria voltar para o menu de escolher o que alterar!!!
*/


/*
	Criar funcionario

	verificar se nEstudantes chegou ao MAX
	criar id
	pedir e guardar nome
	" "	  "  " "	tipo
	" "   "	"	"	regime
	" "   "	"	"	turno
	incrementar nEstudantes ao criar o estudante

Notas:
	Temos de discutir o que faz mais sentido, devolver o nEstudantes ou o idEstudantes pelo return
	ou-
	devolver o nEstudantes e/ou o idEstudantes.

	Secalhar deviamos tentar incrementar o nEstudantes antes para que o nEstudantes n fique maior que o max depois que a função acabar
*/
void mostrarEstudante(tipoEstudante vetorEstudantes)
{
	printf("Id: %d\n",vetorEstudantes.id);
	printf("Nome: %s\n",vetorEstudantes.nome);
	switch(vetorEstudantes.tipo)
	{
		case 0:
			printf("Tipo: Normal\n");
			break;
		case 1:
			printf("Tipo: Trabalhador\n");
			break;
		case 2:
			printf("Tipo: Extraordinario\n");
			break;
	}

	switch(vetorEstudantes.regime)
	{
		case 0:
			printf("Regime: Diurno\n");
			break;
		case 1:
			printf("Regime: Pos-Laboral\n");
	}
	printf("Turno: %d",vetorEstudantes.turno);

	/*Ainda falta o resto
		W.I.P
		sendo o resto,
	*/
}


int procurarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, int idEstudante)
{
	int i,pos=-1;
	for(i=0;i<nEstudantes;i++)
	{
		if(idEstudante == vetorEstudantes[i].id)
		{
			pos = i;
			i = nEstudantes;
		}
	}
	return pos;
}

void criarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int *nEstudantes)
{

	if ((*nEstudantes)+1 >= MAX_ESTUDANTES)
	{
		printf("Chegou ao numero maximo de estudantes.");

	}
	else
	{
		if (*nEstudantes == 0)
		{
			vetorEstudantes[*nEstudantes].id = 0;
		}
		else
		{
			vetorEstudantes[*nEstudantes].id = vetorEstudantes[(*nEstudantes-1)].id+1;
		}

		lerString("Nome do estudante: ",vetorEstudantes[*nEstudantes].nome,255);
		printf("\n");
		vetorEstudantes[*nEstudantes].tipo = lerInteiro("Tipos: 0 - Normal,\t1 - Trabalhador,\t2 - Extraordinario\n",0,2);
		printf("\n");
		vetorEstudantes[*nEstudantes].regime = lerInteiro("Regimes: 0 - diurno,\t1 - Pos-laboral\n",0,1);
		printf("\n");
		vetorEstudantes[*nEstudantes].turno = lerInteiro("Turno:",1,10);
		printf("\n");
	}
	(*nEstudantes)++;
}

/*
	Alterar os dados do estudante

	Deveriamos dar a opção de deixar o utilizador apenas mudar

	Esta função pode ser optimizada, mas por enquanto fica assim,
	e provavelmente vamos ter que o fazer.


	POR FAVOR N OLHAR PARA O CODIGO ABAIXO!!
	ESTÁ FEIO!!

	W.I.P

*/

void alterarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, int idEstudante)
{
	int opcao,subopcao;
	int pos;

	pos = procurarEstudante(vetorEstudantes,nEstudantes,idEstudante);
	if(pos == -1)
	{
		printf("O aluno que introduzio nao existe\n");
	}
	else
	{
		do
		{
			opcao = -1;
			//consultarEstudante(vetorEstudante,nEstudantes,pos);
			//PRINTS----------------
			printf("1) Nome: %s\n",vetorEstudantes[pos].nome);
			switch(vetorEstudantes[pos].tipo)
			{
				case 0:
					printf("2) Tipo: Normal\n");
					break;
				case 1:
					printf("2) Tipo: Trabalhador\n");
					break;
				case 2:
					printf("2) Tipo: Extraordinario\n");
					break;
			}

			switch(vetorEstudantes[pos].regime)
			{
				case 0:
					printf("3) Regime: Diurno\n");
					break;
				case 1:
					printf("3) Regime: Pos-Laboral\n");
			}
			printf("4) Turno: %d\n",vetorEstudantes[pos].turno);
			printf("5) Tudo\n");
			printf("6) Sair\n");
			//---------------------------------
			opcao = lerInteiro("Opcao: ",1,6);
			printf("\n\n");

			switch(opcao)
			{
				case 1:
					printf("1) Nome: %s\n",vetorEstudantes[pos].nome);
					lerString("=> ",vetorEstudantes[pos].nome,MAX_STRING);
					break;
				case 2:
					/*
					switch(vetorEstudantes[pos].tipo)
					{
						case 0:
							printf("2) Tipo: Normal\n");
							break;
						case 1:
							printf("2) Tipo: Trabalhador\n");
							break;
						case 2:
							printf("2) Tipo: Extraordinario\n");
							break;
					}
					*/
					printf("0 - Normal\t1 - Trabalhador\t2 - Extraordinario\n");
					vetorEstudantes[pos].tipo = lerInteiro("Tipo: ",0,2);
					printf("\n");
					break;
				case 3:
					/*
					switch(vetorEstudantes[pos].regime)
						{
							case 0:
								printf("0) Regime: Diurno\n");
								break;
							case 1:
								printf("1) Regime: Pos-Laboral\n");
								break;
							default:
								printf("Opcao invalida");
						}
					*/
					printf("0 - Diurno\t1 - Pos-Laboral\n");
					vetorEstudantes[pos].tipo = lerInteiro("Regime: ",0,1);
					printf("\n");
					break;
				case 4:
					vetorEstudantes[pos].turno = lerInteiro("Turno ",0,10);
					break;
				case 5:
					//Tudo
					lerString("Nome: ",vetorEstudantes[pos].nome,MAX_STRING);
					printf("\n");

					printf("0 - Normal\t1 - Trabalhador\t2 - Extraordinario\n");
					vetorEstudantes[pos].tipo = lerInteiro("Tipo: ",0,2);
					printf("\n");

					printf("0 - Diurno\t1 - Pos-Laboral\n");
					vetorEstudantes[pos].regime = lerInteiro("Regime: ",0,1);

					vetorEstudantes[pos].turno = lerInteiro("Turno: ",1,10);
					printf("\n");
					break;
				case 6:
					break;
				default:
					printf("Opcao invalida\n");
			} //switch
			printf("\n\n");
		} while (opcao >= 1 && opcao < 6);
	}
}

/*Aqui poderiamos mudar o paramentro idEstudante para pos, e quando se chama a função colocar no parametro a função procurarEstudante por exemplo para ser mais eficiente.*/
/*Tambem podiamos mudar estas variaveis de tipo, regime para strings e usar a função strcmp() para comparar as strings, n sei se é melhor mas é capaz de ser menos eficiente tbh pq tens de usar mais memoria para guardar os vetores dar strings... só uma ideia*/

void consultarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes)
{
	int pos, idEstudante;

	idEstudante = lerInteiro("Introduza o id do estudante.",0,vetorEstudantes[nEstudantes-1].id);
	printf("\n");
	pos = procurarEstudante(vetorEstudantes,nEstudantes,idEstudante);

	if (pos == -1)
	{
		printf("Estudante com esse id nao existe\n");
	}
	else
	{
		mostrarEstudante(vetorEstudantes[pos]);
	}
}


void listarEstudantes(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes)
{
	int i;

	if(nEstudantes == 0)
	{
		printf("Nao existe estudantes registados.");
	}
	else
	{
		for(i=0;i<nEstudantes;i++)
		{
			mostrarEstudante(vetorEstudantes[i]);
			printf("\n\n");
		}
	}
}

void menuEstudantes(tipoEstudante vetorEstudantes[MAX_ESTUDANTES],int *nEstudantes)
{
	char opcao;
	int subopcao;
	int idEstudante;
	int pos;
	/*Falta meter os argumentos e criar a funcao listarEstudantes()*/
	do
	{
		idEstudante = 0;
		printf("\n\nMenu Estudantes:\n");
		printf("E - Criar Estudante\tC - Consultar estudante\nA - Alterar Estudante\nL - Listar Estudantes\nS - Sair\n");

		opcao = toupper(lerChar("Opcao: "));
		printf("\n");

		switch(opcao)
		{
			case 'E':
				criarEstudante(vetorEstudantes, nEstudantes);
				break;
			case 'C':
				consultarEstudante(vetorEstudantes,*nEstudantes);
				//consularEstudante();
				break;
			case 'A':
				do
				{
					if (*nEstudantes == 0)
					{
						printf("Nao existe alunos registados para alterar.\n");
						subopcao=2;
					}
					else
					{
						printf("1) Colocar novo id\n");
						printf("2) Sair\n");
						subopcao = lerInteiro("Opcao: ",1,2);
						printf("\n");
						switch(subopcao)
						{
							case 1:
								idEstudante = lerInteiro("Qual o id do estudante que quer alterar ?",0,vetorEstudantes[(*nEstudantes)-1].id);
								printf("\n");
								alterarEstudante(vetorEstudantes,*nEstudantes,idEstudante);
								break;
							case 2:
								break;
							default:
								printf("Opcao invalida");
						}
					}
				} while (subopcao != 2);
				break;
			case 'L':
				listarEstudantes(vetorEstudantes,*nEstudantes);
				break;
			case 'S':
				break;
			default:
				printf("Opcao invalida\n");
		}
	} while(opcao != 'S');
}

