#ifndef ARQ_H
#define ARQ_H

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

typedef struct{
    Vertice* lista;
    int num_vertices;
} Grafo;


Grafo* criar_grafo(int max_vertices);
void inserir_vertice(Grafo* grafo, char* origem, char* nova);
int encontrar_indice(Grafo* g, char* palavra);
void adicionar_aresta(Grafo* grafo, char* origem, char* destino);
void criar_arestas(Grafo* g);
int diferenciar_uma_letra(char* a, char* b);

void carregar_lista_adjacencias(Grafo** grafo, char* path);

int grau_maximo(Grafo* grafo);
int grau_minimo(Grafo* grafo);
int eh_multigrafo(Grafo* grafo, int* lacos, int* repeticoes);
void DFS_G(Grafo* grafo, int raiz, int* vet_marca, int* tamanho, int*componente);
int** componentes_conexos(Grafo* grafo, int* num_componentes, int* tamanhos);

void dijkstra(Grafo* g, char* origem, char* destino);

void printar_lista_adjacencias(Grafo* grafo, int max_origens, int max_destinos);
void analisar_componentes(Grafo* grafo);
int maior_grau_componente(Grafo* grafo, int* componente, int tamanho);
int menor_grau_componente(Grafo* grafo, int* componente, int tamanho);

#endif