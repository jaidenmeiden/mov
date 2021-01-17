/*  Programa de prueba de la unidad de numeros en Coma Fija con 32 bits para
	representar la parte decimal y 0 para la entera. */

#include <math.h>
#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <bios.h>
#include <cf1.h>
#include <utilidad.h>

CF1 x;
CF0 y;

#define TOTAL_INTERVALOS  100
#define TOTAL_PRUEBAS 	 1000

#define INT_RELOJ 0x1C
#define TOTAL_CLICKS 182 /*Cuando TOTAL_CLICKS sea 0, abandonamos el c¢mputo*/
#define SEGUNDOS 10.0   /*182 ticks equivalen a 10 segundos.*/

LARGO tiempo;
CF1 N (9.0), M5 (-5.0);

REAL    valor,  	//Valor del que hay que obtener las raices cuadradas.
		errorTa,   	//Error acceso a tablas.
		errorTIL,  	//Error acceso a tablas e interpolacion lineal.
		errorTaD,   //Error acceso a tablas directas.
		errorTDIL,  //Error acceso a tablas directas e interpolacion lineal.
		INC_PRUEBA;	//Incremento del valor con el que se calcula la funcion

CF1		valorcf1;	//variable "valor" en formato CF1

ENTERO intervalo, pruebas;

#define TAMANO_CADENA 100
CARACTER cadena [TAMANO_CADENA], *cadena1;

FILE *fichero;


PROC esperar_sig_click()
PPIO
tiempo = biostime(0, 0L);
REPETIR Mientras  tiempo == biostime(0, 0L) FREPETIR
tiempo++;
/*Esperamos a que se produzca el primer tick de reloj para comenzar el testeo.*/
FIN

PROC calcula_potencia ()
PPIO

LARGO Total;
REAL auxr1 = 0.123456789, auxr2 = 0.876543211, auxr;
CF1 auxcf1 = auxr1, auxcf2 = auxr2, auxcf;
LARGO auxl, auxl1 = auxcf1.valor, auxl2 = auxcf2.valor;

#define continuar() ((biostime(0,0L) - tiempo) < TOTAL_CLICKS)

cout << "Pulse una tecla para continuar." << endl;
getch ();
cout << "Resultados del benchmark. \n\n";

Total= 0;
esperar_sig_click();

// Testeamos cuantos productos reales en coma flotante se pueden realizar en 10 segundos.

E1:
SI continuar()
ENTONCES auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2; auxr = auxr1 * auxr2; auxr = auxr1 * auxr2;
		 auxr = auxr1 * auxr2;
		 ++Total;
		 goto E1;
FSI

cout << "Total productos reales / segundo = " << Total*4 << endl;

Total= 0;
esperar_sig_click();

// Testeamos cuantas divisiones reales en coma flotante se pueden realizar en 10 segundos.

E2:
SI continuar()
ENTONCES auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2; auxr = auxr1 / auxr2; auxr = auxr1 / auxr2;
		 auxr = auxr1 / auxr2;
		 ++Total;
		 goto E2;
FSI

cout << "Total divisiones reales / segundo = " << Total*4 << endl;

Total= 0;
esperar_sig_click();

// Testeamos cuantas sumas reales en coma flotante se pueden realizar en 10 segundos.

E3:
SI continuar()
ENTONCES auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2; auxr = auxr1 + auxr2; auxr = auxr1 + auxr2;
		 auxr = auxr1 + auxr2;
		 ++Total;
		 goto E3;
FSI

cout << "Total sumas reales / segundo = " << Total*4 << endl;

Total= 0;
esperar_sig_click();

// Testeamos cuantas restas reales en coma flotante se pueden realizar en 10 segundos.

E4:
SI continuar()
ENTONCES auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2; auxr = auxr1 - auxr2; auxr = auxr1 - auxr2;
		 auxr = auxr1 - auxr2;
		 ++Total;
		 goto E4;
FSI

cout << "Total restas reales / segundo = " << Total*4 << endl;


Total= 0;
esperar_sig_click();

