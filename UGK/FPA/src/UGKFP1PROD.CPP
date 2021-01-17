/*  Programa de prueba de la unidad de numeros en Fixed Point con 32 bits for
	representar la parte FractionalPart y 0 for la IntegerPart. */

#include <math.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <UGKFP1.h>
#include <UGKutilities.h>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

FP1 x;
FP0 y;

int i, j;

using namespace std;

void mainFP1() {
FP0 a (-0.345);
FP1 b (a),
	f (-123.45678),
	d (1.000345),
	e ;

#define FICHERO "prodcf1.err"
#define ANCHO 100

FILE *fichero;
double xr, yr, zr;
char cadena [100];

if ( (fichero = fopen (FICHERO,"w")) == NULL) { cout << "Error. No se puede abrir el fichero " << FICHERO << endl;};

fclose (fichero);

xr = -11.0;
for ( i = 0 ; i < ANCHO ; i++)
{
	  xr += 23.0 / ANCHO;
	  fichero = fopen (FICHERO,"a");

	  yr = -11.0;
	  for ( j = 0 ; j < ANCHO ; j++
	  ){ yr += 23.0 / ANCHO;
			zr = zr + UGK::absd (xr*yr - double (FP1 (xr) * FP1 (yr)));
	  }
	  zr /= ANCHO;
	  sprintf (cadena, " X = %f Error = %e \n", xr, zr);
	  fwrite  (cadena, strlen (cadena), 1, fichero);
	  fclose (fichero);
}

}
