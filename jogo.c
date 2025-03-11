#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include <time.h>

struct assam{
    int orientacao;//1 norte, 2 leste, 3 sul, 4, oeste;
    int x;//ponteiro pro tabuleiro;
};
typedef struct assam assam;

typedef struct{
    char cores[9];//vermelho, amarelo, verde, azul, roxo;
    struct tapete *outro_pedaco;
}tapete;

typedef struct{
    int dinheiro;
    char cores[9];
    int quantidade;
}jogadores;

/*typedef struct{
    Pilha *tapete;
    espaco *norte;
    espaco *sul;
    espaco *leste;
    espaco *oeste;
}espaco;*/

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


