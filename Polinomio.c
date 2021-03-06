/*---------------------------------Tarea Programación Avanzada-Operacion de polinomios--------------------------------**/
/************************************************************************************************************************
    Autores   : NICOLAS IGNACIO HONORATO DROGUETT; EDUARDO BALTRA ROJAS.
    Programa  : Operacion de polinomios.
	Proposito : Generar polinomios y realizar las operaciones básicas que se puede hacer con ellos.
    Fecha     : Santiago de Chile, 16 de noviembre de 2018.
	Compilador: gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0
	Standard  : C99

************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/**--------------------------------------------CONSTANTES GLOBALES----------------------------------------------------**/
#define maxCoef 1048576 			//Es el valor máximo absoluto que puede tomar un coeficiente.
#define largoListaComparaciones 1000 //Es el largo de las listas en la función para comparar métodos
#define limiteGrdComparaciones 50	//Es el grado máximo que se comparará en los métodos

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
struct Monomio *crearMonomio(long coef,long grd);
void crearPolinomio(struct Polinomio **pol);
void agregarMonomio(struct Polinomio **pol,struct Monomio *mon);
struct Polinomio *generarPolinomio(long grdIt);
void imprimirPolinomio(struct Polinomio *pol);

struct Polinomio *copiarPolinomio(struct Polinomio *pol);
struct Polinomio *copiarPartePolinomio(struct Polinomio *pol, long grdIn,long grdFin);
struct Monomio *copiarMonomio(struct Monomio *mon);

struct Monomio *sumarMonomios(struct Monomio *molp, struct Monomio *molq,int signo);
struct Polinomio *sumaPol(struct Polinomio *polp, struct Polinomio *polq,int signo);
struct Polinomio *sumarPolinomios(struct Polinomio *polp, struct Polinomio *polq);
struct Polinomio *restarPolinomios(struct Polinomio *polp, struct Polinomio *polq);

struct Monomio *multiplicarMonomios(struct Monomio *mp,struct Monomio *mq);
struct Polinomio *multiplicarFB(struct Polinomio *polp,struct Polinomio *polq);
void sumarMonomioPolinomio(struct Polinomio **pol, struct Monomio *mon);

struct Polinomio *multiplicarRYC(struct Polinomio *polp, struct Polinomio *polq);
struct Polinomio *multiplicarMonomioPolinimio(struct Polinomio *pol,struct Monomio *mon);

void multiplicarPorPotencia(struct Polinomio **pol, long grd);
struct Polinomio *multiplicarDYC(struct Polinomio *polp, struct Polinomio *polq,struct Polinomio *(*metodoMult)(struct Polinomio*,struct Polinomio*,struct Polinomio*,struct Polinomio*));
struct Polinomio *metodoClasico(struct Polinomio *a0,struct Polinomio *a1,struct Polinomio *b0,struct Polinomio *b1);
struct Polinomio *metodoKaratsuba(struct Polinomio *a0,struct Polinomio *a1,struct Polinomio *b0,struct Polinomio *b1);
struct Polinomio *metodoClasicoInductivo(struct Polinomio *a0,struct Polinomio *a1,struct Polinomio *b0,struct Polinomio *b1);
struct Polinomio *metodoKaratsubaInductivo(struct Polinomio *a0,struct Polinomio *a1,struct Polinomio *b0,struct Polinomio *b1);
struct Polinomio *multiplicacionPolinomios(struct Polinomio *p,struct Polinomio *q);

double menuSuma(struct Polinomio *p,struct Polinomio *q);
double menuResta(struct Polinomio *p,struct Polinomio *q);
double menuFuerzaBruta(struct Polinomio *p,struct Polinomio *q);
double menuRYC(struct Polinomio *p,struct Polinomio *q);
double menuMetodosDYC(struct Polinomio *p,struct Polinomio *q,struct Polinomio *(*metodoMult)(struct Polinomio*,struct Polinomio*,struct Polinomio*,struct Polinomio*));
double menuMultiplicaciones(struct Polinomio *p,struct Polinomio *q);

void comparacionMetodos(long n, long grd,long grdMax);
void comparacionesMetodos(long n,long grdMax);
void escribirDatosComparacion(int grd,double clasico,double karatsuba);

