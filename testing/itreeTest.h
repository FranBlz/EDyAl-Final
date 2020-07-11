#ifndef __ITREETEST_H__
#define __ITREETEST_H__

#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include "itree.h"

void test_altura_itree(void);
void test_altura_balanceo_simple_der(void);
void test_altura_balanceo_simple_izq(void);
void test_altura_balanceo_doble_izq(void);
void test_altura_balanceo_doble_der(void);
void test_altura_eliminacion_simple(void);
void test_altura_eliminacion_doble(void);


#endif