#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include <time.h>
#include "tabuleiro.h"

int mainKayky(){
    srand(time(NULL));
    int qnt, cor;
    printf("Quantos jogadores participar�o?\n");
    scanf("%i", &qnt);

    system("cls");
    Assam *piece = criarAssam();
    Tabuleiro *board = criarTabuleiro(piece);
    do{

    }while(0);
    return 0;
}

