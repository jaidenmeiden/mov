/**	Declaration of all the parser methods to understand the initialization files
*	@author Ramon Mollá
*	@version 2012-09
*/

#include <UGKHTMLParser.h>
#include <UGKString.h>

#define Tag2Lexeme(Lexeme,pTag) Lexeme = pTag->getTagName())

UGK_API CP_MessageType CP_ParserMsgs[LOG_PARSER_MAX_LOGMSG] =
{
	"Unknown",			//This tag has no matching. It is for management purpouses only. 
	"Character Type (",
	") not compatible.",

	"Token ",
	" allowed in a ",
	" not allowed in a ",
	" group.",

	"Begining the file parsing.",
	"Starting the interpretation of the file.",
	"Start tag: ",
	"First tag was not an HTML tag.",
	" was not an HTML tag.",
	"Only the attribute HEAD or BODY may appear in a group HTML.",
	
	"End tag: ",
	" clossing tag out from the HTML section.",
	" clossing tag in an unknown state.",
	" clossing tag without correspondent opening tag.",
	" clossing tag without correspondent opening tag in a ",
	" segment.",

	"Text: ",
	"This file does not corresponds to this videogame.",
	"This file type is \"\n",
	"\". It is required a file of type \"\n",
	"This file versión is v",
	". This does not corresponds with this game version v",

	"Comments: %s\n",
	"Ending the file parsing.",
	
	"Ending Label: ",
	"Comments: ",
	"File parsing is finished.",
	" Top : ",
	" SubTop : ",
	" Characters: ",
	"Label ",
	" does not belong to any hardware type."
};

using namespace UGK;

///Constructor
CHTMLParser::CHTMLParser	()
{
	//Clear identifiers
	Version.clear();
	Title.clear();

	ResetState();
}

///Destructor
CHTMLParser::~CHTMLParser	()
{
#ifdef _DEBUG	//Only works when Debug mode  is activated
	if (LogFile.is_open()) 
		LogFile.close();
#endif
	ResetState();
}

CP_TokenType CHTMLParser::Lexeme2Token (CP_LexemeType Lexeme)
{
	CurrentToken = LexemeDictionary.find(Lexeme);
	if (LexemeDictionary.end() == CurrentToken)
		return CP_NO_TOKEN;
	else return CurrentToken->second;
}

CP_LexemeType CHTMLParser::Token2Lexeme (CP_TokenType Token)
{	
	for (CurrentToken = LexemeDictionary.begin(); CurrentToken != LexemeDictionary.end(); ++CurrentToken) 
		if (Token  == CurrentToken->second)
			return  (CP_LexemeType) CurrentToken->first;
	return UGKS_EMPTY_STRING;	//In case no matching happens
}

#ifdef _DEBUG	//Only works when Debug mode is activated
/**
*	\fn void CHTMLParser::FileTypeMismatch		(CString FileType, CString ExpectedType)
*	Reports a parser error associated to a file type mismatch when parsing a file.
*	\param[in] FileType		Type of the file currently parsed
*	\param[in] ExpectedType	Expected type of the file
*/
void CHTMLParser::FileTypeMismatch(CP_StringType FileType, CP_StringType ExpectedType)
{
	CP_MessageType msg;

	msg = CP_ParserMsgs[LOG_PARSER_FILE_TYPE];
	msg += FileType;
	msg += CP_ParserMsgs[LOG_PARSER_FILE_TYPE2];
	msg += ExpectedType;
	msg += "\".";
	ErrorParser(msg);
}

/**
*	\fn void CHTMLParser::VersionMismatch (const CString &V)
*	Reports a parser error associated to a version mismatch when parsing a file.
*	\param[in] V Current file version. Differentfrom current video game version
*/
void CHTMLParser::VersionMismatch(const CP_MessageType &V)
{
	CP_MessageType msg;

	msg = CP_ParserMsgs[LOG_PARSER_FILE_VERSION];
	msg += V;
	msg += CP_ParserMsgs[LOG_PARSER_FILE_VERSION2];
	msg += Version;
	msg += ".";
	ErrorParser (msg);
}

/**
*	\fn void CHTMLParser::TagNotAllowed (CP_LexemeType Token, CString Group)
*	Sets a parser error associated to a given mismatch TAG and Group when parsing a file.
*	\param[in] Token Token to log
*	\param[in] Group mismatch to log
*/
void CHTMLParser::TagNotAllowed(CP_LexemeType Token, CP_LexemeType Group)
{
	CP_MessageType msg;

	msg	= CP_ParserMsgs[LOG_PARSER_TAG];
	msg += Token;
	msg += CP_ParserMsgs[LOG_PARSER_NOT_ALLOWED];
	msg += Group;
	msg += CP_ParserMsgs[LOG_PARSER_GROUP];
	ErrorParser( msg);
}

/**
*	\fn void CHTMLParser::ErrorClosingTag(CString TagString)
*	Error Msj to log when a given TAG is not properly closed when parsing a file.
*	Typically this is when the closed tag does not match the current parser state 
*	\param[in] TagString Message to log
*/

void CHTMLParser::ErrorClosingTag(CP_MessageType TagString) ///<Logs a parser error of not matching closing tags
{
	CP_MessageType msg;
	
	msg = TagString;
	msg += CP_ParserMsgs[LOG_PARSER_END_TAG_ERROR1];
	ErrorParser	(msg);
}

#ifdef _DEBUG	//Only works when Debug mode  is activated
//Preface for the Token analysis
void CHTMLParser::TagError(CP_StringType Text)
{
	CP_MessageType msg;

	if (LogFile.is_open())
	{
		msg = CP_ParserMsgs[LOG_PARSER_TAG_CHARACTER_TYPE];
		msg += Text;
		msg += CP_ParserMsgs[LOG_PARSER_TAG_NOT_COMPATIBLE];
		ErrorParser(msg);
	}
}
#endif


#endif

/**
*	\fn void CHTMLParser::Init(CP_MessageType LogFileName)
*	Initializes the parser and sets the log file where to store the results of parsing a file.
*	\param[in] Text File where to store the logs
*/

void CHTMLParser::Init(CP_MessageType LogFileName)
{
#ifdef _DEBUG	//Only works when Debug mode  is activated
	if (!LogFileName.empty())
	{
		LogFile.open(LogFileName);
		if (!LogFile.is_open())	//The file is opened
			exit(UGK_HTML_PARSER_LOG_FILE_ERROR);	//Cannot open file. Finish program
	}
#endif
	ResetState();
}


/**
*	\fn void CHTMLParser::Finish()
*	Reset the parser and close the log file
*/

void CHTMLParser::Finish()
{
#ifdef _DEBUG	//Only works when Debug mode  is activated
	LogFile.close();
#endif
	ResetState();
}
