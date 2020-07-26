#ifndef __CONJUNTOS_H__
#define __CONJUNTOS_H__

#include "tablahash.h"
#include "itree.h"

/* 
* Crea un conjunto vacío
*/
TablaHash *conjuntos_iniciar();

/* 
* Destruye un conjunto
*/
void conjunto_destruir(TablaHash *tabla);

/* 
* Imprime el conjunto de nombre "alias"
*/
void imprimir_conjunto(char alias[], TablaHash *tabla);

/* 
* Lleva a cabo la operación pedida con los conjuntos dados
* y almacena el resultado en la tabla
*/
void perform_operacion(char alias[], char set1[], char set2[],
                       TablaHash *tabla, int op);

/* 
* Lleva a cabo el complemento pedido y lo almacena en la tabla
*/
void perform_complemento(char alias[], char set[], TablaHash *tabla);

/* 
* Lleva a cabo la insercion en la tabla de un conjunto por compresión
*/
void perform_insercion_comp(char alias[], int val1, int val2,
                        TablaHash *tabla);

/*
* Lleva a cabo la insercion en la tabla de un conjunto por extension
*/
void perform_insercion_ext(char alias[], int array[], int cantElem,
                        TablaHash *tabla);

#endif
