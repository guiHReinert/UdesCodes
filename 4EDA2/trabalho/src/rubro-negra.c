#include "../include/arvores.h"

/*
    Criacao
*/

ArvoreRN* criarRN() {
    ArvoreRN* arvore = malloc(sizeof(ArvoreRN));

    NodoRN* nulo = malloc(sizeof(NodoRN));
    nulo->cor      = Preto;
    nulo->esquerda = nulo;
    nulo->direita  = nulo;
    nulo->pai      = nulo;
    nulo->valor    = 0;

    arvore->nulo = nulo;
    arvore->raiz = nulo;

    return arvore;
}

NodoRN* criarNodoRN(ArvoreRN* arvore, NodoRN* pai, int chave, Cor cor) {
    NodoRN* nodo = malloc(sizeof(NodoRN));

    nodo->pai      = pai;
    nodo->esquerda = arvore->nulo;
    nodo->direita  = arvore->nulo;
    nodo->valor    = chave;
    nodo->cor      = cor;

    return nodo;
}

/*
    Operacoes
*/

NodoRN* localizarNodoRN(ArvoreRN* arvore, NodoRN* nodo, int chave) {
    if (nodo->valor == chave) {
        return nodo;
    } else {
        if (chave < nodo->valor) {
            if (nodo->esquerda != arvore->nulo) {
                return localizarNodoRN(arvore, nodo->esquerda, chave);
            }
        } else {
            if (nodo->direita != arvore->nulo) {
                return localizarNodoRN(arvore, nodo->direita, chave);
            }
        }
    }

    return arvore->nulo;
}

// Busca da posicao do novo nodo
static NodoRN* adicionarNodoRN(ArvoreRN* arvore, NodoRN* nodo, int chave) {
    if (chave > nodo->valor) {
        if (nodo->direita == arvore->nulo) {
            NodoRN* nodoNovo = criarNodoRN(arvore, nodo, chave, Vermelho);
            nodo->direita = nodoNovo;
            return nodoNovo;
        } else {
            return adicionarNodoRN(arvore, nodo->direita, chave);
        }
    } else {
        if (nodo->esquerda == arvore->nulo) {
            NodoRN* nodoNovo = criarNodoRN(arvore, nodo, chave, Vermelho);
            nodo->esquerda = nodoNovo;
            return nodoNovo;
        } else {
            return adicionarNodoRN(arvore, nodo->esquerda, chave);
        }
    }
}

void adicionarChaveRN(ArvoreRN* arvore, int chave) {
    if (arvore->raiz == arvore->nulo) {
        arvore->raiz = criarNodoRN(arvore, arvore->nulo, chave, Preto);
    } else {
        NodoRN* nodo = adicionarNodoRN(arvore, arvore->raiz, chave);
        balancearRN(arvore, nodo);
    }
}

// Fonte:
// https://www.geeksforgeeks.org/dsa/deletion-in-red-black-tree/

void removerChaveRN(ArvoreRN* arvore, int chave) {

    // Arvore vazia
    if (arvore->raiz == arvore->nulo) {return;}

    NodoRN* nodo = localizarNodoRN(arvore, arvore->raiz, chave);
    if (nodo == arvore->nulo) {
        printf("\t\t\t\t\tNodo %d nao encontrado.\n", chave);
        return;
    }
    printf("REMOVER NODO %d: (%d) (%d)\n\n", chave,
        nodo->esquerda->valor, nodo->direita->valor);

    NodoRN* pai = nodo->pai;
    
    // Nodo sem filhos
    if (nodo->esquerda == arvore->nulo && nodo->direita == arvore->nulo) {
        printf("\tSEM FILHOS\n");
        // Arvore unitaria
        if (pai == arvore->nulo) {
            arvore->raiz = arvore->nulo;
        }
        // Eh uma folha ah esquerda
        else if (nodo == pai->esquerda) {
            pai->esquerda = arvore->nulo;
        } else {
            pai->direita = arvore->nulo;
        }

        free(nodo);
        balancearRN(arvore, pai);
        return;
        
    // Nodo com 1 filho (XOR)
    } else if (
        (nodo->esquerda != arvore->nulo || nodo->direita != arvore->nulo) &&
        !(nodo->esquerda != arvore->nulo && nodo->direita != arvore->nulo)
    ) {
        printf("\tUM FILHO\n");
        NodoRN* filho = (nodo->esquerda != arvore->nulo ?
            nodo->esquerda : nodo->direita);

        // nodo eh a raiz
        if (pai == arvore->nulo) {
            arvore->raiz = filho;
            filho->pai = arvore->nulo;

        // nodo eh o filho da esquerda de pai, logo serah ocupado por filho
        } else if (nodo == pai->esquerda) {
            pai->esquerda = filho;
            filho->pai = pai;
        } else {
            pai->direita = filho;
            filho->pai = pai;
        }

        free(nodo);
        balancearRN(arvore, pai);
        return;
    
    // Nodo com 2 filhos
    } else {
        printf("\tFUDEU\n");

        // Encontra o sucessor (menor da subarvore direita)
        NodoRN* sucessor = nodo->direita;
        while (sucessor->esquerda != arvore->nulo) {
            sucessor = sucessor->esquerda;
        }

        // Salva a cor original do sucessor para saber se precisara balancear
        Cor corOriginal = sucessor->cor;

        // Filho direito do sucessor (unico filho possivel, pois esquerda e nulo)
        NodoRN* filhoSucessor = sucessor->direita;

        if (sucessor->pai != nodo) {
            // Sucessor nao e filho direto — desconecta e reconecta
            sucessor->pai->esquerda = filhoSucessor;
            filhoSucessor->pai      = sucessor->pai;
            sucessor->direita       = nodo->direita;
            sucessor->direita->pai  = sucessor;
        } else {
            // Sucessor e filho direto — filhoSucessor ja esta no lugar certo
            filhoSucessor->pai = sucessor;
        }

        // Coloca o sucessor no lugar do nodo em ambos os casos
        if (nodo->pai == arvore->nulo) {
            arvore->raiz = sucessor;
        } else if (nodo->pai->esquerda == nodo) {
            nodo->pai->esquerda = sucessor;
        } else {
            nodo->pai->direita = sucessor;
        }

        sucessor->pai           = nodo->pai;
        sucessor->esquerda      = nodo->esquerda;
        sucessor->esquerda->pai = sucessor;
        sucessor->cor           = nodo->cor;

        free(nodo);

        if (corOriginal == Preto) {
            balancearRN(arvore, filhoSucessor);
        }
        return;
    }
}

