/** DEVICES READER
*	@author Sonia Cardenas
*	@author David Peris
*	@version 2015-05-06
*/

#include <UGKDeviceParser.h>
#include <UGKKeyboardParser.h>
#include <UGKHTMLReader.h>
#include <UGKPhysics.h>
#include <vector>
#include <UGKHardwareList.h>

//GCHARS_CharacterType	CDevP_CharType; //se define la variables Tipo de Caracter
UGKPHY_CINEMATIC_ACTION	CDevP_CinematicAction;
unsigned			int NumberDevices;

extern char* CHW_HWType[CHW_MAX_HW_TYPE];	///chars linked to the enum CHW_HARDWARE_TYPE

/**   
   @fn CDevP_Tags
   @param MAXTAGS_DEV maximum number of tags
   @param CDevP_TAG_MAX_LONG the maximum length of the labels
   An array of allowed tags for the analyzer
*/
CP_LexemeType CDevP_OwnTags[MAXTAGS_DEV-MAXTAGS_D] = 
{
	"BUTTONS",
	"CONFIG",
	"DEVICE",
	"ID",
	"NAME",
	"RESOLUTION",
	"SENSITIVITY",
	"VIBRATION",
	"X",
	"Y"
};

using namespace UGK;

CDeviceParser::CDeviceParser()
{
	Type = "InputDevices";	//Type of parser
	ResetState();
	Push(NIL_D);
	AssignTags (CDevP_OwnTags, MAXTAGS_DEV);
	ActiveHw = CHW_NO_HW;		//La lista esta vacia
	HW = NULL;
}

UGKOS_DIS_UNUSED_VBLE_WARNINGS
/**   
   @fn BeginParse 
   @param DWORD dwAppData represents the open file
   @param bool bAbort is aborted if parser 
   This function starts the debugger parser
*/
void CDeviceParser::BeginParse(DWORD dwAppData, bool &bAbort)
{
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

#ifdef _DEBUG
	WriteLog(LOG_PARSER_BEGIN_PARSE,"");
#endif
}

/**   
   @fn StartTag
   @param CLiteHTMLTag pTag represents HTML tags
   @param DWORD dwAppData represents the open file
   @param bool bAbort represents whether the parser is aborted    
   This function defines the HTML tags permitted in the matrix of the analyzer and classified by categories or groups
*/
void CDeviceParser::StartTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort)
{
	CP_LexemeType	TagString;
	CP_TokenType	Token;

	TagString = UGKS_CString2string(pTag->getTagName());

#ifdef _DEBUG
	WriteLog(LOG_PARSER_START_TAG,TagString);
#endif

	Token = Lexeme2Token(TagString);

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	switch(Token)
	{
	case NIL_D://Starting and ending states
				break;
	case BODY_D:
	case HEAD_D:
	case HTML_D:
	case TITLE_D:		
 	case TYPE_D:
	case VERSION_D:
	case BUTTONS_D:
	case DEVICE_D:
	case ID_D:
	case NAME_D:
	case RESOLUTION_D:
	case SENSITIVITY_D:
	case VIBRATION_D:
	case X_D:
	case Y_D:
	case CONFIG_D:
		Push(Token);
		break;
	default:;
	};
}

