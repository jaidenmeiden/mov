/*LANGUAGE READER
	@author Ramon Molla
	@version 2007-09-11
*/
#include <UGKLanguageParser.h>
#include <UGKString.h>
#include <UGKDefaultHTMLLabels.h>
#include <iostream>

extern	DHTML_TagsArrayType DHTML_TagsArray;

//Sensitive string tags
CP_LexemeType CLaP_Tags[L_MAXTAGS-MAXTAGS_D] = 
{
	"CONTENT",
	"ID",
	"LANGUAGE",
	"RESOURCE"
};

CP_MessageType CLaP_LanguageParserMsgs[] =
{
	"\". It is required a \"LANGUAGE\" file type.",
	"Language",
	" English ",
	" Spanish ",
	" Catalan "
};

typedef struct
{
	int				ID;
	CP_StringType	Resource;
} CLaP_LangRes;

#define CLaP_NO_ID -1
CLaP_LangRes TempRes = { CLaP_NO_ID, "" };

using namespace UGK;

void CLanguageReader::SaveResource()
{
	Language->SetText(TempRes.ID, TempRes.Resource);
	TempRes.ID = CLaP_NO_ID;
	TempRes.Resource.clear();
}

CLanguageReader::CLanguageReader(CP_StringType V, CP_StringType T)
{
	AssignTags(CLaP_Tags, L_MAXTAGS);
	Title	= T;
	Version = V;
	Type = CLaP_LanguageParserMsgs[LOG_LANGUAGE_LANGUAGE];	//Type of parser. Do not change. It is always the same. Its nature is not changed
}

UGKOS_DIS_UNUSED_VBLE_WARNINGS
void CLanguageReader::BeginParse(DWORD dwAppData, bool &bAbort)
{
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

#ifdef _DEBUG
	WriteLog(LOG_PARSER_BEGIN_PARSE, "");
#endif
}

void CLanguageReader::StartTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort)
{
	CP_LexemeType	TagString;
	CP_TokenType	Token;

	TagString = UGKS_CString2string(pTag->getTagName());

#ifdef _DEBUG
	WriteLog(LOG_PARSER_START_TAG,TagString);
#endif

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	Token = Lexeme2Token(TagString);
 	switch(Top())
	{case NIL_D://Starting and ending states
				if (HTML_D == Token)
				{//It is a HTML file. Change to HTML state
					Push(HTML_D);
					//Do some initializations
				}
				else ErrorParser(CP_ParserMsgs[LOG_PARSER_NOT_HTML_TAG]);
		break;
	 case BODY_D:	//HTML tag
					switch (Token)
					{
						case L_RESOURCE: Push(Token); //Change to the state specified by the Token
							break;
						default: TagNotAllowed(TagString,DHTML_TagsArray[BODY_D]);
					}
		break;
	 case L_RESOURCE :
		 switch (Token)
		 {
		 case L_ID:		
		 case L_CONTENT:
			 Push(Token);
			 break;
		 default: ErrorParser(CLaP_LanguageParserMsgs[LOG_LANGUAGE_PARSER_ERROR_RESOURCE]); 
		 }
		 break;
	 case HEAD_D:		//HTML tag
					switch (Token)
					{
					case TYPE_D:
						//Rename Token to the correct context
							Token = TYPE_D;
					case TITLE_D:
					case VERSION_D:
					case L_LANGUAGE:
						Push(Token); //Change to the state specified by the Token
						break;
					default: TagNotAllowed (TagString,DHTML_TagsArray[HEAD_D]);
					}
		break;
	case HTML_D:	//HTML Token
					//The parser is at the very beginning of the iniitalization file
					switch (Token)
					{
					case HEAD_D:		//A HEAD Token is expected
					case BODY_D: 
						Push(Token); //Change to the state specified by the Token
						break;
					default: 
							ErrorParser	(CP_ParserMsgs[LOG_PARSER_ONLY_HEAD_OR_BODY]);
							TagError	(TagString);	//DHTML_TagsArray[HTML_D]
					}
		break;
	default:;
	};
}

