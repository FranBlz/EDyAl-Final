#ifndef __BSTREE_H__
#define __BSTREE_H__
#include <stdlib.h>

typedef void (*FuncionVisitante) (int dato);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BSTNodo {
    int dato;
    struct _BSTNodo *left;
    struct _BSTNodo *right;
}BSTNodo;

typedef BSTNodo *BSTree;

BSTree bstree_crear();

BSTree bstree_insertar(BSTree arbol, int dato);

BSTree bstree_eliminar(BSTree arbol, int dato);

BSTree bstree_minimo(BSTree arbol);

int bstree_contiene(BSTree arbol, int dato);

int bstree_nelementos(BSTree arbol);

void bstree_recorrer(BSTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit);

#endif /* __BSTREE_H__ */