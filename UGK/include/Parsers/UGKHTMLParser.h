
/**	General Parser class that manages general functions of any given parser
	Implements both the lexical analyzer and the sintactic analizer

*	Prefix CP_: Class Parser

*	@author Ramon Molla
*	@version 2012-09
*/

#ifndef CP_PARSER
#define CP_PARSER

#include <UGKDefaultHTMLLabels.h>
#include <LiteHTMLReader.h>
#include <stack>
#include <map>

using namespace std;

#ifndef FSTREAM_INITIALIZED
#define FSTREAM_INITIALIZED
#include <fstream>
#endif

typedef enum {
	LOG_PARSER_UNKNOWN,
	LOG_PARSER_TAG_CHARACTER_TYPE,
	LOG_PARSER_TAG_NOT_COMPATIBLE,
	
	LOG_PARSER_TAG,
	LOG_PARSER_ALLOWED,
	LOG_PARSER_NOT_ALLOWED,
	LOG_PARSER_GROUP,
	
	LOG_PARSER_BEGIN_PARSE,
	LOG_STARTING_INTERPRETATION,
	LOG_PARSER_START_TAG,
	LOG_PARSER_NOT_HTML_TAG,
	LOG_PARSER_NOT_HTML_TAG2,
	LOG_PARSER_ONLY_HEAD_OR_BODY,

	LOG_PARSER_END_TAG_END,
	LOG_PARSER_END_TAG_MAXTAGS,
	LOG_PARSER_END_TAG_UNK,
	LOG_PARSER_END_TAG_ERROR1,
	LOG_PARSER_END_TAG_ERROR2,
	LOG_PARSER_SEGMENT,

	LOG_PARSER_TEXT,
	LOG_PARSER_NOT_THIS_VG,
	LOG_PARSER_FILE_TYPE,
	LOG_PARSER_FILE_TYPE2,
	LOG_PARSER_FILE_VERSION,
	LOG_PARSER_FILE_VERSION2,
	 
	LOG_PARSER_COMMENT,
	LOG_PARSER_END_PARSE,
	
	LOG_PARSER_END_LABEL,
	LOG_PARSER_COMMENTS,
	LOG_PARSER_FILE_PARSING_FINISHED,
	LOG_PARSER_TOP,
	LOG_PARSER_SUBTOP,
	LOG_PARSER_CHARACTERS,
	LOG_PARSER_LABEL,
	LOG_PARSER_NO_HW,
	LOG_PARSER_MAX_LOGMSG
} CP_LogMsg;

#define CP_MessageType	UGKS_String
#define CP_LexemeType	UGKS_String
#define CP_StringType	UGKS_String
#define CP_TokenType	int

UGK_API extern CP_MessageType CP_ParserMsgs[LOG_PARSER_MAX_LOGMSG];

UGK_API typedef map<CP_LexemeType, CP_TokenType> LexemeDictionaryType;

#define CP_NO_TOKEN -1
#define StartStack() {StateStack.push(NIL_D);subTop = NIL_D;}

/**	
*	CHTMLParser

*	@author Ramon Molla
*	@author David Peris
*	@version 2015-05
*/

namespace UGK
{
	class UGK_API CHTMLParser : public ILiteHTMLReaderEvents
	{

	protected:
		//Head of the file general attributes
		CP_StringType	Title;		///< Program TITLE
		CP_StringType	Version;	///< Program VERSION
		CP_StringType	Type;		///<Type of the parser created

		//Stack that supports the stack machine
		stack<CP_TokenType>		StateStack;	///<Stack to store the different states while parsing a file
		CP_TokenType			subTop;		///< Token under the top tag on the StateStack. For checking purpouses

#ifdef _DEBUG	//Only works when Debug mode  is activated
		ofstream				LogFile;	///<For reporting about the parsing for debugging
#endif

		LexemeDictionaryType			LexemeDictionary;
		LexemeDictionaryType::iterator	CurrentToken;

		///Frees the stack so that it is completely empty
		inline void ResetState()
		{
			//Clear stack
			while (!StateStack.empty()) StateStack.pop();
			StartStack()
		}

#ifdef _DEBUG	//Only works when Debug mode is activated
		/**
		*	\fn inline void CHTMLParser::TagError(const char *Text) 
		*	Virtual error manager that logs the associated error to a given TAG when parsing a file.
		*	Given by default in case the user does not create it on a given parser
		*	\param[in] Text Message to log
		*/
		void	TagError		(CP_MessageType Text);

		/**
		@fn inline void TagError(CP_LexemeType Token, CP_StringType Group)
		@param CP_LexemeType Token: this is the label that does not belong to the message
		@param CP_StringType Group this is the name of the group classification label for the message
		*/
		inline void TagError		(CP_LexemeType Token, CP_StringType Group)	{ if (LogFile.is_open())	TagNotAllowed(Token, Group); }
		inline void	ErrorParser		(CP_MessageType msg)	{ LogFile << UGKS_string2charstr(Type) << " parser error: " << UGKS_string2charstr(msg) << std::endl; }
		void		ErrorClosingTag	(CP_StringType TagString); ///<Logs a parser error of not matching closing tags
		inline void WriteLog		(CP_LogMsg LM, CP_LexemeType TagString) {LogFile << CP_ParserMsgs[LM] << TagString << UGKS_NEW_LINE_STRING;}
#else
		#define ErrorParser(msg)
		inline void TagError(CP_LexemeType, CP_StringType){}
		inline void TagError(CP_MessageType){}
		#define WriteLog(LM,TagString)
#endif

		///Translates from a string to the token that the string represents
		CP_TokenType Lexeme2Token (CP_LexemeType Lexeme);

