#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "jogo.h"
#include "tabuleiro.h"
#include "jogadores.h"
#include <time.h>
#include <string.h>
#include <math.h>

struct assam{
    int orientacao;//0 norte, 1 leste, 2 sul, 3 oeste;
    Espaco* posicao;//ponteiro pro tabuleiro;
};
struct jogadorOf{
    int dinheiro;
    char cor[10];
    int quantidadeTapetes;
};

int dado(){
    srand(clock());

    int n = 1 + rand()%(6);

    if (n == 1) {
        return 1;
    } else if (n == 2 || n == 3) {
        return 2;
    } else if (n == 4) {
        return 3;
    } else {
        return 4;
    }
}
struct tap {
    char cor[10];
    struct tap* prox;
    struct tap* outro;
};
typedef struct tap Tap;
typedef struct tap* Pilha;
struct espaco {
    Pilha* tapetes;
    struct espaco* norte;
    struct espaco* sul;
    struct espaco* leste;
    struct espaco* oeste;
    int linha;
    int coluna;
};

Assam* criarAssam(){
    Assam *piece;
    piece = (Assam*)malloc(sizeof(Assam));
    if(piece != NULL){
        *piece = (Assam)malloc(sizeof(struct assam));
        (*piece)->orientacao = 0;
        (*piece)->posicao = NULL;
    }

    return piece;
}
void setPosAssam(Assam* ass, Espaco* pos) {
    (*ass)->posicao = pos;
}
Pilha* criarP() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p != NULL) {
        *p = NULL;
    }
    return p;
}
int moverAssam(Assam *piece, int n, Tabuleiro* tab){
    Assam auxPiece = *piece;
    for(int j=0;j<n;j++){
        switch(auxPiece->orientacao){
            case 0:
                if(auxPiece->posicao->linha == 0){
                    if(auxPiece->posicao->coluna == TAM - 1 && TAM%2==1){
                        auxPiece->orientacao = 3;
                    }else{
                        auxPiece->orientacao = 2;
                    }
                }
                auxPiece->posicao = auxPiece->posicao->norte;
                break;
            case 1:
                if(auxPiece->posicao->coluna == TAM - 1){
                    if(auxPiece->posicao->linha == 0 && TAM%2==1){
                        auxPiece->orientacao = 2;
                    }else{
                        auxPiece->orientacao = 3;
                    }
                }
                auxPiece->posicao = auxPiece->posicao->leste;
                break;
            case 2:
                if(auxPiece->posicao->linha == TAM - 1){
                    if(auxPiece->posicao->coluna == 0 && TAM%2==1){
                        auxPiece->orientacao = 1;
                    }else{
                        auxPiece->orientacao = 0;
                    }
                }
                auxPiece->posicao = auxPiece->posicao->sul;
                break;
            case 3:
                if(auxPiece->posicao->coluna == 0){
                    if(auxPiece->posicao->linha == TAM - 1 && TAM%2==1){
                        auxPiece->orientacao = 0;
                    }else{
                        auxPiece->orientacao = 1;
                    }
                }
                auxPiece->posicao = auxPiece->posicao->oeste;
                break;
        }
    }
    return 1;
}
int putTapete(Tabuleiro *board, Assam *piece, int casa1, int casa2, Jogadores *lista_de_jogadores, struct jogadorOf* jogadorVez){
    Espaco *aux1, *aux2;
    Assam auxPiece = *piece;
    if((casa1 < 0 || casa1 > 3 || casa2 < 0 || casa2 > 3)){
        printf("Posições inválidas\n");
        system("pause");
        return 0;
    }
    if((casa2 == (casa1 + 2)%4)){
        printf("Não pode colocar o tapete abaixo de Assam\n");
        system("pause");
        return 0;
    }
    switch(casa1){
        case 0:
            if(auxPiece->posicao->linha == 0){
                printf("Não pode passar da borda do tabuleiro\n");
                system("pause");
                return 0;
            }
            aux1 = auxPiece->posicao->norte;
            break;
        case 1:
            if(auxPiece->posicao->coluna == TAM - 1){
                printf("Não pode passar da borda do tabuleiro\n");
                system("pause");
                return 0;
            }
            aux1 = auxPiece->posicao->leste;
            break;
        case 2:
            if(auxPiece->posicao->linha == TAM - 1){
                printf("Não pode passar da borda do tabuleiro\n");
                system("pause");
                return 0;
            }
            aux1 = auxPiece->posicao->sul;
            break;
        case 3:
            if(auxPiece->posicao->coluna == 0){
                printf("Não pode passar da borda do tabuleiro\n");
                system("pause");
                return 0;
            }
            aux1 = auxPiece->posicao->oeste;
            break;
        default:
            printf("ERRO");
            return 0;
    }
    switch(casa2){
        case 0:
            if(aux1->linha == 0){
                printf("Não pode passar da borda do tabuleiro\n");
                system("pause");
                return 0;
            }
            aux2 = aux1->norte;
            break;
        case 1:
            if(aux1->coluna == TAM - 1){
                printf("Não pode passar da borda do tabuleiro\n");
                system("pause");
                return 0;
            }
            aux2 = aux1->leste;
            break;
        case 2:
            if(aux1->linha == TAM - 1){
                printf("Não pode passar da borda do tabuleiro\n");
                system("pause");
                return 0;
            }
            aux2 = aux1->sul;
            break;
        case 3:
            if(aux1->coluna == 0){
                printf("Não pode passar da borda do tabuleiro\n");
                system("pause");
                return 0;
            }
            aux2 = aux1->oeste;
            break;
        default:
            printf("ERRO");
            return 0;
    }
    if ((*aux1->tapetes) != NULL && (*aux2->tapetes) != NULL) {
        if((*aux1->tapetes)->outro == (*aux2->tapetes)){//há um tapete completo por cima
            printf("Não pode cobrir outro tapete completamente\n");
            system("pause");
            return 0;
        }
    }
    return empilha(aux1->tapetes, aux2->tapetes, jogadorVez->cor);
}
int descontarValor(Assam *piece, Jogadores *lista_jogadores, int player){
    Assam auxPiece = *piece;
    if(strcmp((*auxPiece->posicao->tapetes)->cor, "vermelho")!=0){
        //criar nó descritor com o tamanho da pilha ou implementar algoritmo de busca que retorna a área de um determinado trapete
        return 1;
    }
    return 0;
}
int BuscaProfunda(Espaco *casa, int **visitado, char color[10]) {
    if (visitado[casa->linha][casa->coluna] || *casa->tapetes == NULL || strcmp((*casa->tapetes)->cor, color)!=0)
        return 0;

    visitado[casa->linha][casa->coluna] = 1;

    int size = 1;

    if(casa->coluna!=0)
        size += BuscaProfunda(casa->oeste, visitado, color);//oeste
    if(casa->coluna!=TAM)
        size += BuscaProfunda(casa->leste, visitado, color);//leste
    if(casa->linha!=0)
        size += BuscaProfunda(casa->norte, visitado, color);//norte
    if(casa->linha!=TAM)
        size += BuscaProfunda(casa->sul, visitado, color);//sul

    return size;
}

