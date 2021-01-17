/**	Definition of the class KEYBOARD READER

*	Prefix: CSH_

*	@author Ramon Molla
*	@version 2016-06
*
*
*/

#include <UGKKeyboardParser.h>
#include <UGKString.h>
#include <UGKDefaultHTMLLabels.h>
#include <iostream>
#include <map>

/// This parser read the information from the html file Keyboard.html, its located in the rute SpaceInvaders\SI 2011\configuration
extern	DHTML_TagsArrayType DHTML_TagsArray;

///Collection of strings that are used to identify the keys pressed in the configuration HTML file 
UGKS_String CK_KEY_LEXEME[CK_KB_MAX_CTROL_INPUTS] =
{
	//Mouse buttons
	"LBUTTON",
	"RBUTTON",
	"CANCEL",
	"MBUTTON",

	//Control keys
	"BACK",
	"TAB",
	"ESCAPE",
	"SPACE",
	"PRIOR",
	"NEXT",
	"END",
	"HOME",
	"LEFT",
	"UP",
	"RIGHT",
	"DOWN",
	"SELECT",
	"PRINT",
	"EXECUTE",
	"SNAPSHOT",
	"INSERT",
	"DELETE",
	"HELP",
	"SLEEP",

	//Numeric Pad
	"NUMPAD0",
	"NUMPAD1",
	"NUMPAD2",
	"NUMPAD3",
	"NUMPAD4",
	"NUMPAD5",
	"NUMPAD6",
	"NUMPAD7",
	"NUMPAD8",
	"NUMPAD9",
	"MULTIPLY",
	"ADD",
	"SEPARATOR",
	"SUBTRACT",
	"DECIMAL",
	"DIVIDE",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"F16",
	"F17",
	"F18",
	"F19",
	"F20",
	"F21",
	"F22",
	"F23",
	"F24",

	"NUMLOCK",
	"SCROLL",
	"LSHIFT",
	"RSHIFT",
	"LCONTROL",
	"RCONTROL",
	"LMENU",
	"RMENU",
	"BROWSER_BACK",
	"BROWSER_FORWARD",
	"BROWSER_REFRESH",
	"BROWSER_STOP",
	"BROWSER_SEARCH",
	"BROWSER_FAVORITES",
	"BROWSER_HOME",

	//Multimedia control
	"VOLUME_MUTE",
	"VOLUME_DOWN",
	"VOLUME_UP",
	"MEDIA_NEXT_TRACK",
	"MEDIA_PREV_TRACK",
	"MEDIA_STOP",
	"MEDIA_PLAY_PAUSE",
	"LAUNCH_MAIL",
	"LAUNCH_MEDIA_SELECT",
	"LAUNCH_APP1",
	"LAUNCH_APP2",

	//Game Pads
	"GP_A",
	"GP_B",
	"GP_X",
	"GP_Y",
	"GP_RSHOULDER",
	"GP_LSHOULDER",
	"GP_LTRIGGER",
	"GP_RTRIGGER",
	"GP_DPAD_UP",
	"GP_DPAD_DOWN",
	"GP_DPAD_LEFT",
	"GP_DPAD_RIGHT",
	"GP_MENU",
	"GP_VIEW",
	"GP_LTHUMBSTICK_BUTTON",
	"GP_RTHUMBSTICK_BUTTON",
	"GP_LTHUMBSTICK_UP",
	"GP_LTHUMBSTICK_DOWN",
	"GP_LTHUMBSTICK_RIGHT",
	"GP_LTHUMBSTICK_LEFT",
	"GP_RTHUMBSTICK_UP",
	"GP_RTHUMBSTICK_DOWN",
	"GP_RTHUMBSTICK_RIGHT",
	"GP_RTHUMBSTICK_LEFT"
};

