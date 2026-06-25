#ifndef AVL_H
#define AVL_H

/*
    Definicao
*/
typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
    int altura;
} NoAVL;

typedef struct arvore {
    struct no* raiz;
} ArvoreAVL;

/*
    Funcoes
*/

ArvoreAVL* criarAVL(void);
static NoAVL* criarNoAVL(NoAVL* pai, int valor);

int isVaziaAVL(ArvoreAVL* arvore);
NoAVL* localizarNoAVL(NoAVL* no, int valor, int* count);
NoAVL* remocaoAVL(ArvoreAVL* arvore, int valor, int* count);
void percorrerAVL(NoAVL* no, void (*callback)(int));
void visitar(int valor);

NoAVL* adicionarNoAVL(NoAVL* no, int valor, int* count);
NoAVL* adicionarChaveAVL(ArvoreAVL* arvore, int valor, int* count);

static NoAVL* encontrarSucessor(NoAVL* no, int* count);
static void balanceamentoAVL(ArvoreAVL* arvore, NoAVL* no, int* count);
static int altura(NoAVL* no);
static int fb(NoAVL* no);
static NoAVL* rsd(ArvoreAVL* arvore, NoAVL* no);
static NoAVL* rse(ArvoreAVL* arvore, NoAVL* no);
static NoAVL* rdd(ArvoreAVL* arvore, NoAVL* no);
static NoAVL* rde(ArvoreAVL* arvore, NoAVL* no);

void printarAVL(ArvoreAVL* arvore);

#endif
