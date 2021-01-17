/**	Definition of the general characteristics of the UPV Game Kernel - UGK

*	Prefix: UGK_

*	@author Ramon Molla
*	@modified 
*	@version 2014-05
*/

#ifndef UGK_UGK
#define UGK_UGK

#include <UGKOS.h>

#define UGKDecimal float

#ifdef	UGKOS_WINDOWS
	//#define DLL_EXPORTS
	//#define DLL_IMPORTS
	
	#ifdef DLL_EXPORTS
		#define UGKMMO_API __declspec(dllexport)
		#define UGK_API __declspec(dllexport)
	#elif defined(DLL_IMPORTS)
		#define UGKMMO_API __declspec(dllimport)
		#define UGK_API __declspec(dllimport)
	#else
	//For .lib files. No DLL. Static linking
		#define UGKMMO_API
		#define UGK_API
	#endif
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

#ifdef	UGKOS_GCC
#elif	defined(UGKOS_VS)
#endif

typedef enum
{
	UGK_NO_ERROR,
	UGK_WINDOW_CREATION_ERROR,
	UGK_CHOOSE_PIXEL_FORMAT_ERROR,
	UGK_SET_PIXEL_FORMAT_ERROR,
	UGK_SDL_INITIALIZATION_ERROR,
	UGK_SDL_MIX_OPEN_AUDIO_ERROR,
	UGK_LANG_READER_LOG_FILE_ERROR,
	UGK_DEVICE_READER_LOG_FILE_ERROR,
	UGK_HTML_PARSER_LOG_FILE_ERROR,
	UGK_LOG_FILE_ERROR,
	UGK_MESSASGE_BOX_ERROR
} UGK_END_ERRORS;

#define UGK_HTML_EXT ".html"
#define UGK_LOG_EXT "_Log.txt"

#endif
