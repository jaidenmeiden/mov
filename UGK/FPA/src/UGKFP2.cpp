/* UNIDAD DE TRATAMIENTO DE NUMEROS EN FORMATO COMA FIJA 32 BITS
			DESARROLLADO POR RAMON P. MOLLA VAYA.
				VALENCIA. DICIEMBRE DE 1992 (c)


	Unidad de descripcion de la clase COMA FIJA 2.
	Representacion en coma fija de 32 bits. 16 for la parte FractionalPart y
	16 for la IntegerPart.
*/

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
#include <UGKFP2.h>
#include <UGKutilities.h>

#define LN2		  11629080L	//Natural logarithm en FP1

#define MIN_EXP_FP2 11
#define MAX_EXP_FP2 11
#define DISPLAC_EXP  3 // 2 en caso de tablas de 16K

#define DISPLAC_FP0_FP2 15
#define DISPLAC_FP1_FP2  8

//Tablas exponential parte IntegerPart.

extern long expCF2[];

extern long *lnp; 		// Vector de tabla de logaritmos neperianos.[0, 1]
extern long *expncl;	// Vector de tabla de exponenciales.        [0, 1]

static FP2 R32000 (181.019336); //Raiz cuadrada de 2^15-1.

using namespace std;

FP0 FP2::sin ()
{
	static FP1 cf1;
	// Se eliminan todas las vueltas completas y se convierte en FP1.
	cf1.Long = (Long % TWOPIFP2) << FPDISPLACE;
	return cf1.sin ();
}

FP0 FP2::cosin()
{
	static FP1 cf1;
	// Se eliminan todas las vueltas completas y se convierte en FP1.
	cf1.Long = (Long % TWOPIFP2) << FPDISPLACE;
	return cf1.cosin();
}

FP0 FP2::sinil ()
{
	static FP1 cf1;
	// Se eliminan todas las vueltas completas y se convierte en FP1.
	cf1.Long = (Long % TWOPIFP2) << FPDISPLACE;
	return cf1.sinil ();
}

FP0 FP2::cosinil ()
{
	static FP1 cf1;
	// Se eliminan todas las vueltas completas y se convierte en FP1.
	cf1.Long = (Long % TWOPIFP2) << FPDISPLACE;
	return cf1.cosinil ();
}

// LOG NEP: FP1 -> FP1

FP1 FP2::ln()
{
	static FP1 cf1;
	long auxl;
	int c;

	if ( Long <= 0
	){ cout << "No se puede hallar el logaritmo de "
				  << double(*this) << endl;
			 return cf1;
	};

	c = UGK::Zeros (Long);	//Total de Zeros tiene por la izquierda el parametro.

	/*Se normaliza la mantisa for poder acceder a la tabla de logaritmos.
	  Dado que las tablas son de tamaño 8K, se necesitaran al menos 13 bits for
	  acceder a ellas. Puesto que la palabra que se utiliza es de 32 bits, el
	  numero maximo de Zeros por la izquierda permitidos seran 32 - 13 = 19. Si
	  el numero de Zeros es menor de 19 entonces eliminamos los bits
	  significativos que sobran; sino, habra que poner Zeros.
	  */

	if ( c > 19
	){ auxl = Long << (c - 19);
	} else { 	 auxl = Long >> (19 - c);
	};

	cf1.Long = lnp [auxl] + LN2 * (POS_PTO_DEC-c);	//ln (2^a * b) = a*ln 2 + ln b
	return cf1;
}

FP1 FP2::lnil()
{

	static FP1 cf1;
	long auxl, FractionalPart;
	int c;

	if ( Long <= 0
	){ cout << "No se puede hallar el logaritmo de "
				  << double(*this) << endl;
			 return cf1;
	};

	c = UGK::Zeros (Long);	//Total de Zeros tiene por la izquierda el parametro.

	//Se normaliza la mantisa for poder acceder a la tabla de logaritmos.

	if ( c >= 19
	){ auxl     = Long << (c - 19);
			 //ln (2^a * b) = a*ln 2 + ln b
			 cf1.Long = lnp [auxl] + LN2*(POS_PTO_DEC-c);
	} else { 	 auxl = Long >> (19 - c);
			 FractionalPart  = ((Long << (12 + c)) & 2147483647L) >> (12 + c);
			 cf1.Long = LN2 * (POS_PTO_DEC-c) + lnp [auxl] +
						(((lnp [auxl+1] - lnp[auxl]) * FractionalPart) >> (19-c));
	};

	return cf1;
}