/* Testeamos cuantos productos en coma fija se pueden realizar en 10 segundos. */

E5:
SI continuar()
ENTONCES auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2; auxcf = auxcf1 *auxcf2;
		 auxcf = auxcf1 *auxcf2;
		 ++Total;
		 goto E5;
FSI

cout << "Total productos coma fija / segundo = " << Total*4 << endl;

Total= 0;
esperar_sig_click();

/* Testeamos cuantas divisiones en coma fija se pueden realizar en 10 segundos. */

E6:
SI continuar()
ENTONCES auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2; auxcf = auxcf1 / auxcf2;
		 auxcf = auxcf1 / auxcf2;
		 ++Total;
		 goto E6;
FSI

cout << "Total divisiones coma fija / segundo = " << Total*4 << endl;

Total= 0;
esperar_sig_click();

/* Testeamos cuantas sumas en coma fija se pueden realizar en 10 segundos. */

E7:
SI continuar()
ENTONCES auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 auxcf = auxcf1 + auxcf2; auxcf = auxcf1 + auxcf2;
		 ++Total;
		 goto E7;
FSI

cout << "Total sumas coma fija / segundo = " << Total*16.1 << endl;

Total= 0;
esperar_sig_click();

/* Testeamos cuantas restas en coma fija se pueden realizar en 10 segundos. */

E8:
SI continuar()
ENTONCES auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2; auxcf = auxcf1 - auxcf2;
		 auxcf = auxcf1 - auxcf2;
		 ++Total;
		 goto E8;
FSI

cout << "Total restas coma fija / segundo = " << Total*16.1 << endl;

Total= 0;
esperar_sig_click();

/* Testeamos cuantos productos enteros se pueden realizar en 10 segundos. */

E9:
SI continuar()
ENTONCES auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2; auxl = auxl1 *auxl2; auxl = auxl1 *auxl2;
		 auxl = auxl1 *auxl2;
		 ++Total;
		 goto E9;
FSI

cout << "Total productos enteros / segundo = " << Total*8 << endl;

Total= 0;
esperar_sig_click();

/* Testeamos cuantas divisiones enteras se pueden realizar en 10 segundos. */

E10:
SI continuar()
ENTONCES auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 auxl = auxl1 / auxl2; auxl = auxl1 / auxl2;
		 ++Total;
		 goto E10;
FSI

cout << "Total divisiones enteras / segundo = " << Total*8 << endl;

Total= 0;
esperar_sig_click();

/* Testeamos cuantas sumas enteras se pueden realizar en 10 segundos. */

E11:
SI continuar()
ENTONCES auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2; auxl = auxl1 + auxl2; auxl = auxl1 + auxl2;
		 auxl = auxl1 + auxl2;
		 ++Total;
		 goto E11;
FSI

cout << "Total sumas enteras / segundo = " << Total*16 << endl;

Total= 0;
esperar_sig_click();

/* Testeamos cuantas restas enteras se pueden realizar en 10 segundos. */

E12:
SI continuar()
ENTONCES auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 auxl = auxl1 - auxl2; auxl = auxl1 - auxl2;
		 ++Total;
		 goto E12;
FSI

cout << "Total restas enteras / segundo = " << Total*16 << endl;

Total= 0;
esperar_sig_click();

/* Testeamos cuantos incrementos unitarios enteros se pueden realizar en 10 segundos. */

E13:
SI continuar()
ENTONCES auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 auxl++; auxl++; auxl++; auxl++; auxl++;
		 ++Total;
		 goto E13;
FSI

cout << "Total incrementos unitarios enteros / segundo = " << Total*20.05 << endl;


Total= 0;
esperar_sig_click();

/* Testeamos cuantos decrementos unitarios enteros se pueden realizar en 10 segundos. */

E14:
SI continuar()
ENTONCES auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 auxl--; auxl--; auxl--; auxl--; auxl--;
		 ++Total;
		 goto E14;
FSI

cout << "Total decrementos unitarios enteros / segundo = " << Total*20.05 << endl;


