#include <stdlib.h>
#include "conjunto.h"

Conjunto conjunto_crear() {
  Conjunto conj = malloc(sizeof(struct _Conjunto));
  conj->parteExt = avltree_crear();
  conj->parteComp = itree_crear();

  return conj;
}

void insertar_partes(Conjunto c1, int tipo, int set[], int cant) {
  
}

Conjunto conjunto_unir(Conjunto c1, Conjunto c2) {
  Conjunto new = conjunto_crear();
}

// Conjunto conjunto_intersectar(Conjunto c1, Conjunto c2) {

// }

// Conjunto conjunto_complementar(Conjunto c1) {

// }

// Conjunto conjunto_restar(Conjunto c1, Conjunto c2) {

// }

// void conjunto_eliminar(Conjunto c1) {

// }