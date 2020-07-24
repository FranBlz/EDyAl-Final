#include <stdio.h>
#include <stdlib.h>
#include "conjuntos.h"
#include "tablahash.h"
#include "itree.h"

static void imprimir_intervalo(Interval intervalo) {
  if(intervalo != NULL) {
    if(intervalo->bgn != intervalo->end) {
      printf("%d:%d", intervalo->bgn, intervalo->end);
    }else {
      printf("%d", intervalo->bgn);
    }
  }else {
    printf("{}");
  }
}

unsigned hash(char* clave) {  
  int p = 7;
  for(int i = 0; clave[i] != '\0'; i++) {
    p = (p * 31) + clave[i];
  }
  return p;
}

TablaHash* conjuntos_iniciar() {
  return tablahash_crear(31, hash);
}

void conjunto_destruir(TablaHash* tabla) {
  tablahash_destruir(tabla);
}

void imprimir_conjunto(char alias[], TablaHash* tabla) {
  ITree raiz = tablahash_buscar(tabla, alias);
  if(raiz != NULL) {
    itree_recorrer(raiz, imprimir_intervalo);
  }else {
    printf("Esa clave no corresponde a ningun elemento\n");
  }
  raiz = NULL;

  // printf("alias %s\n\n", alias);
  // for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
  //   if(tabla->tabla[idx].clave != NULL && tabla->tabla[idx].dato != NULL) {
  //     printf("%s", tabla->tabla[idx].clave);
  //     itree_recorrer(tabla->tabla[idx].dato, imprimir_intervalo);
  //     puts("");
  //   }else {
  //     printf("VACIO %d\n", idx);
  //   }
  // }
}

void perform_operacion(char alias[], char set1[], char set2[], TablaHash* tabla, int op) {
  ITree result = itree_crear();
  ITree tree1 = tablahash_buscar(tabla, set1), tree2 = tablahash_buscar(tabla, set2);

  if(tree1 != NULL && tree2 != NULL) {
    if(tree1->intervalo == NULL)
      tree1 = NULL;
    if(tree2->intervalo == NULL)
      tree2 = NULL;

    switch(op) {
        case 1:
          result = itree_unir(tree1, tree2, result);
          break;
        case 2:
          result = itree_interseccion(tree1, tree2, result);
          break;
        case 3:
          result = itree_diferencia(tree1, tree2, result);
          break;
    }
    tablahash_eliminar(tabla, alias);
    if(result == NULL)
      result = itree_insertar(result, NULL);
    tablahash_insertar(tabla, alias, result);
  }else {
    printf("Algun conjunto pedido no existe\n");
  }
}

void perform_complemento(char alias[], char set[], TablaHash* tabla) {
  ITree result = itree_crear();
  ITree tree = tablahash_buscar(tabla, set);
  
  if(tree != NULL) {
    if(tree->intervalo == NULL)
      tree = NULL;

    result = itree_complemento(tree, result);
    tablahash_eliminar(tabla, alias);
    if (result == NULL)
      result = itree_insertar(result, NULL);
    tablahash_insertar(tabla, alias, result);
  }else {
    printf("El conjunto pedido no existe\n");
  }
}

void perform_insercion_comp(char alias[], int val1, int val2, TablaHash *tabla) {
  Interval intervalo = malloc(sizeof(Intervalo));
  intervalo->bgn = val1;
  intervalo->end = val2;
  ITree arbol = itree_crear();
  arbol = itree_insertar(arbol, intervalo);

  tablahash_eliminar(tabla, alias);
  tablahash_insertar(tabla, alias, arbol);

  free(intervalo);
}

void perform_insercion_ext(char alias[], int array[], int cantElem, TablaHash *tabla) {
  ITree arbol = itree_crear();
  Interval intervalo = malloc(sizeof(Intervalo));
  
  if(cantElem == 0) {
    arbol = itree_insertar(arbol, NULL);
  }else {
    for(int i = 0; i < cantElem; i++) {
      intervalo->bgn = array[i];
      intervalo->end = array[i];
      arbol = itree_insertar(arbol, intervalo);
    }
  }

  tablahash_eliminar(tabla, alias);
  tablahash_insertar(tabla, alias, arbol);
  free(intervalo);
}
