#define TAM 9
typedef struct espaco Espaco;
typedef Espaco* Tabuleiro;
typedef struct assam* Assam;
typedef struct tap* Pilha;

Tabuleiro* criarT();
Pilha* criarP();
int empilha(Pilha*, Pilha*, char*);
void printTable(Tabuleiro*, Assam*);
Espaco* retEspaco(Tabuleiro*, int, int);
Pilha* retPilha(Espaco*);
void rotacionarAssamHor(Assam*);
void rotacionarAssamAntiHor(Assam*);
