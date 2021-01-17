#include <iostream.h>
#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <bios.h>
#include <alea.h>
#include <CF0.h>

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
REAL auxr;
CF0 auxcf0, aux2cf0;

#define continuar() ((biostime(0,0L) - tiempo) < TOTAL_CLICKS)

inicializa_raices ();

cout << "Resultados del benchmark. \n\n";
Total= 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

/* Testeamos cuantas raices cuadradas en coma flotante puede realizar en 10 segundos. */

E1:
auxr = double(semilla.alea());
SI continuar()
ENTONCES auxr = sqrt (auxr);
		 auxr = sqrt (auxr);
		 auxr = sqrt (auxr);
		 auxr = sqrt (auxr);
		 auxr = sqrt (auxr);
		 auxr = sqrt (auxr);
		 auxr = sqrt (auxr);
		 auxr = sqrt (auxr);
		 auxr = sqrt (auxr);
		 auxr = sqrt (auxr);
		 ++Total;
		 goto E1;
FSI

cout << "Total raices cuadradas reales / segundo = " << Total <<endl;

Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

/* Testeamos cuantas raices cuadradas en coma fija por tabla se pueden realizar en 10 segundos. */

E2:
auxcf0 = semilla.alea();
SI continuar()
ENTONCES aux2cf0 = auxcf0.sqrt ();
		 aux2cf0 = auxcf0.sqrt ();
		 aux2cf0 = auxcf0.sqrt ();
		 aux2cf0 = auxcf0.sqrt ();
		 aux2cf0 = auxcf0.sqrt ();

		 aux2cf0 = auxcf0.sqrt ();
		 aux2cf0 = auxcf0.sqrt ();
		 aux2cf0 = auxcf0.sqrt ();
		 aux2cf0 = auxcf0.sqrt ();
		 aux2cf0 = auxcf0.sqrt ();
		 Total++;
		 goto E2;
FSI

cout << "Total raices cuadradas coma fija / segundo = " <<	Total << endl;

Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

/* Testeamos cuantas raices cuadradas en coma fija con interpolacion lineal
   pueden realizar en 10 segundos. */

E3:
auxcf0 = semilla.alea();
SI continuar()
ENTONCES aux2cf0 = auxcf0.sqrtil ();
		 aux2cf0 = auxcf0.sqrtil ();
		 aux2cf0 = auxcf0.sqrtil ();
		 aux2cf0 = auxcf0.sqrtil ();
		 aux2cf0 = auxcf0.sqrtil ();
		 aux2cf0 = auxcf0.sqrtil ();
		 aux2cf0 = auxcf0.sqrtil ();
		 aux2cf0 = auxcf0.sqrtil ();
		 aux2cf0 = auxcf0.sqrtil ();
		 aux2cf0 = auxcf0.sqrtil ();
		 ++Total;
		 goto E3;
FSI

cout << "Total raices cuadradas tabla + I.L. / segundo = " << Total << endl;
Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

/* Testeamos cuantas raices cuadradas en coma fija con turbo por tabla se
   pueden realizar en 10 segundos. */

E4:
auxcf0 = semilla.alea();
SI continuar()
ENTONCES aux2cf0 = auxcf0.sqrt2 ();
		 aux2cf0 = auxcf0.sqrt2 ();
		 aux2cf0 = auxcf0.sqrt2 ();
		 aux2cf0 = auxcf0.sqrt2 ();
		 aux2cf0 = auxcf0.sqrt2 ();

		 aux2cf0 = auxcf0.sqrt2 ();
		 aux2cf0 = auxcf0.sqrt2 ();
		 aux2cf0 = auxcf0.sqrt2 ();
		 aux2cf0 = auxcf0.sqrt2 ();
		 aux2cf0 = auxcf0.sqrt2 ();
		 Total++;
		 goto E4;
FSI

cout << "Total raices cuadradas coma fija con turbo / segundo = " <<	Total << endl;

Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

/* Testeamos cuantas raices cuadradas con turbo en coma fija con interpolacion
   lineal pueden realizar en 10 segundos. */

E5:
auxcf0 = semilla.alea();
SI continuar()
ENTONCES aux2cf0 = auxcf0.sqrt2il ();
		 aux2cf0 = auxcf0.sqrt2il ();
		 aux2cf0 = auxcf0.sqrt2il ();
		 aux2cf0 = auxcf0.sqrt2il ();
		 aux2cf0 = auxcf0.sqrt2il ();
		 aux2cf0 = auxcf0.sqrt2il ();
		 aux2cf0 = auxcf0.sqrt2il ();
		 aux2cf0 = auxcf0.sqrt2il ();
		 aux2cf0 = auxcf0.sqrt2il ();
		 aux2cf0 = auxcf0.sqrt2il ();
		 ++Total;
		 goto E5;
FSI

cout << "Total raices cuadradas tabla turbo + I.L. / segundo = "
	 << Total << endl;

FIN_PROG_PPAL