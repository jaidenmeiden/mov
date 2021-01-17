#ifndef BEHAVIOR_H
#define BEHAVIOR_H

namespace UGK
{
	/**
	* States of the behaviors.
	*/
	typedef enum
	{
		/// The behavior has not been initialized yet.
		BS_INACTIVE,

		/// The behavior has succeed its execution.
		BS_SUCCESS,

		/// The behavior has failed its execution.
		BS_FAILURE,

		/// The behavior is running.
		BS_RUNNING,

		/// Maximum number of states.
		BS_MAX_STATES
	}
	BEHAVIOR_STATE;

	/**
	* Base node class of the behavior trees used to create composites, decorators or actions.
	*/
	class Behavior
	{
	protected:
		/// State of the behavior.
		BEHAVIOR_STATE state;

		/// Virtual method called when the behavior is initialized.
		virtual void OnStart() { }

		/// Virtual method called when the behavior is ticked via BehaviorNode::Tick method. Must be implemented to add custom logic.
		virtual BEHAVIOR_STATE OnUpdate() { return BS_INACTIVE; }

		/// Virtual method called when the behavior has finished its execution.
		virtual void OnEnd( BEHAVIOR_STATE state ) { }

	public:
		/// Base constructor.
		Behavior();

		/// Helper and wrapper method that ensures the correct execution of the virtual methods. Call this method to move the behavior 1 time unit forward.
		BEHAVIOR_STATE Tick();

		/// Resets the behavior.
		virtual void Reset() { state = BS_INACTIVE; }
	};
}

#endif