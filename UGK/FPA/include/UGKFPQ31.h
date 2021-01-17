/* CABECERA DE TRATAMIENTO DE NUMEROS EN FORMATO COMA FIJA 64 BITS
			DESARROLLADO POR RAMON P. MOLLA VAYA.
				VALENCIA. AGOSTO DE 1999 (c)

  Unidad de descripcion de la clase COMA FIJA 2 UTILIZANDO NÚMEROS DE 64 BITS.
  Representacion en coma fija de 64 bits. 32 for la parte FractionalPart y
  32 for la IntegerPart. Utilización de tipo de datos "union" for acelerar acceso
  a parte IntegerPart o FractionalPart
*/

#ifndef FPQ31_YA_DEFINIDA
#define FPQ31_YA_DEFINIDA

#define MENOSUNOFPQ31	4294967295L
#define SIGNONEGFPQ31	4294967295L
#define DOSFPQ31		8589934592
#define UNOFPQ31		4294967296L
#define UNOFPQ31R		4294967296.0
#define CERO5FPQ31		2147483648L
#define CERO25FPQ31		1073741824		//0.25 
#define BIT31Q31 		2147483648L		//En formato de 32 bits
#define MAX_FPQ31		2147483647.0	//Valor máximo (positivo) que puede tomar un FractionalPart en coma fija
#define MIN_FPQ31	   -2147483648.0	//Valor mínimo (positivo) que puede tomar un FractionalPart en coma fija
#define MAX_FPlQ31		2147483647L		//Valor máximo (positivo) que puede tomar un FractionalPart en coma fija
#define MIN_FPlQ31     -2147483648L		//Valor mínimo (positivo) que puede tomar un FractionalPart en coma fija
#define INVONEFP2RQ31	2.3283064365386962890625E-10

class FPQ15;

//Define un número en coma fija de 64 bits donde la parte FractionalPart ocupa 32 bits y la
//parte IntegerPart también
class FPQ31
{
public:
	union {
			//Un número en coma fija de 64 bits puede ser entendido como...
		__int64	V;	//...un entero de 64 bits
		
			//...un entero de 32 bits (parte IntegerPart) con signo 
			//y un entero sin signo de 32 bits (parte FractionalPart) sin signo 
		struct {
			unsigned long	Dec;	//The 16 lsbs represent the FractionalPart part
			long			Int;	//The 16 msbs represent the integer part	
		};

			//...cuatro enteros de 16 bits
		struct {
			unsigned short int DecLo, DecHi;	//Parte FractionalPart
			unsigned short int IntLo, IntHi;	//Parte IntegerPart
		};

			//...un número de 32 bits centrado en el centro de la mantisa.
			//De esta forma, se desprecian los 16 Msb y los 16 lsb
		struct {
			short int	DecLow;	//Parte IntegerPart alta (16 bits) de 32 bits
			long Q15;		//La parte central es la que corresponde a un Q15
			short int	IntHigh;	//Parte IntegerPart alta (16 bits) de 32 bits
		};
	};

	//OPERADORES DE INICIALIZACION
	inline FPQ31 () { }
	inline FPQ31 (const double v) 
	{
		if ( v >= MAX_FPQ31
		){	Int = MAX_FPlQ31;			//Rebosamiento positivo. Saturación de 
					Dec = 0;
		} else {    if ( v <= MIN_FPQ31
				){	Int = MIN_FPlQ31;	//Rebosamiento negativo. Saturación de 
							Dec = 0;
				} else { V = v * UNOFPQ31R + 0.5;
				};
		};
	}

	inline FPQ31 (const int v) {	Int = v; Dec = 0; }
	inline FPQ31 (const long v) {	Int = v; Dec = 0; }
	inline FPQ31 (const __int64 v) {	V = v; }
	inline FPQ31 (const long ParteEntera, const long ParteDecimal)
	{
		Int = ParteEntera;
		Dec = ParteDecimal;
	}
	
	// OPERADORES DE CONVERSION
	inline operator long ()		{ return Int; }
	inline operator int ()	
	{ 
		FPQ31 Aux;
		Aux.V = V + CERO5FPQ31;
		return Aux.Int; 
	}
	inline operator double ()	{ return V * INVONEFP2RQ31; }

	// OPERADORES ARITMETICOS
	inline FPQ31 operator + (FPQ31 a) { return FPQ31 (a.V + V); }
	inline FPQ31 operator - (FPQ31 a) { return FPQ31(V - a.V); }
	inline FPQ31 FPQ31::operator - () { return FPQ31(-V); }

	FPQ31 operator *					(FPQ31);
	FPQ31 operator /					(FPQ31);
	FPQ31 operator /					(FPQ15);

	inline void operator ++ ()		{ V+=UNOFPQ31; }
	inline void operator -- ()		{ V-=UNOFPQ31; }
	inline void operator += (FPQ31 a) { V += a.V; }
	inline void operator -= (FPQ31 a) { V -= a.V; }
	inline void operator *= (FPQ31 a) { *this = (a*(*this)); }
	
	inline FPQ31 operator >> (int n) { return FPQ31(V >> n); }
	inline FPQ31 operator << (int n) { return FPQ31(V << n); }

	// OPERADORES BOOLEANOS
	inline bool operator >   (FPQ31 a) { return V > a.V; }
	inline bool operator <   (FPQ31 a) { return V < a.V; }
	inline bool operator >=  (FPQ31 a) { return V >= a.V; }
	inline bool operator <=  (FPQ31 a) { return V <= a.V; }
	inline bool operator ==  (FPQ31 a) { return V == a.V; }
	inline bool operator !=  (FPQ31 a) { return V != a.V; }

	// OPERADORES DE REDONDEO
	FPQ31 Round						();
	void Redondea			();
	FPQ31 Abs						();

};

#define MaxQ31(a,b) (a>=b)?a:b;

#endif
