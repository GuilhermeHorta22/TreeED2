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

struct Pilha
{
	tree *no;
	struct Pilha *prox;
};
typedef struct Pilha pilha;

struct Fila
{
	tree *no;
	struct Fila *prox;
};
typedef struct Fila fila;


//fun��o que inicializa a fila
void initFila(fila **f)
{
	*f = NULL;
}

//FALTA TERMINAR O TAD DE FILA

//fun��o que verifica se a fila ta vazia
char isEmptyFila(fila *f)
{
	return f == NULL;
}

//fun��o que enfileira
void enqueue(fila **f, tree *no)
{
	fila *novoNo, *aux;
	novoNo = (fila*)malloc(sizeof(fila));
	novoNo->no = no;
	novoNo->prox = NULL;
	
	if(*f == NULL)
		*f = novoNo;
	else
	{
		fila *aux = *f;
		while(aux->prox != NULL)
			aux = aux->prox;
			
		aux->prox = novoNo;
	}
}

//fun��o que desinfilera
void dequeue(fila **f, tree **no)
{
	fila *aux;
	aux = *f;
	*no = (*f)->no; //passando o conteudo da fila
	*f = (*f)->prox;
	free(aux);
}

//fun��o que exclui um no pelo lado
void exclusaoLado(tree **raiz, tree *e, tree *pai, char lado)
{
	tree *sub = NULL;
	tree *subPai = NULL;
	int aux;
	
	if(e->esq == NULL && e->dir == NULL) //n�o tem nenhum filho
	{
		if(e != pai)
		{
			if(e->info > pai->info)
				pai->dir = NULL;
			else
				pai->esq = NULL;
		}
		else //se caso existir apenas a raiz
			*raiz = NULL;
		free(e);
	}
	else
	if(e->esq == NULL || e->dir == NULL) //apenas um filho
	{
		if(e != pai)
		{
			if(e->info > pai->info) //lado direito
			{
				if(e->esq != NULL) //tem um filho
					pai->dir = e->esq;
				else
					pai->dir = e->dir;
			}
			else
			{
				if(e->esq != NULL)
					pai->esq = e->esq;
				else
					pai->esq = e->dir;
			}
		}
		else
		{
			if(e->esq != NULL)
				*raiz = e->esq;
			else
			if(e->dir != NULL)
				*raiz = e->dir;
		}
		free(e);
	}
	else //tem dois filhos
	{
		if(lado == 'd')
		{
			sub = e->dir;
			subPai = e;
			while(sub->esq != NULL)
			{
				subPai = sub;
				sub = sub->esq;
			}
			aux = sub->info;
			exclusaoLado(&*raiz,sub,subPai,lado);
			e->info = aux;
		}
		else
		if(lado == 'e')
		{
			sub = e->esq;
			subPai = e;
			while(sub->dir != NULL)
			{
				subPai = sub;
				sub = sub->dir;
			}
			aux = sub->info;
			exclusaoLado(&*raiz,sub,subPai,lado);
			e->info = aux;
		}
		else
			printf("\nNao existe esse lado!\n");
	}
}

//fun��o que faz a travessia em pre ordem dentro da ABB
void pre_ordem(tree *raiz)
{
	if(raiz != NULL)
	{
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
	}
}

//fun��o que verifica a quantidade de n�
void quantNo(tree *raiz, int *cont)
{
	if(raiz != NULL)
	{
		quantNo(raiz->esq,&*cont);
		quantNo(raiz->dir,&*cont);
		(*cont)++;
	}
}

//fun��o principal do balanceamento
void BuscaBalanceamento(tree **raiz)
{
	tree *no;
	fila *f;
	initFila(&f);
	enqueue(&f,*raiz);
	while(!isEmptyFila(f))
	{
		dequeue(&f,&no);
		if(no->esq != NULL)
			enqueue(&f,no->esq);
		if(no->dir != NULL)
			enqueue(&f,no->dir);
	}
}

//fun��o que iniciliza a pilha
void init(pilha **p)
{
	*p = NULL;
}

//fun��o que verifica se a pilha est� vazia
char isEmpty(pilha *p)
{
	return p == NULL;
}

//fun��o que insere um elemento na pilha
void push(pilha **p, tree *raiz)
{
	pilha *nova = (pilha*)malloc(sizeof(pilha));
	nova->no = raiz;
	
	nova->prox = *p;
	*p = nova;
}

//fun��o que retira um elemento da pilha
void pop(pilha **p, tree **raiz)
{
	pilha *aux;
	if(!isEmpty(*p))
	{
		aux = *p;
		*raiz = (*p)->no;
		*p = aux->prox;
		free(aux);
	}
}

