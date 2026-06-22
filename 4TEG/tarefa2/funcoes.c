#include "funcoes.h"

/*
    Criacao
*/

Grafo* criar_grafo(int max_vertices){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if(!grafo){
        printf("Nao foi possivel criar o grafo.");
    }

    grafo->lista = (Vertice*)malloc(max_vertices*sizeof(Vertice));
    if(!grafo->lista){
        printf("Nao foi possivel criar a lista de adjacencias.");
    }
    for(int i=0; i < max_vertices; i++){
        grafo->lista[i].listaAdj = NULL;
        grafo->lista[i].palavra = NULL;
        grafo->lista[i].grau = 0;
        grafo->lista[i].valor = i;
    }

    grafo->num_vertices = max_vertices;

    return grafo;
}

/*
    "origem" se refere ao valor do grafo da lista de adjacencia, enquanto
    "palavra" serah a palavra do novo vertice a ser encadeado.
*/
void inserir_vertice(Grafo* grafo, char* origem, char* nova){
    int o = encontrar_indice(grafo, origem);
    int d = encontrar_indice(grafo, nova);

    if(o == -1 || d == -1) return;

    NoAdj* novo = malloc(sizeof(NoAdj));
    novo->valor = d;
    novo->prox = grafo->lista[o].listaAdj;

    grafo->lista[o].listaAdj = novo;
    grafo->lista[o].grau++;
}

int encontrar_indice(Grafo* g, char* palavra){
    for(int i = 0; i < g->num_vertices; i++){
        if(g->lista[i].palavra != NULL && strcmp(g->lista[i].palavra, palavra) == 0){
            return i;
        }
    }
    return -1;
}

/*
    Adiciona a aresta no vertice "origem" e a aresta reciproca para o vertice
    "destino". Aqui eh desconsiderado o vertice 0 na intepretacao do grafo, mas
    computacionalmente ele serah utilizado apenas como um indice da lista.
*/
void adicionar_aresta(Grafo* grafo, char* origem, char* destino){
    if(strlen(origem) != 4 || strlen(destino) != 4){
        return;
    }

    inserir_vertice(grafo, origem, destino);

    if(strcmp(origem, destino)){
        inserir_vertice(grafo, destino, origem);
    }
}

void criar_arestas(Grafo* g) {
    printf("iniciando criacao de arestas...\n");

    for(int i = 0; i < g->num_vertices; i++) {

        if(i % 200 == 0){
            printf("processando i = %d\n", i);
        }

        for(int j = i + 1; j < g->num_vertices; j++) {

            char* p = g->lista[i].palavra;
            char* q = g->lista[j].palavra;

            if(p && q && diferenciar_uma_letra(p, q)) {
                adicionar_aresta(g, p, q);
            }
        }
    }

    printf("fim criacao de arestas\n");
}

int diferenciar_uma_letra(char* a, char* b) {
    int dif = 0;

    for(int i = 0; i < 4; i++) {
        if(a[i] != b[i]) {
            dif++;
            if(dif > 1) return 0;
        }
    }

    return dif == 1;
}

/*
    Importacao da base de dados
*/

/*
    Abre o arquivo CSV e posteriormente alimenta a lista de adjacencias no
    grafo.
*/
void carregar_lista_adjacencias(Grafo** grafo, char* path){
    
    FILE* file = fopen(path, "r");
    if(!file){
        printf("Erro ao abrir o arquivo\n");
    }

    // Abre e le o arquivo uma vez para retornar a quantidade de vertices.
    int num_vertices = 0;
    char buffer[BUFFER];
    while(fgets(buffer, BUFFER, file)){
        num_vertices++;
    }

    *grafo = criar_grafo(num_vertices);

    int id = 0;
    rewind(file);
    while(fgets(buffer, BUFFER, file)){
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Coleta os vertices de origem.
        // id < 100 ? printf("%s", buffer) : 0;
        (*grafo)->lista[id].palavra = strdup(buffer);
        (*grafo)->lista[id].valor = id;
        id++;
    }
    (*grafo)->num_vertices = id;
    criar_arestas(*grafo);

    fclose(file);
}

/*
    Analise dos componentes conexos
*/

/*
    Graus maximo e minimo do grafo.
*/
int grau_maximo(Grafo* grafo){
    int maior = 0;
    for(int i=0; i<grafo->num_vertices; i++){
        grafo->lista[i].grau > maior ? maior = grafo->lista[i].grau : 0;
    }
    return maior;
}
int grau_minimo(Grafo* grafo){
    int menor = grafo->num_vertices;
    for(int i=0; i<grafo->num_vertices; i++){
        grafo->lista[i].grau < menor ? menor = grafo->lista[i].grau : 0;
    }
    return menor;
}

int eh_multigrafo(Grafo* grafo, int* lacos, int* repeticoes){

    for(int i = 0; i < grafo->num_vertices; i++){

        for(NoAdj* a = grafo->lista[i].listaAdj; a; a = a->prox){

            if(a->valor == i){
                (*lacos)++;
            }

            for(NoAdj* b = a->prox; b; b = b->prox){
                if(b->valor == a->valor){
                    (*repeticoes)++;
                }
            }
        }
    }

    return (*lacos > 0 || *repeticoes > 0);
}

