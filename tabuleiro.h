#define TAM 7
typedef struct espaco Espaco;
typedef Espaco* Tabuleiro;
typedef struct assam* Assam;

Tabuleiro* criarT();
void printTable(Tabuleiro*, Assam*);
Espaco* retEspaco(Tabuleiro*, int, int);
void rotacionarAssamHor(Assam*);
void rotacionarAssamAntiHor(Assam*);
