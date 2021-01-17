/* UNIDAD DE TRATAMIENTO DE NUMEROS ALEATORIOS EN FORMATO COMA FIJA 32 BITS
				DESARROLLADO POR RAMON P. MOLLA VAYA.
					VALENCIA. DICIEMBRE DE 1992 (c)


	Unidad de implementacion de la clase CRandom.
	Representacion en coma fija de 32 bits. 32 for la parte FractionalPart y
	0 for la IntegerPart, es decir FP0. Utiliza notacion en C'2, por lo que
	un bit se destina a	bit de signo, y los otros 31 a la mantisa. */

/*************************************************************************/
/*                                                                       */
/*         Cabecera del generador de distribuciones eleatorias           */
/*                            Fichero "aleacf0.cpp"                      */
/*                                                                       */
/*************************************************************************/

//#include <conio.h>
#include <math.h>
#include <iostream>
#include <UGKFP0Random.h>
#include <UGKutilities.h>

#define UNIDAD 		ONEFP1R
#define MAXIMO_CF     127.0

void CRandom::error (const tipo_error e)
{

static char *error_msg[] =
{
	 "Rango maximo de la variable aleatoria ha sido rebasado.",
	 "CORRIENTE debe pertenecer a [0,15].",
	 "seed debe pertenecer a [0,15].  ",
	 "a>b en funcion UNIFORME.           ",
	 "s>x en funcion ERLANG.             ",
	 "s<=x en funcion HIPEREXP.          ",
	 "Tipo de error no valido.           "
};

std::cout << " ERROR CRandom : " << error_msg[e] << "\n";
}

// OPERADORES DE CREACION

CRandom::CRandom   				(const double r)
{
if ( UGK::absd (r) > UNIDAD
){ error (RANGOEXC);
} else {     seed = r*UNIDAD;
};
}

CRandom::CRandom 				()
{
seed = 1L;
}

CRandom::CRandom 				(const long l)
{
seed = l;
}

/*-------------------SELECCIONA LA CORRIENTE DEL GENERADOR----------------*/

void CRandom::select_seed (const int c)
{

#define TOTAL_SEEDS 16

// semillas for las corrientes 0 a 15

static long corrientes [TOTAL_SEEDS] =
{
0L,
1973272912L,  747177549L,   20464843L,  640830765L, 1098742207L,
  78126602L,   84743774L,  831312807L,  124667236L, 1172177002L,
1124933064L, 1223960546L, 1878892440L, 1449793615L,  553303732L
};

/* Selecciona y asigna una seed entre 1<=n<=15 a la variable aleatoria
   correspondiente, y devuelve la que ha sido seleccionada. */

if ( (c<0) || (c>=TOTAL_SEEDS)
){ error (CORRIENTE);
} else { 	 seed = corrientes [c];
};
}

/*---------------INSTALA UNA NUEVA seed EN UNA CORRIENTE---------------*/

void CRandom::install_seed (const FP0 s)
{
// instala una nueva seed.
seed = s.Long;
}

/*---------------GENERADOR DE NUMEROS ALEATORIOS.-------------------------*/
FP0 CRandom::alea ()
{
	#define A 	   16807L      /*multiplier (7**5) for 'ranf' */
	#define M 2147483647L      /*modulus (2**31-1) for 'ranf' */
	static  FP0 cf01;
	short *p,*q,k;
	long Hi,Lo;

   /* generate product using double precision simulation (comments   */
   /* refer to In`s lower 16-bits as "L", its upper 16 bits as "H")  */
   p=(short *)&seed; Hi=*(p+1)*A;    /* 16807*H->Hi */
   *(p+1)=0; Lo=seed*A;              /* 16807*L->Lo */
   p=(short *)&Lo; Hi+=*(p+1);  		/* add high-order bits of Lo to Hi  */
   q=(short *)&Hi;              		/* low order bits of Hi-> LO */
   *(p+1)=*q&0X7FFF;            		/* clear sign bit    */
   k=*(q+1)<<1; if (*q&0X8000) k++;     /* Hi bits 31-45->k  */
   /* form Z + K [-M] (where Z=Lo) : presubtract M to avoid overflow */
   Lo-=M; Lo+=k; if (Lo<0) Lo+=M;
   cf01.Long = seed = Lo;

   return cf01;
  }


/*------------GENERADOR DE VARIABLES ALEATORIAS ENTRE A y B---------------*/

FP0 CRandom::uniforme (FP0 a, FP0 b)
{
// 'uniforme'devuelve una variable pseudo-aleatoria de distribuci¢n
// uniforme entre dos fronteras: inferior "a", y superior "b"                 */

if ( a>b
){ error (UNIFORME);
};
return a + (b-a)*alea();
}

/*-------GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION exponential-------*/

