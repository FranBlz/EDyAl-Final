#include "itreeTest.h"
#include <stdlib.h>

void test_altura_itree(void){

    CU_ASSERT_EQUAL(itree_altura(NULL), -1);

    Interval intervalo = malloc(sizeof(Intervalo));
    intervalo->bgn = 30;
    intervalo->end = 30;
    ITree raiz = itree_insertar(NULL, intervalo);

    CU_ASSERT_EQUAL(itree_altura(raiz), 0);

    intervalo->bgn = 5;
    intervalo->end = 5;
    raiz = itree_insertar(raiz, intervalo);

    intervalo->bgn = 35;
    intervalo->end = 35;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 32;
    intervalo->end = 32;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 40;
    intervalo->end = 40;
    raiz = itree_insertar(raiz, intervalo);

    CU_ASSERT_EQUAL(itree_altura(raiz), 2);
    intervalo->bgn = 4;
    intervalo->end = 4;
    raiz = itree_insertar(raiz, intervalo);

    intervalo->bgn = 6;
    intervalo->end = 6;
    raiz = itree_insertar(raiz, intervalo);

    intervalo->bgn = 7;
    intervalo->end = 7;
    raiz = itree_insertar(raiz, intervalo);

    CU_ASSERT_EQUAL(itree_altura(raiz), 3);

    itree_destruir(raiz);
    free(intervalo);
}

void test_altura_balanceo_simple_der(void) {
    ITree raiz = itree_crear();
    Interval intervalo = malloc(sizeof(Intervalo));

    intervalo->bgn = 7;
    intervalo->end = 7;    
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 6;
    intervalo->end = 6;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 8;
    intervalo->end = 8;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 5;
    intervalo->end = 5;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 4;
    intervalo->end = 4;
    raiz = itree_insertar(raiz, intervalo);

    CU_ASSERT_EQUAL(itree_altura(raiz), 2);
    CU_ASSERT_EQUAL(itree_altura(raiz->left), 1);
    CU_ASSERT_EQUAL(itree_altura(raiz->left->left), 0);
    CU_ASSERT_EQUAL(itree_altura(raiz->left->right), 0);

    itree_destruir(raiz);
    free(intervalo);
}

void test_altura_balanceo_simple_izq(void) {
    ITree raiz = itree_crear();
    Interval intervalo = malloc(sizeof(Intervalo));

    intervalo->bgn = 7;
    intervalo->end = 7;    
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 6;
    intervalo->end = 6;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 8;
    intervalo->end = 8;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 9;
    intervalo->end = 9;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 10;
    intervalo->end = 10;
    raiz = itree_insertar(raiz, intervalo);

    CU_ASSERT_EQUAL(itree_altura(raiz), 2);
    CU_ASSERT_EQUAL(itree_altura(raiz->right), 1);
    CU_ASSERT_EQUAL(itree_altura(raiz->right->right), 0);
    CU_ASSERT_EQUAL(itree_altura(raiz->right->left), 0);

    itree_destruir(raiz);
    free(intervalo);
}

void test_altura_balanceo_doble_izq(void) {
    ITree raiz = itree_crear();
    Interval intervalo = malloc(sizeof(Intervalo));

    intervalo->bgn = 10;
    intervalo->end = 10;    
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 5;
    intervalo->end = 5;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 11;
    intervalo->end = 11;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 4;
    intervalo->end = 4;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 6;
    intervalo->end = 6;
    raiz = itree_insertar(raiz, intervalo);

    intervalo->bgn = 7;
    intervalo->end = 7;
    raiz = itree_insertar(raiz, intervalo);

    CU_ASSERT_EQUAL(itree_altura(raiz), 2);
    CU_ASSERT_EQUAL(itree_altura(raiz->right), 1);
    CU_ASSERT_EQUAL(itree_altura(raiz->left->left), 0);
    CU_ASSERT_EQUAL(itree_altura(raiz->left), 1);

    itree_destruir(raiz);
    free(intervalo);
}

