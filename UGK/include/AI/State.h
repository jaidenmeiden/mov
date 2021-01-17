/****************************************
*	Initial Author:		Nathaniel Meyer	*
*	E-Mail:		nath_meyer@hotmail.com	*
*	Website:	http://www.nutty.ca		*
*										*
*   You are free to use, redistribute,  *
*   and alter this file in anyway, so   *
*   long as credit is given where due.	*
****************************************/

/**
 *	PROJECT - Finite State Machine support for Deterministic Finite Automata
 *
 *	state.h
 *	
 *	Refactored by Ramón Mollá <rmolla@dsic.upv.es>
 *
 *	HISTORY:
 *
 *	Adapted to be used by any kind of objects in any given program. It goes on using callbacks 
 *	but these calbacks have a new object parameter that provides the local information to execute 
 *	properly.
 *	The code have been doxygenated in order to imrpove the readability and support automatic documentation
 *	@version 11-2015
 *  Refactored by Ramón Mollá to suppoort unicode
 *	Prefix: STT_

 *  
 */

#ifndef State_h
#define State_h

#include <vector>
#include <UGKString.h>

#define STT_NO_VALID_STATE -1

#define STT_EventType	UGKS_String
#define STT_NameType	UGKS_String

	/*
		State Class
		- A state consists of a set of specifications and transitions
		- A state can only do what its told to and nothing more
		*/
typedef void* (*mFuncPtr) (LPSTR *args, void  *Object);	//Object must be casted to the one needed

namespace UGK
{
	/*
		eWhen
		- Actions to define within the state
		*/
	enum eWhen
	{
		eOnEntry = 0,	/// Action taken on entering the state
		eDo,			/// Action taken from entering the state until leaving the state. 
		/// Action done by default if no Event is received
		eOnExit,		/// Action taken on leaving the state
		eOnEvent		/// Action taken based on the Event received
		/// Specify Event, Arguments, and Condition
	};

	/*
		eType
		- Specifies the action type
		- Only action is supported
		*/
	enum eType
	{
		eAction = 0,	// Action is a function
		// Specify Name
		eSendEvent,		// Send an Event
		// - Specify Name, Arguments, and Target
		eDontUse		// Don't Use
	};

	/*
	Specification
	- There are exactly 4 specifications as defined in eWhen
	*/
	struct _specification
	{
		STT_NameType name;	// Name of the action
		STT_EventType Event;// Event this specification is tied to
		int type;			// Type of action
		mFuncPtr func;		// Pointer to the action
	};	// 3 main actions + 4-mMaxEvents

	class State;

	struct _transition
	{
		//State *cFrom;			// From State	NOT NEEDED
		State *cTo;				// To State
		STT_EventType Event;	// Event ties to outgoing state
	};

	class CCharacter;

	class UGK_API State
	{
	protected:

		STT_NameType Name;	///< Name of the state
		std::vector<_transition>	Transition;
		std::vector<_specification>	Specification;

	public:

		_specification SpecificationEntry;
		_specification SpecificationDo;
		_specification SpecificationExit;

		/*
			Constructor / Destructor
			*/
		State();
		~State();

		/*	Accessor Methods */
		inline STT_NameType	getName()		{ return Name; }
		inline unsigned int	getEvents()		{ return Specification.size(); }
		inline unsigned int	getTransitions(){ return Transition.size(); }

		inline void				AddSpecification(_specification s)	{ Specification.push_back(s); }
		inline _specification	GetSpecification(int s)				{ return Specification[s]; }

		inline void			AddTransition(_transition t){ Transition.push_back(t); }
		inline _transition	GetTransition(int t)		{ return Transition[t]; };


		/*
			Clean
			- Cleans/Resets all data within the state
			*/
		void clean();

		/*
			Transitions
			@param: Event
			- Name which identifies the proper action to take
			@param: args
			- If provided, it will be passed on to the action
			- Return true if switch is successful
			*/
		void addTransition(STT_EventType Event, State *cState);
		bool incoming(const STT_EventType Event, LPSTR *args, void *Object);
		State *outgoing(const STT_EventType Event, LPSTR *args, void *Object);

		/*
			addAction
			@param: when
			- Specify the action activation (0-4)
			@param: type
			- Specify the action type (0-1)
			@param: name
			- Name of the action to call
			@param: Event
			- Name of the Event to cause the action
			@param: funcPtr
			- Specify what function will be executed for this state
			*/
		// Fix from Meyer's code
		void addAction(eWhen when, eType type, STT_NameType name, mFuncPtr funcPtr);
		// Fix from Meyer's code
		void addAction(eWhen when, eType type, STT_NameType name, STT_EventType Event, mFuncPtr funcPtr);	// Set OnEvent action

		//Inline functions
		/*	Operator Methods */
		inline void setName(STT_NameType name) { Name = name; }
	};
}
#endif