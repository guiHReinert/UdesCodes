#include "../include/conjunto.h"


/*
    Criacao
*/

ArvoreAVL* criarAVL() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
  
    return arvore;
}

NoAVL* criarNoAVL(NoAVL* pai, int valor) {
    NoAVL* no = malloc(sizeof(NoAVL));
    no->valor = valor;
    no->pai = pai;
    no->esquerda = NULL;
    no->direita = NULL;

    return no;
}

/*
    Operacoes
*/

int isVaziaAVL(ArvoreAVL* arvore) {
    return arvore->raiz == NULL;
}

NoAVL* adicionarNoAVL(NoAVL* no, int valor, int* count) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            NoAVL* novo = criarNoAVL(no, valor);
            no->direita = novo;
				
            (*count)++;
            return novo;
        } else {
            return adicionarNoAVL(no->direita, valor, count);
        }
    } else {
        if (no->esquerda == NULL) {
            NoAVL* novo = criarNoAVL(no, valor);
            no->esquerda = novo;
			
            (*count)++;
            return novo;
        } else {
            return adicionarNoAVL(no->esquerda, valor, count);
        }
    }
}

NoAVL* adicionarChaveAVL(ArvoreAVL* arvore, int valor, int* count) {
    if (isVaziaAVL(arvore)) {
        NoAVL* novo = criarNoAVL(NULL, valor);
        arvore->raiz = novo;
			
        return novo;
    } else {
        NoAVL* no = adicionarNoAVL(arvore->raiz, valor, count);
        balanceamentoAVL(arvore, no, count);
        
        return no;
    }
}

NoAVL* localizarNoAVL(NoAVL* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizarNoAVL(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizarNoAVL(no->direita, valor);
            }
        }
    }

    return NULL;
}

void percorrerAVL(NoAVL* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrerAVL(no->esquerda,callback);
        callback(no->valor);
        percorrerAVL(no->direita,callback);
    }
}

void visitar(int valor){
    // printf("%d ", valor);
}

/*
    Balanceamento
*/

void balanceamentoAVL(ArvoreAVL* arvore, NoAVL* no, int* count) {
    while (no != NULL) {
        int fator = fb(no);

        if (fator > 1) { //árvore mais profunda a esquerda
            //rotação para a direita
            if (fb(no->esquerda) > 0) {
                // printf("RSD(%d)\n",no->valor);
                //rotação simples a direita, FB do filho tem sinal igual
                rsd(arvore, no, count); 
            } else {
                // printf("RDD(%d)\n",no->valor);
                //rotação dupla a direita, FB do filho tem sinal diferente
                rdd(arvore, no, count); 
            }
        } else if (fator < -1) { //árvore mais profunda a direita
            //rotação para a esquerda
            if (fb(no->direita) < 0) {
                // printf("RSE(%d)\n",no->valor);
                //rotação simples a esquerda, FB do filho tem sinal igual
                rse(arvore, no, count); 
            } else {
                // printf("RDE(%d)\n",no->valor);
                //rotação dupla a esquerda, FB do filho tem sinal diferente
                rde(arvore, no, count);
            }
        }

        no = no->pai; 
    }
}

int altura(NoAVL* no){
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    //max(esquerda,direita)
    return esquerda > direita ? esquerda : direita;
}

int fb(NoAVL* no) {
    int esquerda = 0,direita = 0;
  
    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda - direita;
}

NoAVL* rse(ArvoreAVL* arvore, NoAVL* no, int* count) {
    NoAVL* pai = no->pai;
    NoAVL* direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}



