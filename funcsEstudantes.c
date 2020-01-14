#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "funcsAuxiliares.h"
#include "constantes.h"
#include "estruturas.h"
#include "funcsEstudantes.h"
#include "funcsTreinos.h"
#include <stdlib.h>

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
	printf("Turno: %d\n\n",vetorEstudantes.turno);
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

void alterarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes)
{
	int opcao,subopcao;
	int pos;
	int idEstudante;

	if (nEstudantes == 0)
	{
		printf("Nao existe alunos registados para alterar.\n");
	}
	else
	{

		idEstudante = lerInteiro("Qual o id do estudante que quer alterar ?",0,vetorEstudantes[nEstudantes-1].id);
		printf("\n");

		pos = procurarEstudante(vetorEstudantes,nEstudantes,idEstudante);
		if(pos == -1)
		{
			printf("Nao existe um aluno com este id\n");
		}
		else
		{
			do
			{
				opcao = -1;
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
				opcao = lerInteiro("Opcao: ",1,6);
				printf("\n\n");

				switch(opcao)
				{
					case 1:
						printf("1) Nome anterior: %s\n",vetorEstudantes[pos].nome);
						lerString("=> ",vetorEstudantes[pos].nome,MAX_STRING);
						break;
					case 2:
						printf("0 - Normal\t1 - Trabalhador\t2 - Extraordinario\n");
						vetorEstudantes[pos].tipo = lerInteiro("Tipo: ",0,2);
						printf("\n");
						break;
					case 3:
						printf("0 - Diurno\t1 - Pos-Laboral\n");
						vetorEstudantes[pos].regime = lerInteiro("Regime: ",0,1);
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
				}
				printf("\n\n");
			} while (opcao >= 1 && opcao < 6);
		}
	}
}

void consultarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, tipoTreino * vetorTreinos, int nTreinos, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas)
{
	int pos, idEstudante,i,idRecente;
	tipoData dataUltimo, dataTreino;

	// Para saber qual é o primeiro a passar no filtro
	dataUltimo.ano = -1;

	if(nEstudantes==0) {
		printf("Nao existem estudantes para consultar.\n");
	}
	else {
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
			printf("Treinos pertencentes ao estudante:\n");
			for(i=0;i<nTreinos;i++) {
				if(vetorTreinos[i].idEstudante==idEstudante){
					mostrarTreino(vetorTreinos[i]);
					dataTreino = vetorTreinos[i].dataRealizacao;
					if(vetorTreinos[i].estado==1){
						if(dataUltimo.ano == -1) {
							//Primeiro treino do estudante a aparecer, marcar este como o mais recente
							dataUltimo = dataTreino;
							idRecente = i;
						}
						else{
							if(dataEMaior(dataUltimo,dataTreino)){
								dataUltimo = dataTreino;
								idRecente = i;
							}
						}
					}
				}
			}
			printf("\n\nTreino mais recente: \n");
			mostrarTreino(vetorTreinos[idRecente]);
			mostrarPerguntasTreino(vetorTreinos[idRecente],vetorPerguntas, nPerguntas);
		}
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

//para passar array ao qsort
typedef struct EstudanteMedia {
	int idEstudante;
	float media;
} tipoEstudanteMedia;

int compararNotaMaior(const void *p, const void *q) {
	float nota1 = ((const tipoEstudanteMedia *)p)->media;
	float nota2 = ((const tipoEstudanteMedia *)q)->media;

	return (nota2 - nota1);
}

void rankingEstudantes(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas, tipoTreino * vetorTreino, int nTreinos) {
	tipoEstudanteMedia mediaEstudantes[MAX_ESTUDANTES] = {0};
	tipoEstudanteMedia mediaEstudantesOrdenada[MAX_ESTUDANTES] = {0};
	int nTreinosEstudante[MAX_ESTUDANTES] = {0};
	int i, pos;
	int vazio = 1;

	for(i=0;i<nTreinos;i++) {
		if(vetorTreino[i].estado == 1) {
			vazio = 0;
			mediaEstudantes[vetorTreino[i].idEstudante].media += vetorTreino[i].classificacao;
			nTreinosEstudante[vetorTreino[i].idEstudante]++;
		}
	}
	if(vazio == 1) {
		printf("Nao existem treinos realizados.\n");
	}
	else {
		for(i=0;i<nEstudantes;i++) {
			mediaEstudantes[i].idEstudante = vetorEstudantes[i].id; //para saber-se apos de ordenar
			if(nTreinosEstudante[i] != 0){
				mediaEstudantes[i].media /= (float)nTreinosEstudante[i];
			}
			else {
				// Para nao dividir 0/0 e dar erro
				mediaEstudantes[i].media = 0.00;
			}
		}
		qsort((void*)mediaEstudantes, nEstudantes, sizeof(tipoEstudanteMedia), compararNotaMaior);
		printf("Ranking de estudantes:\n");
		for(i=0;i<nEstudantes;i++) {
			pos = procurarEstudante(vetorEstudantes,nEstudantes,mediaEstudantes[i].idEstudante);
			printf("%d. %s -> %.2f\n",pos+1,vetorEstudantes[pos].nome, mediaEstudantes[i].media);
		}
	}
}

void menuEstudantes(tipoEstudante vetorEstudantes[MAX_ESTUDANTES],int *nEstudantes,tipoTreino * vetorTreinos, int nTreinos, tipoPergunta vetorPerguntas[MAX_PERGUNTAS], int nPerguntas)
{
	char opcao;
	int subopcao;
	int idEstudante;
	int pos;

	do
	{
		idEstudante = 0;
		printf("\n\nMenu Estudantes:\n");
		printf("E - Criar Estudante\tC - Consultar estudante\nA - Alterar Estudante\nL - Listar Estudantes\nR - Ranking Estudantes\nS - Sair\n");

		opcao = toupper(lerChar("Opcao: "));
		printf("\n");

		switch(opcao)
		{
			case 'E':
				criarEstudante(vetorEstudantes, nEstudantes);
				break;
			case 'C':
				consultarEstudante(vetorEstudantes,*nEstudantes,vetorTreinos,nTreinos,vetorPerguntas,nPerguntas);
				break;
			case 'A':
				alterarEstudante(vetorEstudantes, *nEstudantes);

				break;
			case 'L':
				listarEstudantes(vetorEstudantes,*nEstudantes);
				break;
			case 'R':
				rankingEstudantes(vetorEstudantes, *nEstudantes, vetorPerguntas, nPerguntas, vetorTreinos, nTreinos);
				break;
			case 'S':
				break;
			default:
				printf("Opcao invalida\n");
		}
	} while(opcao != 'S');
}
