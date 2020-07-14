#include <stdlib.h>
#include "hashTest.h"

unsigned hash(char* clave) {  
  int p = 7;
  for(int i = 0; clave[i] != '\0'; i++)
    p = p*7 + clave[i]; //si no anda el hash es por esto (quizas)
  return p;
}

static void imprimir_intervalo(Interval intervalo) {
  printf("[%d, %d] ", intervalo->bgn, intervalo->end);
}

void test_insertar_hash1(void){
  TablaHash* newTable = tablahash_crear(31, hash);
  ITree arbol = itree_crear();
  Interval intervalo = malloc(sizeof(Intervalo));

  intervalo->bgn = 2;
  intervalo->end = 4;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 1;
  intervalo->end = 1;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 9;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 6;
  intervalo->end = 8;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbolete", arbol);

  arbol = itree_crear();
  intervalo->bgn = 4;
  intervalo->end = 6;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbusto", arbol);

  arbol = itree_crear();
  arbol = itree_unir(tablahash_buscar(newTable, "Arbolete"), tablahash_buscar(newTable, "Arbusto"));
  tablahash_insertar(newTable, "Resultado", arbol);

  itree_recorrer_dfs(tablahash_buscar(newTable, "Resultado"), imprimir_intervalo);

  tablahash_destruir(newTable);
  free(intervalo);
}

void test_insertar_hash2(void){
  TablaHash* newTable = tablahash_crear(31, hash);
  ITree arbol = itree_crear();
  Interval intervalo = malloc(sizeof(Intervalo));

  intervalo->bgn = 2;
  intervalo->end = 4;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 1;
  intervalo->end = 1;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 9;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 6;
  intervalo->end = 8;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbolete", arbol);

  arbol = itree_crear();
  intervalo->bgn = 4;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbusto", arbol);

  arbol = itree_crear();
  arbol = itree_unir(tablahash_buscar(newTable, "Arbolete"), tablahash_buscar(newTable, "Arbusto"));
  tablahash_insertar(newTable, "Resultado", arbol);

  itree_recorrer_dfs(tablahash_buscar(newTable, "Resultado"), imprimir_intervalo);
  
  tablahash_destruir(newTable);
  free(intervalo);
}

void test_insertar_hash3(void){
  TablaHash* newTable = tablahash_crear(31, hash);
  ITree arbol = itree_crear();
  Interval intervalo = malloc(sizeof(Intervalo));

  intervalo->bgn = 2;
  intervalo->end = 5;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 1;
  intervalo->end = 1;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 9;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 6;
  intervalo->end = 8;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbolete", arbol);

  arbol = itree_crear();
  intervalo->bgn = 4;
  intervalo->end = 8;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbusto", arbol);

  arbol = itree_crear();
  arbol = itree_unir(tablahash_buscar(newTable, "Arbolete"), tablahash_buscar(newTable, "Arbusto"));
  tablahash_insertar(newTable, "Resultado", arbol);

  itree_recorrer_dfs(tablahash_buscar(newTable, "Resultado"), imprimir_intervalo);
  
  tablahash_destruir(newTable);
  free(intervalo);
}

void test_insertar_hash4(void){
  TablaHash* newTable = tablahash_crear(31, hash);
  ITree arbol = itree_crear();
  Interval intervalo = malloc(sizeof(Intervalo));

  intervalo->bgn = 2;
  intervalo->end = 4;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 1;
  intervalo->end = 1;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 9;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 6;
  intervalo->end = 8;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbolete", arbol);

  arbol = itree_crear();
  intervalo->bgn = 9;
  intervalo->end = 10;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbusto", arbol);

  arbol = itree_crear();
  arbol = itree_unir(tablahash_buscar(newTable, "Arbolete"), tablahash_buscar(newTable, "Arbusto"));
  tablahash_insertar(newTable, "Resultado", arbol);

  itree_recorrer_dfs(tablahash_buscar(newTable, "Resultado"), imprimir_intervalo);
  
  tablahash_destruir(newTable);
  free(intervalo);
}

void test_insertar_hash5(void){
  TablaHash* newTable = tablahash_crear(31, hash);
  ITree arbol = itree_crear();
  Interval intervalo = malloc(sizeof(Intervalo));

  intervalo->bgn = 2;
  intervalo->end = 4;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 1;
  intervalo->end = 100;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 9;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 6;
  intervalo->end = 8;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbolete", arbol);

  arbol = itree_crear();
  intervalo->bgn = 32;
  intervalo->end = 32;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbusto", arbol);

  arbol = itree_crear();
  arbol = itree_unir(tablahash_buscar(newTable, "Arbolete"), tablahash_buscar(newTable, "Arbusto"));
  tablahash_insertar(newTable, "Resultado", arbol);

  itree_recorrer_dfs(tablahash_buscar(newTable, "Resultado"), imprimir_intervalo);
  
  tablahash_destruir(newTable);
  free(intervalo);
}

void test_insertar_hash6(void){
  TablaHash* newTable = tablahash_crear(31, hash);
  ITree arbol = itree_crear();
  Interval intervalo = malloc(sizeof(Intervalo));

  intervalo->bgn = 2;
  intervalo->end = 4;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 1;
  intervalo->end = 1;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 9;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 6;
  intervalo->end = 8;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbolete", arbol);

  arbol = itree_crear();
  intervalo->bgn = -1;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbusto", arbol);

  arbol = itree_crear();
  arbol = itree_unir(tablahash_buscar(newTable, "Arbolete"), tablahash_buscar(newTable, "Arbusto"));
  tablahash_insertar(newTable, "Resultado", arbol);

  itree_recorrer_dfs(tablahash_buscar(newTable, "Resultado"), imprimir_intervalo);
  
  tablahash_destruir(newTable);
  free(intervalo);
}

void test_insertar_hash7(void){
  TablaHash* newTable = tablahash_crear(31, hash);
  ITree arbol = itree_crear();
  Interval intervalo = malloc(sizeof(Intervalo));

  intervalo->bgn = 2;
  intervalo->end = 4;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 1;
  intervalo->end = 1;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 9;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 6;
  intervalo->end = 8;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbolete", arbol);

  arbol = itree_crear();
  intervalo->bgn = 5;
  intervalo->end = 5;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 1;
  intervalo->end = 3;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 8;
  intervalo->end = 8;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = -1;
  intervalo->end = 6;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "Arbusto", arbol);

  arbol = itree_crear();
  arbol = itree_unir(tablahash_buscar(newTable, "Arbolete"), tablahash_buscar(newTable, "Arbusto"));
  tablahash_insertar(newTable, "Resultado", arbol);

  itree_recorrer_dfs(tablahash_buscar(newTable, "Arbolete"), imprimir_intervalo);
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "Arbusto"), imprimir_intervalo);
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "Resultado"), imprimir_intervalo);

  tablahash_destruir(newTable);
  free(intervalo);
}