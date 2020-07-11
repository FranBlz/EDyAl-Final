#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#define LIMITE 0.7

#include "conjunto.h"

typedef unsigned (*FuncionHash)(char* clave);

typedef struct _CasillaHash{
  char* clave;
  Conjunto dato;
  struct _CasillaHash* sig;
} CasillaHash;

typedef struct {
  CasillaHash* tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
} TablaHash;

TablaHash* tablahash_crear(unsigned capacidad, FuncionHash fun);

void tablahash_insertar(TablaHash* tabla, char* clave, Conjunto dato);

Conjunto tablahash_buscar(TablaHash* tabla, char* clave);

void tablahash_eliminar(TablaHash* tabla, char* clave);

void tablahash_redimensionar(TablaHash *tabla);

void tablahash_destruir(TablaHash* tabla);

#endif /* __TABLAHASH_H__ */