///Map that join not ascii symbols \number with the real asociated key
std::map <CP_StringType, CP_StringType> NoAsciiSymbols = { { "1", "VK_ESCAPE" }, { "2", "VK_F1" }, { "3", "VK_F2" }, { "4", "VK_F3" }, { "5", "VK_F4" }, { "6", "VK_F5" }, { "7", "VK_F12" }, { "8", "VK_OEM_7" }, { "9", "VK_RIGHT" }, { "10", "VK_LEFT" }, { "11", "VK_UP" }, { "12", "VK_SPACE" }, { "13", "VK_ADD" }, { "14", "VK_SUBTRACT" } };
///Necessary variables for the code
CP_StringType key;
CP_StringType action;
CP_StringType aux;
CP_StringType character;
CP_StringType cabecera = "CSIK_";
int period;
//Sensitive string tags
CP_LexemeType CKyP_Tags[K_MAXTAGS - MAXTAGS_D] =
{
	"ACTION",	//CONTENT
	"KEY",		//ID
	"LANGUAGE", //LANGUAGE
	"NEXUS",	//Amount of time to wait until the next character is released when the key is pressed continously
	"PERIOD"	//RESOURCE
};

CP_MessageType CKyP_KeyboardParserMsgs[] =
{
	"\". It is required a \"KEYBOARD\" file type.",
	"Keyboard"
};

using namespace UGK;
/// This method saves the nexus, i.e. the method receive the parameters character (the key pressed), key (the key pressed), 
/// action (the associated action to the pressed key) and period (amount of time in ms a pressed key lasts to send a new command to the game) 
/// from the parser and send these parameters to the SetNexus method of the UKGKeyboard class
void CKeyboardParser::SaveNexus(CP_StringType key, CP_StringType action, int period){Keyboard->SetNexus(action,key,period);}

CKeyboardParser::CKeyboardParser(CP_StringType V, CP_StringType T)
{
	AssignTags(CKyP_Tags, K_MAXTAGS);
	Title = T;
	Version = V;
	Type = CKyP_KeyboardParserMsgs[LOG_KEYBOARD_KEYBOARD];	//Type of parser. Do not change. It is always the same. Its nature is not changed
}


CKeyboardParser::CKeyboardParser(){
	AssignTags(CKyP_Tags, K_MAXTAGS);
	Type = CKyP_KeyboardParserMsgs[LOG_KEYBOARD_KEYBOARD];
	ISO639 = "";
}

UGKOS_DIS_UNUSED_VBLE_WARNINGS
void CKeyboardParser::BeginParse(DWORD dwAppData, bool &bAbort)
{
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

#ifdef _DEBUG
	WriteLog(LOG_PARSER_BEGIN_PARSE,"");
#endif
}

void CKeyboardParser::StartTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort)
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
	switch (Top())
	{
	case NIL_D://Starting and ending states
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
		case K_NEXUS: Push(Token); //Change to the state specified by the Token
			break;
		default: TagNotAllowed(TagString, DHTML_TagsArray[BODY_D]);
		}
		break;
	case K_NEXUS:
		switch (Token)
		{
		case K_KEY:
		case K_PERIOD:
		case K_ACTION:
			Push(Token);
			break;
		default: ErrorParser(CKyP_KeyboardParserMsgs[LOG_KEYBOARD_PARSER_ERROR_RESOURCE]);
		}
		break;
	case HEAD_D:		//HTML tag
		switch (Token)
		{
		case TYPE_D:
		case TITLE_D:
		case VERSION_D:
		case K_LANGUAGE:
			Push(Token); //Change to the state specified by the Token
			break;
		default: TagNotAllowed(TagString, DHTML_TagsArray[HEAD_D]);
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
			ErrorParser(CP_ParserMsgs[LOG_PARSER_ONLY_HEAD_OR_BODY]);
			TagError(TagString);	//DHTML_TagsArray[HTML_D]
		}
		break;
	default:;
	};
}

