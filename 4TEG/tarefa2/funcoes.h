#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024

typedef struct NoAdj {
    int valor;
    struct NoAdj *prox;
} NoAdj;

typedef struct Vertice{
    char* palavra;
    int grau;
    int valor;
    NoAdj* listaAdj;
} Nodo, Vertice;

/*
    O grafo apresenta uma lista de adjacencias composta por todos os vertices
    encadeados ordenadamente com os vertices com arestas em comum.
*/
typedef struct Grafo{
    Vertice* lista;
    int num_vertices;
} Grafo;


Grafo* criar_grafo(int max_vertices);
void inserir_vertice(Grafo* grafo, char* origem, char* nova);
void adicionar_aresta(Grafo* grafo, char* origem, char* destino);
void carregar_lista_adjacencias(Grafo** grafo, char* path);
int grau_maximo(Grafo* grafo);
int grau_minimo(Grafo* grafo);
void printar_lista_adjacencias(Grafo* grafo, int max_origens, int max_destinos);
int diferenca_uma_letra(char* a, char* b);
void criar_arestas(Grafo* g);
int** componentesConexos(Grafo* grafo, int* num_componentes, int* tamanhos);
void DFS_G(Grafo* grafo, int raiz, int* vet_marca, int* tamanho, int*componente);
int ehMultigrafo(Grafo* grafo, int* lacos, int* repeticoes);
int encontrar_indice(Grafo* g, char* palavra);
void dijkstra(Grafo* g, char* origem, char* destino);
int vertice_maior_grau_componente(Grafo* grafo, int* componente, int tamanho);
int vertice_menor_grau_componente(Grafo* grafo, int* componente, int tamanho);
void analisar_componentes(Grafo* grafo);



#endif