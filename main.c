#include <sys/wait.h>
#include <unistd.h>//para hostname y user name
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>  //para obeter el current directory

#define SEG_BUFSIZE 64
#define SEG_DELIMITADOR " \n"   //busca espacio, y saldo de liena
#define BUFSIZE 1024

int bash_cd(char **args);
int bashComands(char **args);
char * read_line(void);
char ** split_line(char *line);

/**
   @brief Main .
   @return status code
 */
int main(void) {

    char *line;
    char **args;
    int status;
    //agregado
    register struct passwd *pw; //obtener usuario
    char hostname[BUFSIZE];// buffer para el  Pc name
    char cwd[BUFSIZE];// directorio actual

    gethostname(hostname, BUFSIZE-1);//get PC name
    pw = getpwuid(geteuid ()); //con la funcion get id obnet el nombre
    do {
        printf("%s@%s %s $ ",pw->pw_name,hostname,getcwd(cwd, sizeof(cwd)));

        line = read_line();
        args = split_line(line);//args es un arreglo de segentos de la cadena principal
        status = bashComands(args);//

        free(line);//libero memoria alloc
        free(args);
    }while (status);

    return 0;
}

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char * read_line(void)
{
    int bufsize = BUFSIZE;
    int posicion = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    char c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character
        c = getchar();//me devuelve caracter

        if (c == EOF) {
            exit(EXIT_SUCCESS);
        } else if (c == '\n') {//finaliza la linea
            buffer[posicion] = '\0';
            return buffer;
        } else {
            buffer[posicion] = c;
        }
        posicion++;

        // If we have exceeded the buffer, reallocate.
        if (posicion >= bufsize) {
            bufsize += BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **split_line(char *line)
{
    int bufsize = SEG_BUFSIZE, posicion = 0;
    char **tokens = malloc(bufsize * sizeof(char*));//alloc memoria para
    //para definir un arreglo de strings
    char *token, **tokens_backup;

    if (!tokens) {
        fprintf(stderr, "error de allocacion \n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SEG_DELIMITADOR);//rompe un cadena en segmentos
    //de acuerdo al delimitador , si no lo encuentra retorna null
    // cuando termina de encontrar a todos retorna null
    // cada llamada retorna el segmento siguiente
    while (token != NULL) {
        tokens[posicion] = token;// guardo la primer cadena
        posicion++;

        if (posicion >= bufsize) {
            bufsize += SEG_BUFSIZE;
            tokens_backup = tokens;//se realiza un backup en caso que falte memoria
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                free(tokens_backup);//libero la memoria que contien el back up
                fprintf(stderr, "error de allocation \n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SEG_DELIMITADOR);//pido el segmnto cadena siguiente separado por el delim
    }
    tokens[posicion] = NULL;  // ultimo dato guardo un null
    return tokens;
}


/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int bashComands(char **args) {

    if (args[0] == NULL) {
        // si se recibe un comando vacio
        return 1;
    }

    if (strcmp(args[0], "cd") == 0){
        return bash_cd(args);
    }
    else if(strcmp(args[0], "help") == 0){
        printf("Tipee un comando y los argumentos.\n");
        printf("comados existentes:\n");
        printf(" cd\n help\n");
        return 1;
    }
    else if(strcmp(args[0],"exit") == 0){
        //exit(EXIT_FAILURE);
        return 0;
    }
    else{
        fprintf(stderr, "No such file or drirctory\n");
        //perror("No such file or drirctory");
        return -1;
    }

}

/**
   @brief construccion comando: change directory.
   @param PATH lista de argumentos.  PATH[0] is "cd".  PATH[1] is the directory.
   @return siempre returns 1
 */
int bash_cd(char **PATH)
{
    if (PATH[1] == NULL) {
        fprintf(stderr, "expected argument to \"cd\"\n");
    } else {
        if (chdir(PATH[1]) != 0) {
            perror("bash");
        }
    }
    return 1;
}

//si el comando emocional ./ compio el path dondes estoy y concateno
//si ../ borro ultimo y concateno
//si ~/ /home y concateno.