#include "../include/arvores.h"

/*
    Criacao
*/

BArvore* criarArvoreB(int ordem) {
    BArvore* a = malloc(sizeof(BArvore));
    a->ordem = ordem;
    a->raiz = criarNodoB(a);
    return a;
}

BNodo* criarNodoB(BArvore* arvore) {
    int max = arvore->ordem * 2;
    BNodo* nodo = malloc(sizeof(BNodo));
    nodo->pai = NULL;
    nodo->chaves = malloc(sizeof(int) * (max + 1));
    nodo->filhos = malloc(sizeof(BNodo) * (max + 2));
    nodo->total = 0;
    for (int i = 0; i < max + 2; i++)
    nodo->filhos[i] = NULL;
    return nodo;
}

/*
    Operacoes
*/

int pesquisaBinariaB(BNodo* nodo, int chave) {
    int inicio = 0, fim = nodo->total - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (nodo->chaves[meio] == chave) {
            return meio; //encontrou
        } else if (nodo->chaves[meio] > chave) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return inicio; //não encontrou
}

// Percorre todos os nodos da arvore.
void percorrerArvoreB(BNodo* nodo, void (visita)(int chave)) {
    if (nodo != NULL) {
        for (int i = 0; i < nodo->total; i++){
            percorrerArvoreB(nodo->filhos[i], visita);
            printf("(%d)\n", nodo->chaves[i]);
        }
        percorrerArvoreB(nodo->filhos[nodo->total], visita);
    }
}

// Busca uma chave.
int localizarChaveB(BArvore* arvore, int chave) {
    BNodo *nodo = arvore->raiz;
    while (nodo != NULL) {
        int i = pesquisaBinariaB(nodo, chave);
        if (i < nodo->total && nodo->chaves[i] == chave) {
            return 1; //encontrou
        } else {
            nodo = nodo->filhos[i];
        }
    }
    return 0; //não encontrou
}

// Busca um nodo a partir de uma chave.
BNodo* localizarNodoB(BArvore* arvore, int chave) {
    BNodo *nodo = arvore->raiz;
    while (nodo != NULL) {
        int i = pesquisaBinariaB(nodo, chave);
        if (nodo->filhos[i] == NULL)
            return nodo; //encontrou nó
        else
            nodo = nodo->filhos[i];
    }
    return NULL; //não encontrou nenhum nó
}

// Split: divide as chaves de um nodo.
BNodo* dividirNodoB(BArvore* arvore, BNodo* nodo) {
    int meio = nodo->total / 2;
    BNodo* novo = criarNodoB(arvore);
    novo->pai = nodo->pai;
    for (int i = meio + 1; i < nodo->total; i++) {
        novo->filhos[novo->total] = nodo->filhos[i];
        novo->chaves[novo->total] = nodo->chaves[i];
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
            novo->total++;
    }
    novo->filhos[novo->total] = nodo->filhos[nodo->total];
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
    nodo->total = meio;
    return novo;
}

// Verifica overflow em um nodo
int transbordoB(BArvore *arvore, BNodo *nodo) {
    return nodo->total > arvore->ordem * 2;
}

// Adiciona uma chave em um nodo.
void adicionarChaveNodoB(BNodo* nodo, BNodo* direita, int chave) {
    int i = pesquisaBinariaB(nodo, chave);
    for (int j = nodo->total - 1; j >= i; j--) {
        nodo->chaves[j + 1] = nodo->chaves[j];
        nodo->filhos[j + 2] = nodo->filhos[j + 1];
    }
    nodo->chaves[i] = chave;
    nodo->filhos[i + 1] = direita;
    nodo->total++;
}

// Adicionar uma chave.
void adicionarChaveB(BArvore* arvore, int chave) {
    BNodo* nodo = localizarNodoB(arvore, chave);
    adicionarChaveRecursivoB(arvore, nodo, NULL, chave);
}
void adicionarChaveRecursivoB(BArvore* arvore, BNodo* nodo, BNodo* novo, int chave) {
adicionarChaveNodoB(nodo, novo, chave);
if (transbordoB(arvore, nodo)) {
    int promovido = nodo->chaves[arvore->ordem];
    BNodo* novo = dividirNodoB(arvore, nodo);
    if (nodo->pai == NULL) {
        BNodo* raiz = criarNodoB(arvore);
        raiz->filhos[0] = nodo;
        adicionarChaveNodoB(raiz, novo, promovido);
        nodo->pai = raiz;
        novo->pai = raiz;
        arvore->raiz = raiz;
    } else
    adicionarChaveRecursivoB(arvore, nodo->pai, novo, promovido);
    }
}
