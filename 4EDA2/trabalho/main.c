#include "include/conjunto.h"

int main(){
    srand(time(NULL));   

    int numAmostras = 10,
        nums[] = {
            1, 10, 20, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000,
            8000, 9000, 10000
        };

    int numConjuntos = sizeof(nums)/sizeof(nums[0]);

Conjunto **conjuntos = malloc(sizeof *conjuntos * numConjuntos);   
 for (int c=0; c < numConjuntos; c++) {
        conjuntos[c] = criarConjunto(nums[c], numAmostras);
        carregarConjunto(conjuntos[c]);
    }
    exportarConjuntos(conjuntos, numConjuntos, "output/conjuntos.csv");
    free(conjuntos);

    return 0;
}