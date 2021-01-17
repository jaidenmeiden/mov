/**	Fixed Point Arithmetic based on 32 bits integer numbers
*	Class Atirhmetic.

*	Prefix: UGKFPA_

*	@author Ramon Molla
*	@modified 
*	@version 2014-11
*/

#include <UGKFPArithmetic.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <UGKFP0.h>
#include <UGKutilities.h>
#include <atlstr.h>
#include <stddef.h>

#define MAX_ROOT        8192
#define MAX_POT           19

using namespace std;
using namespace UGK;

long *Roots;	   ///< Square roots array between [0,1] in FP0 format

extern FP0 R2[MAX_POT];  // (sqrt (2))^-x, donde x pertenece a [1, 31]

void CFPArithmetic::InitRoots()
{

int  i;
double  auxr,
		inc_raiz; //Difference between two consecutive positions within the table of logarithms

	//Calcules the table of 0.5 roots powers

	if (RootsInitialized) return;
	else
	{
		RootsInitialized = true;
		auxr 	      = 1.0;
		R2[0].Long  = ONEFP0;
		for ( i = 1  ; i <= MAX_POT ; i++)
		{ auxr   = auxr * sqrt (0.5);
			R2 [i] = auxr;
		}

		//Book for memory for the conversion tables
		if (NULL==(Roots = (long *) malloc ((MAX_ROOT + 1) * sizeof (long))))
			exit (-1);
	
		//Se calculan los incrementos.
		inc_raiz = 1.0 / MAX_ROOT;
		auxr     = 0.0;

		//Se calcula la tabla de raices entre 0 y 1.
		for ( i = 0  ; i <= MAX_ROOT ; i++)
		{
			Roots [i] = ONEFP0R * sqrt (auxr);
			auxr    += inc_raiz;
		}
	};
}