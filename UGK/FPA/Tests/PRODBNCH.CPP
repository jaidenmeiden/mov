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
#define TOTAL_CLICKS 	 182 	 /*Cuando TOTAL_CLICKS sea 0, abandonamos el c¢mputo*/
#define SEGUNDOS 		  10.0   /*182 ticks equivalen a 10 segundos.*/
#define TOTAL_OPERACIONES 20.0

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
CF0 CERO5 (0.01);
REAL auxr, auxr1, auxr2;
CF0 auxcf, auxcf1, auxcf2;

#define continuar() ((biostime(0,0L) - tiempo) < TOTAL_CLICKS)

cout << "Resultados del benchmark. \n\n";
Total= 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

E1:
auxr2 = auxr1 = double(semilla.alea());
SI continuar()
ENTONCES auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;

		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;

		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;

		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;

		 ++Total;
		 goto E1;
FSI

cout << "Total productos reales / segundo = " << Total * TOTAL_OPERACIONES / SEGUNDOS << endl;

Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

E2:
auxcf2 = auxcf1 = semilla.alea();
SI continuar()
ENTONCES auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;

		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;

		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;

		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;
		 auxcf = auxcf1 * auxcf2;

		 Total++;
		 goto E2;
FSI

cout << "Total productos coma fija / segundo = " <<	Total * TOTAL_OPERACIONES / SEGUNDOS  << endl;

Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

/* Testeamos cuantas divisiones en coma flotante puede realizar en 10 segundos. */

E3:
auxr2 = auxr1 = double(semilla.alea());
SI continuar()
ENTONCES auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;

		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;

		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;

		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;

		 ++Total;
		 goto E3;
FSI

cout << "Total divisiones reales / segundo = " << Total * TOTAL_OPERACIONES / SEGUNDOS << endl;


Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

E4:
auxcf1 = semilla.alea();
auxcf2 = auxcf1 + CERO5;
auxcf1 = auxcf1 - CERO5;


SI continuar()
ENTONCES auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;

		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;

		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;

		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 Total++;
		 goto E4;
FSI

cout << "Total divisiones coma fija / segundo = " <<	Total * TOTAL_OPERACIONES / SEGUNDOS  << endl;

Total= 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

E5:
auxr2 = auxr1 = double(semilla.alea());
SI continuar()
ENTONCES auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;

		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;

		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;

		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;

		 ++Total;
		 goto E5;
FSI

cout << "Total productos reales / segundo = " << Total * TOTAL_OPERACIONES / SEGUNDOS << endl;
Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

E6:
auxcf2 = auxcf1 = semilla.alea();
SI continuar()
ENTONCES auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;

		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;

		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;

		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2;
		 Total++;
		 goto E6;
FSI

cout << "Total sumas coma fija / segundo = " <<	Total * TOTAL_OPERACIONES / SEGUNDOS  << endl;

FIN_PROG_PPAL