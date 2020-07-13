#include <stdio.h>
#include <stdlib.h>
#include "tablahash.h"

unsigned hash(char* clave) {  
  int p = 7;
  for(int i = 0; clave[i] != '\0'; i++)
    p = p*31 + clave[i]; //si no anda el hash es por esto (quizas)
  return p;
}

int main() {
  int n, end = 0;
  char keyBuff[256];
  Interval iBuff[256];
  TablaHash *th = tablahash_crear(31, hash);

  while (!end) {
    scanf("%[^\n]", iBuff);
    getchar();
  }

  tablahash_destruir(th);

  return 0;
}









#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "itree.h"

#define CANT_OPCIONES 6
#define MAX_DIGITS_DOUBLE 320

#define OPCION_INCORRECTA -1
#define FORMATO_INTERVALO_INCORRECTO -2
#define DATOS_INNECESARIOS -3
#define INICIO_MAYOR_QUE_FIN -4
#define FALTA_OPCION -5
#define FALTA_INTERVALO -6

/**
 * Imprime en pantalla los extremos del intervalo dado
**/
static void imprimir_intervalo(Interval intervalo) {
  printf("[%g, %g] ", intervalo->bgn, intervalo->end);
}

/**
 * Verifica que la opcion indicada en la entrada por terminal sea apta
**/
int verificar_opcion(char opcion[], char *opciones[], int cantOpciones) {
  if (opcion == NULL)
    return FALTA_OPCION;
  int i;
  for (i = 0; i < cantOpciones && strcmp(opciones[i], opcion) != 0; i++);
  return i == cantOpciones ? OPCION_INCORRECTA : i;
}

/**
 * Procesa la entrada por terminal para obtener el intervalo en double
 * Tambien retorna los errores correspondientes de haberlos
**/
int get_intervalo(Interval intervalo, int opcion) {
  char *buf = strtok(NULL, "");
  if (buf == NULL)
    return FALTA_INTERVALO;

  if (buf[0] != '[' || !(isdigit(buf[1]) || buf[1] == '-'))
    return FORMATO_INTERVALO_INCORRECTO;

  intervalo->bgn = strtod(buf + 1, &buf);

  if (buf[0] != ',' || buf[1] != ' ' || !(isdigit(buf[2]) || buf[2] == '-'))
    return FORMATO_INTERVALO_INCORRECTO;

  intervalo->end = strtod(buf + 2, &buf);

  if (buf[0] != ']')
    return FORMATO_INTERVALO_INCORRECTO;

  if (buf[1] != '\0')
    return DATOS_INNECESARIOS;

  return intervalo->bgn <= intervalo->end ? opcion : INICIO_MAYOR_QUE_FIN;
}


void interprete(char *opciones[], int cantOpciones) {
  int end = 0, opcion;
  char buf[MAX_DIGITS_DOUBLE * 2 + 20];
  char *ptr;

  Interval intervalo = malloc(sizeof(Intervalo)), resultado;
  ITree raiz = itree_crear();

  while (!end) {
    scanf("%[^\n]", buf);
    getchar();

    ptr = strtok(buf, " ");

    opcion = verificar_opcion(ptr, opciones, cantOpciones);

    if (0 <= opcion && opcion <= 2)
      opcion = get_intervalo(intervalo, opcion);
    else if (3 <= opcion && opcion <= 5){
      ptr = strtok(NULL, "");
      if (ptr != NULL)
        opcion = DATOS_INNECESARIOS;
    }

    switch (opcion) {
    case 0:
      raiz = itree_insertar(raiz, intervalo);
      break;
    case 1:
      raiz = itree_eliminar(raiz, intervalo);
      break;
    case 2:
      resultado = itree_intersectar(raiz, intervalo);
      if (resultado != NULL) {
        printf("Si, ");
        imprimir_intervalo(resultado);
      } else
        printf("No");
      puts("");
      break;
    case 3:
      itree_recorrer_dfs(raiz, imprimir_intervalo);
      puts("");
      break;
    case 4:
      itree_recorrer_bfs(raiz, imprimir_intervalo);
      puts("");
      break;
    case 5:
      end = 1;
      break;
    case OPCION_INCORRECTA:
      printf("Por favor, ingrese una opcion correcta. Las opciones son:\n");
      for (int i = 0; i < cantOpciones; i++)
        printf("%s\n", opciones[i]);
      break;
    case FORMATO_INTERVALO_INCORRECTO:
      printf("Por favor, ingrese el intervalo en un formato correcto. El formato esperado es:\n"
           "[inicio, fin]\n"
           "siendo cada uno de los extremos un numero con su parte decimal separada por .\n"
           "Ejemplo: [2.34, 6.21]\n");
      break;
    case DATOS_INNECESARIOS:
      printf("Por favor, no ingrese mas datos que los indicados (incluyendo espacios).\n");
      break;
    case INICIO_MAYOR_QUE_FIN:
      printf("Por favor, ingrese un intervalo donde el inicio sea menor o igual que el fin\n");
      break;
    case FALTA_OPCION:
      printf("Por favor, ingrese un comando\n");
      break;
    case FALTA_INTERVALO:
      printf("Por favor, ingrese un intervalo junto con el comando.\n"
             "Ejemplo: 'i [a, b]' siendo a y b números válidos\n");
      break;
    }
  }

  free(intervalo);
  itree_destruir(raiz);
}

int main() {
  char *opciones[] = {
    "i",
    "e",
    "?",
    "dfs",
    "bfs",
    "salir"
  };

  interprete(opciones, CANT_OPCIONES);
  return 0;
}