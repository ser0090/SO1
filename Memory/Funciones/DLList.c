//
// Created by tincho on 06/10/17.
//
#include <unistd.h>
#define true 1
#define false 0

typedef struct Nodos Nodo;
struct Nodos{
    Nodo *next;//siguiente nodo
    Nodo *previous;//nodo anterior
    int size;//tamaño del bloque, sin considerar la cabeza
    int free;//flag de libre
};

/**
 * libera el nodo, si los nodos adyacentes estan libres, los unifica. si el nodo siguiente es el final,reduce el brk
 * y configura el nodo actual como el final.
 * Metodo RECURSIVO
 * @param nodo a liberar
 * @return
 */
void blockFree(Nodo* nodo){
    nodo->free=true;
    if(nodo->previous==NULL){ // indica que es el primer nodo
        if(nodo->next!=NULL) {//indica que el primer nodo NO es unico, si el primer nodo es unico, no cambia nada, solo indica libre
            if (nodo->next->free == true) {
                nodo->size += nodo->next->size + sizeof(Nodo *);
                nodo->next = nodo->next->next;
                nodo->next->previous = nodo;

            }

        }
        return;
    }else if(nodo->next!=NULL) {//indica si es un nodo central
            if(nodo->next->free==true) {
                nodo->size += nodo->next->size + sizeof(Nodo *);
                nodo->next = nodo->next->next;
                nodo->next->previous = nodo;
            }
    } // no es necesario saber si el nodo es final en este punto, eso se resuelve mas adelante

    Nodo* previous = nodo->previous; //necesito almacenar este valor para reducir el brk

    if(nodo->next==NULL){// se vueleve a consultar esto ya que si el nodo era el ante ultimo y se fusiono
                        // con el ultimo se habra convertido ahora en el ultimo
        brk(nodo);//muevo el brk hasta el inicio del nodo, eliminando su contenido y el nodo
        previous->next=NULL;// el nodo previo sera ahora el ultimo

    }

    if(previous->free == true){// si el nodo anterior esta libre.
           blockFree(nodo->previous); // se llama esta funcion recursivamente provocando que la fusion sea siempre con nodos siguientes
    }

    }




/**
 * busca el primer bloque con tamaño mayor o igual al tamaño del parametro
 * @param bytes , tamaño del bloque
 * @param comienzo , nodo de inicio de busqueda
 * @return puntero al nodo encontrado. si llega al final de la lista(next->NULL)retornara ese nodo.
 */
void * firstFit(int bytes, Nodo* comienzo){
    while(comienzo->next!=NULL){
        if(comienzo->free==true && (comienzo->size >= bytes)){
            break;
        }
        comienzo = comienzo->next;


    }
    return comienzo;

}

/**
 * permite crear un bloque al final de la lista
 * @param final nodo final de la lista
 * @return puntero al nodo creado
 */
Nodo* crearBloque(int size){
    Nodo * nuevo=sbrk(size + sizeof(Nodo));
    if(nuevo==(void *)-1){return NULL;}

    nuevo->free=true;
    nuevo->next=NULL;
    nuevo->size=size;
    return nuevo;
}

void split(Nodo* nodo,int size){

    Nodo* nuevo = (void*)nodo+size+ sizeof(Nodo);
    nuevo->size = nodo->size - size - sizeof(Nodo);
    nuevo->next=nodo->next;
    nuevo->previous = nodo;

    nuevo->next->previous=nuevo;

    nodo->size= size;
    nodo->next=nuevo;

}

/**
 * busca o genera un nuevo bloque y retorna el puntero al bloque
 * @param size, tamaño de bloque.
 * @return puntero al bloque
 */
Nodo* blockAlloc(int size,Nodo* comienzo){
    Nodo* libre=firstFit(size,comienzo);//busca un bloque libre

    if(libre->next==NULL && (libre->free==false || libre->size >= size)){// si el nodo retornado es el ultimo de la lista,
        Nodo* nuevo = crearBloque(size);                                      //y no cumple con el tamaño o no esta libre crea un nuevo nodo
        if(nuevo==NULL){return NULL;}
        nuevo->previous=libre;
        libre->next=nuevo;
        libre=nuevo;
    }else if(libre->size > (size+ sizeof(Nodo))){ // si el tamaño del nodo es suficintemente grande como para un split lo hace.
        split(libre,size);
    }

    libre->free=false;
    return libre;
}
