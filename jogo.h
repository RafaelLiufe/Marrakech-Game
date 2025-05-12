//#include <windows.h>
//#include "tabuleiro.h"
typedef struct espaco Espaco;
typedef Espaco* Tabuleiro;
//typedef struct tap* Pilha;
typedef struct assam* Assam;
typedef struct lista* Jogadores;
typedef struct jogadorOf jogadorOf;
typedef struct elementoListaJogadores* ListaJogadores;
//Pilha* criarP();
int dado();
//Jogadores* listaJogadores(int);
//int setPlayer(Jogadores*, int, int);
Assam* criarAssam();
void setPosAssam(Assam*, Espaco*);
int moverAssam(Assam*, int,Tabuleiro*);
int putTapete(Tabuleiro*, Assam*, int, int, Jogadores*, struct jogadorOf*);
int updateInfo(ListaJogadores*, struct jogadorOf*, Assam*, int*);
//int AreaDoTapete(Assam*);
void printInicio();
//void printVez(const char*);
void diceAnim();
DWORD WINAPI passo(LPVOID);
DWORD WINAPI putTap(LPVOID);
DWORD WINAPI dice(LPVOID);
//void printState(Assam*, ListaJogadores*, int, Tabuleiro*);