void liberarMemoria(struct Polinomio **pol);
long stringToLong(char *s);
/**-----------------------------------------------FIN PROTOTIPOS------------------------------------------------------**/
int main(int argc, char **argv){
	struct Polinomio *polp=NULL,*polq=NULL;
	clock_t begin;
	double tsp=-1,trp=-1,tfb=-1,tryc=-1,tdyc=-1,tkt=-1,tid=-1;
	srand(time(0));
	system("clear");
	if(argc==3){
		polp=generarPolinomio(stringToLong(argv[1]));
		printf("Polinomio 1: \n");
		imprimirPolinomio(polp);
		polq=generarPolinomio(stringToLong(argv[2]));
		printf("Polinomio 2: \n");
		imprimirPolinomio(polq);
		tsp=menuSuma(polp,polq);
		trp=menuResta(polp,polq);
		tfb=menuFuerzaBruta(polp,polq);
		tryc=menuRYC(polp,polq);
		printf("\nMultiplicacion polinomio 1 por polinomio 2 (Div. y conquistar): \n");
		tdyc=menuMetodosDYC(polp,polq,&metodoClasico);
		printf("\nMultiplicacion polinomio 1 por polinomio 2 (karatsuba): \n");
		tkt=menuMetodosDYC(polp,polq,&metodoKaratsuba);
		printf("\nMultiplicacion polinomio 1 por polinomio 2: \n");
		tid=menuMultiplicaciones(polp,polq);
		liberarMemoria(&polp);
		liberarMemoria(&polq);
		printf("\nTiempos: |Suma Polinomios %.3lfms |Resta Polinomios: %.3lfms\n",tsp,trp);
		printf("Ti. multiplicacion: |Fue.Bruta %.3lfms |RedYConq: %.3lfms\n",tfb,tryc);
		printf("Ti. multiplicacion DYC: |Clasico: %.3lfms |Karatsuba: %.3lfms |Ambos: %.3lfms\n",tdyc,tkt,tid);
		printf("Si tiempo = -1 signica que no se ejecutó el algoritmo.\n");
	}
	else{
		printf("Comparaciones: |Largo de listas: %d |Grado máximo: %d",largoListaComparaciones,limiteGrdComparaciones);
		comparacionesMetodos(largoListaComparaciones,limiteGrdComparaciones);
	}
	return 0;
}

/**-----------------------------------------------FUNCIONES MENU-------------------------------------------------------**/

double menuSuma(struct Polinomio *p,struct Polinomio *q){
	struct Polinomio *polSuma=NULL;
	clock_t begin;
	double tsp=-1;
	begin=clock();
	polSuma=sumarPolinomios(p,q);
	tsp=(double) ((clock()-begin)*1000)/CLOCKS_PER_SEC;
	printf("\nSuma de los polinomios: \n");
	imprimirPolinomio(polSuma);
	liberarMemoria(&polSuma);
	return tsp;
}

double menuResta(struct Polinomio *p,struct Polinomio *q){
	struct Polinomio *polResta=NULL;
	clock_t begin;
	double trp=-1;
	begin=clock();
	polResta=restarPolinomios(p,q);
	trp=(double) ((clock()-begin)*1000)/CLOCKS_PER_SEC;
	printf("Resta de los polinomios (p1-p2): \n");
	imprimirPolinomio(polResta);
	liberarMemoria(&polResta);
	return trp;
}

double menuFuerzaBruta(struct Polinomio *p,struct Polinomio *q){
	struct Polinomio *polMult=NULL;
	clock_t begin;
	double tfb=-1;
	if(p->monomio->grd<500 && q->monomio->grd<500){
		begin=clock();
		polMult=multiplicarFB(p,q);
		tfb=(double) ((clock()-begin)*1000)/CLOCKS_PER_SEC;
		printf("\nMultiplicacion polinomio 1 por polinomio 2 (Fuerza bruta): \n");
		imprimirPolinomio(polMult);
		liberarMemoria(&polMult);
	}
	else
		printf("\nLos grados son muy altos para M. fuerza bruta! (Tiempo >~ 1 min) \n");
	return tfb;
}

double menuRYC(struct Polinomio *p,struct Polinomio *q){
	struct Polinomio *polMult=NULL;
	clock_t begin;
	double tryc=-1;
	printf("\nMultiplicacion polinomio 1 por polinomio 2 (Red. y colquistar): \n");
	begin=clock();
	polMult=multiplicarRYC(p,q);
	tryc=((clock()-begin)*1000)/CLOCKS_PER_SEC;
	imprimirPolinomio(polMult);
	liberarMemoria(&polMult);
	return tryc;
}