//fun��o que cria um novo no para ser adicionado na arvore
tree *criaNo(int info)
{
	tree *novoNo = (tree*)malloc(sizeof(tree));
	novoNo->info = info;
	novoNo->esq = novoNo->dir = NULL;
	return novoNo;
}

//fun��o que localiza um no na arvore
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

//fun��o que auxilia na localiza��o de um no na arvore
tree *localizaNo(tree *raiz, int info)
{
	tree *no = NULL;
	localiza(raiz,info,&no);
	return no;
}

//fun��o que insere um elemento na arvore ABB de forma interativa
void insereABBint(tree **raiz, int info)
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

//fun��o que insere um elemento na arvore ABB de forma recursiva
void inserirABBrec(tree **raiz, int info)
{
	if(*raiz == NULL)
		*raiz = criaNo(info);
	else
	{
		if(info > (*raiz)->info)
			inserirABBrec(&(*raiz)->dir,info);
		else
			inserirABBrec(&(*raiz)->esq,info);
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

//fun��o que busca um elemento na arvore ABB de forma recursiva com return
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

//fun��o que busca um elemento na arvore ABB de maneira recursiva
void buscaABBrec(tree *raiz, int info, tree **aux)
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

//fun��o que busca um elemento na arvore ABB de maneira mais curta (recursiva)
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

//fun��o que exibe a arvore montada (graficamente)
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

//fun��o que exibe a arvore em pre ordem
void pre_ordemInt(tree *raiz)
{
	pilha *p;
	init(&p);
	push(&p,raiz);
	while(!isEmpty(p))
	{
		if(raiz != NULL)
		{
			pop(&p,&raiz);
			while(raiz != NULL)
			{
				printf("\n%d",raiz->info);
				push(&p,raiz);
				raiz = raiz->esq;
			}
		}
		pop(&p,&raiz);
		raiz = raiz->dir;
		if(raiz != NULL)
			push(&p,raiz);
	}
}

//fun��o que exibe a arvore em pos ordem
void in_ordemInt(tree *raiz)
{
	pilha *p;
	init(&p);
	push(&p,raiz);
	while(!isEmpty(p))
	{
		if(raiz != NULL)
		{
			pop(&p,&raiz);
			while(raiz != NULL)
			{
				push(&p,raiz);
				raiz = raiz->esq;
			}
		}
		pop(&p,&raiz);
		printf("\n%d",raiz->info);
		raiz = raiz->dir;
		if(raiz != NULL)
			push(&p,raiz);
	}
}

//fun��o que exibe a arvore em in ordem
void pos_ordemInt(tree *raiz)
{
	pilha *p, *p2;
	init(&p);
	init(&p2);
	push(&p,raiz);
	while(!isEmpty(p))
	{
		if(raiz != NULL)
		{
			pop(&p,&raiz);
			while(raiz != NULL)
			{
				push(&p2,raiz);
				push(&p,raiz);
				raiz = raiz->dir;
			}
		}
		pop(&p,&raiz);
		raiz = raiz->esq;
		if(raiz != NULL)
			push(&p,raiz);
		
		while(!isEmpty(p2))
		{
			pop(&p2,&raiz);
			printf("\n%d",raiz->info);
		}
	}
}

//deletando uma ABB inteira usando pos_ordem (RECURSIVO)
void delPos_ordem(tree **raiz)
{
	if(*raiz != NULL)
	{
		delPos_ordem(&(*raiz)->esq);
		delPos_ordem(&(*raiz)->dir);
		free(*raiz);
	}
	*raiz = NULL;
}

//deletando uma ABB inteira usando pos_ordem (INTERATIVO)
void delPos_ordemInt(tree **raiz)
{
	tree *aux = *raiz;
	pilha *p, *p2;
	init(&p);
	init(&p2);
	
	push(&p,aux);
	while(!isEmpty(p))
	{
		if(aux != NULL)
		{
			pop(&p,&aux);
			while(aux != NULL)
			{
				push(&p,aux);
				push(&p2,aux);
				aux = aux->dir;
			}
		}
		pop(&p,&aux);
		aux = aux->esq;
		if(aux != NULL)
			push(&p,aux);
		
		while(!isEmpty(p2))
		{
			pop(&p2,&aux);
			free(aux);
		}
	}
	*raiz = NULL;
}

void buscaNo(tree *raiz, int info, tree **e, tree **pai)
{
	*e = raiz;
	while(*e != NULL && (*e)->info != info)
	{
		if(info > (*e)->info)
		{
			*pai = *e;
			*e = (*e)->dir;
		}
		else
		{
			*pai = *e;
			*e = (*e)->esq;
		}
	}
}

void excluiNo(tree **raiz, tree *e, tree *pai)
{
	tree *sub = NULL;
	tree *subPai = NULL;
	int aux;
	
	if(e->esq == NULL && e->dir == NULL) //n�o tem nenhum filho
	{
		if(e != pai)
		{
			if(e->info > pai->info)
				pai->dir = NULL;
			else
				pai->esq = NULL;
		}
		else //se caso existir apenas a raiz
			*raiz = NULL;
		free(e);
	}
	else
	if(e->esq == NULL || e->dir == NULL) //apenas um filho
	{
		if(e != pai)
		{
			if(e->info > pai->info) //lado direito
			{
				if(e->esq != NULL) //tem um filho
					pai->dir = e->esq;
				else
					pai->dir = e->dir;
			}
			else
			{
				if(e->esq != NULL)
					pai->esq = e->esq;
				else
					pai->esq = e->dir;
			}
		}
		else
		{
			if(e->esq != NULL)
				*raiz = e->esq;
			else
			if(e->dir != NULL)
				*raiz = e->dir;
		}
		free(e);
	}
	else //tem dois filhos
	{
		sub = e->dir;
		subPai = e;
		while(sub->esq != NULL)
		{
			pai = sub;
			sub = sub->esq;
		}
		aux = sub->info;
		excluiNo(&*raiz,sub,subPai);
		e->info = aux;
	}
}

//fun��o que balanceia a ABB
void balanceamento(tree **raiz, tree *e, tree *pai)
{
	tree *sub = NULL;
	tree *subPai = NULL;
	tree *no = NULL;
	int aux, fb;
	
	if(e->esq == NULL && e->dir == NULL) //n�o tem nenhum filho
	{
		if(e != pai)
		{
			if(e->info > pai->info)
				pai->dir = NULL;
			else
				pai->esq = NULL;
		}
		else //se caso existir apenas a raiz
			*raiz = NULL;
		free(e);
	}
	else
	if(e->esq == NULL || e->dir == NULL) //apenas um filho
	{
		if(e != pai)
		{
			if(e->info > pai->info) //lado direito
			{
				if(e->esq != NULL) //tem um filho
					pai->dir = e->esq;
				else
					pai->dir = e->dir;
			}
			else
			{
				if(e->esq != NULL)
					pai->esq = e->esq;
				else
					pai->esq = e->dir;
			}
		}
		else
		{
			if(e->esq != NULL)
				*raiz = e->esq;
			else
			if(e->dir != NULL)
				*raiz = e->dir;
		}
		free(e);
	}
	else
	{
		do
		{
			int qtdeDir=0, qtdeEsq=0;
			quantNo(no->dir,&qtdeDir);
			quantNo(no->esq,&qtdeEsq);
			fb = qtdeEsq + qtdeDir;
			if(fb < -1 || fb > 1)
			{
				aux = no->info;
				if(no->esq == NULL)
					no = no->dir;
				else
				if(no->dir == NULL)
					no = no->esq;
				buscaNo(*raiz,aux,&e,&pai);
				
				if(fb > 0)
					exclusaoLado(&*raiz,e,pai,'d');
				else
					exclusaoLado(&*raiz,e,pai,'e');
				
				inserirABBrec(&*raiz,aux);
			}
		}while(fb < -1 || fb > 1);
	}
}

char menu(void)
{
	printf("*** MENU ARVORE ABB ***\n");
	printf("\n[A] - Busca ABB interativa");
	printf("\n[B] - Busca ABB recursiva");
	printf("\n[C] - Busca ABB recursiva com return");
	printf("\n[D] - Busca ABB recursiva curta");
	printf("\n[E] - Exibe ABB montada");
	printf("\n[F] - Exibe ABB pre ordem interativo");
	printf("\n[G] - Exibe ABB in ordem interativo");
	printf("\n[H] - Exibe ABB pos ordem interativo");
	printf("\n[I] - Localiza no ABB");
	printf("\n[J] - Deletando uma ABB inteira recursivo");
	printf("\n[K] - Deletando uma ABB inteira interativa");
	printf("\n[L] - Excluindo no ABB");
	printf("\n[M] - Balanceando ABB");
	printf("\n[N] - Quantidade de no ABB");
	printf("\n[ESC] - Encerrar algoritmo\n");
	printf("\nOpcao: ");
	
	return toupper(getche());
}

int main()
{
	tree *raiz = NULL;
	tree *aux = NULL; //vou usar na buscaABB
	
	//vou usar na fun��o de excluir um no
	tree *e = NULL;
	tree *pai = NULL;
	
	char op;
	int valor, x=60, y=1, dist=20, info, cont=0;
	
	//montando a arvore
	inserirABBrec(&raiz,15); //raiz da arvore
	inserirABBrec(&raiz,8);
	inserirABBrec(&raiz,5);
	inserirABBrec(&raiz,12);
	inserirABBrec(&raiz,10);
	inserirABBrec(&raiz,20);
	inserirABBrec(&raiz,18);
	inserirABBrec(&raiz,22);
	inserirABBrec(&raiz,23);
	inserirABBrec(&raiz,27);
	inserirABBrec(&raiz,26);
	
	do
	{
		op = menu();
		system("cls");
			
		switch(op)
		{
			case 'A':
				printf("### BUSCA ABB INTERATIVA ###\n");
				printf("\nDigite um valor para ser buscado: ");
				scanf("%d",&valor);
				aux = buscaABBint(raiz,valor);
				if(aux == NULL)//n�o achou
					printf("\nNao achou o valor!!!\n");
				else
					printf("\nValor: %d",aux->info);
				
				break;
				
			case 'B':
				printf("### BUSCA ABB RECURSIVA ###\n");
				printf("\nDigite um valor para ser buscado: ");
				scanf("%d",&valor);
				buscaABBrec(raiz,valor,&aux);
				if(aux == NULL)
					printf("\nNao achou o valor!!!");
				else
					printf("\nValor: %d",aux->info);
					
				break;
				
			case 'C':
				printf("### BUSCA ABB RECURSIVA COM RETURN ###\n");
				printf("\nDigite um valor para ser buscado: ");
				scanf("%d",&valor);
				aux = buscaABBret(raiz,valor);
				if(aux == NULL)
					printf("\nNao achou o valor!!!");
				else
					printf("\nValor: %d",aux->info);
					
				break;
				
			case 'D':
				printf("### BUSCA ABB CURTA ###");
				printf("\nDigite um valor para ser buscado: ");
				scanf("%d",&valor);
				buscaABB(raiz,valor,&aux);
				if(aux == NULL)
					printf("\nNao achou o valor!!!");
				else
					printf("\nValor: %d",aux->info);
					
				break;
				
			case 'E':
				//printf("### EXIBE ABB MONTADA ###\n");
				exibeTree(raiz,x,y,dist);
				
				break;
				
			case 'F':
				printf("### EXIBE ABB PRE ORDEM INTERATIVO ###\n");
				pre_ordemInt(raiz);
				
				break;
				
			case 'G':
				printf("### EXIBE ABB IN ORDEM INTERATIVO ###\n");
				in_ordemInt(raiz);
				
				break;
				
			case 'H':
				printf("### EXIBE ABB POS ORDEM INTERATIVO ###\n");
				pos_ordemInt(raiz);
				
				break;
			
			case 'I':
				printf("### LOCALIZA NO ABB ###\n");
				printf("\nValor para ser localizado: ");
				scanf("%d",&valor);
				
				aux = localizaNo(raiz,valor);
				if(aux != NULL)
					printf("\nValor: %d",aux->info);
				else
					printf("\nValor nao encontrado!\n");
					
				break;
				
			case 'J':
				printf("### DELETANDO ABB INTEIRA RECURSIVO###\n");
				delPos_ordem(&raiz);
				
				printf("\nArvore deletada com sucesso!\n");
				break;
				
			case 'K':
				printf("### DELETANDO ABB INTEIRA INTERATIVO###\n");
				delPos_ordemInt(&raiz);
				
				printf("\nArvore deletada com sucesso!\n");
				break;
				
			case 'L':
				printf("### EXCLUINDO NO DA ABB ###\n");
				
				printf("\nDigite o valor para ser excluido: ");
				scanf("%d",&info);
				
				buscaNo(raiz,info,&e,&pai);
				
				if(e != NULL && e->info == info) //achou
				{
					excluiNo(&raiz,e,pai);
					printf("\nNo excluido com sucesso!");
				}
				else
					printf("\nNao foi encontrado o no para exclusao!");
				
				break;
				
			case 'M':
				printf("### BALANCEADO ARVORE ABB ###\n");
				balanceamento(&raiz,e,pai);
				
				
				break;
				
			case 'N':
				printf("### QUANTIDADE DE NO NA ABB ###\n");
				
				quantNo(raiz,&cont);
				printf("\nQuantidade de no: %d",cont);
				
				break;
				
			case 27:
				printf("Algoritmo encerrado!\n");
				
				break;
		}
		getch(); //para travar a exibi��o
		system("cls");
	}while(op != 27);
}
