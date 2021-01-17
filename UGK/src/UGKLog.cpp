/**	Declaration of the class Log

	Prefix: CL_

	@author Ramon Molla
	@version 2011-11
*/

#include <stdlib.h>
#include <UGKLog.h>
#include <UGKString.h>

using namespace UGK;
CLog Log;

/**
   * @fn CLog
   * Constructor to the Log
   * By default the file name starts empty    
   * And the function is called Home
*/
CLog::CLog()
{
	FileName.clear();
	Init();
}

/**   
   * @fn CLog::Init(CString File)
   * Start with the Log File
   * @param CString File the name of the file
   * @return This function opens the log file otherwise it returns 0
*/
void CLog::Init(UGKS_String File)
{
	FileName = File;

	LogFile.open(File);
	if (!LogFile)	//NAME the file
		exit(UGK_LOG_FILE_ERROR);
	Init();
}

/**   
   * @fn CLog::Init
   * Start the Log
   * This function starts the progress bar, the image of the game loaded disabled
*/
void CLog::Init(){LogIndex	= 0;}

/**   
   * @fn CLog::DisplayMsgBoxError
   * @param LPCTSTR File name of the file
   * @param int Line represents the line number where the error occurred
   * @param LPCTSTR Message represents the message to be displayed
   * This function displays an error in a text box
*/
void CLog::DisplayMsgBoxError(LPCTSTR File, int Line, LPCTSTR Message)
{
	TCHAR ErrorBuf[512];

	// Create the Error string.
	wsprintf(ErrorBuf, LPCWSTR("Sorry, an error has occurred...\n\n%s\nFile %s, line %d, version %s\n\nPlease check http://ramon.blogs.upv.es to grab the last release.\nIf the error persists email Ramon Molla at rmolla@dsic.upv.es"), 
		Message, File, Line, Version);

	// Dump the error to the debugger, if present.
	OutputDebugString(ErrorBuf);

	// Display the error using MessageBox.
	if (lstrlen(Message))
		MessageBox(NULL, ErrorBuf, Message, MB_OK | MB_TOPMOST);
}

/**   
   * @fn CLog::DisplayMsgBoxErrorAndExit
   * @param LPCTSTR File name of the file
   * @param int Line represents the line number where the error occurred
   * @param LPCTSTR Message represents the message to display
   * This function calls the function to display the error DisplayMsgBoxError
*/
void CLog::DisplayMsgBoxErrorAndExit(LPCTSTR File, int Line, LPCTSTR Message)
{
	DisplayMsgBoxError(File, Line, Message);
	exit(UGK_MESSASGE_BOX_ERROR);
}

/**   
   * @fn CLog::DisplayLastErrorDebug
   * Show last bug in the compiler
   * You configure the format of the message box to the errors generated FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS 
   * This function shows the format of the error on the screen
*/
void CLog::DisplayLastErrorDebug(void)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
	OutputDebugString((LPCTSTR)lpMsgBuf); //Envia lpMsgBuf al depurado por pantalla
	LocalFree(lpMsgBuf); //libera lpMsgBuf de memoria bloqueado
}
/**   
   * @fn CLog::DisplayLastErrorBox
   * Show last error on the box
   * You set the format to display the message box to the errors generated FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS 
   * This function shows in a box the configuration of the message error
*/
void CLog::DisplayLastErrorBox(void)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
	BOX((LPCWSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
/**   
   * @fn CLog::Add (CString Text)
   * Add to the Log
   * @param CString Text: represents the text to copy to Log
   * Copy the text to the Log and increments its index
   * After updates the Log
*/
void CLog::Add(UGKS_String Text)
{
	LogStrings[LogIndex] = Text;		// Copies the text onto the current Log Index

	LogIndex++;							// The index is incremented in one unit
	if (UGKCL_MAXSTRINGS <= LogIndex) LogIndex = UGKCL_MAXSTRINGS -1;
}

/**   
   * @fn CLog::Close
   * Closes the log file before exiting
*/
void CLog::Close()
{
}

/**   
   * @fn CLog::Write()
   * Writes in a log file a given log information
*/

void CLog::Write()
{
}