		///Given a token, this method converts it into its lexeme (string) associated to it
		CP_LexemeType Token2Lexeme (CP_TokenType Token);

	public:

		///Constructor
		CHTMLParser	();
		///Destructor
		~CHTMLParser	();

		void		Init				(CP_StringType LogFileName);
		void		Finish				();	///< Close everything internally

#ifdef _DEBUG	//Only works when Debug mode is activated
		void		VersionMismatch		(const CP_StringType &V);
		void		TagNotAllowed		(CP_LexemeType Token, CP_StringType Group);
		void		FileTypeMismatch	(CP_StringType FileType, CP_StringType ExpectedType);
#else
		#define TagNotAllowed(TagString,Tag) 
		#define VersionMismatch(CP_StringType)
		#define FileTypeMismatch(FileType,ExpectedType)
#endif

		/**
		*	\fn void AssignTags DHTML_TagsArrayType Tags, DHTML_TagsArray OwnTags, unsigned int Size)
		*	Copy internal Tags for parsing into the external tags of the corresponding parser
		*	\param[out] Tags	The array destination
		*	\param[in]  OwnTags	The array with the tags related to the current parser
		*	\param[in]  Size	Amount of tags counting CP_ParserTags and current parser ones
		*/
		inline void AssignTags (DHTML_TagsArrayType Tags, CP_TokenType HTMLSize, CP_LexemeType OwnTags[], CP_TokenType OwnSize)
		{
			int TagsIndex, OwnTagsIndex;

			LexemeDictionary.clear();
	
			for(TagsIndex = 0; TagsIndex<HTMLSize;TagsIndex++) LexemeDictionary[Tags[TagsIndex]] = TagsIndex;
			for(OwnTagsIndex = 0; OwnTagsIndex<OwnSize-HTMLSize;OwnTagsIndex++, TagsIndex++) LexemeDictionary[OwnTags[OwnTagsIndex]] = TagsIndex;
		}

		/**
		*	\fn void AssignTags DHTML_TagsArrayType Tags, DHTML_TagsArray OwnTags, unsigned int Size)
		*	Copy internal Tags for parsing into the external tags of the corresponding parser
		*	\param[out] Tags	The array destination
		*	\param[in]  OwnTags	The array with the tags related to the current parser
		*	\param[in]  Size	Amount of tags counting CP_ParserTags and current parser ones
		*/
		inline void AssignTags(CP_LexemeType OwnTags[], CP_TokenType OwnSize) {AssignTags(DHTML_TagsArray, MAXTAGS_D, OwnTags, OwnSize);}

		/**
		*	\fn void CHTMLParser::WriteFile(HANDLE hFile)
		*	\param[in] hFile Handle to the file to open and parse
		*/
		virtual void WriteFile(HANDLE hFile){};

		CP_MessageType		GetMsg(CP_LogMsg Msg) { return CP_ParserMsgs[Msg]; }

		/**
		*	\fn inline void SetVersion (CP_StringType V)
		*	Sets the name of the version to find inside of the parsed file
		*	\param[in] Text Version of the program to parse
		*/
		inline void SetVersion(CP_StringType V) { Version = V; }///< Updates the protected attribute "Version". The version number of the videogame that appears inside the HTML file

		/**
		*	\fn inline void SetTitle(CP_StringType T)
		*	Sets the name of the title to find inside of the parsed file
		*	\param[in] Text Version of the program to parse
		*/
		inline void SetTitle(CP_StringType T)	{ Title = T; } ///< Updates protected attribute "Title". The name of the videogame that appears inside the HTML file

		/**
		*	\fn inline void SetType (CP_StringType T)
		*	Sets the name of the type of parser to find inside of the parsed file
		*	\param[in] Text Version of the program to parse
		*/
		inline void SetType(CP_StringType T) { Type = T; }///< Updates the protected attribute "Version". The version number of the videogame that appears inside the HTML file

		/**
		*	\fn inline CP_StringType GetVersion() 
		*	Gets the name of the version of the file to parse
		*	Retrieves the protected attribute "Version".The version number of the videogame that appears inside the HTML file
		*/
		
		inline CP_StringType GetVersion(){return Version;}

		/**
		*	\fn CP_StringType GetTitle();
		*	Gets the name of the title of the file to parse
		*	Retrieves the protected attribute "Title". The name of the videogame that appears inside the HTML file
		*/
		inline CP_StringType GetTitle(){return Title;}

		/**
		*	\fn CP_StringType GetType();
		*	Gets the name of the type of the file to parse
		*	Retrieves the protected attribute "Title". The name of the videogame that appears inside the HTML file
		*/
		inline CP_StringType GetType(){return Type;}

		inline CP_TokenType	Top			()					{if (StateStack.empty()) return NIL_D; else return StateStack.top();}
		inline CP_TokenType	SubTop		()					{return subTop;}

		/**
		@fn Push
		@param unsigned int Token: label to push in the stack
		Updates the SubTop with the actual Top and then it makes a push of the tag in the stack.
		*/
		inline void		Push		(unsigned int Token)	{subTop = Top(); StateStack.push(Token);}

		/**
		@fn Pop
		Removes the Top of the stack, then if the Top != null it makes another pop and a push of the Top to update 
		correctly the subTop
		*/
		inline void		Pop			()					{CP_TokenType Token; 
														 StateStack.pop();

														 if (StateStack.empty())
															 StartStack()
														 else 
														 {
															 //In order to update SubTop value
															 Token = StateStack.top();
															 StateStack.pop();
															 Push(Token);
														 }
														}
	};
}
#endif
