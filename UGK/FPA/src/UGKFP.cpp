/**	Fixed Point Arithmetic based on 32 bits integer numbers
*	Class Basic definitions.

*	Prefix: UGKFP_

*	@author Ramon Molla
*	@modified
*	@version 2014-11
*/


#include <UGKFP.h>


CString ERROR_MSG[UGKFPA_MAX_ERR] =
{
	"Fixed Point ERROR: ",
	"Representation Range Overpassed when using FP0 format.",
	"Representation Range Overpassed when using FP1 format.",
	"Representation Range Overpassed when using FP2 format.",
	"Representation Range Overpassed when using FP3 format.",
	"Representation Range Overpassed when using FP4 format.",
	"Cannot find the square root value of ",
	"Not defined error."
};