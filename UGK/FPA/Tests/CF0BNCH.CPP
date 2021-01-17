#include <iostream.h>
#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <bios.h>
#include <alea.h>

#define INT_RELOJ 0x1C
#define TOTAL_CLICKS 182 /*Cuando TOTAL_CLICKS sea 0, abandonamos el c¢mputo*/
#define SEGUNDOS 10.0   /*182 ticks equivalen a 10 segundos.*/

LARGO tiempo;

PROC esperar_sig_click()
PPIO
tiempo = biostime(0, 0L);
REPETIR Mientras  tiempo == biostime(0, 0L) FREPETIR
tiempo++;
/*Esperamos a que se produzca el primer tick de reloj para comenzar el testeo.*/
FIN

PROG_PPAL

LARGO Total, auxl;
ALEATORIO semilla;
REAL auxr, auxr1, auxr2;
CF0 auxcf1, auxcf2, auxcf3;

#define continuar() ((biostime(0,0L) - tiempo) < TOTAL_CLICKS)

inicializa_raices();

cout << "Resultados del benchmark. \n\n";
Total= 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos raices cuadradas en coma flotante puede realizar en 10 segundos. */

E1:
auxr1 = 0.000001 + double(semilla.alea());
SI continuar()
ENTONCES auxr = sqrt (auxr1);
		 auxr = sqrt (auxr1);
		 auxr = sqrt (auxr1);
		 auxr = sqrt (auxr1);
		 auxr = sqrt (auxr1);
		 auxr = sqrt (auxr1);
		 auxr = sqrt (auxr1);
		 auxr = sqrt (auxr1);
		 auxr = sqrt (auxr1);
		 auxr = sqrt (auxr1);
		 ++Total;
		 goto E1;
FSI

cout << "Total raiz cuadradas reales / segundo = " << Total <<endl;

Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos raiz cuadradas en coma fija por tabla se pueden realizar en 10 segundos. */

E2:
auxcf1 = semilla.alea();
SI continuar()
ENTONCES auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();

		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 Total++;
		 goto E2;
FSI

cout << "Total raices cuadradas / segundo = " <<	Total << endl;

Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos raices cuadradas en coma flotante puede realizar en 10 segundos. */

E3:
auxcf1 = semilla.alea();
SI continuar()
ENTONCES auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 ++Total;
		 goto E3;
FSI

cout << "Total raices cuadradas tabla + I.L. / segundo = " << Total << endl;
Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos raices cuadradas en coma fija se pueden realizar en 10 segundos. */

E4:
auxcf1 = semilla.alea();
SI continuar()
ENTONCES auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 auxcf2 = auxcf1.sqrt ();
		 ++Total;
		 goto E4;
FSI

cout << "Total raices cuadradas tabla turbo / segundo = " << Total << endl;
Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos raices cuadradas en coma fija puede realizar en 10 segundos. */

E5:
auxcf1 = semilla.alea();
SI continuar()
ENTONCES auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 auxcf2 = auxcf1.sqrtil ();
		 ++Total;
		 goto E5;
FSI

cout << "Total raices cuadradas tabla + I.L. + turbo / segundo = " << Total << endl;

Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos raices cuadradas en coma fija puede realizar en 10 segundos. */

E6:
auxcf1 = semilla.alea();
auxcf2 = -auxcf1;
SI continuar()
ENTONCES auxcf3 = auxcf2 * auxcf1;
		 auxcf3 = auxcf2 * auxcf1;
		 auxcf3 = auxcf2 * auxcf1;
		 auxcf3 = auxcf2 * auxcf1;
		 auxcf3 = auxcf2 * auxcf1;
		 auxcf3 = auxcf2 * auxcf1;
		 auxcf3 = auxcf2 * auxcf1;
		 auxcf3 = auxcf2 * auxcf1;
		 auxcf3 = auxcf2 * auxcf1;
		 auxcf3 = auxcf2 * auxcf1;
		 ++Total;
		 goto E6;
FSI

cout << "Total productos coma fija / segundo = " << Total << endl;

Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos raices cuadradas en coma fija puede realizar en 10 segundos. */

E7:
auxr1 = semilla.alea();
auxr  = -auxr1;
SI continuar()
ENTONCES auxr2 = auxr1 * auxr;
		 auxr2 = auxr1 * auxr;
		 auxr2 = auxr1 * auxr;
		 auxr2 = auxr1 * auxr;
		 auxr2 = auxr1 * auxr;
		 auxr2 = auxr1 * auxr;
		 auxr2 = auxr1 * auxr;
		 auxr2 = auxr1 * auxr;
		 auxr2 = auxr1 * auxr;
		 auxr2 = auxr1 * auxr;
		 ++Total;
		 goto E7;
FSI

cout << "Total productos coma flotante / segundo = " << Total << endl;

FIN_PROG_PPAL