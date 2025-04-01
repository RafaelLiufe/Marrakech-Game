#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"
struct espaco {
    Pilha* tapetes;
    struct espaco* norte;
    struct espaco* sul;
    struct espaco* leste;
    struct espaco* oeste;
    int linha;
    int coluna;
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
    aux->linha = 0;
    aux->coluna = 0;
    for (int i = 1; i < TAM; i++) {
        aux->sul = (Espaco*)malloc(sizeof(Espaco));
        aux->sul->norte = aux;
        aux = aux->sul;
        aux->tapetes = criarP();
        aux->linha = i;
        aux->coluna = 0;
    }
    aux->sul = NULL;
    Espaco* ref = *table;
    for (int i = 1; i <= TAM; i++) {
        aux = ref;
        for (int j = 1; j < TAM; j++) {
            aux->leste = (Espaco*)malloc(sizeof(Espaco));
            aux->leste->oeste = aux;
            aux = aux->leste;
            aux->linha = i - 1;
            aux->coluna = j;
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
        ref = ref->leste;
        aux = aux->leste;
        for (int j = 1; j < TAM; j++) {
            aux2->sul = ref2->sul->leste;
            aux2->sul->norte = ref2->leste;
            ref2 = ref2->sul;
            aux2 = aux2->sul;
        }
    }
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
    while (ref->leste != NULL){
        ref = ref->leste;
    }
    cont = 0;
    while (ref != NULL) {
        if (ref->sul == NULL && cont == 0) {
            ref->leste = ref;
            ref = ref->sul;
        } else if (cont == 0) {
            ref->leste = ref->sul;
            ref = ref->sul;
            cont++;
        } else if (cont == 1) {
            ref->leste = ref->norte;
            ref = ref->sul;
            cont--;
        }
    }
    ref = *table;
    for (int i = 0; i < TAM - 1; i++) {
        ref = ref->leste;
    }
    for (int i = 0; i < TAM - 1; i++) {
        ref = ref->sul;
    }
    //if (ref->oeste->oeste->oeste->oeste->sul == NULL) printf("sim"); ***Teste***
    //if (ref->oeste->sul == NULL) printf("nulo"); ***Teste***
    for (int i = 0; i < TAM; i++) {
        if (TAM % 2 != 0 && i == TAM - 1) {
            ref->sul = ref;
        } else if (i % 2 == 0) {
            ref->sul = ref->oeste;
            ref = ref->oeste;
        } else {
            ref->sul = ref->leste;
            ref = ref->oeste;
        }
    }

    return table;
}
