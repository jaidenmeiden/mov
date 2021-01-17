/**	Declaration of all the parser methods to understand the initialization files
*	@author Ramon Molla
*	@version 2012-08
*/

#include <FSMParser.h>

#define FSMP_Lexeme(T) FSM_Tags[T-UNKNOWN_FSM]

/**
   * Finite State Machine Labels
   * @ Param MAXTAGS_FSM maximun amount of tags
   * @ Param FSM_TAG_MAX_LONG maximun length of tags
   * Label matrix allowed for the analyzer
*/
CP_LexemeType FSM_Tags[MAXTAGS_FSM] =
{
	UGKS_EMPTY_STRING,	//For management purpouses only
	"STATE_INIT",
	"STATE_CONT",
	"VEC_STATE",
		"STATE_NAME",
	"VEC_TRANSITION",
		"TRANSITION",
			"T_NAME",
			"T_ORIGIN",
			"T_DESTINATION",
	"VEC_ACTION",
		"ON_ENTRY",
			"ENTRY_TYPE",
			"ENTRY_NAME",
			"ENTRY_FUNC",
			"ENTRY_ORIGIN",
		"ON_DO",
			"DO_TYPE",
			"DO_NAME",
			"DO_FUNC",
			"DO_ORIGIN",
		"ON_EXIT",
			"EXIT_TYPE",
			"EXIT_NAME",
			"EXIT_FUNC",
			"EXIT_ORIGIN",
		"ON_EVENT",
			"EVENT_TYPE",
			"EVENT_NAME",
			"EVENT_FUNC",
			"EVENT_ORIGIN",
			"EVENT_TRANSITION"
};

using namespace UGK;

UGKS_String CFSMP_ParserTags[FSM_MSG_MAX_LOGMSG] =
{
	"FSM",
	" error function does not exist"
};

void CFSMReader::Start()
{
	cStateList = NULL;
	FSMReset();
	AssignTags(FSM_Tags, MAXTAGS_FSM);
	Type = CFSMP_ParserTags[FSM_MSG_FSM];	//Type of parser
}

CFSMReader::CFSMReader(CP_StringType V, CP_StringType T)
{
	Start();
	Title	= T;
	Version = V;
}

CFSMReader::~CFSMReader()
{
#ifdef _DEBUG	//Only works when Debug mode  is activated
	if (LogFile.is_open())
		LogFile.close();
#endif
	ResetState();
}

/**   
   @fn void CFSMReader::FSMReset()
   Reset the state list and all internal counters or pointers
*/
void CFSMReader::FSMReset()
{	
	n_states = init_state = it_state = 0;
	if (cStateList != NULL)
	{
		delete[] cStateList;
		cStateList = NULL;
	}
}

/**   
	* @fn void CFSMReader::addPublicFunction(const UGKS_String name, mFuncPtr funcPtr)
	* Adds a public function
	* @ Param name Name of the temporary function to create
	* @ Param funcPtr A pointer to the function to add temporarily
*/
void CFSMReader::addPublicFunction(const UGKS_String name, mFuncPtr funcPtr)
{

	_function temp; //se iniciar la variable temp

	temp.name = name; //se le asigna el nombre 
	temp.func=funcPtr;      //Se le asigna una funcion

	function_list.push_back(temp); //se inserta al final de una lista el temporal
}

/**   
   * @fn int CFSMReader::searchPublicFunction(const UGKS_String name)
   * Find a public function
   * @ Param name nombre de la funcion tempora
   * Retorna el numero del temporal si es que existe caso contrario devuelve un numero inexistente
*/
int CFSMReader::searchPublicFunction(const UGKS_String name)
{

	for(unsigned int i=0; i<function_list.size();i++){
		if(!function_list[i].name.compare(name)){
			return i;
		}
	}
	return -1;
}

#ifdef _DEBUG	//Only works when Debug mode  is activated
/**
* @fn void CFSMReader::TagError(const CP_MessageType Text)
* Function error etiqueta
   * @ Param CP_MessageType Text este es el texto a incorporar en el mensaje
   * Se muestra en pantalla el error generado
*/
void CFSMReader::TagError(const CP_MessageType Text)
{	CP_MessageType msg;

	if (LogFile)
	{
		msg = CP_ParserMsgs[LOG_PARSER_TAG_CHARACTER_TYPE];
		msg += Text;
		msg += CP_ParserMsgs[LOG_PARSER_TAG_NOT_COMPATIBLE];
		ErrorParser (msg);
	}
}
#endif

UGKOS_DIS_UNUSED_VBLE_WARNINGS
/**   
   * @fn void  CFSMReader::BeginParse(DWORD dwAppData, bool &bAbort)
   * @param DWORD dwAppData: represents the open file
   * @param bool bAbort: represents if the parser is aborted
   * This function starts the debugger parser
*/
void  CFSMReader::BeginParse(DWORD dwAppData, bool &bAbort)
{
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	WriteLog(LOG_PARSER_BEGIN_PARSE, "");

	ResetState();				//Stack reset
}

