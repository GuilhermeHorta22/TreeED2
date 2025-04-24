#include<stdio.h>
#include<conio2.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct Tree
{
	int info;
	struct Tree *esq, *dir;
};
typedef struct Tree tree;

tree *criaNo(int info)
{
	tree *novoNo = (tree*)malloc(sizeof(tree));
	novoNo->info = info;
	novoNO->esq = novoNo->dir = NULL;
	return novoNo;
}

void localiza(tree *raiz, int info, tree **no)
{
	if(raiz != NULL)
	{
		if(raiz->info == info)
			*no = raiz->info;
		else
		{
			localiza(raiz->esq,info,&*no);
			localiza(raiz->dir,info,&*no);
		}
	}
}

tree *localizaNo(tree *raiz, int info)
{
	tree *no = NULL;
	localiza(raiz,info,&no);
	return no;
}

void insere(tree **raiz, int info)
{
	tree *aux, *ant;
	
	if(*raiz == NULL)
		*raiz = criaNo(info);
	else
	{
		aux = *raiz;
		while(aux != NULL)
		{
			ant = aux;
			if(info > aux->info)
				aux = aux->dir;
			else
				aux = aux->esq;
		}
		if(info > ant->info)
			ant->dir = criaNo(info);
		else
			ant->dir = criaNo(info);
	}
}

//falta ainda dois inserir para ser feito
//void insereRecur(tree **raiz, int info)

void inserirABB(tree **raiz, int info)
{
	if(*raiz == NULL)
		*raiz = criaNo(info);
	else
	{
		if(info > (*raiz)->info)
			insereABB(&(*raiz)->esq,info);
		else
			insereABB(&(*raiz)->esq,info);
	}
}

//escopo da busca na arvore ABB - recursivo e interativo
tree *buscaABBint(tree *raiz, int info)
{
	while(raiz != NULL && raiz->info != info)
	{
		if(info < raiz->info)
			raiz = raiz->esq; //esquerda tem os valores menor que o da raiz
		else
			raiz = raiz->dir; //direita tem os valores maiores que o da raiz
	}
	
	return raiz;
}

//busca recursiva com return
tree *buscaABBret(tree *raiz, int info)
{
	if(raiz != NULL)
	{
		if(info == raiz->info)
			return raiz;
		
		if(info > raiz->info)
			return buscaABBret(raiz->dir,info);
		
		return buscaABBret(raiz->esq,info);
	}
	return NULL;
}

void buscaABBrec(tree *raiz, int info, tree **aux) //não sei se realmente é isso
{
	if(raiz != NULL)
	{
		if(info == raiz->info)
			*aux = raiz;
		else
		if(info > raiz->info)
			buscaABBrec(raiz->dir,info,&*aux);
		else
			buscaABBrec(raiz->esq,info,&*aux);
	}
}

//essa busca é a mesma coisa da anterior, a diferença é que escreve menos um if
void buscaABB(tree *raiz, int info, tree **aux)
{
	if(raiz != NULL || info == raiz->info)
		*aux = raiz;
	else
	if(info > raiz->info)
		buscaABB(raiz->dir,info,&*aux);
	else
		buscaABB(raiz->dir,info,&*aux);
}

//função que exibe a arvore montada (graficamente)
void exibeTree(tree *raiz, int x, int y, int dist)
{
	if(raiz != NULL)
	{
		gotoxy(x,y);
		printf("%d",raiz->info);
		if(raiz->esq != NULL)
		{
			gotoxy(x-dist/2,y+1);
			printf("/");
		}
		if(raiz->dir != NULL)
		{
			gotoxy(x+dist/2,y+1);
			printf("\\");
		}
		exibeTree(raiz->esq,x-dist,y+2,dist/2);
		exibeTree(raiz->dir,x+dist,y+2,dist/2);
	}
}

int main()
{
	tree *raiz = NULL;
	tree *aux = NULL; //vou usar na buscaABB
	
	insere(&raiz,15,0,' '); //raiz da arvore
	insere(&raiz,8,15,'e');
	insere(&raiz,20,15,'d');
	insere(&raiz,5,8,'e');
	insere(&raiz,12,8,'d');
	insere(&raiz,10,12,'e');
	insere(&raiz,18,20,'e');
	insere(&raiz,22,20,'d');
	
	buscaABB(raiz,20,&aux);
	printf("%d\n",aux->info);
}
