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

void leerTokens(char* prog){
 
    int lines = 1;
    int columna = 0;
    char aux[255];
    memset(aux, 0, sizeof(aux));
    int x = 0;
    int y = 0;
    struct Token token;
    bool cadena = false;
    int cadenaAux = 0;
    while(prog[x] != EOF){
        if(prog[x] == '\n'){
            lines++;
            columna = 0;
        }
        char c = prog[x];
        if(cadena == true && cadenaAux != 2){
            if(prog[x] == '"'){
                cadena = true;
                cadenaAux++;
            }
            aux[y] = prog[x];
            y++;
        }
        else if(cadenaAux == 2){
            if(esCadena(aux, &token)){
                cadena = false;
                cadenaAux = 0;
                token.numCol = columna;
                token.numLin = lines;
                insertar(token);
                limpiarToken(token);
            }
            else if(aux[0] == '"'){
                token.tipo = ERROR;
                strcpy(token.nombre, "Error Comilla");
                token.valor = 0;
                strcpy(token.lexema, "Error Comilla");
                token.numCol = columna;
                token.numLin = lines;
                insertar(token);
                limpiarToken(token);
            }
            memset(aux, 0, sizeof(aux));
            y = 0;
            continue;
        }
        else{
            if(esLimitador(prog[x])) {
                if(y!=0){
                   
                    if(tipoDato(aux, &token)){
                        token.numCol = columna;
                        token.numLin = lines;
                        insertar(token);
                        limpiarToken(token);
                      
                    }
                    else if(palReservada(aux, &token)){
                        token.numCol = columna;
                        token.numLin = lines;
                        insertar(token);
                        limpiarToken(token);
                    }
                    else if(esBool(aux, &token)){
                        token.numCol = columna;
                        token.numLin = lines;
                        insertar(token);
                        limpiarToken(token);
                    }
                    else if (esIdentificador(aux, &token)){
                        token.numCol = columna;
                        token.numLin = lines;
                        insertar(token);
                        limpiarToken(token);
                    }
                    else if (esNumero(aux, &token)){
                        token.numCol = columna;
                        token.numLin = lines;
                        insertar(token);
                        limpiarToken(token);
                    }
                   
                    else if(aux[0] == '"'){
                        token.tipo = ERROR;
                        strcpy(token.nombre, "Error Comilla");
                        token.valor = 0;
                        strcpy(token.lexema, "Error Comilla");
                        token.numCol = columna;
                        token.numLin = lines;
                        insertar(token);
                        limpiarToken(token);
                    }
                    else{
                        token.tipo = ERROR;
                        strcpy(token.nombre, "ERROR");
                        token.valor = 0;
                        strcpy(token.lexema, "ERROR");
                        token.numCol = columna;
                        token.numLin = lines;
                        insertar(token);
                        limpiarToken(token);
                    }
                    memset(aux, 0, sizeof(aux));
                    y = 0;
                    continue;
                }
                else{
                    if(operador(prog[x], &token)){

                        token.numCol = columna;
                        token.numLin = lines;
                        insertar(token);
                        limpiarToken(token);
                        //x++;
                        //continue;
                    }
                    else if(esTerminador(prog[x], &token)){
                        if(prog[x] == '\n'){
                            lines++;
                            columna = 0;
                        }
                        else if(prog[x] == EOF){
                        }
                        else{
                        }
                        token.numCol = columna;
                        token.numLin = lines;
                        insertar(token);
                        limpiarToken(token);
                  
                    }

                }
            }
            else{
                if(prog[x] == '"'){
                    cadena = true;
                    cadenaAux++;
                }
                aux[y] = prog[x];
                y++;
            }
        }
        columna++;
        x++;
    }
    if(cadena == true){
        token.tipo = ERROR;
        strcpy(token.nombre, "ERROR Comilla");
        token.valor = 0;
        strcpy(token.lexema, "ERROR Comilla");
        token.numCol = columna;
        token.numLin = lines;
        insertar(token);
        limpiarToken(token);
    }
}
