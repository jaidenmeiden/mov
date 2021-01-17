#include <iostream.h>
#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <bios.h>
#include <alea.h>
#include <CF1.h>

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
CF1 CERO5 (0.000001);
REAL auxr, auxr1, auxr2;
CF1 auxcf1, auxcf2, auxcf3;

#define continuar() ((biostime(0,0L) - tiempo) < TOTAL_CLICKS)

inicializa_logaritmos();

cout << "Resultados del benchmark. \n\n";
Total= 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos senos en coma flotante puede realizar en 10 segundos. */

E1:
auxr1 = 0.000001 + double(semilla.alea());
SI continuar()
ENTONCES auxr = log (auxr1);
		 auxr = log (auxr1);
		 auxr = log (auxr1);
		 auxr = log (auxr1);
		 auxr = log (auxr1);
		 auxr = log (auxr1);
		 auxr = log (auxr1);
		 auxr = log (auxr1);
		 auxr = log (auxr1);
		 auxr = log (auxr1);
		 ++Total;
		 goto E1;
FSI

cout << "Total logaritmos reales / segundo = " << Total <<endl;

Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos logaritmos en coma fija por tabla se pueden realizar en 10 segundos. */

E2:
auxcf1 = CERO5 + CF1(semilla.alea());
SI continuar()
ENTONCES auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();

		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 Total++;
		 goto E2;
FSI

cout << "Total logaritmos / segundo = " <<	Total << endl;

Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos senos en coma flotante puede realizar en 10 segundos. */

E3:
auxcf1 = CERO5 + CF1(semilla.alea());
SI continuar()
ENTONCES auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 ++Total;
		 goto E3;
FSI

cout << "Total logaritmos tabla + I.L. / segundo = " << Total << endl;

Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos logaritmos con turbo en coma fija por tabla se pueden realizar en 10 segundos. */

E4:
auxcf1 = CERO5 + CF1(semilla.alea());
SI continuar()
ENTONCES auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();

		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 auxcf2 = auxcf1.ln ();
		 Total++;
		 goto E4;
FSI

cout << "Total logaritmos turbo / segundo = " <<	Total << endl;

Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos senos en coma flotante puede realizar en 10 segundos. */

E5:
auxcf1 = CERO5 + CF1(semilla.alea());
SI continuar()
ENTONCES auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 auxcf2 = auxcf1.lnil ();
		 ++Total;
		 goto E5;
FSI

cout << "Total logaritmos tabla + I.L. con turbo / segundo = " << Total << endl;

Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos senos en coma flotante puede realizar en 10 segundos. */

E6:
auxcf1 = semilla.alea();
auxcf3 = -auxcf1;
SI continuar()
ENTONCES auxcf2 = auxcf3 * auxcf1;
		 auxcf2 = auxcf3 * auxcf1;
		 auxcf2 = auxcf3 * auxcf1;
		 auxcf2 = auxcf3 * auxcf1;
		 auxcf2 = auxcf3 * auxcf1;
		 auxcf2 = auxcf3 * auxcf1;
		 auxcf2 = auxcf3 * auxcf1;
		 auxcf2 = auxcf3 * auxcf1;
		 auxcf2 = auxcf3 * auxcf1;
		 auxcf2 = auxcf3 * auxcf1;
		 ++Total;
		 goto E6;
FSI

cout << "Total productos en coma fija / segundo = " << Total << endl;

Total = 0;
semilla.selecciona_semilla(1);
esperar_sig_click();

/* Testeamos cuantos senos en coma flotante puede realizar en 10 segundos. */

E7:
auxr1 = semilla.alea();
auxr  = -auxr1;
SI continuar()
ENTONCES auxr2 = auxr * auxr1;
		 auxr2 = auxr * auxr1;
		 auxr2 = auxr * auxr1;
		 auxr2 = auxr * auxr1;
		 auxr2 = auxr * auxr1;
		 auxr2 = auxr * auxr1;
		 auxr2 = auxr * auxr1;
		 auxr2 = auxr * auxr1;
		 auxr2 = auxr * auxr1;
		 auxr2 = auxr * auxr1;
		 ++Total;
		 goto E7;
FSI

cout << "Total productos en coma flotante / segundo = " << Total << endl;

FIN_PROG_PPAL
