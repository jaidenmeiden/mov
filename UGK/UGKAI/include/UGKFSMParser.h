/**	Class that loads the values by default in the very beginning of the game

*	Prefix FSM_: Class Initialization Parser

*	@author Jorge Izquierdo Ciges
*	@version 2007-09-11
*/

#include "UGKHTMLParser.h"

#include "UGKFA_Classic.h"
#include "UGKFA_Inertial.h"
#include "UGKFSM_State.h"
#include "UGKFSM_Event.h"

#include <vector>
#include <iostream>

#ifndef FSTREAM_INITIALIZED
#define FSTREAM_INITIALIZED
#include <fstream>
#endif

#ifndef FSMPARSER_DEFINED /// Macro Parser is erased
#define FSMPARSER_DEFINED /// Macro Parser is defined

#define CSIG_MAX_LEVELS	99	// Max levels if Initialization.HTML_D is not correct

/** \typedef FSM_TagType

*	Types of tags the initialization parser can match during the parsing
*	They can be used also as states of of the stack machine (parser) during the parsing
*/
typedef enum {
	UNKNOWN_FSM = MAXTAGS_D,
	STATE_INIT_FSM,
	STATE_FSM,
	ON_ENTRY_FSM,	// This tag is for executing code when reaching a state
	ON_DO_FSM,		// This tag is for executing code inside a state
	ON_EXIT_FSM,	// This tag is for executing code when leaving a state
	ON_EVENT_FSM,	// This tag is for state management only
	TRANSITION_FSM,
	PROBABILITY_FSM,
	NAME_FSM,
	DESTINATION_FSM, 
	TIME_FSM,		// 18
	MAXTAGS_FSM		///<This tag is for management purpouses only. There is no correspondence to any string label in the HTML_D file
} FSM_TagType;

typedef enum {
	FSM_MSG_FSM,
	FSM_MSG_FUNC_NOT_EXIST,
	FSM_MSG_MAX_LOGMSG
} CFSMP_LogMsg;

/**
@class CFSMReader
* Define the Finite State Machine class reading with bypass or class inheritance ILiteHTMLReaderEvents
* Where is the constructor and destructor of the class and are also actions for the parser based on FSM_TagType

*	@version 2007-09-11
*/

namespace UGK
{
	class UGK_API  CFSMReader : public CHTMLParser
	{
	private:

		FA_Classic* FA;							///< FA constructed by the FSMparser that is given to the AI Manager
		CP_StringType	FA_title;
		/*list<FSM_State> state_list;			///< List in order to associate a number to each state
		list<FSM_Event*> eventos;				///< List in order to store all events of an state
		UGKS_String FA_id;*/

		list<FSM_State*> state_list;			///< List in order to associate a number to each state
		list<FSM_Transition*> transitions_list;
		FSM_State* p_current_state;
		FSM_State* p_current_final_state;
		FSM_Event* p_event;					///< List in order to store all events of an state
		list<FSM_Event*> eventos;				///< List in order to store all events of an state

		//FSM states
		//TODO: Remove these following four attributes and change them by "FSM *AI;" and refactorize
		CP_StringType	init_state;
		double latency = 0;
		CP_StringType current_state_id;
		//FSM_Event current_temp_Event;
		FSM_Transition* p_transition;
		bool newTransition;
		bool isInertial = false;
		

		//FSM_State constructor attributes
		CP_StringType temp_state_name;
		CP_StringType temp_initial_flag;

		//FSM_Event constructor atributes
		CP_StringType temp_event_id;

		//FSM_Transition constructor atributes
		CP_StringType temp_transition_ID;
		CP_StringType temp_transition_final_state;
		int temp_transition_probability;

		/// Temporary variables are defined for the analyzer
		CP_StringType	temp_name, temp_event, temp_event_transition;

		int		temp_type,
			temp_origin,
			temp_destination,
			temp_probability;
			
		void BeginParse(DWORD dwAppData, bool &bAbort); /// Begin parse
		void StartTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort); /// start tag
		void EndTag(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort); /// end the tag
		void Characters(const CP_StringType &rText, DWORD dwAppData, bool &bAbort); /// characters
		void Comment(const CP_StringType &rComment, DWORD dwAppData, bool &bAbort); /// comments
		void EndParse(DWORD dwAppData, bool bIsAborted); /// end parse

		FSM_State* getState(CP_StringType id);
		int findState(CP_StringType id);

		void verboseStateList();

	public:
		
		/*inline int		getFSMNumStates()	{ return n_states; };
		inline int		getFSMInitState()	{ return init_state; }
		inline FSM_State *	getFSMStatesVector()	{ return cStateList; }*/
		void			FSMReset();
		void			Start();
		
		///Constructor
		CFSMReader(){ Start(); }
		CFSMReader(CP_StringType V, CP_StringType T);

		FA_Classic* getFA();
	};
}
#endif
