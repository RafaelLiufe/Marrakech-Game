#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "tabuleiro.h"
#include "jogo.h"
struct assam{
    int orientacao;//0 norte, 1 leste, 2 sul, 3 oeste;
    Espaco* posicao;//ponteiro pro tabuleiro;
};
struct espaco {
    Pilha* tapetes;
    struct espaco* norte;
    struct espaco* sul;
    struct espaco* leste;
    struct espaco* oeste;
    int linha;
    int coluna;
};
struct tap {
    char cor[10];
    struct tap* prox;
    struct tap* outro;
};
typedef struct tap Tap;
Pilha* criarPilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p != NULL) {
        *p = NULL;
    }
    return p;
}
int empilha(Pilha* p1, Pilha* p2, char* cor) {
    if (p1 != NULL || p2 != NULL) {
        Tap* e1 = (Tap*)malloc(sizeof(Tap));
        strcpy(e1->cor, cor);
        Tap* e2 = (Tap*)malloc(sizeof(Tap));
        strcpy(e2->cor, cor);
        e1->outro = e2;
        e2->outro = e1;
        e1->prox = *p1;
        *p1 = e1;
        e2->prox = *p2;
        *p2 = e2;
        return 1;
    } else {
        return 0;
    }
}
Espaco* retEspaco(Tabuleiro* tab, int m, int n) {
    if (m > 4 || m < 0 || n > 4 || n < 0) {
        return NULL;
    } else {
        Espaco* aux = *tab;
        for (int i = 0; i < n; i++) {
            aux = aux->leste;
        }
        for (int i = 0; i < m; i++) {
            aux = aux->sul;
        }
        return aux;
    }
}
Pilha* retPilha(Espaco* esp) {
    if (esp == NULL) {
        return NULL;
    } else {
        return esp->tapetes;
    }
}
Tabuleiro* criarT() {
    Tabuleiro* table = (Tabuleiro*)malloc(sizeof(Tabuleiro));
    if (table != NULL) {
        *table = NULL;
    }
    *table = (Espaco*)malloc(sizeof(Espaco));
    Espaco* aux = *table;
    aux->tapetes = criarPilha();
    aux->linha = 0;
    aux->coluna = 0;
    for (int i = 1; i < TAM; i++) {
        aux->sul = (Espaco*)malloc(sizeof(Espaco));
        aux->sul->norte = aux;
        aux = aux->sul;
        aux->tapetes = criarPilha();
        aux->linha = i;
        aux->coluna = 0;
    }
    aux->sul = NULL;
    Espaco* ref = *table;
    for (int i = 1; i <= TAM; i++) {
        aux = ref;
        for (int j = 1; j < TAM; j++) {
            aux->leste = (Espaco*)malloc(sizeof(Espaco));
            aux->leste->oeste = aux;
            aux = aux->leste;
            aux->linha = i - 1;
            aux->coluna = j;
            aux->tapetes = criarPilha();
        }
        aux->leste = NULL;
        ref = ref->sul;
    }
    ref = *table;
    aux = ref->leste;
    Espaco* ref2;
    Espaco* aux2;
    for (int i = 1; i < TAM; i++) {
        ref2 = ref;
        aux2 = aux;
        ref = ref->leste;
        aux = aux->leste;
        for (int j = 1; j < TAM; j++) {
            aux2->sul = ref2->sul->leste;
            aux2->sul->norte = ref2->leste;
            ref2 = ref2->sul;
            aux2 = aux2->sul;
        }
    }
    ref = *table;
    int cont = 0;
    while (ref != NULL) {
        if (ref->leste == NULL && cont == 0) {
            ref->norte = ref;
            ref = ref->leste;
        } else if (cont == 0) {
            ref->norte = ref->leste;
            ref = ref->leste;
            cont++;
        } else if (cont == 1) {
            ref->norte = ref->oeste;
            ref = ref->leste;
            cont--;
        }
    }
    ref = *table;
    cont = 0;
    while (ref != NULL) {
        if (ref->sul == NULL && cont == 0) {
            ref->oeste = ref;
            ref = ref->sul;
        } else if (cont == 0) {
            ref->oeste = ref->sul;
            ref = ref->sul;
            cont++;
        } else if (cont == 1) {
            ref->oeste = ref->norte;
            ref = ref->sul;
            cont--;
        }
    }
    ref = *table;
    while (ref->leste != NULL){
        ref = ref->leste;
    }
    cont = 0;
    while (ref != NULL) {
        if (ref->sul == NULL && cont == 0) {
            ref->leste = ref;
            ref = ref->sul;
        } else if (cont == 0) {
            ref->leste = ref->sul;
            ref = ref->sul;
            cont++;
        } else if (cont == 1) {
            ref->leste = ref->norte;
            ref = ref->sul;
            cont--;
        }
    }
    ref = *table;
    for (int i = 0; i < TAM - 1; i++) {
        ref = ref->leste;
    }
    for (int i = 0; i < TAM - 1; i++) {
        ref = ref->sul;
    }
    //if (ref->oeste->oeste->oeste->oeste->sul == NULL) printf("sim"); ***Teste***
    //if (ref->oeste->sul == NULL) printf("nulo"); ***Teste***
    for (int i = 0; i < TAM; i++) {
        if (TAM % 2 != 0 && i == TAM - 1) {
            ref->sul = ref;
        } else if (i % 2 == 0) {
            ref->sul = ref->oeste;
            ref = ref->oeste;
        } else {
            ref->sul = ref->leste;
            ref = ref->oeste;
        }
    }

    return table;
}
void printTable(Tabuleiro* tab, Assam* ass) {
    void headLine() {
        for (int i = 0; i < TAM; i++) {
            printf("+ - ");
        }
        printf("+\n");
    }
    void innerLine(Espaco* ref) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        Espaco* aux = ref;
        for (int i = 0; i < TAM; i++) {
            if (*(aux->tapetes) != NULL) {
                printf("| ");
                Tap* tap = *(aux->tapetes);
                if (strcmp(tap->cor, "vermelho") == 0) {
                    SetConsoleTextAttribute(hConsole, 4);
                } else if (strcmp(tap->cor, "amarelo") == 0) {
                    SetConsoleTextAttribute(hConsole, 6);
                } else if (strcmp(tap->cor, "verde") == 0) {
                    SetConsoleTextAttribute(hConsole, 2);
                } else if (strcmp(tap->cor, "azul") == 0) {
                    SetConsoleTextAttribute(hConsole, 1);
                } else {
                    SetConsoleTextAttribute(hConsole, 5);
                }
                printf("■ ");
                SetConsoleTextAttribute(hConsole, 7);
            } else if ((*ass)->posicao == aux) {
                printf("| ");
                SetConsoleTextAttribute(hConsole, 3);
                switch ((*ass)->orientacao) {
                case 0:
                    printf("▲ ");
                    break;
                case 1:
                    printf("► ");
                    break;
                case 2:
                    printf("▼ ");
                    break;
                case 3:
                    printf("◄ ");
                    break;
                }
                SetConsoleTextAttribute(hConsole, 7);
            } else {
                printf("|   ");
            }
            aux = aux->leste;
        }
        printf("|\n");
    }
    if (tab != NULL && *tab != NULL) {
        headLine();
        Espaco* ref = *tab;
        for (int i = 0; i < TAM; i++) {
            innerLine(ref);
            headLine();
            ref = ref->sul;
        }
    }
}
void rotacionarAssamHor(Assam* ass) {
    if (ass != NULL) {
        if ((*ass)->orientacao != 3) {
            (*ass)->orientacao += 1;
        } else {
            (*ass)->orientacao = 0;
        }
    }
}
void rotacionarAssamAntiHor(Assam* ass) {
    if (*ass != NULL) {
        if ((*ass)->orientacao != 0) {
            (*ass)->orientacao -= 1;
        } else {
            (*ass)->orientacao = 3;
        }
    }
}
