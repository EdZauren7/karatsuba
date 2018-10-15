/*---------------------------------Tarea Programación Avanzada-Operacion de polinomios--------------------------------**/
/************************************************************************************************************************
    Autores   : NICOLAS IGNACIO HONORATO DROGUETT; EDUARDO BALTRA ROJAS.
    Programa  : Operacion de polinomios.
	Proposito : Generar polinomios y realizar las operaciones básicas que se puede hacer con ellos.
    Fecha     : Santiago de Chile, 12 de Octubre de 2018.
	Compilador: gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0
	Standard  : C99

************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/**--------------------------------------------CONSTANTES GLOBALES----------------------------------------------------**/
#define maxCoef 1048576  //+-1048576 //Es el valor máximo absoluto que puede tomar un coeficiente.
#define maxGrd 4194304   //4194304  //Es el valor máximo que puede tomar un grado.


/**------------------------------------------------ESTRUCTURAS--------------------------------------------------------**/
/**
 * struct Monomio:
 * 
 * Esta estructura representa a un monomio cualquiera. Almacena un coeficiente (coef) y el grado (grd).
 */
struct Monomio{
	long coef;
	long grd;
};
/**
 * struct Polinomio:
 * 
 * Estructura lista enlazada. Simula un polinomio teniendo varios monomios consecutivos.
 */
struct Polinomio{
	struct Monomio *monomio;
	struct Polinomio *sig;
};
/**-------------------------------------------------PROTOTIPOS--------------------------------------------------------**/
void crearPolinomio(struct Polinomio **pol);
void agregarMonomio(struct Polinomio **pol,struct Monomio *mon);
struct Polinomio *generarPolinomio(long grdIt);
void imprimirPolinomio(struct Polinomio *pol);

struct Polinomio *copiarPolinomio(struct Polinomio *pol);
struct Monomio *copiarMonomio(struct Monomio *mon);

struct Monomio *sumaMons(struct Monomio *monp, struct Monomio *monq,int signo);
struct Polinomio *sumaPol(struct Polinomio *polp, struct Polinomio *polq,int signo);
struct Polinomio *sumarPolinomios(struct Polinomio *polp, struct Polinomio *polq);
struct Polinomio *restarPolinomios(struct Polinomio *polp, struct Polinomio *polq);

void liberarMemoria(struct Polinomio *pol);
long stringToLong(char *s);
/**-----------------------------------------------FIN PROTOTIPOS------------------------------------------------------**/
	
int main(unsigned int argc, char **argv){
	struct Polinomio *polp=NULL;
	struct Polinomio *polq=NULL;
	struct Polinomio *polSuma=NULL;
	struct Polinomio *polResta=NULL;
	struct Polinomio *copia=NULL;
	long gradop=0;
	long gradoq=0;
	srand(time(0));
	gradop=stringToLong(argv[1]);
	gradoq=stringToLong(argv[2]);
	system("clear");
	polp=generarPolinomio(gradop);
	printf("Polinomio 1: \n");
	imprimirPolinomio(polp);
	polq=generarPolinomio(gradoq);
	printf("Polinomio 2: \n");
	imprimirPolinomio(polq);
	printf("Polinomio 1 (copia, ver código): \n");
	copia=copiarPolinomio(polp);
	imprimirPolinomio(copia);
	printf("\nSuma de los polinomios: \n");
	polSuma=sumarPolinomios(polp,polq);
	imprimirPolinomio(polSuma);
	printf("Resta de los polinomios (p1-p2): \n");
	polResta=restarPolinomios(polp,polq);
	imprimirPolinomio(polResta);
	liberarMemoria(polp);
	liberarMemoria(polq);
	liberarMemoria(polSuma);
	liberarMemoria(polResta);
	liberarMemoria(copia);
	return 0;
}





/**-------------------------------------------------FUNCIONES---------------------------------------------------------**/
/**
 * generarPolinomio:
 * 
 * Función que genera un polinomio aleatorio de un grado dado. 
 * 
 * El polinomio generado está ordenado por grado, de mayor a menor.
 */
struct Polinomio *generarPolinomio(long grdIt){
	struct Polinomio *pol=NULL;
	struct Monomio *mon=NULL;
	while(grdIt>=0){
		mon=(struct Monomio*) calloc(1,sizeof(struct Monomio));
		mon->coef=rand()%maxCoef;
		if(rand()%2!=0)
			mon->coef=-mon->coef;
		mon->grd=grdIt;
		agregarMonomio(&(pol),mon);
		grdIt--;
	}
	return pol;
}







/**
 * crearPolinomio:
 * 
 * Función que asigna memoria al parámetro pol.
 */
void crearPolinomio(struct Polinomio **pol){
	(*pol)=(struct Polinomio*) calloc(1,sizeof(struct Polinomio));
	return;
}






/**
 * agregarMonomio:
 * 
 * Función que agrega el monomio mon al final de la lista pol.
 */
void agregarMonomio(struct Polinomio **pol,struct Monomio *mon){
	struct Polinomio *it=*(pol);
	if(it==NULL){
		crearPolinomio(pol);
		(*pol)->monomio=mon;
		(*pol)->sig=NULL;
		return;
	}
	while(it!=NULL){
		if(it->sig==NULL){
			crearPolinomio(&(it->sig));
			it->sig->monomio=mon;
			return;
		}
		else{
			it=it->sig;
		}
	}
	return;
}






