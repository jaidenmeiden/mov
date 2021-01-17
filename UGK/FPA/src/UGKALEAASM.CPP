/* UNIDAD DE TRATAMIENTO DE NUMEROS ALEATORIOS EN FORMATO COMA FIJA 32 BITS
				DESARROLLADO POR RAMON P. MOLLA VAYA.
					VALENCIA. DICIEMBRE DE 1992 (c)


	Unidad de descripcion de la parte de bajo nivel de la clase CRandom.
	Representacion en coma fija de 32 bits. 32 for la parte FractionalPart y
	0 for la IntegerPart, es decir FP0. Utiliza notacion en C'2, por lo que
	un bit se destina a	bit de signo, y los otros 31 a la mantisa. */

/*************************************************************************/
/*                                                                       */
/*                Generador de distribuciones eleatorias                 */
/*                         Fichero "aleaasm.cpp"                         */
/*                                                                       */
/*************************************************************************/

#include <UGKFPRandom.h>

//ACHTUNG: Modificar para que soporte 32/64 bits y devuelva long/long long para evitar uso de constructores FPx

#pragma inline  // Indicate to the compiler that there is assembler code among the C++ code 

#define A 		   	   16807      // multiplier (7**5) for 'alea'
#define M 		  2147483647      // module (2**31-1) for 'alea'

#define MAX_DECK 		 256	  //Amount of values to riffle

/****************************************************************************/
/*                                                                          */
/*                generador de números aleatorios MINIMAL STANDARD.         */
/*                          Xn+1 = 7**5 * Xn mod (2**31 - 1)                */
/*                                                                          */
/* Esta implementaci¢n es para el Intel 80386 usando compilador de C que    */
/* permita introducci¢n de c¢digo máquina en linea.                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/

long shuffling [MAX_DECK];

FP0 CRandom::aleaAsm ()
{
long aux;
static FP0 cf0;


aux = seed;
_asm {
	mov eax, aux
	mov edx, A
	mul edx
	mov ecx, M
	div ecx
	mov aux, edx
	}

/* Hasta aqu¡ el generador minimal standard. A continuaci¢n someteremos el
   nuevo Long obtenido a un shuffling y mezcla con ^. *
seed                         = aux;
p								= (char *)&aux;
aux                             = shuffling [*p];
shuffling [*p]				    = seed;*/
seed = cf0.Long             = aux;// ^ seed;

return cf0;
}