/**   
   * @fn void CFSMReader::StartTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort)
   * Function Start Tags. What to do when a new tag is reached. Typically stores a new state on the stack
   * @param CLiteHTMLTag pTag: represents HTML's Tags
   * @param DWORD dwAppData: represents the open file
   * @param bool bAbort: represents if the parser is aborted
*/
void CFSMReader::StartTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort)
{
	CP_StringType	msg;
	CP_LexemeType	TagString;
	CP_TokenType	Token;

	TagString = UGKS_CString2string(pTag->getTagName());

	WriteLog(LOG_PARSER_START_TAG,TagString);

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	Token = Lexeme2Token(TagString); //revisar si la etiqueta es permitida y obtener el nombre de etiqueta
	// Comenzar una clasificacion y copiado de etiquetas segun su categoria
	switch(Top()){
		case NIL_D:		//Starting and ending states
			if (HTML_D == Token){
				//It is a HTML_D file. Change to HTML_D state
				Push(HTML_D);
			}
	#ifdef _DEBUG	//Only works when Debug mode  is activated
			else{
				msg = CP_ParserMsgs[LOG_PARSER_TAG];
				msg += TagString;
				msg += CP_ParserMsgs[LOG_PARSER_NOT_HTML_TAG2];
				ErrorParser(msg);
			}
	#endif
			break;

		case HTML_D:
			switch(Token){
				case HEAD_D:
				case BODY_D:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					msg = FSM_Tags[HTML_D];
					TagNotAllowed (TagString, msg);
			#endif
			}
			break;

		case HEAD_D:
			switch(Token){
				case TITLE_D:
				case VERSION_D:
				case TYPE_D:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					TagNotAllowed (TagString, FSM_Tags[HEAD_D]);
			#endif
			}
			break;

		case BODY_D:
			switch(Token){
				case STATE_INIT_FSM:
				case STATE_CONT_FSM:
				case VEC_STATE_FSM:
				case VEC_TRANSITION_FSM:
				case VEC_ACTION_FSM:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					TagNotAllowed (TagString, FSM_Tags[BODY_D]);
			#endif
			}
			break;

		case VEC_STATE_FSM:
			switch(Token){
				case STATE_NAME_FSM:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					TagNotAllowed(TagString, FSMP_Lexeme(VEC_STATE_FSM));
			#endif
			}
			break;
		case VEC_TRANSITION_FSM:
			switch(Token){
				case TRANSITION_FSM:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					TagNotAllowed(TagString, FSMP_Lexeme(VEC_TRANSITION_FSM));
			#endif
			}
			break;
		case VEC_ACTION_FSM:
			switch(Token){
				case ON_ENTRY_FSM:
				case ON_DO_FSM:
				case ON_EXIT_FSM:
				case ON_EVENT_FSM:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					TagNotAllowed(TagString, FSMP_Lexeme(VEC_ACTION_FSM));
			#endif
			}
			break;
		case TRANSITION_FSM:
			switch(Token){
				case T_NAME_FSM:
				case T_ORIGIN_FSM:
				case T_DESTINATION_FSM:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					TagNotAllowed(TagString, FSMP_Lexeme(TRANSITION_FSM));
			#endif
			}
			break;
		case ON_ENTRY_FSM:
			switch(Token){
				case ENTRY_TYPE_FSM:
				case ENTRY_NAME_FSM:
				case ENTRY_FUNC_FSM:
				case ENTRY_ORIGIN_FSM:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					TagNotAllowed(TagString, FSMP_Lexeme(ON_ENTRY_FSM));
			#endif
			}
			break;
		case ON_DO_FSM:
			switch(Token){
				case DO_TYPE_FSM:
				case DO_NAME_FSM:
				case DO_FUNC_FSM:
				case DO_ORIGIN_FSM:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					TagNotAllowed(TagString, FSMP_Lexeme(ON_DO_FSM));
			#endif
			}
			break;
		case ON_EXIT_FSM:
			switch(Token){
				case EXIT_TYPE_FSM:
				case EXIT_NAME_FSM:
				case EXIT_FUNC_FSM:
				case EXIT_ORIGIN_FSM:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					TagNotAllowed(TagString, FSMP_Lexeme(ON_EXIT_FSM));
			#endif
			}
			break;
		case ON_EVENT_FSM:
			switch(Token){
				case EVENT_TYPE_FSM:
				case EVENT_NAME_FSM:
				case EVENT_FUNC_FSM:
				case EVENT_ORIGIN_FSM:
				case EVENT_TRANSITION_FSM:
					Push(Token);
					break;
			#ifdef _DEBUG	//Only works when Debug mode is activated
				default:
					TagNotAllowed(TagString, FSMP_Lexeme(ON_EVENT_FSM));
			#endif
			}
			break;
	};
}

