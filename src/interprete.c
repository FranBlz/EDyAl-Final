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

int check_alpha(char word[]) {
  int flag = 1;
  if(!strcmp(word, "\0"))
    flag = 0;
  for(int i = 0; flag == 1 && (word[i] != '\0' && word[i] != '\n'); i++) {
    if(!isalpha(word[i]))
      flag = 0;
  }

  return flag;
}

int verificar_opcion(char first[], char cond[], char rest[]) {
  if (first == NULL) {
    return ERROR;
  }else if (!strcmp(first, "salir")) {
    if (!strcmp(cond, "\0"))
      return SALIR;
  }else if (!strcmp(first, "imprimir")) {
    if(check_alpha(cond) && !strcmp(rest, "\0"))
      return IMPRIMIR;
  }else if(check_alpha(first) && !strcmp(cond, "=") && strcmp(rest, "\0")) {
    return OPERACION;
  }

  return ERROR;
}


void define_operacion(char alias[], char op[], char aux[], TablaHash *tabla) {
  char *first = malloc(sizeof(char)*256);
  char *scnd = malloc(sizeof(char)*256);
  char *thrd = malloc(sizeof(char)*256);
  first[0] = '\0';
  scnd[0] = '\0';
  thrd[0] = '\0';

  printf("OP %s\n", op);

  sscanf(op, "%s %s %s %[^\n]", first, scnd, thrd, aux);

  if(!strcmp(aux, "\0") && (check_alpha(first) && check_alpha(thrd))) {
    if(!strcmp(scnd, "|")) {
      printf("UNION\n");
      printf("FIRST %s\n", first);
      printf("SCND %s\n", scnd);
      printf("THRD %s\n", thrd);
      printf("REST %s\n", aux);
    }else if(!strcmp(scnd, "&")) {
      printf("INTERSECCION\n");
      printf("FIRST %s\n", first);
      printf("SCND %s\n", scnd);
      printf("THRD %s\n", thrd);
      printf("REST %s\n", aux);
    }else if(!strcmp(scnd, "-")) {
      printf("RESTA\n");
      printf("FIRST %s\n", first);
      printf("SCND %s\n", scnd);
      printf("THRD %s\n", thrd);
      printf("REST %s\n", aux);
    }else {
      printf("Error al definir operacion entre conjuntos\n");
    }
  }else if(first[0] == '~' && !strcmp(scnd, "\0") && !strcmp(thrd, "\0") && !strcmp(aux, "\0")) {
    sscanf(first, "~%s", first);
    printf("COMPLEMENTO\n");
  }else {
    printf("FIRST %s\n", first);
    printf("SCND %s\n", scnd);
    printf("THRD %s\n", thrd);
    printf("REST %s\n", aux);
    printf("Error de sintaxis en la operación\n");
  }

  if(tabla != NULL) {
    printf("ALIAS %s\n", alias);
  }

  free(first);
  free(scnd);
  free(thrd);
}

int main() {
  int end = 0, opcion;
  char buff[256];
  char *first, *rest, *cond;
  first = malloc(sizeof(char)*256);
  cond = malloc(sizeof(char)*256);
  rest = malloc(sizeof(char)*256);

  Interval intervalo = malloc(sizeof(Intervalo));
  ITree raiz = itree_crear();
  TablaHash* tabla = tablahash_crear(31, hash);

  while (!end) {
    first[0] = '\0';
    cond[0] = '\0';
    rest[0] = '\0';
    printf("Ingrese un comando:\n");
    if(fgets(buff, 256, stdin) != NULL) {
      if(buff[strlen(buff) - 1] == '\n') {
        sscanf(buff, "%s %s %[^\n]", first, cond, rest);
      }else {
        for(char ch = getchar(); ch != '\n'; ch = getchar());
        printf("Excedio el limite de caracteres (254)\n");
      }
    }

    opcion = verificar_opcion(first, cond, rest);

    switch (opcion) {
    case 0:
      printf("SALIR\n");
      end = 1;
      break;
    case 1:
      printf("IMPRIMIR\n");
      raiz = tablahash_buscar(tabla, cond);
      if(raiz != NULL) {
        itree_recorrer_dfs(raiz, imprimir_intervalo);
      }else {
        printf("Esa clave no corresponde a ningun elemento\n");
      }
      raiz = NULL;
      break;
    case 2:
      // printf("OPERACION\n");
      cond[0] = '\0';
      define_operacion(first, rest, cond, tabla);
      break;
    case -1:
      printf("Comando inválido\n");
      break;
    }
    puts("");
  }

  free(intervalo);
  free(first);
  free(cond);
  free(rest);
  itree_destruir(raiz);
  tablahash_destruir(tabla);
}


// void realizar_complemento(char alias[], char first[], TablaHash *tabla) {
//   ITree temp = itree_crear();
//   temp = tablahash_buscar(tabla, first);
//   if(temp != NULL) {
//     temp = itree_complemento(temp);
//     if(tablahash_buscar(tabla, alias) != NULL)
//       tablahash_eliminar(tabla, alias);
//     tablahash_insertar(tabla, alias, temp);
//     printf("Complemento de conjunto\n");
//   }else {
//     printf("No existe el conjunto pedido\n");
//   }
// }

// void realizar_operacion(char alias[], char op[], TablaHash *tabla) {
//   char *set1 = malloc(sizeof(char)*256);
//   char *div = malloc(sizeof(char)*256);
//   char *set2 = malloc(sizeof(char)*256);
//   char *rest = malloc(sizeof(char)*256);
//   sscanf(op, "%s %s %s", set1, div, set2);
//   if(!strcmp(rest, "\0")) {
//     if(check_alpha(set1) && check_alpha(set2)) {
//       if(!strcmp(div, "|")) {
//         printf("UNION\n");
//       }else if(!strcmp(div, "&")) {
//         printf("INTERSECCION\n");
//       }else if(!strcmp(div, "-")) {
//         printf("RESTA\n");
//       }
      
//       ITree temp = itree_crear();
//       temp = tablahash_buscar(tabla, alias);
//       if(temp != NULL)
//       printf("sdf");
//     }
//   }else {
//     printf("Caracteres de mas en operación");
//   }

//   printf("SET1 %s\n", set1);
//   printf("DIV %s\n", div);
//   printf("SET2 %s\n", set2);

//   free(set1);
//   free(div);
//   free(set2);
// }

// void define_operacion(char alias[], char op[], TablaHash *tabla) {
//   char *first = malloc(sizeof(char)*256);
//   char *rest = malloc(sizeof(char)*256);
//   sscanf(op, "%s %[^\n]", first, rest);

//   if(!strcmp(first, "=")) {
//     if(rest[0] == '{') {
//       printf("Insercion de conjunto\n");
//     }else if(rest[0] == '~') {
//       sscanf(rest, "~%s", first);
//       if(check_alpha(first)) {
//         realizar_complemento(alias, first, tabla);
//       }else {
//         printf("Nombre de conjunto invalido\n");
//       }
//     }else if(isalpha(rest[0])) {
//       realizar_operacion(alias, rest, tabla);
//       printf("Operacion entre conjuntos\n");
//     }
//   }else {
//     printf("Error en sintaxis de operación\n");
//   }

//   free(first);
//   free(rest);
// }