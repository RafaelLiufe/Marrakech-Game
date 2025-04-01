#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include <time.h>

int main(){
    srand(time(NULL));
    int qnt, cor;
    printf("Quantos jogadores participarão?\n");
    scanf("%i", &qnt);
    Jogadores *lista_jogadores = listaJogadores(qnt);
    system("cls");
    printf("Cores disponíveis:\n1.vermelho\n2.amarelo\n3.verde\n4.azul\n5.roxo\n");
    for(int i=0;i<qnt;i++){
        printf("Jogador %i, qual cor você escolhe?\n", i+1);
        scanf("%i", &cor);
        if(!setPlayer(lista_jogadores, i, cor)){
            printf("ERRO\n");
            return 0;
        }
    }
    system("cls");
    Assam *piece = criarAssam();
    Tabuleiro *board = criarTabuleiro(piece);
    do{

    }while(0);
    return 0;
}
