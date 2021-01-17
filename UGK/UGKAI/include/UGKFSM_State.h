/** Header with definitions needed for the management of FSM states

*	Prephix = UGKFSMS_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Mollá
				Joan Sancho

*	@version 2016-02
*/

#ifndef UGKFSM_STATE
#define UGKFSM_STATE

#include <UGKString.h>
#include <list>

#define NULLSTATE -1
#define STATUS_ERROR -1
#define STATUS_OK 1
	
#define CONCURRENT_STATES 3

namespace UGK{

	class FSM_Transition;
	class FSM_Event;
	class FA_Classic;

	typedef std::list<FSM_Transition*>	UGKFSMS_TransitionList;

	/// State object class
	class UGK_API FSM_State
	{
	private:
		int state_TAG; ///< State tag identifier
		int action_TAG; ///< Action tag identifier of this State
		int in_action_TAG; ///< IN Action tag identifier of this State
		int out_action_TAG; ///< OUT Action tag identifier of this State
		UGKS_String initial; ///< Flag that determines if this state is initial
		UGKS_String stateName; ///< State's name (UGKS_String identifier)

	protected:
		UGKFSMS_TransitionList stateTransitions; ///< List of this state's transitions
		FA_Classic* subFA; ///< Object to attach a submachine
		unsigned int priority; ///< Priority of this state. Only used in FA_Stack
		double latency; ///< Latency of this state. Only used in FA_Inertial
		short State_credits; ///< State execution credits. Only used in FA_Concurrent_States

	public:
		/// Initializes a new instance of the State class. 
		FSM_State();
		/// Initializes a new instance of the State class. 
		FSM_State(UGKS_String ID, UGKS_String FlagInitial, int latency);
		/// Initializes a new instance of the State class. 
		FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG);
		/// Initializes a new instance of the State class. 
		FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG, unsigned int priority);
		/// Initializes a new instance of the State class. 
		FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG, int latency);
		/// Initializes a new instance of the State class. 
		FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG, short credits);
		/// Adds a submachine to this State or changes the one that is already attached 
		int addFA(FA_Classic* subFA);
		/// Adds a transition to this state if It is possible
		int addTransition(FSM_Transition* newTransition);
		/// Get the tag assigned to this state
		int getTag();
		/// Get the ID that identifies this state
		UGKS_String getID();
		/// Get latency if it exists
		double getLatency();
		/// Get priority if it exists
		int getPriority();
		/// Get credits if they exist
		short getCredits();
		/// Get subFA if it exists
		FA_Classic* getSubFA();
		/// Get if this State is initial or not
		bool isInitial();
		/// Get the list of transitions of this state
		UGKFSMS_TransitionList getTransitions();
		/// Get the action tag assigned to this state
		int getAction();
		/// Get the IN action tag assigned to this state
		int getInAction();
		/// Get the OUT action tag assigned to this state
		int getOutAction();
		/// Set the latency of the inertial state
		void setLatency(double latency);
	};
}

#endif