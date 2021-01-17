/**	Define the entry point for the application dll if proceed

*	Prefix: UGKDLL_

*	@author Ramón Mollá
*	@version 2014-09
*/

//#include <UGK.h>
//
//#ifdef	UGKOS_WINDOWS
//	#include <stdafx.h>
//
//	BOOL APIENTRY DllMain( HMODULE hModule,
//						   DWORD  ul_reason_for_call,
//						   LPVOID lpReserved
//						 )
//	{
//		switch (ul_reason_for_call)
//		{
//		case DLL_PROCESS_ATTACH:
//		case DLL_THREAD_ATTACH:
//		case DLL_THREAD_DETACH:
//		case DLL_PROCESS_DETACH:
//			break;
//		}
//		return TRUE;
//	}
//
//#elif	defined(UGKOS_LINUX)
//#elif	defined(UGKOS_OSX)
//#elif	defined(UGKOS_ANDROID)
//#endif