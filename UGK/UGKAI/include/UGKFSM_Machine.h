/** Header with definitions needed for the management of FSM linked to a character

*	Prephix = UGKFSMM_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Mollá
				Joan Sancho

*	@version 2016-02
*/

#ifndef UGKFSM_MACHINE
#define UGKFSM_MACHINE

#include "UGKFA_Classic.h"
#include <time.h>
#include <map>
#include <stack>

using namespace std;

namespace UGK {

	//#define CONCURRENT_STATES 3

	/// This class allows to go through a Finite Automaton
	class UGK_API FSM_Machine
	{
	private:
		FA_Classic* FSM; ///< Current FSM
		FSM_State* CurrentState; ///< Current State in current FSM
		list<int> DoActions; ///< List of Actions to do
		FSM_Transition* t_aux; ///< Chosen Transition in selection phase
		bool change; ///< Flag that determines a change of state
		list<stack<FA_Classic*>> FSM_Stack; ///< List of stacks of FSMs (used to remember the previous one)
		list<stack<FSM_State*>> SuperiorStack; ///< List of stacks of States (used to remember the previous one)
		bool stackable; ///< Flag that determines if a situation is stackable
		int RandomNumber; ///< Random number to determine activation

		//INERTIAL attributes
		float inertialTimer; //Medir el tiempo ///< Inertial FSM timer
		int lastEvent; ///< Stores lastEvent value (used to control the timer)

		//STACK attributes
		list<stack<FSM_State*>> ControlStack; ///< Control Stack used in FA_Stack

		//FSM_CONCURRENT_STATES
		UGKFAC_StateList EnabledStates; ///< Enabled States in this cycle
		UGKFAC_StateList EnabledStatesCopy; ///< Auxiliar list of enabled states
		map<int, int> StatesCredits; ///< Dictionary of execution credits
		bool UpdateEnabled; ///< Flag to update enabled states in current cycle
		int MaxEnabled; ///< Max number of concurrent states

	public:
		/// Initializes a new instance of theFSM_Machine class. 
		FSM_Machine();
		/// Initializes a new instance of the FSM_Machineclass. 
		FSM_Machine(FA_Classic* fsm);
		/// Get Current FSM
		FA_Classic* getFSM();
		/// Get Current State (not valid for Concurrent States)
		FSM_State* getCurrentState();
		/// Get Current States
		UGKFAC_StateList getEnabledStates();
		/// Set Current States
		void setCurrentState(FSM_State* state);
		/// Updates situation of current/s FSM
		list<int> UpdateFSM(list<int> Events);
		/// Updates state of current FSM
		FSM_State* UpdateFSM(UGKS_String event_name);
	};

}

#endif