double menuMetodosDYC(struct Polinomio *p,struct Polinomio *q,struct Polinomio *(*metodoMult)(struct Polinomio*,struct Polinomio*,struct Polinomio*,struct Polinomio*)){
	struct Polinomio *polMult=NULL;
	double begin;
	double tdyc=-1;
	begin=clock();
	polMult=multiplicarDYC(p,q,metodoMult);
	tdyc=(((clock()-begin)*1000)/CLOCKS_PER_SEC);
	imprimirPolinomio(polMult);
	liberarMemoria(&polMult);
	return tdyc;
}

double menuMultiplicaciones(struct Polinomio *p,struct Polinomio *q){
	struct Polinomio *polMult=NULL;
	double begin;
	double tid=-1;
	begin=clock();
	polMult=multiplicacionPolinomios(p,q);
	tid=(((clock()-begin)*1000)/CLOCKS_PER_SEC);
	imprimirPolinomio(polMult);
	liberarMemoria(&polMult);
	return tid;
}





/**-------------------------------------------FUNCIONES COMPARACIONES-------------------------------------------------**/

/**
 * comparacionesMetodos:
 * 
 * Función que compara los métodos de DYC clásico y karatsuba, desde el grado 1
 * hasta el grado grdMax.  
 */
void comparacionesMetodos(long n,long grdMax){
	long i=1;
	int k;
	FILE *in;
	in=fopen("datosComparacion.csv","w");
	if(in)
		fprintf(in,"Grado;T.Clasico;T.Karatsuba\n");
	fclose(in);
	printf("\n\n|------------------------------------------------------------------------------------------------------|\n");
	for(;i<=grdMax;i++){
		comparacionMetodos(n,i,grdMax);
		if(i%15==0)
			for(k=1;k<=15;k++)
				printf("\33[2K\033[1A\33[2K");
	}
	printf("|------------------------------------------------------------------------------------------------------|\n\n");
}





/**
 * comparacionMetodos:
 * 
 * Función que genera dos listas de tamaño n, donde se guardan polinomios de grado grd generados aleatoriamente.
 * 
 * Se realiza una multiplicación cruzada de ambas listas con los métodos de DYC clásico y karatsuba. Se promedian
 * los tiempos de ejecución y se comparan.
 * 
 * Además, escribe en un archivo los resultados obtenidos.
 */
void comparacionMetodos(long n, long grd,long grdMax){
	struct Polinomio **lista1=(struct Polinomio**) calloc(n,sizeof(struct Polinomio*));
	struct Polinomio **lista2=(struct Polinomio**) calloc(n,sizeof(struct Polinomio*));
	struct Polinomio *aux1,*aux2;
	long i=0,j=0,c=1;
	double tdyc=0,tkt=0,ttdyc,ttkt;
	clock_t begin;
	char *metodo="Ambos";
	while((grdMax/=10)>0)
		c++;
	for(;i<n;i++){
		lista1[i]=generarPolinomio(rand()%grd);
		lista2[i]=generarPolinomio(rand()%grd);
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			begin=clock();
			aux1=multiplicarDYC(lista1[i],lista2[j],&metodoClasico);
			tdyc+=(((clock()-begin)*1000)/CLOCKS_PER_SEC);
			liberarMemoria(&aux1);
			begin=clock();
			aux2=multiplicarDYC(lista1[i],lista2[j],&metodoKaratsuba);
			tkt+=(((clock()-begin)*1000)/CLOCKS_PER_SEC);
			liberarMemoria(&aux2);
		}
		printf("\r| Comparaciones: %.2lf %%",(double) (((i+1)*100)/n));
		fflush(stdout);
		liberarMemoria(&lista1[i]);
	}
	free(lista1);
	for(i=0;i<n;i++)
		liberarMemoria(&lista2[i]);
	free(lista2);
	ttdyc=tdyc/(n*n);
	ttkt=tkt/(n*n);
	if((ttdyc-ttkt)<0)
		metodo="Clasico";
	else if((ttdyc-ttkt)>0)
		metodo="Karatsuba";
	printf("\r| Grado maximo: %0*ld ||AVG:  |M. clasico: %.5lfms  |M. Karatsuba: %.5lfms ||Menor tiempo: %s\n",(int)c,grd,ttdyc,ttkt,metodo);
	escribirDatosComparacion(grd,ttdyc,ttkt);
	return;
}





