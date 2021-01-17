/* UNIDAD DE TRATAMIENTO DE NUMEROS EN FORMATO COMA FIJA 32 BITS
			DESARROLLADO POR RAMON P. MOLLA VAYA.
				VALENCIA. DICIEMBRE DE 1992 (c)


  Unidad de descripcion de la clase COMA FIJA 1.
  Representacion en coma fija de 32 bits. 24 for la parte FractionalPart y
  8 for la IntegerPart.
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <UGKFP1.h>
#include <UGKutilities.h>

#define DISPLAC_ANG       12  // 11 for 16K
#define DISPLAC_LOG       11  // 10 for 16K
#define DISPLAC_EXP       11  // 10 for 16K

#define MAX_SINE        6434  // 12868 for 16K
#define MAX_LOG         8192  // 16382 for 16K
#define MAX_EXP         8192  // 16382 for 16K

#define LN2         11629080L //Natural logarithm of 2 in FP1
#define LN128       81403560L //Natural logarithm of 128 in FP1
#define LSB24		16777215L //24 bits menos significativos

#define MIN_EXP_FP1 16
#define MIN_EXP_FP2 11
#define MIN_EXP_FP3  5

#define MAX_EXP_FP1  4
#define MAX_EXP_FP2 11
#define MAX_EXP_FP3 16

#define EXP_FP1     21
#define EXP_FP2     23
#define EXP_FP3     22

FP1 cf1, cf11;

FP1 R128(11.3137085),
    ZEROFP1;

//Tablas de la parte IntegerPart de la funcion exponential.
long expCF1[EXP_FP1];
long expCF2[EXP_FP2];
long expCF3[EXP_FP3];

long *expncl = NULL;// Exponential			array [0, 1]
long *sen = NULL;	// Sine					array [0, pi/2]
long *lnp = NULL;	// Natural logarithm	array [0, 1]

using namespace std;

long sin(long angle);
long s(long x);

void InitializeSines()
{
	int  i;
	double    auxr = 0.0,
		inc_ang; //Diferencia del angulo entre dos posiciones consecutivas
				 //de la tabla de sins.

	if (NULL != sen)
		cout << "Atencion : Tabla de sins ya ha sido inicializada." << endl;
	else {
		//Se reserva memoria for la tabla de conversion.
		sen = (long*)malloc((MAX_SINE + 1) * sizeof(long));

		//Se calculan los incrementos.
		inc_ang = M_PI / 2.0 / MAX_SINE;

		for (i = 0; i <= MAX_SINE; i++)
		{
			sen[i] = ONEFP0R * sin(auxr);
			auxr += inc_ang;
		}
	};
}

//funcion que inicializa los logaritmos
void initializeLogarithms()
{
	int  i;
	double    auxr,
		inc_log; //Diferencia entre dos posiciones consecutivas de la tabla
				 //de logaritmos.

	if (NULL != lnp)
		cout << "Atencion : Tabla de logaritmos ya ha sido inicializada."
			<< endl;
	else {	//Se reserva memoria for tablas de conversion.
		lnp = (long*)malloc((MAX_LOG + 1) * sizeof(long));

		//Se calculan los incrementos.
		inc_log = 1.0 / MAX_LOG;

		auxr = inc_log;
		for (i = 1; i <= MAX_LOG; i++)
		{
			lnp[i] = ONEFP1R * log(auxr);
			auxr += inc_log;
		}
		lnp[0] = 2 * lnp[1]; //Valor mas pequeño daria -infinito. No se debe calcular
	};
}

//funcion que inicializa los exponenciales
void initializeExponential()
{

	int  i;
	double    auxr = 0.0,
		inc_exp; //Diferencia entre dos posiciones consecutivas de la tabla
				 //de exponenciales.

	if (NULL != expncl)
		cout << "Atencion : Tabla de exponenciales ya ha sido inicializada."
			<< endl;
	else {
		//Se reserva memoria for tablas de conversion.
		expncl = (long*)malloc((MAX_EXP + 1) * sizeof(long));

		//Se calculan los incrementos.
		inc_exp = 1.0 / MAX_EXP;

		//Inic. de tablas de parte IntegerPart del exponente de funcion exponential.

		for (i = -MIN_EXP_FP1; i <= MAX_EXP_FP1; i++)
			expCF1[MIN_EXP_FP1 + i] = ONEFP1R * exp(i);

		for (i = -MIN_EXP_FP2; i <= MAX_EXP_FP2; i++)
			expCF2[MIN_EXP_FP2 + i] = ONEFP2R * exp(i);

		for (i = -MIN_EXP_FP3; i <= MAX_EXP_FP3; i++)
			expCF3[MIN_EXP_FP3 + i] = ONEFP3R * exp(i);

		//Inic. de tablas de parte FractionalPart del exponente de funcion exponential.
		for (i = 0; i <= MAX_EXP; i++)
		{
			expncl[i] = ONEFP1R * exp(auxr);
			auxr += inc_exp;
		}
	};
}

// sin : FP1 -> FP0

long s(long x)
{
	/* A partir de este punto, ya tenemos convertido cualquier angulo al primer
	   cuadrante. Ahora, s¢lo tenemos que calcular el sin de este angulo.
	*/

	//BIT11 en tablas de 16K
	if (x & BIT12)
	{
		x = x >> DISPLAC_ANG;
		x++;
	}
	else {
		x = x >> DISPLAC_ANG;
	};

	return sen[x];
}

