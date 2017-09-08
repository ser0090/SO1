#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include "funciones/cd.c"
#include "funciones/buscarArchivo.c"
#define BUFSIZE 1024

int main() {

    char input[200];
    char *comando;
    char *args[20];

    char hostname[BUFSIZE];// buffer para el  Pc name


    gethostname(hostname, BUFSIZE-1);//get PC name

    while(1) {
        printf("%s@%s %s $ ", getpwuid(geteuid())->pw_name, hostname, getcwd(NULL, 0));

        fgets(input, 200, stdin);// pide el comando. se hace con fgets xq permite leer la linea completa
        input[strlen(input) - 1] = NULL;//como el string se toma desde archivo, se debe borrar el ultimo caracter(\n)
        // xq trae problemas para la lectura de los argumentos
        comando = strtok(input, " ");//toma el comando. primer cadena antes de un espacio.
        if (strcmp(comando, "exit") == 0) { exit(0); } // si el comando es exit, sale del Baash

        args[0] = strtok(NULL, " "); //como el parametro es NULL, toma la ultma cadena q se le paso y sigue avanzando
        for (int i = 1; args[i] != NULL && i < 20; i++) { args[i] = strtok(NULL, " "); } // obtengo todos los argumentos

        if (strcmp(comando, "cd") == 0) {//ejecuto el comando interno cd
            bash_cd(&args[0]);
            continue;
        }

        char* p[1000];
        if(buscarArchivo(comando,p)==0){printf("\n%s\n",p);}
        else{printf("\nno existe\n");}

    }


    return 0;
}