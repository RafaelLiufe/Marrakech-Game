#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"
struct espaco {
    Pilha* tapetes;
    struct espaco* norte;
    struct espaco* sul;
    struct espaco* leste;
    struct espaco* oeste;
};
struct tap {
    struct tdata* dados;
    struct tap* prox;
    struct tap* outro;
};
struct tdata {
    int jogador;
};
Pilha* criarP() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p != NULL) {
        *p = NULL;
    }
    return p;
}
Tabuleiro* criarT() {
    Tabuleiro* table = (Tabuleiro*)malloc(sizeof(Tabuleiro));
    if (table != NULL) {
        *table = NULL;
    }
    *table = (Espaco*)malloc(sizeof(Espaco));
    Espaco* aux = *table;
    aux->tapetes = criarP();
    for (int i = 1; i < TAM; i++) {
        aux->sul = (Espaco*)malloc(sizeof(Espaco));
        aux->sul->norte = aux;
        aux = aux->sul;
        aux->tapetes = criarP();
    }
    aux->sul = NULL;
    Espaco* ref = *table;
    for (int i = 1; i < TAM; i++) {
        aux = ref;
        for (int j = 1; j < TAM; j++) {
            aux->leste = (Espaco*)malloc(sizeof(Espaco));
            aux->leste->oeste = aux;
            aux = aux->leste;
            aux->tapetes = criarP();
        }
        aux->leste = NULL;
        ref = ref->sul;
    }
    ref = *table;
    aux = ref->leste;
    Espaco* ref2;
    Espaco* aux2;
    for (int i = 1; i < TAM; i++) {
        ref2 = ref;
        aux2 = aux;
        ref = ref->leste; // Na última apontam a NULL
        aux = aux->leste;
        for (int j = 1; j < TAM - 1; j++) {
            aux2->sul = ref2->sul->leste;
            aux2->sul->norte = ref2->leste;
            ref2 = ref2->sul; //na última apontam a NULL
            aux2 = aux2->sul;
        }
    }
    //experimental
    ref = *table;
    int cont = 0;
    while (ref != NULL) {
        if (ref->leste == NULL && cont == 0) {
            ref->norte = ref;
            ref = ref->leste;
        } else if (cont == 0) {
            ref->norte = ref->leste;
            ref = ref->leste;
            cont++;
        } else if (cont == 1) {
            ref->norte = ref->oeste;
            ref = ref->leste;
            cont--;
        }
    }
    ref = *table;
    cont = 0;
    while (ref != NULL) {
        if (ref->sul == NULL && cont == 0) {
            ref->oeste = ref;
            ref = ref->sul;
        } else if (cont == 0) {
            ref->oeste = ref->sul;
            ref = ref->sul;
            cont++;
        } else if (cont == 1) {
            ref->oeste = ref->norte;
            ref = ref->sul;
            cont--;
        }
    }
    ref = *table;
    cont = 0;
    while (ref->leste != NULL) {
        ref = ref->leste;
    }
    if (ref->norte == ref) {
        ref->leste = ref;
        ref = ref->sul;
    }
    while (ref != NULL) {
        if (cont == 0) {
            ref->leste = ref->sul;
            ref = ref->sul;
            cont++;
        } else if (cont == 1) {
            ref->leste = (Espaco*)malloc(sizeof(Espaco)); //CORRIGIR DEPOIS
            ref->leste = ref->norte;
            ref = ref->sul;
            cont--;
        }
    }
    free(ref);
    ref = (Espaco*)malloc(sizeof(Espaco));
    ref = *table; //HÁ ERRO AQUI
    printf("teste\n");
    cont = 0;
    while (ref->sul != NULL) {
        ref = ref->sul;
    }
    if (ref->oeste == ref) {
        ref->sul = ref;
        ref = ref->leste;
    }
    do {
        if (cont == 0) {
            ref->sul = ref->oeste;
            ref = ref->oeste;
            cont++;
        } else if (cont == 1) {
            ref->sul = ref->oeste;
            ref = ref->leste;
            cont--;
        }
    } while (ref->oeste != ref);

    return table;
}
