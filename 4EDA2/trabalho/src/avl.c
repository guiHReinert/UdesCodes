#include "../include/arvores.h"

/*
    Criacao
*/
ArvoreAVL* criarAVL() {
    ArvoreAVL* arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;

    return arvore;                
}

NodoAVL* criarNodoAVL(NodoAVL* pai, int valor) {
    printf("Adicionando %d\n", valor);

    NodoAVL* nodo = malloc(sizeof(NodoAVL));
    nodo->valor    = valor;
    nodo->pai      = pai;           
    nodo->esquerda = NULL;          
    nodo->direita  = NULL;         

    return nodo;                    
}

/*
    Balanceamento
*/

NodoAVL* rse(ArvoreAVL* arvore, NodoAVL* nodo) {
    NodoAVL* pai    = nodo->pai;
    NodoAVL* direita = nodo->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = nodo;
    }

    nodo->direita = direita->esquerda;
    nodo->pai     = direita;

    direita->esquerda = nodo;
    direita->pai      = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == nodo) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

NodoAVL* rsd(ArvoreAVL* arvore, NodoAVL* nodo) {
    NodoAVL* pai     = nodo->pai;
    NodoAVL* esquerda = nodo->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = nodo;
    }

    nodo->esquerda = esquerda->direita;
    nodo->pai      = esquerda;

    esquerda->direita = nodo;
    esquerda->pai     = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == nodo) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

NodoAVL* rde(ArvoreAVL* arvore, NodoAVL* nodo) {
    nodo->direita = rsd(arvore, nodo->direita);
    return rse(arvore, nodo);
}

NodoAVL* rdd(ArvoreAVL* arvore, NodoAVL* nodo) {
    nodo->esquerda = rse(arvore, nodo->esquerda);
    return rsd(arvore, nodo);
}

int altura(NodoAVL* nodo) {
    int esquerda = 0, direita = 0;
    if (nodo->esquerda != NULL) {
        esquerda = altura(nodo->esquerda) + 1;
    }
    if (nodo->direita != NULL) {
        direita = altura(nodo->direita) + 1;
    }
    return esquerda > direita ? esquerda : direita;
}

int fb(NodoAVL* nodo) {
    int esquerda = 0, direita = 0;
    if (nodo->esquerda != NULL) {
        esquerda = altura(nodo->esquerda) + 1;
    }
    if (nodo->direita != NULL) {
        direita = altura(nodo->direita) + 1;
    }
    return esquerda - direita;
}

void balanceamentoAVL(ArvoreAVL* arvore, NodoAVL* nodo) {
    while (nodo != NULL) {
        int fator = fb(nodo);

        if (fator > 1) {
            if (fb(nodo->esquerda) > 0) {
                printf("RSD(%d)\n", nodo->valor);
                rsd(arvore, nodo);
            } else {
                printf("RDD(%d)\n", nodo->valor);
                rdd(arvore, nodo);
            }
        } else if (fator < -1) {
            if (fb(nodo->direita) < 0) {
                printf("RSE(%d)\n", nodo->valor);
                rse(arvore, nodo);
            } else {
                printf("RDE(%d)\n", nodo->valor);
                rde(arvore, nodo);
            }
        }

        nodo = nodo->pai;
    }
}

/*
    Operacoes
*/

NodoAVL* adicionarNodoAVL(NodoAVL* nodo, int valor) {
    if (valor > nodo->valor) {
        if (nodo->direita == NULL) {
            NodoAVL* nodoNovo = criarNodoAVL(nodo, valor);
            nodo->direita = nodoNovo;

            return nodoNovo;
        } else {
            return adicionarNodoAVL(nodo->direita, valor);
        }
    } else {
        if (nodo->esquerda == NULL) {
            NodoAVL* nodoNovo = criarNodoAVL(nodo, valor);
            nodo->esquerda = nodoNovo;

            return nodoNovo;
        } else {
            return adicionarNodoAVL(nodo->esquerda, valor);
        }
    }
}

NodoAVL* adicionarChaveAVL(ArvoreAVL* arvore, int valor) {
    if (arvore->raiz == NULL) {     /* era: vazia(avl_arvore_s) */
        NodoAVL* nodoNovo = criarNodoAVL(NULL, valor);
        arvore->raiz = nodoNovo;

        return nodoNovo;
    } else {
        NodoAVL* nodo = adicionarNodoAVL(arvore->raiz, valor);
        balanceamentoAVL(arvore, nodo);

        return nodo;
    }
}

// REMOVER
