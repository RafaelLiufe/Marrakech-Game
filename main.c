#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "jogo.h"
#include <time.h>
#include "tabuleiro.h"
#include "jogadores.h"

void printState(Assam*, Tabuleiro*, ListaJogadores*, struct jogadorOf *);
int main() {
    system("chcp 65001");
    system("cls");

    int qnt, cor, fim = 0, sentido, dice, vez = 0, tap1, tap2;
    struct jogadorOf *jogadorVez;

    ListaJogadores* lista = criarListaJogadores();
    Tabuleiro* tab = criarT();
    Assam* pieceAssam = criarAssam();
    setPosAssam(pieceAssam, retEspaco(tab, TAM/2, TAM/2));

    printInicio();
    printf("\n       ");
    system("pause");
    system("cls");

    printf("Quantos jogadores participarão? ");
    scanf("%i", &qnt);
    seeds(lista, qnt);
    system("cls");

    acessarJogadorPorCor(lista, "vermelho", jogadorVez);

    while(!fim){
        printState(pieceAssam, tab, lista, jogadorVez);

        printf("Você deseja girar o Assam em sentido horário (1), anti-horário (2) ou não girar(0)? ");
        scanf("%i", &sentido);
        if(sentido){
            if(sentido == 1)
                rotacionarAssamHor(pieceAssam);
            else
                rotacionarAssamAntiHor(pieceAssam);
        }
        system("cls");
        printState(pieceAssam, tab, lista, jogadorVez);

        printf("Dado girando...\n");
        //Sleep(2000);
        dice = dado();
        printf("Caiu %d! Ande as casas\n", dice);
        system("pause");
        system("cls");
        moverAssam(pieceAssam, dice, tab);
        printState(pieceAssam, tab, lista, jogadorVez);
        updateInfo(lista, jogadorVez, pieceAssam);

        /*for (int i = 0; i < dice-1; i++) {
            //system("cls");
            //if(!moverAssam(pieceAssam, 1, tab)) printf("não movi!");
            //printState(pieceAssam, tab, lista, jogadorVez);
            //Sleep(500);
        }*/
        printf("Onde deseja colocar um tapete? Digite dois números: Norte(0), Leste(1), Sul(2), Oeste(3)");
        scanf("%d", &tap1);
        scanf("%d", &tap2);
        fflush(stdin);
        putTapete(tab, pieceAssam, tap1, tap2, lista, jogadorVez->cor);
        removerTapeteListaJogadores(lista, jogadorVez->cor, 1);
        system("cls");
        printState(pieceAssam, tab, lista, jogadorVez);
        printf("\t\t    ");
        system("pause");
        system("cls");

//        if (vez != qnt - 1) {
//            vez++;
//        } else {
//            vez = 0;
//        }
        passarVez(lista, jogadorVez);
        fim = verificarFimJogo(lista);
    }

    return 0;
}
void seeds(ListaJogadores *lc, int qtd){
    struct jogadorOf novo;
    int success;
    const char *cores[] = {"vermelho", "amarelo", "verde", "azul", "roxo"};

    for(int i = 0; i < qtd; i++){
        novo.quantidadeTapetes = 3;
        novo.dinheiro = 1;

        snprintf(novo.cor, sizeof(novo.cor), "%s", cores[i]);
        inserirFimListaJogadores(lc ,novo);
    }
}
void printState(Assam* pieceAssam, Tabuleiro* tab, ListaJogadores* lista, struct jogadorOf *jogadorVez) {
    printVez(jogadorVez->cor);
    imprimirListaJogadores(lista);
    printTable(tab, pieceAssam);
}