int AreaDoTapete(Assam* casa) {
    int **visitado = (int**)malloc(sizeof(int*)*TAM);
    for(int i=0;i<TAM;i++)
        visitado[i] = (int*)malloc(sizeof(int)*TAM);
    for(int i=0;i<TAM;i++)
        for(int j=0;j<TAM;j++)
            visitado[i][j] = 0;
    int area = BuscaProfunda((*casa)->posicao, visitado, (*((*casa)->posicao->tapetes))->cor);
    for(int i =0;i<TAM;i++)
        free(visitado[i]);
    free(visitado);
    return area;
}
void printInicio() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 4);
    printf(" __  __                            _                _\n");
    printf("|  \\/  |                          | |              | |\n");
    printf("| \\  / |  __ _  _ __  _ __   __ _ | | __  ___  ___ | |__\n");
    printf("| |\\/| | / _` || '__|| '__| / _` || |/ / / _ \\/ __|| '_ \\\n");
    printf("| |  | || (_| || |   | |   | (_| ||   < |  __/\\__ \\| | | |\n");
    printf("|_|  |_| \\__,_||_|   |_|    \\__,_||_|\\_\\ \\___||___/|_| |_|\n");
    SetConsoleTextAttribute(hConsole, 5);
    printf("\t      _____\n");
    printf("\t     / ____|\n");
    printf("\t    | |  __   __ _  _ __ ___    ___\n");
    printf("\t    | | |_ | / _` || '_ ` _ \\  / _ \\\n");
    printf("\t    | |__| || (_| || | | | | ||  __/\n");
    printf("\t     \\_____| \\__,_||_| |_| |_| \\___|\n");
    SetConsoleTextAttribute(hConsole, 7);

}
void printVez(const char* color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\t\t\t     ");
    printf("Vez do jogador ");
    if (strcmp(color, "vermelho") == 0) {
        SetConsoleTextAttribute(hConsole, 4);
    } else if (strcmp(color, "amarelo") == 0) {
        SetConsoleTextAttribute(hConsole, 6);
    } else if (strcmp(color, "verde") == 0) {
        SetConsoleTextAttribute(hConsole, 2);
    } else if (strcmp(color, "azul") == 0) {
        SetConsoleTextAttribute(hConsole, 1);
    } else {
        SetConsoleTextAttribute(hConsole, 5);
    }
    printf("%s\n", color);
    SetConsoleTextAttribute(hConsole, 7);
}

