/*  Programa de prueba de la unidad de numeros en Coma Fija con 32 bits para
	representar la parte decimal y 0 para la entera.
*/

#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <UGKFP3.h>

CF0 y;
CF3 x;

PROC contenido ( CF3 a)
PPIO
printf (" %15.10f \n", double (a));
FIN

PROC suma ( CF3 a, CF3 b)
PPIO
cout << double (a) << " + " << double (b) << " = " << double (a+b) << endl;
cout << "El valor de " << double (a) << " + " << double (b) << " es ";
a += b;
cout << double (a) << endl;
FIN

PROC resta ( CF3 a, CF3 b)
PPIO
cout << double (a) << " - " << double (b) << " = " << double (a-b) << endl;
cout << "El valor de " << double (a) << " - " << double (b) << " es ";
a -= b;
cout << double (a) << endl;
FIN

PROC niega (CF3 a)
PPIO
cout << "El valor de -" << double (a) << " es " << double (-a) << endl;
FIN

PROC compara ( CF3 a, CF3 b)
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

PROC raices (CF3 f)
PPIO
cout << "Raiz (" << double(f) << ") = " << sqrt (double (f))    << " "
										<< double (f.sqrt())    << " "
										<< double (f.sqrtil())  << " "
										<< double (f.sqrt2())   << " "
										<< double (f.sqrt2il()) << endl;
FIN

PROC resultexp (CF3 v)
PPIO

cout << "exp (" << double (v) << ") = "
	 << exp (double(v)) 	<< " : "
	 << double (v.expasm()) << " : "
	 << double (v.exp   ()) << " : " << endl;
FIN

PROC resultln (CF3 v)
PPIO

cout << "ln (" << double (v) << ") = " << log (double(v)) << " : "
     << double(v.ln ()) << " : "  << double (v.lnil ()) << endl;
FIN


PROC resultseno (CF3 v)
PPIO

cout << "sen (" << double (v) << ") = " << sin (double(v)) << " : ";
cout << double (v.senoasm ()) << " : ";
cout << double (v.seno ()) << " : ";
cout << double (v.senoil ()) << endl;
FIN

CF0 divide (CF3 a, CF3 b)
PPIO
y = a/b;
printf ("%3.9f / %3.9f = %3.9f \n",double (a), double (b), double(y));
DEVUELVE y;
FIN

CF3 multiplica (CF3 a, CF3 b)
PPIO
x = a*b;
printf ("%3.9f * %3.9f = %3.9f \n",double (a), double (b), double(x));
DEVUELVE x;
FIN

PROG_PPAL
CF0 a (-0.345);
CF3 b (a),
	c (-12300.45678),
	d (1000000,345),
	e ;

cout << " || " << double(a) << " || " << double(b) << " || " << double(c)
	 <<	" || " << double(d) << " || " << double(e) << "\n";

contenido (a);
niega (b);
suma (b, a);
compara (a, b);
compara (a, c);
resta (b, c);

multiplica(b,c);
multiplica(CF3(a),c);
multiplica(c, b);
multiplica(e, b);
multiplica(c, b);
multiplica(e, b);
multiplica(c, b);
multiplica(CF3(a), b);
divide (200000.12345, 200221.12547);
divide (1000100.12345, -8000000.34567);
divide (-1022123.45, -8023345.67);
divide (2345678.9, 7890123.4);
divide (-0.23456789, 10.78901234);
divide (-1234560.23456789, -2345678.78901234);
divide (11111111.1111, 10000);

inicializa_senos ();
inicializa_logaritmos();
inicializa_exponenciales();

resultln (0.32);
resultln (123100.85);
resultln (100.78);
resultln (1112345.678);
resultln (2067.01234);
resultln (8000000.12345678);
resultln (6.00002345678);

getch();

resultseno (500.0);
resultseno (-16700.85);
resultseno (28.78);
resultseno (-11000.12345678);
resultseno (20124.5678);
resultseno (-300.512345678);
resultseno (169.02345678);

getch();

resultexp (-3.995);
resultexp (10.85);
resultexp (0.78);
resultexp (-2.123456);
resultexp (2.0123456);
resultexp (-0.001234);
resultexp (9.00002345);
resultexp (-.0023456);

getch();

inicializa_raices ();

raices (0.2345678901);
raices (0.6723);
raices (0.9888723);
raices (0.111123);
raices (0.00003223);

raices (120.2345678901);
raices (34.6723);
raices (50.9888723);
raices (11.111123);
raices (5.00003223);

raices (30120.2345678901);
raices (3456.6723);
raices (508.9888723);
raices (111.111123);
raices (5.00003223);

getch();

contenido (1234523.456789123);
contenido (234583.4567890123);
contenido (-234.23);
contenido (-32.82345678901);

niega (1234514.23456789123);
niega (2345143.834567890123);
niega (-234.23);
niega (-32.82345678901);

compara (.54321, .5432);
compara (-123.54321, .5432);
compara (2134.5421, 2134.5421);
compara (-2345.54321, -2343.5432);

getch();

suma (232345.467890, 2345354.4321);
suma (-43.67890, 1343245.4321);
suma (567.267890, -434356.4321);
resta (5.67890, 4325326.4321);
resta (-8455234.67890, 678.4321);
resta (.67890, -78.4321);
resta (-.167890, -7894.4321);

suma (.678999991, .321);
suma (-2435.67890, .6789);
suma (245.67890, .2190875);
resta (.67890, .4321);
resta (.43210, 798.4321);
resta (2346435.167890, -6780.4321);
resta (-.67890, -425.14321);

FIN_PROG_PPAL