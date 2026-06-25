#include "../include/arvores.h"

/*
    Criacao
*/

ArvoreB* criarArvoreB(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));

    a->ordem = ordem;
    a->raiz = criarNodoB(a);

    return a;
}

NodoB* criarNodoB(ArvoreB* arvore) {
    NodoB* nodo = malloc(sizeof(NodoB));
    int max = arvore->ordem * 2;

    nodo->pai = NULL;
    nodo->chaves = malloc(sizeof(int) * (max + 1));
    nodo->filhos = malloc(sizeof(NodoB) * (max + 2));
    nodo->total = 0;

    for (int i = 0; i < max + 2; i++) {
        nodo->filhos[i] = NULL;
    }
    
    return nodo;
}

/*
    Operacoes
*/

int pesquisaBinariaB(NodoB* nodo, int chave) {
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

void percorrerArvoreB(NodoB* nodo, void (*visita)(int chave, void* ctx), void* ctx) {
    if (nodo != NULL) {
        for (int i = 0; i < nodo->total; i++){
            percorrerArvoreB(nodo->filhos[i], visita, ctx);
            printf("(%d)\n", nodo->chaves[i]);
        }
        percorrerArvoreB(nodo->filhos[nodo->total], visita, ctx);
    }
}

int localizarChaveB(ArvoreB* arvore, int chave) {
    NodoB *nodo = arvore->raiz;
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

NodoB* localizarNodoB(ArvoreB* arvore, int chave) {
    NodoB *nodo = arvore->raiz;
    while (nodo != NULL) {
        int i = pesquisaBinariaB(nodo, chave);
    if (nodo->filhos[i] == NULL)
        return nodo; //encontrou nó
    else
        nodo = nodo->filhos[i];
    }
    return NULL; //não encontrou nenhum nó
}

// Split: divide as chaves de um nodo
NodoB* dividirNodoB(ArvoreB* arvore, NodoB* nodo) {
    int meio = nodo->total / 2;
    NodoB* novo = criarNodoB(arvore);
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
int transbordoB(ArvoreB *arvore, NodoB *nodo) {
    return nodo->total > arvore->ordem * 2;
}

void adicionarChaveNodoB(NodoB* nodo, NodoB* direita, int chave) {
    int i = pesquisaBinariaB(nodo, chave);
    for (int j = nodo->total - 1; j >= i; j--) {
        nodo->chaves[j + 1] = nodo->chaves[j];
        nodo->filhos[j + 2] = nodo->filhos[j + 1];
    }
    nodo->chaves[i] = chave;
    nodo->filhos[i + 1] = direita;
    nodo->total++;
}

static void adicionarChaveRecursivoB(ArvoreB* arvore, NodoB* nodo, NodoB* novo, int chave) {
adicionarChaveNodoB(nodo, novo, chave);
if (transbordoB(arvore, nodo)) {
    int promovido = nodo->chaves[arvore->ordem];
    NodoB* novo = dividirNodoB(arvore, nodo);
    if (nodo->pai == NULL) {
        NodoB* raiz = criarNodoB(arvore);
        raiz->filhos[0] = nodo;
        adicionarChaveNodoB(raiz, novo, promovido);
        nodo->pai = raiz;
        novo->pai = raiz;
        arvore->raiz = raiz;
    } else
    adicionarChaveRecursivoB(arvore, nodo->pai, novo, promovido);
    }
}

void adicionarChaveB(ArvoreB* arvore, int chave) {
    NodoB* nodo = localizarNodoB(arvore, chave);
    adicionarChaveRecursivoB(arvore, nodo, NULL, chave);
}

static void printarNodoB(ArvoreB *arvore, NodoB *nodo, int camada) {
    if (!nodo) {return;}

    // Separa-se a arvore na secao dos nodos mais ah direita, meio com a raiz, e
    // os nodos mais ah esquerda, respectivamente, de cima para baixo
    int meio = (nodo->total+1)/2;

    for (int i = nodo->total; i >= meio; i--) {
        printarNodoB(arvore, nodo->filhos[i], camada + arvore->ordem);
    }

    for (int i = 0; i < camada; i++) {printf("\t");}

    printf("%s[", nodo == arvore->raiz ? "(R)" : "");
    for (int i = 0; i < nodo->total; i++) {
        printf("%d%s",
            nodo->chaves[i],
            i + 1 < nodo->total ? "|" : ""
        );
    }
    printf("]\n");

    for (int i = meio-1; i >= 0; i--) {
        printarNodoB(arvore, nodo->filhos[i], camada + arvore->ordem);
    }

    if (nodo->total > 0) {
        printf("\n");
    }
}

void printarB(ArvoreB* arvore) {
    if (!arvore || !arvore->raiz) {return;}
    printarNodoB(arvore, arvore->raiz, 0);
}
