#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"
#include "b.h"
#include "rubro-negra.h"

typedef struct conjunto {
    int num;
    int numAmostra;

    ArvoreAVL* AVL;
    ArvoreRN* RN;
    ArvoreB* B1;
    ArvoreB* B5;
    ArvoreB* B10;

    int* avl;
    int* rn;
    int* b1;
    int* b5;
    int* b10;
    
} Conjunto;

/*
    Funcoes
*/

Conjunto* criarConjunto(int num, int numAmostra);
void carregarConjunto(Conjunto* conj);

#endif