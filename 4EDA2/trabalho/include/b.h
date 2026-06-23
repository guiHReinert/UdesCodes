#ifndef B_H
#define B_H

/*
    Definicao
*/
typedef struct bNodo {
    int total;
    int* chaves;
    struct bNodo** filhos;
    struct bNodo* pai;
} BNodo;

typedef struct bArvore {
    BNodo* raiz;
    int ordem;
} BArvore;

/*
    Funcoes
*/
BArvore* criarArvoreB(int ordem);
BNodo*   criarNodoB(BArvore* arvore);
int      pesquisaBinariaB(BNodo* nodo, int chave);
void     percorrerArvoreB(BNodo* nodo, void (visita)(int chave));
int      localizarChaveB(BArvore* arvore, int chave);
BNodo*   localizarNodoB(BArvore* arvore, int chave);
BNodo*   dividirNodoB(BArvore* arvore, BNodo* nodo);
int      transbordoB(BArvore* arvore, BNodo* nodo);
void     adicionarChaveNodoB(BNodo* nodo, BNodo* direita, int chave);
void     adicionarChaveB(BArvore* arvore, int chave);
void     adicionarChaveRecursivoB(BArvore* arvore, BNodo* nodo, BNodo* novo, int chave);

#endif
