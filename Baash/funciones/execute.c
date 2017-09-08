//
// Created by bangho on 08/09/17.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int ejecutar (char *path, char *args[]){
    int pid;
    int status;
    strcpy(args[0],path);
    pid = vfork();
    if (pid<0) {
        printf("Fork error \n");
        exit(1);
    }
    if(pid == 0){ /* Child executes here */

        execvp(path, args);
        printf("Exec error \n");
        exit(1);
    } else 	/* Parent executes here */
        wait(&status);
    //printf("Hello there! \n");
    return 0;


}