#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "jogo.h"
#include <time.h>
#include "tabuleiro.h"
#include "jogadores.h"

int main() {
    system("chcp 65001");
    system("cls");

    int qnt, cor, fim = 0, sentido, dice, vez = 0, tap1, tap2;


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

    while(!fim){
        printState(pieceAssam, tab, lista, vez);
        printf("Você deseja girar o Assam em sentido horário (1), anti-horário (2) ou não girar(0)? ");
        scanf("%i", &sentido);
        if(sentido){
            if(sentido == 1)
                rotacionarAssamHor(pieceAssam);
            else
                rotacionarAssamAntiHor(pieceAssam);
        }
        system("cls");
        printState(pieceAssam, tab, lista, vez);
        printf("Dado girando...\n");
        dice = dado();
        printf("Caiu %d! Ande as casas\n", dice);
        system("pause");
        for (int i = 1; i <= dice; i++) {
            system("cls");
            if(!moverAssam(pieceAssam, 1, tab)) printf("não movi!");
            printState(pieceAssam, tab, lista, vez);
            Sleep(500);
        }
        printf("Onde deseja colocar um tapete? Digite dois números: Norte(0), Leste(1), Sul(2), Oeste(3)");
        scanf("%d", &tap1);
        scanf("%d", &tap2);
        fflush(stdin);
        putTapete(tab, pieceAssam, tap1, tap2, lista, vez);
        system("cls");
        printState(pieceAssam, tab, lista, vez);
        printf("\t\t    ");
        system("pause");
        system("cls");

        if (vez != qnt) {
            vez++;
        } else {
            vez = 0;
        }
    }

    return 0;
}
//void seeds(ListaJogadores*, int);
// MAIN DE OTAVIO
/*int main_de_otavio(){
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
}*/
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
    struct jogadorOf novo;
    int success;
    const char *cores[] = {"vermelho", "amarelo", "verde", "azul", "roxo"};

    for(int i = 0; i < qtd; i++){
        novo.quantidadeTapetes = 15;
        novo.dinheiro = 30;

        snprintf(novo.cor, sizeof(novo.cor), "%s", cores[i]);
        inserirFimListaJogadores(lc ,novo);
    }
}
void printState(Assam* pieceAssam, Tabuleiro* tab, ListaJogadores* lista, int vez) {
    printVez(vez);
    imprimirListaJogadores(lista);
    printTable(tab, pieceAssam);
}
