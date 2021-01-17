/* CABECERA DE TRATAMIENTO DE NUMEROS EN FORMATO COMA FIJA 32 BITS
			DESARROLLADO POR RAMON P. MOLLA VAYA.
				VALENCIA. MAYO DE 2000 (c)

  Unidad de descripcion de la clase COMA FIJA 2.
  Representacion en coma fija de 32 bits. 16 for la parte FractionalPart y
  16 for la IntegerPart. Utilización de tipo de datos "union" for acelerar acceso
  a parte IntegerPart o FractionalPart
  Utiliza tecnología MMX encapsulada dentro de una clase
*/

#ifndef FP_YA_DEFINIDA
#define FP_YA_DEFINIDA

#include <UGKFP.h>

//Constantes Multimedia
#define TOTAL_DATA 2	//Number of simultaneous data that may be treated in parallel. 
						//Typically 2 numbers of 32 bits in MMX technology

class FPQ15mmx
{
public:
	union {
		FPQ15	Vfp[TOTAL_DATA];	
		__int64 V;
	} ;

	// OPERADORES DE INICIALIZACION
	inline FPQ15mmx () { }
	FPQ15mmx (const double v[TOTAL_DATA]) 
	{
	int i;

		for (  i=0 ; i<TOTAL_DATA ; i++ )
		{
			if ( v[i] >= MAX_FP
			){	Vfp[i].V216.Int = MAX_FPi;			//Rebosamiento positivo. Saturación de 
						Vfp[i].V216.Dec = MENOSUNOFP;
			} else {    if ( v[i] <= MIN_FP
					){	Vfp[i].V216.Int = MIN_FPi;	//Rebosamiento negativo. Saturación de 
								Vfp[i].V216.Dec = 0;
					} else { Vfp[i].V32 = v[i] * UNOFP;
					};
			};
		}
	}

	inline FPQ15 (const int v[TOTAL_DATA]) 
	{	
	int i;

		for (  i=0 ; i<TOTAL_DATA ; i++ )
		{
			Vfp[i].V216.Int = v[i];
			Vfp[i].V216.Dec = 0;
		} 
	}

	inline FPQ15 (const long v[TOTAL_DATA]) 
	{	
	int i;

		for (  i=0 ; i<TOTAL_DATA ; i++ )
		{
			Vfp[i].V32 = v[i];
		} 
	}

	inline FPQ15 (const int ParteEntera[TOTAL_DATA], const int ParteDecimal[TOTAL_DATA])
	{
	int i;

		for (  i=0 ; i<TOTAL_DATA ; i++ )
		{
			Vfp[i].V216.Int = ParteEntera[i];
			Vfp[i].V216.Dec = ParteDecimal[i];
		} 
	}
	
	// OPERADORES DE CONVERSION
	inline operator long (int i)		{ return Vfp[i].V216.Int; }
	inline operator int (int i)		{ return Vfp[i].V216.Int; }
	inline operator double (int i)	{ return Vfp[i].V32 * INVONEFP2R; }

	// OPERADORES ARITMETICOS
	inline FPQ15 operator + (FPQ15mmx a) 
	{ 
	FPQ15mmx aux;


Vfp[i].
		return FPQ15mmx (a.V32 + V32); 
	}

	inline FPQ15 operator - (FPQ15mmx a) { return FPQ15(V32 - a.V32); }
	inline FPQ15 FPQ15::operator - () { return FPQ15(-V32); }

	FPQ15 operator *					(FPQ15);
	FPQ15 operator /					(FPQ15);

	inline void operator ++ ()		{ V216.Int++; }
	inline void operator -- ()		{ V216.Int--; }
	inline void operator += (FPQ15 a) { V32 += a.V32; }
	inline void operator -= (FPQ15 a) { V32 -= a.V32; }
	
	inline FPQ15 operator >> (int n) { return FPQ15(V32 >> n); }
	inline FPQ15 operator << (int n) { return FPQ15(V32 << n); }

	// OPERADORES BOOLEANOS
	inline bool operator >   (const FPQ15 a) { return V32 > a.V32; }
	inline bool operator <   (const FPQ15 a) { return V32 < a.V32; }
	inline bool operator >=  (const FPQ15 a) { return V32 >= a.V32; }
	inline bool operator <=  (const FPQ15 a) { return V32 <= a.V32; }
	inline bool operator ==  (const FPQ15 a) { return V32 == a.V32; }
	inline bool operator !=  (const FPQ15 a) { return V32 != a.V32; }

	// OPERADORES DE REDONDEO
	FPQ15 Round						();
	void Redondea			();

};

FPQ15 Multiplica (FPQ15 a, FPQ15 b);		//Versión acelerada de multiplicación de dos números en coma fija

#endif
