#include "BehaviorSelector.h";

using namespace UGK;

BEHAVIOR_STATE BehaviorSelector::OnUpdate()
{
	while( true )
	{
		BEHAVIOR_STATE s = currentChild->Tick();

		// If the child succeeds or keeps running.
		if( s != BS_FAILURE )
			return s;

		// Else the child has failed.
		// The selector moves to the next child.
		if( currentIndex < GetChildCount() - 1 )
		{
			currentIndex++;
			currentChild = children[currentIndex];
		}
		else
		{
			// End of selector, all the children have failed.
			return BS_FAILURE;
		}
	}
}