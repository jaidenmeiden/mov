/**	Header for fixed point numbers using FP1 format
	Using 32 bits. 24 for the Fractional Part and 8 for the Integer Part

*	Prefix: FP1_

*	@author Ramon Molla
*	@modified 
*	@version 2014-11
*/

#ifndef FP1_JUST_DEFINED
#define FP1_JUST_DEFINED

#include <UGKFP0.h>

#define INVONEFP1R 5.960464478e-8
#define INVONEFP1f 5.960464478e-8f
#define FP1_ZERO5 	   BIT23 //Bit number 23rd set to one

#define FP1_PIMED   26353589L         /* 1.570796327 (PI/2)  en Fixed Point 1 */
#define FP1_PI      52707178L         /* 3.141592654 (PI)    en Fixed Point 1 */
#define FP1_3PIMED  79060768L         /* 4.71238848  (3PI/2) en Fixed Point 1 */
#define FP1_TWOPI  105414357L         /* 6.283185307 (2PI)   en Fixed Point 1 */

//When truncating the fractional and integer part of a number, if the number is negative, the integer part has to be set to ones
#define NEG_SIGN_BIT_INT_PART_FP1 255

class FP1;
extern FP1 R128;

void InitializeSines ();
void initializeLogarithms();
void initializeExponential();
long sasm (long);	// Funcion sin en series de Taylor.
long easm (long);	// Funcion exponencial en series de Taylor.

class FP1
{
public:
	union
	{
		struct
		{
			unsigned char		LowByte;
			unsigned short int	MiddelInt;
			char				HighByte;
		};
		unsigned char		Shorts	[UGKFP_BYTES];
		unsigned short int	Ints	[UGKFP_SHORT_INTS];
		long	 int		Long;
	};

	// OPERADORES DE INICIALIZACION
	FP1 						();
	FP1							(int e);
	FP1 						(const double);
	//FP1 						(const UGKFPA64b);
	FP1 						(const long, const long);
	FP1 						(const FP0);

	// OPERADORES DE CONVERSION
	operator long				();
	
	//ARITHMETIC OPERATORS
	inline operator int			()		{int aux = Ints[0]; return HighByte; }
	inline operator double		()		{return Long * INVONEFP1R;}
	inline operator float		()		{return Long * INVONEFP1f; }
	inline FP1 operator +		(FP1 a) {a.Long += Long; return a;}
	inline FP1 operator -		(FP1 a) {a.Long = Long - a.Long; return a;}
	inline FP1 operator -		()		{static FP1 fp1; fp1.Long = - Long; return fp1;}

	FP1 operator *				(FP0);
	FP1 operator * 				(FP1);
	FP0 operator / 				(FP1);

	inline FP1 operator ++		()	{Long += ONEFP1;}
	inline FP1 operator --		()	{Long -= ONEFP1;}

	inline void FP1::operator -=	(const FP1 a)	{Long -= a.Long;}
	inline void FP1::operator +=	(const FP1 a)	{Long += a.Long;}
	inline void FP1::operator *=	(const FP1 a)	{Long *= a.Long;}
	inline void FP1::operator /=	(const FP1 a)	{Long *= a.Long; Long = Long >> 8;}
	
	/**
	*	@func void fractional(FP1 &fract)
	*	@brief Calculates the fractional part of a FP1 number. No rounding is performed
	*	@param fract   [out] Return value of the fractional part of the number
	*/
	inline void fractional(FP1 &fract)
	{
		fract.Long = Long;
		if (Long < 0)
			fract.HighByte = NEG_SIGN_BIT_INT_PART_FP1;
		else
			fract.HighByte = 0;
	}

	/**
	*	@func void integer(FP1 &intPart)
	*	@brief Calculates the integer part of a FP1 number. No rounding is performed
	*	@param integer [out] Return value of the integer part of the number
	*/
	inline void integer(FP1 &intPart)
	{
		intPart.Long = 0;
		intPart.HighByte = HighByte;
	}

	/**
	*	@func void modf(FP1 &integer, FP1 &fract)
	*	@brief Uses the same name as modf in math.h standard header
	*	@param integer [out] Return value of the integer part of the number
	*	@param fract   [out] Return value of the fractional part of the number
	*/
	inline void modf(FP1 &intPart, FP1 &fract)
	{
		integer		(intPart);
		fractional	(fract);
	}

	// LOGIC OPERATORS
	inline bool FP1::operator >		(const FP1 a)	{return Long > a.Long;}
	inline bool FP1::operator <		(const FP1 a)	{return Long < a.Long;}
	inline bool FP1::operator >=	(const FP1 a)	{return Long >= a.Long;}
	inline bool FP1::operator <=	(const FP1 a)	{return Long <= a.Long;}
	inline bool FP1::operator ==	(const FP1 a)	{return Long == a.Long;}
	inline bool FP1::operator !=	(const FP1 a)	{return Long != a.Long;}

	//MATH FUNCTIONS
	FP0 sin				();
	FP0 sinil 			();
	FP0 cosin			();
	FP0 cosinil			();

	FP1 ln				();
	FP1 lnil			();
	FP1 ln2             ();
	FP1 ln2il           ();

	FP1 exp				();
	FP1 expil			();

	inline FP1 sqrt		() {FP0 c; c.Long = Long; return R128 * c.sqrt();}
	inline FP1 sqrtil	() {FP0 c; c.Long = Long; return R128 * c.sqrtil();}
	inline FP1 sqrt2	() {FP0 c; c.Long = Long; return R128 * c.sqrt2();}
	inline FP1 sqrt2il	() {FP0 c; c.Long = Long; return R128 * c.sqrt2il();}
};

#endif