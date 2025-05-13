typedef struct jogadorOf JogadorOf;
typedef struct espaco* Tabuleiro;
typedef struct assam* Assam;
typedef struct elementoListaJogadores* ListaJogadores;
struct jogadorOf* criarJ();
void seeds(ListaJogadores*, int);
void printState(Assam*, Tabuleiro*, ListaJogadores*, struct jogadorOf *);
ListaJogadores* criarListaJogadores();

void imprimirListaJogadores(ListaJogadores*);

int removerTapeteListaJogadores(ListaJogadores*,struct jogadorOf*, int);

int verificarFimJogo(ListaJogadores*);
void verificarVencedor(ListaJogadores*);

int acessarJogadorPorCor(ListaJogadores*, const char* , struct jogadorOf*);
void passarVez(ListaJogadores*, struct jogadorOf*);
