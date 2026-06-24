#include "include/arvores.h"

void main(){
    ArvoreRN* rn = criarRN();
    ArvoreAVL* avl = criarAVL(); 
    int tamRN = 10;

    /*
        RUBRO-NEGRA
    */

    for (int i=0; i < tamRN/2+1; i++) {
        adicionarChaveRN(rn, -i);
        adicionarChaveRN(rn, i);
    }
    printarRN(rn); printf("\n");
    
    printf("\t\t Removendo Arvore Rubro-Negra\n\n");
    for (int i=0; i < tamRN/2+1; i++) {
        removerChaveRN(rn, -i);
        printarRN(rn);
        for (int i=0; i < 50; i++) {printf("-");} printf("\n");
        removerChaveRN(rn, i);
        printarRN(rn);
        for (int i=0; i < 50; i++) {printf("-");} printf("\n");
    }

    /*
        AVL
    */

    // for (int num=0; num < 10; num++) {
    //     adicionarChaveAVL(avl, num);
    //     printf("chave: %d\n", num);
    // }
    // printarAVL(avl);

    // printf("\n\t\tRemovendo AVL\n\n");
    // for (int i=0; i < 10; i++) {
    //     if (i % 2 != 0) {continue;}
    //     remocaoAVL(avl, i);
    //     printarAVL(avl);
    // }

    /*
        B
    */


    
}