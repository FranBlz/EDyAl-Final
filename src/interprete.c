#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "conjuntos.h"

#define INSERCION 3
#define OPERACION 2
#define IMPRIMIR 1
#define SALIR 0
#define ERROR -1

int string_to_int(char* str) {
  int sign = 1, base = 0, i = 0, flag = 1; 
  if (str[i] == '-') { 
    sign = -1;
    i++; 
  } 

  for (;str[i] != '\0' && flag; i++) {
    base = 10 * base + (str[i] - '0');
    if(!isdigit(str[i]))
      flag = 0;
  }
  
  return (base > INT_MAX || base < INT_MIN) ? 0 : base * sign * flag;
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
  if (first[0] == '\0') {
    return ERROR;
  }else if (!strcmp(first, "salir")) {
    if (read == 1)
      return SALIR;
  }else if (!strcmp(first, "imprimir")) {
    if(read == 2 && check_alpha(cond))
      return IMPRIMIR;
  }else if(read == 3 && check_alpha(first) && !strcmp(cond, "=")) {
    if(rest[0] == '{') {
      return INSERCION;
    }else {
      return OPERACION;
    }
  }
  return ERROR;
}

void define_operacion(char alias[], char op[], TablaHash *tabla) {
  char first[256], scnd[256], thrd[256], aux[256];
  int read;

  read = sscanf(op, "%s %s %s %[^\n]", first, scnd, thrd, aux);

  if(read == 3 && (check_alpha(first) && check_alpha(thrd))) {
    if(!strcmp(scnd, "|")) {
      perform_operacion(alias, first, thrd, tabla, 1);
    }else if(!strcmp(scnd, "&")) {
      perform_operacion(alias, first, thrd, tabla, 2);
    }else if(!strcmp(scnd, "-")) {
      perform_operacion(alias, first, thrd, tabla, 3);
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

void check_insercion_ext(char alias[], char rest[], TablaHash* tabla) {
  char aux[256];
  int j = 0, flag = 1, f = 0, i;
  int array[256];
  if(!strcmp(rest, "}")) {
    perform_insercion_ext(alias, array, f, tabla);
  }else {
    if(rest[strlen(rest) - 1] == '}') {
      for (i = 0; rest[i] != '\0' && flag; i++) {
        if (rest[i] != ',' && (isdigit(rest[i]) || rest[i] == '-')) {
          if(rest[i] == '-' && j != 0)
            flag = 0;
          aux[j] = rest[i];
          j++;
        }else if ((rest[i] == ',' && (isdigit(rest[i + 1]) || rest[i + 1] == '-')) || (rest[i] == '}' && rest[i + 1] == '\0')) {
          aux[j] = '\0';
          array[f] = string_to_int(aux);
          if(array[f] == 0 && strcmp(aux, "0"))
            flag = 0;
          j = 0;
          f++;
        }else {
          flag = 0;
        }
      }

      if(flag) {
        perform_insercion_ext(alias, array, f, tabla);
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
  int read, num1, num2;

  read = sscanf(set, "{%s : %s <= %s <= %s %[^\n]", var1, val1, var2, val2, aux);

  if(read == 4) {
    int temp = read;
    read = 0;
    if(val2[strlen(val2) - 1] == '}') {
      unsigned i;
      for(i = 0; isdigit(val2[i]) || val2[i] == '-'; i++);
      if(i == strlen(val2) - 1) {
        val2[i] = '\0';
        read = temp;
      }
    }
  }

  if(read == 4) {
    num1 = string_to_int(val1);
    num2 = string_to_int(val2);

    int i;
    char c1, c2;
    for(i = 0, c1 = var1[i]; isalpha(c1); c1 = var1[i++]);
    for(i = 0, c2 = var2[i]; isalpha(c2); c2 = var2[i++]);

    if(c1 != '\0' || c2 != '\0')
      read = 0;  
  }

  if(read == 4) {
    if(!strcmp(var1, var2) && (!(strcmp(val1, "0") && num1 == 0) && !(strcmp(val2, "0") && num2 == 0)) && num1 <= num2) {
      perform_insercion_comp(alias, num1, num2, tabla);
    }else {
      printf("Comando inválido para inserción de conjunto\n");
    }
  }else {
    aux[0] = '\0';
    read = sscanf(set, "{%s %[^\n]", var1, aux);
    if(read == 1) {
      check_insercion_ext(alias, var1, tabla);
    }else {
      printf("Comando inválido para inserción de conjunto\n");
    }
  }
}

int main() {
  int end = 0, opcion, read;
  char buff[256], first[256], cond[256], rest[256];
  first[0] = '\0';

  TablaHash* tabla = conjuntos_iniciar();

  while (!end) {
    // printf("Ingrese un comando:\n");
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
      conjunto_destruir(tabla);
      end = 1;
      break;
    case IMPRIMIR:
      imprimir_conjunto(cond, tabla);
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