/**	Fixed Point Arithmetic based on 32 bits integer numbers
*	Class Atirhmetic.

*	Prefix: UGKFPA_

*	@author Ramon Molla
*	@modified 
*	@version 2014-11
*/

#ifndef UGKFPA_ARITHMETIC
#define UGKFPA_ARITHMETIC
#include <stddef.h>
#include <UGK.h>

//Comment this definition always when generating the .lib or .dll library
//#define UGKFPA_ASSEMBLER

#ifdef UGKFPA_ASSEMBLER
#define exp() exp()
#define sin() sinasm()
#define cosin() cosinasm()
#endif

extern long *Roots;	   ///< Square roots array between [0,1] in FP0 format

namespace UGK
{
	class UGK_API CFPArithmetic
	{
	private:
		bool RootsInitialized;

	public:

		CFPArithmetic()
		{
			RootsInitialized	= false;
			Roots				= NULL;
		}

		~CFPArithmetic();

		void InitRoots ();
		// Dado un tipo de error cometido durante el trabajo con numeros en CFx,
		// indica el error cometido mediante el mensaje correspondiente.
		void Error				(int UGKFPA_ErrorType);
	};

	/*extern CFPArithmetic FPArithmetic;*/
}
#endif