//FP2 FP2::expasm					()
//{
//	static FP1 cf1;
//	static FP2 fp2;
//
//	if ( Long < ONEFP2)
//	{
//		cf1.Long   = Long << 8;
//		return  cf1.exp ();
//	} 
//	else
//	{     
//		cf1.Long   = easm (Ints[UGKFP_LO]);//Exp. de la parte FractionalPart.
//		//Exp. de la parte  IntegerPart.
//		fp2.Long  = expCF2 [MIN_EXP_FP2 + Ints[UGKFP_HI]];
//		return fp2 * cf1;
//	};
//}

FP2 FP2::exp				 	()
{

	long  FractionalPart;
	static FP2 fp2;
	static FP1 cf1;

	if ( Long < ONEFP2
	){ cf1.Long = Long << 8;
			 return  cf1.exp ();
	} else {     FractionalPart  = Long & 65535L; // Se seleccionan los 24 lsb
			 if ( FractionalPart & 4 		  // 2 en caso de tablas de 16K
			 ){ FractionalPart = FractionalPart >> DISPLAC_EXP;
						FractionalPart++;
			 } else {     FractionalPart = FractionalPart >> DISPLAC_EXP;
			 };
			 cf1.Long   = expncl [FractionalPart]; 	//exponential de la parte FractionalPart.
			 //Exp. de parte IntegerPart.
			 fp2.Long  = expCF2 [MIN_EXP_FP2 + Ints[UGKFP_HI]];
			 return fp2 * cf1;
	};
}

FP2 FP2::expil					()
{

	long FractionalPart;
	int resto;
	static FP2 fp2;
	static FP1 cf1;

	if ( Long < ONEFP2
	){ cf1.Long = Long << 8;
			 return  cf1.expil ();
	} else {     FractionalPart    = Long & 65535L;			// Se seleccionan los 16 lsb
			 FractionalPart	= FractionalPart >> DISPLAC_EXP;
			 resto      =  Long &     7;
			 // Exp. de parte IntegerPart.
			 fp2.Long  = expCF2 [MIN_EXP_FP2 + Ints[UGKFP_HI]];
			 cf1.Long  = expncl [FractionalPart] // Exp. de la parte FractionalPart.
						+ (((expncl [FractionalPart+1] - expncl [FractionalPart])*resto)
						>> DISPLAC_EXP);
			 return fp2 * cf1;
	};
}

FP2 FP2::sqrt()		{ static FP0 c; c.Long = Long; return R32000 * c.sqrt(); }
FP2 FP2::sqrtil()	{ static FP0 c; c.Long = Long; return R32000 * c.sqrtil(); }
FP2 FP2::sqrt2()	{ static FP0 c; c.Long = Long; return R32000 * c.sqrt2(); }
FP2 FP2::sqrt2il()	{ static FP0 c; c.Long = Long; return R32000 * c.sqrt2il(); }

FP2::operator long ()
{

long aux;

if ( Long < 0
){ // Bit vigesimo cuarto a 0 significa que hay que redondear.
		 aux = Long - ZERO5FP2;
		 aux = aux >> POS_PTO_DEC;
} else {	 // Bit vigesimo cuarto a 1, como v.Long es positivo, hay que
		 // incrementar en una unidad tras la rotacion.
		 aux = Long + ZERO5FP2;
		 aux = aux >> POS_PTO_DEC;
};
return aux;
}

FP2::FP2 (const FP0 v)
{
if ( v.Long < 0
){ // Bit decimo quinto significa que hay que redondear
		 if ( (v.Long & 32768L) == 0
		 ){ Long = v.Long >> DISPLAC_FP0_FP2;
				  Long--;
		 } else {     Long = v.Long >> DISPLAC_FP0_FP2;
		 };
} else {     if ( v.Long & 32768L     // Bit decimo quinto a 1, como v.Long es
								// positivo, hay que incrementar en una
								// unidad tras la rotacion.
		 ){ Long = v.Long >> DISPLAC_FP0_FP2;
				  Long++;
		 } else {     Long = v.Long >> DISPLAC_FP0_FP2;
		 };
};
}

