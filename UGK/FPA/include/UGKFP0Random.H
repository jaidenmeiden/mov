/* CABECERA DE TRATAMIENTO DE NUMEROS ALEATORIOS EN FORMATO COMA FIJA
				DESARROLLADO POR RAMON P. MOLLA VAYA.
					VALENCIA. ENERO DE 1993 (c)


	Unidad de descripcion de la clase CRandom.
	Representacion en coma fija de 32 bits. Utiliza notacion en C'2, por lo que
	un bit se destina a	bit de signo, y los otros 31 a la mantisa. */

/*************************************************************************/
/*                                                                       */
/*         Cabecera del generador de distribuciones eleatorias           */
/*                            Fichero "aleacf.cpp"                       */
/*                                                                       */
/*************************************************************************/

#ifndef ALEA_FP0_YA_DECLARADA
#define ALEA_FP0_YA_DECLARADA

#include <UGKFP1.h>

typedef enum
{
	 RANGOEXC,
	 CORRIENTE,
	 SEMILLA,
	 UNIFORME,
	 ERLANG,
	 HIPEREXP
} tipo_error;

class CRandom
{
	long seed;
	void error (const tipo_error); //Genera errores seg£n fallo.
public:

	// OPERADORES DE CREACION
	CRandom 					(const double);
	CRandom 					();
	CRandom	 				(const long);

	//SELECCIONA LA CORRIENTE DEL GENERADOR
	void select_seed		(const int);
	//INSTALA UNA NUEVA SEMILLA EN UNA CORRIENTE
	void install_seed   			(const FP0);

	//GENERADOR DE NUMEROS ALEATORIOS CONGRUENCIAL MULTIPLICATIVO ENTRE 0 y 1 PARA EMSAMBLADOR
	FP0 aleaAsm();
	//GENERADOR DE NUMEROS ALEATORIOS CONGRUENCIAL MULTIPLICATIVO ENTRE 0 y 1
	FP0 alea			        ();
	//GENERADOR DE NUMEROS ALEATORIOS CONGRUENCIAL MULTIPLICATIVO ENTRE 0 y 1
	FP0 alea2			        ();
	//GENERADOR DE VARIABLES ALEATORIAS ENTRE A y B
	FP0 uniforme		      	(FP0, FP0);
	//GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION EXPONENCIAL
	FP1 exponential 		  	(FP0);
	//GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION ERLANG
	FP1 erlang		    	  	(FP0,  FP0);
	//GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION HIPEREXPONENCIAL
	double hiperexp      			(FP0,  FP0);
	//GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION NORMAL
	FP1 normal    	    		(FP0,  FP0);
};
#endif