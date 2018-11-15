Modo de compilación:

gcc polinomio.c -o polinomio.out -lm -std=c99

Modo de ejecutar:

- Modo ejecución Normal (suma,resta y multiplicaciones): 
	./polinomio.out GradoPolinomio1 GradoPolinomio2
- Modo comparación de métodos:
	./polinomio.out

ex:

time ./polinomio.out 150 100

Donde el primer polinomio será grado 150 y el segundo grado 100.

IMPORTANTE:

- Para cambiar los parámetros de comparación (largo de las listas y grado límite) se deben editar las constantes globales largoListaComparaciones y limiteGrdComparaciones.

- El grado máximo para la multiplicación por fuerza bruta es de 500.
