//#include <dos.h>
#include <stdlib.h>
//#include <conio.h>
#include <stdio.h>
//#include <string.h>
#include <math.h>
#include <CF1.h>
#include <time.h>

#define TOTAL_CLICKS 10 * CLOCKS_PER_SEC  /*Cuando TOTAL_CLICKS sea 0, abandonamos el c¢mputo*/
#define TOTAL_BUCLES 1000000

#define continuar() (TOTAL_BUCLES > Total)
#define INC_SEMILLA 0.0000001

clock_t TiempoComienzo;
CF1 N (9.0), M5 (-5.0);
LARGO auxe3, auxe2, auxe1, Total, AuxEntero1, AuxEntero2;
REAL aux1, aux2, SemillaReal, TotalTiempo;
CF1 auxcf1, auxcf2, auxcf3, Semilla;

extern FILE *FicheroResultados;

/*Esperamos a que se produzca el primer tick de reloj para comenzar el testeo.*/
PROCEDIMIENTO esperar_sig_click()
PPIO
clock_t TiempoComienzo;

TiempoComienzo = clock();
REPETIR Mientras  TiempoComienzo == clock() FREPETIR
FIN_PROCEDIMIENTO

PROCEDIMIENTO Benchmark_ExponencialesCF1()

PPIO

inicializa_exponenciales();

fprintf(FicheroResultados, "\n Resultados del benchmark de exponenciales. \n\n");

Total= 0;
Semilla = 0.0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

/* Testeamos cuantas exponenciales en coma flotante puede realizar en 10 segundos. */

E1:
aux1 = -5.0 + SemillaReal * 9.0;
SemillaReal += INC_SEMILLA ;
SI continuar()
ENTONCES aux2 = exp(aux1);	//1
		 aux2 = exp(aux1);	//2
		 aux2 = exp(aux1);	//3
		 aux2 = exp(aux1);	//4
		 aux2 = exp(aux1);	//5

		 aux2 = exp(aux1);	//6
		 aux2 = exp(aux1);	//7
		 aux2 = exp(aux1);	//8
		 aux2 = exp(aux1);	//9
		 aux2 = exp(aux1);	//10
		 
		 aux2 = exp(aux1);	//11
		 aux2 = exp(aux1);	//12
		 aux2 = exp(aux1);	//13
		 aux2 = exp(aux1);	//14
		 aux2 = exp(aux1);	//15
		 
		 aux2 = exp(aux1);	//16
		 aux2 = exp(aux1);	//17
		 aux2 = exp(aux1);	//18
		 aux2 = exp(aux1);	//19
		 aux2 = exp(aux1);	//20
		 
		 ++Total;
		 goto E1;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total exponenciales reales / segundo = %f \n", (Total*20.0*CLOCKS_PER_SEC)/TotalTiempo);

Total = 0;
Semilla = 0;
esperar_sig_click();

/* Testeamos cuantas exponenciales en coma fija por tabla se pueden realizar en 10 segundos. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E2:
auxcf1 = M5 + Semilla * N;
Semilla.valor ++;
SI continuar()
ENTONCES auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();

		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();

		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();

		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 auxcf2  = auxcf1.exp ();
		 
		 Total++;
		 goto E2;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total exponenciales tabla / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
Semilla=0;
esperar_sig_click();

/* Testeamos cuantas exponenciales en coma fija mediante interpolacion lineal se pueden
   realizar en 10 segundos. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E3:
auxcf1 = M5 + Semilla * N;
Semilla.valor ++;
SI continuar()
ENTONCES auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();
		 auxcf2  = auxcf1.expil ();

		 ++Total;
		 goto E3;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total exponenciales tabla + I.L. / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

/* Testeamos cuantas exponenciales en coma fija mediante series de Taylor se pueden
   realizar en 10 segundos. */

Total = 0;
Semilla=0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E4:
auxcf1 = M5 + Semilla * N;
Semilla.valor ++;
SI continuar()
ENTONCES auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();
		 auxcf2  = auxcf1.expasm ();

		 ++Total;
		 goto E4;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total exponenciales Taylor / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

FIN_PROCEDIMIENTO

/////////////////////////////////////////////////////////////////////////////////////

PROCEDIMIENTO Benchmark_SenosCF1()

