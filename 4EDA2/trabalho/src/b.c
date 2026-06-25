#include "../include/conjunto.h"

/*
    CRIACAO
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
    OPERACOES
*/

int pesquisaBinariaB(NodoB* nodo, int chave) {
    int inicio = 0, fim = nodo->total - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (nodo->chaves[meio] == chave) {
            return meio;
        } else if (nodo->chaves[meio] > chave) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return inicio;
}

void percorrerArvoreB(NodoB* nodo, void (*visita)(int chave, void* ctx), void* ctx) {
    if (nodo != NULL) {
        for (int i = 0; i < nodo->total; i++) {
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
        if (i < nodo->total && nodo->chaves[i] == chave) {return 1;} else {
            nodo = nodo->filhos[i];
        }
    }
    return 0;
}

/*
    ADICAO DE CHAVES
*/

NodoB* localizarNodoB(ArvoreB* arvore, int chave) {
    NodoB *nodo = arvore->raiz;
    while (nodo != NULL) {
        int i = pesquisaBinariaB(nodo, chave);
        if (nodo->filhos[i] == NULL) {
            return nodo;
        } else {
            nodo = nodo->filhos[i];
        }
    }
    return NULL;
}

// Split: divide as chaves de um nodo
NodoB* dividirNodoB(ArvoreB* arvore, NodoB* nodo) {
    int meio = nodo->total / 2;
    NodoB* novo = criarNodoB(arvore);
    novo->pai = nodo->pai;

    for (int i = meio + 1; i < nodo->total; i++) {
        novo->filhos[novo->total] = nodo->filhos[i];
        novo->chaves[novo->total] = nodo->chaves[i];
        if (novo->filhos[novo->total] != NULL) {
            novo->filhos[novo->total]->pai = novo;
        }
        novo->total++;
    }

    novo->filhos[novo->total] = nodo->filhos[nodo->total];

    if (novo->filhos[novo->total] != NULL) {
        novo->filhos[novo->total]->pai = novo;
    }
    nodo->total = meio;

    return novo;
}

int overflowB(ArvoreB *arvore, NodoB *nodo) {
    return nodo->total > arvore->ordem * 2;
}

void adicionarChaveNodoB(NodoB* nodo, NodoB* direita, int chave, int* count) {
    int i = pesquisaBinariaB(nodo, chave);
    for (int j = nodo->total - 1; j >= i; j--) {
        nodo->chaves[j + 1] = nodo->chaves[j];
        nodo->filhos[j + 2] = nodo->filhos[j + 1];
        // (*count)++;
    }
    nodo->chaves[i] = chave;
    nodo->filhos[i + 1] = direita;
    nodo->total++;
}

static void adicionarChaveRecursivoB(ArvoreB* arvore, NodoB* nodo, NodoB* novo,
    int chave, int* count) {
    (*count)++;
    adicionarChaveNodoB(nodo, novo, chave, count);
    if (overflowB(arvore, nodo)) {
        int promovido = nodo->chaves[arvore->ordem];
        NodoB* novo = dividirNodoB(arvore, nodo);

        if (nodo->pai == NULL) {
            NodoB* raiz = criarNodoB(arvore);
            raiz->filhos[0] = nodo;
            adicionarChaveNodoB(raiz, novo, promovido, count);
            nodo->pai = raiz;
            novo->pai = raiz;
            arvore->raiz = raiz;
        } else {
            adicionarChaveRecursivoB(arvore, nodo->pai, novo, promovido, count);
        }
    }
}

void adicionarChaveB(ArvoreB* arvore, int chave, int* count) {
    NodoB* nodo = localizarNodoB(arvore, chave);
    adicionarChaveRecursivoB(arvore, nodo, NULL, chave, count);
}

/*
    REMOCAO DE CHAVES
*/

// Merge: filho + chave do pai + irmao direito → um nodo so
static NodoB* mergeB(ArvoreB* arvore, NodoB* pai, int idx_esq) {
    NodoB* esq = pai->filhos[idx_esq];
    NodoB* dir = pai->filhos[idx_esq + 1];

    esq->chaves[esq->total] = pai->chaves[idx_esq];
    esq->total++;

    for (int j = 0; j < dir->total; j++) {
        esq->chaves[esq->total] = dir->chaves[j];
        esq->filhos[esq->total] = dir->filhos[j];
        if (esq->filhos[esq->total] != NULL) {
            esq->filhos[esq->total]->pai = esq;
        }
        esq->total++;
    }
    esq->filhos[esq->total] = dir->filhos[dir->total];
    if (esq->filhos[esq->total] != NULL) {
        esq->filhos[esq->total]->pai = esq;
    }

    for (int j = idx_esq; j < pai->total - 1; j++) {
        pai->chaves[j] = pai->chaves[j + 1];
        pai->filhos[j + 1] = pai->filhos[j + 2];
    }
    pai->total--;

    free(dir->chaves);
    free(dir->filhos);
    free(dir);

    if (pai->pai == NULL && pai->total == 0) {
        arvore->raiz = esq;
        esq->pai = NULL;
        free(pai->chaves);
        free(pai->filhos);
        free(pai);
    }

    return esq;
}

static void fixUnderflowB(ArvoreB* arvore, NodoB* nodo) {
    if (nodo->pai == NULL || nodo->total >= arvore->ordem) {return;}

    NodoB* pai = nodo->pai;

    int idx = -1; // Indice do nodo relativo aos filhos do seu pai
    for (int i = 0; i <= pai->total; i++) {
        if (pai->filhos[i] == nodo) {
            idx = i;
            break;
        }
    }

    NodoB* irmao_esq = (idx > 0)          ? pai->filhos[idx - 1] : NULL;
    NodoB* irmao_dir = (idx < pai->total) ? pai->filhos[idx + 1] : NULL;

    if (irmao_esq != NULL && irmao_esq->total > arvore->ordem) {
        for (int j = nodo->total; j > 0; j--) {
            nodo->chaves[j]     = nodo->chaves[j - 1];
            nodo->filhos[j + 1] = nodo->filhos[j];
        }
        nodo->filhos[1] = nodo->filhos[0];

        nodo->chaves[0]  = pai->chaves[idx - 1];
        nodo->filhos[0]  = irmao_esq->filhos[irmao_esq->total];
        if (nodo->filhos[0] != NULL) {
            nodo->filhos[0]->pai = nodo;
        }

        pai->chaves[idx - 1] = irmao_esq->chaves[irmao_esq->total - 1];
        irmao_esq->total--;
        nodo->total++;

    } else if (irmao_dir != NULL && irmao_dir->total > arvore->ordem) {
        nodo->chaves[nodo->total]     = pai->chaves[idx];
        nodo->filhos[nodo->total + 1] = irmao_dir->filhos[0];
        if (nodo->filhos[nodo->total + 1] != NULL) {
            nodo->filhos[nodo->total + 1]->pai = nodo;
        }
        nodo->total++;

        pai->chaves[idx] = irmao_dir->chaves[0];

        for (int j = 0; j < irmao_dir->total - 1; j++) {
            irmao_dir->chaves[j]  = irmao_dir->chaves[j + 1];
            irmao_dir->filhos[j]  = irmao_dir->filhos[j + 1];
        }
        irmao_dir->filhos[irmao_dir->total - 1] = irmao_dir->filhos[irmao_dir->total];
        irmao_dir->total--;

    } else if (irmao_esq != NULL) {
        NodoB* merged = mergeB(arvore, pai, idx - 1);
        fixUnderflowB(arvore, merged->pai != NULL ? pai : arvore->raiz);
    } else {
        NodoB* merged = mergeB(arvore, pai, idx);
        fixUnderflowB(arvore, merged->pai != NULL ? pai : arvore->raiz);
    }
}

void removerChaveNodoB(ArvoreB* arvore, NodoB* nodo, int chave) {
    int i = pesquisaBinariaB(nodo, chave);

    if (i < nodo->total && nodo->chaves[i] == chave) {

        // Caso folha
        if (nodo->filhos[0] == NULL) {
            for (int j = i; j < nodo->total - 1; j++) {
                nodo->chaves[j] = nodo->chaves[j + 1];
            }
            nodo->total--;

            fixUnderflowB(arvore, nodo);
        } else {
            NodoB* filho = nodo->filhos[i];

            while (filho->filhos[filho->total] != NULL) {
                filho = filho->filhos[filho->total];
            }

            int predecessor = filho->chaves[filho->total - 1];
            nodo->chaves[i] = predecessor;

            removerChaveNodoB(arvore, filho, predecessor);
        }
    } else {
        if (nodo->filhos[i] == NULL) {return;}

        // Procurar a chave no nodo seguinte da mesma camada
        removerChaveNodoB(arvore, nodo->filhos[i], chave);
    }
}

void removerChaveB(ArvoreB* arvore, int chave) {
    if (arvore == NULL || arvore->raiz == NULL) {return;}
    removerChaveNodoB(arvore, arvore->raiz, chave);
}

/*
    EXPORTAR DADOS
*/

static void printarNodoB(ArvoreB *arvore, NodoB *nodo, int camada) {
    if (!nodo) {
        return;
    }

    int meio = (nodo->total + 1) / 2;

    for (int i = nodo->total; i >= meio; i--) {
        printarNodoB(arvore, nodo->filhos[i], camada + arvore->ordem);
    }

    for (int i = 0; i < camada; i++) {
        printf("\t");
    }

    printf("%s[", nodo == arvore->raiz ? "(R)" : "");
    for (int i = 0; i < nodo->total; i++) {
        printf("%d%s",
            nodo->chaves[i],
            i + 1 < nodo->total ? "|" : ""
        );
    }
    printf("]\n");

    for (int i = meio - 1; i >= 0; i--) {
        printarNodoB(arvore, nodo->filhos[i], camada + arvore->ordem);
    }

    if (nodo->total > 0) {
        printf("\n");
    }
}

void printarB(ArvoreB* arvore) {
    if (!arvore || !arvore->raiz) {
        return;
    }
    printarNodoB(arvore, arvore->raiz, 0);
}