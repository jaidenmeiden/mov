/**	Fixed Point Arithmetic based on 32 bits integer numbers
*	Class FIXED POINT 3.
*	24 bits for the Integer Part (including sign bit) and 8 for the Fractional Part

*	Prefix: UGKFPA_

*	@author Ramon Molla
*	@modified 
*	@version 2014-11
*/

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <UGKFP3.h>
#include <UGKutilities.h>

#define LN2        11629080L  //Natural logarithm en FP1

#define FP3_ZERO5		128 //Bit numero 7 a uno.
#define MIN_EXP_FP3  	  5
#define MAX_EXP_FP3 	 16

FP2	R8M(2896.309203);

using namespace std;

extern long expCF3[];  //Tablas exponential parte IntegerPart.

extern long *lnp;      // Vector de tabla de logaritmos neperianos.[0, 1]
extern long *expncl;   // Vector de tabla de exponenciales.        [0, 1]

FP0 FP3::sin()
{
	static FP1 cf1;

	// Se eliminan todas las vueltas completas y se convierte en FP1.
	cf1.Long = ((Long << 8) % TWOPIFP2) << 8;
	return cf1.sin();
}

FP0 FP3::cosin ()
{
static FP1 cf1;

	// Se eliminan todas las vueltas completas y se convierte en FP1.
	cf1.Long = ((Long << 8) % TWOPIFP2) << 8;
	return cf1.cosin ();
}

FP0 FP3::sinil ()
{
	static FP1 cf1;

	// Se eliminan todas las vueltas completas y se convierte en FP1.
	cf1.Long = ((Long << 8) % TWOPIFP2) << 8;
	return cf1.sinil ();
}

FP0 FP3::cosinil ()
{
	static FP1 cf1;

	// Se eliminan todas las vueltas completas y se convierte en FP1.
	cf1.Long = ((Long << 8) % TWOPIFP2) << 8;
	return cf1.cosinil ();
}

// LOG NEP: FP1 -> FP1

FP1 FP3::ln()
{
	long auxl;
	int c;
	static FP1 cf1;

	if ( Long <= 0)
	{
		cout <<"No se puede hallar el logaritmo de "<< double(*this) << endl;
		return cf1;
	}

	c = UGK::Zeros (Long);  //Numero de Zeros por la izquierda del parametro.

	/*Se normaliza la mantisa for poder acceder a la tabla de logaritmos.
	  Dado que las tablas son de tamaño 8K, se necesitaran al menos 13 bits for
	  acceder a ellas. Puesto que la palabra que se utiliza es de 32 bits, el
	  numero maximo de Zeros por la izquierda permitidos seran 32- 13 = 19. Si el
	  numero de Zeros es menor de 19, entonces eliminamos los bits significativos
	  que sobran; sino, habra que poner Zeros.
	  */

	if ( c > 19	)
		auxl = Long << (c - 19);
	else auxl = Long >> (19 - c);

	cf1.Long = lnp [auxl] + LN2 * (DEC_POINT_POSFP3-c); //ln (2^a * b) = a*ln 2 + ln b
	return cf1;
}

	FP1 FP3::lnil()
	{

	long auxl, FractionalPart;
	int c;
	static FP1 cf1;

	if ( Long <= 0)
	{
		cout <<"No se puede hallar el logaritmo de "<< double(*this) << endl;
		return cf1;
	};

	c = UGK::Zeros (Long);  //Cuantos Zeros tiene por la izquierda el parametro.

	//Se normaliza la mantisa for poder acceder a la tabla de logaritmos.

	if (c >= 19)
	{
		auxl     = Long << (c - 19);
		cf1.Long = lnp [auxl] + LN2*(DEC_POINT_POSFP3-c); //ln(2^a*b)=a*ln2+lnb
	} 
	else
	{
		auxl     = Long >> (19 - c);
		FractionalPart  = ((Long << (12 + c)) & 2147483647) >> (12 + c);
		cf1.Long = LN2 * (DEC_POINT_POSFP3-c) + lnp [auxl] +
		(((lnp [auxl+1] - lnp[auxl]) * FractionalPart) >> (19-c));
	};

	return cf1;
}