Total= 0;
esperar_sig_click();

/* Testeamos cuantos incrementos enteros se pueden realizar en 10 segundos. */

E15:
SI continuar()
ENTONCES auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 auxl+= auxl1; auxl+= auxl1; auxl+= auxl1; auxl+= auxl1;
		 ++Total;
		 goto E15;
FSI

cout << "Total incrementos enteros / segundo = " << Total*20.05 << endl;


Total= 0;
esperar_sig_click();

/* Testeamos cuantos decrementos enteros se pueden realizar en 10 segundos. */

E16:
SI continuar()
ENTONCES auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 auxl-= auxl1; auxl-= auxl1; auxl-= auxl1; auxl-= auxl1;
		 ++Total;
		 goto E16;
FSI

cout << "Total decrementos enteros / segundo = " << Total*20.05 << endl;


Total= 0;
esperar_sig_click();

/* Testeamos cuantos incrementos unitarios en coma fija se pueden realizar en 10 segundos. */

E17:
SI continuar()
ENTONCES ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf;	++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf;	++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf;	++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf;	++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf;	++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++auxcf; ++auxcf; ++auxcf; ++auxcf; ++auxcf;
		 ++Total;
		 goto E17;
FSI

cout << "Total incrementos unitarios en coma fija / segundo = " << Total*20.05 << endl;


Total= 0;
esperar_sig_click();

/* Testeamos cuantos decrementos unitarios en coma fija se pueden realizar en 10 segundos. */

E18:
SI continuar()
ENTONCES --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 --auxcf; --auxcf; --auxcf; --auxcf; --auxcf;
		 ++Total;
		 goto E18;
FSI

cout << "Total decrementos unitarios en coma fija / segundo = " << Total*20.05 << endl;


Total= 0;
esperar_sig_click();

/* Testeamos cuantos incrementos en coma fija se pueden realizar en 10 segundos. */

E19:
SI continuar()
ENTONCES auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1; auxcf+= auxcf1;
		 ++Total;
		 goto E19;
FSI

cout << "Total incrementos en coma fija / segundo = " << Total*8 << endl;


Total= 0;
esperar_sig_click();

/* Testeamos cuantos decrementos enteros se pueden realizar en 10 segundos. */

E20:
SI continuar()
ENTONCES auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1; auxcf-= auxcf1;
		 ++Total;
		 goto E20;
FSI

cout << "Total decrementos en coma fija / segundo = " << Total*8 << endl;

FIN


PROC calcula_errores ()
PPIO
REAL e;
e	     = sqrt (valor);
valorcf1 = valor;

errorTa  += absd (e - double (valorcf1.sqrt     ()));
errorTIL += absd (e - double (valorcf1.sqrtil   ()));
errorTaD += absd (e - double (valorcf1.sqrt2    ()));
errorTDIL+= absd (e - double (valorcf1.sqrt2il  ()));

valor    += INC_PRUEBA;
FIN

#define FICHERO "c:\\tstsqrt1.err"

PROC guarda (CARACTER *cadena)
PPIO
FILE *fichero;

SI (fichero = fopen (FICHERO, "a")) == NULL
ENTONCES cout << "Error, no se puede abrir el fichero especificado. \n";
		 exit(-1);
FSI
fwrite (cadena, strlen (cadena), 1, fichero);
fclose (fichero);
FIN

PROC contenido ( CF1 a)
PPIO
printf (" %15.10f \n", double (a));
FIN

PROC suma ( CF1 a, CF1 b)
PPIO
cout << double (a) << " + " << double (b) << " = " << double (a+b) << endl;
FIN

PROC resta ( CF1 a, CF1 b)
PPIO
cout << double (a) << " - " << double (b) << " = " << double (a-b) << endl;
FIN

PROC niega (CF1 a)
PPIO
cout << "El valor de -" << double (a) << " es " << double (-a) << endl;
FIN

PROC incdec ( CF1 a)
PPIO
a++;
cout << "++a = " << double (a) << " --a = ";
--a;
cout << double (a) << endl;

