#ifndef BEHAVIOR_SEQUENCE_H
#define BEHAVIOR_SEQUENCE_H

#include "BehaviorComposite.h";

namespace UGK
{
	/**
	* Sequence, the AND behavior.
	* The sequence will execute each child behavior in order.
	* If any child behavior fails then the sequence will immediately return failure.
	* If all the children behaviors have succeed then the sequence will return success.
	*/
	class BehaviorSequence : public BehaviorComposite
	{
	protected:
		/// Override.
		virtual BEHAVIOR_STATE OnUpdate();
	};
}

#endif