int parte_entera_FP3 (long x)
{
	x = x >> 8;

	if ( x > MAX_EXP_FP3)
	{
		cout <<  "Error: Exponente " << x <<
				 " excede el maximo Long permitido en funcion EXPASM. " << endl;
		exit (-1);
	} 
	else if ( x < -MIN_EXP_FP3+1)
		 {
			 cout << "Error: Exponente " << x <<
			 " excede el minimo Long permitido en funcion EXPASM. " << endl;
			 exit (-1);
		 };
	return x;
}

// revisar para #ifndef UGKFPA_ASSEMBLER

FP3 FP3::exp ()
{
	static FP3 c3;
	static FP1 cf1;

	if ( Long < ONEFP3)
	{
		cf1.Long = Long << DISPLACE_FP1_FP3;
			
			

		return  cf1.exp ();
	} 
	else
	{     //Exp. de la parte FractionalPart.
			 cf1.Long = easm ((Long & 255) << DISPLACE_FP0_FP3);
			 //Exp. de la parte  IntegerPart.
			 c3.Long  = expCF3 [MIN_EXP_FP3 + parte_entera_FP3 (Long)];
			 return c3 * cf1;
	};
}
//
//FP3 FP3::exp                    ()
//{
//	static FP3 c3;
//	static FP1 cf1;
//
//	if ( Long < ONEFP3)
//	{
//		cf1.Long = Long << DISPLACE_FP1_FP3;
//		return cf1.exp ();
//	} 
//	else
//	{
//		cf1.Long  = expncl [Long & 255];//Exp. de parte FractionalPart.
//		//Exp. de parte  IntegerPart.
//		c3.Long = expCF3 [MIN_EXP_FP3 + parte_entera_FP3 (Long)];
//		return c3 * cf1;
//	};
//}

FP3 FP3::sqrt					()
{
	static FP0 c;

	c.Long = Long;
	return R8M * c.sqrt();
}

FP3 FP3::sqrtil					()
{
	static FP0 c;

	c.Long = Long;
	return R8M * c.sqrtil();
}

FP3 FP3::sqrt2					()
{
	static FP0 c;

	c.Long = Long;
	return R8M * c.sqrt2();
}

FP3 FP3::sqrt2il				()
{
	static FP0 c;

	c.Long = Long;
	return R8M * c.sqrt2il();
}

FP3::FP3 ()
{
Long = 0;
}

FP3::FP3 (const double v)	{if ( fabs (v) > MAX_FP3R)	Error (UGKFPA_RROFP3);	else Long = v * ONEFP3R;}
FP3::FP3 (const int v)		{Long = v * ONEFP3;}

/*FP3::FP3 (const UGKFPA64b v)
{
if ( abs (v.IntegerPart) > MAX_FP3
){ error (UGKFPA_RROFP3);
} else {     Long = (v.IntegerPart << DISPLACE_FP1_FP3) + (v.FractionalPart >>
				 3*DISPLACE_FP1_FP3);
};
}
*/
FP3::FP3 (const long v1, const long v2){Long = (v1 << DISPLACE_FP1_FP3) + (v2 >> 3*DISPLACE_FP1_FP3);}

FP3::operator long ()
{

long aux;
if ( Long < 0
){ // Bit vigesimo cuarto a 0 significa que hay que redondear.
		 aux = Long - FP3_ZERO5;
		 aux = aux >> DEC_POINT_POSFP3;
} else {     // Bit vigesimo cuarto a 1, como v.Long es positivo, hay que
		 // incrementar en una unidad tras la rotacion.
		 aux = Long - FP3_ZERO5;
		 aux = aux >> DEC_POINT_POSFP3;
};
return aux;
}

FP3::operator int (){return (Long + FP3_ZERO5) >> DEC_POINT_POSFP3;}

