#ifndef BEHAVIOR_SELECTOR_H
#define BEHAVIOR_SELECTOR_H

#include "BehaviorComposite.h";

namespace UGK
{
	/**
	* Selector, the OR behavior.
	* The selector will execute each child behavior in order.
	* If any child behavior succeeds then the selector will immediately return success.
	* If all the children behaviors have failed then the selector will return failure.
	*/
	class BehaviorSelector : public BehaviorComposite
	{
	protected:
		/// Override.
		virtual BEHAVIOR_STATE OnUpdate();
	};
}

#endif