/** Header with definitions needed for the management of FSM events

*	Prephix = UGKFSME_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#ifndef UGKFSM_EVENT
#define UGKFSM_EVENT

#include <UGKString.h>

namespace UGK{

	typedef enum
	{
		FSM_BASIC_EVENT,
		FSM_STACKABLE_EVENT,
		FSM_MAX_EVENT
	} FSM_EVENT_TYPE;

	/// FSM_Event class used to create events in the loading phase
	class UGK_API FSM_Event
	{
	private:
		UGKS_String Event_id; ///< Identifier or name of this FSM_Event
		int Event_tag; ///< Identifier tag number of this FSM_Event
		FSM_EVENT_TYPE Event_type; ///< Type of FSM_Event (FSM_BASIC_EVENT, FSM_STACKABLE_EVENT or FSM_MAX_EVENT)

	public:
		/// Initializes a new instance of the FSM_Event class. 
		FSM_Event() {}
		/// Initializes a new instance of the FSM_Event class. 
		FSM_Event(UGKS_String id);
		/// Initializes a new instance of the FSM_Event class. 
		FSM_Event(UGKS_String id, int event_tag, UGKS_String type);
		/// Get this FSM_Event identifier name
		UGKS_String getID();
		/// Get this FSM_Event identifier tag
		int getEventTag();
		/// Get this FSM_Event type (FSM_BASIC_EVENT or FSM_STACKABLE_EVENT)
		FSM_EVENT_TYPE getEventType();
	};

}

#endif