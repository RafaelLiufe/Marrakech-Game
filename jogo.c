#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include <time.h>
#include <string.h>
#include <math.h>

struct assam{
    int orientacao;//0 norte, 1 leste, 2 sul, 3 oeste;
    Espaco* posicao;//ponteiro pro tabuleiro;
};
typedef struct assam assam;

struct jogador{
    int dinheiro;
    char cor[10];
    int quantidade;
};

typedef struct jogador jogador;
struct lista{
    jogador players[5];
    int n;
};


int dado(){
    int n = 1 + rand()%(6);
    switch(n){
    case 1:
        return 1;
    case 2:
    case 5:
        return 2;
    case 4:
    case 3:
        return 3;
    case 6:
        return 4;
    }
}

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
Jogadores* listaJogadores(int n){
    struct lista* aux = (Jogadores)malloc(sizeof(struct lista));
    aux->n = n;
    Jogadores *Lista = (Jogadores*)malloc(sizeof(Jogadores));
    Lista = &aux;
    return Lista;
}
int setPlayer(Jogadores* lista, int n, int cor){
    if(lista == NULL || *lista == NULL)
        return 0;
    char cores[5][10] = {"vermelho", "amarelo", "verde", "azul", "roxo"};
    (*lista)->players[n].dinheiro = 50;
    (*lista)->players[n].quantidade = 10;
    strcpy((*lista)->players[n].cor, cores[cor-1]);
    return 1;
}
Assam criarAssam(){
    Assam peca = (Assam)malloc(sizeof(assam));
    peca->orientacao = 0;
    peca->posicao = NULL;
    return peca;
}

Pilha* criarP() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p != NULL) {
        *p = NULL;
    }
    return p;
}
int empilha(Pilha *p, struct tap tapete){
    if(p==NULL)
        return 0;
    if(*p == NULL){
        struct tap *novoTap = (Pilha)malloc(sizeof(struct tap));
        novoTap->dados->jogador;
    }

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
    /*experimental
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
    } while (ref->oeste != ref);*/

    return table;
}

int moverAssam(Tabuleiro *board, Assam piece, int n, int dir){
    if(!((dir - piece->orientacao + 4) % 4 == 1 || (dir - piece->orientacao + 4) % 4 == 3))
        return 0;

    switch(dir){
        case 0:
            piece->orientacao = dir;
            for(int j=0;j<n;j++){
                piece->posicao = piece->posicao->norte;
            }
            break;
        case 1:
            piece->orientacao = dir;
            for(int j=0;j<n;j++){
                piece->posicao = piece->posicao->leste;
            }
            break;
        case 2:
            piece->orientacao = dir;
            for(int j=0;j<n;j++){
                piece->posicao = piece->posicao->sul;
            }
            break;
        case 3:
            piece->orientacao = dir;
            for(int j=0;j<n;j++){
                piece->posicao = piece->posicao->oeste;
            }
            break;
        default:
            printf("ERRO");
    }
    return 1;
}
int putTap(Tabuleiro *board, Assam piece, int p1, int p2, struct tap tapete){
    Espaco *aux1, *aux2;
    if((p2 - p1 + 4) % 4 == 2)
        return 0;
    switch(p1){
        case 0:
            aux1 = piece->posicao->norte;
            break;
        case 1:
            aux1 = piece->posicao->leste;
            break;
        case 2:
            aux1 = piece->posicao->sul;
            break;
        case 3:
            aux1 = piece->posicao->oeste;
            break;
        default:
            printf("ERRO");
    }
    switch(p2){
        case 0:
            aux2 = aux1->norte;
            break;
        case 1:
            aux2 = aux1->leste;
            break;
        case 2:
            aux2 = aux1->sul;
            break;
        case 3:
            aux2 = aux1->oeste;
            break;
        default:
            printf("ERRO");
    }
    //if((*aux1->tapetes)->    )
}
