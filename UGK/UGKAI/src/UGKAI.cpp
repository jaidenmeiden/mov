#include "UGKAI.h"

using namespace UGK;

FSM_State* CArtificial_Intelligence::getCurrentState()
{
	return current_state;
}

FSM_State* CArtificial_Intelligence::sendEvent(UGKS_String event_id)
{
	current_state = FSM.UpdateFSM(event_id);
	return current_state;
}

void CArtificial_Intelligence::loadAI(FSM_Machine* AI)
{
	FSM = *AI;
	current_state = FSM.getCurrentState();
}

void CArtificial_Intelligence::loadBT(Behavior* behavior)
{
	this->behaviorTree = behavior;
}
