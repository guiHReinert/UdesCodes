#include "../include/arvores.h"

/*
    Criacao
*/

ArvoreRN* criarRN() {
    ArvoreRN* arvore = malloc(sizeof(ArvoreRN));

    arvore->raiz = NULL;
    arvore->nulo = NULL;

    return arvore;
}

NodoRN* criarNodoRN(int valor, Cor cor) {
    NodoRN* nodo = malloc(sizeof(NodoRN));

    nodo->pai = NULL;
    nodo->esquerda = NULL;
    nodo->direita = NULL;
    nodo->valor = valor;
    nodo->cor = cor;

    return nodo;
}

/*
    Operacoes
*/


// Busca da posicao do novo nodo
static NodoRN* adicionarNodoRN(ArvoreRN* arvore, int valor) {
    if (valor > atual->valor) {

        // Valor maior que todos
        if (atual->direita == NULL) {
            NodoRN* novo = criarNodoRN(valor, Vermelho);
            atual->direita = novo;
        } else {
            return adicionarNodoRN(atual->);
        }
    }
}

void adicionarChaveRN(ArvoreRN* arvore, int valor) {

    // Arvore vazia
    if (arvore->raiz == NULL) {
        NodoRN* novo = criarNodoRN(NULL, valor);
        arvore->raiz = novo;

        return novo;
    } else {
        NodoRN* novo = adicionarNodoRN();
        balancearRN(arvore, nodo);
    }
}

/*
    Balanceamento
*/

void rotEsquerdaRN(ArvoreRN* arvore, NodoRN* nodo) {
    NodoRN* direita = nodo->direita;
    nodo->direita = direita->esquerda;
    if (direita->esquerda != arvore->nulo)
        // Se houver filho à esquerda em direita, ele será pai do nó
        direita->esquerda->pai = nodo;

    // Ajusta nodo pai do nó à direita
    direita->pai = nodo->pai;

    if (nodo->pai == arvore->nulo)
        // Se nó for raiz, o nó direita será a nova raiz da árvore
        arvore->raiz = direita;
    else if (nodo == nodo->pai->esquerda)
        // Corrige relação pai-filho do novo pai (esquerda)
        nodo->pai->esquerda = direita;
    else
        // Corrige relação pai-filho do novo pai (direita)
        nodo->pai->direita = direita;

    // Corrige relação pai-filho entre o nó pivô e o nó à direita
    direita->esquerda = nodo;
    nodo->pai = direita;
}

void rotDireitaRN(ArvoreRN* arvore, NodoRN* nodo) {
    NodoRN* esquerda = nodo->esquerda;
    nodo->esquerda = esquerda->direita;
    if (esquerda->direita != arvore->nulo)
        // Se houver filho à direita em esquerda, ele será pai do nó
        esquerda->direita->pai = nodo;
        // Ajusta nodo pai do nó à esquerda
        esquerda->pai = nodo->pai;
    if (nodo->pai == arvore->nulo)
        // Se nó for raiz, o nó esquerda será a nova raiz da árvore
        arvore->raiz = esquerda;
    else if (nodo == nodo->pai->esquerda)
        // Corrige relação pai-filho do novo pai (esquerda)
        nodo->pai->esquerda = esquerda;
    else
        // Corrige relação pai-filho do novo pai (direita)
        nodo->pai->direita = esquerda;
        // Corrige relação pai-filho entre o nó pivô e o nó à esquerda
        esquerda->direita = nodo;
    nodo->pai = esquerda;
}

void balancearRN(ArvoreRN* arvore, NodoRN* nodo) {
    //Garante que todos os níveis foram balanceados
    while (nodo->pai->cor == Vermelho) {
        if (nodo->pai == nodo->pai->pai->esquerda) {
            NodoRN *tio = nodo->pai->pai->direita;
            if (tio->cor == Vermelho) {
                // Resolve caso 2
                tio->cor = Preto;
                nodo->pai->cor = Preto;
                nodo->pai->pai->cor = Vermelho;
                // Vai para o nível anterior
                nodo = nodo->pai->pai;
            } else {
                if (nodo == nodo->pai->direita) {
                    // Vai para o nível anterior
                    nodo = nodo->pai;
                    // Resolve caso 3
                    rotEsquerdaRN(arvore, nodo);
                } else {
                    // Resolve caso 4
                    nodo->pai->cor = Preto;
                    nodo->pai->pai->cor = Vermelho;
                    rotDireitaRN(arvore, nodo->pai->pai);
                }
            }
        } else {
            //Repete o mesmo código do bloco if, invertendo o lado dos direita e esquerda
        }
    }
    arvore->raiz->cor = Preto; //Resolve caso 1
}