void test_altura_balanceo_doble_der(void) {
    ITree raiz = itree_crear();
    Interval intervalo = malloc(sizeof(Intervalo));

    intervalo->bgn = 10;
    intervalo->end = 10;    
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 5;
    intervalo->end = 5;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 16;
    intervalo->end = 16;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 4;
    intervalo->end = 4;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 6;
    intervalo->end = 6;
    raiz = itree_insertar(raiz, intervalo);

    intervalo->bgn = 19;
    intervalo->end = 19;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 18;
    intervalo->end = 18;
    raiz = itree_insertar(raiz, intervalo);

    CU_ASSERT_EQUAL(itree_altura(raiz), 2);
    CU_ASSERT_EQUAL(itree_altura(raiz->right), 1);
    CU_ASSERT_EQUAL(itree_altura(raiz->right->left), 0);
    CU_ASSERT_EQUAL(itree_altura(raiz->right->right), 0);

    itree_destruir(raiz);
    free(intervalo);
}

void test_altura_eliminacion_simple(void) {
    ITree raiz = itree_crear();
    Interval intervalo = malloc(sizeof(Intervalo));

    intervalo->bgn = 16;
    intervalo->end = 16;    
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 5;
    intervalo->end = 5;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 25;
    intervalo->end = 25;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 0;
    intervalo->end = 0;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 8;
    intervalo->end = 8;
    raiz = itree_insertar(raiz, intervalo);

    intervalo->bgn = 17;
    intervalo->end = 17;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 26;
    intervalo->end = 26;
    raiz = itree_insertar(raiz, intervalo);

    intervalo->bgn = 6;
    intervalo->end = 6;
    raiz = itree_insertar(raiz, intervalo);

    intervalo->bgn = 0;
    intervalo->end = 0;
    raiz = itree_eliminar(raiz, intervalo);

    CU_ASSERT_EQUAL(itree_altura(raiz), 2);
    CU_ASSERT_EQUAL(itree_altura(raiz->right), 1);
    CU_ASSERT_EQUAL(itree_altura(raiz->right->left), 0);
    CU_ASSERT_EQUAL(itree_altura(raiz->right->right), 0);

    itree_destruir(raiz);
    raiz = NULL;
    intervalo->bgn = 9;
    intervalo->end = 9;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 5;
    intervalo->end = 5;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 10;
    intervalo->end = 10; 
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 0;
    intervalo->end = 0;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 6;
    intervalo->end = 6;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 11;
    intervalo->end = 11;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = -1;
    intervalo->end = -1;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 1;
    intervalo->end = 1;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 2;
    intervalo->end = 2;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 10;
    intervalo->end = 10; 
    raiz = itree_eliminar(raiz, intervalo);


    CU_ASSERT_EQUAL(itree_altura(raiz), 3);
    CU_ASSERT_EQUAL(itree_altura(raiz->right), 2);
    CU_ASSERT_EQUAL(itree_altura(raiz->right->right), 0);
    CU_ASSERT_EQUAL(itree_altura(raiz->left), 1);

    itree_destruir(raiz);
    free(intervalo);
}

void test_altura_eliminacion_doble(void) {
    Interval intervalo = malloc(sizeof(Intervalo));
    ITree raiz = itree_crear();
    intervalo->bgn = 10;
    intervalo->end = 10;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 5;
    intervalo->end = 5;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 11;
    intervalo->end = 11;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 12;
    intervalo->end = 12;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 4;
    intervalo->end = 4;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 8;
    intervalo->end = 8;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 7;
    intervalo->end = 7;
    raiz = itree_insertar(raiz, intervalo);
    
    intervalo->bgn = 12;
    intervalo->end = 12;

    raiz = itree_eliminar(raiz, intervalo);

    CU_ASSERT_EQUAL(itree_altura(raiz), 2);
    CU_ASSERT_EQUAL(itree_altura(raiz->left), 1);
    CU_ASSERT_EQUAL(itree_altura(raiz->right), 1);

    itree_destruir(raiz);
    raiz = itree_crear();
    intervalo->bgn = 10;
    intervalo->end = 10;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 6;
    intervalo->end = 6;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 17;
    intervalo->end = 17;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 3;
    intervalo->end = 3;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 15;
    intervalo->end = 15;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 19;
    intervalo->end = 19;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 14;
    intervalo->end = 14;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 16;
    intervalo->end = 16;
    raiz = itree_insertar(raiz, intervalo);
    intervalo->bgn = 3;
    intervalo->end = 3;
    raiz = itree_eliminar(raiz, intervalo);

    CU_ASSERT_EQUAL(itree_altura(raiz), 2);
    CU_ASSERT_EQUAL(itree_altura(raiz->left), 1);
    CU_ASSERT_EQUAL(itree_altura(raiz->right), 1);

    itree_destruir(raiz);
    free(intervalo);
}