#ifndef UGKFPA_ASSEMBLER
FP0 FP1::sin()
{
	long l;
	static FP0 c;

	l = Long % TWOPI_FP1; //Eliminamos todas las vueltas completas.

	if (l < 0)
		if (l > -HALFPI_FP1)
			c.Long = -s(-l);
		else if (l > -PI_FP1)
		{
			l += PI_FP1;
			c.Long = -s(l);
		}
		else
		{
			if (l > -TQPI_FP1)
				l = -PI_FP1 - l;
			else
				l += TWOPI_FP1;
			c.Long = s(l);
		}
	else  if (l > TQPI_FP1)
	{
		l = TWOPI_FP1 - l;
		c.Long = -s(l);
	}
	else if (l > PI_FP1)
	{
		l -= PI_FP1;
		c.Long = -s(l);
	}
	else
	{
		if (l > HALFPI_FP1) l = PI_FP1 - l;
		c.Long = s(l);
	};
	return c;
}
#else

long FP1 : sin(long angle)
{

	long l;

	l = angle % TWOPI_FP1; //Eliminamos todas las vueltas completas.

	if (l < 0)
		if (l > -HALFPI_FP1)
			l = -s(-l);
		else {
			if (l > -PI_FP1)
			{
				l += PI_FP1;
				l = -s(l);
			}
			else 
			{
				if (l > -TQPI_FP1)
					l = -PI_FP1 - l;
				else
					l += TWOPI_FP1;
				l = s(l);
			};
		};
	else {
		if (l > TQPI_FP1)
		{
			l = TWOPI_FP1 - l;
			l = -s(l);
		}
		else
			if (l > PI_FP1)
			{
				l -= PI_FP1;
				l = -s(l);
			}
			else
			{
				if (l > HALFPI_FP1)
					l = PI_FP1 - l;
				l = s(l);
			};
	};
	return l;

}
/*

FP0 FP1::sin()
{
	long l;
	static FP0 c;

	l = Long % TWOPI_FP1;

	c.Long = sinasm(l);
	return c;
}

*/
#endif

#ifndef UGKFPA_ASSEMBLER
FP0 FP1::cosin()
{
	long l;
	static FP0 c;

	l = Long % TWOPI_FP1; //Eliminamos todas las vueltas completas.

	if (l < 0)
	{
		if (l > -HALFPI_FP1)
		{
			l += HALFPI_FP1;
			c.Long = s(l);
		}
		else {
			if (l > -PI_FP1)
			{
				l += HALFPI_FP1;
				c.Long = -s(-l);
			}
			else {
				if (l > -TQPI_FP1)
				{
					l += TQPI_FP1;
					c.Long = -s(l);
				}
				else {
					l += TQPI_FP1;
					c.Long = s(-l);
				};
			};
		};
	}
	else {
		if (l > TQPI_FP1)
		{
			l -= TQPI_FP1;
			c.Long = s(l);
		}
		else {
			if (l > PI_FP1)
			{
				l = TQPI_FP1 - l;
				c.Long = -s(l);
			}
			else {
				if (l > HALFPI_FP1)
				{
					l -= HALFPI_FP1;
					c.Long = -s(l);
				}
				else {
					l = HALFPI_FP1 - l;
					c.Long = s(l);
				};
			};
		};
	};
	return c;
}

