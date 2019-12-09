#include "constantes.h"
#include "estruturas.h"
#include <stdio.h>
#include "funcoesAuxiliares.h"


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

void criarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int *nEstudantes, int *idEstudantes)
{
	if ((*nEstudantes)+1 >= MAX_ESTUDANTES)
	{
		printf("Chegou ao numero maximo de estudantes.");
	}
	else
	{
		vetorEstudantes[(*nEstudantes)].id = *idEstudantes + 1;
		lerString("Nome do estudante: ",vetorEstudantes[(*nEstudantes)].nome,255);
		vetorEstudantes[(*nEstudantes)].tipo = lerInteiro("Tipos: 0 - Normal,\t1 - Trabalhador,\t2 - Extraordinario",0,2);
		vetorEstudantes[(*nEstudantes)].regime = lerInteiro("Regimes: 0 - diurno,\t1 - Pos-laboral",0,1);
		vetorEstudantes[(*nEstudantes)].turno = lerInteiro("Turno:",0,100);
	}
}

/*
	Alterar os dados do estudante

	Deveriamos dar a opção de deixar o utilizador apenas mudar
*/
void alterarEstudante(tipoEstudante vetorEstudantes[MAX_ESTUDANTES], int nEstudantes, int idEstudante)
{

}

void consultarEstudante(tipoEstudante vetorEstudante[MAX_ESTUDANTES], int nEstudantes)
{

}

void procurarEstudante(tipoEstudante vetorEstudante[MAX_ESTUDANTES], int nEstudantes, int idEstudante)
{

}
