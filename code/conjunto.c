#include <stdlib.h>
#include "conjunto.h"

Conjunto crear(int tipo, int set[], int cant) {
  Conjunto conj = malloc(sizeof(struct _Conjunto));
  conj->parteExt = bstree_crear();
  conj->parteComp = bstree_crear();

  if(tipo) {
    for(int i = 0; i < cant; i++) {
      conj->parteExt = bstree_insertar(conj->parteExt, set[i]);
    }
  }

  return conj;
}

Conjunto conjunto_unir(Conjunto c1, Conjunto c2) {
  
}

// Conjunto conjunto_intersectar(Conjunto c1, Conjunto c2) {

// }

// Conjunto conjunto_complementar(Conjunto c1) {

// }

// Conjunto conjunto_restar(Conjunto c1, Conjunto c2) {

// }

void conjunto_eliminar(Conjunto c1) {

}