void CKeyboardParser::EndTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort)
{
	CP_StringType	msg;
	CP_LexemeType	TagString;
	CP_TokenType	Token;
	bool Error = false;

	TagString = UGKS_CString2string(pTag->getTagName());

#ifdef _DEBUG
	WriteLog(LOG_PARSER_END_TAG_END,TagString);
#endif

	//printf("Etiqueta fin: %s\n", pTag->getTagName());
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	Token = Lexeme2Token(TagString);
	switch (Top())
	{
	case BODY_D:
	case K_ACTION:
	case HEAD_D:
	case HTML_D:
	case K_KEY:
	case K_PERIOD:
	case K_LANGUAGE:
	case TITLE_D:
	case TYPE_D:
	case VERSION_D:	//The parser is at the very end of the initialization file					
		if (Top() == Token) Pop();	//Change to the previous state
		else Error = true;
		break;
	case K_NEXUS:
		/// When the tag nexus closes is the moment where we have all information about a key and we can send it to the UGKKeyboard class,
		/// for that we use the savenexus method
		SaveNexus(key, action, period);
		break;
	case NIL_D:
	case K_MAXTAGS:	//Closing a label when all the lables are closed is an error
#ifdef _DEBUG	//Only works when Debug mode is activated
		msg = TagString;
		msg += CP_ParserMsgs[LOG_PARSER_END_TAG_MAXTAGS];
		ErrorParser(msg);
#endif
		break;
	case CP_NO_TOKEN:	//This tag is for management purpouses only. There is no correspondence to any string label in the HTML file
#ifdef _DEBUG	//Only works when Debug mode is activated
		msg = TagString;
		msg += CP_ParserMsgs[LOG_PARSER_END_TAG_UNK];
		ErrorParser(msg);
#endif
		break;
	default:;
	};	//Switch

#ifdef _DEBUG	//Only works when Debug mode is activated
	if (Error)
	{
		msg = TagString;
		msg += CP_ParserMsgs[LOG_PARSER_END_TAG_ERROR1];

		if (StateStack.size() >= 2)
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

void CKeyboardParser::Characters(const CP_StringType &rText, DWORD dwAppData, bool &bAbort)
{
	static int     intAux, msgBox;

	if (bAbort) return;

#ifdef _DEBUG
	WriteLog(LOG_PARSER_TEXT,rText);
#endif

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;
	
	switch (Top())
	{
	case K_ACTION:
		/// When the parser read the label action we must read the rText where is located the action and we must add the prefix CSIK_, with this
		/// prefix we complement the lexemma read and we obtain the action
		action = cabecera.append(rText);
		break;
	case K_KEY:
		/// When the parser read the label key exist two possibilities, the key has the form \number, in this case we get the number and
		/// make the swap with the real key associated. The other case can be the key has the number ascii or directly the proper character of the key,
		/// in this case we read directly the value
		aux = rText.substr(0, 1);
		if (aux.compare("\\") == 0){
			key = rText.substr(1, rText.length());
			key=NoAsciiSymbols[key];
			character = key;
		}
		else{
			key = rText;
			character = rText;
		}
		break;
	case K_PERIOD:
		/// When the parser read the label period, we read the value and transform it to char and later to integer
		period = atoi(UGKS_string2charstr(rText));
		break;
	case K_LANGUAGE:
		ISO639 = rText;
		break;
	case TITLE_D:	//HTML tag
		if (rText.compare(Title))
		{
			ErrorParser(CP_ParserMsgs[LOG_PARSER_NOT_THIS_VG]);
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

void CKeyboardParser::Comment(const CP_StringType &rComment, DWORD dwAppData, bool &bAbort)
{
	std::cout << CP_ParserMsgs[LOG_PARSER_COMMENT] << rComment;
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;
}

void CKeyboardParser::EndParse(DWORD dwAppData, bool bIsAborted)
{
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	if (bIsAborted) std::cout << CP_ParserMsgs[LOG_PARSER_END_PARSE];
};

UGKOS_ENA_UNUSED_VBLE_WARNINGS