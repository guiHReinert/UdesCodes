#include "include/conjunto.h"

int main(){
    srand(time(NULL));   

    int sumAVL=0, sumRN=0, sumB1=0, sumB5=0, sumB10=0,
        numConjuntos[] =
        {10, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000};

    float qnt = sizeof(numConjuntos)/sizeof(numConjuntos[0]);
    
    clock_t t = clock();
    for (int n=0; n < qnt; n++) {
        printf("\n\t\tCONJUNTO %d: %d", n+1, numConjuntos[n]);
        Conjunto* conj = criarConjunto(numConjuntos[n]);
        carregarConjunto(conj);

        printf("\nsumAVL: %d\n", conj->avl[0]);
        printf("sumRN: %d\n", conj->rn[0]);
        printf("sumB1: %d\n", conj->b1[0]);
        printf("sumB5: %d\n", conj->b5[0]);
        printf("sumB10: %d\n\n", conj->b10[0]);
        printf("Media: %.2f\n", (conj->avl[0] + conj->rn[0] + conj->b1[0]
            + conj->b5[0] + conj->b10[0]) / 5.0);

        sumAVL += conj->avl[0];
        sumRN += conj->rn[0];
        sumB1 += conj->b1[0];
        sumB5 += conj->b5[0];
        sumB10 += conj->b10[0];
    }
    t = clock() - t;
    double tempoTotal = ((double)t)/CLOCKS_PER_SEC;

    printf("\n\t\tMEDIA POR ARVORE\n\n");
    printf("Tempo total: %f\n\n", tempoTotal);
    printf("sumAVL: %.2f\n", (double)sumAVL/qnt);
    printf("sumRN: %.2f\n", (double)sumRN/qnt);
    printf("sumB1: %.2f\n", (double)sumB1/qnt);
    printf("sumB5: %.2f\n", (double)sumB5/qnt);
    printf("sumB10: %.2f\n", (double)sumB10/qnt);

    return 0;
}