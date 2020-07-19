#include <stdlib.h>
#include "hashTest.h"

unsigned hash(char* clave) {  
  int p = 7;
  for(int i = 0; clave[i] != '\0'; i++)
    p = (p * 31) + clave[i];
  return p;
}

static void imprimir_intervalo(Interval intervalo) {
  printf("[%d, %d] ", intervalo->bgn, intervalo->end);
}

void test_operaciones1(void) {
  TablaHash* newTable = tablahash_crear(31, hash);
  ITree arbol = itree_crear();
  Interval intervalo = malloc(sizeof(Intervalo));

  intervalo->bgn = 7;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 3;
  intervalo->end = 5;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 15;
  intervalo->end = 15;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = -3;
  intervalo->end = 1;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 11;
  intervalo->end = 12;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 20;
  intervalo->end = 20;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "A", arbol);

  arbol = itree_crear();
  intervalo->bgn = 2;
  intervalo->end = 2;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 6;
  intervalo->end = 6;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 10;
  intervalo->end = 10;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 13;
  intervalo->end = 14;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 16;
  intervalo->end = 19;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "B", arbol);

  arbol = itree_crear();
  arbol = itree_unir(tablahash_buscar(newTable, "A"), tablahash_buscar(newTable, "B"), arbol);
  tablahash_insertar(newTable, "UNION", arbol);
  arbol = itree_crear();
  arbol = itree_interseccion(tablahash_buscar(newTable, "A"), tablahash_buscar(newTable, "B"), arbol);
  tablahash_insertar(newTable, "INTERSECCION", arbol);
  arbol = itree_crear();
  arbol = itree_diferencia(tablahash_buscar(newTable, "A"), tablahash_buscar(newTable, "B"), arbol);
  tablahash_insertar(newTable, "AminusB", arbol);
  arbol = itree_crear();
  arbol = itree_diferencia(tablahash_buscar(newTable, "B"), tablahash_buscar(newTable, "A"), arbol);
  tablahash_insertar(newTable, "BminusA", arbol);
  arbol = itree_crear();
  arbol = itree_diferencia(tablahash_buscar(newTable, "A"), tablahash_buscar(newTable, "UNION"), arbol);
  tablahash_insertar(newTable, "AminusUNION", arbol);
  arbol = itree_crear();
  arbol = itree_diferencia(tablahash_buscar(newTable, "B"), tablahash_buscar(newTable, "UNION"), arbol);
  tablahash_insertar(newTable, "BminusUNION", arbol);
  arbol = itree_crear();
  arbol = itree_complemento(tablahash_buscar(newTable, "A"), arbol);
  tablahash_insertar(newTable, "compA", arbol);
  arbol = itree_crear();
  arbol = itree_complemento(tablahash_buscar(newTable, "B"), arbol);
  tablahash_insertar(newTable, "compB", arbol);

  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "A"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "B"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "UNION"), imprimir_intervalo);
  puts("");
  puts("");
  CU_ASSERT_EQUAL(tablahash_buscar(newTable, "INTERSECCION"), NULL);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "AminusB"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "BminusA"), imprimir_intervalo);
  puts("");
  puts("");
  CU_ASSERT_EQUAL(tablahash_buscar(newTable, "AminusUNION"), NULL);
  puts("");
  puts("");
  CU_ASSERT_EQUAL(tablahash_buscar(newTable, "BminusUNION"), NULL);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "compA"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "compB"), imprimir_intervalo);
  puts("");

  tablahash_destruir(newTable);
  free(intervalo);
}

void test_operaciones2(void) {
  TablaHash* newTable = tablahash_crear(31, hash);
  ITree arbol = itree_crear();
  Interval intervalo = malloc(sizeof(Intervalo));

  intervalo->bgn = 7;
  intervalo->end = 9;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 3;
  intervalo->end = 5;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 15;
  intervalo->end = 15;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = -3;
  intervalo->end = 1;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 11;
  intervalo->end = 12;
  arbol = itree_insertar(arbol, intervalo);
  intervalo->bgn = 20;
  intervalo->end = 20;
  arbol = itree_insertar(arbol, intervalo);
  tablahash_insertar(newTable, "A", arbol);

  arbol = itree_crear();
  tablahash_insertar(newTable, "N1", arbol);
  arbol = itree_crear();
  tablahash_insertar(newTable, "N2", arbol);
  
  arbol = itree_crear();
  arbol = itree_unir(tablahash_buscar(newTable, "N1"), tablahash_buscar(newTable, "N2"), arbol);
  tablahash_insertar(newTable, "N3", arbol);
  arbol = itree_crear();
  arbol = itree_interseccion(tablahash_buscar(newTable, "N1"), tablahash_buscar(newTable, "N2"), arbol);
  tablahash_insertar(newTable, "N4", arbol);
  arbol = itree_crear();
  arbol = itree_diferencia(tablahash_buscar(newTable, "N1"), tablahash_buscar(newTable, "N2"), arbol);
  tablahash_insertar(newTable, "N5", arbol);
  arbol = itree_crear();
  arbol = itree_diferencia(tablahash_buscar(newTable, "N1"), tablahash_buscar(newTable, "A"), arbol);
  tablahash_insertar(newTable, "N6", arbol);
  arbol = itree_crear();
  arbol = itree_diferencia(tablahash_buscar(newTable, "A"), tablahash_buscar(newTable, "N2"), arbol);
  tablahash_insertar(newTable, "A2", arbol);
  arbol = itree_crear();
  arbol = itree_complemento(tablahash_buscar(newTable, "N1"), arbol);
  tablahash_insertar(newTable, "U", arbol);
  
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "N1"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "N2"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "N3"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "N4"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "N5"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "N6"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "A2"), imprimir_intervalo);
  puts("");
  puts("");
  itree_recorrer_dfs(tablahash_buscar(newTable, "U"), imprimir_intervalo);
  puts("");

  tablahash_destruir(newTable);
  free(intervalo);
}