#ifndef B_H
#define B_H

/*
    Definicao
*/
typedef struct NodoB {
    int total;
    int* chaves;
    struct NodoB** filhos;  
    struct NodoB* pai;
} NodoB;

typedef struct ArvoreB {
    NodoB* raiz;
    int ordem;
} ArvoreB;

/*
    Funcoes
*/
ArvoreB* criarArvoreB(int ordem);
NodoB* criarNodoB(ArvoreB* arvore);
int pesquisaBinariaB(NodoB* nodo, int chave);
void percorrerArvoreB(NodoB* nodo, void (*visita)(int chave, void* ctx), void* ctx);
int localizarChaveB(ArvoreB* arvore, int chave);
NodoB* localizarNodoB(ArvoreB* arvore, int chave);
NodoB* dividirNodoB(ArvoreB* arvore, NodoB* nodo);
int transbordoB(ArvoreB* arvore, NodoB* nodo);
void adicionarChaveNodoB(NodoB* nodo, NodoB* direita, int chave);
void adicionarChaveB(ArvoreB* arvore, int chave);
void printarB(ArvoreB* arvore);

#endif
