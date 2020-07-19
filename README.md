# EDyAl-Final

## Notas:
* mandar consulta con dudas
* hacer el interprete
* hacer interseccion, resta y complemento
* mejorar tests
* ADVERTENCIA: revisar en insertar la necesidad de restore, considerar otras opciones para preservar el intervalo
* ADVERTENCIA: revisar union, interseccion e insertar
    * union podria optimizarse quiza
    * interseccion tiene demasiadas funciones aux y similitud con insertar, chequear mas casos
    * insertar tiene variables al pedo y codigo repetido?
* ADVERTENCIA: para usar itree tengo que arreglar todos los errores que me dijeron en ese tp (chequear balance al pedo, revisar balance para mantener alturas, etc)

* NO OLVIDAR:
    * revisar insertar para poner una bandera
    * cambiar funciones hash1 y hash2 por algunas mas consistentes (sobretodo hash2)
    * para ingresar un conjunto con nombre ya ocupado, generar el arbol nuevo, borrar el indice anterior y luego insertar
    * considerar linear probing con un indice de carga bajo y una buena funcion de hash inicial
    * definir un tipo de open adressing para la tabla hash
    * modificar la tabla hash para que la busqueda y eliminacion tambien usen el modelo de open adressing
    * si busco un elemento que no esta, y hago una operacion, esta se hace con NULL, lo cual no es correcto (modificar la busqueda o algo para que se distinga un elemento que no existe ocn uno vacio)
    * agregar modificaciones necesarias para lograr la existencia y buen comportamiento de conjuntos vacios
    * atento al error de obtener basura en scnd