/**	Definition of the UGKS_String class

*	Prefix: UGKS_

*	@author Ramon Molla
*	@version 2016-02
*/

#ifndef UGKS_STRING
#define UGKS_STRING

#include <string>
#include <UGK.h>

#ifdef	UGKOS_WINDOWS
	#ifndef WINDOWS_LOADED
	#define WINDOWS_LOADED
	#include <windows.h>
	#endif

	#define UGKS_EMPTY_LPWSTR	LPWSTR("")
	#define UGKS_EMPTY_LPCWSTR	LPCWSTR("")
	#define UGKS_EMPTY_LPCTSTR	LPCTSTR("")

	//CString macros conversions
	#define UGKS_CString2string(s) CT2A(s)
	#define UGKS_string2CString(s) s.c_str()
	#define UGKS_string2LPCWSTR(s) LPCWSTR(s.c_str())
	#define UGKS_string2LPCTSTR(s) LPCTSTR(s.c_str())

#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

#define UGKS_EMPTY_STRING ""
#define UGKS_NEW_LINE_STRING std::endl
#define UGKS_STR_END '\0'

#define UGKS_string2charstr(s) s.c_str()

#define UGKS_String	std::string

UGKS_String UGK_API	UGKS_GenerateFullPathName(UGKS_String  &Result, UGKS_String  Path, UGKS_String  Name);
UGKS_String UGK_API UGKS_RelativeFullPathName(UGKS_String  &Result, UGKS_String  Path, UGKS_String  Name);
#endif