/*
    Busca por DFS, com algumas alteracoes para a descricao dos componentes
    conexos:
        - tamanho: tamanho do componente encontrado pela DFS
        - componente: vetor com as "raizes", ou seja, os valores dos vertices
        que compoem um mesmo componente conexo (distribuicao).
*/
void DFS_G(Grafo* grafo, int raiz, int* vet_marca, int* tamanho, int*componente){
    // Caso nao se queira retornar um vetor com os valores marcados.

    vet_marca[raiz] = 1;
    // printf("%d ", raiz);
    componente[*tamanho] = raiz;
    (*tamanho)++;
    
    NoAdj* walker = grafo->lista[raiz].listaAdj;
    while(walker != NULL){
        int idx = walker->valor;
        if(idx >= 0 && vet_marca[idx] == 0){
            DFS_G(grafo, walker->valor, vet_marca, tamanho, componente);
        }
        walker = walker->prox;
    }
}


/*
    Deve-se descrever os componentes conexos contidos no grafo a partir das
    características abaixo:
        1. Distribuicao dos componentes conexos;
        2. Quantidade de componentes conexos;
        3. Tamanhos dos componentes conexos.
*/
int** componentes_conexos(Grafo* grafo, int* num_componentes, int* tamanhos){
    // Distribuicao dos vertices por componentes conexos
    int** componentes = (int**)calloc(grafo->num_vertices, sizeof(int*));
    // Vetor principal de comparacao dos vertices
    int* marcados = (int*)calloc(grafo->num_vertices, sizeof(int));
    *num_componentes = 0;

    for(int i=0; i<grafo->num_vertices; i++){
        componentes[*num_componentes] = (int*)calloc(grafo->num_vertices, sizeof(int));
        if(!marcados[i]){
            tamanhos[*num_componentes] = 0;
            DFS_G(grafo, i, marcados, &(tamanhos[*num_componentes]), componentes[*num_componentes]);
            (*num_componentes)++;
        }
    }
    return componentes;
}

/*
    Busca do caminho minimo por Dijkstra
*/
void dijkstra(Grafo* g, char* origem, char* destino){
    int src = encontrar_indice(g, origem);
    int dst = encontrar_indice(g, destino);

    if(src == -1 || dst == -1){
        printf("Palavra nao encontrada.\n");
        return; 
    }

    int n = g->num_vertices;

    int IN[n];          // conjunto fechado
    int d[n];           // distâncias
    int s[n];           // predecessores

    for(int i = 0; i < n; i++){
        IN[i] = 0;
        d[i] = 999999;
        s[i] = -1;
    }

    // IN = {x}
    IN[src] = 1;
    d[src] = 0;

    // inicialização de vizinhos de x
    for(NoAdj* v = g->lista[src].listaAdj; v; v = v->prox){
        d[v->valor] = 1;   // peso = 1
        s[v->valor] = src;
    }

    // enquanto existir vértice fora de IN
    while(1){

        int p = -1;
        int min = 999999;

        // p = nó fora de IN com menor d[z]
        for(int i = 0; i < n; i++){
            if(!IN[i] && d[i] < min){
                min = d[i];
                p = i;
            }
        }

        if(p == -1) break;

        IN[p] = 1;

        // relaxamento
        for(NoAdj* v = g->lista[p].listaAdj; v; v = v->prox){

            int z = v->valor;

            if(!IN[z]){

                int distAnterior = d[z];

                if(d[p] + 1 < d[z]){
                    d[z] = d[p] + 1;
                    s[z] = p;
                }
            }
        }
    }

    // reconstrução do caminho
    if(d[dst] == 999999){
        printf("Nao existe caminho.\n");
        return;
    }

    printf("\nCaminho minimo (distancia %d):\n", d[dst]);

    int path[n];
    int k = 0;

    for(int v = dst; v != -1; v = s[v]){
        path[k++] = v;
    }

    for(int i = k - 1; i >= 0; i--){
        printf("%s", g->lista[path[i]].palavra);
        if(i > 0) printf(" -> ");
    }

    printf("\n");
}

/* 
    Exposicao dos dados
*/

void printar_lista_adjacencias(Grafo* grafo, int max_vertical, int max_horizontal){
    
    for(int i = 0; i < max_vertical; i++){
        NoAdj* walker = grafo->lista[i].listaAdj;

        int count = 0;
        while(walker && count++ < max_horizontal){
            printf("(%d)[%s]{%d} -> ",
                i+1, grafo->lista[i].palavra, grafo->lista[i].grau);
            walker = walker->prox;
        }
        printf("NULL\n");
    }
}

void analisar_componentes(Grafo* grafo){
    int num_componentes = 0;
    int* tamanhos = calloc(grafo->num_vertices, sizeof(int));

    int** componentes = componentes_conexos(grafo, &num_componentes, tamanhos);

    printf("Componentes: %d\n", num_componentes);

    for(int i = 0; i < num_componentes; i++){

        int vMaior = maior_grau_componente(grafo, componentes[i], tamanhos[i]);
        int vMenor = menor_grau_componente(grafo, componentes[i], tamanhos[i]);

        printf("\nComponente %d\n", i + 1);
        printf("Tamanho: %d\n", tamanhos[i]);

        printf("Maior grau: %s (%d)\n",
            grafo->lista[vMaior].palavra, grafo->lista[vMaior].grau);

        printf("Menor grau: %s (%d)\n",
            grafo->lista[vMenor].palavra, grafo->lista[vMenor].grau);
    }
}

int maior_grau_componente(Grafo* grafo, int* componente, int tamanho) {
    int maior = componente[0];
    for(int i = 1; i < tamanho; i++){
        if(grafo->lista[componente[i]].grau > grafo->lista[maior].grau){
            maior = componente[i];
        }
    }
    return maior;
}

int menor_grau_componente(Grafo* grafo, int* componente, int tamanho){
    int menor = componente[0];
    for(int i = 1; i < tamanho; i++){
        if(grafo->lista[componente[i]].grau < grafo->lista[menor].grau){
            menor = componente[i];
        }
    }
    return menor;
}
