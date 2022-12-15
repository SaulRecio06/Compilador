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



int tamArchivo(FILE *f){        // Encuentra el total de caracteres en el archivo moviendo el puntero que lo lee, al final reinicia el puntero a su posici�n original.
    size_t pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);
    fseek(f, pos, SEEK_SET);
    return length;
}



void analizadorLexico(struct nodo *reco){
    sintaxisPrograma(reco, 1);
}


int main(int argc, char *argv[])
{
   if(argc >= 2){                                              // Verifica que el programa se haya ejecutado con un parametro
        char nombreArchivo[strlen(argv[1])];
        strcpy(nombreArchivo, argv[1]);
        printf("\t\t%s:\n", nombreArchivo);

        FILE *archivo;                                          // Abre el archivo mandado en el parametro y lo guarda en strArchivo
        archivo = fopen(nombreArchivo, "r");
        if(archivo == NULL){
            printf("ERROR de apertura del archivo\n");
            fclose(archivo);
        }
        else{
            int sizeArchivo = tamArchivo(archivo);
            printf("Numero de caracteres en el archivo: %d\n", sizeArchivo);
            printf("---------------------------------\n");
            char strArchivo[sizeArchivo];
            fflush(stdin);
            for(int x = 0; x<sizeArchivo-2; x++){
                char c = fgetc(archivo);
                strArchivo[x] = c;
            }
            fclose(archivo);
            strArchivo[sizeArchivo-1] = EOF;
            printf("%s\n", strArchivo);
            printf("---------------------------------\n");
            leerTokens(strArchivo);

            //imprimirLista(raiz);

            analizadorLexico(raiz);
        }
    }
    else{
        printf("Error, archivo vacio.");
    }
    return 0;
}
