#include "itree.h"
#include <stdlib.h>
#include <stdio.h>

ITree itree_crear() {
  return NULL;
}

void itree_destruir(ITree arbol) {
  if (arbol != NULL) {
    itree_destruir(arbol->left);
    itree_destruir(arbol->right);
    free(arbol->intervalo);
    free(arbol);
  }
}

int itree_altura_aux(ITree arbol) {
  if (arbol == NULL)
    return 0;
  int sizeIzq = itree_altura_aux(arbol->left);
  int sizeDer = itree_altura_aux(arbol->right);
  return sizeIzq > sizeDer ? sizeIzq + 1 : sizeDer + 1;
}
// Cambiar altura para que respete las correcciones de valentina
// 1 - la altura empieza en 1?
// 2 - agregar un valor de altura a los nodos para no recalcular el arbol entero
int itree_altura(ITree arbol) {
  return arbol == NULL ? -1 : itree_altura_aux(arbol) - 1;
}

int itree_balance_factor(ITree arbol) {
  return itree_altura(arbol->right) - itree_altura(arbol->left);
}

double itree_max_aux(double maySub, ITree nodo2) {
  if (nodo2 == NULL)
    return maySub;
  return maySub > nodo2->maySub ? maySub : nodo2->maySub;
}

double itree_max_sub(ITree nodo) {
  return itree_max_aux(itree_max_aux(nodo->intervalo->end, nodo->left), nodo->right);
}

ITree itree_rotacion_simple_der(ITree arbol) {
  ITree aux = arbol->left;
  arbol->left = aux->right;
  aux->right = arbol;
  if (aux->left != NULL)
    aux->left->maySub = itree_max_sub(aux->left);
  aux->right->maySub = itree_max_sub(aux->right);
  aux->maySub = itree_max_sub(aux);
  return aux;
}

ITree itree_rotacion_simple_izq(ITree arbol) {
  ITree aux = arbol->right;
  arbol->right = aux->left;
  aux->left = arbol;
  if (aux->right != NULL)
    aux->right->maySub = itree_max_sub(aux->right);
  aux->left->maySub = itree_max_sub(aux->left);
  aux->maySub = itree_max_sub(aux);
  return aux;
}

ITree itree_balancear_izq(ITree arbol) {
  if (itree_balance_factor(arbol->left) <= 0)
    arbol = itree_rotacion_simple_der(arbol);
  else {
    arbol->left = itree_rotacion_simple_izq(arbol->left);
    arbol = itree_rotacion_simple_der(arbol);
  }
  return arbol;
}

ITree itree_balancear_der(ITree arbol) {
  if (itree_balance_factor(arbol->right) >= 0)
    arbol = itree_rotacion_simple_izq(arbol);
  else {
    arbol->right = itree_rotacion_simple_der(arbol->right);
    arbol = itree_rotacion_simple_izq(arbol);
  }
  return arbol;
}

ITree create_node(Interval intervalo) {
  ITree nodo = malloc(sizeof(INode));
  nodo->intervalo = malloc(sizeof(Intervalo));
  nodo->intervalo->bgn = intervalo->bgn;
  nodo->intervalo->end = intervalo->end;
  nodo->maySub = intervalo->end;
  nodo->left = NULL;
  nodo->right = NULL;
  return nodo;
}

double get_direccion_arbol(Interval nodo, Interval intervalo) {
  double inicio = intervalo->bgn - nodo->bgn;
  return inicio == 0 ? intervalo->end - nodo->end : inicio;
}

ITree itree_insertar(ITree arbol, Interval intervalo) {
  if (arbol == NULL)
    return create_node(intervalo);

  double posicion = get_direccion_arbol(arbol->intervalo, intervalo);
  if (posicion < 0) {
    arbol->left = itree_insertar(arbol->left, intervalo);
    arbol->maySub = itree_max_sub(arbol);
    if (itree_balance_factor(arbol) < -1)
      arbol = itree_balancear_izq(arbol);
  } else if (posicion > 0) {
    arbol->right = itree_insertar(arbol->right, intervalo);
    arbol->maySub = itree_max_sub(arbol);
    if (itree_balance_factor(arbol) > 1)
      arbol = itree_balancear_der(arbol);
  }

  return arbol;
}

ITree itree_minimo(ITree arbol) {
  while (arbol->left != NULL)
    arbol = arbol->left;
  return arbol;
}

ITree itree_eliminar(ITree arbol, Interval intervalo) {
  if (arbol == NULL)
    return arbol;

  double posicion = get_direccion_arbol(arbol->intervalo, intervalo);

  if (posicion == 0) {
    ITree aux = arbol;
    if (arbol->left != NULL && arbol->right != NULL) {
      aux = itree_minimo(arbol->right);

      Interval i = arbol->intervalo;
      arbol->intervalo = aux->intervalo;
      aux->intervalo = i;

      arbol->right = itree_eliminar(arbol->right, aux->intervalo);
      if (itree_balance_factor(arbol) < -1)
        arbol = itree_balancear_izq(arbol);
      arbol->maySub = itree_max_sub(arbol);
    } else {
      arbol = arbol->left == NULL ? arbol->right : arbol->left;
      free(aux->intervalo);
      free(aux);
    }
  } else if (posicion < 0) {
    arbol->left = itree_eliminar(arbol->left, intervalo);
    arbol->maySub = itree_max_sub(arbol);
    if (itree_balance_factor(arbol) > 1)
      arbol = itree_balancear_der(arbol);
  } else {
    arbol->right = itree_eliminar(arbol->right, intervalo);
    arbol->maySub = itree_max_sub(arbol);
    if (itree_balance_factor(arbol) < -1)
      arbol = itree_balancear_izq(arbol);
  }
  return arbol;
}

int intersectar(Interval i1, Interval i2) {
  return !(i1->end < i2->bgn || i2->end < i1->bgn);
}

Interval itree_intersectar(ITree arbol, Interval intervalo) {
  if (arbol != NULL) {
    if (intersectar(arbol->intervalo, intervalo))
      return arbol->intervalo;
    if (arbol->left != NULL && arbol->left->maySub >= intervalo->bgn)
      return itree_intersectar(arbol->left, intervalo);
    if (intervalo->end > arbol->intervalo->bgn)
      return itree_intersectar(arbol->right, intervalo);
  }
  return NULL;
}

void itree_recorrer_dfs(ITree arbol, FuncionVisitante visit) {
  if (arbol != NULL) {
    visit(arbol->intervalo);
    itree_recorrer_dfs(arbol->left, visit);
    itree_recorrer_dfs(arbol->right, visit);
  }
}
