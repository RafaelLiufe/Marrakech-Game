#include "tabuleiro.h"
typedef struct espaco Espaco;
typedef Espaco* Tabuleiro;
typedef struct tap* Pilha;
typedef struct assam* Assam;
typedef struct lista* Jogadores;

Pilha* criarP();
int dado();
Jogadores* listaJogadores(int);
int setPlayer(Jogadores*, int, int);
Assam* criarAssam();
void setPosAssam(Assam*, Espaco*);
int moverAssam(Tabuleiro*, Assam*, int, int);
int putTapete(Tabuleiro*, Assam*, int, int, Jogadores*, int);
