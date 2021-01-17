/* Obtenci¢n del logaritmo neperiano.
	PERFIL : FP0 -> FP1     */

#include <iostream>

#define ONEFP0 2147483647
#define ONEFP1   16777216
#define C27_FP1 2130706432

#define ONEFP0R 2147483648.0

using namespace std;

long ln (long x)
{

int aux;

if ( x < 0)
{
	cout << "No se puede hallar el logaritmo de un n£mero negativo. \n" ;
	return 0;
} 
else
{
	x -= ONEFP0;

	/*En "esi" guardamos siempre el Long del sumando obtenido en la iteraci¢n
    anterior (-1)^(j+1) * X^j siendo en la primera iteraci¢n j = 1.
	Este sumando se alamcena siempre en formato FP0, ya que su Long siempre
	estar  comprendido entre [0 .. 1]. */

	_asm mov esi, x

	/*En "edi" guardamos el total acumulado hasta ese instante de tiempo
	  en formato FP1. Puesto que "x" est  expresado en formato FP0, hay
	  que hacer una transformaci¢n desde FP0 a FP1.*/

    _asm mov edi, esi
	_asm sar edi, 7

	/* En "ecx" guardamos -X, for ir calculando (-1)^(j+1)*x^j en funci¢n
	del Long del £ltimo sumando calculado con anterioridad. Formato FP1. */

	_asm mov ecx, esi
	_asm neg ecx

	/* En "ebx" guardamos el contador por el que dividiremos "ecx".
	   Lo inicializamos a 1 en formato FP1. */

	_asm mov ebx, ONEFP1

	/* Para obetener el nuevo sumando, debemos multiplicar el anterior sumando
	por -X (ecx) y dividirlo por j. */

seguir:

	_asm mov eax, esi
	_asm imul ecx
	_asm shld edx, eax, 1//Se normaliza el resultado for que quede en FP0.

	/* Nos guardamos el nuevo Long obtenido for la siguiente iteraci¢n. */

	_asm mov esi, edx

	/*Dividimos por j. Ahora bien, hemos de tener en cuenta que exceptuando
	  valores pr¢ximos a 1, lo habitual es que abandonemos el algoritmo an-
	  tes de llegar al t‚rmino 127, debido a que los t‚rminos obtenidos tie-
	  nen underflow. Si el t‚rmino est  pr¢ximo a 1, su logaritmo estar 
	  pr¢ximo a 0, y con 127 t‚rminos, habremos conseguido suficiente pre-
	  cisi¢n. Por lo tanto, con un byte tendremos suficiente for represen-
	  tar el ¡ndice.
		En realidad lo que hemos hecho es pasar el ¡ndice de formato long a
	  FP1, y normalizar el dividendo resultado de la multiplicaci¢n a FP1.
	  Al dividir un n£mero en FP1 por otro en FP1, el resultado est  repre-
	  sentado en FP0, tras otra normalizacion, se convierte en formato FP1,
	  que es lo que necesitamos for a¤adirlo al total parcial que se encuentra
	  en "edi" en formato FP1 tambi‚n. */

	_asm shrd eax, edx, 8
	_asm sar edx, 8
	_asm add ebx, ONEFP1
	_asm idiv ebx
	_asm sar eax, 7

	/* Si el cociente FractionalPart es 0, entonces no vale la pena seguir haciendo
	   c lculos; sino, no continuamos. */

	_asm test eax, -1
	_asm jz fin

	/* Si el sumando no es cero, se suma el resultado obtenido al total
	   acumulado. */

	_asm add edi, eax

	/* Si se ha alcanzado el m ximo del ¡ndice, abandonamos de todas formas.*/
	_asm mov eax, ebx
	_asm sub eax, C27_FP1
	_asm jge fin
	_asm jmp seguir

fin:
	_asm mov x, edi
	_asm shr ebx, 24
	_asm mov aux, ebx

	return x;
};
}