/*
    Balanceamento
*/

void rotEsquerdaRN(ArvoreRN* arvore, NodoRN* nodo) {
    NodoRN* direita = nodo->direita;
    nodo->direita = direita->esquerda;

    // Se houver filho a esquerda em direita, ele sera pai do no
    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = nodo;
    }

    // Ajusta pai do no a direita
    direita->pai = nodo->pai;

    if (nodo->pai == arvore->nulo) {
        // No e raiz: direita sera a nova raiz da arvore
        arvore->raiz = direita;
    } else if (nodo == nodo->pai->esquerda) {
        // Corrige relacao pai-filho do novo pai (esquerda)
        nodo->pai->esquerda = direita;
    } else {
        // Corrige relacao pai-filho do novo pai (direita)
        nodo->pai->direita = direita;
    }

    // Corrige relacao pai-filho entre o no pivo e o no a direita
    direita->esquerda = nodo;
    nodo->pai = direita;
}

void rotDireitaRN(ArvoreRN* arvore, NodoRN* nodo) {
    NodoRN* esquerda = nodo->esquerda;
    nodo->esquerda = esquerda->direita;

    // Se houver filho a direita em esquerda, ele sera pai do no
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = nodo;
    }

    // Ajusta pai do no a esquerda
    esquerda->pai = nodo->pai;

    if (nodo->pai == arvore->nulo) {
        // No e raiz: esquerda sera a nova raiz da arvore
        arvore->raiz = esquerda;
    } else if (nodo == nodo->pai->esquerda) {
        // Corrige relacao pai-filho do novo pai (esquerda)
        nodo->pai->esquerda = esquerda;
    } else {
        // Corrige relacao pai-filho do novo pai (direita)
        nodo->pai->direita = esquerda;
    }

    // Corrige relacao pai-filho entre o no pivo e o no a esquerda
    esquerda->direita = nodo;
    nodo->pai = esquerda;
}

void balancearRN(ArvoreRN* arvore, NodoRN* nodo) {

    // Garante que todos os niveis foram balanceados
    while (nodo->pai != arvore->nulo && nodo->pai->cor == Vermelho) {
        if (nodo->pai == nodo->pai->pai->esquerda) {
            NodoRN* tio = nodo->pai->pai->direita;

            if (tio->cor == Vermelho) {

                // Caso 2 — tio vermelho: recolorir e subir
                tio->cor = Preto;
                nodo->pai->cor = Preto;
                nodo->pai->pai->cor = Vermelho;
                nodo = nodo->pai->pai;
            } else {

                // Tio e preto
                if (nodo == nodo->pai->direita) {

                    // Caso 3 — no esta a direita: rotacionar para alinhar
                    nodo = nodo->pai;
                    rotEsquerdaRN(arvore, nodo);
                }

                // Caso 4 — no esta a esquerda: recolorir e rotacionar
                nodo->pai->cor = Preto;
                nodo->pai->pai->cor = Vermelho;
                rotDireitaRN(arvore, nodo->pai->pai);
            }
        } else {

            // Espelho: pai e filho direito do avo
            NodoRN* tio = nodo->pai->pai->esquerda;

            if (tio->cor == Vermelho) {

                // Caso 2 espelhado — tio vermelho: recolorir e subir
                tio->cor = Preto;
                nodo->pai->cor = Preto;
                nodo->pai->pai->cor = Vermelho;
                nodo = nodo->pai->pai;
            } else {

                // Tio e preto
                if (nodo == nodo->pai->esquerda) {

                    // Caso 3 espelhado — no esta a esquerda: rotacionar para alinhar
                    nodo = nodo->pai;
                    rotDireitaRN(arvore, nodo);
                }

                // Caso 4 espelhado — no esta a direita: recolorir e rotacionar
                nodo->pai->cor = Preto;
                nodo->pai->pai->cor = Vermelho;
                rotEsquerdaRN(arvore, nodo->pai->pai);
            }
        }
    }

    // Caso 1 — garante que a raiz e sempre preta
    arvore->raiz->cor = Preto;
}

static void fixBB(ArvoreRN* arvore, NodoRN* nodo) {
    printf("SERAH FIXADO\n");
}

static void printarNodoRN(ArvoreRN* arvore, NodoRN* nodo, int profundidade) {
    if (nodo == arvore->nulo) {return;}
    printarNodoRN(arvore, nodo->direita, profundidade + 1);
    for (int i = 0; i < profundidade; i++) {
        printf("\t");
    }
    printf("%s %d%s\n",
        nodo == arvore->raiz ? "[R]" : "",
        nodo->valor,
        nodo->cor == Vermelho ? "(V)" : "(P)"
    );
    printarNodoRN(arvore, nodo->esquerda, profundidade + 1);
}

void printarRN(ArvoreRN* arvore) {
    printarNodoRN(arvore, arvore->raiz, 0);
}
