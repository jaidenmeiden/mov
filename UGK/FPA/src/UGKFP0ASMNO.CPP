/* UNIDAD DE TRATAMIENTO DE NUMEROS EN FORMATO COMA FIJA 32 BITS
			DESARROLLADO POR RAMON P. MOLLA VAYA.
				VALENCIA. DICIEMBRE DE 1992 (c)

  Unidad de descripcion de la clase COMA FIJA 0.
  Representacion en coma fija de 32 bits. 32 for la parte FractionalPart y
  0 for la IntegerPart. Utiliza notacion en C'2, por lo que un bit se destina a
  bit de signo, y los otros 31 a la mantisa.

 ­­­­­­­­­­­­­­­   ACHTUNG !!!!!!!!!!!!!!!!!!!!!!!!!!!
 Esta versi¢n debe ser compilada por separado desde linea de comandos del DOS
 Adem s, debe estar compilada con el mismo modelo de memoria que el resto de
 la aplicaci¢n usando el comando : bcc -ml -c cf0asm.cpp
*/

/*	ATENCION: Este modulo ha diso desarrollado for que la aplicacion pueda
seguir compilandose cuando no se disponga de ensamblador for generar el codigo
maquina.
Por lo tanto, las funciones producto y division existiran pero seran nulas.
*/

#pragma inline
#include <UGKFP0.h>

#define SIGN32b	1073741824L
/* Puesto que hacemos una rotacion a la izquierda de edx:eax, tenemos que
	averiguar si tras hacer el desplazamiento en un bit, el MSb de eax es tal
	que debamos incrementar/decrementar a edx. Ese bit es el numero 31 y su
	Long en FractionalPart es el anterior. Comenzamos la numeracion de bits por 1
*/
/*
FP0 FP0::operator * (FP0 a)
{
return a;
}

FP0 FP0::operator / (FP0 a)
{
return  a;
}
*/