#ifndef AVL_H
#define AVL_H

/*
    Definicao
*/
typedef struct NodoAVL {
    struct NodoAVL* pai;
    struct NodoAVL* esquerda;
    struct NodoAVL* direita;
    int valor;
    int altura;
} NodoAVL;

typedef struct AVLArvore {
    NodoAVL* raiz;
} ArvoreAVL;

/*
    Funcoes
*/
ArvoreAVL* criarAVL(void);
NodoAVL*   criarNodoAVL(NodoAVL* pai, int valor);
NodoAVL*   rse(ArvoreAVL* arvore, NodoAVL* nodo);
NodoAVL*   rsd(ArvoreAVL* arvore, NodoAVL* nodo);
NodoAVL*   rde(ArvoreAVL* arvore, NodoAVL* nodo);
NodoAVL*   rdd(ArvoreAVL* arvore, NodoAVL* nodo);
int        altura(NodoAVL* nodo);
int        fb(NodoAVL* nodo);
void       balanceamentoAVL(ArvoreAVL* arvore, NodoAVL* nodo);
NodoAVL*   adicionarNodoAVL(NodoAVL* nodo, int valor);
NodoAVL*   adicionarChaveAVL(ArvoreAVL* arvore, int valor);

#endif
