#define TAM 5
typedef struct espaco Espaco;
typedef Espaco* Tabuleiro;
typedef struct tap* Pilha;

Tabuleiro* criarT();
Pilha* criarP();
void empilha(Pilha*, Pilha*, char*);
void printTable(Tabuleiro*, Assam*);
Espaco* retMid(Tabuleiro*);
Espaco* retEspaco(Tabuleiro*, int, int);
Pilha* retPilha(Espaco*);
void rotacionarAssamHor(Assam*);
void rotacionarAssamAntiHor(Assam*);