/**   
   * @fn void CFSMReader::EndTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort)
   * Function End Token. What to do when an ending tag is reached. Typically pops the state from the stack
   * @param CLiteHTMLTag pTag: represents HTML's Tags
   * @param DWORD dwAppData: representa the open file
   * @param bool bAbort: represents if the parse is aborted
   * This function define the end of an Allowed tag
*/
void CFSMReader::EndTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort)
{
	CP_MessageType	msg;
	CP_LexemeType	TagString;
	CP_TokenType	Token;
	bool Error = false;
	int temp_func=-1;

	TagString = UGKS_CString2string(pTag->getTagName());

	WriteLog(LOG_PARSER_END_LABEL,TagString);

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	Token = Lexeme2Token(TagString);
	switch(Top()){
		case TRANSITION_FSM:
			if (Top() == Token){
				cStateList[temp_origin].addTransition(temp_event, &cStateList[temp_destination]);
				Pop();
			}
			else Error = true;
			break;
		case ON_ENTRY_FSM:
			if (Top() == Token)
			{
				temp_func=searchPublicFunction(temp_name_function);
				if(-1 != temp_func)
				{
					cStateList[temp_origin].addAction(eOnEntry, (eType)temp_type, temp_name, function_list[temp_func].func);
					Pop();
				}
			#ifdef _DEBUG	//Only works when Debug mode is activated
				else
				{
					msg = temp_name_function;
					msg += CFSMP_ParserTags[FSM_MSG_FUNC_NOT_EXIST];
					ErrorParser( msg);
					Error=true;
				}
			#endif
			}
			else{
				Error = true;
			}
			break;
		case ON_DO_FSM:
			if (Top() == Token){
				temp_func=searchPublicFunction(temp_name_function);
				if(-1 != temp_func)
				{
					cStateList[temp_origin].addAction(eDo, (eType)temp_type, temp_name, function_list[temp_func].func);
					Pop();
				}
			#ifdef _DEBUG	//Only works when Debug mode is activated
				else
				{
					msg = temp_name_function;
					msg += CFSMP_ParserTags[FSM_MSG_FUNC_NOT_EXIST];
					ErrorParser( msg);
					Error=true;
				}
			#endif
			}
			else Error = true;
			break;
		case ON_EXIT_FSM:
			if (Top() == Token){
				temp_func=searchPublicFunction(temp_name_function);
				if(-1 != temp_func)
				{
					cStateList[temp_origin].addAction(eOnExit, (eType)temp_type, temp_name, function_list[temp_func].func);
					Pop();
				}
			#ifdef _DEBUG	//Only works when Debug mode is activated
				else
				{
					msg = temp_name_function;
					msg += CFSMP_ParserTags[FSM_MSG_FUNC_NOT_EXIST];
					ErrorParser( msg);
					Error=true;
				}
			#endif
			}
			else Error = true;
			break;
		case ON_EVENT_FSM:
			if (Top() == Token){
				temp_func=searchPublicFunction(temp_name_function);
				if(-1 != temp_func)
				{
					cStateList[temp_origin].addAction(eOnEvent, (eType)temp_type, temp_name, temp_event_transition, function_list[temp_func].func);
					Pop();
				}
			#ifdef _DEBUG	//Only works when Debug mode is activated
				else
				{
					msg = temp_name_function;
					msg += CFSMP_ParserTags[FSM_MSG_FUNC_NOT_EXIST];
					ErrorParser( msg);
					Error=true;
				}
			#endif
			}
			else Error = true;
			break;
		case HTML_D:
		case HEAD_D:
		case TITLE_D:
		case VERSION_D:
		case TYPE_D:
		case BODY_D:
		case STATE_INIT_FSM:
		case STATE_CONT_FSM:
		case VEC_STATE_FSM:
		case STATE_NAME_FSM:
		case VEC_TRANSITION_FSM:
		case T_NAME_FSM:
		case T_ORIGIN_FSM:
		case T_DESTINATION_FSM:
		case VEC_ACTION_FSM:
		case ENTRY_TYPE_FSM:
		case ENTRY_NAME_FSM:
		case ENTRY_FUNC_FSM:
		case ENTRY_ORIGIN_FSM:
		case DO_TYPE_FSM:
		case DO_NAME_FSM:
		case DO_FUNC_FSM:
		case DO_ORIGIN_FSM:
		case EXIT_TYPE_FSM:
		case EXIT_NAME_FSM:
		case EXIT_FUNC_FSM:
		case EXIT_ORIGIN_FSM:
		case EVENT_TYPE_FSM:
		case EVENT_NAME_FSM:
		case EVENT_FUNC_FSM:
		case EVENT_ORIGIN_FSM:
		case EVENT_TRANSITION_FSM:
			if (Top() == Token) Pop();	//Change to the previous state
			else Error = true;
			break;
		case UNKNOWN_FSM:
		#ifdef _DEBUG	//Only works when Debug mode is activated
			msg = TagString;
			msg += CP_ParserMsgs[LOG_PARSER_END_TAG_UNK];
			ErrorParser(msg);
		#endif
			break;
		case NIL_D:
			break;
	};
#ifdef _DEBUG	//Only works when Debug mode is activated
	if (Error)
	{
		msg = TagString;
		msg += CP_ParserMsgs[LOG_PARSER_END_TAG_ERROR2];
		if (StateStack.size()>=2)
		{
			unsigned int AuxState = Top();
			Pop();
			msg += FSM_Tags[Top()];
			Push(AuxState);
		}
		else msg += FSM_Tags[Top()];
		msg +=  CP_ParserMsgs[LOG_PARSER_END_TAG_ERROR2];
		ErrorParser(msg);
	}
#endif
}
/**   
   * @fn void CFSMReader::Characters(const HTML_String &rText, DWORD dwAppData, bool &bAbort)
   * Function of Characters
   * @param CString &rText: represents string
   * @param DWORD dwAppData: represents de open file
   * @param bool bAbort: represents if the parser is aborted
*/
void CFSMReader::Characters(const CP_StringType &rText, DWORD dwAppData, bool &bAbort)
{

	WriteLog(LOG_PARSER_TEXT,rText);

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	switch(Top()){
		//TEXT
		case TITLE_D:
			if (rText.compare(Title))
			{
				ErrorParser(CP_ParserMsgs[LOG_PARSER_NOT_THIS_VG]);
				bAbort = true;
			}
			break;
		case VERSION_D:
			if (rText.compare(Version)){
				VersionMismatch(rText);
				bAbort = true;
			}
			break;
		case TYPE_D:
			if (rText.compare(Type))
			{
				FileTypeMismatch(rText, CFSMP_ParserTags[FSM_MSG_FSM]);
				bAbort = true;
			}
			break;
		case STATE_INIT_FSM:
			init_state = atoi(UGKS_string2charstr(rText));
			break;
		case STATE_CONT_FSM:
			n_states = atoi(UGKS_string2charstr(rText));
			cStateList=new State[n_states];
			break;
		case STATE_NAME_FSM:
			cStateList[it_state].setName(rText);
			it_state++;
			break;
			//PROPOSITO GENERAL
		case T_NAME_FSM:
		case ENTRY_NAME_FSM:
		case DO_NAME_FSM:
		case EXIT_NAME_FSM:
			temp_name = rText;
			break;
		case EVENT_NAME_FSM:
			temp_event = rText;
			break;
		case T_ORIGIN_FSM:
		case ENTRY_ORIGIN_FSM:
		case DO_ORIGIN_FSM:
		case EXIT_ORIGIN_FSM:
		case EVENT_ORIGIN_FSM:
			temp_origin = atoi(UGKS_string2charstr(rText));
			break;
		case T_DESTINATION_FSM:
			temp_destination = atoi(UGKS_string2charstr(rText));
			break;
		case ENTRY_TYPE_FSM:
		case DO_TYPE_FSM:
		case EXIT_TYPE_FSM:
		case EVENT_TYPE_FSM:
			temp_type = atoi(UGKS_string2charstr(rText));
			break;
		case ENTRY_FUNC_FSM:
		case DO_FUNC_FSM:
		case EXIT_FUNC_FSM:
		case EVENT_FUNC_FSM:
			temp_name_function = rText;
			break;
		case EVENT_TRANSITION_FSM:
			temp_event_transition = rText;
			break;
	};
}

/**   
   * @fn void CFSMReader::Comment(const HTML_String &rComment, DWORD dwAppData, bool &bAbort)
   * Function Comments
   * @param HTML_String &rComment: represents the comment string
   * @param DWORD dwAppData: represents the open file
   * @param bool bAbort: represents if the parser is aborted
   * This function defines the comments for the tags
*/
void CFSMReader::Comment(const CP_StringType &rComment, DWORD dwAppData, bool &bAbort)
{
	WriteLog(LOG_PARSER_COMMENTS,rComment);

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;
}
/**   
   * @fn EndParse
   * Function to finish de parser
   * @param DWORD dwAppData: represents the 6k4emjopen file
   * @param bool bAbort: represents if the parser is aborted
   * This function closes the file that abort the parser
*/
void CFSMReader::EndParse(DWORD dwAppData, bool bIsAborted)
{
	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);

	if (bIsAborted)
		WriteLog(LOG_PARSER_FILE_PARSING_FINISHED,"");
}

UGKOS_ENA_UNUSED_VBLE_WARNINGS