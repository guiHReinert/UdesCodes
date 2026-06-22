#include "funcoes.h"

/*
    Como compilar e rodar este projeto:

clear && gcc main.c funcoes.c -o main && ./main

*/

int main(){

    /*
        Carregar o grafo
    */
    Grafo* grafo = NULL;
    
    carregar_lista_adjacencias(&grafo, "palavras_filtradas_4letras.txt");

    printf("\nVertices: %d\n", grafo->num_vertices);
    printf("Grau maximo: %d\n", grau_maximo(grafo));
    printf("Grau minimo: %d\n\n", grau_minimo(grafo));

    /*
        Verificar se eh multigrafo
    */
    int lacos = 0, repeticoes = 0;

    if(eh_multigrafo(grafo, &lacos, &repeticoes)){
        printf("Eh multigrafo: SIM\n");
        printf("Lacos: %d\n", lacos);
        printf("Arestas repetidas: %d\n\n", repeticoes);
    } else {
        printf("Eh multigrafo: NAO\n\n");
    }

    /*
        Analise dos componentes conexos
    */
    int num_componentes = 0;
    int* tamanhos = calloc(grafo->num_vertices, sizeof(int));
    int** componentes = componentes_conexos(grafo, &num_componentes, tamanhos);

    int soma = 0;

    for(int i = 0; i < num_componentes; i++){
        soma += tamanhos[i];
    }

    printf("Soma: %d\n", soma);
    printf("Vertices: %d\n\n", grafo->num_vertices);

    printf("Componentes: %d\n\n", num_componentes);

    for(int i = 0; i < num_componentes; i++){
        printf("Componente %d: %d vertices\n", i + 1, tamanhos[i]);
    }
    printf("\n");
    
    analisar_componentes(grafo);

    /*
        Busca de caminho minimo por Dijkstra
    */
    char origem[10], destino[10];

    printf("Origem: ");
    scanf("%s", origem);

    printf("Destino: ");
    scanf("%s", destino);

    dijkstra(grafo, origem, destino);

    return 0;
}
    

