//
// Created by bangho on 08/09/17.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "buscarArchivo.c"

int ejecutar (char *path, char *args[], int flag, char* RedirectStdin , char* RedirectStdout);

void findAndExecute(char** args,int concurrentFlag,char* RedirectStdin , char* RedirectStdout){
    char p[1024];
    if (buscarArchivo(args[0], p) == 0) {

        args[0]=p;
        ejecutar(p, args,concurrentFlag,RedirectStdin,RedirectStdout);

    } else {
        printf("\nno existe\n");
    }
}
int ejecutar (char *path, char *args[], int flag,char* RedirectStdin , char* RedirectStdout){
    int pid;
    int status;
    //strcpy(args[0],path);
    pid = vfork();
    if (pid<0) {
        printf("Fork error \n");
        exit(1);
    }
    if(pid == 0){ /* Child executes here */
        if(RedirectStdin!=NULL){
            int fdin=open(RedirectStdin,O_RDONLY,0600);
            dup2(fdin,STDIN_FILENO);
        }
        if(RedirectStdout!=NULL){
            int fdout=open(RedirectStdout,O_WRONLY | O_CREAT,0600);
            dup2(fdout,STDOUT_FILENO);

        }
        execvp(path, args);
        printf("Exec error \n");
        exit(1);
    } else {    /* Parent executes here */
        if(!flag)
            wait(&status);
    }
    //printf("Hello there! \n");
    return 0;

}