Modo de compilación:

gcc polinomio.c -o polinomio.out -lm -std=c99

Modo de ejecutar:

./polinomio.out GradoPolinomio1 GradoPolinomio2


ex:

time ./polinomio.out 150 100

Donde el primer polinomio será grado 150 y el segundo grado 100.

IMPORTANTE:

- El grado máximo para la multiplicación por fuerza bruta es de 500.
- Para ver los resultados de la multiplicación DYC (clásico y karatsuba), los grados deben ser iguales.