#else
/**
*  @fn FP0 FP1::cosin()
*	Calculates cosine value via assembler
*  @return FP0 cosine value
*/
FP0 FP1::cosin()
{
	long l;
	static FP0 c;

	l = Long % TWOPI_FP1; //Eliminamos todas las vueltas completas.

	if (l < 0)
	{
		if (l > -HALFPI_FP1)
		{
			l += HALFPI_FP1;
			l = sasm(l);
		}
		else {
			if (l > -PI_FP1)
			{
				l = -l - HALFPI_FP1;
				l = -sasm(l);
			}
			else {
				if (l > -TQPI_FP1)
				{
					l += TQPI_FP1;
					l = -sasm(l);
				}
				else {
					l = -l - TQPI_FP1;
					l = sasm(l);
				};
			};
		};
	}
	else {
		if (l > TQPI_FP1)
		{
			l -= TQPI_FP1;
			l = sasm(l);
		}
		else {
			if (l > PI_FP1)
			{
				l = TQPI_FP1 - l;
				l = -sasm(l);
			}
			else {
				if (l > HALFPI_FP1)
				{
					l -= HALFPI_FP1;
					l = -sasm(l);
				}
				else {
					l = HALFPI_FP1 - l;
					l = sasm(l);
				};
			};
		};
	};
	c.Long = l;
	return c;
}
#endif

long sil(long x)
{
	long FractionalPart;

	/* A partir de este punto, ya tenemos convertido cualquier angulo al primer
	   cuadrante. Ahora, s¢lo tenemos que calcular el sin de este angulo. */

	FractionalPart = x & 4095; //Valor de los 12 bits lsb. 2047 en tablas 16K
	x = x >> DISPLAC_ANG;

	return sen[x] + (((sen[x + 1] - sen[x]) * FractionalPart) >> DISPLAC_ANG);
}

FP0 FP1::sinil()
{
	long l;
	static FP0 c;

	l = Long % TWOPI_FP1; //Eliminamos todas las vueltas completas.

	if (l < 0)
	{
		if (l > -HALFPI_FP1)
			c.Long = -sil(-l);
		else {
			if (l > -PI_FP1)
			{
				l += PI_FP1;
				c.Long = -sil(l);
			}
			else {
					if (l > -TQPI_FP1)
						l = -PI_FP1 - l;
					else
						l += TWOPI_FP1;
					c.Long = sil(l);
				 };
		};
	}
	else {
		if (l > TQPI_FP1)
		{
			l = TWOPI_FP1 - l;
			c.Long = -sil(l);
		}
		else {
			if (l > PI_FP1)
			{
				l -= PI_FP1;
				c.Long = -sil(l);
			}
			else {
				if (l > HALFPI_FP1)
					l = PI_FP1 - l;
				c.Long = sil(l);
			};
		};
	};
	return c;
}

FP0 FP1::cosinil()
{
	long l;
	static FP0 c;

	l = Long % TWOPI_FP1; //Eliminamos todas las vueltas completas.

	if (l < 0)
	{
		if (l > -HALFPI_FP1)
		{
			l += HALFPI_FP1;
			c.Long = sil(l);
		}
		else {
			if (l > -PI_FP1)
			{
				l += HALFPI_FP1;
				c.Long = -sil(-l);
			}
			else {
				if (l > -TQPI_FP1)
				{
					l += TQPI_FP1;
					c.Long = -sil(l);
				}
				else {
					l += TQPI_FP1;
					c.Long = sil(-l);
				};
			};
		};
	}
	else {
		if (l > TQPI_FP1)
		{
			l -= TQPI_FP1;
			c.Long = sil(l);
		}
		else {
			if (l > PI_FP1)
			{
				l = TQPI_FP1 - l;
				c.Long = -sil(l);
			}
			else {
				if (l > HALFPI_FP1)
				{
					l -= HALFPI_FP1;
					c.Long = -sil(l);
				}
				else {
					l = HALFPI_FP1 - l;
					c.Long = sil(l);
				};
			};
		};
	};
	return c;
}

