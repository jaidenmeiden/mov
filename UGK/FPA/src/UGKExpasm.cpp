#include <iostream>

#define ONEFP1 16777216

//Este procedimiento calcula siempre la funcion exponential entre [0, 1].

// easm : FP0 -> FP1

long easm (long x)
{

/*En "edi" se guarda el total acumulado tras la primera iteraci¢n, es decir, x . Usa FP1*/

	__asm mov edi, ONEFP1

/*En "esi" se guarda siempre el Long del sumando obtenido en la iteraci¢n anterior
X^j / j! siendo en la primera iteraci¢n j=1.*/

	__asm mov esi, x

// En "ebx" se almacena el Long de "x".

	__asm mov ebx, esi

/*En "ecx" se almacena el indice por el que se dividir a cada termino en formato FP1. */
	__asm mov ecx, edi

// Se obtiene el segundo sumando, es decir, 1 + x

	__asm mov eax, esi
	__asm sar eax, 7
	__asm add edi, eax

/*Seguidamente se pasa a calcular el resto de las iteraciones.*/

seguir:

/*Para obtener el nuevo sumando, se debe multiplicar el anterior termino por
 x (ebx) y dividirlo por j (ecx) */

	__asm mov eax, esi
	__asm imul ebx

 //El resultado que esta representado en FP0 se convierte al formato FP1.

	__asm shrd eax, edx, 7
	__asm sar edx, 7

// Se incrementa el indice en una unidad en formato FP1.

	__asm add ecx, ONEFP1

/*Se divide por j. Ahora bien, se ha de tener en cuenta que "ecx" est  representado en FP1
de 32 bits. Por ello, el resultado quedara en formato FP0, al dividir un numero en formato
FP1 por otro n£mero en FP1. */

	__asm idiv ecx

/*Se guarda el resultado del sumando actual en "esi" en formato FP0. */

	__asm mov esi, eax

/* El resultado que genera el algoritmo, est  en formato FP0, los resultados parciales se
guardan en FP1, ya que ‚stos pueden tener oscilaciones entre [0.. e]. Por lo tanto, se
debe convertir de FP0 a FP1, y sumar despues. */

	__asm sar eax, 7

	__asm test eax, -1
	__asm jz fin
/*Ahora se suma el resultado obtenido al total acumulado. */

	__asm add edi, eax
	__asm jmp seguir

fin:
	__asm mov x, edi

return x;
}
