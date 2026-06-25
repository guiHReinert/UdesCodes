#include "../include/conjunto.h"

Conjunto* criarConjunto(int num) {
    Conjunto* conj = malloc(sizeof(Conjunto));
    if (conj == NULL) { return NULL; }

    conj->num = num;

    conj->AVL = criarAVL();
    conj->RN = criarRN();
    conj->B1 = criarArvoreB(1);
    conj->B5 = criarArvoreB(5);
    conj->B10 = criarArvoreB(10);

    conj->avl = malloc(sizeof(int)*2);
    conj->rn = malloc(sizeof(int)*2);
    conj->b1 = malloc(sizeof(int)*2);
    conj->b5 = malloc(sizeof(int)*2);
    conj->b10 = malloc(sizeof(int)*2);

    return conj;
}

void carregarConjunto(Conjunto* conj) {
    int* adicoes = malloc(sizeof(int)*conj->num);
    for(int i=0; i < conj->num; i++) {
        int r = rand() % 10000;      
        adicoes[i] = r;
    }
    int* remocoes = malloc(sizeof(int)*conj->num);
    for(int i=0; i < conj->num; i++) {
        int r = rand() % 10000;      
        remocoes[i] = r;
    }

    clock_t t;
    t = clock();

    int adAVL, adRN, adB, remAVL, remRN, remB;

    // Insercao das chaves
    for (int n=0; n < conj->num; n++) {
        adAVL = 0;
        adicionarChaveAVL(conj->AVL, adicoes[n], &adAVL);
        conj->avl[0] += adAVL;
        adRN = 0;
        adicionarChaveRN(conj->RN, adicoes[n], &adRN);
        conj->rn[0] += adRN; 
        adB = 0;
        adicionarChaveB(conj->B1, adicoes[n], &adB);
        conj->b1[0] += adB; 
        adB = 0;
        adicionarChaveB(conj->B5, adicoes[n], &adB);
        conj->b5[0] += adB; 
        adB = 0;
        adicionarChaveB(conj->B10, adicoes[n], &adB);
        conj->b10[0] += adB; 
    }

    // Remocao das chaves
    for (int n=0; n < conj->num; n++) {
        remAVL = 0;
        remocaoAVL(conj->AVL, remocoes[n], &remAVL);
        conj->avl[1] += remAVL;

    //     remRN = 0;
    //     removerChaveRN(conj->RN, remocoes[n], &remRN);
    //     conj->rn[1] += remRN;

    //     remB = 0;
    //     removerChaveB(conj->b1, remocoes[n], &remB);
    //     conj->b1[1] += remB;

    //     remB = 0;
    //     removerChaveB(conj->b5, remocoes[n], &remB);
    //     conj->b5[1] += remB;

    //     remB = 0;
    //     removerChaveB(conj->b10, remocoes[n], &remB);
    //     conj->b10[1] += remB;
    }

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC;
    printf("\n\nTempo: %lf s\n", tempo);
}

// void exportarConjunto(Conjunto* conj) {

// }

