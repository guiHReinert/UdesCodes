#ifndef RUBRO_NEGRA_H
#define RUBRO_NEGRA_H

/*
    Definicao
*/
typedef enum coloracao { Vermelho, Preto } Cor;

typedef struct NodoRN {
    struct NodoRN* pai;
    struct NodoRN* esquerda;
    struct NodoRN* direita;
    Cor cor;
    int valor;
} NodoRN;

typedef struct ArvoreRN {
    NodoRN* raiz;
    NodoRN* nulo;
} ArvoreRN;

/*
    Funcoes
*/
ArvoreRN* criarRN(void);
NodoRN* criarNodoRN(ArvoreRN* arvore, NodoRN* pai, int valor, Cor cor);

void adicionarChaveRN(ArvoreRN* arvore, int valor, int* count);
static void fixBB(ArvoreRN* arvore, NodoRN* nodo, NodoRN* pai);

void removerChaveRN(ArvoreRN* arvore, int chave);

void rotEsquerdaRN(ArvoreRN* arvore, NodoRN* nodo);
void rotDireitaRN(ArvoreRN* arvore, NodoRN* nodo);
void balancearRN(ArvoreRN* arvore, NodoRN* nodo);
void printarRN(ArvoreRN* arvore);

#endif
