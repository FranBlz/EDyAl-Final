#include <stdio.h>
#include <stdlib.h>
#include "tablahash.h"
#include "conjunto.h"

unsigned hash(char* clave) {  
  int p = 0;
  for(int i = 0; clave[i] != '\0'; i++)
    p += clave[i];
  return p;
}

int main() {
  int n;
  char *pos;
  TablaHash *th = tablahash_crear(10, hash);

  n = 111;
  pos = "Juan";
  tablahash_insertar(th, pos, n);
  // n = 222;
  // pos = "Ana";
  // tablahash_insertar(th, pos, n);
  n = 333;
  pos = "Fede";
  tablahash_insertar(th, pos, n);
  n = 444;
  pos = "Ciro";
  tablahash_insertar(th, pos, n);
  n = 555;
  pos = "Lucho";
  tablahash_insertar(th, pos, n);
  n = 666;
  pos = "Alex";
  tablahash_insertar(th, pos, n);
  n = 777;
  pos = "Juna";
  tablahash_insertar(th, pos, n);

  for(int i=0;i<th->capacidad;i++){
    printf("INDICE: %d DATO: ", i);
    if(th->tabla[i].dato == 0)
      printf("VACIO");
    else
      printf("%d", th->tabla[i].dato);
    puts("");
  }

  n = 222;
  pos = "Ana";
  tablahash_eliminar(th, pos);
  
  // n = 555;
  // pos = "Lucho";
  // tablahash_buscar(th, pos);

  // puts("");
  // for(int i=0;i<th->capacidad;i++){
  //   printf("INDICE: %d DATO: ", i);
  //   if(th->tabla[i].dato == NULL)
  //     printf("VACIO");
  //   else
  //     printf("%d", (*(int*)th->tabla[i].dato));
  //   puts("");
  // }

  tablahash_destruir(th);

  return 0;
}