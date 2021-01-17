/*	Programa de prueba de la unidad de numeros en Coma Fija con 32 bits para
	representar la parte decimal y 0 para la entera. */

#include <iostream.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <cf2.h>

CF0 y;
CF2 x;

PROC contenido ( CF2 a)
PPIO
printf (" %15.10f \n", double (a));
FIN

PROC suma ( CF2 a, CF2 b)
PPIO
cout << double (a) << " + " << double (b) << " = " << double (a+b) << endl;
cout << "El valor de " << double (a) << " + " << double (b) << " es ";
a += b;
cout << double (a) << endl;
FIN

PROC resta ( CF2 a, CF2 b)
PPIO
cout << double (a) << " - " << double (b) << " = " << double (a-b) << endl;
cout << "El valor de " << double (a) << " - " << double (b) << " es ";
a -= b;
cout << double (a) << endl;
FIN

PROC niega (CF2 a)
PPIO
cout << "El valor de -" << double (a) << " es " << double (-a) << endl;
FIN

PROC compara ( CF2 a, CF2 b)
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

PROC raices (CF2 f)
PPIO
cout << "Raiz (" << double(f) << ") = " << sqrt (double (f))    << " "
										<< double (f.sqrt())    << " "
										<< double (f.sqrtil())  << " "
										<< double (f.sqrt2())   << " "
										<< double (f.sqrt2il()) << endl;
FIN

PROC resultexp (CF2 v)
PPIO

cout << "exp (" << double (v) << ") = " << exp (double(v)) << " : "
	 << double (v.expasm()) << " : "
	 << double (v.exp   ()) << " : "
	 << double (v.expil ()) << endl;
FIN

PROC resultln (CF2 v)
PPIO

cout << "ln (" << double (v) << ") = " << log (double(v)) << " : "
	 << double(v.ln ()) << " : "  << double (v.lnil ()) << endl;
FIN


PROC resultseno (CF2 v)
PPIO

cout << "sen (" << double (v) << ") = " << sin (double(v)) << " : ";
cout << double (v.senoasm ()) << " : ";
cout << double (v.seno ()) << " : ";
cout << double (v.senoil ()) << endl;
FIN

CF0 divide (CF2 a, CF2 b)
PPIO
y = a/b;
printf ("%3.9f / %3.9f = %3.9f \n",double (a), double (b), double(y));
DEVUELVE y;
FIN

CF2 multiplica (CF2 a, CF2 b)
PPIO
x = a*b;
printf ("%3.9f * %3.9f = %3.9f \n",double (a), double (b), double(x));
DEVUELVE x;
FIN

PROG_PPAL
CF0 a (-0.345);
CF2 b (a),
	c (-12300.45678),
	d (1000.000345),
	e ;

inicializa_raices();
inicializa_senos ();
inicializa_logaritmos();
inicializa_exponenciales();

cout << " " << double(a) << " " << double(b) << " " << double(c) << " "
	 << double(d) << " " << double(e) << "\n";

e = CF2(a);
cout << "Valor de " << double(a) << " es " << double(e) << "\n";

e = -b;
cout << "El valor de - " << double(b) << " es " << double(e) << "\n";

e = b + CF2(a);
cout << double(b) << " + " << double(a) << " = " << double(e) << "\n";

SI CF2(a) < c
ENTONCES cout << double(a) << " es menor que " << double(c) << "\n";
SINO     cout << double(a) << " es mayor que " << double(c) << "\n";
FSI

cout << double(b) << " - " << double(c) <<" = " << double(b-c)
	 << "\nAhora comenzamos por los productos y divisiones.\n";

multiplica (b,c);
divide 	   (CF2(a),c);

SI CF2(a) == b
ENTONCES cout << double(a) << " es igual que "    << double(b) << "\n";
SINO	 cout << double(a) << " no es igual que " << double(b) << "\n";
FSI

multiplica(c, b);
multiplica(e, b);
multiplica(c, b);
multiplica(e, b);
multiplica(c, b);

divide (20.12345, 20.12547);
divide (0.12345,-10.34567);
divide (-0.012345,-10.34567);
divide (0.23456789, 10.78901234);
divide (-0.23456789,10.78901234);
divide (-0.23456789, -100.78901234);

cout << "Comenzamos la simulacion." << endl;

resultln (0.32);
resultln (12310.85);
resultln (10.78);
resultln (110.12345678);
resultln (2067.012345678);
resultln (30000.0012345678);
resultln (6.00002345678);

getch();

resultseno (500.0);
resultseno (-100.85);
resultseno (28.78);
resultseno (-1100.12345678);
resultseno (21.012345678);
resultseno (-30.0012345678);
resultseno (69.00002345678);
resultexp (-5.995);
resultexp (.85);
resultexp (0.78);
resultexp (-8.123456);
resultexp (2.0123456);
resultexp (-0.001234);
resultexp (9.00002345);
resultexp (-.0023456);

getch();

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

contenido (12345.23456789123);
contenido (2345.834567890123);
contenido (-234.23);
contenido (-32.82345678901);

niega (12345.23456789123);
niega (2345.834567890123);
niega (-234.23);
niega (-32.82345678901);

compara (.54321, .5432);
compara (-123.54321, .5432);
compara (2134.5421, 2134.5421);
compara (-.54321, -.5432);

getch();

suma (23.467890, 354.4321);
suma (-43.67890, 3245.4321);
suma (567.267890, -4356.4321);
resta (5.67890, 4325.4321);
resta (-234.67890, 678.4321);
resta (.67890, -78.4321);
resta (-.167890, -7894.4321);

suma (.678999991, .321);
suma (-2435.67890, .6789);
suma (245.67890, .2190875);
resta (.67890, .4321);
resta (.43210, 798.4321);
resta (.167890, -6780.4321);
resta (-.67890, -.14321);

FIN_PROG_PPAL