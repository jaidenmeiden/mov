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

#ifndef ALEA_CF_YA_DECLARADA
#define ALEA_CF_YA_DECLARADA

#include <UGKFP2.h>

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
	CRandom	 					(const long);

	//SELECCIONA LA CORRIENTE DEL GENERADOR
	void select_seed		(const int);
	//INSTALA UNA NUEVA SEMILLA EN UNA CORRIENTE
	void install_seed   			(const FP0);

	//GENERADOR DE NUMEROS ALEATORIOS CONGRUENCIAL MULTIPLICATIVO ENTRE 0 y 1
	FP0 aleaAsm();
	//GENERADOR DE NUMEROS ALEATORIOS CONGRUENCIAL MULTIPLICATIVO ENTRE 0 y 1
	FP0 alea			        ();
	//GENERADOR DE VARIABLES ALEATORIAS ENTRE A y B
	FP2 uniforme		      	(FP2, FP2);
	//GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION EXPONENCIAL
	FP2 exponencial 		  	(FP2);
	//GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION ERLANG
	double erlang		     	(FP2,  FP2);
	//GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION HIPEREXPONENCIAL
	double hiperexp      		(FP2,  FP2);
	//GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION NORMAL
	FP2 normal					(FP2,  FP2);
};
#endif