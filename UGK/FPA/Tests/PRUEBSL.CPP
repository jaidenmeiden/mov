// Programa de prueba de la clase SUPER LARGO.

#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <sl.h>

PROC contenido ( SL a)
PPIO
printf (" %15.10f \n", double (a));
FIN

PROC suma ( SL a, SL b)
PPIO
cout << double (a) << " + " << double (b) << " = " << double (a+b) << endl;
FIN

PROC resta ( SL a, SL b)
PPIO
cout << double (a) << " - " << double (b) << " = " << double (a-b) << endl;
FIN

PROC niega (SL a)
PPIO
cout << "El valor de -" << double (a) << " es " << double (-a) << endl;
FIN

PROC incdec ( SL a)
PPIO
a++;
cout << "++a = " << double (a) << " --a = ";
--a;
cout << double (a) << endl;

a += 1;
cout << "++a = " << double (a) << " --a = ";
a -= 1;
cout << double (a) << endl;
FIN

PROC despizq ( SL a)
PPIO
cout << double (a) << " << 24 = " << double (a << 24) << endl;
FIN

PROC despder (SL a)
PPIO
cout << double (a) << " >> 24 = " << double (a >> 24) << endl;
FIN

PROC compara ( SL a, SL b)
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

PROG_PPAL
contenido (1234567890.23456789123);
contenido (1987654321.834567890123);
contenido (-1234567.23);
contenido (-987654321.82345678901);

compara (12345.54321, 12345.5432);
compara (-12345.54321, 12345.5432);
compara (12345.54321, 12345.54321);
compara (9812345.54321, 987612345.5432);

incdec (-.23456);
incdec (.23456);
incdec (23424.2345876);
incdec (354624.267583456);
incdec (457824.56723456);

getch();

despizq (1111.2222);
despizq (1234.5678);
despizq (2222.1111);
despder (1111.2222);
despder (1234.5678);
despder (2222.1111);

suma (12345.67890, 98765.4321);
suma (-12345.67890, 98765.4321);
suma (12345.67890, -98765.4321);
resta (12345.67890, 98765.4321);
resta (-12345.67890, 98765.4321);
resta (12345.67890, -98765.4321);
resta (-12345.67890, -98765.4321);

suma (1.678999991, 98765.4321);
suma (-12345.67890, 12345.6789);
suma (1200000345.67890, 98990765.4321);
resta (1234000005.67890, 98765.4321);
resta (98765.43210, 98765.4321);
resta (12345.67890, -98765.4321);
resta (-5.67890, -5.4321);

niega (-23456787.7654321);
niega (3456787.7654321);
niega (787.7654321);
niega (-123456787.7654321);
niega (-.7654321);
niega (.7654321);

FIN_PROG_PPAL