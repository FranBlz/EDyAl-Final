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

typedef void (*FuncionVisitante) (Interval dato);

ITree itree_crear();

void itree_destruir(ITree arbol);

int itree_altura(ITree arbol);

int itree_balance_factor(ITree arbol);

ITree itree_insertar(ITree arbol, Interval intervalo);

ITree itree_eliminar(ITree arbol, Interval intervalo);

Interval itree_intersectar(ITree arbol, Interval intervalo);

void itree_recorrer(ITree arbol, FuncionVisitante visit);

ITree itree_unir(ITree arbol1, ITree arbol2, ITree newTree);
ITree itree_copiar(ITree newTree, ITree arbol);

ITree itree_interseccion(ITree arbol1, ITree arbol2, ITree result);
ITree itree_interseccion_aux(Interval intervalo, ITree arbol, ITree result);

ITree itree_complemento(ITree arbol, ITree result);
ITree itree_complemento_aux(ITree arbol, Interval intervalo, ITree result);

ITree itree_diferencia(ITree arbol1, ITree arbol2, ITree result);
ITree itree_diferencia_aux(Interval intervalo, ITree arbol, ITree result);

#endif