void escribirDatosComparacion(int grd,double clasico,double karatsuba){
	FILE *in;
	in=fopen("datosComparacion.csv","a");
	if(in)
		fprintf(in,"%d;%.6lf;%.6lf\n",grd,clasico,karatsuba);
	fclose(in);
	return;
}





/**-------------------------------------------------FUNCIONES---------------------------------------------------------**/

/**
 * generarPolinomio:
 * 
 * Función que genera un polinomio aleatorio a partir de un grado dado. 
 * 
 * El polinomio generado está ordenado por grado, de mayor a menor.
 */
struct Polinomio *generarPolinomio(long grdIt){
	struct Polinomio *pol=NULL;
	while(grdIt-->=0)
		agregarMonomio(&(pol),crearMonomio(rand()%2==0?(rand()%maxCoef):-(rand()%maxCoef),grdIt+1));
	return pol;
}





/**
 * crearMonomio:
 * 
 * Función que retorna una nuevo struct Monomio.
 */
struct Monomio *crearMonomio(long coef,long grd){
	struct Monomio *monomio=(struct Monomio*) calloc(1,sizeof(struct Monomio));
	monomio->coef=coef;
	monomio->grd=grd;
	return monomio;
}





/**
 * crearPolinomio:
 * 
 * Función que asigna memoria al parámetro pol.
 */
