//
// Created by bangho on 08/09/17.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int ejecutar (char *path, char *args[], int flag);

void findAndExecute(char** args,int concurrentFlag){
    char p[1024];
    if (buscarArchivo(args[0], p) == 0) {

        args[0]=p;
        ejecutar(p, args,concurrentFlag);

    } else {
        printf("\nno existe\n");
    }
}
int ejecutar (char *path, char *args[], int flag){
    int pid;
    int status;
    //strcpy(args[0],path);
    pid = vfork();
    if (pid<0) {
        printf("Fork error \n");
        exit(1);
    }
    if(pid == 0){ /* Child executes here */

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