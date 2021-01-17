#ifndef _AI_H_
#define _AI_H_

#include "UGKFSM_Machine.h"
#include "UGKFSM_State.h"
#include "BehaviorTree.h"

using namespace UGK;

typedef enum
{
	UGKAI_SM, //State Machine
	UGKAI_BT, //Behaviour Trees
	UGKAI_NN, //Neural Networks
	UGKAI_MAX_AI
} UGKAI_AI_TYPES;

namespace UGK
{
	class CArtificial_Intelligence
	{
	private:
		UGKAI_AI_TYPES Type;

		FSM_State*	current_state;		///< Stores the state for not having to overload FSM message system
		FSM_Machine	FSM;				///< Stores the FSM related to the AI of this character

		Behavior* behaviorTree;			///< Root node of the behavior tree

	public:
		CArtificial_Intelligence() {}					///< Constructor with initialization
		FSM_State*	getCurrentState();					///< Returns the FSM's current state
		FSM_State*	sendEvent(UGKS_String event_id);	///< Signals the FSM with an event and updates AI current state
		void		loadAI(FSM_Machine* AI);			///< Sets the current AI with one determined AI from AIManager

		void		loadBT(Behavior* behavior);			///< Loads a behavior tree as the AI system
	};
}

#endif //_AI_H