FP2::FP2 (const FP1 v)
{
if ( v.Long < 0
){ // Bit octavo a 0 significa que hay que redondear
		 if ( (v.Long & 128) == 0
		 ){ Long = v.Long >> DISPLAC_FP1_FP2;
				  Long--;
		 } else {     Long = v.Long >> DISPLAC_FP1_FP2;
		 };
} else {     if ( v.Long & 128 // Bit octavo a 1, como v.Long es positivo, hay que
						  // incrementar en una unidad tras la rotacion
		 ){ Long = v.Long >> DISPLAC_FP1_FP2;
				  Long++;
		 } else {     Long = v.Long >> DISPLAC_FP1_FP2;
		 };
};
}

/* Puesto que hacemos una rotacion a la izquierda de edx:eax, tenemos que
averiguar si tras hacer el desplazamiento en un bit, el MSb de eax es tal
que debamos incrementar/decrementar a edx. Ese bit es el numero 15 y su
Long en FractionalPart es el anterior.
*/
FP2 FP2::operator * (FP2 a)
{
	long aux;

	aux = Long;
	__asm
	{
		mov eax, aux
		mov edx, a.Long
		imul edx
		// FP2 * FP2 -> CF4. Por lo tanto, deberemos desplazar el resultado 16
		// posiciones a la izquierda.
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
	__asm dec edx
	__asm jmp seguir
positivo :
	// Al contrario que en el caso anterior, si el MSb es uno,
	// incrementaremos la parte de mayor peso en una unidad.
	__asm
	{
		and eax, BIT15
			jnz inc_edx
			jmp seguir
	}
inc_edx:
	__asm inc edx
seguir :
	__asm
	{
		mov a.Long, edx
			inc edx //Testeamos si los 4 MSB sólo contienen el signo negativo.
			jnz nocero
			mov a.Long, edx
	}
nocero:
	return a;
}

FP2 FP2::operator * (FP0 a)
{
	long aux;
	static FP2 cf2;


	aux = Long;
	__asm
	{
		mov eax, aux
			mov edx, a.Long
			imul edx
			// FP0 * FP2 -> FP2. Por lo tanto, deberemos desplazar el resultado 16
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
	__asm dec edx
	__asm jmp seguir
positivo :
	// Al contrario que en el caso anterior, si el MSb es uno,
	// incrementaremos la parte de mayor peso en una unidad.
	__asm
	{
		and eax, BIT30
			jnz inc_edx
			jmp seguir
	}
inc_edx:
	__asm inc edx
seguir :
	__asm
	{
		mov aux, edx
			inc edx //Testeamos si los 4 MSB s¢lo contienen el signo negativo.
			jnz nocero
			mov aux, edx
	}
nocero:
	cf2.Long = aux;
	return cf2;
}

FP2 FP2::operator * (FP1 a)
{
	long aux;
	static FP2 cf2;

	aux = Long;
	__asm
	{
		mov eax, aux
			mov edx, a.Long
			imul edx
			// FP1 * FP2 -> FP3. Por lo tanto, deberemos desplazar el resultado 16
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
	__asm dec edx
	__asm jmp seguir
positivo :
	// Al contrario que en el caso anterior, si el MSb es uno,
	// incrementaremos la parte de mayor peso en una unidad.
	__asm
	{
		and eax, BIT23
			jnz inc_edx
			jmp seguir
	}
inc_edx:
	__asm inc edx
seguir :
	__asm
	{
		mov aux, edx
			inc edx //Testeamos si los 4 MSB s¢lo contienen el signo negativo.
			jnz nocero
			mov aux, edx
	}
nocero:
	cf2.Long = aux;
	return cf2;
}

FP0 FP2::operator / (FP2 a)
{
	long l;
	static FP0 cf0;

	if (Long == a.Long
		){
		cf0.Long = ONEFP0;
	}
	else {
		l = Long;
		__asm
		{
			mov edx, l
				mov ebx, a.Long
				// Anulamos el acumulador
				xor eax, eax
				shrd eax, edx, 1
				sar edx, 1
				idiv ebx
				// Movemos el cociente al resultado
				mov l, eax
		}
		cf0.Long = l;
	};
	return cf0;
}
