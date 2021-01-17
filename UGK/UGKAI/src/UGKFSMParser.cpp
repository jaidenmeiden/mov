/**	Declaration of all the parser methods to understand the initialization files
*	@author Ramon Molla
*	@version 2012-08
*/

#include <UGKFSMParser.h>

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
	"STATE",
		"ON_ENTRY",
		"ON_DO",
		"ON_EXIT",
		"ON_EVENT",
			"TRANSITION",
				"PROBABILITY",
	// Internal tags common to all main tags
	"NAME",
	"DESTINATION",
	"TIME",			// 18
};

using namespace UGK;

UGKS_String CFSMP_ParserTags[FSM_MSG_MAX_LOGMSG] =
{
	"FSM",
	" error function does not exist"
};


void CFSMReader::Start()
{
	FSMReset();
	AssignTags(FSM_Tags, MAXTAGS_FSM);
	Type = CFSMP_ParserTags[FSM_MSG_FSM];	//Type of parser
	
	printf("Starting FSM Loader\n");
	
}

CFSMReader::CFSMReader(CP_StringType V, CP_StringType T)
{
	Start();
	Title = T;
	Version = V;
}

/**
@fn void CFSMReader::FSMReset()
Reset the state list and all internal counters or pointers
*/
void CFSMReader::FSMReset()
{
	state_list.clear();
	transitions_list.clear();
	eventos.clear();
}

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

	WriteLog(LOG_PARSER_START_TAG, TagString);

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	Token = Lexeme2Token(TagString); //revisar si la etiqueta es permitida y obtener el nombre de etiqueta
	// Comenzar una clasificacion y copiado de etiquetas segun su categoria
	switch (Top()){
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
		switch (Token){
		case HEAD_D:
		case BODY_D:
			Push(Token);
			break;
#ifdef _DEBUG	//Only works when Debug mode is activated
		default:
			msg = FSM_Tags[HTML_D];
			TagNotAllowed(TagString, msg);
#endif
		}
		break;

	case HEAD_D:
		switch (Token){
		case TITLE_D:
		case VERSION_D:
		case TYPE_D:
			Push(Token);
			break;
#ifdef _DEBUG	//Only works when Debug mode is activated
		default:
			TagNotAllowed(TagString, FSM_Tags[HEAD_D]);
#endif
		}
		break;

	case BODY_D:
		switch (Token){
		case STATE_INIT_FSM:
		case STATE_FSM:
			Push(Token);
			break;
#ifdef _DEBUG	//Only works when Debug mode is activated
		default:
			TagNotAllowed(TagString, FSM_Tags[BODY_D]);
#endif
		}
		break;

	case STATE_FSM:
		switch (Token){
		case NAME_FSM:
		case TIME_FSM:
		case ON_ENTRY_FSM:
		case ON_EXIT_FSM:
		case ON_EVENT_FSM:
		case ON_DO_FSM:
			Push(Token);
			break;
#ifdef _DEBUG	//Only works when Debug mode is activated
		default:
			TagNotAllowed(TagString, FSMP_Lexeme(STATE_FSM));
#endif
		}
		break;

	case ON_EVENT_FSM:	//We put first ON_EVENT_FSM because it has an especial subtag
		switch (Token){
		case TRANSITION_FSM:
			Push(Token);
			break;
		}
	case ON_ENTRY_FSM:
	case ON_EXIT_FSM:
	case ON_DO_FSM:
		switch (Token){
		case NAME_FSM:
			Push(Token);
			break;
#ifdef _DEBUG	//Only works when Debug mode is activated
		default:
			TagNotAllowed(TagString, FSMP_Lexeme(ON_EVENT_FSM));
			TagNotAllowed(TagString, FSMP_Lexeme(ON_ENTRY_FSM));
			TagNotAllowed(TagString, FSMP_Lexeme(ON_EXIT_FSM));
#endif
		}
		break;

	case TRANSITION_FSM:
		switch (Token){
		case NAME_FSM:
		case DESTINATION_FSM:
		case PROBABILITY_FSM:
			Push(Token);
			break;
#ifdef _DEBUG	//Only works when Debug mode is activated
		default:
			TagNotAllowed(TagString, FSMP_Lexeme(TRANSITION_FSM));
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
	int temp_func = -1;

	TagString = UGKS_CString2string(pTag->getTagName());

	WriteLog(LOG_PARSER_END_LABEL, TagString);

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	Token = Lexeme2Token(TagString);
	switch (Top()){
	case STATE_FSM:
		if (Top() == Token){
			latency = 0;
			Pop();
		}
		else Error = true;
		break;

	case TRANSITION_FSM:
		if (Top() == Token){
			if (newTransition)
			{
				p_transition = new FSM_Transition(temp_transition_ID, p_current_state, p_current_final_state, temp_transition_probability, eventos);
				transitions_list.push_back(p_transition);
				p_current_state->addTransition(p_transition);
				newTransition = false;
			}
			Pop();
		}
		else Error = true;
		break;
	case ON_ENTRY_FSM:
		if (Top() == Token)
		{
				Pop();
			
#ifdef _DEBUG	//Only works when Debug mode is activated

				msg += CFSMP_ParserTags[FSM_MSG_FUNC_NOT_EXIST];
				ErrorParser(msg);
				Error = true;
	
#endif
		}
		else{
			Error = true;
		}
		break;
	case ON_DO_FSM:
		if (Top() == Token){
			
				Pop();
		
#ifdef _DEBUG	//Only works when Debug mode is activated
			
				msg += CFSMP_ParserTags[FSM_MSG_FUNC_NOT_EXIST];
				ErrorParser(msg);
				Error = true;
#endif
		}
		else Error = true;
		break;
	case ON_EXIT_FSM:
		if (Top() == Token){
		
				Pop();
			
#ifdef _DEBUG	//Only works when Debug mode is activated
					msg += CFSMP_ParserTags[FSM_MSG_FUNC_NOT_EXIST];
				ErrorParser(msg);
				Error = true;
			
#endif
		}
		else Error = true;
		break;
	case ON_EVENT_FSM:
		if (Top() == Token) {
			eventos.clear();
			Pop();

#ifdef _DEBUG	//Only works when Debug mode is activated
			msg += CFSMP_ParserTags[FSM_MSG_FUNC_NOT_EXIST];
			ErrorParser(msg);
			Error = true;

#endif
		}
		else Error = true;
		break;
	case BODY_D:
		if (Top() == Token)
		{
			if (!isInertial)
			{
				FA = new FA_Classic(FA_title, true);
			}
			else if (isInertial)
			{
				FA = new FA_Inertial(FA_title, true);
			}
			FA->setStatesList(state_list);
			FA->setTransitionsList(transitions_list);
			FA->Start();
			Pop();	//Change to the previous state
		}
		else Error = true;
		break;
	case HTML_D:
	case HEAD_D:
	case TITLE_D:
	case VERSION_D:
	case TYPE_D:
	case STATE_INIT_FSM:
	case NAME_FSM:
	case TIME_FSM:
	case PROBABILITY_FSM:
	case DESTINATION_FSM:
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
		if (StateStack.size() >= 2)
		{
			unsigned int AuxState = Top();
			Pop();
			msg += FSM_Tags[Top()];
			Push(AuxState);
		}
		else msg += FSM_Tags[Top()];
		msg += CP_ParserMsgs[LOG_PARSER_END_TAG_ERROR2];
		ErrorParser(msg);
	}
#endif
}
/**
* @fn void CFSMReader::Characters(const HTML_String &rText, DWORD dwAppData, bool &bAbort)
* Function of Characters
* @param CString &rText: represents string
* @param DWORD dwAppData: represents the open file
* @param bool bAbort: represents if the parser is aborted
*/
void CFSMReader::Characters(const CP_StringType &rText, DWORD dwAppData, bool &bAbort)
{
	WriteLog(LOG_PARSER_TEXT, rText);

	UGKOS_UNUSED_VBLE_WARNINGS(dwAppData);
	bAbort = false;

	switch (Top()){
		//TEXT
	case TITLE_D:
		if (!rText.compare(Title))
		{
			ErrorParser(CP_ParserMsgs[LOG_PARSER_NOT_THIS_VG]);
			bAbort = true;
		}
		else
		{
			FA_title = rText;
		}
		break;
	case VERSION_D:
		if (!rText.compare(Version)){
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
		init_state = rText;
		break;
	case NAME_FSM:
		// Top refers to the "case:" Tag, subTop is the previous Tag
		if (subTop == STATE_FSM) 
		{
			cout << "detected state: " << rText << "\n";
			if (findState(rText) == 0)
			{
				cout << "State not found, defining: \n";
				if (init_state == rText)
					p_current_state = new FSM_State(rText, "YES", latency);
				else
					p_current_state = new FSM_State(rText, "NO", latency);
				state_list.push_back(p_current_state);
			}
			else 
			{
				p_current_state = getState(rText);
			}

			verboseStateList();
		}
		else if (subTop == ON_EVENT_FSM)
		{
			p_event = new FSM_Event(rText);
			eventos.push_back(p_event);
			cout << "  Created new event \n";
		}
		else if (subTop == TRANSITION_FSM)
		{
			temp_transition_ID = rText;
			newTransition = true;
			cout << "   Entering new transition\n";
		}
		break;
		
	case TIME_FSM:
		if (subTop == STATE_FSM)
		{
			latency = atof(UGKS_string2charstr(rText));
			p_current_state->setLatency(latency);
			cout << "State latency: " << latency << "\n";
			if (latency > 0)
				isInertial = true;
		}

	case DESTINATION_FSM:
		if (subTop == TRANSITION_FSM)
		{
			if (findState(rText) == 0)
			{
				cout << "     State " << rText << " not found, defining in destination: \n";
				if (init_state == rText)
					p_current_final_state = new FSM_State(rText, "YES", latency);
				else
					p_current_final_state = new FSM_State(rText, "NO", latency);
				state_list.push_back(p_current_final_state);
			}
			else
			{
				p_current_final_state = getState(rText);
			}
		}
		
		break;
	case PROBABILITY_FSM:
		if (subTop == TRANSITION_FSM)
		{
			temp_transition_probability = atof(UGKS_string2charstr(rText));
		}
		break;

		//PROPOSITO GENERAL
		/*case ORIGIN_FSM:
		temp_origin = atoi(UGKS_string2charstr(rText));
		break;*/

		/*case TYPE_FSM:
		temp_type = atoi(UGKS_string2charstr(rText));
		break;
		case FUNC_FSM:
		temp_name_function = rText;
		break;
		case EVENT_TRANSITION_FSM:
		temp_event_transition = rText;
		break;*/

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
	WriteLog(LOG_PARSER_COMMENTS, rComment);

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
		WriteLog(LOG_PARSER_FILE_PARSING_FINISHED, "");
}

FSM_State* CFSMReader::getState(CP_StringType id)
{
	for (list<FSM_State*>::iterator it = state_list.begin(); it != state_list.end(); it++)
		if ((*it)->getID() == id)
			return *it;
}

int CFSMReader::findState(CP_StringType id)
{
	for (list<FSM_State*>::iterator it = state_list.begin(); it != state_list.end(); it++)
		if ((*it)->getID() == id)
			return 1;
	return 0;
}

void CFSMReader::verboseStateList()
{
	for (list<FSM_State*>::iterator it = state_list.begin(); it != state_list.end(); it++)
		cout << "State: " << (*it)->getID() << "\n";	
}

FA_Classic* CFSMReader::getFA()
{
	return FA;
}



UGKOS_ENA_UNUSED_VBLE_WARNINGS