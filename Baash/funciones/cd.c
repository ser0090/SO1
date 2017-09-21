//
// Created by tincho on 07/09/17.
//

#include <unistd.h>//para hostname y user name
#include <stdio.h>
#define BUFSIZE 1024

char *bash_cdHome(char *PATH);
/**
 * cambia de directorio segun la variable PATH
 * @param PATH el camino para cambiar de direccion
 * @return 1 si se pudo cambiar de directorio
 * @perror si el camino no es valido
 */
int bash_cd(char **PATH)
{
    if (PATH[0] == NULL) {
        //si no hay path habre por defecto /home/user
        PATH[0]=getpwuid(geteuid ())->pw_dir;
    }
    else if(strstr( PATH[0],"~/" )!='\0') {
            PATH[0]=bash_cdHome(strstr( PATH[0],"~/" )+1);
        }

    if (chdir(PATH[0]) != 0) {
            perror("bash");
    }
    return 1;
}

/**
 * recibe un camino y lo concatena con /home/user/
 * @param PATH el camino a concatenar
 * @return buffer camino concatenado con /home/user/path
 */
char *bash_cdHome(char *PATH){
    char *buffer = malloc(sizeof(char) * BUFSIZE);
    strcpy(buffer,getpwuid(geteuid ())->pw_dir);//obtengo el /home/userX
    strncat(buffer, PATH, BUFSIZE);
    return buffer;
}
