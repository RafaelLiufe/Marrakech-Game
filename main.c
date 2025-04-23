#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include <time.h>
#include "tabuleiro.h"
#include "jogo.h"
#include "jogadores.h"

int main() {
    system("chcp 65001");
    system("cls");

    int qnt, cor, fim = 0, sentido, dice;


    ListaJogadores* lista = criarListaJogadores();
    Tabuleiro* tab = criarT();
    Assam* pieceAssam = criarAssam();
    setPosAssam(pieceAssam, retEspaco(tab, TAM/2, TAM/2));
    //empilha(retPilha(retEspaco(tab, 0, 0)), retPilha(retEspaco(tab, 1, 0)), "azul");
    //empilha(retPilha(retEspaco(tab, 4, 2)), retPilha(retEspaco(tab, 4, 3)), "vermelho");
    //printTable(tab, ass);

    printf("Quantos jogadores participarão? ");
    scanf("%i", &qnt);
    seeds(lista, qnt);

    while(1){
        imprimirListaJogadores(lista);
        printTable(tab, pieceAssam);
        printf("Você deseja girar o Assam? em sentido horário (1), anti-horário (2) ou não girar(0)? ");
        scanf("%i", &sentido);
        if(sentido){
            if(sentido == 1)
                rotacionarAssamHor(pieceAssam);
            else
                rotacionarAssamAntiHor(pieceAssam);
        }
        printf("Dado girando...\n");
        //fflush(stdout);
        //Sleep(3000);
        dice = dado();
        printf("Caiu %d! Ande as casas\n", dice);
        if(!moverAssam(pieceAssam, dice, tab))
            printf("não movi!");
        system("pause");
        system("cls");
    }

    return 0;
}
void seeds(ListaJogadores*, int);
// MAIN DE OTAVIO
int main_de_otavio(){
    ListaJogadores* lista = criarListaJogadores();

    int qnt, cor, fim;
    printf("Quantos jogadores participarao? ");
    scanf("%i", &qnt);

    seeds(lista, qnt);
    imprimirListaJogadores(lista);
    removerDinheiroListaJogadores(lista, "vermelho", 5);
    adicinarDinheiroListaJogadores(lista, "verde", 10);
    removerTapeteListaJogadores(lista, "amarelo", 10);
    removerTapeteListaJogadores(lista, "vermelho", 10);
    imprimirListaJogadores(lista);
    fim = verificarFimJogo(lista);

    if(fim){
        verificarVencedor(lista);
    }
}
int mainKayky(){
    srand(time(NULL));
    int qnt, cor;
    printf("Quantos jogadores participar�o?\n");
    scanf("%i", &qnt);

    system("cls");
    Assam *piece = criarAssam();
    Tabuleiro *board = criarT();
    do{

    }while(0);
    return 0;
}

void seeds(ListaJogadores *lc, int qtd){
    struct jogador novo;
    int success;
    const char *cores[] = {"vermelho", "amarelo", "verde", "azul", "roxo"};

    for(int i = 0; i < qtd; i++){
        novo.quantidadeTapetes = 15;
        novo.dinheiro = 30;

        snprintf(novo.cor, sizeof(novo.cor), "%s", cores[i]);
        inserirFimListaJogadores(lc ,novo);
    }
}
