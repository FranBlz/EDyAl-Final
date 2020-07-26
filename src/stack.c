#include "stack.h"
#include "itree.h"
#include <stdlib.h>

Pila pila_crear() {
  return NULL;
}

int pila_es_vacia(Pila stack) {
  return (stack == NULL);
}

ITree pila_ultimo(Pila stack) {
  return stack->dato;
}

Pila pila_apilar(Pila stack, ITree data) {
  Pila newNode = malloc(sizeof(SNodo));
  newNode->dato = data;
  newNode->sig = stack;

  return newNode;
}

Pila pila_desapilar(Pila stack) {
  if (!pila_es_vacia(stack)) {
    Pila temp = stack->sig;
    free(stack);

    return temp;
  }

  return NULL;
}

void pila_destruir(Pila stack) {
  Pila temp = stack;
  for (; stack != NULL; stack = stack->sig) {
    temp = stack;
    free(temp);
  }
}
