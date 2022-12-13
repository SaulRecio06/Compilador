#ifndef SINTAXIS_H_INCLUDED
#define SINTAXIS_H_INCLUDED

struct nodo *sintaxisExp(struct nodo *reco, int edo);
struct nodo *sintaxisVariable(struct nodo *reco, int edo);
struct nodo *sintaxisConstante(struct nodo *reco, int edo);
struct nodo *sintaxisLeer(struct nodo *reco, int edo);
struct nodo *sintaxisEscribir(struct nodo *reco, int edo);
struct nodo *sintaxisAsignar(struct nodo *reco, int edo);
struct nodo *sintaxisSino(struct nodo *reco, int edo);
struct nodo *sintaxisIf(struct nodo *reco, int edo);
struct nodo *sintaxisMientras(struct nodo *reco, int edo) ;
struct nodo *sintaxisPara(struct nodo *reco, int edo);
void sintaxisPrograma(struct nodo *reco, int edo);

#endif // SINTAXIS_H_INCLUDED