/**
 * imprimirPolinomio:
 * 
 * Función que imprime todo el contenido del polinomio pol.
 * 
 * Se escribe de la forma : ax^e+... 
 */
void imprimirPolinomio(struct Polinomio *pol){
	struct Polinomio *it=pol;
	struct Monomio *mon;
	if(it!=NULL){
		mon=it->monomio;
		printf("%ldx^%ld",mon->coef,mon->grd);
		it=it->sig;
		while(it!=NULL){
			mon=it->monomio;
			if(mon->coef>=0)
				printf("+%ldx^%ld",mon->coef,mon->grd);
			else
				printf("%ldx^%ld",mon->coef,mon->grd);
			it=it->sig;
		}
		printf("\n");
	}
	else 
		printf("0\n");
	return;
}






/**
 * copiarPolinomio:
 * 
 * Función que crea y retorna una copia del polinomio pol.
 */
struct Polinomio *copiarPolinomio(struct Polinomio *pol){
	struct Polinomio *copia=NULL;
	while(pol!=NULL){
		agregarMonomio(&copia,copiarMonomio(pol->monomio));
		pol=pol->sig;
	}
	return copia;
}






/**
 * copiarMonomio:
 * 
 * Función que crea y retorna una copia del parámetro mon. 
 */
struct Monomio *copiarMonomio(struct Monomio *mon){
	struct Monomio *copia=(struct Monomio*) calloc(1,sizeof(struct Monomio));
	copia->coef=mon->coef;
	copia->grd=mon->grd;
	return copia;
}






/**
 * sumaMons:
 * 
 * Función que recibe y suma (o resta, dependiendo del parámetro signo) dos 
 * monomios monp y monq. 
 * 
 * Retorna una nueva estructura correspondiente a la suma.
 */
struct Monomio *sumaMons(struct Monomio *monp, struct Monomio *monq,int signo){
	struct Monomio *suma=NULL;
	if(monp->grd==monq->grd){
		suma=(struct Monomio*) calloc(1,sizeof(struct Monomio));
		suma->coef=monp->coef+(signo * monq->coef);
		suma->grd=monp->grd;
	}
	return suma;
}






/**
 * sumaPol:
 * 
 * Función llamada por las funciones sumarPolinomios y restarPolinomios.
 * 
 * Suma o resta (dependiendo del parámetro signo) un polinomio polq al polinomio
 * polp. Retornando así, una nueva estructura correspondiente a la operación hecha.
 * 
 * La función itera desde el grado mayor hasta que una de las dos listas sea nula. Similar
 * a la iteración de merge de dos listas.
 * 
 * Se asume que polp y polq no reciben valores NULL al llamar a la función.
 */
struct Polinomio *sumaPol(struct Polinomio *polp, struct Polinomio *polq,int signo){
	struct Polinomio *acum=NULL;
	long gradoMayor=polq->monomio->grd;
	struct Monomio *monp,*monq,*aux;
	if(polp->monomio->grd>polq->monomio->grd)
		gradoMayor=polp->monomio->grd;
	while(polp!=NULL && polq!=NULL){
		monp=polp->monomio;
		monq=polq->monomio;
		if(monp->grd==gradoMayor && monq->grd==gradoMayor){
			agregarMonomio(&(acum),sumaMons(monp,monq,signo));
			polp=polp->sig;
			polq=polq->sig;
		}
		else if(monp->grd==gradoMayor){
			agregarMonomio(&(acum),copiarMonomio(monp));
			polp=polp->sig;
		}
		else if(monq->grd==gradoMayor){
				aux=copiarMonomio(monq);
				aux->coef*=signo;
				agregarMonomio(&(acum),aux);
				polq=polq->sig;
		}
		gradoMayor--;
	}
	while(polp!=NULL){
		agregarMonomio(&(acum),copiarMonomio(polp->monomio));
		polp=polp->sig;
	}
	while(polq!=NULL){
		aux=copiarMonomio(polq->monomio);
		aux->coef*=signo;
		agregarMonomio(&(acum),aux);
		polq=polq->sig;
	}
	return acum;
}





/**
 * sumarPolinomios:
 * 
 * Función que suma dos polinomios polp y polq, especificando el signo a la función sumaPol.
 */
struct Polinomio *sumarPolinomios(struct Polinomio *polp, struct Polinomio *polq){
	return sumaPol(polp,polq,1);
}





/**
 * restarPolinomios:
 * 
 * Función que resta el polinomio polq a polp, especificando el signo a la función sumaPol.
 */
struct Polinomio *restarPolinomios(struct Polinomio *polp, struct Polinomio *polq){
	return sumaPol(polp,polq,-1);
}





/**
 * liberarMemoria:
 * 
 * Función que libera la memoria utilizada por una estructura de polinomio.
 */
void liberarMemoria(struct Polinomio *pol){
	struct Polinomio *aux;
	while(pol!=NULL){
		aux=pol->sig;
		free(pol->monomio);
		free(pol);
		pol=aux;
	}
	return;
}





long stringToLong(char *s){
    long suma=0;
    int i=-1;
    while(s[++i]!='\0')
        suma=(suma*10)+(s[i]-'0');
    return suma;
}



/**-----------------------------------------------FIN FUNCIONES-------------------------------------------------------**/
