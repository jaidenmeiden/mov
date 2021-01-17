#include <math.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <UGKutilities.h>
#include <UGKFP1.h>

#define TOTAL_INTERVALOS  100
#define TOTAL_PRUEBAS 	 8192

using namespace std;

#ifdef	UGKOS_WINDOWS
	//#define _CRT_SECURE_NO_WARNINGS
//	#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif

#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1

double	aux,
		Long,  	//Valor del que hay que obtener las exponenciales.
		e,			//exponential calculado en cada iteracion. Coma flotante.
		errorTa,   	//Error en acceso a tablas.
		errorTIL,  	//Error en acceso a tablas e interpolacion lineal.
		INC_PRUEBA;	//Constante que incrementa el Long mediante el que se calcula la funcion

FP1		valorcf1;	//variable "Long" en formato FP1.

int intervalo, pruebas;

#define TAMANO_CADENA 100
char cadena [TAMANO_CADENA], *cadena1;

FILE *fichero;

void calcula_errores ()
{
e	     = exp (Long);
valorcf1 = Long;

errorTa  += UGK::absd (e - double (valorcf1.exp    ()));
errorTIL += UGK::absd (e - double (valorcf1.expil  ()));

Long    += INC_PRUEBA;
}

#define FICHERO "tstexpf1.err"

void guarda (char *cadena)
{
	FILE *fichero;

	if ( (fichero = fopen (FICHERO, "a")) == NULL)
	{
		cout << "Error, no se puede abrir el fichero especificado. " << endl;
		exit(-1);
	};

	fwrite (cadena, strlen (cadena), 1, fichero);
	fclose (fichero);
}

void resultexp (FP1 v)
{

cout << "exp (" << double (v) << ") = " << exp (double(v)) << " : "
	 << double (v.exp   ()) << " : "
	 << double (v.expil ()) << endl;
}

void main() {

initializeExponential();

if ( (fichero = fopen (FICHERO, "a")) == NULL
){ cout << "Error, no se puede abrir el fichero especificado. " << endl;
		 exit(-1);
};
cadena1 = "Formato de los resultados obtenidos. \n";
fwrite (cadena1, strlen (cadena1), 1, fichero);
fclose (fichero);

guarda ("Valor y exponential asociado. \n");
guarda ("Error en Taylor, Tablas / Tablas con I.L.\n\n");
/*
resultexp (-10.995);
resultexp (3.85);
resultexp (0.78);
resultexp (-8.12345678);
resultexp (4.012345678);
resultexp (-0.0012345678);
resultexp (.00002345678);
*/

Long 		= -15.0;
INC_PRUEBA 	= 20.0 / 819200.0;

for ( intervalo = 0 ; intervalo < TOTAL_INTERVALOS  ; intervalo++
){
	  errorTa  = errorTIL = 0.0;

	  sprintf (cadena, "Exp (%f) = %f \n", Long, e);
	  guarda  (cadena);

	  for ( pruebas = 0 ; pruebas < TOTAL_PRUEBAS ; pruebas++
	  ){ calcula_errores();
	  }

	  errorTa  = errorTa  / TOTAL_PRUEBAS;
	  errorTIL = errorTIL / TOTAL_PRUEBAS;

	  sprintf (cadena, "Intervalo %d ; %e %e \n", intervalo, errorTa, errorTIL);
	  guarda  (cadena);
	  cout << cadena;
}

}
