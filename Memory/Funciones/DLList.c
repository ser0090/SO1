//
// Created by tincho on 06/10/17.
//
#define true 1
#define false 0

typedef struct Nodos{
    Nodo *next;//siguiente nodo
    Nodo *previous;//nodo anterior
    int size;//tamaño del bloque, sin considerar la cabeza
    int free;
}Nodo;

/**
 * libera el nodo, si los nodos adyacentes estan libres, los unifica
 * @param nodo
 * @return
 */
Nodo * blockFree(Nodo* nodo){
    nodo->free=true;
    if(nodo->next->free == true){//si el siguiente bloque esta libre, uno los bloques
        nodo->size+=nodo->next->size + sizeof(Nodo);//recalculo el tamaño del bloque completo.
        nodo->next->next->previous=nodo;//actualiza el puntero a previo del siguiente nodo siguiente
        nodo->next=nodo->next->next;//actualizo el valor de next del nodo actual
    }
    if(nodo->previous->free == true){
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

}
/**
 * busca o genera un nuevo bloque y retorna el puntero al bloque
 * @param size, tamaño de bloque.
 * @return puntero al bloque
 */
Nodo* blockAlloc(int size,Nodo* comienzo){
    Nodo* libre=firstFit(size,comienzo);//busca un bloque libre
    if(libre->next==NULL){
        //ampliar el break y generar nuevo nodo
    }
    libre->free=false;
    return libre;
}

Nodo* crearNodo()