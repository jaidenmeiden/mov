#ifndef BEHAVIOR_COMPOSITE_H
#define BEHAVIOR_COMPOSITE_H

#include "Behavior.h";
#include <vector>;

using namespace std;

namespace UGK
{
	/**
	* Base class of the composite behaviors.
	* A composite behavior has a collection of child behaviors.
	*/
	class BehaviorComposite : public Behavior
	{
	protected:
		/// Collection of child behaviors.
		vector<Behavior*> children;

		/// Current behavior that the composite is executing.
		Behavior* currentChild;

		/// Current index of the behavior that the composite is executing.
		int currentIndex;

		/// Override.
		virtual void OnStart();

	public:
		/// Override.
		virtual void Reset();

		/// Returns the number of child behaviors of the composite.
		int GetChildCount();

		/// Adds a new behavior to the collection of child behaviors.
		void Add( Behavior* behavior );

		/// Clears the collection of child behaviors.
		void Clear();
	};
}

#endif