#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio2.h>

#define TF 100
#define N 5

struct caixa
{
	int chave, pos;
	struct caixa *prox;
};
typedef struct caixa Caixa;

struct tpReg
{
	int cod;
	char nome[30];
	int idade;
	char status;
};

int hash(int chave)
{
	return chave % N;
}

void busca_lista(Caixa *inicio, int chave, Caixa **no)
{
	while(inicio != NULL && chave > inicio->chave)
		inicio = inicio->prox;
		
	if(inicio != NULL && inicio->chave == chave)
		*no = inicio;
	else
		*no = NULL;
}

void insere_lista(Caixa **inicio, int chave, int pos)
{
	//fazer um insere ordenado
}

void exclusao_logica(Caixa T[N], tpReg tabDados[TF], int codigo)
{
	int ender;
	Caixa *aux;
	
	ender = hash(codigo);
	busca_lista(T[ender], codigo, &aux);
	if(aux != NULL) //achou
	{
		if(tabDados[aux->prox].status == 1)
			tabDados[aux->prox].status = 0; //false
		else
			printf("\nChave ja excluida!");
	}
	else
		printf("\nChave nao encontrada!");
}


void insere(Caixa T[N], tpReg tabDados[TF], int *tl, tpReg reg)
{
	int ender;
	Caixa *aux;
	
	ender = hash(reg.cod);
	busca_lista(T[ender], reg.cod, &aux);
	if(aux == NULL)
	{
		tabDados[*tl] = reg;
		insere_lista(&T[ender], reg.cod, *tl);
		(*tl)++;
	}
	else
		printf("\nChave existente!");
}
