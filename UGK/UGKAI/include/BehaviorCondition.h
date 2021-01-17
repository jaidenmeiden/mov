#ifndef BEHAVIOR_CONDITION_H
#define BEHAVIOR_CONDITION_H

#include "BehaviorDecorator.h";

namespace UGK
{
	/**
	* Base class of the behavior conditions.
	* Extend this class to create custom condition behaviors overriding the BehaviorCondition::CheckCondition method.
	*/
	class BehaviorCondition : public BehaviorDecorator
	{
	protected:
		/// Override.
		virtual BEHAVIOR_STATE OnUpdate();

		/// Virtual method used to be implemented by new conditions.
		virtual bool CheckCondition();
	};
}

#endif