#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tablahash.h"
#include "itree.h"

TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash) {
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->hash = hash;
  tabla->capacidad = capacidad;
  tabla->tabla = malloc(sizeof(CasillaHash) * capacidad);
  tabla->numElems = 0;

  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->tabla[idx].clave = NULL;
    tabla->tabla[idx].dato = NULL;
  }

  return tabla;
}

void tablahash_insertar(TablaHash* tabla, char* clave, ITree dato) {
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  if(tabla->numElems + 1 <= tabla->capacidad) {
    tabla->numElems++;
    if(tabla->tabla[idx].clave == NULL) {
      tabla->tabla[idx].clave = malloc(sizeof(char) * strlen(clave) + 1);
      strcpy(tabla->tabla[idx].clave, clave);
      tabla->tabla[idx].dato = dato;
    }else {
      // int incremento = 7 - (tabla->hash(clave) % 7) ;
      // int aux = idx + incremento;

      int aux = idx + 1;

      for(; tabla->tabla[aux % tabla->capacidad].clave != NULL; aux ++);
      
      tabla->tabla[aux % tabla->capacidad].clave = malloc(sizeof(char) * strlen(clave) + 1);
      strcpy(tabla->tabla[aux % tabla->capacidad].clave, clave);
      tabla->tabla[aux % tabla->capacidad].dato = dato;
    }

    if(((double)tabla->numElems / (double)tabla->capacidad) >= LIMITE)
      tablahash_redimensionar(tabla);
  }
}

void tablahash_redimensionar(TablaHash *tabla) {
  if(tabla != NULL) {
    tabla->capacidad = tabla->capacidad * 2;
    CasillaHash* tablaAux = malloc(sizeof(CasillaHash) * tabla->capacidad);

    for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
      tablaAux[idx].clave = NULL;
      tablaAux[idx].dato = NULL;
    }

    CasillaHash* temp = tabla->tabla;
    tabla->numElems = 0;
    tabla->tabla = tablaAux;

    for(int i = 0; i < (tabla->capacidad / 2); i++) {
      if(temp[i].dato != NULL)
        tablahash_insertar(tabla, temp[i].clave, temp[i].dato);
      if(temp[i].clave != NULL)
        free(temp[i].clave);
    }

    free(temp);
  }
}

ITree tablahash_buscar(TablaHash* tabla, char* clave) {
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  ITree dato = itree_crear();  
  if(tabla->tabla[idx].clave != NULL) {
    CasillaHash* aux;
    for(aux = &(tabla->tabla[idx % tabla->capacidad]); (aux->clave != NULL && (strcmp(aux->clave, clave) != 0)) || (aux->dato == NULL && aux->clave != NULL); aux = &(tabla->tabla[(idx++) % tabla->capacidad]));
  
    if(aux->clave != NULL) {
      dato = aux->dato;
    }
  }

  return dato;
}

void tablahash_eliminar(TablaHash* tabla, char* clave) {
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  if(tabla->tabla[idx].clave != NULL) {
    CasillaHash* aux;
    for(aux = &(tabla->tabla[idx % tabla->capacidad]); (aux->clave != NULL && (strcmp(aux->clave, clave) != 0)) || (aux->dato == NULL && aux->clave != NULL); aux = &(tabla->tabla[(idx++) % tabla->capacidad]));
    
    if(aux->clave != NULL) {
      itree_destruir(aux->dato);
      aux->dato = NULL;
    }
  }
}

void tablahash_destruir(TablaHash* tabla) {
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
    if(tabla->tabla[idx].clave != NULL) {
      free(tabla->tabla[idx].clave);
      itree_destruir(tabla->tabla[idx].dato);
    }
  }
  free(tabla->tabla);
  free(tabla);
}
