#include "include/conjunto.h"

int main(){
    srand(time(NULL));   

    int numAmostras = 1,
        nums[] =
        // {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000};
        // {10, 20, 50};
        {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
    int numConjuntos = sizeof(nums)/sizeof(nums[0]);

    Conjunto** conjuntos = malloc(sizeof(Conjunto)*numConjuntos);
    for (int c=0; c < numConjuntos; c++) {
        conjuntos[c] = criarConjunto(nums[c], numAmostras);
        carregarConjunto(conjuntos[c]);
    }
    exportarConjuntos(conjuntos, numConjuntos, "output/conjuntos.csv");
    exportarMedias(conjuntos, numConjuntos, "output/medias.csv");



    // int sumAVL=0, sumRN=0, sumB1=0, sumB5=0, sumB10=0,
    //     remsAVL=0, remsRN=0, remsB1=0, remsB5=0, remsB10=0,
    //     numConjuntos[] =
    //     {10, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000},
    //     // {10, 50, 100},
    //     numAmostra = 10;


    // float qnt = sizeof(numConjuntos)/sizeof(numConjuntos[0]);
    
    // clock_t t = clock();
    // for (int n=0; n < qnt; n++) {
    //     printf("\n\t\tCONJUNTO %d: %d\n\n", n+1, numConjuntos[n]);
    //     Conjunto* conj = criarConjunto(numConjuntos[n], numAmostra);
    //     carregarConjunto(conj);

    //     printf("\nsumAVL:\t%d\t\tremsAVL: %d\n", conj->avl[0], conj->avl[1]);
    //     printf("sumRN:\t%d\t\tremsRN: %d\n", conj->rn[0], conj->rn[1]);
    //     printf("sumB1:\t%d\t\tremsB1: %d\n", conj->b1[0], conj->b1[1]);
    //     printf("sumB5:\t%d\t\tremsB5: %d\n", conj->b5[0], conj->b5[1]);
    //     printf("sumB10:\t%d\t\tremsB10: %d\n\n", conj->b10[0], conj->b10[1]);

    //     sumAVL += conj->avl[0];
    //     sumRN += conj->rn[0];
    //     sumB1 += conj->b1[0];
    //     sumB5 += conj->b5[0];
    //     sumB10 += conj->b10[0];
    //     remsAVL += conj->avl[1];
    //     remsRN += conj->rn[1];
    //     remsB1 += conj->b1[1];
    //     remsB5 += conj->b5[1];
    //     remsB10 += conj->b10[1];
    // }
    // t = clock() - t;
    // double tempoTotal = ((double)t)/CLOCKS_PER_SEC;

    // printf("\n\t\tMEDIA POR ARVORE\n\n");
    // printf("Tempo total: %f s\n\n", tempoTotal);
    // printf("sumAVL:\t%.2f\t\tremsAVL: %.2f\n",
    //     (double)sumAVL/qnt, (double)remsAVL/qnt);
    // printf("sumRN:\t%.2f\t\tremsRN: %.2f\n",
    //     (double)sumRN/qnt, (double)remsRN/qnt);
    // printf("sumB1:\t%.2f\t\tremsB1: %.2f\n",
    //     (double)sumB1/qnt, (double)remsB1/qnt);
    // printf("sumB5:\t%.2f\t\tremsB5: %.2f\n",
    //     (double)sumB5/qnt, (double)remsB5/qnt);
    // printf("sumB10:\t%.2f\t\tremsB10: %.2f\n",
    //     (double)sumB10/qnt, (double)remsB10/qnt);

    return 0;
}