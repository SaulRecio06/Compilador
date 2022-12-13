#ifndef TOKENS_H_INCLUDED
#define TOKENS_H_INCLUDED

typedef enum tipoToken{
    PalRes, //0
    ID, //1
    Num, //2
    Sim, //3
    TipoDato, //4
    Cadena, //5
    ERROR, //6
    Booleano //7
} tt;

struct Token{
    char nombre[255];
    enum tipoToken tipo;
    char lexema[255];
    float valor;
    int numLin;
    int numCol;
};

struct nodo{
    struct Token info;
    struct nodo *izq;
    struct nodo *der;
};

extern struct nodo *raiz;
 extern struct nodo *act;


void limpiarToken(struct Token token);
void insertar(struct Token token);
void imprimirLista(struct nodo *reco);

#endif // TOKENS_H_INCLUDED
