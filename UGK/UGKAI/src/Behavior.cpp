#include "Behavior.h";

using namespace UGK;

Behavior::Behavior()
{
	state = BS_INACTIVE;
}

BEHAVIOR_STATE Behavior::Tick()
{
	// OnStart is only called when the behavior has not been initialized.
	if( state == BS_INACTIVE )
		OnStart();

	// Call the OnUpdate method to update the state of the behavior.
	state = OnUpdate();

	// If the behavior is not running call OnEnd.
	if( state != BS_RUNNING )
		OnEnd(state);

	return state;
}