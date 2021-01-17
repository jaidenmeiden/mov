/**	Declaration of all the Reader methods to understand the initialization files
*	@author Ramon Mollá
*	@version 2014-11
*/

#include <UGKHTMLReader.h>

using namespace UGK;

/**
*	\fn void ParseFile ()
*	Opens a file previously assigned and parses it depending on the parser loaded before invoking this method
*/
void CHTMLReader::ParseFile ()
{
	CString FileName = UGKS_string2charstr(HTMLFileName);

	if (HTMLFile.Open(FileName, CFile::modeRead))
	{
		ReadFile((HANDLE) HTMLFile.m_hFile);
		HTMLFile.Close();
	}
}

void CHTMLReader::ParseFile(UGKS_String FileName, UGKS_String Folder, CHTMLParser *Parser)
{
	UGKS_String FileLog;

	//Set Title and Version for the Parser
	Parser->SetTitle(GetTitle());
	Parser->SetVersion(GetVersion());

	//Contruct names of the complete path log and file names
	UGKS_GenerateFullPathName(FileLog, Folder, FileName);
	FileName = FileLog;
	FileLog += UGK_LOG_EXT;
	FileName += UGK_HTML_EXT;

	//Set the log file and...
	Parser->Init(FileLog);
	//Assigning the generic parser to the reader
	setEventHandler(Parser);
	//Parse the file 
	ParseFile(FileName);
	Parser->Finish();
}