FP1 CRandom::exponential (FP0 x)
{
// 'exponential' devuelve una variable pseudo-aleatoria de distribuci¢n
// exponential negativa de media x. El formato minimo ha de ser FP1.
return -FP1(alea()).lnil() * x;
}

/*----------GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION ERLANG---------*/

FP1 CRandom::erlang (FP0 x, FP0 s)
{
// 'erlang'devuelve una variable pseudo-aleatoria de distribuci¢n
// Erlang con una media "x" y una desviaci¢n standard "s".
// El formato minimo ha de ser FP1.

int i,k;
static FP0 cf02, cf03;

if ( s>x
){ error (ERLANG);
		 return -1.0;
} else { cf03 = s / x;
	 cf03 = cf03 * cf03;
	 k    = 1.0 / double (cf03);
	 cf02 = 1.0;

	 for ( i=0 ; i<k ; i++
	 ){ cf02 = cf02 * alea();
	 }

	 return -double (FP1(cf02).lnil() * x) / k;
};
}

/*----GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION HIPEREXPONENCIAL----*/

double CRandom::hiperexp (FP0 x, FP0 s)
{
// 'hiperexp' devuelve una variable pseudo-aleatoria basada en la distribuci¢n
//  hiperexponencial de dos etapas de Morse de media "x" y desvici¢n standard
//  s, siendo s>x. El formato minimo ha de ser FP1.

FP0 cf02, cf03;
FP1 cf1;

cf03 = 1.0;

if ( s<=x
){ error (HIPEREXP);
		 return -1.0;
} else { cf02 = x / s;
	 cf02 = cf02 * cf02;

	 cf02 = FP1 (cf03 - cf02) / (FP1(cf03) + FP1(cf02));	// p=0.5*(1.0-sqrt((z-1.0)/(z+1.0)));
	 cf02 = cf03 - cf02.sqrtil();
	 cf02.Long = cf02.Long >> 1;		//Se divide por 2

	 if ( alea () > cf02
	 ){ cf02 = cf03 - cf02;
	 };

	 cf1 		 = FP1(alea()).lnil() * x;
	 cf1.Long 	 = cf1.Long >> 1;

	 return - double (cf1) / double (cf02);
};
}

/*----------GENERADOR DE VARIBLE ALEATORIA DE DISTRIBUCION NORMAL--------*/

FP1 CRandom::normal(FP0 x, FP0 s)
{
// 'normal' devuelve una variable pseudo-aleatoria de distribuci¢n
// normal y de media "x" y desviaci¢n standard "s".

double	 auxr;
static FP1 z1, z2 = 0, cf01;
FP0 cf02, cf03, cf04;

if ( z2.Long != 0L)
{
	z1   = z2;
	z2   = 0;   /* En la proxima llamada, se utilizara el Long actual */
} 
else
{
	do {
		cf02 = alea();
		cf02.Long -= ZERO5FP0;
		cf03 = alea();
		cf03.Long -= ZERO5FP0;
		cf04 = cf02 * cf02 + cf03 * cf03;
	} while ( cf04.Long >= ZERO25FP0);

		 cf04.Long = cf04.Long << 1;	//Se multiplica por 2.
		 cf01.Long = cf04.Long << 1;
		 auxr	   = sqrt (-double (FP1 (cf01).lnil()) / double (cf04));

		 if ( auxr > MAXIMO_CF)
				z1 = MAXIMO_CF;
		 else   z1 = auxr;

		 cf03.Long = cf03.Long << 1;
		 cf02.Long = cf02.Long << 1;
		 z2 = z1 * cf03;
		 z1 = z1 * cf02;
};
return FP1 (x) + z1*s;
}

/*		ACHTUNG!!!!!!!!!!!!!!!!!!!!!!

	LA DISTRIBUCION NORMAL TIENE SIEMPRE QUE REALIZARSE CON FORMATOS FP1 ||
	SUPERIOR.

	DADO QUE LAS OPERACIONES ARITMETICAS SIEMPRE PRESENTAN EL FORMATO
	CFx * CFy DONDE x > y, ESTA IMPLEMENTACION SOLO PUEDE TRABAJAR CON
	FORMATOS CFn / n<=1. SOLUCION, IMPLEMENTAR LAS FUNCIONES QUE PERMITAN
	OTRO ORDEN DE PARAMETROS, || REALIZAR OTRA IMPLEMENTACION DONDE EL RESULTADO
	DE LOS LOGARITMOS (FP1) ){ PUESTO EN LA PARTE DERECHA. DE ESTA FORMA,
	SIEMPRE SE PODRA UTILIZAR ESTA IMPLEMENTACION PARA CUALQUIER typedef DE
	FORMATO CFn / n >= 1.
*/