int updateInfo(ListaJogadores* lista, struct jogadorOf *jogadorVez, Assam* assamPiece, int* removido) {
    Assam aux = *assamPiece;
    const char* tapete = (*aux->posicao->tapetes != NULL) ? (*aux->posicao->tapetes)->cor : " ";
    const char cor[10];
    strcpy(cor, jogadorVez->cor);
    if (strcmp(cor, tapete)==0)
        return 0;
    int area = AreaDoTapete(assamPiece);
    if(area == 0)
        return 0;
    struct jogadorOf* isInGame = criarJ();
    if(!acessarJogadorPorCor(lista, tapete, isInGame))
        return 0;
    free(isInGame);
    int qtd = removerDinheiroListaJogadores(lista, cor, area, jogadorVez, removido);
    adicinarDinheiroListaJogadores(lista, tapete, qtd);
    printf("\t\t Jogador %s pagou %i moedas ao jogador %s\n", cor, qtd, tapete);
    return 1;
}
void diceAnim() {
    HANDLE thread;
    DWORD threadId;

    int diceAux = 0;
    thread = CreateThread(NULL, 0, dice, NULL, 0, &threadId);

    printf("\t\t\t\t  Dado girando");
    for (int i = 1; i <= 8; i++) {
        switch (diceAux) {
            case 0:
                printf("");
                break;
            case 1:
                printf(".");
                break;
            case 2:
                printf("..");
                break;
            case 3:
                printf("...");
                break;
        }
        fflush(stdout);
        Sleep(600);
        for (int i = 1; i <= diceAux; i++) {
            printf("\b \b");
        }
        if (diceAux < 3) {
            diceAux++;
        } else {
            diceAux = 0;
        }
        fflush(stdout);
    }
        printf("\n");
}
DWORD WINAPI passo(LPVOID lpParam) {
    Beep(261, 200);
    return 0;
}
DWORD WINAPI putTap(LPVOID lpParam) {
    Beep(342, 200);
    return 0;
}
DWORD WINAPI dice(LPVOID lpParam) {
    Beep(200, 5000);
    return 0;
}