FP1 FP1::ln()
{
	int c;

	if (Long <= 0)
	{
		cout << "No se puede hallar el logaritmo de " << double(*this) << endl;
		return cf1;
	};

	c = UGK::Zeros(Long);  //Total Zeros tiene por la izquierda el parametro.

	//Se normaliza la mantisa for poder acceder a la tabla de logaritmos.

	if (c >= 19)
		cf1.Long = lnp[Long] - 127919880L;
	else
		//ln (2^a * b) = a*ln 2 + ln b
		cf1.Long = lnp[Long >> (19 - c)] + LN2 * (8 - c);

	return cf1;
}

FP1 FP1::lnil()
{

	long auxl, FractionalPart;
	int c;

	if (Long <= 0)
	{
		cout << "No se puede hallar el logaritmo de "
			<< double(*this) << endl;
		return cf1;
	};

	c = UGK::Zeros(Long);  //Total de Zeros tiene por la izquierda el parametro.

	//Se normaliza la mantisa for poder acceder a la tabla de logaritmos.

	if (c >= 19)
		cf1.Long = lnp[Long] - 127919880L; //-11*ln(2^-1) en formato FP1
	else {
		auxl = Long >> (19 - c);
		FractionalPart = ((Long << (12 + c)) & 2147483647L) >> (12 + c);
		cf1.Long = LN2 * (8 - c) + lnp[auxl] +
			(((lnp[auxl + 1] - lnp[auxl]) * FractionalPart) >> (19 - c));
	};
	return cf1;
}

FP1 FP1::ln2()
{
	long auxl;

	if (Long <= 0)
	{
		cout << "No se puede hallar el logaritmo de " << double(*this) << endl;
		return cf1;
	};

	if (Long & BIT18)
	{
		auxl = Long >> DESP18;
		auxl++;
	}
	else auxl = Long >> DESP18;

	cf1.Long = LN128 + lnp[auxl];
	return cf1;
}

FP1 FP1::ln2il()
{

	long auxl, FractionalPart;

	if (Long <= 0)
	{
		cout << "No se puede hallar el logaritmo de "
			<< double(*this) << endl;
		return cf1;
	};

	FractionalPart = (Long >> 6) & 4095; // 2^12 - 1
	auxl = Long >> DESP18;
	cf1.Long = LN128 + lnp[auxl] + ((((lnp[auxl + 1] - lnp[auxl]) >> 6) * FractionalPart) >> 6);

	return cf1;
}

long parte_entera_FP1(long x)
{

	/* Si justo antes de obtener la parte IntegerPart completa, lo que aparece es el
	   signo negativo arrastrado, o bien el Long -1, al desplazar un bit mas
	   (dividir por dos) el Long de la parte IntegerPart sera cero.
	*/

	x = x >> 24;

	if (x > MAX_EXP_FP1)
	{
		cout << "Error: Exponente " << x
			<< " excede el maximo Long permitido en funcion EXPASM. " << endl;
		exit(-1);
	}
	else {
		if (x < -MIN_EXP_FP1 + 1)
		{
			cout << "Error: Exponente " << x <<
				" excede el minimo Long permitido en funcion EXPASM. " << endl;
			exit(-1);
		};
	};

	return x;
}

#ifndef UGKFPA_ASSEMBLER

