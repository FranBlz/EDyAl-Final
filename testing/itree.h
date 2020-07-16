#ifndef __ITREE_H__
#define __ITREE_H__

typedef struct _Intervalo {
  int bgn;
  int end;
} Intervalo;

typedef Intervalo *Interval;

typedef struct _INode {
  Interval intervalo;
  int alt;
  double maySub;
  struct _INode *left;
  struct _INode *right;
} INode;

typedef INode *ITree;

typedef void (*FuncionVisitante)(Interval dato);

/**
 * Crea y devuelve un arbol de intervalos
**/
ITree itree_crear();

/**
 * Destruye todos los elementos del arbol de intervalos
**/
void itree_destruir(ITree arbol);

/**
 * Devuelve la altura del arbol
**/
int itree_altura(ITree arbol);

/**
 * Devuelve el factor por el cual se decidira si el arbol esta balanceado
**/
int itree_balance_factor(ITree arbol);

/**
 * Inserta el intervalo indicado al arbol
**/
ITree itree_insertar(ITree arbol, Interval intervalo);

/**
 * Elimina (de existir) el intervalo indicado del arbol
**/
ITree itree_eliminar(ITree arbol, Interval intervalo);

/**
 * Devuelve (de existir) el intervalo del arbol con el cual el
 * intervalo dado se interseca
**/
Interval itree_intersectar(ITree arbol, Interval intervalo);

/**
 * Recorre el arbol por altura
**/
void itree_recorrer_dfs(ITree arbol, FuncionVisitante visit);

ITree itree_copiar(ITree newTree, ITree arbol);

ITree itree_unir(ITree arbol1, ITree arbol2);

ITree itree_interseccion(ITree arbol1, ITree arbol2);
ITree itree_interseccion_aux1(ITree arbol1, ITree arbol2, ITree result);
ITree itree_interseccion_aux2(Interval intervalo, ITree arbol, ITree result);

ITree itree_complemento(ITree arbol);
ITree itree_complemento_aux(ITree result, ITree arbol, Interval intervalo);

ITree itree_diferencia(ITree arbol1, ITree arbol2);
ITree itree_diferencia_aux1(ITree arbol1, ITree arbol2, ITree result);
ITree itree_diferencia_aux2(Interval intervalo, ITree arbol, ITree result);

#endif
