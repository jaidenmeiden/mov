/**	Definition of the Operating System the videogame is running on

*	Prefix: UGKOS_

*	@author Ramon Molla
*	@modified 
*	@version 2014-05
*/

#ifndef UGKOS_OPERATINGSYTEM
#define UGKOS_OPERATINGSYTEM

#define UGKOS_WINDOWS
//#define UGKOS_LINUX
//#define UGKOS_OSX
//#define UGKOS_ANDROID

#define UGKOS_OPENGL

/* Copy and paste these lines wherever you need a specific code for a specific OS
#ifdef	UGKOS_WINDOWS
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif
*/

#ifdef	UGKOS_WINDOWS
	#define UGKOS_DIRECTORY_SEPARATOR "\\"
	#define UGKOS_THIS_DIRECTORY ".\\"

	#define FALSE   0
	#define TRUE    1
	#define NULL    0

	#define UGKOS_UNUSED_VBLE_WARNINGS(a) UNUSED(a)
	#define UGKOS_DIS_UNUSED_VBLE_WARNINGS
	#define UGKOS_ENA_UNUSED_VBLE_WARNINGS

	//#define UGKOS_DIRECTX
	#define UGKOS_OPENGL
#elif	defined(UGKOS_LINUX)
	#define UGKOS_DIRECTORY_SEPARATOR "/"
	#define UGKOS_THIS_DIRECTORY "./"

	#define UGKOS_DIS_UNUSED_VBLE_WARNINGS		#pragma GCC UGKOS_UNUSED_VBLE_WARNINGS push \
												#pragma GCC UGKOS_UNUSED_VBLE_WARNINGS  ignored "-Wunused-variable"
	#define UGKOS_ENA_UNUSED_VBLE_WARNINGS		#pragma GCC UGKOS_UNUSED_VBLE_WARNINGS  pop
	#define UGKOS_UNUSED_VBLE_WARNINGS(a) 

#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

#endif
