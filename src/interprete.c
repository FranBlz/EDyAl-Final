#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tablahash.h"
#include "itree.h"

// #define OPCION_INCORRECTA -1
// #define FORMATO_INTERVALO_INCORRECTO -2
// #define DATOS_INNECESARIOS -3
// #define INICIO_MAYOR_QUE_FIN -4
// #define FALTA_OPCION -5
// #define FALTA_INTERVALO -6

#define OPERACION 2
#define IMPRIMIR 1
#define SALIR 0
#define ERROR -1

unsigned hash(char* clave) {  
  int p = 7;
  for(int i = 0; clave[i] != '\0'; i++)
    p = (p * 31) + clave[i]; //si no anda el hash es por esto (quizas)
  return p;
}

static void imprimir_intervalo(Interval intervalo) {
  printf("[%d, %d] ", intervalo->bgn, intervalo->end);
}

int verificar_opcion(char first[], char rest[]) {
  if (first == NULL)
    return ERROR;
  if (!strcmp(first, "salir") && (!strcmp(rest, "\n") || !strcmp(rest, "\0")))
    return SALIR;
  if (!strcmp(first, "imprimir"))
    return IMPRIMIR;

  return ERROR;
}

int main() {
  int end = 0, opcion;
  char buff[256];
  char *first, *rest;
  first = malloc(sizeof(char)*256);
  rest = malloc(sizeof(char)*256);

  Interval intervalo = malloc(sizeof(Intervalo));
  intervalo->bgn = 1;
  intervalo->end = 2;
  ITree raiz = itree_crear();

  while (!end) {
    printf("Interprete:\n");
    if(fgets(buff, 256, stdin) != NULL) {
      if(buff[strlen(buff) - 1] == '\n') {
        sscanf(buff, "%s %[^\n]", first, rest);
      }else {
        for(char ch = getchar(); ch != '\n'; ch = getchar());
        printf("Excedio el limite de caracteres (254)\n");
      }
    }

    printf("FIRST %s\n", first);
    printf("REST %s\n", rest);

    opcion = verificar_opcion(first, rest);

    switch (opcion) {
    case 0:
      printf("SALIR\n");
      end = 1;
      break;
    case 1:
      printf("IMPRIMIR\n");
      imprimir_intervalo(intervalo);
      break;
    case 2:
      printf("OPERACION\n");
      break;
    case -1:
      printf("ERROR\n");
      break;
    }
    puts("");
    first[0] = '\0';
    rest[0] = '\0';
  }

  free(intervalo);
  free(first);
  free(rest);
  itree_destruir(raiz);
}