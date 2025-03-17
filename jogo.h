#define TAM 7
typedef struct espaco Espaco;
typedef Espaco* Tabuleiro;
typedef struct tap* Pilha;
typedef struct assam* Assam;

Tabuleiro* criarT();
Pilha* criarP();
int dado();
typedef struct lista* Jogadores;
Jogadores* listaJogadores(int);
int setPlayer(Jogadores*, int, int);
Assam criarAssam();
