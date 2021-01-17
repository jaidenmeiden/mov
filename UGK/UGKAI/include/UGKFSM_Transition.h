/** Header with definitions needed for the management of FSM transitions

*	Prephix = UGKFSMT_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Mollá 
				Joan Sancho

*	@version 2016-02
*/

#ifndef UGKFSM_TRANSITION
#define UGKFSM_TRANSITION

#include <UGKFSM_Event.h>
#include <UGKFSM_State.h>

namespace UGK {

	typedef std::list<FSM_Event*> UGKFSMT_EventList;

	class UGK_API FSM_Transition
	{
	private:
		UGKS_String transitionName; ///< Name that identifies this transitio
		int transition_TAG; ///< Transition tag identifier
		int action_TAG; ///< Action tag identifier of this transition
		FSM_State* origin; ///< State origin from which this transition leaves
		FSM_State* final; ///< State final to which this transition arrives
		UGKFSMT_EventList EventsList; ///< Collection of events that enable this transition
		double probability; ///< Probability of execution of this transition. Only used if the FA is probabilistic

	public:
		/// Initializes a new instance of the Transition class. 
		FSM_Transition();
		/// Initializes a new instance of the Transition class. 
		FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int probability, UGKFSMT_EventList EventsList);
		/// Initializes a new instance of the Transition class. 
		FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int transition_tag, int action_tag, UGKFSMT_EventList EventsList);
		/// Initializes a new instance of the Transition class.  
		FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int transition_tag, int action_tag, UGKFSMT_EventList EventsList, int probability);
		/// Initializes a new instance of the Transition class.  
		FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int transition_tag, int action_tag, int probability);

		/*
		*	\fn int FSM_Transition::getTag()
		*	\brief Get transition's tag identifier
		*	\return transition's tag value
		*/
		inline int getTag(){ return transition_TAG; }

		/*
		*	\fn int FSM_Transition::getAction()
		*	\brief Get transition's action tag identifier
		*	\return transition's action tag value
		*/
		inline int getAction(){ return action_TAG; }

		/*
		*	\fn UGKFSMT_EventList FSM_Transition::getEvents()
		*	\brief Get the specified list of events that can enable this transition
		*	\return List FSM_Events list attached to this transition
		*	\warning It can be empty
		*/
		inline UGKFSMT_EventList FSM_Transition::getEvents(){ return EventsList; }

		/// Get probability attached to this transition. 100% default value
		double getProbability();

		/*
		*	\fn FSM_State* FSM_Transition::getOrigin()
		*	\brief Get the origin state of this transition
		*	\return State object
		*/
		inline FSM_State* getOrigin() { return origin; }

		/*
		*	\fn FSM_State* FSM_Transition::getFinal()
		*	\brief Get the destination state of this transition
		*	\return State object
		*/
		inline FSM_State* getFinal(){ return final; }

		/*
		*	\fn UGKS_String FSM_Transition::getID()
		*	\brief Get transition's name identifier
		*	\return A UGKS_String value with the ID or null value
		*/
		inline UGKS_String getID(){ return transitionName; }

		/// Set this transition's probability value
		int setProbability(double newProbability);
	};

}

#endif

