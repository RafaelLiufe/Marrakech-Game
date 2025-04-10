#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "tabuleiro.h"

int main_de_Rafael() {
    system("chcp 65001");
    system("cls");
    Tabuleiro* tab = criarT();
    Assam* ass = (Assam*)malloc(sizeof(Assam));
    ass->orientacao = 0;
    ass->posicao = retEspaco(tab, TAM/2, TAM/2);
    empilha(retPilha(retEspaco(tab, 0, 0)), retPilha(retEspaco(tab, 1, 0)), "azul");
    empilha(retPilha(retEspaco(tab, 4, 2)), retPilha(retEspaco(tab, 4, 3)), "vermelho");
    rotacionarAssamHor(ass);
    printTable(tab, ass);

    return 0;
}

