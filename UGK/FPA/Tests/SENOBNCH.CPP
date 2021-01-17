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
#define MAX_CUENTA 65536

ENTERO aux, TotalL, i, TotalH;

REAL auxr;

LARGO tiempo;

LOGICO seguir;

CF1 auxcf1, pimed (1.570796327), p(1.0);
extern CF0 c;

PROC esperar_sig_click()
PPIO
tiempo = biostime(0, 0L);
REPETIR Mientras  tiempo == biostime(0, 0L) FREPETIR
tiempo++;
/*Esperamos a que se produzca el primer tick de reloj para comenzar el testeo.*/
FIN

PROG_PPAL

LARGO Total;
CARACTER cadena[100], *cadena1;
ALEATORIO semilla;
FILE *fichero;

#define FICHERO  "c:senobnch.res"
#define continuar() ((biostime(0,0L) - tiempo) < TOTAL_CLICKS)

SI (fichero = fopen (FICHERO, "w")) == NULL
ENTONCES cout << "Error. Fichero " << FICHERO << " no ha podido ser accedido." << endl;
		 exit (-1);
FSI

inicializa_funciones();

cadena1 = "Resultados del benchmark. \n\n";
fwrite (cadena1, strlen (cadena1), 1, fichero);

Total= 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

/* Testeamos cuantos senos en coma flotante puede realizar en 10 segundos. */

E1:
SI continuar()
ENTONCES auxr = sin (semilla.alea());
		 auxr = sin (semilla.alea());
		 auxr = sin (semilla.alea());
		 auxr = sin (semilla.alea());
		 auxr = sin (semilla.alea());
		 auxr = sin (semilla.alea());
		 auxr = sin (semilla.alea());
		 auxr = sin (semilla.alea());
		 auxr = sin (semilla.alea());
		 auxr = sin (semilla.alea());
		 ++Total;
		 goto E1;
FSI

sprintf (cadena, "Total senos reales / segundo = %d \n",
		Total);
cout << cadena << endl;
fwrite (cadena, strlen (cadena), 1, fichero);

Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

/* Testeamos cuantos senos en coma fija por series de Taylor  puede realizar en 10 segundos. */

E2:
auxcf1 = p*CF1(semilla.alea());
SI continuar()
ENTONCES c = auxcf1.senoasm ();
		 c = auxcf1.senoasm ();
		 c = auxcf1.senoasm ();
		 c = auxcf1.senoasm ();
		 c = auxcf1.senoasm ();
		 c = auxcf1.senoasm ();
		 c = auxcf1.senoasm ();
		 c = auxcf1.senoasm ();
		 c = auxcf1.senoasm ();
		 c = auxcf1.senoasm ();
		 Total++;
		 goto E2;
FSI

sprintf (cadena, "Total senos Taylor / segundo = %d \n",
		Total);
cout << cadena << endl;
fwrite (cadena, strlen (cadena), 1, fichero);

Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

/* Testeamos cuantos senos en coma flotante puede realizar en 10 segundos. */

E3:
auxcf1 = pimed*CF1(semilla.alea());
SI continuar()
ENTONCES c = auxcf1.seno ();
		 c = auxcf1.seno ();
		 c = auxcf1.seno ();
		 c = auxcf1.seno ();
		 c = auxcf1.seno ();
		 c = auxcf1.seno ();
		 c = auxcf1.seno ();
		 c = auxcf1.seno ();
		 c = auxcf1.seno ();
		 c = auxcf1.seno ();
		 ++Total;
		 goto E3;
FSI

sprintf (cadena, "Total senos tabla / segundo = %d \n",
		Total);
cout << cadena << endl;
fwrite (cadena, strlen (cadena), 1, fichero);

Total = 0;
semilla.pon_semilla (semilla.selecciona_semilla(1));
esperar_sig_click();

/* Testeamos cuantos senos en coma flotante puede realizar en 10 segundos. */

E4:
auxcf1 = pimed*CF1(semilla.alea());
SI continuar()
ENTONCES c = auxcf1.senoil ();
		 c = auxcf1.senoil ();
		 c = auxcf1.senoil ();
		 c = auxcf1.senoil ();
		 c = auxcf1.senoil ();
		 c = auxcf1.senoil ();
		 c = auxcf1.senoil ();
		 c = auxcf1.senoil ();
		 c = auxcf1.senoil ();
		 c = auxcf1.senoil ();
		 ++Total;
		 goto E4;
FSI

sprintf (cadena, "Total senos tabla + IL / segundo = %d \n",
		Total);
cout << cadena << endl;
fwrite (cadena, strlen (cadena), 1, fichero);

fclose (fichero);
FIN_PROG_PPAL