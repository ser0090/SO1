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
Nodo * blockFree(Nodo* nodo){
    nodo->free=true;
    if(nodo->next->free == true){//si el siguiente bloque esta libre, uno los bloques
        if(nodo->next->next==NULL){
            sbrk((-1 )*(nodo->size + sizeof(Nodo)));
            nodo->free=true;
            nodo->next=NULL;
            nodo->size=0;
        }else {
            nodo->size += nodo->next->size + sizeof(Nodo);//recalculo el tamaño del bloque completo.
            nodo->next->next->previous = nodo;//actualiza el puntero a previo del siguiente nodo siguiente
            nodo->next = nodo->next->next;//actualizo el valor de next del nodo actual
        }
    }
    if(nodo->previous!=NULL && nodo->previous->free == true){
        return blockFree(nodo->previous);
    }
    return nodo;
}
/**
 * busca el primer bloque con tamaño mayor o igual al tamaño del parametro
 * @param bytes , tamaño del bloque
 * @param comienzo , nodo de inicio de busqueda
 * @return puntero al nodo encontrado. si llega al final de la lista(next->NULL)retornara ese nodo.
 */
void * firstFit(int bytes, Nodo* comienzo){
    while(comienzo->next!=NULL && comienzo->size < bytes){
        comienzo = comienzo->next;
    }
    return comienzo;

}

/**
 * permite crear un bloque.en principio sera al final de la lista
 * @param final nodo final de la lista
 * @return puntero al nodo creado
 */
Nodo* crearBloque(Nodo* final, int size){
    Nodo * nuevo=sbrk(size + sizeof(Nodo));
    if(nuevo==(void *)-1){return NULL;}
    nuevo =sbrk(0)-sizeof(Nodo);//valor del nuevo nodo

    nuevo->free=true;
    nuevo->next=NULL;
    nuevo->previous=final;
    nuevo->size=0;

    final->next=nuevo;
    final->size=size;
    return final;
}

/**
 * busca o genera un nuevo bloque y retorna el puntero al bloque
 * @param size, tamaño de bloque.
 * @return puntero al bloque
 */
Nodo* blockAlloc(int size,Nodo* comienzo){
    Nodo* libre=firstFit(size,comienzo);//busca un bloque libre
    if(libre->next==NULL){
        libre = crearBloque(libre,size);
        if(libre==NULL){return NULL;}
    }

    libre->free=false;
    return libre;
}