PPIO
LARGO Total;
CF1 auxcf1, Semilla;
CF0 auxcf2;
REAL aux1, aux2, SemillaReal;

inicializa_senos ();

fprintf(FicheroResultados, "\n Resultados del benchmark de senos. \n\n");

Total= 0;
Semilla = 0.0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

/* Testeamos cuantos senos en coma flotante puede realizar en 10 segundos. */

E1:
aux1 = SemillaReal;
SemillaReal += INC_SEMILLA ;
SI continuar()
ENTONCES aux2 = sin(aux1);	//1
		 aux2 = sin(aux1);	//2
		 aux2 = sin(aux1);	//3
		 aux2 = sin(aux1);	//4
		 aux2 = sin(aux1);	//5

		 aux2 = sin(aux1);	//6
		 aux2 = sin(aux1);	//7
		 aux2 = sin(aux1);	//8
		 aux2 = sin(aux1);	//9
		 aux2 = sin(aux1);	//10
		 
		 aux2 = sin(aux1);	//11
		 aux2 = sin(aux1);	//12
		 aux2 = sin(aux1);	//13
		 aux2 = sin(aux1);	//14
		 aux2 = sin(aux1);	//15
		 
		 aux2 = sin(aux1);	//16
		 aux2 = sin(aux1);	//17
		 aux2 = sin(aux1);	//18
		 aux2 = sin(aux1);	//19
		 aux2 = sin(aux1);	//20
		 
		 ++Total;
		 goto E1;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total senos reales / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
Semilla = 0;
esperar_sig_click();

/* Testeamos cuantos senos en coma fija por tabla se pueden realizar en 10 segundos. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E2:
auxcf1 = Semilla;
Semilla.valor ++;
SI continuar()
ENTONCES auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();

		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();

		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();

		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 auxcf2  = auxcf1.seno ();
		 
		 Total++;
		 goto E2;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total senos tabla / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
Semilla=0;
esperar_sig_click();

/* Testeamos cuantos senos en coma fija mediante interpolacion lineal se pueden
   realizar en 10 segundos. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E3:
auxcf1 = Semilla;
Semilla.valor ++;
SI continuar()
ENTONCES auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();
		 auxcf2  = auxcf1.senoil ();

		 ++Total;
		 goto E3;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total senos tabla + I.L. / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

/* Testeamos cuantos senos en coma fija mediante series de Taylor se pueden
   realizar en 10 segundos. */

Total = 0;
Semilla=0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E4:
auxcf1 = Semilla;
Semilla.valor ++;
SI continuar()
ENTONCES auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();
		 auxcf2  = auxcf1.senoasm ();

		 ++Total;
		 goto E4;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total senos Taylor / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

FIN_PROCEDIMIENTO

/////////////////////////////////////////////////////////////////////////////////

PROCEDIMIENTO Benchmark_Aritmeticosfl()

PPIO

fprintf(FicheroResultados, "\n Resultados del benchmark aritméticos reales. \n\n");

Total= 0;
aux1 = 3.0;
aux2 = -111111223230.0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

/* Testeamos cuantas sumas en coma flotante puede realizar en 10 segundos. */

E1:
SI continuar()
ENTONCES aux2 += aux1 ;	//1
		 aux2 += aux1 ;	//2
		 aux2 += aux1 ;	//3
		 aux2 += aux1 ;	//4
		 aux2 += aux1 ;	//5

		 aux2 += aux1 ;	//6
		 aux2 += aux1 ;	//7
		 aux2 += aux1 ;	//8
		 aux2 += aux1 ;	//9
		 aux2 += aux1 ;	//10
		 
		 aux2 += aux1 ;	//11
		 aux2 += aux1 ;	//12
		 aux2 += aux1 ;	//13
		 aux2 += aux1 ;	//14
		 aux2 += aux1 ;	//15
		 
		 aux2 += aux1 ;	//16
		 aux2 += aux1 ;	//17
		 aux2 += aux1 ;	//18
		 aux2 += aux1 ;	//19
		 aux2 += aux1 ;	//20
		 
		 ++Total;
		 goto E1;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total sumas reales / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
