/* CABECERA DE TRATAMIENTO DE NUMEROS EN FORMATO COMA FIJA 32 BITS
			DESARROLLADO POR RAMON P. MOLLA VAYA.
				VALENCIA. DICIEMBRE DE 1992 (c)

  Unidad de descripcion de la clase COMA FIJA 2.
  Representacion en coma fija de 32 bits. 16 for la parte FractionalPart y
  16 for la IntegerPart.
*/

#ifndef CF2_YA_DEFINIDA
#define CF2_YA_DEFINIDA
#include <UGKFP1.h>

#define INVONEFP2R 1.525878906E-5
#define INVONEFP2f 1.525878906E-5f

//When truncating the fractional and integer part of a number, if the number is negative, the integer part has to be set to ones
#define NEG_SIGN_BIT_INT_PART_FP2 65535

class FP2
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
	FP2 ()								{Long = 0;}
	FP2 (const double v)				{if ( fabs (v) > MAX_FP2R)	 Error (UGKFPA_RROFP2); else Long = v * ONEFP2R;}
	FP2 (const int v)					{Long = v * ONEFP2;}
	FP2 (const long v1, const long v2)	{Long = (v1 << 2*FPDISPLACE) + (v2 >> 2*FPDISPLACE);}

	//FP2                              (const UGKFPA64b);

	// OPERADORES DE CONVERSION
	inline operator int		() {return (Long + ZERO5FP2) >> POS_PTO_DEC;}
	inline operator double	() {return Long * INVONEFP2R;}
	inline operator float	() {return Long * INVONEFP2f; }

	operator long                    ();
	FP2                              (const FP0);
	FP2                              (const FP1);

	// OPERADORES ARITMETICOS
	FP2 operator *                  (FP2);
	FP2 operator *                  (FP1);
	FP2 operator *                  (FP0);
	FP0 operator /                  (FP2);

	/**
	*	@func void fractional(FP2 &fract)
	*	@brief Calculates the fractional part of a FP2 number. No rounding is performed
	*	@param fract   [out] Return value of the fractional part of the number
	*/
	inline void fractional(FP2 &fract)
	{
		fract.Ints[UGKFP_LO] = Ints[UGKFP_LO];
		if (Long < 0)
			fract.Ints[UGKFP_HI] = NEG_SIGN_BIT_INT_PART_FP2;
		else
			fract.Ints[UGKFP_HI] = 0;
	}

	/**
	*	@func void integer(FP2 &intPart)
	*	@brief Calculates the integer part of a FP2 number. No rounding is performed
	*	@param integer [out] Return value of the integer part of the number
	*/
	inline void integer(FP2 &intPart)
	{
		intPart.Ints[UGKFP_LO] = 0;
		intPart.Ints[UGKFP_HI] = Ints[UGKFP_HI];
	}

	/**
	*	@func void modf(FP2 &integer, FP2 &fract)
	*	@brief Uses the same name as modf in math.h standard header
	*	@param integer [out] Return value of the integer part of the number
	*	@param fract   [out] Return value of the fractional part of the number
	*/
	inline void modf(FP2 &intPart, FP2 &fract)
	{
		integer		(intPart);
		fractional	(fract);
	}

	inline FP2 operator		+	(FP2 a) {a.Long += Long; return a;}
	inline FP2 operator		-	(FP2 a) {a.Long = Long - a.Long; return a;}
	inline FP2 operator		-	()		{static FP2 cf2; cf2.Long = -Long; return cf2;}

	inline FP2 operator		++	()		{ Long += ONEFP2; }
	inline FP2 operator		--	()		{ Long -= ONEFP2; }
	inline void operator	+=	(FP2 a) { Long += a.Long; }
	inline void operator	-=	(FP2 a) { Long -= a.Long; }

	//Logic operators
	inline bool operator	>   (const FP2 a) { return Long > a.Long; }
	inline bool operator	<   (const FP2 a) { return Long < a.Long; }
	inline bool operator	>=  (const FP2 a) { return Long >= a.Long; }
	inline bool operator	<=  (const FP2 a) { return Long <= a.Long; }
	inline bool operator	==  (const FP2 a) { return Long == a.Long; }
	inline bool operator	!=  (const FP2 a) { return Long != a.Long; }
	
	//Truncation operators
	inline int				trunc ()		  { return Long >> POS_PTO_DEC; }
	inline FP2 operator		>>	(int n)		  {static FP2 aux; aux.Long = Long >> n; return aux;}

	// OPERADORES ALGEBRAICOS
	FP0 sin                        ();
	FP0 cosin                      ();
	FP0 sinasm						();
	FP0 cosinasm               	();
	FP0 sinil 						();
	FP0 cosinil					();

	FP1 ln                      	();
	FP1 lnil                    	();

	FP2 exp						();
	//FP2 exp							();
	FP2 expil						();

	FP2 sqrt						();
	FP2 sqrtil						();
	FP2 sqrt2						();
	FP2 sqrt2il						();
};
#endif
