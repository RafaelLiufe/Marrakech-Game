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
int moverAssam(Assam*, int,Tabuleiro*);
int putTapete(Tabuleiro*, Assam*, int, int, Jogadores*, int);
void printInicio();
void printVez(int);
//void printState(Assam*, ListaJogadores*, int, Tabuleiro*);
