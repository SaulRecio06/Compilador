#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "Tokens.h"

struct nodo *raiz = NULL;
struct nodo *act = NULL;

void limpiarToken(struct Token token){
    token.valor = 0;
    memset(token.lexema, 0, sizeof(token.lexema));
    memset(token.nombre, 0, sizeof(token.nombre));
    token.tipo = 0;
    token.numCol = 0;
    token.numLin = 0;
}

void insertar(struct Token token)
{
    struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));
    nuevo->info = token;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    if (raiz == NULL)
    {
        raiz = nuevo;
        act = nuevo;
    }
    else
    {
        nuevo->izq = act;
        act->der = nuevo;
        act = nuevo;
    }
}

void imprimirLista(struct nodo *reco)
{
    if (reco != NULL)
    {
        printf("Nombre: %-20s\t", reco->info.nombre);
        printf("Tipo: %d\t", reco->info.tipo);
        switch (reco->info.tipo) {
            case 0:{
                printf("Tipo: PalRes\t");
                break;
            }
            case 1:{
                printf("Tipo: ID\t");
                break;
            }
            case 2:{
                printf("Tipo: Num\t");
                break;
            }
            case 3:{
                printf("Tipo: Sim\t");
                break;
            }
            case 4:{
                printf("Tipo: TipoDato\t");
                break;
            }
            case 5:{
                printf("Tipo: Cadena\t");
                break;
            }
            case 6:{
                printf("Tipo: ERROR\t");
                break;
            }
            case 7:{
                printf("Tipo: BOOLEANO\t");
                break;
            }
        }
        printf("Lexema: %-10s\t", reco->info.lexema);
        printf("Valor: %-10.2f ", reco->info.valor);
        printf("Linea: %-10d Columna: %d\n", reco->info.numLin, reco->info.numCol);
        imprimirLista(reco->der);
    }

}