/**   
   @fn EndTag
   @param CLiteHTMLTag pTag represents HTML tags
   @param DWORD dwAppData represents the open file
   @param bool bAbort represents whether the parser is aborted    
   This function defines the end of a label acuardo permitted its category, If not shown an error message
*/
void CDeviceParser::EndTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort)
{
	CP_MessageType msg;
	CP_LexemeType	TagString;
	CP_TokenType	Token;
	bool Error = false;

	TagString = UGKS_CString2string(pTag->getTagName());

#ifdef _DEBUG
	WriteLog(LOG_PARSER_END_TAG_END, TagString);
#endif

	//printf("Etiqueta fin: %s\n", pTag->getTagName());
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	Token = Lexeme2Token(TagString);

	switch(Top())
	{
	case BODY_D:
	case HEAD_D:
	case HTML_D:
	case TITLE_D:
	case TYPE_D:
	case VERSION_D:
	case BUTTONS_D:
	case DEVICE_D:
	case ID_D:
	case NAME_D:
	case RESOLUTION_D:
	case SENSITIVITY_D:
	case VIBRATION_D:
	case X_D:
	case Y_D:
	case CONFIG_D:
		//The parser is at the very end of the initialization file
		if (Top() == Token) Pop();	//Change to the previous state
		else Error = true;
		break;
	 case NIL_D:
	 case MAXTAGS_DEV:
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
	{
		msg = TagString;
		msg += CP_ParserMsgs[LOG_PARSER_END_TAG_ERROR2];

		if (StateStack.size()>=2)
		{
			unsigned int AuxState = Top();
			Pop();
			if (Top() >= MAXTAGS_D)
				msg += Token2Lexeme(Top());
			Push(AuxState);
		}
		else if (Top() >= MAXTAGS_D)
				msg += Token2Lexeme(Top());
 		msg += CP_ParserMsgs[LOG_PARSER_END_TAG_ERROR2];
		ErrorParser(msg);
	}
#endif
}

/**   
   @fn Characters
   @param CString &rText represents the text
   @param DWORD dwAppData represents the open file
   @param bool bAbort represents if the the parser is aborted
   This function defines the text for labels for the game   
   Otherwise it shows an error message
*/
void CDeviceParser::Characters(const UGKS_String &rText, DWORD dwAppData, bool &bAbort)
{
	UGKS_String aux = rText;
	//printf("parsing: %s\n",aux);

	if (bAbort) return;

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

#ifdef _DEBUG
	if (!isspace(rText[0]))
		WriteLog(LOG_PARSER_TEXT, aux);
	WriteLog(LOG_PARSER_TOP,Token2Lexeme((CP_TokenType)Top()));
	WriteLog(LOG_PARSER_SUBTOP, Token2Lexeme(SubTop()));
#endif

	switch(Top())
	{
	/*	In this case, A new node for the Scene Graph is performed.
		Type, casting and dynamic memory allocation has to be done
	*/
	case BODY_D:///Generic treatment. Only for management purpouses. This parser is only sensitive to specific "names"
	case DEVICE_D:///Generic treatment. Only for management purpouses. This parser is only sensitive to specific "names"
	case HTML_D:   //HTML tag
	case HEAD_D:   //HTML tag
		break;
	case NAME_D:///Comprueba si es el NAME perteneciente a DEVICE y añade el nuevo Hardware a la lista de Devices.
		if(SubTop() == DEVICE_D){
			bool nuevo = FALSE;
			for(int i = 0; i < CHW_MAX_HW_TYPE && !nuevo; i++)
			{
				if (0 == aux.compare(CHW_HWType[i]))
				{
					bool nuevo = TRUE;
					ActiveHw = (CHW_HARDWARE_TYPE)i;
					HW = DeviceManager->NewHW(ActiveHw);
					if (HW != NULL) DeviceManager->pushBack(HW);
				}	
			}
			#ifdef _DEBUG
				if (!nuevo)
				{
					WriteLog(LOG_PARSER_LABEL, aux);
					WriteLog(LOG_PARSER_NO_HW,"");
				}
			#endif
		}
		break;
	case ID_D:
		if (ActiveHw == CHW_IN_JOYSTICK)
			((CJoystick*)HW)->setIndex( atoi(UGKS_string2charstr(aux)));
		else if (ActiveHw == CHW_IN_GAMECONTROLLER)
			((CGameController*)HW)->setIndex(atoi(UGKS_string2charstr(aux)));
#ifdef CHW_USE_WIIMOTE
		else if (ActiveHw == CHW_IN_WIIMOTE)
			((CWiiMote*)HW)->SetUid(atoi(UGKS_string2charstr(aux)));
#endif
		break;
	case X_D:
		if (ActiveHw == CHW_IN_WEBCAM)
			((UGKWebCam*)HW)->XRes = atoi(UGKS_string2charstr(aux));
		else if (ActiveHw == CHW_GRAPHIC)
			((CGraphicCard*)HW)->DeskTop.Width = atoi(UGKS_string2charstr(aux));
		break;
	case Y_D:
		if (ActiveHw == CHW_IN_WEBCAM)
			((UGKWebCam*)HW)->YRes = atoi(UGKS_string2charstr(aux));
		else if (ActiveHw == CHW_GRAPHIC)
			((CGraphicCard*)HW)->DeskTop.Height = atoi(UGKS_string2charstr(aux));
		break;
	case VIBRATION_D:
		if( ActiveHw == CHW_IN_JOYSTICK )
			((CJoystick*)HW)->setVibration( aux.compare("YES") == 0 );
		else if (ActiveHw == CHW_IN_GAMECONTROLLER)
			((CGameController*)HW)->setVibration(aux.compare("YES") == 0);
		break;
	case SENSITIVITY_D:
		if (ActiveHw == CHW_IN_MOUSE)
			((CMouse*)HW)->sensitivity = atof(UGKS_string2charstr(aux));
#ifdef CHW_USE_KINECT
		else if (ActiveHw == CHW_IN_KINECT)
			((CKinect*)HW)->sensibility = atof(UGKS_string2charstr(aux));
#endif
		break;
	case BUTTONS_D:
		if (ActiveHw == CHW_IN_JOYSTICK)
			((CJoystick*)HW)->setButtons(atoi(UGKS_string2charstr(aux)));
		break;
	case CONFIG_D:
		if (ActiveHw == CHW_IN_KEYBOARD)
			((CKeyboard*)HW)->SetConfigFolder(aux);
		break;
	case RESOLUTION_D:
		break;
	case TITLE_D:   //HTML tag
	case TYPE_D:
	case VERSION_D:
		break;
	default:;		//Tags not supported are not managed, even if they have content associated
	};	//Switch
}

/**   
   @fn Comment
   @param CString &rComment represents the string of comments
   @param DWORD dwAppData represents the open file
   @param bool bAbort represents if the parser is aborted    
   This function defines Entries for tags
*/
void CDeviceParser::Comment(const UGKS_String &rComment, DWORD dwAppData, bool &bAbort)
{
#ifdef _DEBUG
	UGKS_String aux = rComment;
	WriteLog(LOG_PARSER_COMMENTS, aux);
#endif
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;
}

/**   
   @fn EndParse
   @param DWORD dwAppData represents the open file
   @param bool bAbort represents if the parser is aborted  
   This function closes the file if the parser is aborted  
*/
void CDeviceParser::EndParse(DWORD dwAppData, bool bIsAborted)
{
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	if (bIsAborted) printf ("Se ha acabado la interpretación del fichero.\n");
};