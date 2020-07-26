#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#define LIMITE 0.7

#include "itree.h"

typedef unsigned (*FuncionHash) (char *clave);

typedef struct _CasillaHash {
  char *clave;
  ITree dato;
} CasillaHash;

typedef struct {
  CasillaHash *tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
} TablaHash;

/* 
* Crea una tabla hash de capacidad y funcion de hash dada
*/
TablaHash *tablahash_crear(unsigned capacidad, FuncionHash fun);

/* 
* Inserta en la tabla el dato en la casilla que corresponde con clave segun la 
* funcion hash de la tabla
*/
void tablahash_insertar(TablaHash *tabla, char *clave, ITree dato);

/* 
* Devuelve el arbol presente en la casilla de la tabla que
* corresponde con la clave dada segun la funcion de hash de la tabla
*/
ITree tablahash_buscar(TablaHash *tabla, char *clave);

/* 
* Elimina el dato en la casilla de la tabla indicada por la clave
*/
void tablahash_eliminar(TablaHash *tabla, char *clave);

/* 
* Redimensiona la tabla al siguiente primo de su capacidad
* actual, reasigna las claves de los elementos presentes y
* descarta aquellos elementos que hayan sido borrados
*/
void tablahash_redimensionar(TablaHash *tabla);

/* 
* Elimina la tabla dada y todos sus elementos
*/
void tablahash_destruir(TablaHash *tabla);

#endif
