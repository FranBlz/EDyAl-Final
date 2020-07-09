#include "bstree.h"
#include <stdlib.h>

BSTree bstree_crear() {
    return NULL;
}

BSTree bstree_insertar(BSTree arbol, int dato) {
    if(arbol == NULL) {
        BSTree nodo = malloc(sizeof(BSTNodo));
        nodo->dato = dato;
        nodo->left = NULL;
        nodo->right = NULL;
        arbol = nodo;
    }else if(dato > arbol->dato) {
        arbol->right = bstree_insertar(arbol->right, dato);
    }else {
        arbol->left = bstree_insertar(arbol->left, dato);
    }

    return arbol;
}

int bstree_contiene(BSTree arbol, int dato) {
    int flag = 0;
    if(arbol != NULL) {
        if(arbol->dato == dato) {
            flag = 1;
        }else if(dato > arbol->dato) {
            flag = bstree_contiene(arbol->right, dato);
        }else {
            flag = bstree_contiene(arbol->left, dato);
        }
    }
    return flag;
}

int bstree_nelementos(BSTree arbol) {
    int cant, l = 0, r = 0;

    if(arbol != NULL) {
        l = bstree_nelementos(arbol->left);
        r = bstree_nelementos(arbol->right);
        cant = l + r + 1;
    }else {
        return 0;
    }

    return cant;
}

void bstree_recorrer(BSTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit) {
  if(arbol != NULL) {
    if(orden == BTREE_RECORRIDO_IN) {
      bstree_recorrer(arbol->left, orden, visit);
      visit(arbol->dato);
      bstree_recorrer(arbol->right, orden, visit);
    }else if (orden == BTREE_RECORRIDO_PRE) {
      visit(arbol->dato);
      bstree_recorrer(arbol->left, orden, visit);
      bstree_recorrer(arbol->right, orden, visit);
    }else {
      bstree_recorrer(arbol->left, orden, visit);
      bstree_recorrer(arbol->right, orden, visit);
      visit(arbol->dato);
    }
  }
}

BSTree bstree_minimo(BSTree arbol) {
    if(arbol->left != NULL) {
        return bstree_minimo(arbol->left); 
    }else {
        return arbol;
    }
}

BSTree bstree_eliminar(BSTree arbol, int dato) {
    BSTree aux, min;
    
    if(arbol->dato == dato && arbol->left == NULL && arbol->right == NULL) {
        aux = arbol;
        arbol = NULL;
        free(aux);
    }else if(arbol->dato == dato) {
        if(arbol->left == NULL) {
            aux = arbol;
            arbol = arbol->right;
            free(aux);
        }else if(arbol->right == NULL) {
            aux = arbol;
            arbol = arbol->left;
            free(aux);
        }else {
            min = bstree_minimo(arbol->right);
            arbol->dato = min->dato;
            arbol->right = bstree_eliminar(arbol->right, min->dato);
        }
    }else if(dato > arbol->dato) {
        arbol->right = bstree_eliminar(arbol->right, dato);
    }else {
        arbol->left = bstree_eliminar(arbol->left, dato);
    }

    return arbol;
}