/** Header with definitions needed for the management of classic FSM

*	Prephix = UGKFAC_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#ifndef UGKFA_CLASSIC
#define UGKFA_CLASSIC

#include "UGKFSM_Transition.h"

namespace UGK{

	typedef std::list<FSM_State*>		UGKFAC_StateList;

	//extern UGKS_String FSM_EventTypeName[FSM_MAX_EVENT];

	class UGK_API FA_Classic
	{
	protected:
		UGKS_String ID; ///< Identifier of this FA
		UGKFAC_StateList StatesList; ///< List of states of this FA
		UGKFSMS_TransitionList TransitionsList; ///< List of transitions of this FA
		int n_AddedStates; ///< Number of added states
		int n_notAddedStates; ///< Number of not added states
		int n_AddedTransitions; ///< Number of added transitions
		int n_notAddedTransitions; ///< Number of not added transitions
		int FA_tag; ///< Token that identifies this FA
		int positionInGraph; ///< Position in the FA (used internally)
		UGKS_String FAtype; ///< Type of FA
		bool existInitial; ///< Flag that determines if there is one initial state in this FA
		FSM_State* initial; ///< Initial state
		UGKS_String CallbackName; ///< Events Routine for this FA 
		bool FlagProbabilistic; ///< Probabilistic

	public:
		/// Initializes a new instance of the FA_Classic class.
		FA_Classic(){}
		~FA_Classic(){}

		FA_Classic(UGKS_String ID, bool FlagProbabilistic);
		FA_Classic(UGKS_String ID, int tag, UGKS_String CallbackName, bool FlagProbabilistic);

		/// This method allows the starting of the FSM based on this FA
		virtual void Start();
		/// Add a new state node to the FSM based on this FA
		int addState(FSM_State* newState);
		/// Add a new transition to the FSM based on this FA
		int addTransition(FSM_Transition* newTransition);
		/// Set initial state
		void setInitialState(FSM_State* initialState);
		/// Set states list
		void setStatesList(UGKFAC_StateList statesList);
		/// Set transitions list
		void setTransitionsList(UGKFSMS_TransitionList transitionsList);
		/// Get the tag that identifies the FSM based on this FA
		int getTag();
		/// Get the events routine of the FSM based on this FA
		UGKS_String getCallback();
		/// Get current nº of states that have been added to the FSM based on this FA
		int getAddedStates();
		/// Get current nº of states that have not been added to the FSM based on this FA
		int getNotAddedStates();
		/// Obtain current nº of transitions that have been added to the FSM based on this FA
		int getAddedTransitions();
		/// Get current nº of transitions that have not been added to the FSM based on this FA
		int getNotAddedTransitions();
		/// Get a boolean flag that determines if exist one initial state in the FSM based on this FA
		bool ExistInitial();
		/// Get the StatesList
		UGKFAC_StateList getStatesList();
		/// Get the TransitionsList
		UGKFSMS_TransitionList getTransitionsList();
		/// Get the state (if exist) whose identifier is ID
		FSM_State* getStateByID(UGKS_String ID);
		/// Get the state (if exist) whose identification number is tag
		FSM_State* getStateByTag(int tag);
		/// Get initial state in the FSM based on this FA
		FSM_State* getInitialState();
		/// Get FA type (virtual, the other FAs override this method)
		virtual UGKS_String getFAtype();
		/// Get FA id (virtual, the other FAs override this method)
		virtual UGKS_String getFAid();
		/// Get if the FSM based on this FA is probabilistic or not
		bool isProbabilistic();
		/// This method allows to change callback events routine for the FSM based on this FA
		void setCallback(UGKS_String newCallback);
	};

}
#endif

