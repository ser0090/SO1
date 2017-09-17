#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

#include "funciones/cd.c"
#include "funciones/execute.c"
#include "funciones/ComandosInternos.c"
#include "funciones/findRedirectCommand.c"
#define BUFSIZE 1024
#define SEG_DELIMITADOR " \n"

//Ver la funcion dup2() para redirigir la stdin y stdout
//usar los flags WarningON, y cppcheck




int main() {

    char input[BUFSIZE];

    char *args[20];
   // char* p= malloc(sizeof(char) * BUFSIZE);

    char hostname[BUFSIZE];// buffer para el  Pc name


    gethostname(hostname, BUFSIZE-1);//get PC name

    while(1) {
        printf("%s@%s %s $ ", getpwuid(geteuid())->pw_name, hostname, getcwd(NULL, 0));

        fgets(input, BUFSIZE, stdin);// pide el comando. se hace con fgets xq permite leer la linea completa
        input[strlen(input) - 1] = NULL;//como el string se toma desde archivo, se debe borrar el ultimo caracter(\n)
                                        // xq trae problemas para la lectura de los argumentos

        char *comands[]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};//comandos divididos por ampersand

        int concurrentFlag=1;//indica si los procesos se ejecutaran concurrentemente;
        comands[0]=strtok_r(input, "&", comands+1);
        if(comands[1]==NULL || *comands[1]=='\0'){concurrentFlag=0;}
        int index=0;

        do {
            char* inFile=NULL;
            char* outFile=NULL;
            findRedirectCommand(comands[index],&inFile,&outFile);

            args[0] = strtok(comands[index], SEG_DELIMITADOR);//toma el comando. primer cadena antes de un espacio.
            args[1] = strtok(NULL," "); //como el parametro es NULL, toma la ultma cadena q se le paso y sigue avanzando
            for (int i = 2; args[i] != NULL && i < 20; i++) {// obtengo todos los argumentos
                args[i] = strtok(NULL, " ");
            }

            if(comandosInternos(args)!=0) {

                findAndExecute(args, concurrentFlag,inFile,outFile);
            }
            index++;
        }while(comands[index]!=NULL && *comands[index]!='\0');
    }


    return 0;
}