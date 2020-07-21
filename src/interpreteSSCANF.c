#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tablahash.h"
#include "itree.h"

#define INSERCION 3
#define OPERACION 2
#define IMPRIMIR 1
#define SALIR 0
#define ERROR -1

typedef ITree (*FuncionOperacion)(ITree set1, ITree set2, ITree result);

unsigned hash(char* clave) {  
  int p = 7;
  for(int i = 0; clave[i] != '\0'; i++) {
    p = (p * 31) + clave[i];
  }
  return p;
}

static void imprimir_intervalo(Interval intervalo) {
  if(intervalo != NULL) {
    if(intervalo->bgn != intervalo->end) {
      printf("%d:%d", intervalo->bgn, intervalo->end);
    }else {
      printf("%d", intervalo->bgn);
    }
  }else {
    printf("{}");
  }
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

int verificar_opcion(char first[], char cond[], char rest[], int read) {
  if (read == 0) {
    return ERROR;
  }else if (!strcmp(first, "salir")) {
    if (read == 1)
      return SALIR;
  }else if (!strcmp(first, "imprimir")) {
    if(check_alpha(cond) && read == 2)
      return IMPRIMIR;
  }else if(check_alpha(first) && !strcmp(cond, "=") && read == 3) {
    if(rest[0] == '{') {
      return INSERCION;
    }else {
      return OPERACION;
    }
  }
  return ERROR;
}

void perform_operacion(char alias[], char set1[], char set2[], TablaHash* tabla, FuncionOperacion fun) {
  ITree result = itree_crear();
  ITree tree1 = tablahash_buscar(tabla, set1), tree2 = tablahash_buscar(tabla, set2);

  if(tree1 != NULL && tree2 != NULL) {
    if(tree1->intervalo == NULL)
      tree1 = NULL;
    if(tree2->intervalo == NULL)
      tree2 = NULL;

    result = fun(tree1, tree2, result);
    tablahash_eliminar(tabla, alias);
    tablahash_insertar(tabla, alias, result);
  }else {
    printf("Algun conjunto pedido no existe\n");
  }
}

void perform_complemento(char alias[], char set[], TablaHash* tabla) {
  ITree result = itree_crear();
  ITree tree = tablahash_buscar(tabla, set);
  
  if(tree != NULL) {
    if(tree->intervalo == NULL)
      tree = NULL;

    result = itree_complemento(tree, result);
    tablahash_eliminar(tabla, alias);
    tablahash_insertar(tabla, alias, result);
  }else {
    printf("El conjunto pedido no existe\n");
  }
}

void define_operacion(char alias[], char op[], TablaHash *tabla) {
  char first[256], scnd[256], thrd[256], aux[256];
  int read;

  read = sscanf(op, "%s %s %s %[^\n]", first, scnd, thrd, aux);

  if(read == 3 && (check_alpha(first) && check_alpha(thrd))) {
    if(!strcmp(scnd, "|")) {
      perform_operacion(alias, first, thrd, tabla, itree_unir);
    }else if(!strcmp(scnd, "&")) {
      perform_operacion(alias, first, thrd, tabla, itree_interseccion);
    }else if(!strcmp(scnd, "-")) {
      perform_operacion(alias, first, thrd, tabla, itree_diferencia);
    }else {
      printf("Error al definir operacion entre conjuntos\n");
    }
  }else if(first[0] == '~' && read == 1) {
    sscanf(first, "~%s", first);
    if(check_alpha(first)) {
      perform_complemento(alias, first, tabla);
    }else {
      printf("Error de sintaxis en complemento\n");
    }
  }else {
    printf("Error de sintaxis en la operación\n");
  }
}

void perform_insercion_comp(char alias[], int val1, int val2, TablaHash *tabla) {
  Interval intervalo = malloc(sizeof(Intervalo));
  intervalo->bgn = val1;
  intervalo->end = val2;
  ITree arbol = itree_crear();
  arbol = itree_insertar(arbol, intervalo);

  tablahash_eliminar(tabla, alias);
  tablahash_insertar(tabla, alias, arbol);

  free(intervalo);
}

void perform_insercion_ext(char alias[], char rest[], TablaHash* tabla) {
  char aux[256];
  int j = 0, flag = 1, f = 0, i;
  int array[256];
  if(!strcmp(rest, "}")) {
    ITree arbol = itree_crear();
    arbol = itree_insertar(arbol, NULL);
    tablahash_eliminar(tabla, alias);
    tablahash_insertar(tabla, alias, arbol);
  }else {
    if(rest[strlen(rest) - 1] == '}') {
      for (i = 0; rest[i] != '}' && flag; i++) {
        if (rest[i] != ',' && (isdigit(rest[i]) || rest[i] == '-')) {
          aux[j] = rest[i];
          j++;
        }else if (rest[i] == ',' && rest[i + 1] != ',') {
          aux[j] = '\0';
          array[f] = atoi(aux);
          f++;
          j = 0;
        }else {
          flag = 0;
        }
      }
      aux[j] = '\0';
      array[f] = atoi(aux);
      if(rest[i + 1] == '}')
        flag = 0;

      if(flag) {
        ITree arbol = itree_crear();
        Interval intervalo = malloc(sizeof(Intervalo));
        for(int i = 0; i <= f; i++) {
          intervalo->bgn = array[i];
          intervalo->end = array[i];
          arbol = itree_insertar(arbol, intervalo);
        }

        tablahash_eliminar(tabla, alias);
        tablahash_insertar(tabla, alias, arbol);
        free(intervalo);
      }else {
        printf("Caracter inválido en el conjunto\n");
      }
    } else {
      printf("Formato de conjunto por extensión inválido\n");
    }
  }
}

void define_insercion(char alias[], char set[], TablaHash *tabla) {
  char var1[256], var2[256], val1[256], val2[256], aux[256];
  aux[0] = '\0';
  int read, num1, num2;

  read = sscanf(set, "{%s : %s <= %s <= %s} %[^\n]", var1, val1, var2, val2, aux);

  if(read == 4) {
    num1 = atoi(val1);
    num2 = atoi(val2);
  }

  if(read == 4 && !strcmp(aux, "\0")) {
    if(!strcmp(var1, var2) && (!(strcmp(val1, "0") && num1 == 0) && !(strcmp(val2, "0") && num2 == 0)) && num1 <= num2) {
      perform_insercion_comp(alias, num1, num2, tabla);
    }else {
      printf("Formato inválido para conjunto por compresión\n");
    }
  }else {
    aux[0] = '\0';
    read = sscanf(set, "{%s %[^\n]", var1, aux);
    if(read == 1 && !strcmp(aux, "\0")) {
      perform_insercion_ext(alias, var1, tabla);
    }else {
      printf("Formato inválido para conjunto por extensión\n");
    }
  }
}

int main() {
  int end = 0, opcion, read;
  char buff[256], first[256], cond[256], rest[256];

  Interval intervalo = malloc(sizeof(Intervalo));
  ITree raiz = itree_crear();
  TablaHash* tabla = tablahash_crear(31, hash);

  while (!end) {
    printf("Ingrese un comando:\n");
    if(fgets(buff, 256, stdin) != NULL) {
      if(buff[strlen(buff) - 1] == '\n') {
        read = sscanf(buff, "%s %s %[^\n]", first, cond, rest);
      }else {
        for(char ch = getchar(); ch != '\n'; ch = getchar());
        printf("Excedio el limite de caracteres (254)\n");
      }
    }

    opcion = verificar_opcion(first, cond, rest, read);

    switch (opcion) {
    case SALIR:
      free(intervalo);
      itree_destruir(raiz);
      tablahash_destruir(tabla);
      end = 1;
      break;
    case IMPRIMIR:
      // raiz = tablahash_buscar(tabla, cond);
      // if(raiz != NULL) {
      //   itree_recorrer_dfs(raiz, imprimir_intervalo);
      // }else {
      //   printf("Esa clave no corresponde a ningun elemento\n");
      // }
      // raiz = NULL;

      for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
        if(tabla->tabla[idx].clave != NULL && tabla->tabla[idx].dato != NULL) {
          printf("%s", tabla->tabla[idx].clave);
          itree_recorrer_dfs(tabla->tabla[idx].dato, imprimir_intervalo);
          puts("");
        }else {
          printf("VACIO %d\n", idx);
        }
      }


      break;
    case OPERACION:
      define_operacion(first, rest, tabla);
      break;
    case INSERCION:
      define_insercion(first, rest, tabla);
      break;
    case ERROR:
      printf("Comando inválido\n");
      break;
    }
    puts("");
  }
}