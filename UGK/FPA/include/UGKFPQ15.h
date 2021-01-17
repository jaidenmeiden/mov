/* CABECERA DE TRATAMIENTO DE NUMEROS EN FORMATO COMA FIJA 32 BITS
			DESARROLLADO POR RAMON P. MOLLA VAYA.
				VALENCIA. AGOSTO DE 1999 (c)

  Unidad de descripcion de la clase COMA FIJA 2.
  Representacion en coma fija de 32 bits. 16 for la parte FractionalPart y
  16 for la IntegerPart. Utilización de tipo de datos "union" for acelerar acceso
  a parte IntegerPart o FractionalPart
*/

#ifndef FPQ15_YA_DEFINIDA
#define FPQ15_YA_DEFINIDA

#include <UGKFPQ31.h>

#define MENOSUNOFPQ15	65535
#define SIGNONEGFPQ15	65535
#define UNOFPQ15		65536L
#define DOSFPQ15		131072L
#define CERO5FPQ15		32768L
#define CERO25FPQ15		16384L
#define BIT15Q15 		32768	//En formato de 16 bits
#define MAX_FPrQ15		32767.0	//Valor máximo (positivo) que puede tomar un FractionalPart en coma fija
#define MIN_FPrQ15	   -32768.0	//Valor mínimo (positivo) que puede tomar un FractionalPart en coma fija
#define MAX_FPiQ15		32767	//Valor máximo (positivo) que puede tomar un FractionalPart en coma fija
#define MIN_FPiQ15     -32768	//Valor mínimo (positivo) que puede tomar un FractionalPart en coma fija
#define INVONEFP2R		1.52587890625E-5

#define MAX_FPQ15		2147483647L	//Valor máximo (positivo) que puede tomar un FractionalPart en coma fija entendido como 32 bits
#define MIN_FPQ15	   -2147483648L	//Valor mínimo (negativo) que puede tomar un FractionalPart en coma fija

//class FPQ31;

class FPQ15
{
public:
	union {
		long	V;	//32 bits integer
		struct {
			unsigned short int Dec;		//The 16 lsbs represent the FractionalPart part
			short int Int;				//The 16 msbs represent the integer part	
		};
	//...cuatro enteros de 16 bits
		struct {
			unsigned char DecLo, DecHi;	//Parte FractionalPart
			unsigned char IntLo, IntHi;	//Parte IntegerPart
		};

			//...un número de 32 bits centrado en el centro de la mantisa.
			//De esta forma, se desprecian los 16 Msb y los 16 lsb
		struct {
			char	DecLow;	//Parte IntegerPart alta (16 bits) de 32 bits
			short int Q7;		//La parte central es la que corresponde a un Q15
			char	IntHigh;	//Parte IntegerPart alta (16 bits) de 32 bits
		};
	} ;

	// OPERADORES DE INICIALIZACION
	inline FPQ15 () { }
	inline FPQ15 (const double v) 
	{
		if ( v >= MAX_FPrQ15
		){	Int = MAX_FPiQ15;			//Rebosamiento positivo. Saturación de 
					Dec = 0;
		} else {    if ( v <= MIN_FPrQ15
				){	Int = MIN_FPiQ15;	//Rebosamiento negativo. Saturación de 
							Dec = 0;
				} else { V = v * UNOFPQ15;
				};
		};
	}

	inline FPQ15 (const int v) {	Int = v; Dec = 0; }
	inline FPQ15 (const long v) {	V = v; }
	inline FPQ15 (const int ParteEntera, const int ParteDecimal)
	{
		Int = ParteEntera;
		Dec = ParteDecimal;
	}
		

	// OPERADORES DE CONVERSION
	inline operator long	()	{ return Int; }
	inline operator int		()	{ return Int; }
	inline operator double	()	{ return V * INVONEFP2R; }

	// OPERADORES ARITMETICOS
	inline FPQ15 operator + (FPQ15 a) { return FPQ15 (a.V + V); }
	inline FPQ15 operator - (FPQ15 a) { return FPQ15(V - a.V); }
	inline FPQ15 FPQ15::operator - () { return FPQ15(-V); }

	FPQ15 operator *		(FPQ15);
	FPQ15 operator /		(FPQ15);

	inline void operator ++ ()		{ V+=UNOFPQ15; }
	inline void operator -- ()		{ V-=UNOFPQ15; }
	inline void operator += (FPQ15 a) { V += a.V; }
	inline void operator -= (FPQ15 a) { V -= a.V; }
	inline void operator *= (FPQ15 a) { *this = (a*(*this)); }
		
	inline FPQ15 operator >> (int n) { return FPQ15(V >> n); }
	inline FPQ15 operator << (int n) { return FPQ15(V << n); }

	// OPERADORES BOOLEANOS
	inline bool operator >   (const FPQ15 a) { return V > a.V; }
	inline bool operator <   (const FPQ15 a) { return V < a.V; }
	inline bool operator >=  (const FPQ15 a) { return V >= a.V; }
	inline bool operator <=  (const FPQ15 a) { return V <= a.V; }
	inline bool operator ==  (const FPQ15 a) { return V == a.V; }
	inline bool operator !=  (const FPQ15 a) { return V != a.V; }

	// OPERADORES DE REDONDEO y VARIOS
	FPQ15 Round						();
	int	  Roundi					();
	void Redondea			();
	FPQ15 Abs						();	//Valor absoluto del número

};

FPQ15 Multiplica (FPQ15 a, FPQ15 b);		//Versión acelerada de multiplicación de dos números en coma fija
//Determina el máximo entre dos valores en coma fija
#define MaxQ15(a,b) ((a)>=(b))?(a):(b);

#endif