a += 1;
cout << "++a = " << double (a) << " --a = ";
a -= 1;
cout << double (a) << endl;
FIN

PROC compara ( CF1 a, CF1 b)
PPIO

SI  a < b
ENTONCES cout << double (a) << " es menor que " << double (b) << endl;
SINO	 cout << double (a) << " es mayor o igual que " << double (b) << endl;
FSI

SI  a <= b
ENTONCES cout << double (a) << " es menor o igual que " << double (b) << endl;
SINO	 cout << double (a) << " es mayor que " << double (b) << endl;
FSI

SI  a > b
ENTONCES cout << double (a) << " es mayor que " << double (b) << endl;
SINO	 cout << double (a) << " es menor o igual que " << double (b) << endl;
FSI

SI  a >= b
ENTONCES cout << double (a) << " es mayor o igual que " << double (b) << endl;
SINO	 cout << double (a) << " es menor que " << double (b) << endl;
FSI

SI  a == b
ENTONCES cout << double (a) << " es igual que " << double (b) << endl;
SINO	 cout << double (a) << " es distinto que " << double (b) << endl;
FSI

SI  a != b
ENTONCES cout << double (a) << " es distinto que " << double (b) << endl;
SINO	 cout << double (a) << " es igual que " << double (b) << endl;
FSI

cout << "Pulse una tecla para continuar." << endl;
getch();
FIN

PROC senos (CF1 f)
PPIO
cout << "Seno (" << double(f) << ") = " << sin (f) << " "
	 << double(f.senoasm()) << " " << double(f.seno())
	 << " " << double(f.senoil()) << "\n";
FIN

PROC exponen (CF1 f)
PPIO
cout << "Exp (" << double(f) << ") = " << exp (f) << " " << double(f.expasm())
	 << " " << double(f.exp()) << " " << double(f.expil()) << endl;
FIN

PROC raices (CF1 f)
PPIO
cout << "Raiz (" << double(f) << ") = " << sqrt (double (f))    << " "
										<< double (f.sqrt())    << " "
										<< double (f.sqrtil())  << " "
										<< double (f.sqrt2())   << " "
										<< double (f.sqrt2il()) << endl;
FIN

CF0 divide (CF1 a, CF1 b)
PPIO
y = a/b;
printf ("%3.9f / %3.9f = %3.9f \n",double (a), double (b), double(y));
DEVUELVE y;
FIN

CF1 multiplica (CF1 a, CF1 b)
PPIO
x = a*b;
printf ("%3.9f * %3.9f = %3.9f \n",double (a), double (b), double(x));
DEVUELVE x;
FIN

