/* CABECERA DE TRATAMIENTO DE NUMEROS EN FORMATO COMA FIJA 32 BITS
			DESARROLLADO POR RAMON P. MOLLA VAYA.
				VALENCIA. DICIEMBRE DE 1992 (c)

  Unidad de descripcion de la clase COMA FIJA 3.
  Representacion en coma fija de 32 bits. 24 for la parte IntegerPart y
  8 for la FractionalPart.
*/

#ifndef CF3_YA_DEFINIDA
#define CF3_YA_DEFINIDA

#include <UGKFP2.h>

#define INVONEFP3R 0.00390625
#define INVONEFP3f 0.00390625f

#define DOSPICF3    1608L	// 6.283185307 (2PI) in Fixed Point 3 format
#define	CERO5CF3	128L
#define DOSCF3		512L

class FP3
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

	// OPERADORES INICIALIZADORES
	FP3 						();
	FP3							(const double);
	//FP3 						(const UGKFPA64b);
	FP3							(const int v);
	FP3 						(const long, const long);

	// OPERADORES DE CONVERSION
	inline operator double		() { return Long * INVONEFP3R; };
	inline operator float		() { return Long * INVONEFP3f; };
	operator long				();
	operator int				();
	FP3 						(const FP0);
	FP3 						(const FP1);
	FP3 						(const FP2);

	// OPERADORES ARITMETICOS
	inline FP3 FP3::operator + (FP3 a)	{a.Long += Long;return a;}
	inline FP3 FP3::operator - (FP3 a)	{a.Long = Long - a.Long;return a;}
	inline FP3 FP3::operator - ()		{static FP3 c3;c3.Long = -Long;return c3;}

	FP3 operator * 				(FP3);
	FP3 operator *              (FP2);
	FP3 operator *              (FP1);
	FP3 operator *              (FP0);
	FP0 operator / 				(FP3);


	/**
	*	@func void fractional(FP3 &fract)
	*	@brief Calculates the fractional part of a FP3 number. No rounding is performed
	*	@param fract   [out] Return value of the fractional part of the number
	*/
	inline void fractional(FP3 &fract)
	{
		if (Long < 0)
			fract.Long = ALL_ONES;
		else
			fract.Long = 0;
		fract.LowByte = LowByte;
	}

	/**
	*	@func void integer(FP3 &intPart)
	*	@brief Calculates the integer part of a FP3 number. No rounding is performed
	*	@param integer [out] Return value of the integer part of the number
	*/
	inline void integer(FP3 &intPart)
	{
		intPart.Long = Long;
		intPart.LowByte = 0;
	}

	/**
	*	@func void modf(FP3 &integer, FP3 &fract)
	*	@brief Uses the same name as modf in math.h standard header
	*	@param integer [out] Return value of the integer part of the number
	*	@param fract   [out] Return value of the fractional part of the number
	*/
	inline void modf(FP3 &intPart, FP3 &fract)
	{
		integer		(intPart);
		fractional	(fract);
	}

	inline void FP3::operator ++	()		{ Long += ONEFP3; }
	inline void FP3::operator --	()		{ Long -= ONEFP3; }
	inline void FP3::operator +=	(FP3 a) { Long += a.Long; }
	inline void FP3::operator -=	(FP3 a) { Long -= a.Long; }

	// OPERADORES ALGEBRAICOS
	FP0 sin                    ();
	FP0 cosin                  ();
	FP0 sinasm					();
	FP0 cosinasm               ();
	FP0 sinil 					();
	FP0 cosinil				();

	FP1 ln                      ();
	FP1 lnil                    ();

	FP3 exp				();
	//FP3 exp						();

	FP3 sqrt					();
	FP3 sqrtil					();
	FP3 sqrt2					();
	FP3 sqrt2il					();

	// OPERADORES LOGICOS
	inline bool FP3::operator >		(const FP3 a) { return Long > a.Long; }
	inline bool FP3::operator <		(const FP3 a) { return Long < a.Long; }
	inline bool FP3::operator >=	(const FP3 a) { return Long >= a.Long; }
	inline bool FP3::operator <=	(const FP3 a) { return Long <= a.Long; }
	inline bool FP3::operator ==	(const FP3 a) { return Long == a.Long; }
	inline bool FP3::operator !=	(const FP3 a) { return Long != a.Long; }
};
#endif