struct jogador{
    int dinheiro;
    char cor[10];
    int quantidade;
};

typedef struct elementoListaJogadores *ListaJogadores;

ListaJogadores* criarListaJogadores();
void destruirListaJogadores(ListaJogadores*);
int tamanhoListaJogadores(ListaJogadores*);
int vaziaListaJogadores(ListaJogadores*);
int cheiaListaJogadores(ListaJogadores*);
