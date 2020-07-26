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

/*
* Crea un arbol de intervalos vacío
*/
ITree itree_crear();

/*
* Elimina un arbol de intervalos y sus contenidos
*/
void itree_destruir(ITree arbol);

/*
* Calcula y devuelve la altura de un nodo mediante sus hijos
*/
int itree_altura(ITree arbol);

/*
* Devuelve el factor por el cual se decidira si el arbol esta balanceado
*/
int itree_balance_factor(ITree arbol);

/*
* Inserta el intervalo dado en el arbol
*/
ITree itree_insertar(ITree arbol, Interval intervalo);

/*
* Elmina (de existir) el intervalo dado del arbol
*/
ITree itree_eliminar(ITree arbol, Interval intervalo);

/*
* Devuelve (de existir) el intervalo del arbol con el cual el
* intervalo dado se interseca
*/
Interval itree_intersectar(ITree arbol, Interval intervalo);

/*
* Realiza el recorrido inorder del arbol dado visitando cada nodo
* mediante una funcion visitante
*/
void itree_recorrer(ITree arbol, FuncionVisitante visit);

/*
* Une dos arboles y devuelve el arbol resultante
*/
ITree itree_unir(ITree arbol1, ITree arbol2, ITree newTree);

/*
* Funcion auxiliar para itree_unir, copia un arbol en el otro y devuelve
* el resultado
*/
ITree itree_copiar(ITree newTree, ITree arbol);

/*
* Intersecta dos arboles y devuelve el arbol resultante
*/
ITree itree_interseccion(ITree arbol1, ITree arbol2, ITree result);

/*
* Función auxiliar para itree_interseccion, realiza la comparación de
* un intervalo con un arbol para determinar qué intervalos se intersecan y
* luego insertar dichos intervalos en el arbol resultado
*/
ITree itree_interseccion_aux(Interval intervalo, ITree arbol, ITree result);

/*
* Realiza el complemento de un arbol y devuelve el arbol resultante
*/
ITree itree_complemento(ITree arbol, ITree result);

/*
* Funcion auxiliar para itree_complemento, compara el intervalo mas amplio posible
* con el arbol para insertar en el resultado aquellas partes del intervalo que
* no esten presentes en el arbol a comparar
*/
ITree itree_complemento_aux(ITree arbol, Interval intervalo, ITree result);

/*
* Realiza la diferencia entre dos arboles y devuelve el arbol resultante
*/
ITree itree_diferencia(ITree arbol1, ITree arbol2, ITree result);

/*
* Funcion auxiliar para itree_diferencia, compara un intervalo con el arbol para insertar
* en el resultado aquellas partes del intervalo que no esten presentes en el arbol 
* a comparar
*/
ITree itree_diferencia_aux(Interval intervalo, ITree arbol, ITree result);

#endif
