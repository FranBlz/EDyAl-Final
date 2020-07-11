#ifndef __AVLTREE_H__
#define __AVLTREE_H__

typedef struct _ANode {
  int dato;
  struct _ANode *left;
  struct _ANode *right;
} ANode;

typedef ANode *AVLTree;

/**
 * Crea y devuelve un arbol de intervalos
**/
AVLTree avltree_crear();

/**
 * Destruye todos los elementos del arbol de intervalos
**/
void avltree_destruir(AVLTree arbol);

/**
 * Devuelve la altura del arbol
**/
int avltree_altura(AVLTree arbol);

/**
 * Devuelve el factor por el cual se decidira si el arbol esta balanceado
**/
int avltree_balance_factor(AVLTree arbol);

/**
 * Inserta el intervalo indicado al arbol
**/
AVLTree avltree_insertar(AVLTree arbol, int dato);

/**
 * Elimina (de existir) el intervalo indicado del arbol
**/
AVLTree avltree_eliminar(AVLTree arbol, int dato);

/**
 * Devuelve (de existir) el intervalo del arbol con el cual el
 * intervalo dado se interseca
**/
int avltree_buscar(AVLTree arbol, int dato);

/**
 * Recorre el arbol por altura
**/
void avltree_recorrer_dfs(AVLTree arbol);

#endif