esperar_sig_click();
aux1 = 0.00000001;
aux2 = 1.0;
/* Testeamos cuantos productos en coma flotante se pueden realizar en 10 segundos. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E2:
SI continuar()
ENTONCES aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;

		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;

		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;

		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 aux2 *= aux1 ;
		 
		 Total++;
		 goto E2;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total productos reales / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
esperar_sig_click();
aux1 = 1.00000001;
aux2 = 2.0;
/* Testeamos cuantas divisiones en coma flotante se pueden realizar en 10 segundos. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E3:
SI continuar()
ENTONCES aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;

		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;

		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;

		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 aux2 /= aux1 ;
		 
		 ++Total;
		 goto E3;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total divisiones reales / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

FIN


PROCEDIMIENTO Benchmark_Aritmeticoscf()

PPIO
fprintf(FicheroResultados, "\n Resultados del benchmark aritméticos en coma fija. \n\n");

/* Testeamos cuantas sumas en coma fija se pueden realizar en 10 segundos. */

Total = 0;
esperar_sig_click();
auxcf1.valor = 3;
auxcf2 = 2.0;

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E4:
SI continuar()
ENTONCES auxcf2 = auxcf2 + auxcf1 ;	//1
		 auxcf2 = auxcf2 + auxcf1 ;	//2
		 auxcf2 = auxcf2 + auxcf1 ;	//3
		 auxcf2 = auxcf2 + auxcf1 ;	//4
		 auxcf2 = auxcf2 + auxcf1 ;	//5

		 auxcf2 = auxcf2 + auxcf1 ;	//6
		 auxcf2 = auxcf2 + auxcf1 ;	//7
		 auxcf2 = auxcf2 + auxcf1 ;	//8
		 auxcf2 = auxcf2 + auxcf1 ;	//9
		 auxcf2 = auxcf2 + auxcf1 ;	//10
		 
		 auxcf2 = auxcf2 + auxcf1 ;	//11
		 auxcf2 = auxcf2 + auxcf1 ;	//12
		 auxcf2 = auxcf2 + auxcf1 ;	//13
		 auxcf2 = auxcf2 + auxcf1 ;	//14
		 auxcf2 = auxcf2 + auxcf1 ;	//15
		 
		 auxcf2 = auxcf2 + auxcf1 ;	//16
		 auxcf2 = auxcf2 + auxcf1 ;	//17
		 auxcf2 = auxcf2 + auxcf1 ;	//18
		 auxcf2 = auxcf2 + auxcf1 ;	//19
		 auxcf2 = auxcf2 + auxcf1 ;	//20
		 
		 ++Total;
		 goto E4;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total sumas en coma fija / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
esperar_sig_click();
auxcf1 = 1.0000001;
auxcf2 = 34.21344;
/* Testeamos cuantos productos en coma fija se pueden realizar en 10 segundos. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E5:
SI continuar()
ENTONCES auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;

		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;

		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;

		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 auxcf3= auxcf2 * auxcf1 ;
		 
		 Total++;
		 goto E5;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total productos en coma fija / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
esperar_sig_click();
auxcf1 = 1.00000001;
auxcf2 = 0.99;
/* Testeamos cuantas exponenciales en coma fija se pueden realizar en 10 segundos. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E6:
SI continuar()
ENTONCES auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;

		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;

		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;

		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 auxcf2 = auxcf2 / auxcf1 ;
		 
		 ++Total;
		 goto E6;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total divisiones en coma fija / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

FIN

PROCEDIMIENTO Benchmark_Aritmeticosent()

PPIO
fprintf(FicheroResultados, "\n Resultados del benchmark aritméticos enteros. \n\n");

/* Testeamos cuantas sumas en coma fija se pueden realizar en 10 segundos. */