FP3::FP3 (const FP0 v)
{
if ( v.Long < 0
){ // Bit vigesimo tercero a 0 significa que hay que redondear
		 if ( (v.Long & BIT23) == 0
		 ){ Long = v.Long >> DISPLACE_FP0_FP3;
                  Long--;
         } else {     Long = v.Long >> DISPLACE_FP0_FP3;
         };
} else {     if ( v.Long & BIT23   // Bit vigesimo tercero a 1, como v.Long es
								// positivo, hay que incrementar en una
                                // unidad tras la rotacion
         ){ Long = v.Long >> DISPLACE_FP0_FP3;
                  Long++;
         } else {Long = v.Long >> DISPLACE_FP0_FP3;
         };
};
}

#define BIT16 32768L
FP3::FP3 (const FP1 v)
{
if ( v.Long < 0
){ // Bit decimo quinto a 0 significa que hay que redondear
         if ( (v.Long & BIT16) == 0
		 ){ Long = v.Long >> DISPLACE_FP1_FP3;
                  Long--;
         } else {     Long = v.Long >> DISPLACE_FP1_FP3;
		 };
} else {     if ( v.Long & BIT16     // Bit decimo quinto a 1, como v.Long es
								// positivo, hay que incrementar en una
								// unidad tras la rotacion
         ){ Long = v.Long >> DISPLACE_FP1_FP3;
                  Long++;
         } else {     Long = v.Long >> DISPLACE_FP1_FP3;
         };
};
}


FP3::FP3 (const FP2 v)
{
if ( v.Long < 0
){ // Bit octavo a 0 significa que hay que redondear
         if ( (v.Long & 128) == 0
		 ){ Long = v.Long >> DISPLACE_FP2_FP3;
                  Long--;
         } else {     Long = v.Long >> DISPLACE_FP2_FP3;
         };
} else {     if ( v.Long & 128       // Bit octavo a 1, v.Long es positivo, hay que
								// incrementar en una unidad tras la rotacion
         ){ Long = v.Long >> DISPLACE_FP2_FP3;
                  Long++;
         } else {     Long = v.Long >> DISPLACE_FP2_FP3;
         };
};
}

/* Puesto que hacemos una rotacion a la izquierda de edx:eax, tenemos que
averiguar si tras hacer el desplazamiento en un bit, el MSb de eax es tal
que debamos incrementar/decrementar a edx. Ese bit es el numero 15 y su
Long en FractionalPart es el anterior.
*/
FP3 FP3::operator * (FP3 a)
{
	long aux;

	aux = Long;
	_asm {
		mov eax, aux
			mov edx, a.Long
			imul edx
			// FP3 * FP3 -> CF6. Por lo tanto, debemos desplazar el resultado 24
			// posiciones a la izquierda mas una por el signo.
			shld edx, eax, 24
			test edx, -1
			jge  positivo
			// El resultado es negativo. Si MSb de la palabra de menos peso es 0, al
			// estar en C'2, dicha palabra tiene un Long absoluto > 0.5, y debemos
			// incrementar el Long absoluto de la parte de mayor peso en una unidad.
			// Como esta parte esta representada en Long negativo, restaremos 1.
			and eax, BIT7
			jz  dec_edx
			jmp seguir
	}
dec_edx:
	_asm dec edx
	_asm jmp seguir
positivo :
	// Al contrario que en el caso anterior, si el MSb es uno,
	// incrementaremos la parte de mayor peso en una unidad.
	_asm and eax, BIT7
	_asm jnz inc_edx
	_asm jmp seguir
inc_edx :
	_asm inc edx
seguir :
	_asm {
		mov a.Long, edx
			inc edx //Testeamos si los 4 MSB s¢lo contienen el signo negativo.
			jnz nocero
			mov a.Long, edx
	}
nocero:
	return a;
}

