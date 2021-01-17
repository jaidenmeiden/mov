/**	Fixed Point Arithmetic based on 32 bits integer numbers
*	Class Basic definitions.

*	Prefix: UGKFP_

*	@author Ramon Molla
*	@modified 
*	@version 2014-11
*/

#ifndef UGKFP_DEF
#define UGKFP_DEF

#include <UGK.h>
#include <atlstr.h>
#include <iostream>
#include <string>

//#define UGKFP_ASM

//There are four kinds of fixed point formats in this implementation
enum {
	UGKFP_FP0,
	UGKFP_FP1,
	UGKFP_FP2,
	UGKFP_FP3,
	UGKFP_MAX_FP
};

#define ALL_ONES		4294967295L

// One unit definition value depending on the fixed point formato selected
#define ONEFP0	BIT31
#define ONEFP1	BIT24
#define ONEFP2  BIT16
#define ONEFP3	BIT8

// One unit definition value depending on the fixed point formato selected in floating point format
#define ONEFP0R   2147483648.0
#define ONEFP1R     16777216.0
#define ONEFP2R        65536.0
#define ONEFP3R          256.0

// Max value that can be registered is when all bits are set to one except the sign one
#define MAX_VALUE	2147483647L

// One unit definition value depending on the fixed point formato selected in floating point format
#define MAX_FP0R		  0.999999940395355224609375
#define MAX_FP1R		127.99609375
#define MAX_FP2R      65535.999847412109375
#define MAX_FP3R   16777215.99609375

//FP0 predefined values
#define	INVONEFP0R 4.656612875E-10  //Inverse of ONEFP0R. For more efficiency. In doube precision format
#define	INVONEFP0f 4.656612875E-10f //Inverse of ONEFP0R. For more efficiency. In float format

#define ZERO25FP0 	 BIT29 		//Bit numero 29 a uno.
#define ZERO5FP0 	 BIT30 		//Bit numero 30 a uno. Es el trigesimo primero. El trigésimo segundo es el de signo

//FP1 predefined values

#define INC_ANG 2.44140625E-4

#define HALFPI_FP1  26353589L	/* 1.570796327 (PI_FP1/2)	in Fixed Point 1 */
#define PI_FP1      52707178L   /* 3.141592654 (PI_FP1)		in Fixed Point 1 */
#define TQPI_FP1	79060768L   /* 4.71238848  (3PI/2)		in Fixed Point 1 */
#define TWOPI_FP1  105414357L   /* 6.283185307 (2PI)		in Fixed Point 1 */

#define DESP18              18

#define SIGN32b 	2147483648L
#define FPDISPLACE			 8

#define C27_FP1		2130706432L

//FP2 predefined values

#define ZERO5FP2 	32768L 		//Bit numero 15 a uno.
#define TWOFP2 		BIT18	 	//Bit numero 17 a uno.
#define TWOPIFP2    411775L     //6.283185307 (2PI) en Fixed Point 2

#define POS_PTO_DEC	16

#define DEC_POINT_POSFP1      24
#define DEC_POINT_POSFP3       8

//Critical predefined bits 
#define BIT7		 128
#define BIT8		 256
#define BIT11       1024
#define BIT12       2048
#define BIT15 	   32768
#define BIT16	   65536L
#define BIT18     131072L
#define BIT23    8388608L
#define BIT24	16777216L
#define BIT29  536870912L
#define BIT30 1073741824L
#define BIT31 2147483648L
#define BIT31 2147483648L

#define DISPLACE_FP0_FP3	  23
#define DISPLACE_FP1_FP3	  16
#define DISPLACE_FP2_FP3	   8

//The amount of bytes used to support a FP number
#define UGKFP_BYTES 4
#define UGKFP_SHORT_INTS 2

//Where is the low part and the high part of a FP number
#define UGKFP_LO	0
#define UGKFP_HI	1

//Where is the low BYTE and the high BYTE plus the sign bit of a FP number split into 4 bytes
#define UGKFP_LOB	0
#define UGKFP_HIB	3

typedef enum
{
	UGKFPA_RROFPE,	//Fixed Point ERROR generic header
	UGKFPA_RROFP0,	//Representation Range Overpassed when using FP0 format.
	UGKFPA_RROFP1,	//Representation Range Overpassed when using FP1 format.
	UGKFPA_RROFP2,	//Representation Range Overpassed when using FP2 format.
	UGKFPA_RROFP3,	//Representation Range Overpassed when using FP3 format.
	UGKFPA_RROFP,	//Representation Range Overpassed when using FP0 format.
	UGKFPA_SRE,		//Square Root Error found
	UGKFPA_ERREND,  //Error No Definido.
	UGKFPA_MAX_ERR
} UGKFPA_ErrorType;

extern CString ERROR_MSG[UGKFPA_MAX_ERR];

inline void Error(const UGKFPA_ErrorType e) { std::cout << std::endl << ERROR_MSG[UGKFPA_RROFPE] << ERROR_MSG[e] << std::endl; }
inline void SquareRootError(const long Long){ char Aux[64];  _itoa(Long, Aux, 10);  std::cout << ERROR_MSG[UGKFPA_SRE] << Aux << std::endl; }

#endif
