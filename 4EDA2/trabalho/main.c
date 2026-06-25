#include "include/conjunto.h"

int main(){
    ArvoreRN* rn = criarRN();
    ArvoreAVL* avl = criarAVL(); 
    ArvoreB* b = criarArvoreB(2);
    int tamRN = 10, tamAVL = 10, tamB = 20;

    /*
        RUBRO-NEGRA
    */

    // for (int i=0; i < tamRN/2+1; i++) {
    //     adicionarChaveRN(rn, -i);
    //     adicionarChaveRN(rn, i);
    // }
    // printarRN(rn);
    
    // printf("\t\tRemovendo Arvore Rubro-Negra\n\n");
    // for (int i=0; i < tamRN/2+1; i++) {
    //     removerChaveRN(rn, -i);
    //     printarRN(rn);
        // printf("\n"); for (int i=0; i < 50; i++) {printf("-");} printf("\n\n");
    //     removerChaveRN(rn, i);
    //     printarRN(rn);
        // printf("\n"); for (int i=0; i < 50; i++) {printf("-");} printf("\n\n");
    // }

    /*
        AVL
    */

    // for (int i=0; i < tamAVL/2+1; i++) {
    //     adicionarChaveAVL(avl, -i);
    //     adicionarChaveAVL(avl, i);
    // }
    // printarAVL(avl);

    // printf("\t\tRemovendo AVL\n\n");
    // for (int i=0; i < tamAVL/2+1; i++) {
    //     printf("chave: %d, ", -i);
    //     remocaoAVL(avl, -i);
    //     printarAVL(avl);
    //     printf("\n"); for (int i=0; i < 50; i++) {printf("-");} printf("\n\n");
    //     printf("chave: %d, ", i);
    //     remocaoAVL(avl, i);
    //     printarAVL(avl);
    //     printf("\n"); for (int i=0; i < 50; i++) {printf("-");} printf("\n\n");
    // }

    /*
        B
    */

    // int ex1[] = {25, 10, 3, 8, 14, 40, 20, 9, 2, 6, 28, 11, 1};
    // for (int i=0; i < 13; i++) {
    //     adicionarChaveB(b, ex1[i]);
    // }

    // for (int i=0; i < tamB/2+1; i++) {
    //     adicionarChaveB(b, -i);
    //     adicionarChaveB(b, i);
    // }
    // printf("\t\tRemovendo B\n\n");
    // for (int i=0; i < tamB/2+1; i++) {
    //     printf("chave: %d, ", -i);
    //     removerChaveB(b, -i);
    //     printarB(b);
    //     printf("\n"); for (int i=0; i < 50; i++) {printf("-");} printf("\n\n");
    //     printf("chave: %d, ", i);
    //     removerChaveB(b, i);
    //     printarB(b);
    //     printf("\n"); for (int i=0; i < 50; i++) {printf("-");} printf("\n\n");
    // }

    // for (int i=0; i < tamB+1; i++) {
    //     // printf("chave: %d\n\n", i);
    //     adicionarChaveB(b, i);
    //     // printarB(b);
    //     // printf("\n"); for (int i=0; i < 50; i++) {printf("-");} printf("\n");
    // }
    // printarB(b);
    // printf("\t\tRemovendo B\n\n");
    // for (int i=0; i < tamB+1; i++) {
    //     printf("chave: %d\n\n", i);
    //     removerChaveB(b, i);
    //     printarB(b);
    //     printf("\n"); for (int i=0; i < 50; i++) {printf("-");} printf("\n");
    // }

    Conjunto* conj = criarConjunto(10);
    carregarConjunto(conj);


    return 0;
}