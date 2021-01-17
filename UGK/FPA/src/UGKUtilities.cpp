/**	Definition of two functions useful for fast calculus using fixed point arithmetic inside the UPV Game Kernel - UGK

*	Prefix: UGKUTL_

*	@author Ramon Molla
*	@modified 
*	@version 2014-11
*/
namespace UGK{

	int Zeros(long x)
	{
		__int16 aux;

		__asm mov eax, x
		__asm bsr ecx, eax
		__asm jz AllZeros
		__asm mov WORD PTR aux, cx

		return 31 - aux;

	AllZeros:
		return 32;

	}

}