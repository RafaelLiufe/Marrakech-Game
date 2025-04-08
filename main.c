#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include <time.h>
#include "tabuleiro.h"
#include "jogadores.h"

void seeds(ListaJogadores*, int);

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
    return 0;
}

void seeds(ListaJogadores *lc, int qtd){
    struct jogador novo;
    int success;
    const char *cores[] = {"vermelho", "amarelo", "verde", "azul", "roxo"};

    for(int i = 0; i < qtd; i++){
        novo.quantidadeTapetes = 10;
        novo.dinheiro = 10;

        snprintf(novo.cor, sizeof(novo.cor), "%s", cores[i]);
        inserirFimListaJogadores(lc ,novo);
    }
}
