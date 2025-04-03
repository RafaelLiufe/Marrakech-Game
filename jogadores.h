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
