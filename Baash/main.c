#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include "funciones/cd.c"
#include "funciones/buscarArchivo.c"
#include "funciones/execute.c"
#define BUFSIZE 1024
#define SEG_DELIMITADOR " \n"
int main() {

    char input[BUFSIZE];
    //char *comando;
    char *args[20];
    char* p= malloc(sizeof(char) * BUFSIZE);

    char hostname[BUFSIZE];// buffer para el  Pc name


    gethostname(hostname, BUFSIZE-1);//get PC name

    while(1) {
        printf("%s@%s %s $ ", getpwuid(geteuid())->pw_name, hostname, getcwd(NULL, 0));

        fgets(input, BUFSIZE, stdin);// pide el comando. se hace con fgets xq permite leer la linea completa
        input[strlen(input) - 1] = NULL;//como el string se toma desde archivo, se debe borrar el ultimo caracter(\n)
        // xq trae problemas para la lectura de los argumentos
        args[0] = strtok(input, SEG_DELIMITADOR);//toma el comando. primer cadena antes de un espacio.
        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        } // si el comando es exit, sale del Baash
        /*else if(strcmp(comando, "help") == 0){
            printf("Tipee un comando y los argumentos.\n");
            printf("comados existentes:\n");
            printf(" cd\n help\n");
        }*/
        args[1] = strtok(NULL, " "); //como el parametro es NULL, toma la ultma cadena q se le paso y sigue avanzando
        for (int i = 2; args[i] != NULL && i < 20; i++) {
            args[i] = strtok(NULL, " ");
        } // obtengo todos los argumentos

        if (strcmp(args[0], "cd") == 0) {//ejecuto el comando interno cd
            bash_cd(&args[1]);
            continue;
        }
        //char* p[1000];
        if(buscarArchivo(args[0],p)==0){
            //printf("\n%s\n",p);
            ejecutar(p,args);
            //free(p);
        }
        else{
            printf("\nno existe\n");
        }
    }


    return 0;
}