//
// Created by tincho on 06/10/17.
//
#include "DLList.c"
void* malloc(int size){
    static Nodo* inicio;
    if(inicio==NULL){
        inicio=sbrk(0);
        if(sbrk(sizeof(Nodo))==NULL){return NULL;}
        inicio->free=true;
        inicio->next=NULL;
        inicio->previous=NULL;
        inicio->size=0;
    }

    return blockAlloc(size,inicio)+1;
}

void * free(void* bloque){
    bloque = (Nodo*)bloque -1 ;

    return blockFree(bloque);

}
