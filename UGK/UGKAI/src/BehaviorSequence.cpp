#include "BehaviorSequence.h";

using namespace UGK;

BEHAVIOR_STATE BehaviorSequence::OnUpdate()
{
	while( true )
	{
		BEHAVIOR_STATE s = currentChild->Tick();

		// If the child fails or keeps running.
		if( s != BS_SUCCESS )
			return s;

		// Else the child has succeed.
		// The sequence moves to the next child.
		if( currentIndex < GetChildCount() - 1 )
		{
			currentIndex++;
			currentChild = children[currentIndex];
		}
		else
		{
			// End of sequence, all the children have succeed.
			return BS_SUCCESS;
		}
	}
}