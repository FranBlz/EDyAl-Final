#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "itree.h"
#include "tablahash.h"

#define CANT_OPCIONES 6
#define MAX_DIGITS_DOUBLE 320

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

int verificar_opcion(char opcion[]) {
  if (opcion == NULL)
    return ERROR;
  if (strcmp(opcion, "salir"))
    return SALIR;
  if (strcmp(opcion, "imprimir"))
    return IMPRIMIR;
  
  int flag = 1;
  for(int i = 0; opcion[i] != '\0'; i++) {
    if(!isalpha(opcion[i]))
      flag = 0;
  }
  if(flag) 
    return OPERACION;
}

int main() {
  int end = 0 , opcion;
  char buff[256];
  char *ptr;

  Interval intervalo = malloc(sizeof(Intervalo));
  ITree raiz = itree_crear();

  while (!end) {
    scanf("%[^\n]", buff);
    getchar();

    ptr = strtok(buff, " ");

    opcion = verificar_opcion(ptr);

    switch (opcion) {
    case 0:
      printf("\nSALIR\n");
      break;
    case 1:
      printf("\nIMPRIMIR\n");
      break;
    case 2:
      printf("\nOPERACION\n");
      break;
    case -1:
      printf("\nERROR\n");
      break;
    }
  }

  free(intervalo);
  itree_destruir(raiz);
}