FP3 FP3::operator * (FP2 a)
{
	long aux;
	static FP3 c3;


	aux = Long;

	_asm {
		mov eax, aux
			mov edx, a.Long
			imul edx
			// FP2 * FP3 -> CF5. Por lo tanto, deberemos desplazar el resultado 16
			// posiciones a la izquierda, mas una por el signo.
			shld edx, eax, 16
			test edx, -1
			jge  positivo
			// El resultado es negativo. Si MSb de la palabra de menos peso es 0, al
			// estar en C'2, dicha palabra tiene un Long absoluto > 0.5, y debemos
			// incrementar el Long absoluto de la parte de mayor peso en una unidad.
			// Como esta parte esta representada en Long negativo, restaremos 1.
			and eax, BIT15
			jz  dec_edx
			jmp seguir
	}
dec_edx:
	_asm dec edx
	_asm jmp seguir
positivo :
	// Al contrario que en el caso anterior, si el MSb es uno,
	// incrementaremos la parte de mayor peso en una unidad.
	_asm and eax, BIT15
	_asm jnz inc_edx
	_asm jmp seguir
inc_edx :
	_asm inc edx
seguir :
	_asm {
		mov aux, edx
			inc edx //Testeamos si los 4 MSB s¢lo contienen el signo negativo.
			jnz nocero
			mov aux, edx
	}
nocero:
	c3.Long = aux;
	return c3;
}

FP3 FP3::operator * (FP1 a)
{
	long aux;
	static FP3 c3;

	aux = Long;

	_asm {
		mov eax, aux
			mov edx, a.Long
			imul edx
			// FP1 * FP3 -> CF4. Por lo tanto, deberemos desplazar el resultado 8
			// posiciones a la izquierda, mas una por el signo.
			shld edx, eax, 8
			test edx, -1
			jge  positivo
			// El resultado es negativo. Si MSb de la palabra de menos peso es 0, al
			// estar en C'2, dicha palabra tiene un Long absoluto > 0.5, y debemos
			// incrementar el Long absoluto de la parte de mayor peso en una unidad.
			// Como esta parte esta representada en Long negativo, restaremos 1.
			and eax, BIT23
			jz  dec_edx
			jmp seguir
	}
dec_edx:
	_asm dec edx
	_asm jmp seguir
positivo :
	// Al contrario que en el caso anterior, si el MSb es uno,
	// incrementaremos la parte de mayor peso en una unidad.
	_asm and eax, BIT23
	_asm jnz inc_edx
	_asm jmp seguir
inc_edx :
	_asm inc edx
seguir :
	_asm {
		mov aux, edx
			inc edx //Testeamos si los 4 MSB s¢lo contienen el signo negativo.
			jnz nocero
			mov aux, edx
	}
nocero:
	c3.Long = aux;
	return c3;
}

FP3 FP3::operator * (FP0 a)
{
	long aux;
	static FP3 c3;

	aux = Long;

	_asm {
		mov eax, aux
			mov edx, a.Long
			imul edx
			// FP0 * FP3 -> FP3. Por lo tanto, deberemos desplazar el resultado 1
			// posiciones a la izquierda, mas una por el signo.
			shld edx, eax, 1
			test edx, -1
			jge  positivo
			// El resultado es negativo. Si MSb de la palabra de menos peso es 0, al
			// estar en C'2, dicha palabra tiene un Long absoluto > 0.5, y debemos
			// incrementar el Long absoluto de la parte de mayor peso en una unidad.
			// Como esta parte esta representada en Long negativo, restaremos 1.
			and eax, BIT30
			jz  dec_edx
			jmp seguir
	}
dec_edx:
	_asm dec edx
	_asm jmp seguir
positivo :
	// Al contrario que en el caso anterior, si el MSb es uno,
	// incrementaremos la parte de mayor peso en una unidad.
	_asm and eax, BIT30
	_asm jnz inc_edx
	_asm jmp seguir
inc_edx :
	_asm inc edx
seguir :
	_asm {
		mov aux, edx
			inc edx //Testeamos si los 4 MSB s¢lo contienen el signo negativo.
			jnz nocero
			mov aux, edx
	}
nocero:
	c3.Long = aux;
	return c3;
}

FP0 FP3::operator / (FP3 a)
{
	long aux;
	static FP0 cf0;

	if (Long >= a.Long
		){
		cf0.Long = ONEFP0;
	}
	else {
		aux = Long;
		_asm {
			mov  edx, aux
				mov  ebx, a.Long
				// Anulamos el acumulador
				xor  eax, eax
				shrd eax, edx, 1
				sar  edx, 1
				idiv ebx
				// Movemos el cociente al resultado
				mov aux, eax
		}
		cf0.Long = aux;
	};
	return cf0;
}
