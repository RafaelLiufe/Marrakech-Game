#include <stdio.h>
#include <stdlib.h>
#include "jogadores.h"

struct elementoListaJogadores {
    struct jogador dados;
    struct elementoListaJogadores *prox;
    struct elementoListaJogadores *ante;
    int quantidadeTapetes
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
