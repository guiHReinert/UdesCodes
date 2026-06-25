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
    int* nums = malloc(sizeof(int)*conj->num);
    srand(time(NULL));   
    for(int i=0; i < conj->num; i++) {
        int r = rand() % conj->num;      
        nums[i] = r;
    }

    for (int n=0; n < conj->num; n++) {
        int avlAd = 0;

        adicionarChaveAVL(conj->AVL, nums[n], &avlAd);
        printf("avlAd: %d\n", avlAd);

        conj->avl[0] =+ avlAd;
    }
}

// void exportarConjunto(Conjunto* conj) {

// }

