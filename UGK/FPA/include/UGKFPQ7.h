/* CABECERA DE TRATAMIENTO DE NUMEROS EN FORMATO COMA FIJA 16 BITS
			DESARROLLADO POR RAMON P. MOLLA VAYA.
				VALENCIA. JUNIO DE 2000 (c)

  Unidad de descripcion de la clase COMA FIJA 2.
  Representacion en coma fija de 16 bits. 8 for la parte FractionalPart y
  8 for la IntegerPart. Utilizaci�n de tipo de datos "union" for acelerar acceso
  a parte IntegerPart o FractionalPart
*/

#ifndef FPQ7_YA_DEFINIDA
#define FPQ7_YA_DEFINIDA

#include <UGKFPQ15.h>

#define MENOSUNOFPQ7	255
#define SIGNONEGFPQ7	255
#define UNOFPQ7			256
#define CERO5FPQ7		128
#define BIT5Q7	 		128
#define MAX_FPQ7		127.0	//Valor m�ximo (positivo) que puede tomar un FractionalPart en coma fija
#define MIN_FPQ7	   -128.0	//Valor m�nimo (positivo) que puede tomar un FractionalPart en coma fija
#define MAX_FPiQ7		127		//Valor m�ximo (positivo) que puede tomar un FractionalPart en coma fija
#define MIN_FPiQ7      -128		//Valor m�nimo (positivo) que puede tomar un FractionalPart en coma fija
#define INVONEFP2RQ7	0.00390625

class FPQ7
{
public:
	union {
		short int	V;	//16 bits integer
		struct {
			unsigned char Dec;		//The 8 lsbs represent the FractionalPart part
			char Int;				//The 8 msbs represent the integer part	
		};
	} ;

	// OPERADORES DE INICIALIZACION
	inline FPQ7 () { }
	inline FPQ7 (const double v) 
	{
		if ( v >= MAX_FPQ7
		){	Int = MAX_FPiQ7;			//Rebosamiento positivo. Saturaci�n de 
					Dec = 0;
		} else {    if ( v <= MIN_FPQ7
				){	Int = MIN_FPiQ7;	//Rebosamiento negativo. Saturaci�n de 
							Dec = 0;
				} else { V = v * UNOFPQ7;
				};
		};
	}

	inline FPQ7 (const int v) {	Int = v; Dec = 0; }
	inline FPQ7 (const long v) {	V = v; }
	inline FPQ7 (const int ParteEntera, const int ParteDecimal)
	{
		Int = ParteEntera;
		Dec = ParteDecimal;
	}

	inline FPQ7 (const FPQ15 v) { V = v.Q7; }

	// OPERADORES DE CONVERSION
	inline operator long	()	{ return Int; }
	inline operator int		()	{ return Int; }
	inline operator double	()	{ return V * INVONEFP2RQ7; }

	// OPERADORES ARITMETICOS
	inline FPQ7 operator + (FPQ7 a) { return FPQ7 (a.V + V); }
	inline FPQ7 operator - (FPQ7 a) { return FPQ7(V - a.V); }
	inline FPQ7 FPQ7::operator - () { return FPQ7(-V); }

	FPQ7 operator *		(FPQ7);
	FPQ7 operator /		(FPQ7);

	inline void operator ++ ()		{ Int++; }
	inline void operator -- ()		{ Int--; }
	inline void operator += (FPQ7 a) { V += a.V; }
	inline void operator -= (FPQ7 a) { V -= a.V; }
	inline void operator *= (FPQ7 a) { *this = (a*(*this)); }
		
	inline FPQ7 operator >> (int n) { return FPQ7(V >> n); }
	inline FPQ7 operator << (int n) { return FPQ7(V << n); }

	// OPERADORES BOOLEANOS
	inline bool operator >   (const FPQ7 a) { return V > a.V; }
	inline bool operator <   (const FPQ7 a) { return V < a.V; }
	inline bool operator >=  (const FPQ7 a) { return V >= a.V; }
	inline bool operator <=  (const FPQ7 a) { return V <= a.V; }
	inline bool operator ==  (const FPQ7 a) { return V == a.V; }
	inline bool operator !=  (const FPQ7 a) { return V != a.V; }

	// OPERADORES DE REDONDEO y VARIOS
	FPQ7 Round						();
	void Redondea			();
	FPQ7 Abs						();	//Valor absoluto del n�mero

};

FPQ7 Multiplica (FPQ7 a, FPQ7 b);		//Versi�n acelerada de multiplicaci�n de dos n�meros en coma fija

#endif