NoAVL* rsd(ArvoreAVL* arvore, NoAVL* no, int* count) {
    NoAVL* pai = no->pai;
    NoAVL* esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

NoAVL* rde(ArvoreAVL* arvore, NoAVL* no, int* count) {
    no->direita = rsd(arvore, no->direita, count);
    return rse(arvore, no, count);
}

NoAVL* rdd(ArvoreAVL* arvore, NoAVL* no, int* count) {
    no->esquerda = rse(arvore, no->esquerda, count);
    return rsd(arvore, no, count);
}

/*Função que auxilia a encontrar o menor da subárvore a direita*/
NoAVL* encontrarSucessor(NoAVL* no) {

    while(no->esquerda != NULL){

        no = no->esquerda;

    }

    return no;

}

NoAVL* remocaoAVL (ArvoreAVL* arvore, int valor, int* count) {

    if (arvore->raiz == NULL) {

        printf("Não há valores a serem removidos...");
        return NULL;

    }

    NoAVL* no = localizarNoAVL(arvore->raiz, valor);
    NoAVL* partidaBalanceamento = NULL;

    if (no==NULL) {

        printf ("Não há esse valor na árvore, impossível remover");
        return NULL;

    } else {

        if (no->esquerda==NULL && no->direita==NULL) {

            printf("CASO FOLHA\n");
            if(no->pai==NULL){
                arvore->raiz=NULL;
                partidaBalanceamento = no->pai;
                free(no);
                balanceamentoAVL(arvore, partidaBalanceamento, count);
                printf("Não havia mais nós, árvore apagada");
                return NULL;
            }

            if(no->pai->esquerda==no){
                no->pai->esquerda=NULL;
                partidaBalanceamento = no->pai;
                free(no);
                balanceamentoAVL(arvore, partidaBalanceamento, count);
                printf ("Filho era uma folha a esquerda, foi removido");
                return NULL;
            }

            if(no->pai->direita==no){
                no->pai->direita=NULL;
                partidaBalanceamento = no->pai;
                free(no);
                balanceamentoAVL(arvore, partidaBalanceamento, count);
                printf ("Filho era uma folha a direita, foi removido");
                return NULL;
            }

        } else if((no->esquerda != NULL && no->direita == NULL) || (no->direita != NULL && no->esquerda == NULL)) {

            printf("CASO 1 FILHO\n");
            NoAVL *filho = NULL;

            if (no->esquerda != NULL) {
                filho=no->esquerda;
            } else {
                filho=no->direita;
            }

            if (no->pai == NULL) {

                arvore->raiz=filho;
                filho->pai=NULL;
                partidaBalanceamento = no->pai;
                free(no);
                balanceamentoAVL(arvore, partidaBalanceamento, count);
                printf ("Remocao realizada: Filho estava conectado diretamente com a raiz...\n");
                return NULL;

            } else if (no->pai->esquerda == no) {

                no->pai->esquerda=filho;
                filho->pai=no->pai;
                partidaBalanceamento = no->pai;
                free(no);
                balanceamentoAVL(arvore, partidaBalanceamento, count);
                printf("Remocao realizada: no com um filho removido (substituicao pela esquerda).\n");
                return NULL;

            } else {
                
                no->pai->direita=filho;
                filho->pai=no->pai;
                partidaBalanceamento = no->pai;
                free(no);
                balanceamentoAVL(arvore, partidaBalanceamento, count);
                printf("Remocao realizada: no com um filho removido (substituicao pela direita).\n");
                return NULL;

            }

        } else {

            printf("CASO 2 FILHOS\n");
            NoAVL* sucessor = encontrarSucessor(no->direita);

            no->valor=sucessor->valor;

            if (sucessor->direita == NULL) {

                if(sucessor->pai->esquerda==sucessor) {

                    sucessor->pai->esquerda=NULL;
                    partidaBalanceamento = sucessor->pai;
                    free(sucessor);
                    balanceamentoAVL(arvore, partidaBalanceamento, count);
                    return NULL;

                } else if (sucessor->pai->direita==sucessor) {
                    
                    sucessor->pai->direita=NULL;
                    partidaBalanceamento = sucessor->pai;
                    free(sucessor);
                    balanceamentoAVL(arvore, partidaBalanceamento, count);
                    return NULL;

                }

            } else {

                NoAVL *filho = sucessor->direita;

                if(sucessor->pai->esquerda==sucessor) {

                    sucessor->pai->esquerda=filho;
                    filho->pai=sucessor->pai;
                    partidaBalanceamento = sucessor->pai;
                    free(sucessor);
                    balanceamentoAVL(arvore, partidaBalanceamento, count);
                    return NULL;

                } else if (sucessor->pai->direita==sucessor) {
                    
                    sucessor->pai->direita=filho;
                    filho->pai=sucessor->pai;
                    partidaBalanceamento = sucessor->pai;
                    free(sucessor);
                    balanceamentoAVL(arvore, partidaBalanceamento, count);
                    return NULL;

                }

            }

        }       
        
    }

}

static void printarNoAVL(ArvoreAVL* arvore, NoAVL* no, int profundidade) {
    if (!no) {return;}
    printarNoAVL(arvore, no->direita, profundidade + 1);
    for (int i = 0; i < profundidade; i++) {
        printf("\t");
    }
    printf("%s %d\n", no == arvore->raiz ? "[R]" : "", no->valor);
    printarNoAVL(arvore, no->esquerda, profundidade + 1);
}

void printarAVL(ArvoreAVL* arvore) {
    printarNoAVL(arvore, arvore->raiz, 0);
    printf("\n");
}
