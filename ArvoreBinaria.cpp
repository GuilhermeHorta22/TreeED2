#include<stdio.h>
#include<conio2.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct Tree
{
	int info;
	struct Tree *esq, *dir; //esq = esquerda | dir = direita
};
typedef struct Tree tree;

//função que cria um nó na raiz
tree *criaNo(int info)
{
	tree *novoNo = (tree*)malloc(sizeof(tree));
	novoNo->info = info;
	novoNo->esq = novoNo->dir = NULL;
	return novoNo;
}

void localiza(tree *raiz, int info, tree **no)
{
	if(raiz != NULL)
	{
		if(raiz->info == info)
			*no = raiz;
		else
		{
			localiza(raiz->esq,info,&*no);
			localiza(raiz->dir,info,&*no);
		}
	}
}

//função que localiza um nó na arvore
tree *localizaNo(tree *raiz, int info)
{
	tree *no=NULL;
	localiza(raiz,info,&no); //vamos precisar dessa função para achar recursivamente
	return no;
}

//função que insere um elemento na arvore
void insere(tree **raiz, int info, int infoPai, char lado)
{
	tree *pai;
	
	//se caso essa raiz ainda não tiver nenhum elemento
	if(*raiz == NULL)
		*raiz = criaNo(info);
	else
	{
		pai = localizaNo(*raiz,infoPai);
		if(pai != NULL)
		{
			if(lado == 'd' && pai->dir == NULL)
				pai->dir = criaNo(info);
			else
			if(lado == 'e' && pai->esq == NULL)
				pai->esq = criaNo(info);
			else
				printf("\nLado nao disponivel!");
		}
	}
}

//travessia em pré-ordem
void pre_ordem(tree *raiz)
{
	if(raiz != NULL)
	{
		printf("%d\n",raiz->info);
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
	}
}

//travesia em in-ordem
void in_ordem(tree *raiz)
{
	if(raiz != NULL)
	{
		in_ordem(raiz->esq);
		printf("%d\n",raiz->info);
		in_ordem(raiz->dir);
	}
}

//travessia em pos-ordem
void pos_ordem(tree *raiz)
{
	if(raiz != NULL)
	{
		pos_ordem(raiz->esq);
		pos_ordem(raiz->dir);
		printf("%d\n",raiz->info);
	}
}

int main()
{
	tree *raiz = NULL;
	insere(&raiz,15,0,' '); //raiz da arvore
	insere(&raiz,8,15,'e');
	insere(&raiz,20,15,'d');
	insere(&raiz,5,8,'e');
	insere(&raiz,12,8,'d');
	insere(&raiz,10,12,'e');
	insere(&raiz,18,20,'e');
	insere(&raiz,22,20,'d');
	
	printf("\n*** EXIBICAO EM PRE-ORDEM ***\n");
	pre_ordem(raiz);
	
	printf("\n*** EXIBICAO EM IN-ORDEM ***\n");
	in_ordem(raiz);
	
	printf("\n*** EXIBICAO EM POS-ORDEM ***\n");
	pos_ordem(raiz);
	getch();
}
