/**	Fixed Point Arithmetic based on 32 bits integer numbers
*	Class FIXED POINT 0.
*	1 bit for the sign bit and 31 for the Fractional Part

*	Prefix: UGKFP0_

*	@author Ramon Molla
*	@modified 
*	@version 2014-11
*/

#ifndef UGKFP0_FP0
#define UGKFP0_FP0

#include <UGKFP.h>

//using namespace UGK;

class FP0
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

	// OPERADORES DE CREACION
	FP0::FP0 (const double v)
	{

		if ( fabs (v) > MAX_FP0R)
			Error (UGKFPA_RROFP0);
		Long = v * ONEFP0R;
	}

	FP0						() {Long = 0L;}
	FP0 					(const long, const long);

	// OPERADORES DE CONVERSION
	inline operator double	()	{return Long * INVONEFP0R;}
	operator int			();
	operator long			();
	inline operator float	() { return Long * INVONEFP0f; }

	// OPERADORES ARITMETICOS
	FP0 operator *			(FP0);
	FP0 operator /			(FP0);
	inline void operator =	(double d) { Long = d*ONEFP0R; }
	inline void operator =	(float  d) { Long = d*ONEFP0R; }

	inline FP0 operator		+	(FP0 a) {a.Long =  a.Long + Long; return a;}
	inline FP0 operator		-	(FP0 a) {a.Long = Long - a.Long; return a;}
	inline FP0 operator		-	()		{FP0 fp0; fp0.Long = -Long; return fp0;}
	
	inline void operator	*=	(FP0 a)	{Long *= a.Long;}
	inline void operator	/=	(FP0 a)	{Long /= a.Long;}
	inline void operator	+=	(FP0 a)	{Long += a.Long;}
	inline void operator	-=	(FP0 a)	{Long -= a.Long;}

	// OPERADORES REALES
	FP0 sqrt			();
	FP0 sqrtil			();
	FP0 sqrt2			();
	FP0 sqrt2il			();

	// OPERADORES LOGICOS
	bool operator >   (const FP0);
	bool operator <   (const FP0);
	bool operator >=  (const FP0);
	bool operator <=  (const FP0);
	bool operator ==  (const FP0);
	bool operator !=  (const FP0);
};

#endif