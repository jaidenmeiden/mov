#include <math.h>
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <cf_comun.h>
#include <utilidad.h>
#include <cf1.h>

#define TOTAL_INTERVALOS  100L
#define TOTAL_PRUEBAS 	 1000L

REAL	aux,
		INC_PRUEBA, //Incremento que se realiza en cada prueba.
		valor,  	//Valor del que hay que obtener los logaritmos.
		lnr,		//Logaritmo calculado en cada iteracion. Coma flotante.
		errorTa,   	//Error en acceso a tablas.
		errorTIL,  	//Error en acceso a tablas e interpolacion lineal.
		errorTaT,  	//Error en acceso a tablas con turbo.
		errorTTIL; 	//Error en acceso a tablas con turbo e interpolacion lineal.

CF1		valorcf1;	//variable "valor" en formato CF1.

ENTERO intervalo, pruebas;

#define TAMANO_CADENA 100
CARACTER cadena [TAMANO_CADENA], *cadena1;

FILE *fichero;

PROC calcula_errores ()
PPIO
lnr      = log (valor);
valorcf1 = valor;

errorTa   += absd (lnr - double(valorcf1.ln    ()));
errorTIL  += absd (lnr - double(valorcf1.lnil  ()));
errorTaT  += absd (lnr - double(valorcf1.ln2   ()));
errorTTIL += absd (lnr - double(valorcf1.ln2il ()));

valor    += INC_PRUEBA;
FIN

#define FICHERO "c:\\testln1.err"

PROC guarda (CARACTER *cadena)
PPIO
FILE *fichero;

SI (fichero = fopen (FICHERO, "a")) == NULL
ENTONCES cout << "Error, no se puede abrir el fichero especificado. " << endl;
		 exit(-1);
FSI
fwrite (cadena, strlen (cadena), 1, fichero);
fclose (fichero);
FIN

PROC resultado (CF1 x)
PPIO

cout << "log (" << double (x) << ") = " << log (x) << " : ";
cout << double(x.ln    ()) << " : ";
cout << double(x.lnil  ()) << " : ";
cout << double(x.ln2   ()) << " : ";
cout << double(x.ln2il ()) << endl;


FIN

PROG_PPAL

inicializa_logaritmos();

SI (fichero = fopen (FICHERO, "a")) == NULL
ENTONCES cout << "Error, no se puede abrir el fichero especificado. " << endl;
		 exit(-1);
FSI
cadena1 = "Formato de los resultados obtenidos. \n";
fwrite (cadena1, strlen (cadena1), 1, fichero);
fclose (fichero);

guarda ("Valor y logaritmo asociado. \n");
guarda ("Error en Tablas / Tablas con I.L. / Tablas Turbo / Tablas Turbo con I.L.\n\n");

cout << "Comenzamos." << endl;

resultado (0.000095);
resultado (10.85);
resultado (56.78);
resultado (0.0012345678);
resultado (67.012345678);
resultado (90.0012345678);
resultado (90.00002345678);
resultado (0.000012345678);
resultado (.0000012345678);
resultado (.12345);

getch();

INC_PRUEBA = 100.0 / (TOTAL_INTERVALOS * TOTAL_PRUEBAS);

valor = INC_PRUEBA;
DESDE intervalo = 0 SII intervalo < TOTAL_INTERVALOS  MEDIANTE intervalo++
HACER
	  errorTa  = errorTIL = errorTaT  = errorTTIL = 0.0;

	  sprintf (cadena, "Log (%f) = %f \n", valor, lnr);
	  guarda  (cadena);

	  DESDE pruebas = 0 SII pruebas < TOTAL_PRUEBAS MEDIANTE pruebas++
	  HACER calcula_errores();
	  FDESDE

	  errorTa   = errorTa   / TOTAL_PRUEBAS;
	  errorTIL  = errorTIL  / TOTAL_PRUEBAS;
	  errorTaT  = errorTaT  / TOTAL_PRUEBAS;
	  errorTTIL = errorTTIL / TOTAL_PRUEBAS;

	  sprintf (cadena, "Intervalo %d ; %e %e %e %e\n", intervalo, errorTa, errorTIL, errorTaT, errorTTIL);
	  guarda  (cadena);
	  cout << cadena;
FDESDE

FIN_PROG_PPAL