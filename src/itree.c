#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "itree.h"

ITree itree_crear() {
  return NULL;
}

void itree_destruir(ITree arbol) {
  if (arbol != NULL) {
    free(arbol->intervalo);
    itree_destruir(arbol->left);
    itree_destruir(arbol->right);
    free(arbol);
  }
}

int intersectar(Interval i1, Interval i2) {
  return !(i1->end < i2->bgn || i2->end < i1->bgn);
}

int itree_altura(ITree arbol) {
  if (arbol == NULL)
    return -1;
  int sizeIzq = arbol->left == NULL ? -1 : arbol->left->alt;
  int sizeDer = arbol->right == NULL ? -1 : arbol->right->alt;
  return sizeIzq > sizeDer ? sizeIzq + 1 : sizeDer + 1;
}

int itree_balance_factor(ITree arbol) {
  return itree_altura(arbol->right) - itree_altura(arbol->left);
}

int itree_max_aux(int maySub, ITree nodo2) {
  if (nodo2 == NULL)
    return maySub;
  return maySub > nodo2->maySub ? maySub : nodo2->maySub;
}

int itree_max_sub(ITree nodo) {
  return itree_max_aux(itree_max_aux(nodo->intervalo->end, nodo->left), nodo->right);
}

ITree itree_rotacion_simple_der(ITree arbol) {
  ITree aux = arbol->left;
  arbol->left = aux->right;
  aux->right = arbol;
  if (aux->left != NULL)
    aux->left->maySub = itree_max_sub(aux->left);
  aux->right->maySub = itree_max_sub(aux->right);
  aux->right->alt = itree_altura(aux->right);
  aux->maySub = itree_max_sub(aux);
  aux->alt = itree_altura(aux);

  return aux;
}

ITree itree_rotacion_simple_izq(ITree arbol) {
  ITree aux = arbol->right;
  arbol->right = aux->left;
  aux->left = arbol;
  if (aux->right != NULL)
    aux->right->maySub = itree_max_sub(aux->right);
  aux->left->maySub = itree_max_sub(aux->left);
  aux->left->alt = itree_altura(aux->left);
  aux->maySub = itree_max_sub(aux);
  aux->alt = itree_altura(aux);

  return aux;
}

ITree itree_balancear_izq(ITree arbol) {
  if (itree_balance_factor(arbol->left) <= 0) {
    arbol = itree_rotacion_simple_der(arbol);
  }else {
    arbol->left = itree_rotacion_simple_izq(arbol->left);
    arbol = itree_rotacion_simple_der(arbol);
  }
  return arbol;
}

ITree itree_balancear_der(ITree arbol) {
  if (itree_balance_factor(arbol->right) >= 0) {
    arbol = itree_rotacion_simple_izq(arbol);
  }else {
    arbol->right = itree_rotacion_simple_der(arbol->right);
    arbol = itree_rotacion_simple_izq(arbol);
  }
  return arbol;
}

ITree create_node(Interval intervalo) {
  ITree nodo = malloc(sizeof(INode));
  if(intervalo != NULL) {
    nodo->intervalo = malloc(sizeof(Intervalo));
    nodo->intervalo->bgn = intervalo->bgn;
    nodo->intervalo->end = intervalo->end;
  }else {
    nodo->intervalo = NULL;
  }
  nodo->alt = 0;
  nodo->maySub = 0;
  nodo->left = NULL;
  nodo->right = NULL;
  return nodo;
}

int get_direccion_arbol(Interval nodo, Interval intervalo) {
  int inicio = 0;
  
  if(intervalo->bgn < nodo->bgn) {
    inicio = -1;
  }else if(intervalo->bgn > nodo->bgn) {
    inicio = 1;
  }

  if(inicio == 0) {
    if(intervalo->end < nodo->end) {
      inicio = -1;
    }else if(intervalo->end > nodo->end) {
      inicio = 1;
    }
  }
  
  // int inicio = intervalo->bgn - nodo->bgn;
  //  == 0 ? intervalo->end - nodo->end : inicio
  return inicio;
}

