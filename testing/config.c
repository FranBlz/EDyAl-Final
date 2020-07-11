#include <CUnit/CUnit.h>
#include "hashTest.h"
#include "treeTest.h"
#include "itreeTest.h"

typedef void (*TipoFunciones) (void);

int initialise_suite(void)
{
   return 0;
}

int cleanup_suite(void)
{
  return 0;
}

int correr_tests(char* nombre_suite, TipoFunciones funciones[], char *nombre_funciones[], int cant_funciones){
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    CU_pSuite suite = CU_add_suite(nombre_suite, initialise_suite, cleanup_suite);
    if (NULL == suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    for(int i=0; i < cant_funciones; i++){
        if(NULL == CU_add_test(suite, nombre_funciones[i], funciones[i])){
            CU_cleanup_registry();
            return CU_get_error();
        } 
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    return CU_get_number_of_tests_failed();
}

int hash_suite(){
    TipoFunciones funciones[] = {
        test_prueba_1,
        test_prueba_2
    };

    char *nombre_funciones[] = {
        "test_prueba_1",
        "test_prueba_2"
    };

    int cant_funciones = 2;
    
    return correr_tests("Hash suite", funciones, nombre_funciones, cant_funciones);
}

int tree_suite(){
    TipoFunciones funciones[] = {
        test_prueba_3,
        test_prueba_4
    };

    char *nombre_funciones[] = {
        "test_prueba_3",
        "test_prueba_4"
    };

    int cant_funciones = 2;
    
    return correr_tests("Tree suite", funciones, nombre_funciones, cant_funciones);
}

int itree_suite(){
    TipoFunciones funciones[] = {
        test_altura_itree,
        test_altura_balanceo_simple_izq,
        test_altura_balanceo_simple_der,
        test_altura_balanceo_doble_izq,
        test_altura_balanceo_doble_der
    };

    char *nombre_funciones[] = {
        "Test altura",
        "Test altura despues de balanceo simple a la izquierda",
        "Test altura despues de balanceo simple a la derecha",
        "Test altura despues de balanceo doble a la izquierda",
        "Test altura despues de balanceo doble a la derecha",
    };

    int cant_funciones = 5;
    
    return correr_tests("Arbol de intervalos", funciones, nombre_funciones, cant_funciones);
}

int main(){

    int failed_test = 0;
    failed_test += hash_suite();
    failed_test += tree_suite();
    failed_test += itree_suite();

    CU_cleanup_registry();

    return failed_test;
}
