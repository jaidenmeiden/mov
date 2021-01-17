#ifndef BEHAVIOR_DECORATOR_H
#define BEHAVIOR_DECORATOR_H

#include "Behavior.h";

namespace UGK
{
	/**
	* Base class of the decorator behaviors.
	* A decorator behavior has 1 child behavior.
	* Transforms the result of the child behavior.
	*/
	class BehaviorDecorator : public Behavior
	{
	protected:
		/// Child behavior of the decorator.
		Behavior* child;

	public:
		/// Override.
		virtual void Reset();

		/// Adds a child behavior to the decorator.
		void Add( Behavior* behavior );
	};
}

#endif