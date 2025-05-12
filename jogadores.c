#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "jogadores.h"


struct elementoListaJogadores {
    struct jogadorOf dados;
    struct elementoListaJogadores *prox;
};

typedef struct elementoListaJogadores ElementoListaJogadores;

void imprimirListaJogadores(ListaJogadores *lc) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (vaziaListaJogadores(lc)) {
        printf("Lista vazia ou nao inicializada!\n");
        return;
    }

    ElementoListaJogadores *inicio = *lc;
    ElementoListaJogadores *aux = inicio;
    int cor;

    printf("\t\t\t+-----------+--------+----------+\n");
    printf("\t\t\t|    Cor    | Caixa  | Tapetes  |\n");
    printf("\t\t\t+-----------+--------+----------+\n");
    do {
        printf("\t\t\t");
        if (strcmp(aux->dados.cor, "vermelho") == 0) {
            cor = 4;
        } else if (strcmp(aux->dados.cor, "amarelo") == 0) {
            cor = 6;
        } else if (strcmp(aux->dados.cor, "verde") == 0) {
            cor = 2;
        } else if (strcmp(aux->dados.cor, "azul") == 0) {
            cor = 1;
        } else {
            cor = 5;
        }

        printf("| ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("%-9s", aux->dados.cor);
        SetConsoleTextAttribute(hConsole, 7);
        printf(" | ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("$%-5d", aux->dados.dinheiro);
        SetConsoleTextAttribute(hConsole, 7);
        printf(" | ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("%-8d", aux->dados.quantidadeTapetes);
        SetConsoleTextAttribute(hConsole, 7);
        printf(" |\n");
        //printf(" | %-6d | %-8d |\n", aux->dados.dinheiro, aux->dados.quantidadeTapetes);
        aux = aux->prox;
    } while (aux != inicio);
    printf("\t\t\t+-----------+--------+----------+\n");
}
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
    /*if (lc == NULL) {
        return 1;
    }
    else if (*lc == NULL) {
        return 1;
    }
    else {
        return 0;
    }*/
    return lc == NULL || *lc == NULL;
}

int cheiaListaJogadores(ListaJogadores *lc) {
    return 0;
}

int inserirFimListaJogadores(ListaJogadores *lc, struct jogadorOf novosdados) {
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

int removerMeioListaJogadores(ListaJogadores *lc, const char *cor, struct jogadorOf *jogadorVez) {
    if (vaziaListaJogadores(lc)) {
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
            *jogadorVez = aux->dados;
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
            return 0;
        }
        ant->prox = aux->prox;
        *jogadorVez = ant->dados;//antes de ser eliminado ele passa a vez
        free(aux);
    }
    return 1;
}

int removerDinheiroListaJogadores(ListaJogadores *lc, const char *cor, int qtd, struct jogadorOf *jogadorVez, int* removido) {
    if (vaziaListaJogadores(lc)) {
        printf("Lista vazia\n");
        return 0;
    }

    ElementoListaJogadores *aux = *lc;
    do {
        if (strcmp(aux->dados.cor, cor) == 0) {
            aux->dados.dinheiro -= qtd;

            if (aux->dados.dinheiro <= 0) {
                printf("Jogador %s ficou sem dinheiro, logo, perdeu!\n", cor);
                qtd += aux->dados.dinheiro;
                *removido = removerMeioListaJogadores(lc, cor, jogadorVez);
            }

            return qtd;//retorna a quantidade que deve pagar, resolve o caso dele ter que pagar 5 tendo apenas 3 por exemplo
        }
        aux = aux->prox;
    } while (aux != *lc);

    return 0;
}

int adicinarDinheiroListaJogadores(ListaJogadores *lc, const char *cor, int qtd) {
    if (vaziaListaJogadores(lc)) {
        return 0;
    }

    ElementoListaJogadores *aux = *lc;
    do {
        if (strcmp(aux->dados.cor, cor) == 0) {
            aux->dados.dinheiro += qtd;

            //printf("Jogador %s recebeu %d. Novo saldo: %d\n", cor, qtd, aux->dados.dinheiro);
            return 1;
        }
        aux = aux->prox;
    } while (aux != *lc);

    return 0;
}

int removerTapeteListaJogadores(ListaJogadores *lc, struct jogadorOf *jogadorVez, int qtd) {
    if (vaziaListaJogadores(lc)) {
        return 0;
    }
    const char *cor = jogadorVez->cor;
    ElementoListaJogadores *aux = *lc;
    do {
        if (strcmp(aux->dados.cor, cor) == 0) {
            aux->dados.quantidadeTapetes -= qtd;

            if (aux->dados.quantidadeTapetes < 0) {
                aux->dados.quantidadeTapetes = 0;
            }

            //printf("Jogador %s perdeu %d tapete(s). Restam: %d\n", cor, qtd, aux->dados.quantidadeTapetes);
            return 1;
        }
        aux = aux->prox;
    } while (aux != *lc);

    //printf("Jogador com a cor %s nao encontrado.\n", cor);
    return 0;
}

int verificarFimJogo(ListaJogadores *lc) {
    if (vaziaListaJogadores(lc)) {
        return 1; // Lista vazia, fim de jogo
    }

    ElementoListaJogadores *inicio = *lc;
    ElementoListaJogadores *aux = inicio;

    // Se só tem um jogador na lista
    if (aux->prox == aux) {
        //printf("fim so tem um jogaador");
        return 1; // Fim de jogo
    }

    // Verificar se todos os jogadores estão com 0 tapetes
    int todosSemTapetes = 1; // Pressupõe que todos estão sem tapetes

    do {
        if (aux->dados.quantidadeTapetes > 0) {
            todosSemTapetes = 0; // Achou um com tapetes, continua o jogo
            break;
        }
        aux = aux->prox;
    } while (aux != inicio);

    //printf("fim todos com 0");
    return todosSemTapetes;
}

void verificarVencedor(ListaJogadores *lc) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (vaziaListaJogadores(lc)) {
        printf("Lista vazia, sem vencedor.\n");
        return;
    }

    ElementoListaJogadores *inicio = *lc;
    ElementoListaJogadores *aux = inicio;
    int cor;

    if (strcmp(aux->dados.cor, "vermelho") == 0) {
        cor = 4;
    } else if (strcmp(aux->dados.cor, "amarelo") == 0) {
        cor = 6;
    } else if (strcmp(aux->dados.cor, "verde") == 0) {
        cor = 2;
    } else if (strcmp(aux->dados.cor, "azul") == 0) {
        cor = 1;
    } else {
        cor = 5;
    }
    if (aux->prox == aux) {
        printf("+---------+----------+----------+\n");
        printf("| Ranking |   Cor    | Dinheiro |\n");
        printf("+---------+----------+----------+\n");
        printf("|    ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("1");
        SetConsoleTextAttribute(hConsole, 7);
        printf("    | ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("%-8s", aux->dados.cor);
        SetConsoleTextAttribute(hConsole, 7);
        printf(" | ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("$%-7d", aux->dados.dinheiro);
        SetConsoleTextAttribute(hConsole, 7);
        printf(" |\n");
        printf("+---------+----------+----------+\n");
        printf("Vencedor: ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("%s", aux->dados.cor);
        SetConsoleTextAttribute(hConsole, 7);
        printf("!\n");
        return;
    }

    // Contar jogadores
    int count = 0;
    do {
        count++;
        aux = aux->prox;
    } while (aux != inicio);

    // Copiar jogadores para vetor
    ElementoListaJogadores *jogadores[count];
    aux = inicio;
    for (int i = 0; i < count; i++) {
        jogadores[i] = aux;
        aux = aux->prox;
    }

    // Ordenar jogadores por dinheiro (bubble sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (jogadores[j]->dados.dinheiro < jogadores[j + 1]->dados.dinheiro) {
                ElementoListaJogadores *temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }

    // Imprimir ranking
    printf("\t\t\t+---------+----------+----------+\n");
    printf("\t\t\t| Ranking |   Cor    | Dinheiro |\n");
    printf("\t\t\t+---------+----------+----------+\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(jogadores[i]->dados.cor, "vermelho") == 0) {
            cor = 4;
        } else if (strcmp(jogadores[i]->dados.cor, "amarelo") == 0) {
            cor = 6;
        } else if (strcmp(jogadores[i]->dados.cor, "verde") == 0) {
            cor = 2;
        } else if (strcmp(jogadores[i]->dados.cor, "azul") == 0) {
            cor = 1;
        } else {
            cor = 5;
        }
        printf("\t\t\t|   ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("%-5d", i + 1);
        SetConsoleTextAttribute(hConsole, 7);
        printf(" | ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("%-8s", jogadores[i]->dados.cor);
        SetConsoleTextAttribute(hConsole, 7);
        printf(" | ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("$%-7d", jogadores[i]->dados.dinheiro);
        SetConsoleTextAttribute(hConsole, 7);
        printf(" |\n");
    }
    printf("\t\t\t+---------+----------+----------+\n");

    // Verificar empate
    if (jogadores[0]->dados.dinheiro == jogadores[1]->dados.dinheiro) {
        printf("\t\t   Empate entre jogadores com maior dinheiro:\n");
        for (int i = 0; i < count; i++) {
            if (strcmp(jogadores[i]->dados.cor, "vermelho") == 0) {
                cor = 4;
            } else if (strcmp(jogadores[i]->dados.cor, "amarelo") == 0) {
                cor = 6;
            } else if (strcmp(jogadores[i]->dados.cor, "verde") == 0) {
                cor = 2;
            } else if (strcmp(jogadores[i]->dados.cor, "azul") == 0) {
                cor = 1;
            } else {
                cor = 5;
            }

            if (jogadores[i]->dados.dinheiro == jogadores[0]->dados.dinheiro) {
                printf("\t\t\t\t- ");
                SetConsoleTextAttribute(hConsole, cor);
                printf("%s", jogadores[i]->dados.cor);
                SetConsoleTextAttribute(hConsole, 7);
                printf(" com ");
                SetConsoleTextAttribute(hConsole, cor);
                printf("$%d", jogadores[i]->dados.dinheiro);
                SetConsoleTextAttribute(hConsole, 7);
                printf(" -\n");
            } else {
                break;
            }
        }
    } else {
        if (strcmp(jogadores[0]->dados.cor, "vermelho") == 0) {
            cor = 4;
        } else if (strcmp(jogadores[0]->dados.cor, "amarelo") == 0) {
            cor = 6;
        } else if (strcmp(jogadores[0]->dados.cor, "verde") == 0) {
            cor = 2;
        } else if (strcmp(jogadores[0]->dados.cor, "azul") == 0) {
            cor = 1;
        } else {
            cor = 5;
        }
        printf("\t\t\t      Vencedor: ");
        SetConsoleTextAttribute(hConsole, cor);
        printf("%s", jogadores[0]->dados.cor);
        SetConsoleTextAttribute(hConsole, 7);
        printf("!\n");
    }
}
struct jogadorOf* criarJ() {
    struct jogadorOf* novo = (struct jogadorOf*)malloc(sizeof(struct jogadorOf));
    if (novo != NULL) {
        return novo;
    } else {
        printf("jogador nulo");
        return NULL;
    }
}
int acessarJogadorPorCor(ListaJogadores *lc, const char *cor, struct jogadorOf *j) {
    if (vaziaListaJogadores(lc)) {
        strcpy(j->cor, "");
        return 0;
    } else if (strcmp((*lc)->dados.cor, cor) == 0){
        strcpy(j->cor, (*lc)->dados.cor);
        j->dinheiro = (*lc)->dados.dinheiro;
        j->quantidadeTapetes = (*lc)->dados.quantidadeTapetes;
    } else {
        ElementoListaJogadores *aux = *lc;
        do {
            aux = aux->prox;
        } while (aux != *lc && strcmp(aux->dados.cor, cor) != 0);

        if (aux == *lc){
            strcpy(j->cor, "");
            return 0;
        }
        j = &aux->dados;
        strcpy(j->cor, aux->dados.cor);
        j->dinheiro = aux->dados.dinheiro;
        j->quantidadeTapetes = aux->dados.quantidadeTapetes;
    }
    return 1;
}

void passarVez(ListaJogadores *lc, struct jogadorOf *j) {
    if (*lc == NULL || j == NULL) return;

    ElementoListaJogadores *atual = *lc;

    do {
        if (strcmp(atual->dados.cor, j->cor) == 0) {
            // Encontrou: o próximo é o jogador da vez
            *j = atual->prox->dados;
            return;
        }
        atual = atual->prox;
    } while (atual != *lc);
}

