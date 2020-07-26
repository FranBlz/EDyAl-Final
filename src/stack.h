#ifndef __STACK_H__
#define __STACK_H__
#include "itree.h"

typedef struct _SNodo {
  ITree dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *Pila;

Pila pila_crear();

int pila_es_vacia(Pila stack);

ITree pila_ultimo(Pila stack);

Pila pila_apilar(Pila stack, ITree data);

Pila pila_desapilar(Pila stack);

void pila_destruir(Pila stack);

#endif
