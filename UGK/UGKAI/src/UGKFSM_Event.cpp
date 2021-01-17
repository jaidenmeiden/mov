/** Header with definitions needed for the management of FSM events

*	Prephix = UGKFSME_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#include "UGKFSM_Event.h"

using namespace UGK;

UGKS_String FSM_EventTypeName[FSM_MAX_EVENT] =
{
	"FSM_BASIC",
	"STACKABLE"
};

/*
*	\fn FSM_Event::FSM_Event(UGKS_String id, int event_tag, UGKS_String type)
*	\brief Initializes a new instance of the FSM_Event class.
*	\param id Name of this FSM_Event
*/
FSM_Event::FSM_Event(UGKS_String id)
{
	Event_id = id;
}

/*
*	\fn FSM_Event::FSM_Event(UGKS_String id, int event_tag, UGKS_String type)
*	\brief Initializes a new instance of the FSM_Event class.
*	\param id Name of this FSM_Event
*	\param event_tag Identifier tag of this FSM_Event
*	\param type "FSM_BASIC_EVENT" or "FSM_STACKABLE_EVENT"
*/
FSM_Event::FSM_Event(UGKS_String id, int event_tag, UGKS_String type)
{
	Event_id = id;
	Event_tag = event_tag;

	if (type.compare(FSM_EventTypeName[FSM_STACKABLE_EVENT]) == 0)
		Event_type = FSM_STACKABLE_EVENT;
	else if (type.compare(FSM_EventTypeName[FSM_BASIC_EVENT]) == 0)
		Event_type = FSM_BASIC_EVENT;
	else
	{
		Event_type = FSM_BASIC_EVENT;
	}
}

/*
*	\fn UGKS_String FSM_Event::getID()
*	\brief Get this FSM_Event identifier name
*	\return UGKS_String value
*/
UGKS_String FSM_Event::getID()
{
	return Event_id;
}

/*
*	\fn int FSM_Event::getEventTag()
*	\brief Get this FSM_Event identifier tag
*	\return int value
*/
int FSM_Event::getEventTag()
{
	return Event_tag;
}

/*
*	\fn int FSM_Event::getEventType()
*	\brief Get this FSM_Event type (FSM_BASIC_EVENT or FSM_STACKABLE_EVENT)
*	\return int value
*/
FSM_EVENT_TYPE FSM_Event::getEventType()
{
	return Event_type;
}
