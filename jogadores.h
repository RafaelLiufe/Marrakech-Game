struct jogador{
    int dinheiro;
    char cor[10];
    int quantidadeTapetes;
};

typedef struct elementoListaJogadores *ListaJogadores;

ListaJogadores* criarListaJogadores();
void destruirListaJogadores(ListaJogadores*);
int tamanhoListaJogadores(ListaJogadores*);
int vaziaListaJogadores(ListaJogadores*);
int cheiaListaJogadores(ListaJogadores*);
int inserirFimListaJogadores(ListaJogadores*, struct jogador);
int removerMeioListaJogadores(ListaJogadores*,const char*);
void imprimirListaJogadores(ListaJogadores*);

int removerDinheiroListaJogadores(ListaJogadores*,const char*, int);
int adicinarDinheiroListaJogadores(ListaJogadores*,const char*, int);
int removerTapeteListaJogadores(ListaJogadores*,const char*, int);

int verificarFimJogo(ListaJogadores*);
void verificarVencedor(ListaJogadores*);

int acessarJogadorPorCor(ListaJogadores*, const char* , struct jogador*);
void passarVez(ListaJogadores*, struct jogador*);
