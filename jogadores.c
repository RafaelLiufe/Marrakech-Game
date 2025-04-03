#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogadores.h"

struct elementoListaJogadores {
    struct jogador dados;
    struct elementoListaJogadores *prox;
    //struct elementoListaJogadores *ante;
};

typedef struct elementoListaJogadores ElementoListaJogadores;

ListaJogadores* criarListaJogadores() {
    ListaJogadores *ldcj;
    ldcj = (ListaJogadores*)malloc(sizeof(ListaJogadores));

    if (ldcj != NULL) {
        *ldcj = NULL;
    }

    return ldcj;
}

void destruirListaJogadores(ListaJogadores *lc) {
    if (lc != NULL && *lc != NULL) {
        ElementoListaJogadores *aux, *backup = *lc;
        while ((*lc)->prox != backup) {
            aux = *lc;
            *lc = (*lc)->prox;
            free(aux);
        }
        free(aux);
        *lc = NULL;
        //free(lc);
    }
}

int tamanhoListaJogadores(ListaJogadores *lc) {
    if (vaziaListaJogadores(lc)) {
        return 0;
    }

    int cont = 0;
    ElementoListaJogadores *aux = *lc;

    do {
        cont++;
        aux = aux->prox;
    } while (aux != *lc);

    return cont;
}

int vaziaListaJogadores(ListaJogadores *lc) {
    if (lc == NULL) {
        return 1;
    }
    else if (*lc == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

int cheiaListaJogadores(ListaJogadores *lc) {
    return 0;
}

int inserirFimListaJogadores(ListaJogadores *lc, struct jogador novosdados) {
    if (lc == NULL) {
        return 0;
    }
    else {

        ElementoListaJogadores *novo = (ElementoListaJogadores*)malloc(sizeof(ElementoListaJogadores));

        if (novo == NULL) return 0;

        novo->dados = novosdados;

        if (vaziaListaJogadores(lc)) {
            *lc = novo;
            novo->prox = novo;
        }
        else {
            novo->prox = *lc;
            ElementoListaJogadores *aux = *lc;
            while (aux->prox != *lc) aux = aux->prox;
            aux->prox = novo;
            //novo->ante = aux;
        }
        return 1;
    }
}

int removerMeioListaJogadores(ListaJogadores *lc, const char *cor) {
    if (vaziaListaJogadores(lc)) {
        printf("lista vazia\n");
        return 0;
    }
    else if (strcmp((*lc)->dados.cor, cor) == 0){
        if (*lc == (*lc)->prox) {
            free(lc);
            *lc = NULL;
        }
        else {
            ElementoListaJogadores *aux = *lc;
            ElementoListaJogadores *backup = *lc;
            *lc = aux->prox;
            free(aux);

            aux = *lc;

            while (aux->prox != backup)
                aux = aux->prox;
            aux->prox = *lc;
        }
    }
    else {
        ElementoListaJogadores *ant = *lc;
        ElementoListaJogadores *aux = ant->prox;

        while (aux != *lc && strcmp(aux->dados.cor, cor) != 0) {
            ant = aux;
            aux = aux->prox;
        }
        if (aux == *lc){
            printf("aux == *lc\n");
            return 0;
        }
        ant->prox = aux->prox;
        free(aux);
    }
    return 1;
}
