#include "BehaviorCondition.h";

using namespace UGK;

BEHAVIOR_STATE BehaviorCondition::OnUpdate()
{
	if( CheckCondition() )
		return child->Tick();
	else
		return BS_FAILURE;
}

bool BehaviorCondition::CheckCondition()
{
	return false;
}