#include <math.h>
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <cf_comun.h>
#include <utilidad.h>
#include <cf1.h>

#define TOPE 100
#define TOTAL_INTERVALOS  100
#define TOTAL_PRUEBAS 	 8192

#define INC_PRUEBA 0.000001220703125	//Incremento que se realiza en cada prueba. 1 / 819200

REAL	aux,
		valor,  	//Valor del que hay que obtener las raices cuadradas.
		rcr,		//Raiz cuadrada calculada en cada iteracion. Coma flotante.
		errorTa,   	//Error en acceso a tablas.
		errorTIL,  	//Error en acceso a tablas e interpolacion lineal.
		errorTaturbo,   	//Error en acceso a tablas acelerado.
		errorTILturbo,  	//Error acc. tablas acelerado e interpol. lineal.
		Error,
		x, y;

CF0		valorcf0;	//variable "valor" en formato CF0.

ENTERO intervalo, pruebas, i, j;

#define TAMANO_CADENA 100
CARACTER cadena [TAMANO_CADENA], *cadena1;

FILE *fichero;

PROC calcula_errores ()
PPIO
rcr      = sqrt (valor);
valorcf0 = valor;

errorTa  += absd (rcr - double(valorcf0.sqrt   	  	()));
errorTIL += absd (rcr - double(valorcf0.sqrtil 		()));
errorTaturbo  += absd (rcr - double(valorcf0.sqrt2  ()));
errorTILturbo += absd (rcr - double(valorcf0.sqrt2il()));

valor    += INC_PRUEBA;
FIN

#define FICHERO "testsqrt.err"

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

PROC resultado (CF0 x)
PPIO

cout << "Raiz cuad (" << double (x) << ") = " << sqrt (double (x)) << " : "
	 << double(x.sqrt ()) << " : " << double(x.sqrtil ())<< endl;

FIN

PROG_PPAL

inicializa_raices();

SI (fichero = fopen (FICHERO, "w")) == NULL
ENTONCES cout << "Error, no se puede abrir el fichero especificado. " << endl;
		 exit(-1);
FSI

cadena1 = "Formato de los resultados obtenidos. \n";
fwrite (cadena1, strlen (cadena1), 1, fichero);
fclose (fichero);

guarda ("Valor y raiz cuadrada asociada. \n");
guarda ("Error en Tablas / Tablas con I.L. / Tablas turbo / Tablas + I.L. turbo \n\n");

resultado (10.95);
resultado (120.85);
resultado (56.78);
resultado (0.0012345678);
resultado (67.012345678);
resultado (90.0012345678);
resultado (90.00002345678);
resultado (0.000012345678);
resultado (.0000012345678);
resultado (.12345);

valor = INC_PRUEBA;
DESDE intervalo = 0 SII intervalo < TOTAL_INTERVALOS  MEDIANTE intervalo++
HACER
	  errorTa  = errorTIL = 0.0;

	  sprintf (cadena, "Raiz (%f) = %f \n", valor, rcr);
	  guarda  (cadena);

	  DESDE pruebas = 0 SII pruebas < TOTAL_PRUEBAS MEDIANTE pruebas++
	  HACER calcula_errores();
	  FDESDE

	  errorTa  = errorTa  / TOTAL_PRUEBAS;
	  errorTIL = errorTIL / TOTAL_PRUEBAS;
	  errorTaturbo  = errorTaturbo  / TOTAL_PRUEBAS;
	  errorTILturbo = errorTILturbo / TOTAL_PRUEBAS;

	  sprintf (cadena, "Intervalo %d ; %e %e %e %e \n",
			   intervalo, errorTa, errorTIL, errorTaturbo, errorTILturbo);
	  guarda  (cadena);
	  cout << cadena;
FDESDE
/*
x = 0.0;
DESDE i = 1 SII i <= TOPE MEDIANTE i++
HACER y = Error = 0.0;
	  DESDE j = 1 SII j <= TOPE MEDIANTE j++
	  HACER Error += absd (x*y - double (CF0(x)*CF0(y)));
			y	  += 0.01;
	  FDESDE
	  sprintf (cadena, "Error %.2f  = %e \n", x, Error / TOPE);
	  fwrite (cadena, strlen (cadena), 1, fichero);
	  x += 0.01;
FDESDE
fclose (fichero);
  */
FIN_PROG_PPAL