ITree itree_insertar(ITree arbol, Interval intervalo) {
  if (arbol == NULL)
    return create_node(intervalo);

  Interval restore = malloc(sizeof(Intervalo));
  restore->bgn = intervalo->bgn;
  restore->end = intervalo->end;

  if(intersectar(arbol->intervalo, intervalo)) {
    if(intervalo->bgn >= arbol->intervalo->bgn && intervalo->end <= arbol->intervalo->end) {
      free(restore);
      return arbol;
    }else if(intervalo->bgn >= arbol->intervalo->bgn && intervalo->bgn <= arbol->intervalo->end) {
      intervalo->bgn += (arbol->intervalo->end - intervalo->bgn) + 1;
    }else if(intervalo->end >= arbol->intervalo->bgn && intervalo->end <= arbol->intervalo->end) {
      intervalo->end -= (intervalo->end - arbol->intervalo->bgn) + 1;
    }else if(intervalo->bgn < arbol->intervalo->bgn && intervalo->end > arbol->intervalo->end) {
      Interval aux = malloc(sizeof(Intervalo));
      aux->bgn = intervalo->bgn;
      aux->end = arbol->intervalo->bgn - 1;
      intervalo->bgn = arbol->intervalo->end + 1;

      arbol = itree_insertar(arbol, aux);
      free(aux);
    }
  }
  int posicion = get_direccion_arbol(arbol->intervalo, intervalo);
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

  arbol->alt = itree_altura(arbol);

  intervalo->bgn = restore->bgn;
  intervalo->end = restore->end;
  free(restore);

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

  int posicion = get_direccion_arbol(arbol->intervalo, intervalo);

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

  if(arbol != NULL)
    arbol->alt -= 1;
  return arbol;
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

ITree itree_copiar(ITree newTree, ITree arbol) {
  if(arbol != NULL) {
    newTree = itree_insertar(newTree, arbol->intervalo);
    newTree = itree_copiar(newTree, arbol->left);
    newTree = itree_copiar(newTree, arbol->right);
  }

  return newTree;
}

ITree itree_unir(ITree arbol1, ITree arbol2, ITree newTree) {
  if(itree_altura(arbol1) >= itree_altura(arbol2)) {
    newTree = itree_copiar(newTree, arbol1);
    newTree = itree_copiar(newTree, arbol2);
  }else {
    newTree = itree_copiar(newTree, arbol2);
    newTree = itree_copiar(newTree, arbol1);
  }

  return newTree;
}

ITree itree_interseccion(ITree arbol1, ITree arbol2, ITree result) {
  if(arbol1 == NULL) {
    return result;
  }

  result = itree_interseccion_aux(arbol1->intervalo, arbol2, result);
  result = itree_interseccion(arbol1->left, arbol2, result);
  result = itree_interseccion(arbol1->right, arbol2, result);

  return result;
}

ITree itree_interseccion_aux(Interval intervalo, ITree arbol, ITree result) {
  if(arbol == NULL)
    return result;
  
  int posicion;
  Interval restore = malloc(sizeof(Intervalo));
  restore->bgn = intervalo->bgn;
  restore->end = intervalo->end;
  
  if(intersectar(arbol->intervalo, intervalo)) {
    Interval aux = malloc(sizeof(Intervalo));
    if(intervalo->bgn >= arbol->intervalo->bgn && intervalo->end <= arbol->intervalo->end) {
      result = itree_insertar(result, intervalo);
    }else if(intervalo->bgn >= arbol->intervalo->bgn && intervalo->bgn <= arbol->intervalo->end) {
      aux->bgn = intervalo->bgn;
      aux->end = arbol->intervalo->end;
      result = itree_insertar(result, aux);
      intervalo->bgn += (arbol->intervalo->end - intervalo->bgn) + 1;
    }else if(intervalo->end >= arbol->intervalo->bgn && intervalo->end <= arbol->intervalo->end) {
      aux->bgn = arbol->intervalo->bgn;
      aux->end = intervalo->end;
      result = itree_insertar(result, aux);
      intervalo->end -= (intervalo->end - arbol->intervalo->bgn) + 1;
    }else if(intervalo->bgn < arbol->intervalo->bgn && intervalo->end > arbol->intervalo->end) {
      aux->bgn = arbol->intervalo->bgn;
      aux->end = arbol->intervalo->end;
      result = itree_insertar(result, aux);
      aux->bgn = intervalo->bgn;
      aux->end = arbol->intervalo->bgn - 1;
      intervalo->bgn = arbol->intervalo->end + 1;
      posicion = get_direccion_arbol(arbol->intervalo, intervalo);
      if (posicion < 0) {
        result = itree_interseccion_aux(aux, arbol->left, result);
      } else if (posicion > 0) {
        result = itree_interseccion_aux(aux, arbol->right, result);
      }
    }
    free(aux);
  }

  posicion = get_direccion_arbol(arbol->intervalo, intervalo);
  if (posicion < 0) {
    result = itree_interseccion_aux(intervalo, arbol->left, result);
  } else if (posicion > 0) {
    result = itree_interseccion_aux(intervalo, arbol->right, result);
  }

  intervalo->bgn = restore->bgn;
  intervalo->end = restore->end;
  free(restore);

  return result;
}

ITree itree_complemento(ITree arbol, ITree result) {
  Interval intervalo = malloc(sizeof(Intervalo));
  intervalo->bgn = INT_MIN;
  intervalo->end = INT_MAX;
  result = itree_complemento_aux(arbol, intervalo, result);
  free(intervalo);
  return result;
}

ITree itree_complemento_aux(ITree arbol, Interval intervalo, ITree result) {
  if (arbol == NULL) {
    result = itree_insertar(result, intervalo);
    return result;
  }

  if(intersectar(arbol->intervalo, intervalo)) {
    if(intervalo->bgn >= arbol->intervalo->bgn && intervalo->end <= arbol->intervalo->end) {
      return result;
    }else if(intervalo->bgn >= arbol->intervalo->bgn && intervalo->bgn <= arbol->intervalo->end) {
      intervalo->bgn += (arbol->intervalo->end - intervalo->bgn) + 1;
    }else if(intervalo->end >= arbol->intervalo->bgn && intervalo->end <= arbol->intervalo->end) {
      intervalo->end -= (intervalo->end - arbol->intervalo->bgn) + 1;
    }else if(intervalo->bgn < arbol->intervalo->bgn && intervalo->end > arbol->intervalo->end) {
      Interval aux = malloc(sizeof(Intervalo));
      aux->bgn = intervalo->bgn;
      aux->end = arbol->intervalo->bgn - 1;
      intervalo->bgn = arbol->intervalo->end + 1;

      result = itree_complemento_aux(arbol, aux, result);
      free(aux);
    }
  }

  int posicion = get_direccion_arbol(arbol->intervalo, intervalo);
  if (posicion < 0) {
    result = itree_complemento_aux(arbol->left, intervalo, result);
  } else if (posicion > 0) {
    result = itree_complemento_aux(arbol->right, intervalo, result);
  }

  return result;
}

ITree itree_diferencia(ITree arbol1, ITree arbol2, ITree result) {
  if(arbol1 == NULL) {
    return result;
  }

  result = itree_diferencia_aux(arbol1->intervalo, arbol2, result);
  result = itree_diferencia(arbol1->left, arbol2, result);
  result = itree_diferencia(arbol1->right, arbol2, result);

  return result;
}

ITree itree_diferencia_aux(Interval intervalo, ITree arbol, ITree result) {
  if (arbol == NULL) {
    result = itree_insertar(result, intervalo);
    return result;
  }

  Interval restore = malloc(sizeof(Intervalo));
  restore->bgn = intervalo->bgn;
  restore->end = intervalo->end;

  if(intersectar(arbol->intervalo, intervalo)) {
    if(intervalo->bgn >= arbol->intervalo->bgn && intervalo->end <= arbol->intervalo->end) {
      free(restore);
      return result;
    }else if(intervalo->bgn >= arbol->intervalo->bgn && intervalo->bgn <= arbol->intervalo->end) {
      intervalo->bgn += (arbol->intervalo->end - intervalo->bgn) + 1;
    }else if(intervalo->end >= arbol->intervalo->bgn && intervalo->end <= arbol->intervalo->end) {
      intervalo->end -= (intervalo->end - arbol->intervalo->bgn) + 1;
    }else if(intervalo->bgn < arbol->intervalo->bgn && intervalo->end > arbol->intervalo->end) {
      Interval aux = malloc(sizeof(Intervalo));
      aux->bgn = intervalo->bgn;
      aux->end = arbol->intervalo->bgn - 1;
      intervalo->bgn = arbol->intervalo->end + 1;

      result = itree_diferencia_aux(aux, arbol, result);
      free(aux);
    }
  }

  int posicion = get_direccion_arbol(arbol->intervalo, intervalo);
  if (posicion < 0) {
    result = itree_diferencia_aux(intervalo, arbol->left, result);
  } else if (posicion > 0) {
    result = itree_diferencia_aux(intervalo, arbol->right, result);
  }

  intervalo->bgn = restore->bgn;
  intervalo->end = restore->end;
  free(restore);

  return result;
}