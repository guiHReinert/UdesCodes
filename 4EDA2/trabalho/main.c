#include "include/conjunto.h"

int main(){
    srand(time(NULL));   

    int numAmostras = 10, numConjuntos = 100;
    int* nums = malloc(sizeof(int)*numConjuntos);

    for (int n=0; n < numConjuntos; n++) {
        nums[n] = 100 + 100*n;
    }

    Conjunto **conjuntos = malloc(sizeof *conjuntos * numConjuntos);  

    time_t t = clock(); 
    for (int c=0; c < numConjuntos; c++) {
        conjuntos[c] = criarConjunto(nums[c], numAmostras);
        carregarConjunto(conjuntos[c]);
    }
    float total = ((float)(clock() - t))/CLOCKS_PER_SEC;
    printf("\nTempo total: %dmin%ds\n", (int)total/60, (int)total%60);
    
    exportarConjuntos(conjuntos, numConjuntos, "output/conjuntos.csv");
    free(conjuntos);

    return 0;
}