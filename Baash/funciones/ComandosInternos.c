//
// Created by bangho on 16/09/17.
//
/**
 * ejecuta los comandos cd y exit
 * @param args contiene el comando y los argumentos asociados
 * @return 0 si el comando no existe
 * @return 1 si el comando es exit
 * @return 2 si el comando es cd
 */
int comandosInternos(char** args) {

    if (strcmp(args[0], "exit") == 0) {
        return 1;
    }

    if (strcmp(args[0], "cd") == 0) {//ejecuto el comando interno cd
        bash_cd(&args[1]);
        return 2;
    }
    return 0;
}