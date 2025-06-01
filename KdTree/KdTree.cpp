#include<stdio.h>
#include<stdlib.h>
#include<conio2.h>

#define TF 6
#define K 2

struct KdTree
{
	int ponto[K];
	struct KdTree *esq, *dir;
};
typedef struct KdTree kdtree;

kdtree *criaNo(int ponto[K])
{
	kdtree *no = (kdtree*)malloc(sizeof(kdtree));
	int i;
	for(i=0; i<K; i++)
		no->ponto[i] = ponto[i];
	no->esq = no->dir = NULL;
	return no;
}

void ordena(int ponto[TF][K], int d, int ini, int fim)
{
	int i, j, tl = fim;
	int aux[K];
	
	while(tl > ini)
	{
		for(i=ini; i<tl; i++)
		{
			if(ponto[i][d] > ponto[i+1][d])
			{
				for(j=0; j<K; j++)
					aux[j] = ponto[i][j];
					
				for(j=0; j<K; j++)
					ponto[i][j] = ponto[i+1][j];
					
				for(j=0; j<K; j++)
					ponto[i+1][j] = aux[j];
			}
		}
		tl--;
	}
}

void insereKdTree(kdtree **raiz, int ponto[TF][K], int n, int ini, int fim)
{
	int d, meio;
	
	if(ini <= fim)
	{
		d = n % K; //d -> indica se precisa ordenar pelo X ou pelo Y
		ordena(ponto, d, ini, fim);
		meio = (ini+fim)/2;
		*raiz = criaNo(ponto[meio]);
		insereKdTree(&(*raiz)->esq, ponto, n+1, ini, meio-1);
		insereKdTree(&(*raiz)->dir, ponto, n+1, meio+1, fim);
	}


//função que exibe a arvore montada (graficamente)
void exibeTree(kdtree *raiz, int x, int y, int dist)
{
	int i;
	if(raiz != NULL)
	{
		gotoxy(x,y);
		printf("(");
        i=0;
        while(i < K) {
        	printf("%d", raiz->ponto[i]);
        	if(i+1<K)
        		printf(", ");
        	i++;
        }
        printf(")");
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
	int i;
	int ponto[TF][K] = {{30,40},{5,25},{10,12},{70,70},{50,30},{35,45}};
	kdtree *raiz = NULL;
	
//	for(i=0; i<TF; i++) //-> APENAS PARA TESTAR A INSERÇÃO NA MATRIZ
//		printf("%d, %d\n",ponto[i][0],ponto[i][1]);
//	getch();
	
	insereKdTree(&raiz, ponto, 0, 0, TF-1);
	ordena(ponto, 0, 0, TF-1);
//	for(i=0; i<TF; i++)
//		printf("%d, %d\n",ponto[i][0],ponto[i][1]);
//	getch();
	
	//fazer um exibir para mostrar a arvore
	exibeTree(raiz,60,1,20);

}
