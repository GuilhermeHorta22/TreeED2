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

//função que iniciliza a pilha
void init(pilha **p)
{
	*p = NULL;
}

//função que verifica se a pilha está vazia
char isEmpty(pilha *p)
{
	return p == NULL;
}

//função que insere um elemento na pilha
void push(pilha **p, tree *raiz)
{
	pilha *nova = (pilha*)malloc(sizeof(pilha));
	nova->no = raiz;
	
	nova->prox = *p;
	*p = nova;
}

//função que retira um elemento da pilha
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

//função que cria um novo no para ser adicionado na arvore
tree *criaNo(int info)
{
	tree *novoNo = (tree*)malloc(sizeof(tree));
	novoNo->info = info;
	novoNo->esq = novoNo->dir = NULL;
	return novoNo;
}

//função que localiza um no na arvore
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

//função que auxilia na localização de um no na arvore
tree *localizaNo(tree *raiz, int info)
{
	tree *no = NULL;
	localiza(raiz,info,&no);
	return no;
}

//função que insere um elemento na arvore ABB de forma interativa
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

//função que insere um elemento na arvore ABB de forma recursiva
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

//função que busca um elemento na arvore ABB de forma recursiva com return
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

//função que busca um elemento na arvore ABB de maneira recursiva
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

//função que busca um elemento na arvore ABB de maneira mais curta (recursiva)
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

//função que exibe a arvore em pre ordem
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

//função que exibe a arvore em pos ordem
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

//função que exibe a arvore em in ordem
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
	
	if(e->esq == NULL && e->dir == NULL) //não tem nenhum filho
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
	printf("\n[ESC] - Encerrar algoritmo\n");
	printf("\nOpcao: ");
	
	return toupper(getche());
}

int main()
{
	tree *raiz = NULL;
	tree *aux = NULL; //vou usar na buscaABB
	
	//vou usar na função de excluir um no
	tree *e = NULL;
	tree *pai = NULL;
	
	char op;
	int valor, x=60, y=1, dist=20, info;
	
	//montando a arvore
	inserirABBrec(&raiz,15); //raiz da arvore
	inserirABBrec(&raiz,8);
	inserirABBrec(&raiz,5);
	inserirABBrec(&raiz,12);
	inserirABBrec(&raiz,10);
	inserirABBrec(&raiz,20);
	inserirABBrec(&raiz,18);
	inserirABBrec(&raiz,22);
	
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
				if(aux == NULL)//não achou
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
				
			case 27:
				printf("Algoritmo encerrado!\n");
				
				break;
		}
		getch(); //para travar a exibição
		system("cls");
	}while(op != 27);
}
