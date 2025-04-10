#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "tabuleiro.h"
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
    struct jogador *proximo;
    struct jogador *anterior;
};

typedef struct jogador jogador;

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
    int linha;
    int coluna;
};
struct tap {
    char cor[10];
    struct tap* prox;
    struct tap* outro;
};
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
void setPosAssam(Assam* ass, Espaco* pos) {
    (*ass)->posicao = pos;
}
Pilha* criarP() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p != NULL) {
        *p = NULL;
    }
    return p;
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
    if(empilha(aux1->tapetes, aux2->tapetes, "vermelho")){
        //(*lista_de_jogadores)->players[player].quantidade--;
        return 1;
    }else return 0;
}
int descontarValor(Assam *piece, Jogadores *lista_jogadores, int player){
    Assam auxPiece = *piece;
    if(strcmp((*auxPiece->posicao->tapetes)->cor, "vermelho")!=0){
        //criar nó descritor com o tamanho da pilha ou implementar algoritmo de busca que retorna a área de um determinado trapete
        return 1;
    }
    return 0;
}
/*int checarJogador(Jogadores *lista_jogadores, int player){
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
}*/
int BuscaProfunda(Espaco *casa, int **visitado, char color[10]) {
    if (visitado[casa->linha][casa->coluna] || *casa->tapetes == NULL || strcmp((*casa->tapetes)->cor, color)!=0)
        return 0;

    visitado[casa->linha][casa->coluna] = 1;

    int size = 1;

    if(casa->coluna!=0)
        size += BuscaProfunda(casa->oeste, visitado, color);//oeste
    if(casa->coluna!=TAM)
        size += BuscaProfunda(casa->leste, visitado, color);//leste
    if(casa->linha!=0)
        size += BuscaProfunda(casa->norte, visitado, color);//norte
    if(casa->linha!=TAM)
        size += BuscaProfunda(casa->sul, visitado, color);//sul

    return size;
}

int AreaDoTapete(Espaco *casa, char color[10]) {
    int **visitado = (int**)malloc(sizeof(int*)*TAM);
    for(int i=0;i<TAM;i++)
        visitado[i] = (int*)malloc(sizeof(int)*TAM);
    for(int i=0;i<TAM;i++)
        for(int j=0;j<TAM;j++)
            visitado[i][j] = 0;
    return BuscaProfunda(casa, visitado, color);
}
