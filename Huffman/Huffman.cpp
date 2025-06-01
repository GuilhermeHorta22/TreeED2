#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio2.h>

struct huffman
{
	int frenq;
	char simbolo;
	struct huffman *esq, *dir;
};
typedef struct huffman Huffman;

struct listTree
{
	struct Huffman *arv;
	struct listTree *prox;
};
typedef struct listTree ListTree;

//na huffman vamos ter uma lista que aponta para cada nó da arvore ai vamos pegando de 2 em 2 para ir criando a arvore

  
