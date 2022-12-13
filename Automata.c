#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "Automata.h"
#include "leerTokens.h"
#include "Sintaxis.h"
#include "Tokens.h"




bool esLimitador(char c){
    if(c == ' ' || c == ';' || c == '[' || c == ']' || c == '(' || c == ')' || c == '\n' || c == EOF || c == '\t' ||
       c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '=' || c == '|' || c == '&' ||
       c == '{' || c == '}'){
        return true;
    }
    return false;
}

bool esTerminador(char c, struct Token *token){
    if(c == ';' || c == '[' || c == ']' || c == '(' || c == ')' || c == '"'|| c == '|'|| c == '&' || c == '{' || c == '}'){
        memset(token->lexema, 0, sizeof(token->lexema));
        token->lexema[0] = c;
        token->tipo = Sim;
        token->valor = 0;
        switch (c) {
            case ';':{
                strcpy(token->nombre, "PuntoYComa");
                break;
            }
            case '[':{
                strcpy(token->nombre, "CorcheteIzq");
                break;
            }
            case ']':{
                strcpy(token->nombre, "CorcheteDer");
                break;
            }
            case '(':{
                strcpy(token->nombre, "ParentesisIzq");
                break;
            }
            case ')':{
                strcpy(token->nombre, "ParentesisDer");
                break;
            }
            case '"':{
                strcpy(token->nombre, "ComillaDoble");
                break;
            }
            case '|':{
                strcpy(token->nombre, "OR");
                break;
            }case '&':{
                strcpy(token->nombre, "AND");
                break;
            }case '{':{
                strcpy(token->nombre, "LlaveIzq");
                break;
            }case '}':{
                strcpy(token->nombre, "LlaveDer");
                break;
            }
            default:
                break;
        }
        return true;
    }
    return false;
}

bool tipoDato(char* str, struct Token *token){
    if(strcmp(str,"Entero") == 0 || strcmp(str,"Real") == 0 || strcmp(str,"Cadena") == 0 || strcmp(str,"Caracter") == 0 || strcmp(str,"Boleado") == 0){
        strcpy(token->lexema, str);
        token->tipo = TipoDato;
        token->valor = 0;
        strcpy(token->nombre, "Tipo de Dato");
        return true;
    }
    return false;
}

bool operador(char c, struct Token *token){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '>' || c == '<'){
        memset(token->lexema, 0, sizeof(token->lexema));
        token->lexema[0] = c;
        token->valor = 0;
        token->tipo = Sim;
        switch (c) {
            case '+':{
                strcpy(token->nombre, "Mas");
                break;
            }
            case '-':{
                strcpy(token->nombre, "Menos");
                break;
            }
            case '*':{
                strcpy(token->nombre, "Por");
                break;
            }
            case '/':{
                strcpy(token->nombre, "Entre");
                break;
            }
            case '=':{
                strcpy(token->nombre, "Igual");
                break;
            }
            case '>':{
                strcpy(token->nombre, "Mayor");
                break;
            }
            case '<':{
                strcpy(token->nombre, "Menor");
                break;
            }
            default:
                break;
        }
        return true;
    }
    return false;
}

bool esNumero(char* str, struct Token *token){
    int z = 1;
    int punto = 0;
    if(str[0] >= '0' && str[0]<= '9'){
        while(z <= strlen(str)-1){
            if(str[z] == '.'){
                punto++;
            }
            if(str[z] == '-'){
                punto++;

            }
            if(!(str[z] == '.' || (str[z] >= '0' && str[z] <= '9')) && punto == 0){
                return false;
            }
            z++;
        }
        strcpy(token->lexema, str);
        token->tipo = Num;
        strcpy(token->nombre, "Constante");
        token->valor = atof(str); // NOLINT(cert-err34-c,cppcoreguidelines-narrowing-conversions)
        return true;
    }
    return false;
}

bool palReservada(char* str, struct Token *token){
    if(strcmp(str, "Vars") == 0 || strcmp(str, "Inicio") == 0 || strcmp(str, "Regresa") == 0 || strcmp(str, "Mostrar") == 0 ||
       strcmp(str, "Leer") == 0  || strcmp(str, "Ysi") == 0  || strcmp(str, "Entonces") == 0  || strcmp(str, "Para") == 0  || 
       strcmp(str, "Mientras") == 0 || strcmp(str, "Osi") == 0 || strcmp(str, "Vacio") == 0 || strcmp(str, "Clase") == 0 || 
       strcmp(str, "Descanso") == 0 || strcmp(str, "Importacion") == 0 || strcmp(str, "Devuelve") == 0){
        strcpy(token->lexema, str);
        token->tipo = PalRes;
        strcpy(token->nombre, "Instruccion");
        token->valor = 0;
        return true;
    }
    return false;
}

bool esBool(char* str, struct Token *token){
    if(strcmp(str, "Verdadero") == 0 || strcmp(str, "Falso") == 0){
        strcpy(token->lexema, str);
        token->tipo = Booleano;
        strcpy(token->nombre, str);
        token->valor = 0;
        return true;
    }
    return false;
}

bool esIdentificador(char* str, struct Token *token){
    if(str[0] >= 'a' && str[0] <= 'z'){
        int z = 1;
        bool aux;
        while(z <= strlen(str)-1){
            char c = str[z];
            if(!((c >= 'A' && c<= 'Z') || (c >= 'a' && c<= 'z') || (c >= '0' && c<= '9') || c == '_')){
                return false;
            }
            z++;
        }
        strcpy(token->lexema, str);
        token->tipo = ID;
        strcpy(token->nombre, "Identificador");
        token->valor = 0;
        return true;
    }
    return false;
}

bool esCadena(char* str, struct Token *token){
    char c = str[0];
    char z = str[strlen(str)-1];
    if(str[0] == '"' && (str[strlen(str)-1] == '"' || str[strlen(str)-1 == ' '])){
        strcpy(token->lexema, str);
        token->tipo = Cadena;
        strcpy(token->nombre, "Cadena");
        token->valor = 0;
        return true;
    }
    else{
        return false;
    }
    
}