void crearPolinomio(struct Polinomio **pol){
	liberarMemoria(pol);
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
		return;
	}
	while(it!=NULL)
		if(it->sig==NULL){
			crearPolinomio(&(it->sig));
			it->sig->monomio=mon;
			return;
		}
		else
			it=it->sig;
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
	while(it!=NULL && it->monomio->coef==0)
		it=it->sig;
	if(it!=NULL){
		if(it->monomio->coef!=0)
			printf("%ldx^%ld",it->monomio->coef,it->monomio->grd);
		while((it=it->sig)!=NULL)
			if(it->monomio->coef!=0)
				printf("%+ldx^%ld",it->monomio->coef,it->monomio->grd);
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
 * sumarMonomios:
 * 
 * Función que recibe y suma (o resta, dependiendo del parámetro signo) dos 
 * monomios molp y molq. 
 * 
 * Retorna una nueva estructura correspondiente a la suma.
 */
struct Monomio *sumarMonomios(struct Monomio *molp, struct Monomio *molq,int signo){
	struct Monomio *suma=NULL;
	if(molp->grd==molq->grd)
		suma=crearMonomio(molp->coef+(signo * molq->coef),molp->grd);
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
	struct Polinomio *acum=copiarPolinomio(polp);
	struct Monomio *aux=NULL;
	while(polq!=NULL){
		aux=copiarMonomio(polq->monomio);
		(aux->coef)*=signo;
		sumarMonomioPolinomio(&acum,aux);
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
				free(mon);
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
 * multiplicarMonomios:
 * 
 * Función que retorna el resultado de multiplicar dos monomios.
 */
struct Monomio *multiplicarMonomios(struct Monomio *mp,struct Monomio *mq){
	return crearMonomio(mp->coef*mq->coef,mp->grd+mq->grd);
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
	struct Polinomio *acumAux=NULL;
	if(polp==NULL || polq==NULL){
		agregarMonomio(&acum,crearMonomio(0,0));
		return acum;
	}
	while(itp!=NULL){
		while(itq!=NULL){
			agregarMonomio(&acum,multiplicarMonomios(itp->monomio,itq->monomio));
			itq=itq->sig;
		}
		itq=polq;
		itp=itp->sig;
	}
	while(acum!=NULL){
		sumarMonomioPolinomio(&suma,acum->monomio);
		acumAux=acum;
		free(acum);
		acum=acumAux->sig;
	}
	return suma;
}






/**
 * multiplicarRYC:
 * 
 * Función que multiplica dos polinomios con el método reducir y colquistar. Se multiplica
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
		liberarMemoria(&auxMult);
		liberarMemoria(&aux);
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
		if(mon->grd<grdFin)
			return copia;
		pol=pol->sig;
	}
	return copia;
}






/**
 * multiplicarDYC:
 * 
 * Función para multiplicar dos polinomios con el método dividir y conquistar.
 * 
 * La función recibe dos polinomios y los divide en dos mitades, las cuales las multiplica dependiendo de la
 * función enviada a metodoMult (red y conquistar o karatsuba).
 * 
 * OBS: Los grados de polp y polq deben ser iguales.
 */
struct Polinomio *multiplicarDYC(struct Polinomio *polp, struct Polinomio *polq,struct Polinomio *(*metodoMult)(struct Polinomio*,struct Polinomio*,struct Polinomio*,struct Polinomio*)){
	struct Polinomio *a0,*a1,*b0,*b1;
	struct Polinomio *multiplicacion=NULL;
	struct Polinomio *aux,*aux2;
	if(polp==NULL || polq==NULL)
		sumarMonomioPolinomio(&multiplicacion,crearMonomio(0,0));
	else if(polp->monomio->grd==0)
		return multiplicarMonomioPolinimio(polq,polp->monomio);
	else if(polq->monomio->grd==0)
		return multiplicarMonomioPolinimio(polp,polq->monomio);
	else{
		if(polp->monomio->grd<polq->monomio->grd){
			aux=polp;
			polp=polq;
			polq=aux;
		}
		if(polq->monomio->grd%2==0){
			aux=multiplicacion;
			aux2=multiplicarMonomioPolinimio(polp,polq->monomio);
			multiplicacion=sumarPolinomios(aux,aux2);
			liberarMemoria(&aux);
			liberarMemoria(&aux2);
			polq=polq->sig;
		}
		while(polp->monomio->grd>polq->monomio->grd){
			aux=multiplicacion;
			aux2=multiplicarMonomioPolinimio(polq,polp->monomio);
			multiplicacion=sumarPolinomios(aux,aux2);
			liberarMemoria(&aux);
			liberarMemoria(&aux2);
			polp=polp->sig;
		}
		a0=copiarPartePolinomio(polp,(polp->monomio->grd-1)/2,0);
		a1=copiarPartePolinomio(polp,polp->monomio->grd,(polp->monomio->grd+1)/2);
		b0=copiarPartePolinomio(polq,(polq->monomio->grd-1)/2,0);
		b1=copiarPartePolinomio(polq,polq->monomio->grd,(polq->monomio->grd+1)/2);
		multiplicarPorPotencia(&a1,-(a0->monomio->grd+1));
		multiplicarPorPotencia(&b1,-(b0->monomio->grd+1));
		aux=multiplicacion;
		aux2=metodoMult(a0,a1,b0,b1);
		multiplicacion=sumarPolinomios(aux,aux2);
		liberarMemoria(&aux);
		liberarMemoria(&aux2);
		liberarMemoria(&a1);
		liberarMemoria(&a0);
		liberarMemoria(&b1);
		liberarMemoria(&b0);
	}
	return multiplicacion;
}






/**
 * metodoClasico:
 * 
 * Función que recibe un polinomio a y un polinomio b, divididos en a0, a1 y b0, b1, respectivamente.
 * Retorna la multiplicación entre todos ellos con el método de dividir y conquistar clásica utilizando
 * la función red. y conquistar.
 * 
 */
struct Polinomio *metodoClasico(struct Polinomio *a0,struct Polinomio *a1,struct Polinomio *b0,struct Polinomio *b1){
	struct Polinomio *suma;
	struct Polinomio *auxMult1,*auxMult2,*auxMult3,*auxMult4,*auxSuma;
	auxMult1=multiplicarRYC(a1,b1);
	multiplicarPorPotencia(&auxMult1,(a0->monomio->grd+1)*2);
	auxMult2=multiplicarRYC(a0,b1);
	auxMult3=multiplicarRYC(a1,b0);
	auxMult4=multiplicarRYC(a0,b0);
	suma=sumarPolinomios(auxMult2,auxMult3);
	multiplicarPorPotencia(&suma,(a0->monomio->grd+1));
	liberarMemoria(&auxMult2);
	liberarMemoria(&auxMult3);
	auxSuma=sumarPolinomios(suma,auxMult1);
	liberarMemoria(&suma);
	liberarMemoria(&auxMult1);
	suma=sumarPolinomios(auxSuma,auxMult4);
	liberarMemoria(&auxMult4);
	liberarMemoria(&auxSuma);
	return suma;
}




/**
 * metodoKaratsuba:
 * 
 * Función que recibe un polinomio a y un polinomio b, divididos en a0, a1 y b0, b1, respectivamente.
 * Retorna la multiplicación entre todos ellos con el método de karatsuba utilizando la función red. y conquistar.
 * 
 */
struct Polinomio *metodoKaratsuba(struct Polinomio *a0,struct Polinomio *a1,struct Polinomio *b0,struct Polinomio *b1){
	struct Polinomio *auxMult1,*auxMult2,*auxMult3;
	struct Polinomio *auxSuma1,*auxSuma2,*auxSuma3,*auxSuma4;
	auxMult1=multiplicarRYC(a1,b1);
	auxMult2=multiplicarRYC(a0,b0);
	auxSuma1=sumarPolinomios(auxMult1,auxMult2);
	auxSuma2=sumarPolinomios(a0,a1);
	auxSuma3=sumarPolinomios(b0,b1);
	auxMult3=multiplicarRYC(auxSuma2,auxSuma3);
	liberarMemoria(&auxSuma3);
	auxSuma4=restarPolinomios(auxMult3,auxSuma1);
	liberarMemoria(&auxMult3);
	multiplicarPorPotencia(&auxMult1,(a0->monomio->grd+1)*2);
	multiplicarPorPotencia(&auxSuma4,(a0->monomio->grd+1));
	liberarMemoria(&auxSuma1);
	liberarMemoria(&auxSuma2);
	auxSuma1=sumarPolinomios(auxMult1,auxSuma4);
	liberarMemoria(&auxMult1);
	liberarMemoria(&auxSuma4);
	auxSuma2=sumarPolinomios(auxSuma1,auxMult2);
	liberarMemoria(&auxSuma1);
	liberarMemoria(&auxMult2);
	return auxSuma2;
}




/**
 * multiplicacionPolinomios:
 * 
 * Función que utiliza los métodos de div. y conquistar clásico y karatsuba. Decide qué método utilizar
 * en función de los grados de los polinomios enviados por parámetro.
 * 
 * Una vez que decide qué método utilizar, las funciones llaman de nuevo a la función para sus respectivas
 * multiplicaciones.
 */
struct Polinomio *multiplicacionPolinomios(struct Polinomio *polp,struct Polinomio *polq){
	struct Polinomio *a0,*a1,*b0,*b1;
	struct Polinomio *multiplicacion=NULL;
	struct Polinomio *aux,*aux2;
	if(polp==NULL || polq==NULL)
		sumarMonomioPolinomio(&multiplicacion,crearMonomio(0,0));	
	else if(polp->monomio->grd==0)
		return multiplicarMonomioPolinimio(polq,polp->monomio);
	else if(polq->monomio->grd==0)
		return multiplicarMonomioPolinimio(polp,polq->monomio);
	else{
		if(polp->monomio->grd<polq->monomio->grd){
			aux=polp;
			polp=polq;
			polq=aux;
		}
		if(polq->monomio->grd%2==0){
			aux=multiplicacion;
			aux2=multiplicarMonomioPolinimio(polp,polq->monomio);
			multiplicacion=sumarPolinomios(aux,aux2);
			liberarMemoria(&aux);
			liberarMemoria(&aux2);
			polq=polq->sig;
		}
		while(polp->monomio->grd>polq->monomio->grd){
			aux=multiplicacion;
			aux2=multiplicarMonomioPolinimio(polq,polp->monomio);
			multiplicacion=sumarPolinomios(aux,aux2);
			liberarMemoria(&aux);
			liberarMemoria(&aux2);
			polp=polp->sig;
		}
		a0=copiarPartePolinomio(polp,(polp->monomio->grd-1)/2,0);
		a1=copiarPartePolinomio(polp,polp->monomio->grd,(polp->monomio->grd+1)/2);
		b0=copiarPartePolinomio(polq,(polq->monomio->grd-1)/2,0);
		b1=copiarPartePolinomio(polq,polq->monomio->grd,(polq->monomio->grd+1)/2);
		multiplicarPorPotencia(&a1,-(a0->monomio->grd+1));
		multiplicarPorPotencia(&b1,-(b0->monomio->grd+1));
		aux=multiplicacion;
		if(polp->monomio->grd<=15 && polq->monomio->grd<=15)
			aux2=metodoClasicoInductivo(a0,a1,b0,b1);
		else
			aux2=metodoKaratsubaInductivo(a0,a1,b0,b1);	
		multiplicacion=sumarPolinomios(aux,aux2);
		liberarMemoria(&aux);
		liberarMemoria(&aux2);
		liberarMemoria(&a1);
		liberarMemoria(&a0);
		liberarMemoria(&b1);
		liberarMemoria(&b0);
	}
	return multiplicacion;
}






/**
 * metodoClasicoInductivo:
 * 
 * Función que recibe un polinomio a y un polinomio b, divididos en a0, a1 y b0, b1, respectivamente.
 * Retorna la multiplicación entre todos ellos con el método de dividir y conquistar clásica utilizando
 * recursión, usando la función multiplicacionPolinomios.
 * 
 */
struct Polinomio *metodoClasicoInductivo(struct Polinomio *a0,struct Polinomio *a1,struct Polinomio *b0,struct Polinomio *b1){
	struct Polinomio *suma;
	struct Polinomio *auxMult1,*auxMult2,*auxMult3,*auxMult4,*auxSuma;
	auxMult1=multiplicacionPolinomios(a1,b1);
	multiplicarPorPotencia(&auxMult1,(a0->monomio->grd+1)*2);
	auxMult2=multiplicacionPolinomios(a0,b1);
	auxMult3=multiplicacionPolinomios(a1,b0);
	auxMult4=multiplicacionPolinomios(a0,b0);
	suma=sumarPolinomios(auxMult2,auxMult3);
	multiplicarPorPotencia(&suma,(a0->monomio->grd+1));
	liberarMemoria(&auxMult2);
	liberarMemoria(&auxMult3);
	auxSuma=sumarPolinomios(suma,auxMult1);
	liberarMemoria(&suma);
	liberarMemoria(&auxMult1);
	suma=sumarPolinomios(auxSuma,auxMult4);
	liberarMemoria(&auxMult4);
	liberarMemoria(&auxSuma);
	return suma;
}




/**
 * metodoKaratsuba:
 * 
 * Función que recibe un polinomio a y un polinomio b, divididos en a0, a1 y b0, b1, respectivamente.
 * Retorna la multiplicación entre todos ellos con el método de karatsuba utilizando la función recursvia
 * multiplicacionPolinomios.
 * 
 */
struct Polinomio *metodoKaratsubaInductivo(struct Polinomio *a0,struct Polinomio *a1,struct Polinomio *b0,struct Polinomio *b1){
	struct Polinomio *auxMult1,*auxMult2,*auxMult3;
	struct Polinomio *auxSuma1,*auxSuma2,*auxSuma3,*auxSuma4;
	auxMult1=multiplicacionPolinomios(a1,b1);
	auxMult2=multiplicacionPolinomios(a0,b0);
	auxSuma1=sumarPolinomios(auxMult1,auxMult2);
	auxSuma2=sumarPolinomios(a0,a1);
	auxSuma3=sumarPolinomios(b0,b1);
	auxMult3=multiplicacionPolinomios(auxSuma2,auxSuma3);
	liberarMemoria(&auxSuma3);
	auxSuma4=restarPolinomios(auxMult3,auxSuma1);
	liberarMemoria(&auxMult3);
	multiplicarPorPotencia(&auxMult1,(a0->monomio->grd+1)*2);
	multiplicarPorPotencia(&auxSuma4,(a0->monomio->grd+1));
	liberarMemoria(&auxSuma1);
	liberarMemoria(&auxSuma2);
	auxSuma1=sumarPolinomios(auxMult1,auxSuma4);
	liberarMemoria(&auxMult1);
	liberarMemoria(&auxSuma4);
	auxSuma2=sumarPolinomios(auxSuma1,auxMult2);
	liberarMemoria(&auxSuma1);
	liberarMemoria(&auxMult2);
	return auxSuma2;
}






/**
 * multiplicarPorPotencia:
 * 
 * Función que recibe un grado y se lo suma a la variable grd de cada monomio del
 * polinomio.
 */
void multiplicarPorPotencia(struct Polinomio **pol, long grd){
	struct Polinomio *it=*pol;
	while(it!=NULL){
		(it->monomio->grd)+=grd;
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
void liberarMemoria(struct Polinomio **pol){
	struct Polinomio *aux;
	while(*pol!=NULL){
		aux=(*pol)->sig;
		free((*pol)->monomio);
		free((*pol));
		(*pol)=aux;
	}
	(*pol)=NULL;
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
