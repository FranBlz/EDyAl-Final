#include "AVLTree.h"
#include <stdlib.h>
#include <stdio.h>

AVLTree avltree_crear() {
  return NULL;
}

void avltree_destruir(AVLTree arbol) {
  if (arbol != NULL) {
    avltree_destruir(arbol->left);
    avltree_destruir(arbol->right);
    free(arbol->dato);
    free(arbol);
  }
}

int avltree_altura_aux(AVLTree arbol) {
  if (arbol == NULL)
    return 0;
  int sizeIzq = avltree_altura_aux(arbol->left);
  int sizeDer = avltree_altura_aux(arbol->right);
  return sizeIzq > sizeDer ? sizeIzq + 1 : sizeDer + 1;
}
// Cambiar altura para que respete las correcciones de valentina
// 1 - la altura empieza en 1?
// 2 - agregar un valor de altura a los nodos para no recalcular el arbol entero
int avltree_altura(AVLTree arbol) {
  return arbol == NULL ? -1 : avltree_altura_aux(arbol) - 1;
}

int avltree_balance_factor(AVLTree arbol) {
  return avltree_altura(arbol->right) - avltree_altura(arbol->left);
}

AVLTree avltree_rotacion_simple_der(AVLTree arbol) {
  AVLTree aux = arbol->left;
  arbol->left = aux->right;
  aux->right = arbol;
  return aux;
}

AVLTree avltree_rotacion_simple_izq(AVLTree arbol) {
  AVLTree aux = arbol->right;
  arbol->right = aux->left;
  aux->left = arbol;
  return aux;
}

AVLTree avltree_balancear_izq(AVLTree arbol) {
  if (avltree_balance_factor(arbol->left) <= 0)
    arbol = avltree_rotacion_simple_der(arbol);
  else {
    arbol->left = avltree_rotacion_simple_izq(arbol->left);
    arbol = avltree_rotacion_simple_der(arbol);
  }
  return arbol;
}

AVLTree avltree_balancear_der(AVLTree arbol) {
  if (avltree_balance_factor(arbol->right) >= 0)
    arbol = avltree_rotacion_simple_izq(arbol);
  else {
    arbol->right = avltree_rotacion_simple_der(arbol->right);
    arbol = avltree_rotacion_simple_izq(arbol);
  }
  return arbol;
}

AVLTree create_node(int num) {
  AVLTree nodo = malloc(sizeof(ANode));
  nodo->dato = num;
  nodo->left = NULL;
  nodo->right = NULL;
  return nodo;
}

// plantear correccion de valentina, usar bandera para no rebalancear hacia arriba constantemente
AVLTree avltree_insertar(AVLTree arbol, int num) {
  if (arbol == NULL)
    return create_node(num);

  int posicion = num - arbol->dato;
  if (posicion < 0) {
    arbol->left = avltree_insertar(arbol->left, num);
    if (avltree_balance_factor(arbol) < -1)
      arbol = avltree_balancear_izq(arbol);
  } else if (posicion > 0) {
    arbol->right = avltree_insertar(arbol->right, num);
    if (avltree_balance_factor(arbol) > 1)
      arbol = avltree_balancear_der(arbol);
  }

  return arbol;
}

AVLTree avltree_minimo(AVLTree arbol) {
  while (arbol->left != NULL)
    arbol = arbol->left;
  return arbol;
}

AVLTree avltree_eliminar(AVLTree arbol, int num) {
  if (arbol == NULL)
    return arbol;

  int posicion = num - arbol->dato;

  if (posicion == 0) {
    AVLTree aux = arbol;
    if (arbol->left != NULL && arbol->right != NULL) {
      aux = avltree_minimo(arbol->right);

      int i = arbol->dato;
      arbol->dato = aux->dato;
      aux->dato = i;

      arbol->right = avltree_eliminar(arbol->right, aux->dato);
      if (avltree_balance_factor(arbol) < -1)
        arbol = avltree_balancear_izq(arbol);
    } else {
      arbol = arbol->left == NULL ? arbol->right : arbol->left;
      free(aux);
    }
  } else if (posicion < 0) {
    arbol->left = avltree_eliminar(arbol->left, num);
    if (avltree_balance_factor(arbol) > 1)
      arbol = avltree_balancear_der(arbol);
  } else {
    arbol->right = avltree_eliminar(arbol->right, num);
    if (avltree_balance_factor(arbol) < -1)
      arbol = avltree_balancear_izq(arbol);
  }
  return arbol;
}

int avltree_buscar(AVLTree arbol, int num) {
  if (arbol != NULL) {
    if (arbol->dato == num)
      return 1;
    if (arbol->left != NULL && arbol->dato < num)
      return avltree_intersectar(arbol->left, num);
    if (arbol->right != NULL && arbol->dato > num)
      return avltree_intersectar(arbol->right, num);
  }
  return NULL;
}

void avltree_recorrer_dfs(AVLTree arbol) {
  if (arbol != NULL) {
    printf("%d", arbol->dato);
    avltree_recorrer_dfs(arbol->left);
    avltree_recorrer_dfs(arbol->right);
  }
}
