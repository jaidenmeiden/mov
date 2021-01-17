/*	Programa de prueba de la unidad de numeros en Coma Fija con 32 bits
	para representar la parte decimal y 0 para la entera. */

#include <iostream.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <cf0.h>

PROC contenido ( CF0 a)
PPIO
printf (" %15.10f \n", double (a));
FIN

PROC suma ( CF0 a, CF0 b)
PPIO
cout << double (a) << " + " << double (b) << " = " << double (a+b) << endl;
cout << "El valor de " << double (a) << " + " << double (b) << " es ";
a += b;
cout << double (a) << endl;
FIN

PROC resta ( CF0 a, CF0 b)
PPIO
cout << double (a) << " - " << double (b) << " = " << double (a-b) << endl;
cout << "El valor de " << double (a) << " - " << double (b) << " es ";
a -= b;
cout << double (a) << endl;
FIN

PROC niega (CF0 a)
PPIO
cout << "El valor de -" << double (a) << " es " << double (-a) << endl;
FIN

PROC compara ( CF0 a, CF0 b)
PPIO

SI  a < b
ENTONCES cout << double (a) << " es menor que " << double (b) << endl;
SINO	 cout << double (a) << " es mayor o igual que " << double (b) << endl;
FSI

SI  a <= b
ENTONCES cout << double (a) << " es menor o igual que " << double (b) << endl;
SINO	 cout << double (a) << " es mayor que " << double (b) << endl;
FSI

SI  a > b
ENTONCES cout << double (a) << " es mayor que " << double (b) << endl;
SINO	 cout << double (a) << " es menor o igual que " << double (b) << endl;
FSI

SI  a >= b
ENTONCES cout << double (a) << " es mayor o igual que " << double (b) << endl;
SINO	 cout << double (a) << " es menor que " << double (b) << endl;
FSI

SI  a == b
ENTONCES cout << double (a) << " es igual que " << double (b) << endl;
SINO	 cout << double (a) << " es distinto que " << double (b) << endl;
FSI

SI  a != b
ENTONCES cout << double (a) << " es distinto que " << double (b) << endl;
SINO	 cout << double (a) << " es igual que " << double (b) << endl;
FSI

cout << "Pulse una tecla para continuar." << endl;
getch();

FIN

CF0 multiplica (CF0 a, CF0 b)
PPIO
CF0 c;
c = a*b;
printf ("%1.11f * %1.11f = %1.11f \n", double (a), double (b), double (c));
DEVUELVE c;
FIN

CF0 divide (CF0 a, CF0 b)
PPIO
CF0 c;
c = a/b;
printf ("%1.11f / %1.11f = %1.11f \n", double (a), double (b), double (c));
DEVUELVE c;
FIN

PROC raiz_cuad (CF0 a)
PPIO
cout << "La raiz cuadrada de " << double (a) << " es " << sqrt (double (a))
	 << " " << double (a.sqrt2()) << endl;
FIN

PROC raizil (CF0 a)
PPIO
cout << "La raiz cuadrada de " << double (a) << " es " << sqrt (double (a))
	 << " " << double (a.sqrt2il()) << endl;
FIN

PROG_PPAL
CF0 a (0.789123),
	b (0.345),
	d (0.93440),
	c (0.89052345678);


cout << "La diferencia entre 0.89052345678 y c es "
	 << 0.89052345678 - double (c) << endl;
printf ("%1.11f * %1.11f = %1.11f \n", double (c), double (c), double (c*c));

inicializa_raices ();
inicializa_raices ();
inicializa_raices ();

suma  (0.23, -.998);
resta (.999, .999999);

a = multiplica (d,d);
c = divide (a,d);

compara (a, b);

a = multiplica (b,b);
c = multiplica (a,b);
a = multiplica (c,b);
c = multiplica (a,b);
a = multiplica (c,b);
c = divide (a,b);
a = divide (c,b);
c = divide (a,b);
a = divide (c,b);

getch();

a = divide (0.12345,0.34567);
a = divide (0.12345,-0.34567);
a = divide (-0.12345,0.34567);
c = divide (0.23456789,0.78901234);
c = divide (-0.23456789,0.78901234);
c = divide (-0.23456789,-0.78901234);
a = divide (c,b);

niega (a);
niega (b);
niega (c);
niega (d);

raiz_cuad (0.1243321123);
raiz_cuad (.999999);
raiz_cuad (0.1234567898);
raiz_cuad (0.987654321);
raiz_cuad (0.000111222333);
raiz_cuad (0.001122334455);
raiz_cuad (0.123123123);

raizil (0.1243321123);
raizil (.999999);
raizil (0.1234567898);
raizil (0.987654321);
raizil (0.000111222333);
raizil (0.001122334455);
raizil (0.123123123);

contenido (.23456789123);
contenido (.834567890123);
contenido (-.23);
contenido (-.82345678901);

compara (.54321, .5432);
compara (-.54321, .5432);
compara (.5421, .5421);
compara (-.54321, -.5432);

getch();

suma (.467890, .4321);
suma (-.67890, .4321);
suma (.267890, -.4321);
resta (.67890, .4321);
resta (-.67890, .4321);
resta (.67890, -.4321);
resta (-.167890, -.4321);

suma (.678999991, .321);
suma (-.67890, .6789);
suma (.67890, .2190875);
resta (.67890, .4321);
resta (.43210, .4321);
resta (.167890, -.4321);
resta (-.67890, -.14321);

FIN_PROG_PPAL