Total = 0;
esperar_sig_click();
auxe1 = 3;
auxe2 = 2;

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E7:
SI continuar()
ENTONCES auxe2 = auxe2 + auxe1 ;	//1
		 auxe2 = auxe2 + auxe1 ;	//2
		 auxe2 = auxe2 + auxe1 ;	//3
		 auxe2 = auxe2 + auxe1 ;	//4
		 auxe2 = auxe2 + auxe1 ;	//5

		 auxe2 = auxe2 + auxe1 ;	//6
		 auxe2 = auxe2 + auxe1 ;	//7
		 auxe2 = auxe2 + auxe1 ;	//8
		 auxe2 = auxe2 + auxe1 ;	//9
		 auxe2 = auxe2 + auxe1 ;	//10
		 
		 auxe2 = auxe2 + auxe1 ;	//11
		 auxe2 = auxe2 + auxe1 ;	//12
		 auxe2 = auxe2 + auxe1 ;	//13
		 auxe2 = auxe2 + auxe1 ;	//14
		 auxe2 = auxe2 + auxe1 ;	//15
		 
		 auxe2 = auxe2 + auxe1 ;	//16
		 auxe2 = auxe2 + auxe1 ;	//17
		 auxe2 = auxe2 + auxe1 ;	//18
		 auxe2 = auxe2 + auxe1 ;	//19
		 auxe2 = auxe2 + auxe1 ;	//20
		 
		 ++Total;
		 goto E7;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total sumas enteras / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
esperar_sig_click();
auxe1 = 12435;
auxe2 = 12445;
/* Testeamos cuantos productos en coma fija se pueden realizar en 10 segundos. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E8:
SI continuar()
ENTONCES auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;

		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;

		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;

		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 auxe3 = auxe2 * auxe1 ;
		 
		 Total++;
		 goto E8;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total productos enteros / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
esperar_sig_click();
auxe1 = 12345;
auxe2 = 123456789;
/* Testeamos cuantas exponenciales en coma fija se pueden realizar en 10 segundos. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E9:
SI continuar()
ENTONCES auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;

		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;

		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;

		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 auxe3 = auxe2 / auxe1 ;
		 
		 ++Total;
		 goto E9;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total divisiones enteras / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

FIN_PROCEDIMIENTO

/////////////////////////////////////////////////////////////////////////////////////

PROCEDIMIENTO Benchmark_RaicesCF1()

PPIO

inicializa_raices();

fprintf(FicheroResultados, "\n Resultados del benchmark de raices. \n\n");

Total= 0;
aux1 = 0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

/* Testeamos cuantos segundos tarda en realizar 20.000.000 de raices cuadradas en coma flotante. */

E10:
aux1 += 0.00001;
SI continuar()
ENTONCES aux2 = sqrt(aux1);	//1
		 aux2 = sqrt(aux1);	//2
		 aux2 = sqrt(aux1);	//3
		 aux2 = sqrt(aux1);	//4
		 aux2 = sqrt(aux1);	//5

		 aux2 = sqrt(aux1);	//6
		 aux2 = sqrt(aux1);	//7
		 aux2 = sqrt(aux1);	//8
		 aux2 = sqrt(aux1);	//9
		 aux2 = sqrt(aux1);	//10
		 
		 aux2 = sqrt(aux1);	//11
		 aux2 = sqrt(aux1);	//12
		 aux2 = sqrt(aux1);	//13
		 aux2 = sqrt(aux1);	//14
		 aux2 = sqrt(aux1);	//15
		 
		 aux2 = sqrt(aux1);	//16
		 aux2 = sqrt(aux1);	//17
		 aux2 = sqrt(aux1);	//18
		 aux2 = sqrt(aux1);	//19
		 aux2 = sqrt(aux1);	//20
		 
		 ++Total;
		 goto E10;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total raices reales / segundo = %f \n", (Total*20.0*CLOCKS_PER_SEC)/TotalTiempo);

Total = 0;
auxcf1.valor = 0;
esperar_sig_click();

/* Testeamos cuantos segundos tarda en realizar 20.000.000 de raices cuadradas en coma fija por tabla. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E11:
auxcf1.valor += 16;
SI continuar()
ENTONCES auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();

		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();

		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();

		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 auxcf2  = auxcf1.sqrt ();
		 
		 Total++;
		 goto E11;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total raices tabla / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
auxcf1.valor = 0;
esperar_sig_click();

/* Testeamos cuantos segundos tarda en realizar 20.000.000 de raices cuadradas en coma fija coma fija mediante interpolacion lineal. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E12:
auxcf1.valor += 16;
SI continuar()
ENTONCES auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();
		 auxcf2  = auxcf1.sqrtil ();

		 ++Total;
		 goto E12;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total raices tabla + I.L. / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

/* Testeamos cuantos segundos tarda en realizar 20.000.000 de raices cuadradas en coma fija mediante una nueva versión. */

