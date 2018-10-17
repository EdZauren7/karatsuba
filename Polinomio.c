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
struct Polinomio *copiarPartePolinomio(struct Polinomio *pol, long grdIn,long grdFin);
struct Monomio *copiarMonomio(struct Monomio *mon);

struct Monomio *sumaMons(struct Monomio *monp, struct Monomio *monq,int signo);
struct Polinomio *sumaPol(struct Polinomio *polp, struct Polinomio *polq,int signo);
struct Polinomio *sumarPolinomios(struct Polinomio *polp, struct Polinomio *polq);
struct Polinomio *restarPolinomios(struct Polinomio *polp, struct Polinomio *polq);

struct Polinomio *multiplicarFB(struct Polinomio *polp,struct Polinomio *polq);
void sumarMonomioPolinomio(struct Polinomio **pol, struct Monomio *mon);

struct Polinomio *multiplicarRYC(struct Polinomio *polp, struct Polinomio *polq);
struct Polinomio *multiplicarMonomioPolinimio(struct Polinomio *pol,struct Monomio *mon);

void multiplicarPorPotencia(struct Polinomio **pol, long grd);
void multiplicarDYC(struct Polinomio *polp, struct Polinomio *polq,struct Polinomio **res);

void liberarMemoria(struct Polinomio *pol);
long stringToLong(char *s);
/**-----------------------------------------------FIN PROTOTIPOS------------------------------------------------------**/
	