PROG_PPAL
CF0 a (-0.345);
CF1 b (a),
	f (-123.45678),
	d (1.000345),
	e;

	/*
inicializa_raices();
inicializa_senos();
inicializa_exponenciales();
inicializa_logaritmos();

//Es para ver si detecta la inicializacion de las tablas.
inicializa_raices();
inicializa_senos();
inicializa_exponenciales();
inicializa_logaritmos();

cout.precision (10);
cout << " " << double(a) << " " << double(b) << " " << double(f) << " "
	 << double(d) << " " << double(e) << "\n";

contenido (a);
niega 	(b);
suma 	(f, a);
compara (e, f);
resta   (b, f);

multiplica (0.000001, -0.000001);

compara (a, f);


e = 0.789012;
b = 3.456789;
f = multiplica (e, b);
e = multiplica (b, f);
f = multiplica (e, b);
e = multiplica (f, b);
b = multiplica (a, f);

getch();

a = divide (20.12345, 20.12347);
a = divide (0.12345, -10.34567);
a = divide (-0.12345, 10.34567);
f = divide (0.23456789, 10.78901234);
f = divide (-0.23456789, 10.78901234);
f = divide (-0.23456789, -10.78901234);

getch();

f = 99.0;
d = 111.45678;
e = 123.456789;
cout << double(f) << " " << double(d) << " " << double(e) << "\n";

f = 0.987654321;
d = 1.456789;
e = 0.123456789;
cout << double(f) << " " << double(d) << " " << double(e) << "\n";

getch();

cout << "Formato de representacion del seno:"
	 << " REAL, TAYLOR, TABLA E INTERPOLADA. \n";
senos (1.0);
senos (2.0);
senos (3.0);
senos (4.0);
senos (5.0);
senos (6.0);
senos (7.0);
senos (18.1234567890);
senos (95.1234567890);

getch();

exponen (-.0001);
exponen (-0.21320);
exponen (-1.0001);
exponen (-2.0);
exponen (-3.02);
exponen (-4.03);
exponen (-5.0);
exponen (-6.04);
exponen (-7.04);
exponen (-8.2345);
exponen (-2.2456);
exponen (-9.9876543210);

getch();

exponen (.203);
exponen (2.0);
exponen (3.0);
exponen (4.03);
exponen (2.2456);
exponen (0.9876543210);
exponen (.601);
exponen (-0.0);
exponen (0.0);
exponen (.00001);

getch();

inicializa_raices();

raices (0.2345678901);
raices (0.6723);
raices (0.9888723);
raices (0.111123);
raices (0.00003223);

raices (120.2345678901);
raices (34.6723);
raices (50.9888723);
raices (11.111123);
raices (5.00003223);

getch();

SI (fichero = fopen (FICHERO, "a")) == NULL
ENTONCES cout << "Error, no se puede abrir el fichero " << FICHERO
			  << "." << endl;
		 exit(-1);
FSI
cadena1 = "Formato de los resultados obtenidos. \n";
fwrite (cadena1, strlen (cadena1), 1, fichero);
fclose (fichero);

guarda ("Valor y raiz cuadrada asociada. \n");
guarda ("Error en Tablas / Tablas con I.L. y con turbo / turbo + I.L. \n\n");

INC_PRUEBA 	= 120.0 / 100000.0;
valor = 0.0;

DESDE intervalo = 0 SII intervalo < TOTAL_INTERVALOS  MEDIANTE intervalo++
HACER
	  errorTaD = errorTa  = errorTIL = errorTDIL = 0.0;

	  DESDE pruebas = 0 SII pruebas < TOTAL_PRUEBAS MEDIANTE pruebas++
	  HACER calcula_errores();
	  FDESDE

	  errorTa   = errorTa   / TOTAL_PRUEBAS;
	  errorTIL  = errorTIL  / TOTAL_PRUEBAS;
	  errorTaD  = errorTaD  / TOTAL_PRUEBAS;
	  errorTDIL = errorTDIL / TOTAL_PRUEBAS;

	  sprintf (cadena, "Intervalo %d ; %e %e %e %e\n",
			   intervalo, errorTa, errorTIL, errorTaD, errorTDIL);
	  guarda  (cadena);
	  cout << cadena;
FDESDE


getch ();

contenido (123.23456789123);
contenido (121.834567890123);
contenido (-67.23);
contenido (-21.82345678901);

compara (125.54321, 125.5432);
compara (-15.54321, 15.5432);
compara (45.54321, 45.54321);
compara (13.54321, 87.5432);

incdec (-.23456);
incdec (.23456);
incdec (24.2345876);
incdec (64.267583456);
incdec (84.56723456);

getch();

suma (15.67890, 98.4321);
suma (-45.67890, 98.4321);
suma (15.67890, -98.4321);
resta (125.67890, 98.4321);
resta (-15.67890, 95.4321);
resta (125.67890, -98.4321);
resta (-123.67890, -85.4321);

suma (1.678999991, 65.4321);
suma (-125.67890, 15.6789);
suma (120.67890, 99.4321);
resta (124.67890, 96.4321);
resta (98.43210, 98.4321);
resta (125.67890, -98.4321);
resta (-5.67890, -5.4321);

niega (-23.7654321);
niega (87.7654321);
niega (78.7654321);
niega (-123.7654321);
niega (-.7621);
niega (.7654321);
*/

calcula_potencia ();

FIN_PROG_PPAL