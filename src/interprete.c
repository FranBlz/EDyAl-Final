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

int verificar_opcion(char opcion[]) {
  if (opcion == NULL)
    return ERROR;
  if (!strcmp(opcion, "salir")) {
    opcion = strtok(NULL, "");
    if(opcion != NULL)
      return ERROR;
    return SALIR;
  }
  if (!strcmp(opcion, "imprimir"))
    return IMPRIMIR;
  
  int flag = 1;
  for(int i = 0; opcion[i] != '\0' && flag == 1; i++) {
    if(!isalpha(opcion[i]))
      flag = 0;
  }
  if(flag) 
    return OPERACION;

  return ERROR;
}

int get_alias(char* ptr) {
  int flag = 1;
  if (ptr == NULL)
    flag = 0;
  for(int i = 0; ptr[i] != '\0' && flag == 1; i++) {
    if(!isalpha(ptr[i]))
      flag = 0;
  }
  return flag;
}

int main() {
  int end = 0, opcion;
  char buff[256];
  char *ptr;

  Interval intervalo = malloc(sizeof(Intervalo));
  intervalo->bgn = 1;
  intervalo->end = 2;
  ITree raiz = itree_crear();

  while (!end) {
    printf("Interprete:\n");
    scanf("%9[^\n]", buff);
    getchar();
    ptr = strtok(buff, " ");

    // printf("%s\n", ptr);

    opcion = verificar_opcion(ptr);

    switch (opcion) {
    case 0:
      printf("SALIR\n");
      end = 1;
      break;
    case 1:
      ptr = strtok(NULL, "");
      if(get_alias(ptr) == 1) {
        printf("IMPRIMIR %s\n", ptr);
        imprimir_intervalo(intervalo);
      }else {
        printf("ERROR\n");
      }
      break;
    case 2:
      printf("OPERACION\n");
      break;
    case -1:
      printf("ERROR\n");
      break;
    }
  }

  free(intervalo);
  itree_destruir(raiz);
}