FP1 FP1::exp()
{
	long  FractionalPart;
	int IntegerPart;

	if (Long < 0)
	{
		// Se seleccionan los 24 lsb
		if (FractionalPart = -Long & LSB24 )
		{
			//512 en caso de tablas de 16K
			if (FractionalPart & 1024)
			{
				FractionalPart = FractionalPart >> DISPLAC_EXP;
				FractionalPart++;
			}
			else {
				FractionalPart = FractionalPart >> DISPLAC_EXP;
			};
			cf11.Long = expncl[FractionalPart]; //Exp. de la parte FractionalPart.
			IntegerPart = MIN_EXP_FP1 + parte_entera_FP1(Long) + 1;
			//Exp. de parte IntegerPart.
		}
		else {
			cf11.Long = ONEFP1;
			IntegerPart = MIN_EXP_FP1 + parte_entera_FP1(Long);
			//Exp. de parte IntegerPart.
		};
		cf1.Long = expCF1[IntegerPart];//Exp. de parte IntegerPart.
		return  cf1 / cf11;
	}
	else {
		FractionalPart = Long & LSB24; // Se seleccionan los 24 lsb
		//512 en caso de tablas de 16K
		if (FractionalPart & 1024 			 )
		{
			FractionalPart = FractionalPart >> DISPLAC_EXP;
			FractionalPart++;
		}
		else {
			FractionalPart = FractionalPart >> DISPLAC_EXP;
		};
		cf11.Long = expncl[FractionalPart]; //exponential de la parte FractionalPart.
		//Exp. de parte IntegerPart.
		cf1.Long = expCF1[MIN_EXP_FP1 + parte_entera_FP1(Long)];
		if (Long < ONEFP1)
			return cf11;
		else
			return cf1 * cf11;
	};
}
#else	//Assembler version
FP1 FP1::exp()
{

	//Exp. de la parte IntegerPart.
	cf1.Long = expCF1[MIN_EXP_FP1 + parte_entera_FP1(Long)];
	if (Long < 0)
	{   //Exp. de la parte FractionalPart.
		cf11.Long = easm((((-Long) & LSB24) << 7) - ONEFP0R);
		return  cf1 / cf11;
	}
	else {        //Exp. de la parte FractionalPart.
		cf11.Long = easm((Long & LSB24) << 7);
		if (Long < ONEFP1)
			return cf11;
		else
			return cf1 * cf11;
	};
}
#endif

FP1 FP1::expil()
{

	long  FractionalPart, resto;

	if (Long < 0)
	{
		// Se seleccionan los 24 lsb
		if (FractionalPart = -Long & LSB24)
		{
			resto = FractionalPart & 2047;
			FractionalPart = FractionalPart >> DISPLAC_EXP;
			//Exp. de parte IntegerPart.
			cf1.Long = expCF1[MIN_EXP_FP1 + parte_entera_FP1(Long) + 1];
			//exponential de la parte FractionalPart.
			cf11.Long = expncl[FractionalPart] +
				(((expncl[FractionalPart + 1] - expncl[FractionalPart])*resto)
					>> DISPLAC_EXP);
		}
		else {
			cf11.Long = ONEFP1;
			//Exp. de parte IntegerPart.
			cf1.Long = expCF1[MIN_EXP_FP1 + parte_entera_FP1(Long)];
		};
		return  cf1 / cf11;
	}
	else {
		FractionalPart = (Long & LSB24) >> DISPLAC_EXP;// Seleccionan 24 lsb
		resto = Long & 2047;
		// Exp. de parte IntegerPart.
		cf1.Long = expCF1[MIN_EXP_FP1 + parte_entera_FP1(Long)];
		cf11.Long = expncl[FractionalPart] +    		// Exp. de la parte FractionalPart.
			(((expncl[FractionalPart + 1] - expncl[FractionalPart])*resto)
				>> DISPLAC_EXP);
		if (Long < ONEFP1)
			return cf11;
		else
			return cf1 * cf11;
	};
}

FP1::FP1() { Long = 0; }

FP1::FP1(const double v)
{
	if (fabs(v) > MAX_FP1R)
		Error(UGKFPA_RROFP1);
	else Long = v * ONEFP1R;
}

FP1::FP1(const long v1, const long v2) { Long = (v1 << 3 * FPDISPLACE) + (v2 >> FPDISPLACE); }

FP1::FP1(int e)
{
	if (abs(e) > MAX_FP1R)
		Error(UGKFPA_RROFP1);
	else Long = e*ONEFP1;
}

