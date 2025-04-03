#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include <time.h>
#include "tabuleiro.h"
#include "jogadores.h"

void seeds(ListaJogadores*, int);

int main(){
    ListaJogadores* lista = criarListaJogadores();

    int qnt, cor;
    printf("Quantos jogadores participarao?\n");
    scanf("%i", &qnt);

    seeds(lista, qnt);

    printf("qtd inicial: %d \n", tamanhoListaJogadores(lista));
    int success = removerMeioListaJogadores(lista, "vermelho");

        if(success){
            printf("sucesso remover\n");
        }
        else{
            printf("error remover\n");
        }
        printf("qtd final: %d \n", tamanhoListaJogadores(lista));
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
        success = inserirFimListaJogadores(lc ,novo);

        if(success){
            printf("sucesso insert: %d \n", i);
        }
        else{
            printf("error insert: %d", i);
        }
    }
    printf("Jogaodres inseridos! \n");
}
