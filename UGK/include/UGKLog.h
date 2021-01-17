/**	Definition of the class Log

Prefix: UGKCL_

@author Ramon Molla
@version 2014-05
*/

#ifndef UGKCL_LOG
#define UGKCL_LOG

#ifndef FSTREAM_INITIALIZED //se borra la macro Inicializacion del log
#define FSTREAM_INITIALIZED //se define la macro Inicializacion del log
#include <fstream>
#endif

#include <UGKString.h>

#define UGKCL_MAXSTRINGS		50	//Amount of different logs that may appear simultaneously on the screen
#define UGKCL_LOADINGBMP_FINAL_POSITION 1.3f

// Shows a messagebox window with a message on the screen
#ifdef UGKOS_WINDOWS
#ifndef WINDOWS_LOADED
#define WINDOWS_LOADED
#include <windows.h>
#endif
#define BOX(text) MessageBox(NULL,text,LPCWSTR("Info"),MB_OK | MB_TOPMOST);
#elif	defined(UGKOS_LINUX)
#include <UGKstring.h>
#elif	defined(UGKOS_OSX)
#include <UGKstring.h>
#elif	defined(UGKOS_ANDROID)
#include <UGKstring.h>
#endif

// MACRO : Show an error message with the file name and the erroneous line
#define ERR(s) Log.DisplayMsgBoxErrorAndExit(LPCTSTR(__FILE__), __LINE__, s)

// MACRO : Show the last error message into the debug output
#define LAST_ERROR() Log.DisplayLastErrorDebug()

// MACRO : Show an integer output string into the debugger once if it si not zero
#ifdef UGKOS_WINDOWS
#define DISPLAY_1INT(var)											\
	static int my_number = 0;									\
if (0 == my_number)											\
			{															\
			my_number = var;										\
			char my_string[300] = UGKS_EMPTY_STRING;					\
			OutputDebugString(_itoa(my_number, my_string, 10));	\
			}
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

// MACRO : Show an integer output into the debugger
#ifdef UGKOS_WINDOWS
#define DISPLAY_INT(var)											\
				{														\
				char my_string[300] = UGKS_EMPTY_STRING;				\
				OutputDebugString(_itoa(var, my_string, 10));		\
				}
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

// MACRO : Show an output string into the debugger
#ifdef UGKOS_WINDOWS
#define DISPLAY(var) OutputDebugString (var);
#pragma warning(disable: 4251)
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

namespace UGK
{
	/**
	@class CLog

	* Set information on a openGL screen/file for debugging options

	@author Ramon Molla
	@version 2012-11
	*/
	class UGK_API CLog
	{
	protected:
		std::ofstream	LogFile;
		UGKS_String		FileName;

	public:
		//Atributes
		UGKS_String Version;						///< Program VERSION to provide information about
		UGKS_String	LogStrings[UGKCL_MAXSTRINGS];	///< 50 logs of 50 characters available
		int			LogIndex;						///< Pointer to the current available log

		//Methods
		void Init(void);

		CLog();				///<Constructor of the class

		//Display procedures in pop up windows
#ifdef UGKOS_WINDOWS
		//Information written on main window 
		void DisplayMsgBoxErrorAndExit	(LPCTSTR File, int Line, LPCTSTR Message);
		void DisplayMsgBoxError			(LPCTSTR File, int Line, LPCTSTR Message);
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

		void Add					(UGKS_String Text);
		void Init					(UGKS_String FileName);
		void DisplayLastErrorDebug	(void);
		void DisplayLastErrorBox	(void);

		//Writting in a log file
		///Closes the log file before exiting
		void Close();
		///Writes in a log file a given log information
		void Write();
	};
}	//namespace UGK
#endif
