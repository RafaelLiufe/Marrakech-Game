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

struct jogador{
    int dinheiro;
    char cor[10];
    int quantidade;
};

typedef struct jogador jogador;

struct lista{//lista estática dos jogadores
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
    default:
        return 1;
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
    char jogador[10];
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
    printf("%i, %i", (*lista)->players[n].dinheiro, (*lista)->players[n].quantidade);
    return 1;
}
Assam* criarAssam(){
    Assam *piece;
    piece = (Assam*)malloc(sizeof(Assam));
    if(piece != NULL){
        *piece = (Assam)malloc(sizeof(struct assam));
        (*piece)->orientacao = 0;
        (*piece)->posicao = NULL;
    }

    return piece;
}

Pilha* criarP() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p != NULL) {
        *p = NULL;
    }
    return p;
}
int empilha(Pilha *p1, Pilha *p2, char playerColor[10]){
    if(p1==NULL || p2 == NULL)
        return 0;
    struct tap *novoTapete1 = (struct tap*)malloc(sizeof(struct tap));
    struct tap *novoTapete2 = (struct tap*)malloc(sizeof(struct tap));
    if(novoTapete1 == NULL || novoTapete2 == NULL)
        return 0;
    strcpy(novoTapete1->dados->jogador, playerColor);
    strcpy(novoTapete2->dados->jogador, playerColor);
    novoTapete1->outro = novoTapete2;
    novoTapete2->outro = novoTapete1;
    novoTapete1->prox = *p1;
    novoTapete2->prox = *p2;
    *p1 = novoTapete1;
    *p2 = novoTapete2;
    return 1;
}
Tabuleiro* criarTabuleiro(Assam *piece) {
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
            if(i== (TAM/2) && j == (TAM/2)){
                Assam auxPiece = *piece;
                auxPiece->posicao = aux;
            }
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

int moverAssam(Tabuleiro *board, Assam *piece, int n, int dir){
    Assam auxPiece = *piece;
    if(!((dir - auxPiece->orientacao + 4) % 4 == 1 || (dir - auxPiece->orientacao + 4) % 4 == 3))
        return 0;

    switch(dir){
        case 0:
            auxPiece->orientacao = dir;
            for(int j=0;j<n;j++){
                auxPiece->posicao = auxPiece->posicao->norte;
            }
            break;
        case 1:
            auxPiece->orientacao = dir;
            for(int j=0;j<n;j++){
                auxPiece->posicao = auxPiece->posicao->leste;
            }
            break;
        case 2:
            auxPiece->orientacao = dir;
            for(int j=0;j<n;j++){
                auxPiece->posicao = auxPiece->posicao->sul;
            }
            break;
        case 3:
            auxPiece->orientacao = dir;
            for(int j=0;j<n;j++){
                auxPiece->posicao = auxPiece->posicao->oeste;
            }
            break;
        default:
            printf("ERRO");
    }
    return 1;
}
int putTapete(Tabuleiro *board, Assam *piece, int casa1, int casa2, Jogadores *lista_de_jogadores, int player){
    Espaco *aux1, *aux2;
    Assam auxPiece = *piece;
    if((casa2 - casa1 + 4) % 4 == 2)
        return 0;
    switch(casa1){
        case 0:
            aux1 = auxPiece->posicao->norte;
            break;
        case 1:
            aux1 = auxPiece->posicao->leste;
            break;
        case 2:
            aux1 = auxPiece->posicao->sul;
            break;
        case 3:
            aux1 = auxPiece->posicao->oeste;
            break;
        default:
            printf("ERRO");
            return 0;
    }
    switch(casa2){
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
            return 0;
    }
    if((*aux1->tapetes)->outro == (*aux2->tapetes)){//há um tapete completo por cima
        return 0;
    }
    if(empilha(aux1->tapetes, aux2->tapetes, (*lista_de_jogadores)->players[player].cor)){
        (*lista_de_jogadores)->players[player].quantidade--;
        return 1;
    }else return 0;
}
int descontarValor(Assam *piece, Jogadores *lista_jogadores, int player){
    Assam auxPiece = *piece;
    if(strcmp((*auxPiece->posicao->tapetes)->dados->jogador, (*lista_jogadores)->players[player].cor)!=0){
        //criar nó descritor com o tamanho da pilha ou implementar algoritmo de busca que retorna a área de um determinado trapete
        return 1;
    }
    return 0;
}
int checarJogador(Jogadores *lista_jogadores, int player){
    if((*lista_jogadores)->players[player].dinheiro <= 0){
       struct lista *aux = *lista_jogadores;
       if(player != aux->n){
       jogador temporario = aux->players[player];
       aux->players[player] = aux->players[aux->n];
       aux->players[aux->n] = temporario;
       }
       aux->n--;
       return 1;
    }
    return 0;
}
