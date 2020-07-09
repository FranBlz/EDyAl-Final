#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include "bstree.h"

typedef struct _Conjunto{
  BSTree parteExt;
  BSTree parteComp;
}*Conjunto;

Conjunto conjunto_crear(int tipo, int set[], int cant);

Conjunto conjunto_unir(Conjunto c1, Conjunto c2);

Conjunto conjunto_intersectar(Conjunto c1, Conjunto c2);

Conjunto conjunto_complementar(Conjunto c1);

Conjunto conjunto_restar(Conjunto c1, Conjunto c2);

void conjunto_eliminar(Conjunto c1);

#endif /* __CONJUNTO_H__ */