FP1::FP1(const FP0 v)
{
	if (v.Long < 0)
	{ // Bit septimo significa que hay que redondear
		if ((v.Long & 64) == 0)
		{
			Long = v.Long >> 7;
			Long--;
		}
		else {
			Long = v.Long >> 7;
		};
	}
	else {
		// Bit septimo  a 1, como v.Long es
		// positivo, hay que incrementar en una
		// unidad tras la rotacion.
		if (v.Long & 64)
		{
			Long = v.Long >> 7;
			Long++;
		}
		else {
			Long = v.Long >> 7;
		};
	};
}

FP1::operator long()
{

	long aux;

	if (Long < 0)
	{ // Bit vigesimo cuarto a 0 significa que hay que redondear.
		aux = Long - FP1_ZERO5;
		aux = aux >> DEC_POINT_POSFP1;
	}
	else {     // Bit vigesimo cuarto a 1, como v.Long es positivo, hay que
		  // incrementar en una unidad tras la rotacion.
		aux = Long + FP1_ZERO5;
		aux = aux >> DEC_POINT_POSFP1;
	};
	return aux;
}

/* Puesto que hacemos una rotacion a la izquierda de edx:eax, tenemos que
averiguar si tras hacer el desplazamiento en ocho bits, el MSb de eax
es tal que debamos incrementar/decrementar a edx. Ese bit es el numero
23 y su Long en FractionalPart es el anterior. Comenzamos la numeracion de
bits por 1.
*/

FP1 FP1::operator * (FP1 a)
{
	long l;

	l = Long;

	__asm
	{
		mov edx, l
		mov eax, a.Long
		imul edx
		// FP1 * FP1 -> FP2. Por lo tanto, debemos desplazar el resultado 8
		// posiciones a la izquierda.
		shld edx, eax, 8
		test edx, -1
		jge  positivo
		// El resultado es negativo. Si MSb de la palabra de menos peso es 0, al
		// estar en C'2, dicha palabra tiene un Long absoluto > 0.5, y debemos
		// incrementar el Long absoluto de la parte de mayor peso en una unidad.
		// Como esta parte esta representada en Long negativo, restaremos 1.
		and eax, BIT23
		jnz seguir
		dec edx
		jmp seguir
	}
positivo:
	// Al contrario que en el caso anterior, si el MSb es uno, incrementaremos
	// la parte de mayor peso en una unidad.
	__asm
	{
		and eax, BIT23
		jz seguir
		inc edx
	}
seguir:
	__asm
	{
		mov a.Long, edx
		inc edx //Testeamos si los 4 MSB s¢lo contienen el signo negativo.
		jnz nocero
		mov a.Long, edx
	}
nocero:
	return a;
}

FP1 FP1::operator * (FP0 a)
{
	long l;
	static FP1 cf1;

	l = Long;
	__asm
	{
		mov edx, l
		mov eax, a.Long
		imul edx
		// FP0 * FP1 -> FP1. Por lo tanto, debemos desplazar el resultado 1
		// posicion a la izquierda.
		shld edx, eax, 1
		test edx, -1
		jge  positivo
		/* El resultado es negativo. Si MSb de la palabra de menos peso es 0, al
		estar en C'2, dicha palabra tiene un Long absoluto > 0.5, y debemos
		incrementar el Long absoluto de la parte de mayor peso en una unidad.
		Como esta parte esta representada en Long negativo, restaremos 1.
		*/
		and eax, BIT30
		jnz seguir
		dec edx
		jmp seguir
	}
positivo:
	// Al contrario que en el caso anterior, si el MSb es uno, incrementaremos
	// la parte de mayor peso en una unidad.
	__asm
	{
		and eax, BIT30
		jz seguir
		inc edx
	}
seguir:
	__asm
	{
		mov l, edx
		inc edx //Testeamos si los 4 MSB s¢lo contienen el signo negativo.
		jnz nocero
		mov l, edx
	}
nocero:
	cf1.Long = l;
	return cf1;
}

FP0 FP1::operator / (FP1 a)
{
	long aux;

	if (Long == a.Long)
		Long = ONEFP0;
	else {
		aux = Long;
		__asm
		{
			mov edx, aux
			mov ebx, a.Long
			// Anulamos el acumulador
			xor eax, eax
			shrd eax, edx, 1
			sar edx, 1
			idiv ebx
			// Movemos el cociente al resultado
			mov aux, eax
		}
		Long = aux;
	};
	return Long;
}