/**	Class that loads the values by default in the very beginning of the game

*	Prefix FSM_: Class Initialization Parser

*	@author Jorge Izquierdo Ciges
*	@version 2007-09-11
*/

#include <UGKHTMLParser.h>
#include "State.h"
#ifndef FSTREAM_INITIALIZED
#define FSTREAM_INITIALIZED
#include <fstream>
#endif

#ifndef FSMPARSER_DEFINED /// Macro Parser is erased
#define FSMPARSER_DEFINED /// Macro Parser is defined

#define FSM_DEBUG	//Class HTML_D Parser Debug activated

#define CSIG_MAX_LEVELS	99	// Max levels if Initialization.HTML_D is not correct

/** \typedef FSM_TagType

*	Types of tags the initialization parser can match during the parsing
*	They can be used also as states of of the stack machine (parser) during the parsing
*/
typedef enum {
	UNKNOWN_FSM = MAXTAGS_D,
	STATE_INIT_FSM,
	STATE_CONT_FSM,
	VEC_STATE_FSM,
		STATE_NAME_FSM,
	VEC_TRANSITION_FSM,
		TRANSITION_FSM,
			T_NAME_FSM,
			T_ORIGIN_FSM,
			T_DESTINATION_FSM,
	VEC_ACTION_FSM,
		ON_ENTRY_FSM,
			ENTRY_TYPE_FSM,
			ENTRY_NAME_FSM,
			ENTRY_FUNC_FSM,
			ENTRY_ORIGIN_FSM,
		ON_DO_FSM,
			DO_TYPE_FSM,
			DO_NAME_FSM,
			DO_FUNC_FSM,
			DO_ORIGIN_FSM,
		ON_EXIT_FSM,
			EXIT_TYPE_FSM,
			EXIT_NAME_FSM,
			EXIT_FUNC_FSM,
			EXIT_ORIGIN_FSM,
		ON_EVENT_FSM,
			EVENT_TYPE_FSM,
			EVENT_NAME_FSM,
			EVENT_FUNC_FSM,
			EVENT_ORIGIN_FSM,
			EVENT_TRANSITION_FSM,//37
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

		struct _function{
				mFuncPtr		func;
				CP_StringType	name;
		};
		std::vector<_function> function_list;
		int searchPublicFunction(const CP_StringType name);

		//FSM states
		//TODO: Remove these following four attributes and change them by "FSM *AI;" and refactorize
		int		n_states;
		int		init_state;
		State	*cStateList;	//FSM constructed by the FSM parser that is given to the AI Manager
		int		it_state;

		/// Temporary variables are defined for the analyzer
		STT_NameType	temp_name_function;
		STT_NameType	temp_name;
		STT_EventType	temp_event,	
						temp_event_transition;

		int		temp_type,
				temp_origin,
				temp_destination;
	protected:

		void BeginParse	(DWORD dwAppData, bool &bAbort); /// Begin parse
		void StartTag	(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort); /// start tag
		void EndTag		(CLiteHTMLTag *pTag, DWORD dwAppData, bool &bAbort); /// end the tag
		void Characters	(const CP_StringType &rText, DWORD dwAppData, bool &bAbort); /// characters
		void Comment	(const CP_StringType &rComment, DWORD dwAppData, bool &bAbort); /// comments
		void EndParse	(DWORD dwAppData, bool bIsAborted); /// end parse


	public:

		void TagError	(const CP_MessageType Text); /// Etiquetas erroneas
	
		void Start();

		void addPublicFunction	(const CP_StringType name, mFuncPtr funcPtr);

		inline int		getFSMNumStates		()	{return n_states;};
		inline int		getFSMInitState		()	{return init_state;};
		inline State *	getFSMStatesVector	()	{return cStateList;};
		void			FSMReset();

		void Init(CP_StringType FileName);

		///Constructor
		CFSMReader(){ Start(); };
		CFSMReader(CP_StringType V, CP_StringType T);

		///Destructor
		~CFSMReader();
	};
}
#endif
