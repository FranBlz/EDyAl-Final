#ifndef __CONJUNTOS_H__
#define __CONJUNTOS_H__

#include "tablahash.h"
#include "itree.h"

TablaHash* conjuntos_iniciar();

void conjunto_destruir(TablaHash* tabla);

void imprimir_conjunto(char alias[], TablaHash* tabla);

void perform_operacion(char alias[], char set1[], char set2[], TablaHash* tabla, int op);

void perform_complemento(char alias[], char set[], TablaHash* tabla);

void perform_insercion_comp(char alias[], int val1, int val2, TablaHash *tabla);

void perform_insercion_ext(char alias[], int array[], int cantElem, TablaHash *tabla);

#endif