int main(int argc, char **argv){
	struct Polinomio *polp=NULL;
	struct Polinomio *polq=NULL;
	struct Polinomio *polSuma=NULL;
	struct Polinomio *polResta=NULL;
	struct Polinomio *polMult=NULL;
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
	/*printf("Polinomio 1 (copia, ver código): \n");
	copia=copiarPolinomio(polp);
	imprimirPolinomio(copia);
	printf("\nSuma de los polinomios: \n");
	polSuma=sumarPolinomios(polp,polq);
	imprimirPolinomio(polSuma);
	printf("Resta de los polinomios (p1-p2): \n");
	polResta=restarPolinomios(polp,polq);
	imprimirPolinomio(polResta);
	printf("\nMultiplicacion polinomio 1 por polinomio 2 (Fuerza bruta): \n");
	polMult=multiplicarFB(polp,polq);
	imprimirPolinomio(polMult);
	liberarMemoria(polMult);*/
	printf("\nMultiplicacion polinomio 1 por polinomio 2 (Red. y conquistar): \n");
	polMult=multiplicarRYC(polp,polq);
	imprimirPolinomio(polMult);
	liberarMemoria(polMult);
	polMult=NULL;
	printf("\nMultiplicacion polinomio 1 por polinomio 2 (Div. y conquistar): \n");
	multiplicarDYC(polp,polq,&polMult);
	imprimirPolinomio(polMult);
	liberarMemoria(polp);
	liberarMemoria(polq);
	liberarMemoria(polSuma);
	liberarMemoria(polResta);
	liberarMemoria(polMult);
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
	(*pol)->sig=NULL;
	(*pol)->monomio=NULL;
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
			it->sig->sig=NULL;
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
		if(mon->coef!=0)
			printf("%ldx^%ld",mon->coef,mon->grd);
		it=it->sig;
		while(it!=NULL){
			mon=it->monomio;
			if(mon->coef>0)
				printf("+%ldx^%ld",mon->coef,mon->grd);
			else if(mon->coef<0)
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
 * copiarPartePolinomio:
 * 
 * Función que retorna la copia de un polinomio desde el grado grdIn (mayor)
 * hasta encontrar el grado grdFin (menor).
 */
struct Polinomio *copiarPartePolinomio(struct Polinomio *pol, long grdIn,long grdFin){
	struct Polinomio *copia=NULL;
	struct Monomio *mon=NULL;
	while(pol!=NULL){
		mon=pol->monomio;
		if(mon->grd<=grdIn && mon->grd>=grdFin)
			agregarMonomio(&copia,copiarMonomio(mon));
		pol=pol->sig;
		if(mon->grd<grdFin)
			pol=NULL;
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
	long gradoMayor=0;
	struct Monomio *monp,*monq,*aux;
	if(polp!=NULL && polq!=NULL){
		if(polp!=NULL)
			gradoMayor=polp->monomio->grd;
		if(polq!=NULL && polp->monomio->grd<polq->monomio->grd)
			gradoMayor=polq->monomio->grd;
	}
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
 * sumarMonomioPolinomio:
 * 
 * Función que suma un monomio (mon) a un polinomio. La función posee 4 casos:
 * 
 * - Si pol es NULL, se asigna mon en la primera posicion.
 * - Si se encuentra un monomio del mismo grado se suman los coeficientes.
 * - Si se encuentra un monomio de menor grado, se inserta mon antes que él.
 * - Si se llega al final de la lista, se agrega al final.
 */
void sumarMonomioPolinomio(struct Polinomio **pol, struct Monomio *mon){
	struct Polinomio *it=*pol;
	struct Polinomio *aux=NULL;
	struct Monomio *monAux=NULL;
	if(it==NULL)
		agregarMonomio(pol,mon);
	else
		while(it!=NULL){
			monAux=it->monomio;
			if(monAux->grd==mon->grd){
				monAux->coef+=mon->coef;
				return;
			}
			else if(monAux->grd<mon->grd){
				aux=(struct Polinomio*) calloc(1,sizeof(struct Polinomio));
				aux->monomio=monAux;
				aux->sig=it->sig;
				it->monomio=mon;
				it->sig=aux;
				return;
			}
			else if(it->sig==NULL){
				aux=(struct Polinomio*) calloc(1,sizeof(struct Polinomio));
				aux->monomio=mon;
				aux->sig=NULL;
				it->sig=aux;
				return;
			}
			it=it->sig;
		}
	return;
}






/**
 * multiplicarFB:
 * 
 * Función que multiplica dos polinomios con el método fuerza bruta. Realiza todas
 * las multiplicaciones de monomios y las guarda en la variable acum.
 * 
 * Cuando finaliza recorre la variable acum y suma todos los monomios dentro
 * de la variable suma, la que luego es retornada.
 */
struct Polinomio *multiplicarFB(struct Polinomio *polp,struct Polinomio *polq){
	struct Polinomio *itp=polp;
	struct Polinomio *itq=polq;
	struct Polinomio *acum=NULL;
	struct Polinomio *suma=NULL;
	struct Monomio *auxMult=NULL;
	struct Monomio *monp=NULL;
	struct Monomio *monq=NULL;
	if(polp==NULL || polq==NULL){
		agregarMonomio(&acum,(struct Monomio*) calloc(1,sizeof(struct Monomio)));
		return acum;
	}
	while(itp!=NULL){
		monp=itp->monomio;
		while(itq!=NULL){
			monq=itq->monomio;
			auxMult=(struct Monomio*) calloc(1,sizeof(struct Monomio));
			auxMult->coef=monp->coef*monq->coef;
			auxMult->grd=monp->grd+monq->grd;
			agregarMonomio(&acum,auxMult);
			itq=itq->sig;
		}
		itq=polq;
		itp=itp->sig;
	}
	while(acum!=NULL){
		sumarMonomioPolinomio(&suma,acum->monomio);
		acum=acum->sig;
	}
	return suma;
}






/**
 * multiplicarRYC:
 * 
 * Función que multiplica dos polinomios con el método reducir y conquistar. Se multiplica
 * el polinomio p por con costante y se acumula en la variable suma.
 */ 
struct Polinomio *multiplicarRYC(struct Polinomio *polp, struct Polinomio *polq){
	struct Polinomio *suma=NULL;
	struct Polinomio *aux=NULL;
	struct Polinomio *auxMult=NULL;
	while(polq!=NULL){
		aux=suma;
		auxMult=multiplicarMonomioPolinimio(polp,polq->monomio);
		suma=sumarPolinomios(aux,auxMult);
		liberarMemoria(auxMult);
		liberarMemoria(aux);
		polq=polq->sig;
	}
	return suma;
}





/**
 * multiplicarMonomioPolinimio:
 * 
 * Función que multiplica un polinomio por un monomio mon.
 * 
 */
struct Polinomio *multiplicarMonomioPolinimio(struct Polinomio *pol,struct Monomio *mon){
	struct Polinomio *multiplicando=copiarPolinomio(pol);
	struct Polinomio *iterador=multiplicando;
	struct Monomio *aux;
	while(iterador!=NULL){
		aux=iterador->monomio;
		if(aux!=NULL){
			aux->coef*=mon->coef;
			aux->grd+=mon->grd;
		}
		iterador=iterador->sig;
	}
	return multiplicando;
}







void multiplicarDYC(struct Polinomio *polp, struct Polinomio *polq,struct Polinomio **res){
	struct Monomio *mon=NULL,*m1,*m2;
	struct Polinomio *a1,*b1,*a0,*b0;
	long np=0,nq=0;
	if(polp->sig==NULL && polq->sig==NULL){
		
		mon=(struct Monomio*) calloc(1,sizeof(struct Monomio));
		mon->coef=polp->monomio->coef*polq->monomio->coef;
		mon->grd=polp->monomio->grd+polq->monomio->grd;
		sumarMonomioPolinomio(res,mon);
		return;
	}
	else{
		np=polp->monomio->grd;
		nq=polq->monomio->grd;
		a1=copiarPartePolinomio(polp,np,np/2);
		a0=copiarPartePolinomio(polp,np/2,0);
		b1=copiarPartePolinomio(polq,nq,nq/2);
		b0=copiarPartePolinomio(polq,nq/2,0);
		if((np+1)%2==0 && (nq+1)%2==0){
			multiplicarDYC(a1,b1,res);
			multiplicarDYC(a1,b0,res);
			multiplicarDYC(a0,b1,res);
			multiplicarDYC(a0,b0,res);
		}
		else if((np+1)%2==0){
			m1=a1->monomio;
			m2=a0->monomio;
			multiplicarDYC(a1,b1,res);
			*(res)=sumarPolinomios(*res,multiplicarMonomioPolinimio(b0,m1));
			multiplicarDYC(a1->sig,b0,res);
			multiplicarDYC(a0,b1,res);
			*res=(sumarPolinomios(*res,multiplicarMonomioPolinimio(b0,m2)));
			multiplicarDYC(a0->sig,b0,res);
		}
		else if((nq+1)%2==0){
			m1=b1->monomio;
			m2=b0->monomio;
			multiplicarDYC(a1,b1,res);
			multiplicarDYC(a1,b0,res);
			*res=(sumarPolinomios(*res,multiplicarMonomioPolinimio(a0,m1)));
			multiplicarDYC(a0,b1->sig,res);
			*res=(sumarPolinomios(*res,multiplicarMonomioPolinimio(a0,m2)));
			multiplicarDYC(a0,b0->sig,res);
		}
		else{
			m1=a1->monomio;
			m2=b1->monomio;
			multiplicarDYC(a1,b1,res);
			multiplicarDYC(a0,b0,res);
			*res=(sumarPolinomios(*res,multiplicarMonomioPolinimio(b0,m1)));
			multiplicarDYC(a1->sig,b0,res);
			*res=(sumarPolinomios(*res,multiplicarMonomioPolinimio(a0,m2)));
			multiplicarDYC(a0,b1->sig,res);
		}
	}
	return;
}





/**
 * 
 */
void multiplicarPorPotencia(struct Polinomio **pol, long grd){
	struct Polinomio *it=*pol;
	while(it!=NULL){
		it->monomio->grd+=grd;
		it=it->sig;
	}
	return;
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
