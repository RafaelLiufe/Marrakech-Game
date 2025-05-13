#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "jogo.h"
#include <time.h>
#include "tabuleiro.h"
#include "jogadores.h"

int main() {
    system("chcp 65001");
    HANDLE thread;
    DWORD threadId;
    system("cls");

    if (TAM < 3) {
        printf("Tamanho inválido de tabuleiro.\n");
        return 1;
    }

    int qnt, fim = 0, sentido, dice, diceAux = 0, tap1, tap2;
    struct jogadorOf *jogadorVez = criarJ();

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
    while (qnt < 3 || qnt > 5) {
        system("cls");
        printf("Quantidade inválida.\n");
        printf("Quantos jogadores participarão? ");
        scanf("%i", &qnt);
    }

    seeds(lista, qnt);

    acessarJogadorPorCor(lista, "vermelho", jogadorVez);
    while(!fim){
        do {
            system("cls");
            printState(pieceAssam, tab, lista, jogadorVez);
            printf("Você deseja girar o Assam em sentido horário (1), anti-horário (2) ou não girar(0)? ");
            scanf("%d", &sentido);
        } while (sentido != 1 && sentido != 2 && sentido != 0);

        if(sentido){
            if(sentido == 1)
                rotacionarAssamHor(pieceAssam);
            else
                rotacionarAssamAntiHor(pieceAssam);
        }
        system("cls");
        printState(pieceAssam, tab, lista, jogadorVez);
        diceAnim();
        dice = dado();
        system("cls");
        printState(pieceAssam, tab, lista, jogadorVez);
        printf("\t\t\t  Caiu %d! Agora ande as casas!\n", dice);
        printf("\t\t    ");
        system("pause");
        for (int i = 1; i <= dice; i++) {
            system("cls");
            thread = CreateThread(NULL, 0, passo, NULL, 0, &threadId);
            moverAssam(pieceAssam, 1, tab);
            printState(pieceAssam, tab, lista, jogadorVez);
            Sleep(500);
        }
        int removido = 0;
        if (updateInfo(lista, jogadorVez, pieceAssam, &removido))
            Sleep(3500);
        if(!removido){

        do {
            system("cls");
            printState(pieceAssam, tab, lista, jogadorVez);
            printf("Onde deseja colocar um tapete?\nDigite um número em relação à Assam: Norte(0), Leste(1), Sul(2), Oeste(3) ");
            scanf("%d", &tap1);
            printf("Agora, em relação ao primeiro tapete: ");
            scanf("%d", &tap2);
            fflush(stdin);
        } while (!putTapete(tab, pieceAssam, tap1, tap2, lista, jogadorVez));
        thread = CreateThread(NULL, 0, putTap, NULL, 0, &threadId);
        removerTapeteListaJogadores(lista, jogadorVez, 1);
        system("cls");
        printState(pieceAssam, tab, lista, jogadorVez);
        printf("\t\t    ");

        }
        system("pause");
        system("cls");
        passarVez(lista, jogadorVez);
        fim = verificarFimJogo(lista);
    }
    verificarVencedor(lista);
    return 0;
}


