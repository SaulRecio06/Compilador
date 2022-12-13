#ifndef AUTOMATA_H_INCLUDED
#define AUTOMATA_H_INCLUDED
#include "Tokens.h"
bool esLimitador(char c);
bool esTerminador(char c, struct Token *token);
bool tipoDato(char* str, struct Token *token);
bool operador(char c, struct Token *token);
bool esNumero(char* str, struct Token *token);
bool palReservada(char* str, struct Token *token);
bool esBool(char* str, struct Token *token);
bool esIdentificador(char* str, struct Token *token);
bool esCadena(char* str, struct Token *token);
#endif // AUTOMATA_H_INCLUDED
