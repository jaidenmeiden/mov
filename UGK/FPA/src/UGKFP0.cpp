/* UNIDAD DE TRATAMIENTO DE NUMEROS EN FORMATO COMA FIJA 32 BITS
			   DESARROLLADO POR RAMON P. MOLLA VAYA.
					VALENCIA. DICIEMBRE DE 1992 (c)


  Unidad de descripcion de la clase COMA FIJA 0.
  Representacion en coma fija de 32 bits. 32 for la parte FractionalPart y
  0 for la IntegerPart. Utiliza notacion en C'2, por lo que un bit se
  destina a bit de signo, y los otros 31 a la mantisa.
*/

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <UGKFP0.h>
#include <UGKutilities.h>
#include <UGKFPArithmetic.h>

#define FP0_ZERO5     1073741824L  //0.5 en formato FP0
#define MAX_ROOT        8192
#define MAX_POT           19
#define SIGN32b		  1073741824L

FP0 R2 [MAX_POT];  // (sqrt (2))^-x, donde x pertenece a [1, 31]

FP0::FP0 (const long v1, const long v2) {Long = v2;}

FP0::operator int ()
{
	if ( Long > FP0_ZERO5)
		return 1;
	else if ( Long < -FP0_ZERO5)
			return -1;
		 else return 0;
}

FP0::operator long ()
{
	if ( Long > FP0_ZERO5)
		return 1;
	else if ( Long < -FP0_ZERO5)
			return -1;
		 else return 0;
}

FP0 FP0::sqrt            ()
{
	static FP0 cf0;

	int c, l;

	if ( Long < 0)
	{
		SquareRootError (Long);
		return -1.0;
	} 
	else if (Long == 0)
		 { 
			 cf0.Long = 0;
			 return cf0;
		 };

	c = UGK::Zeros (Long);  //Total de Zeros tiene por la izquierda el parametro.

	//Se normaliza la mantisa for poder acceder a la tabla de raices.

	if ( c < 19	)
	{
		l = Long >> (18 - c);
		if ( l & 1 )
		{
			l = l >> 1;
			l++;
		}
		else l = l >> 1;
	}
	else 
	{     
		l = Long;
		c = 19;
	};

	cf0.Long  = Roots [l];
	return cf0 * R2 [c-1];
}

FP0 FP0::sqrtil               ()
{
static FP0 cf0;

long FractionalPart, auxl;
int c;

if ( Long < 0
){ SquareRootError (Long);
		 return -1.0;
} else { 	 if ( Long == 0
		 ){ cf0.Long = 0;
				  return cf0;
		 };
};

c = UGK::Zeros (Long);  //Total de Zeros tiene por la izquierda el parametro.

//Se normaliza la mantisa for poder acceder a la tabla de raices.

if ( c >= 19
){ cf0.Long = Roots [Long];
		 c         = 19;
} else {     auxl      = Long >> (19 - c);
		 if ( c <= 7
		 ){ FractionalPart   = ((Long << (12+c)) & 2147483647L) >> 19;
				  cf0.Long = Roots [auxl] +
							  ((((Roots [auxl+1] - Roots[auxl]) >> 6)* FractionalPart)
							  >> 6);
		 } else {     FractionalPart   = ((Long << (12+c)) & 2147483647L) >> (12 + c);
				  cf0.Long = Roots [auxl] +
							  ((((Roots [auxl+1] - Roots[auxl]) >> 6)* FractionalPart)
							  >> (13 - c));
		 };
};
return cf0 * R2 [c-1];
}


FP0 FP0::sqrt2           ()
{
static FP0 cf0;
long x;

if ( Long < 0
){ SquareRootError (Long);
		 return -1.0;
};

if ( Long & BIT18
){ x = Long >> DESP18;
		 x++;
} else {     x = Long >> DESP18;
};

cf0.Long  = Roots [x];
return cf0;
}

FP0 FP0::sqrt2il              ()
{

static FP0 cf0;
long FractionalPart, auxl;

if ( Long < 0
){ SquareRootError (Long);
		 return -1.0;
};

//Se normaliza la mantisa for poder acceder a la tabla de raices.

FractionalPart   = (Long >> 6) & 4095; // 2^12 - 1
auxl 	  = Long >> DESP18;
cf0.Long = Roots [auxl] +
		   ((((Roots [auxl+1] - Roots[auxl]) >> 6) * FractionalPart) >> 6);
return cf0;
}

bool FP0::operator >   (const FP0 a)
{
return Long > a.Long;
}

bool FP0::operator <   (const FP0 a)
{
return Long < a.Long;
}

bool FP0::operator >=  (const FP0 a)
{
return Long >= a.Long;
}

bool FP0::operator <=  (const FP0 a)
{
return Long <= a.Long;
}

bool FP0::operator ==  (const FP0 a)
{
return Long == a.Long;
}

bool FP0::operator !=  (const FP0 a)
{
return Long != a.Long;
}

/* Puesto que hacemos una rotacion a la izquierda de edx:eax, tenemos que
averiguar si tras hacer el desplazamiento en un bit, el MSb de eax es tal
que debamos incrementar/decrementar a edx. Ese bit es el numero 31 y su
Long en FractionalPart es el anterior. Comenzamos la numeracion de bits por 1
*/

FP0 FP0::operator * (FP0 a)
{
	long l;

	l = Long;
	__asm {
		mov  edx, a.Long
			mov  eax, l
			imul edx
			shld edx, eax, 1
			// En lugar de hacer truncamiento, redondeamos.
			test edx, -1
			jge  positivo
			/*
			El resultado es negativo. Si MSb de la palabra de menos peso es 0,
			al estar en C'2, dicha palabra tiene un Long absoluto > 0.5, y
			debemos incrementar el Long absoluto de la parte de mayor peso en
			una unidad. Como esta parte esta representada en Long negativo,
			restaremos 1.
			*/
			and eax, SIGN32b
			jz  decedx
			jmp seg1
	}
decedx:
	__asm dec edx
	__asm jmp seg1
positivo :
	// Al contrario que en el caso anterior, si el MSb es uno,
	// incrementaremos la parte de mayor peso en una unidad.
	__asm and eax, SIGN32b
	__asm jnz incedx
	__asm jmp seg1
incedx :
	__asm inc edx
seg1 :
	__asm {
		mov a.Long, edx
			inc edx    //Testeamos si los 4 MSB s¢lo contienen el signo negativo.
			jnz nocero
			mov a.Long, edx
	}
nocero:
	return a;
}

FP0 FP0::operator / (FP0 a)
{
	long aux;

	if (Long == a.Long
		){
		a.Long = ONEFP0;
	}
	else {
		aux = Long;
		__asm {
			mov edx, aux
				mov ebx, a.Long
				// Anulamos el acumulador
				xor eax, eax
				shrd eax, edx, 1
				sar edx, 1
				idiv ebx
				// Movemos el cociente al resultado
				mov a.Long, eax
		}
	};
	return  a;
}
