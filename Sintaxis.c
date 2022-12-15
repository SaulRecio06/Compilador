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


struct nodo *sintaxisExp(struct nodo *reco, int edo){
    if ( edo == 1 ){
        if ( reco->info.tipo == ID || reco->info.tipo == Num ){
            /*if(strcmp(reco->info.lexema, ";")){
                edo = 5;
                sintaxisExp(reco, edo);
            }
            else{
                edo = 2;
                sintaxisExp(reco->der, edo);
            }*/
            edo = 2;
            sintaxisExp(reco->der, edo);
        }
        else if(strcmp(reco->info.lexema, "(") == 0){
            edo = 3;
            sintaxisExp(reco->der, edo);
        }
        /*else if(strcmp(reco->info.lexema, ";")){
            edo = 5;
            sintaxisExp(reco, edo);
        }*/
        else {
            printf("Error de sintaxis: Se esperaba un Identificador, un Número o un paréntesis en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    }
    else if ( edo == 2 ) {
        if ( strcmp(reco->info.lexema, "+") == 0 || strcmp(reco->info.lexema, "-") == 0 || strcmp(reco->info.lexema, "*") == 0 || strcmp(reco->info.lexema, "/") == 0 ) {
            edo = 1;
            sintaxisExp(reco->der, edo);
        }
        else if(strcmp(reco->info.lexema, ")") == 0){
            return reco;
        }
        else if(strcmp(reco->info.lexema, ";") == 0){
            edo = 5;
            sintaxisExp(reco, edo);
        }
        else {
            printf("Error de sintaxis: Se esperaba un símbolo operador en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    }
    else if ( edo == 3 ) {
        edo = 1;
        //struct nodo *recoAux = sintaxisExp(reco, edo);
        reco = sintaxisExp(reco, edo);
        if(strcmp(reco->info.lexema, ")") == 0){
            edo = 2;
            sintaxisExp(reco->der, edo);
        }
        else{
            printf("Error de sintaxis: Se esperaba un parentesis \")\" derecho en la linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    }
    else if ( edo == 5 ) {
        if ( strcasecmp(reco->info.lexema, ";") != 0 ) {
            printf("321Error de sintaxis: Se esperaba el símbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
        else {
            return (reco);
        }
    }
}

struct nodo * sintaxisVariable(struct nodo *reco, int edo) {
    if ( edo == 1 ){
        if( reco->info.tipo == TipoDato) {
            edo = 2;
            sintaxisVariable(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba un Tipo de Dato en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 2 ) {
        if ( reco->info.tipo == ID ){
            edo = 3;
            sintaxisVariable(reco->der, edo);
        } else{
            printf("Error de sintaxis: Se esperaba un Identificador en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 3 ){
        if ( strcasecmp(reco->info.lexema, "=") == 0){
            edo = 4;
            sintaxisVariable(reco->der, edo);
        } else{
            printf("Error de sintaxis: Se esperaba el simbolo de igualdad ( = ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 4 ){
        if((reco->info.tipo == Cadena) || (reco->info.tipo == Num) || (reco->info.tipo == Booleano)){
            edo = 5;
            sintaxisVariable(reco->der, edo);
        }
        else if(reco->info.tipo == ID) {
            printf("Error de sintaxis: Una variable sólo se puede inicializar con un valor constante, en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
        else {
            printf("Error de sintaxis: Debe asignarse un valor a la variable en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if (edo == 5){
        if ( strcasecmp(reco->info.lexema, ";") != 0 ) {
            printf("Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        } else {
            return (reco->der);
        }
    }
}

struct nodo * sintaxisConstante(struct nodo *reco, int edo) {

    if( edo == 1 ) {
        if ( strcasecmp(reco->info.lexema, "constante") == 0) {
            edo = 2;
            sintaxisConstante(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba la palabra (constante) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    }else if ( edo == 2 ){
        if( reco->info.tipo == TipoDato) {
            edo = 3;
            sintaxisVariable(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba un Tipo de Dato en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 3 ) {
        if ( reco->info.tipo == ID ){
            edo = 4;
            sintaxisVariable(reco->der, edo);
        } else{
            printf("Error de sintaxis: Se esperaba un Identificador en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 4 ){
        if ( strcasecmp(reco->info.lexema, "=") == 0){
            edo = 5;
            sintaxisVariable(reco->der, edo);
        } else{
            printf("Error de sintaxis: Se esperaba el simbolo de igualdad ( = ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 5 ){
        if (reco->info.tipo == Num) {
            edo = 6;
            sintaxisVariable(reco->der, edo);
        } else if ( reco->info.tipo == Cadena ) {
            edo = 6;
            sintaxisVariable(reco->der, edo);
        } else if ( reco->info.tipo == Booleano ) {
            edo = 6;
            sintaxisVariable(reco->der, edo);
        } else {
            printf("Error de sintaxis: Debe asignarse un valor a la variable en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if (edo == 6){
        if ( strcasecmp(reco->info.lexema, ";") != 0 ) {
            printf("Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        } else {
            return (reco->der);
        }
    }
}

struct nodo *sintaxisLeer(struct nodo *reco, int edo){
    if ( edo == 1 ){
        if ( strcasecmp(reco->info.lexema, "Leer") == 0 ){
            edo = 2;
            sintaxisLeer(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba la palabra (Leer) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 2 ) {
        if ( strcasecmp(reco->info.lexema, "(") == 0 ) {
            edo = 3;
            sintaxisLeer(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Parentesis de apertura ( ( )  en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 3 ) {
        //printf(reco->info.lexema);
        if ( reco->info.tipo == 1 ){ //Espera recibir un identificador
            edo = 4;
            sintaxisLeer(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba un Identificador Leer en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 4 ) {
        if ( strcasecmp(reco->info.lexema, ")") == 0 ) {
            edo = 5;
            sintaxisLeer(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Parentesis de cierre ( ) ) Leer  en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 5 ) {
        if ( strcasecmp(reco->info.lexema, ";") != 0 ) {
            printf("Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        } else {
            return (reco->der);
        }
    }
}

struct nodo *sintaxisEscribir(struct nodo *reco, int edo){
    if ( edo == 1 ) {
        if ( strcasecmp(reco->info.lexema, "Mostrar") == 0 ){
            edo = 2;
            sintaxisEscribir(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba la palabra (Mostrar) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 2) {
        if ( strcasecmp(reco->info.lexema, "(") == 0 ) {
            edo = 3;
            sintaxisEscribir(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Parentesis de apertura ( ( )  en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 3 ) {
        if ( (reco->info.tipo == 1) || (reco->info.tipo == 5 ) || ( strcasecmp(reco->info.lexema, "+") == 0 ) ){
            //Espera recibir una cadena en tipo 5 o un ID en tipo 1 o el simbolo "+" para concatenaciones
            edo = 3;
            sintaxisEscribir(reco->der, edo);
        } else if ( !( (reco->info.tipo == 1) || (reco->info.tipo == 5 ) || ( strcasecmp(reco->info.lexema, "+") == 0 ) ) ) {
            edo = 4;
            sintaxisEscribir(reco, edo);
        }else {
            printf("Error de sintaxis: Se esperaba una Cadena o un Identificador en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 4 ) {
        if ( strcasecmp(reco->info.lexema, ")") == 0 ) {
            edo = 5;
            sintaxisEscribir(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Parentesis de cierre ( ) ) Mostrar en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 5 ) {
        if ( strcasecmp(reco->info.lexema, ";") != 0 ) {
            printf("Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        } else {
            return (reco->der);
        }
    }
}

// TODO: Add Expresión.
struct nodo *sintaxisAsignar(struct nodo *reco, int edo) {
    if ( edo == 1 ) {
        if ( reco->info.tipo == ID ) { //Espera un ID
            edo = 2;
            sintaxisAsignar(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba un Identificador en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 2 ) {
        if ( strcasecmp(reco->info.lexema, "=") == 0 ) {
            edo = 3;
            sintaxisAsignar(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo de Asignacion ( = ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 3 ) {
        //printf("\n %d %d\n", reco->info.tipo,  strcmp(reco->der->info.lexema, "-"));
        if(reco->info.tipo == ID || strcasecmp(reco->info.lexema, "(") == 0 || ((reco->info.tipo == Num || reco->info.tipo == Cadena) && (strcmp(reco->der->info.lexema, "+") == 0 || strcmp(reco->der->info.lexema, "-") == 0 || strcmp(reco->der->info.lexema, "*") == 0 || strcmp(reco->der->info.lexema, "/") == 0 || strcmp(reco->der->info.lexema, "(") == 0))) {
            //struct nodo *recoAux = sintaxisExp(reco, 1);
            edo = 4;
            struct nodo *recoAux = sintaxisExp(reco, 1);
            sintaxisAsignar(recoAux, edo);
            //*reco = *sintaxisExp(reco, 1);
            /*if(strcmp(recoAux->info.lexema, ";") == 0){
                edo = 4;
                sintaxisAsignar(reco, edo);
            }
            else{
                printf("\n %d %s\n", reco->info.tipo, reco->der->info.lexema);
                printf("123 Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
            }*/
        }
        else if((reco->info.tipo == Cadena) || (reco->info.tipo == Num) || (reco->info.tipo == Booleano)){
            //Espera recibir una Cadena en tipo 5 o un numero en tipo 2
            edo = 4;
            sintaxisAsignar(reco->der, edo);
        }
        else {
                printf("Error de sintaxis: Se esperaba una asignación en la linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 4 ) {
        if ( strcasecmp(reco->info.lexema, ";") != 0 ) {
            printf("Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        } else {
            return (reco->der);
        }
    }
}

struct nodo *sintaxisSino(struct nodo *reco, int edo) {
    if ( edo == 1) {
        if ( strcasecmp(reco->info.lexema, "sino" ) == 0 ){
            edo = 2;
            sintaxisSino(reco->der, edo);
        }else {
            printf("Error de sintaxis: Se esperaba la palabra ( sino ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 2 ) {
        if ( strcasecmp(reco->info.lexema, "{" ) == 0 ){
            edo = 3;
            sintaxisSino(reco->der, edo);
        }else {
            printf("Error de sintaxis: Se esperaba el simbolo Llave de apertura ( { ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 3 ) {
        //Espacio para cualquier tipo de acción
        if ( strcasecmp(reco->info.lexema, "si" ) == 0 ) {
            edo = 3;
            struct nodo *recoAux = sintaxisIf(reco, 1);
            sintaxisSino(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "Leer" ) == 0 ) {
            edo = 3;
            struct nodo *recoAux = sintaxisLeer(reco, 1);
            sintaxisSino(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "Mostrar" ) == 0 ) {
            edo = 3;
            struct nodo *recoAux = sintaxisEscribir(reco, 1);
            sintaxisSino(recoAux, edo);
        }else if ( reco->info.tipo == ID ) { //Recibe un ID
            edo = 3;
            struct nodo *recoAux = sintaxisAsignar(reco, 1);
            sintaxisSino(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "mientras" ) == 0 ) {
            edo = 3;
            struct nodo *recoAux = sintaxisMientras(reco, 1);
            sintaxisSino(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "para" ) == 0 ) {
            edo = 3;
            struct nodo *recoAux = sintaxisPara(reco, 1);
            sintaxisSino(recoAux, edo);
        }else {  
            edo = 4;
            sintaxisSino(reco, edo);
        }

    } else if ( edo == 4) {
        if ( strcasecmp(reco->info.lexema, "}" ) == 0 ){
            return (reco->der);
        }else {
            printf("Error de sintaxis: Se esperaba el simbolo Llave de cierre ( } ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    }
}

struct nodo *sintaxisIf(struct nodo *reco, int edo){
    //printf(reco->info.lexema);
    if ( edo == 1 ) {
        if ( strcasecmp(reco->info.lexema, "si" ) == 0 ) {
            edo = 2;
            sintaxisIf(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba la palabra ( si ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 2 ) {
        if ( strcasecmp(reco->info.lexema, "(" ) == 0 ) {
            edo = 3;
            sintaxisIf(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Parentesis de apertura ( ( ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 3 ) {
        //Espacio para expresion verdadera o falsa
        if ( (strcasecmp(reco->info.lexema, "verdadero" ) == 0) ||  (strcasecmp(reco->info.lexema, "falso" ) == 0) ){
            edo = 4;
            sintaxisIf(reco->der, edo);
        } else {
            printf("Se esperaba un valor Verdadero o Falso en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }

    } else if ( edo == 4 ) {
        if ( strcasecmp(reco->info.lexema, ")" ) == 0 ) {
            edo = 5;
            sintaxisIf(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Parentesis de cierre ( ) ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 5 ) {
        if ( strcasecmp(reco->info.lexema, "{" ) == 0 ) {
            edo = 6;
            sintaxisIf(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Llave de apertura ( { ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 6 ) {
        //Espacio para cualquier tipo de accion

        if ( strcasecmp(reco->info.lexema, "si" ) == 0 ) {
            edo = 6;
            struct nodo *recoAux = sintaxisIf(reco, 1);
            sintaxisIf(recoAux, edo);						 
        } else if ( strcasecmp(reco->info.lexema, "Leer" ) == 0 ) {
            edo = 6;
            struct nodo *recoAux = sintaxisLeer(reco, 1);
            sintaxisIf(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "Mostrar" ) == 0 ) {
            edo = 6;
            struct nodo *recoAux = sintaxisEscribir(reco, 1);
            sintaxisIf(recoAux, edo);
        }else if ( reco->info.tipo == ID ) { //Recibe un ID
            edo = 6;
            struct nodo *recoAux = sintaxisAsignar(reco, 1);
            sintaxisIf(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "mientras" ) == 0 ){
            edo = 6;
            struct nodo *recoAux = sintaxisMientras(reco, 1);
            sintaxisIf(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "para" ) == 0 ) {
            edo = 6;
            struct nodo *recoAux = sintaxisPara(reco, 1);
            sintaxisIf(recoAux, edo);
        }else { 
            edo = 7;
            sintaxisIf(reco, edo);
        }
    } else if ( edo == 7 ) {
        //printf(reco->info.lexema);
        if ( (strcasecmp(reco->info.lexema, "}" ) == 0) && (strcasecmp(reco->der->info.lexema, "sino" ) == 0) ) {
            edo = 8;
            struct nodo *recoAux = sintaxisSino(reco->der, 1);
            sintaxisIf(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "}" ) == 0 ){
            edo = 8;
            sintaxisIf(reco->der, edo);
        }else {
            printf("Error de sintaxis: Se esperaba el simbolo Llave de cierre ( } ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);																																	   
        }		 
    } else if ( edo == 8 ) {							 
        if ( strcasecmp(reco->info.lexema, ";") != 0 ) {
            printf("Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        } else {
            return (reco->der);
        }
    }
}

struct nodo *sintaxisMientras(struct nodo *reco, int edo) {
    if ( edo == 1 ) {
        if ( strcasecmp(reco->info.lexema, "mientras") == 0 ) {
            edo = 2;
            sintaxisMientras(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba la palabra ( mientras ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 2 ) {
        if ( strcasecmp(reco->info.lexema, "(") == 0 ) {
            edo = 3;
            sintaxisMientras(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Parentesis de apertura ( ( ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 3 ) {
        if ( (strcasecmp(reco->info.lexema, "verdadero" ) == 0) ||  (strcasecmp(reco->info.lexema, "falso" ) == 0) ){
            edo = 4;
            sintaxisIf(reco->der, edo);
        } else {
            printf("Se esperaba un valor Verdadero o Falso en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 4 ) {
        if ( strcasecmp(reco->info.lexema, ")") == 0 ) {
            edo = 5;
            sintaxisMientras(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Parentesis de cierre ( ) ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 5 ) {
        if ( strcasecmp(reco->info.lexema, "{") == 0 ) {
            edo = 6;
            sintaxisMientras(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Llave de apertura ( { ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 6 ) {
        //Espacio para cualquier tipo de acción
        if ( strcasecmp(reco->info.lexema, "mientras" ) == 0 ) {
            edo = 6;
            struct nodo *recoAux = sintaxisMientras(reco, 1);
            sintaxisMientras(recoAux, edo);
        }else if ( strcasecmp(reco->info.lexema, "si" ) == 0 ) {
            edo = 6;
            struct nodo *recoAux = sintaxisIf(reco, 1);
            sintaxisMientras(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "Leer" ) == 0 ) {
            edo = 6;
            struct nodo *recoAux = sintaxisLeer(reco, 1);
            sintaxisMientras(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "Mostrar" ) == 0 ) {
            edo = 6;
            struct nodo *recoAux = sintaxisEscribir(reco, 1);
            sintaxisMientras(recoAux, edo);
        } else if ( reco->info.tipo == ID ) { //Recibe un ID
            edo = 6;
            struct nodo *recoAux = sintaxisAsignar(reco, 1);
            sintaxisMientras(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "para" ) == 0 ){
            edo = 6;
            struct nodo *recoAux = sintaxisPara(reco, 1);
            sintaxisMientras(recoAux, edo);
        } else {
            edo = 7;
            sintaxisMientras(reco, edo);
        }

    } else if ( edo == 7 ) {
        if ( strcasecmp(reco->info.lexema, "}") == 0 ) {
            edo = 8;
            sintaxisMientras(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Llave de cierre ( } ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 8 ) {
        if ( strcasecmp(reco->info.lexema, ";") != 0 ) {
            printf("Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        } else {
            return (reco->der);
        }
    }
}

struct nodo *sintaxisPara(struct nodo *reco, int edo){
    if ( edo == 1 ) {
        if ( strcasecmp(reco->info.lexema, "para" ) == 0 ) {
            edo = 2;
            sintaxisPara(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba la palabra ( para ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 2 ) {
        if (strcasecmp(reco->info.lexema, "(") == 0) {
            edo = 3;
            sintaxisPara(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Parentesis de apertura ( ( ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 3 ) {
        if ( reco->info.tipo == ID ) { //Detecta un Identificador
            edo = 4;
            sintaxisPara(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba un Identificador en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 4 ) {
        if ( strcasecmp(reco->info.lexema, ";") == 0 ) {
            edo = 5;
            sintaxisPara(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 5 ){
        if ( (strcasecmp(reco->info.lexema, "verdadero" ) == 0) ||  (strcasecmp(reco->info.lexema, "falso" ) == 0) ) {
            edo = 6;
            sintaxisPara(reco->der, edo);
        } else {
            printf("Se esperaba un valor Verdadero o Falso en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 6 ) {
        if ( strcasecmp(reco->info.lexema, ";") == 0 ) {
            edo = 7;
            sintaxisPara(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 7 ) {
        if ( reco->info.tipo == Num ) {
            edo = 8;
            sintaxisPara(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba un Numero en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 8 ) {
        if ( strcasecmp(reco->info.lexema, ")") == 0 ) {
            edo = 9;
            sintaxisPara(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Parentesis de cierre ( ) ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 9 ) {
        if ( strcasecmp(reco->info.lexema, "{") == 0 ) {
            edo = 10;
            sintaxisPara(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Llave de apertura ( { ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 10 ) {
        //Espacio para cualquier tipo de accion

        if ( strcasecmp(reco->info.lexema, "para" ) == 0 ) {
            edo = 10;
            struct nodo *recoAux = sintaxisPara(reco, 1);
            sintaxisPara(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "mientras" ) == 0 ) {
            edo = 10;
            struct nodo *recoAux = sintaxisMientras(reco, 1);
            sintaxisPara(recoAux, edo);
        }else if ( strcasecmp(reco->info.lexema, "si" ) == 0 ) {
            edo = 10;
            struct nodo *recoAux = sintaxisIf(reco, 1);
            sintaxisPara(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "Leer" ) == 0 ) {
            edo = 10;
            struct nodo *recoAux = sintaxisLeer(reco, 1);
            sintaxisPara(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "Mostrar" ) == 0 ) {
            edo = 10;
            struct nodo *recoAux = sintaxisEscribir(reco, 1);
            sintaxisPara(recoAux, edo);
        }else if ( reco->info.tipo == ID ) { //Recibe un ID
            edo = 10;
            struct nodo *recoAux = sintaxisAsignar(reco, 1);
            sintaxisPara(recoAux, edo);
        } else {
            edo = 11;
            sintaxisPara(reco, edo);
        }

    } else if ( edo == 11 ) {
        if ( strcasecmp(reco->info.lexema, "}") == 0 ) {
            edo = 12;
            sintaxisPara(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Llave de cierre ( } ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 12 ) {
        if ( strcasecmp(reco->info.lexema, ";") != 0 ) {
            printf("Error de sintaxis: Se esperaba el simbolo Punto y coma ( ; ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        } else {
            return (reco->der);
        }
    }
}

void sintaxisPrograma(struct nodo *reco, int edo){
    if ( edo == 1 ) {
        if ( strcasecmp(reco->info.lexema, "declaracion") == 0 )  {
            edo = 2;
            sintaxisPrograma(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba la palabra (declaracion) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 2 ) {
        if ( strcasecmp(reco->info.nombre, "CorcheteIzq") == 0){
            edo = 3;
            sintaxisPrograma(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Corchete de apertura ( [ ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 3 ){
        if ( reco->info.tipo == TipoDato ){ //Detecta un tipo de dato
            edo = 3;
            //printf(recoAux->info.lexema);
            //printf("\n");
            struct nodo *recoAux = sintaxisVariable(reco, 1);
            sintaxisPrograma(recoAux, edo);

        } else if ( strcasecmp(reco->info.lexema, "constante" ) == 0) {
            edo = 3;
            struct nodo *recoAux = sintaxisConstante(reco, 1);
            sintaxisPrograma(recoAux, edo);
        } else if ( strcasecmp(reco->info.nombre, "CorcheteDer") == 0 ){
            edo = 4;
            sintaxisPrograma(reco, edo);
        } else if ( ( reco->info.tipo != 4 ) || ( strcasecmp(reco->info.lexema, "constante" ) != 0) ){
            printf("Error de sintaxis: Se esperaba un Tipo de Dato o la palabra (constante) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 4 ) {
        //printf(reco->info.lexema);
        if ( strcasecmp(reco->info.nombre, "CorcheteDer") == 0) {
            edo = 5;
            sintaxisPrograma(reco->der, edo);
        } else {
            //printf("Estado 4 \n");
            printf("Error de sintaxis: Se esperaba el simbolo Corchete de cierre ( ] ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 5 ){
        //printf(reco->info.lexema);
        if ( strcasecmp(reco->info.lexema, "principal") == 0){
            edo = 6;
            sintaxisPrograma(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba la palabra (principal) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 6) {
        if(reco->der == NULL){
            edo = 8;
            sintaxisPrograma(NULL, edo);
        }
        else if ( strcasecmp(reco->info.nombre, "CorcheteIzq") == 0){
            edo = 7;
            sintaxisPrograma(reco->der, edo);
        } else {
            printf("Error de sintaxis: Se esperaba el simbolo Corchete de apertura ( [ ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
        }
    } else if ( edo == 7) { //Cuerpo del programa
        if ( strcasecmp(reco->info.lexema, "Leer") == 0 ) {
            edo = 7;
            struct nodo *recoAux = sintaxisLeer(reco, 1);
            //printf(recoAux->info.lexema);
            if(recoAux == NULL){
                edo = 8;
                sintaxisPrograma(NULL, edo);
            }
            else
                sintaxisPrograma(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "Mostrar") == 0 ) {
            edo = 7;
            struct nodo *recoAux = sintaxisEscribir(reco, 1);
            if(recoAux == NULL){
                edo = 8;
                sintaxisPrograma(NULL, edo);
            }
            else
                sintaxisPrograma(recoAux, edo);
        } else if ( reco->info.tipo == ID){ //Espera recibir un identificador
            edo = 7;
            struct nodo *recoAux = sintaxisAsignar(reco, 1);
            if(recoAux == NULL){
                edo = 8;
                sintaxisPrograma(NULL, edo);
            }
            else
                sintaxisPrograma(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "si") == 0 ){
            edo = 7;
            struct nodo *recoAux = sintaxisIf(reco, 1);
            if(recoAux == NULL){
                edo = 8;
                sintaxisPrograma(NULL, edo);
            }
            else
                sintaxisPrograma(recoAux, edo);
        }else if ( strcasecmp(reco->info.lexema, "mientras") == 0 ){
            edo = 7;
            struct nodo *recoAux = sintaxisMientras(reco, 1);
            if(recoAux == NULL){
                edo = 8;
                sintaxisPrograma(NULL, edo);
            }
            else
                sintaxisPrograma(recoAux, edo);
        } else if ( strcasecmp(reco->info.lexema, "para") == 0 ){
            edo = 7;
            struct nodo *recoAux = sintaxisPara(reco, 1);
            if(recoAux == NULL){
                edo = 8;
                sintaxisPrograma(NULL, edo);
            }
            else
                sintaxisPrograma(recoAux, edo);
        }else if(reco != NULL) {
            edo = 8;
            sintaxisPrograma(reco, edo);
        }
    } else {
        //printf("Estado 8\n");
        //printf(reco->info.lexema);
        //if ( strcasecmp(reco->info.nombre, "CorcheteDer") != 0 ){
        if ( reco == NULL ){
            //printf("Error de sintaxis: Se esperaba el simbolo Corchete de cierre ( ] ) en linea %d columna %d", reco->info.numLin, reco->info.numCol);
            printf("Error de sintaxis: Se esperaba el simbolo Corchete de cierre ( ] ) en la ultima linea");
        } else {
            printf("Analisis sintactico correcto, FELICIDADEEEES");
        }
    }
}