Total = 0;
auxcf1.valor = 0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E13:
auxcf1.valor += 16;
SI continuar()
ENTONCES auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();
		 auxcf2  = auxcf1.sqrt2 ();

		 ++Total;
		 goto E13;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total raices 2 / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

/* Testeamos cuantos segundos tarda en realizar 20.000.000 de raices cuadradas en coma fija mediante una nueva versión e interpolación lineal. */

Total = 0;
auxcf1.valor = 0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E14:
auxcf1.valor += 16;
SI continuar()
ENTONCES auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();
		 auxcf2  = auxcf1.sqrt2il ();

		 ++Total;
		 goto E14;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total raices 2 + I.L. / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

FIN_PROCEDIMIENTO

/////////////////////////////////////////////////////////////////////////////////////

PROCEDIMIENTO Benchmark_LogaritmosCF1()

PPIO

inicializa_logaritmos();

fprintf(FicheroResultados, "\n Resultados del benchmark de logaritmos. \n\n");

Total= 0;
aux1 = 0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

/* Testeamos cuantos segundos tarda en realizar 20.000.000 de raices cuadradas en coma flotante. */

E15:
aux1 += 0.00001;
SI continuar()
ENTONCES aux2 = log(aux1);	//1
		 aux2 = log(aux1);	//2
		 aux2 = log(aux1);	//3
		 aux2 = log(aux1);	//4
		 aux2 = log(aux1);	//5

		 aux2 = log(aux1);	//6
		 aux2 = log(aux1);	//7
		 aux2 = log(aux1);	//8
		 aux2 = log(aux1);	//9
		 aux2 = log(aux1);	//10
		 
		 aux2 = log(aux1);	//11
		 aux2 = log(aux1);	//12
		 aux2 = log(aux1);	//13
		 aux2 = log(aux1);	//14
		 aux2 = log(aux1);	//15
		 
		 aux2 = log(aux1);	//16
		 aux2 = log(aux1);	//17
		 aux2 = log(aux1);	//18
		 aux2 = log(aux1);	//19
		 aux2 = log(aux1);	//20
		 
		 ++Total;
		 goto E15;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total logaritmos reales / segundo = %f \n", (Total*20.0*CLOCKS_PER_SEC)/TotalTiempo);

Total = 0;
auxcf1.valor = 0;
esperar_sig_click();

/* Testeamos cuantos segundos tarda en realizar 20.000.000 de raices cuadradas en coma fija por tabla. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E16:
auxcf1.valor += 16;
SI continuar()
ENTONCES auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();

		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();

		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();

		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 auxcf2  = auxcf1.ln ();
		 
		 Total++;
		 goto E16;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total logaitmos tabla / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

Total = 0;
auxcf1.valor = 0;
esperar_sig_click();

/* Testeamos cuantos segundos tarda en realizar 20.000.000 de raices cuadradas en coma fija coma fija mediante interpolacion lineal. */

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E17:
auxcf1.valor += 16;
SI continuar()
ENTONCES auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();
		 auxcf2  = auxcf1.lnil ();

		 ++Total;
		 goto E17;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total logaritmos tabla + I.L. / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

/* Testeamos cuantos segundos tarda en realizar 20.000.000 de raices cuadradas en coma fija mediante una nueva versión. */

Total = 0;
auxcf1.valor = 0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E18:
auxcf1.valor += 16;
SI continuar()
ENTONCES auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();
		 auxcf2  = auxcf1.ln2 ();

		 ++Total;
		 goto E18;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total logaritmos 2 / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

/* Testeamos cuantos segundos tarda en realizar 20.000.000 de raices cuadradas en coma fija mediante una nueva versión e interpolación lineal. */

Total = 0;
auxcf1.valor = 0;
esperar_sig_click();

//Se indica la cantidad de segundos a realizar la prueba
TiempoComienzo = clock();

E19:
auxcf1.valor += 16;
SI continuar()
ENTONCES auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();
		 auxcf2  = auxcf1.ln2il ();

		 ++Total;
		 goto E19;
FSI

TotalTiempo = clock() - TiempoComienzo;

fprintf(FicheroResultados, "Total logaritmos 2 + I.L. / segundo = %f \n", Total*20.0*CLOCKS_PER_SEC/TotalTiempo);

FIN_PROCEDIMIENTO

/////////////////////////////////////////////////////////////////////////////////////