void CLanguageReader::EndTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort)
{
	CP_StringType	msg;
	CP_LexemeType	TagString; 
	CP_TokenType	Token;
	bool Error = false;
	
	TagString = UGKS_CString2string(pTag->getTagName());

	WriteLog(LOG_PARSER_END_TAG_END,TagString);

	//printf("Etiqueta fin: %s\n", pTag->getTagName());
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	Token = Lexeme2Token(TagString);
	switch(Top())
	{case BODY_D:
	 case L_CONTENT:
	 case HEAD_D:
	 case HTML_D:
	 case L_ID:
	 case L_LANGUAGE:
	 case L_RESOURCE:
	 case TITLE_D:
 	 case TYPE_D:
	 case VERSION_D:	//The parser is at the very end of the initialization file					
		 			if (Top() == Token) Pop();	//Change to the previous state
					else Error = true;
		break;
	 case NIL_D:
	 case L_MAXTAGS:	
			#ifdef _DEBUG	//Only works when Debug mode  is activated
					//Closing a label when all the lables are closed is an error
					msg = TagString;
					msg += CP_ParserMsgs[LOG_PARSER_END_TAG_MAXTAGS];
					ErrorParser(msg);
			#endif
		break;
	 case CP_NO_TOKEN:	
				#ifdef _DEBUG	//Only works when Debug mode  is activated
					//This tag is for management purpouses only. There is no correspondence to any string label in the HTML file
					msg = TagString;
					msg += CP_ParserMsgs[LOG_PARSER_END_TAG_UNK];
					ErrorParser(msg);
				#endif
		break;
	default:;
	};	//Switch

#ifdef _DEBUG	//Only works when Debug mode  is activated
	if (Error)
	{	msg = TagString;
		msg += CP_ParserMsgs[LOG_PARSER_END_TAG_ERROR1];

		if (StateStack.size()>=2)
		{
			unsigned int AuxState = Top();
			Pop();
			msg += Token2Lexeme(Top());
			Push(AuxState);
		}
		else msg += Token2Lexeme(Top());
		msg += CP_ParserMsgs[LOG_PARSER_END_TAG_ERROR2];
		ErrorParser(msg);
	}
#endif
}

void CLanguageReader::Characters(const CP_StringType &rText, DWORD dwAppData, bool &bAbort)
{
	static int     intAux, msgBox;

	if (bAbort) return;

#ifdef _DEBUG
	WriteLog(LOG_PARSER_TEXT,rText);
#endif

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	switch(Top())
	{
	case L_CONTENT:
		TempRes.Resource = rText;
		if (CLaP_NO_ID != TempRes.ID)
			SaveResource();
		break;
	case L_ID:
		intAux = atoi(UGKS_string2charstr(rText));
		if (intAux >= 0)
		{
			TempRes.ID = intAux;
			if (!TempRes.Resource.empty())
				SaveResource();
		}
		else
		{
			TempRes.ID = CLaP_NO_ID;
			msgBox = MessageBox(NULL,
				CString(UGKS_string2CString(rText)),
				TEXT("Error al recuperar el ID del RESOURCE"),
				MB_ICONASTERISK | MB_OKCANCEL);
		}

		break;
	case L_LANGUAGE:
		Language->SetCode(rText);
		break;
	case TITLE_D:	//HTML tag
		if (rText.compare(Title))
		{
			ErrorParser (CP_ParserMsgs[LOG_PARSER_NOT_THIS_VG]);
			bAbort = true;
		}
		//MessageBox(NULL,rText,UGKS_EMPTY_STRING,0);////////////////////////////////////////////
		break;
	case TYPE_D:
		if (rText.compare(Type))
		{
			TagNotAllowed(rText,Type);
			bAbort = true;
		}
		break;
	case VERSION_D:
		if (rText.compare(Version))
		{
			VersionMismatch(rText);
			bAbort = true;
		}
		break;
	//default:;		//Tags not supported are not managed, even if they have content associated
	};	//Switch
}

void CLanguageReader::Comment(const CP_StringType &rComment, DWORD dwAppData, bool &bAbort)
{
	std::cout << CP_ParserMsgs[LOG_PARSER_COMMENT] << rComment;
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;
}

void CLanguageReader::EndParse(DWORD dwAppData, bool bIsAborted)
{
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	if (bIsAborted) std::cout << CP_ParserMsgs[LOG_PARSER_END_PARSE];
};

UGKOS_ENA_UNUSED_VBLE_WARNINGS