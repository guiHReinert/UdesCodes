#include "../include/conjunto.h"

Conjunto* criarConjunto(int num, int numAmostra) {
    Conjunto* conj = malloc(sizeof(Conjunto));
    if (conj == NULL) { return NULL; }

    conj->num = num;
    conj->numAmostra = numAmostra;

    conj->AVL = criarAVL();
    conj->RN = criarRN();
    conj->B1 = criarArvoreB(1);
    conj->B5 = criarArvoreB(5);
    conj->B10 = criarArvoreB(10);

    conj->avl = calloc(2, sizeof(long));
    conj->rn = calloc(2, sizeof(long));
    conj->b1 = calloc(2, sizeof(long));
    conj->b5 = calloc(2, sizeof(long));
    conj->b10 = calloc(2, sizeof(long));

    return conj;
}

void carregarConjunto(Conjunto* conj) {

    int sumAdicoes[5] = {0}, sumRemocoes[5] = {0};
    
    clock_t t;
    t = clock();

    for (int i=0; i < conj->numAmostra; i++) {

        conj->AVL = criarAVL();
        conj->RN = criarRN();
        conj->B1 = criarArvoreB(1);
        conj->B5 = criarArvoreB(5);
        conj->B10 = criarArvoreB(10);

        // Criar dois arrays para inserir e remover chaves (shuffle por
        // Fisher-Yates)
        int* adicoes = malloc(sizeof(int) * conj->num);
        for (int i = 0; i < conj->num; i++) {
            adicoes[i] = rand() % 10000;
        }
        int* remocoes = malloc(sizeof(int) * conj->num);
        for (int i = 0; i < conj->num; i++) {
            remocoes[i] = adicoes[i];
        }
        for (int i = conj->num - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int tmp = remocoes[i];
            remocoes[i] = remocoes[j];
            remocoes[j] = tmp;
        }

        for (int k = 0; k < 5; k++) {sumAdicoes[k] = 0;}
        for (int k = 0; k < 5; k++) {sumRemocoes[k] = 0;}

        for (int j=0; j < conj->num; j++) {
            adicionarChaveAVL(conj->AVL, adicoes[j], &sumAdicoes[0]);
            adicionarChaveRN( conj->RN, adicoes[j], &sumAdicoes[1]);
            adicionarChaveB(  conj->B1, adicoes[j], &sumAdicoes[2]);
            adicionarChaveB(  conj->B5, adicoes[j], &sumAdicoes[3]);
            adicionarChaveB(  conj->B10, adicoes[j], &sumAdicoes[4]);
        }
        conj->avl[0] += sumAdicoes[0];
        conj->rn[0]  += sumAdicoes[1];
        conj->b1[0]  += sumAdicoes[2];
        conj->b5[0]  += sumAdicoes[3];
        conj->b10[0] += sumAdicoes[4];

        for (int j=0; j < conj->num; j++) {
            remocaoAVL(    conj->AVL, remocoes[j], &sumRemocoes[0]);
            removerChaveRN(conj->RN, remocoes[j], &sumRemocoes[1]);
            removerChaveB( conj->B1, remocoes[j], &sumRemocoes[2]);
            removerChaveB( conj->B5, remocoes[j], &sumRemocoes[3]);
            removerChaveB( conj->B10, remocoes[j], &sumRemocoes[4]);

        }
        conj->avl[1] += sumRemocoes[0];
        conj->rn[1]  += sumRemocoes[1];
        conj->b1[1]  += sumRemocoes[2];
        conj->b5[1]  += sumRemocoes[3];
        conj->b10[1] += sumRemocoes[4];
    }

    conj->avl[0] /= conj->numAmostra; conj->avl[1] /= conj->numAmostra;
    conj->rn[0]  /= conj->numAmostra; conj->rn[1]  /= conj->numAmostra;
    conj->b1[0]  /= conj->numAmostra; conj->b1[1]  /= conj->numAmostra;
    conj->b5[0]  /= conj->numAmostra; conj->b5[1]  /= conj->numAmostra;
    conj->b10[0] /= conj->numAmostra; conj->b10[1] /= conj->numAmostra;

    t = clock() - t;
    double tempo = ((double)t)/CLOCKS_PER_SEC;
    printf("Tempo do conjunto de %d:\t%lf s\n", conj->num, tempo);
}

void exportarConjuntos(Conjunto** conjuntos, int num, char* path) {
    FILE* file = fopen(path, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo em \"%s\".\n", path);
        return;
    }

    fprintf(file, "n_c,n_a,avl_add,avl_rem,rn_add,rn_rem,b1_add,b1_rem,b5_add,b5_rem,b10_add,b10_rem\n");

    for (int i = 0; i < num; i++) {
        Conjunto* c = conjuntos[i];
        fprintf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
            c->num, c->numAmostra,
            c->avl[0],  c->avl[1],
            c->rn[0],   c->rn[1],
            c->b1[0],   c->b1[1],
            c->b5[0],   c->b5[1],
            c->b10[0],  c->b10[1]
        );
    }

    fclose(file);
    printf("Exportado para %s.\n", path);
}

