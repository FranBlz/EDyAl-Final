#ifndef __STACK_H__
#define __STACK_H__
#include "itree.h"

typedef struct _SNodo {
  ITree dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *Pila;

/* 
* Inicia una pila vacía
*/
Pila pila_crear();

/* 
* Devuelve v o f si la lista está vacía
*/
int pila_es_vacia(Pila stack);

/* 
* Devuelve el último elemento de la pila
*/
ITree pila_ultimo(Pila stack);

/* 
* Añade un nuevo elemento a la pila
*/
Pila pila_apilar(Pila stack, ITree data);

/* 
* Elimina el último elemento de la pila
*/
Pila pila_desapilar(Pila stack);

/* 
* Elimina toda la pila
*/
void pila_destruir(Pila stack);

#endif
