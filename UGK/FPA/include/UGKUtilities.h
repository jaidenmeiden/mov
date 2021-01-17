/**	Definition of two functions useful for fast calculus using fixed point arithmetic inside the UPV Game Kernel - UGK

*	Prefix: UGKUTL_

*	@author Ramon Molla
*	@modified 
*	@version 2014-11
*/

#ifndef UGKUTL_UTILIES
#define UGKUTL_UTILIES

namespace UGK
{
	/**
	*	\fn double absd (const double r)

	*	Generates the absolute value of a floating point number
	*	\param[in] r Number to convert into positive if it is not
	*	\return The positive value of r
	*/
	inline double absd (const double r) {if(r >= 0.0) return r; else return -r;}

	/**
	*	\fn void IntSwap (int &a, int &b)
	*	Swap 2 integer numbers
	*	\param[in,out] a,b Numbers to swap their contents
	*/
	inline void IntSwap (int &a, int &b)
	{
		register int aux;

		aux = a;
		a 	= b;
		b 	= aux;
	}

	/*	Funcion que entrega la cantidad de Zeros que aparecen a
		la izquierda de una palabra de 32 bits. */
	int Zeros (long);
}
#endif