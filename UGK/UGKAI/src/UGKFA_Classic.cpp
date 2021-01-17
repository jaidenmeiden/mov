/** Definition of classic FSM methods

*	Prephix = UGKFAC_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#include "UGKFA_Classic.h"

using namespace UGK;

/**
*	\fn FA_Classic(UGKS_String ID, int tag, UGKS_String CallbackName, bool FlagProbabilistic);
*	\brief Initializes a new instance of the FA_Classic
*	\param ID Name of the FSM based on this FA
*	\param FlagProbabilistic If set to true, then, it is a probabilistic FA_Classic ; otherwise, it is a deterministic FA_Classic
*/
UGK::FA_Classic::FA_Classic(UGKS_String ID, bool FlagProbabilistic)
{
	this->ID = ID;
	existInitial = false;
	n_AddedStates = n_notAddedStates = n_AddedTransitions = n_notAddedTransitions = 0;
	positionInGraph = -1;
	FAtype = "Classic";
	this->FlagProbabilistic = FlagProbabilistic;
}

/**
*	\fn FA_Classic(UGKS_String ID, int tag, UGKS_String CallbackName, bool FlagProbabilistic);
*	\brief Initializes a new instance of the FA_Classic
*	\param ID Name of the FSM based on this FA
*	\param tag Token identifier for the FSM based on this FA
*	\param CallbackName This events routine must be implemented
*	\param FlagProbabilistic If set to true, then, it is a probabilistic FA_Classic ; otherwise, it is a deterministic FA_Classic
*/
UGK::FA_Classic::FA_Classic(UGKS_String ID, int tag, UGKS_String CallbackName, bool FlagProbabilistic)
{
	this->ID = ID;
	existInitial = false;
	n_AddedStates = n_notAddedStates = n_AddedTransitions = n_notAddedTransitions = 0;
	positionInGraph = -1;
	FAtype = "Classic";
	FA_tag = tag;
	this->CallbackName = CallbackName;
	this->FlagProbabilistic = FlagProbabilistic;
}

/*
*	\fn Start()
*	\brief This method allows the starting of the FSM based on this FA
*	It must be called when the FA is complete
*/
void UGK::FA_Classic::Start()
{
	int index = 0;
	for (UGKFAC_StateList::iterator it = StatesList.begin(); it != StatesList.end(); ++it)
	{
		FSM_State* aux = *it;
		if (aux->isInitial())
		{
			existInitial = true;
			initial = *it;
			positionInGraph = index;
		}

		if (aux->getSubFA() != nullptr)
			aux->getSubFA()->Start();

		index++;
	}
}

/*
*	\fn int addState(FSM_State* newState)
*	\brief Add a new state node to the FSM based on this FA
*	\param newState New instance of State class
*	\return STATUS_ERROR if cannot be added
*	\return STATUS_OK if OK
*/
int UGK::FA_Classic::addState(FSM_State* newState)
{

	if (count(StatesList.begin(), StatesList.end(), newState) > 0)
	{
		n_notAddedStates++;
		return STATUS_ERROR;
	}
	else
	{
		StatesList.push_back(newState);
		return STATUS_OK;
	}
	return STATUS_OK;
}

/*
*	\fn int FA_Classic::addTransition(FSM_Transition* newTransition
*	\brief Add a new transition to the FSM based on this FA
*	\param newTransition New instance of Transition class
*	\return STATUS_ERROR if cannot be added
*	\return STATUS_OK if OK
*/
int UGK::FA_Classic::addTransition(FSM_Transition* newTransition)
{
	if (count(StatesList.begin(), StatesList.end(), newTransition->getOrigin()) > 0
		&& count(StatesList.begin(), StatesList.end(), newTransition->getFinal()) > 0
		&& !(newTransition->getID().empty())
		)
	{
		TransitionsList.push_back(newTransition);
		n_AddedTransitions++;
		return STATUS_OK;
	}
	else
	{
		n_notAddedTransitions++;
		return STATUS_ERROR;
	}
	return STATUS_OK;
}

/*
*	\fn int FA_Classic::getTag()
*	\brief Set initial state
*	\return void
*/
void UGK::FA_Classic::setInitialState(FSM_State* initialState)
{
	initial = initialState;
	existInitial = true;
}

/*
*	\fn int FA_Classic::getTag()
*	\brief Set states list
*	\return void
*/
void UGK::FA_Classic::setStatesList(UGKFAC_StateList statesList)
{
	StatesList = statesList;
}

/*
*	\fn int FA_Classic::getTag()
*	\brief Set transitions list
*	\return void
*/
void UGK::FA_Classic::setTransitionsList(UGKFSMS_TransitionList transitionsList)
{
	TransitionsList = transitionsList;
}

/*
*	\fn int FA_Classic::getTag()
*	\brief Get the tag that identifies the FSM based on this FA
*	\return An identifier number
*/
int UGK::FA_Classic::getTag()
{
	return FA_tag;
}

/*
*	\fn UGKS_String FA_Classic::getCallback()
*	\brief Get the events routine of the FSM based on this FA
*	\returnAn UGKS_String with the name of the routine
*/
UGKS_String UGK::FA_Classic::getCallback()
{
	return CallbackName;
}

/*
*	\fn int FA_Classic::getAddedStates()
*	\brief Get current nº of states that have been added to the FSM based on this FA
*	\return int value
*	\warning Only can be used if FSM_Parser is used too
*/
int FA_Classic::getAddedStates()
{
	return n_AddedStates;
}

/*
*	\fn int FA_Classic::getNotAddedStates()
*	\brief Get current nº of states that have not been added to the FSM based on this FA
*	\return int value
*	\warning Only can be used if FSM_Parser is used too
*/
int FA_Classic::getNotAddedStates()
{
	return n_notAddedStates;
}

/*
*	\fn int FA_Classic::getAddedTransitions()
*	\brief Obtain current nº of transitions that have been added to the FSM based on this FA
*	\return int value
*	\warning Only can be used if FSM_Parser is used too
*/
int FA_Classic::getAddedTransitions()
{
	return n_AddedTransitions;
}

/*
*	\fn int FA_Classic::getNotAddedTransitions()
*	\brief Get current nº of transitions that have not been added to the FSM based on this FA
*	\return int value
*	\warning Only can be used if FSM_Parser is used too
*/
int FA_Classic::getNotAddedTransitions()
{
	return n_notAddedTransitions;
}

/*
*	\fn bool FA_Classic::ExistInitial()
*	\brief Get a boolean flag that determines if exist one initial state in the FSM based on this FA
*	\return True or false
*/
bool FA_Classic::ExistInitial()
{
	return existInitial;
}

/*
*	\fn UGKFAC_StateList FA_Classic::getStatesList()
*	\brief Get the StatesList
*	\return List of states of the FSM based on this FA
*	\warning Current added States of the FSM based on this FA
*/
UGKFAC_StateList FA_Classic::getStatesList()
{
	return StatesList;
}

/*
*	\fn UGKFAC_TransitionList FA_Classic::getTransitionsList()
*	\brief Get the TransitionsList
*	\return List of transitions of the FSM based on this FA
*	\warning Current added transitions of the FSM based on this FA
*/
UGKFSMS_TransitionList FA_Classic::getTransitionsList()
{
	return TransitionsList;
}

/*
*	\fn FSM_State* FA_Classic::getStateByID(UGKS_String ID)
*	\brief Get the state (if exist) whose identifier is ID
*	\param ID Identifier or name of a State
*	\return State value or null
*/
FSM_State* FA_Classic::getStateByID(UGKS_String ID)
{
	for (UGKFAC_StateList::iterator it = StatesList.begin(); it != StatesList.end(); ++it)
	{
		FSM_State* aux = *it;
		if (aux->getID().compare(ID) == 0) return aux;
	}
	return nullptr;
}

/*
*	\fn FSM_State* FA_Classic::getStateByTag(int tag)
*	\brief Get the state (if exist) whose identification number is tag
*	\param tag Identification tag
*	\return State value or null
*/
FSM_State* FA_Classic::getStateByTag(int tag)
{

	//Iterar sobre List
	for (UGKFAC_StateList::iterator it = StatesList.begin(); it != StatesList.end(); ++it)
	{
		FSM_State* aux = *it;
		if (aux->getTag() == tag) return aux;
	}
	return nullptr;
}

/*
*	\fn FSM_State* FA_Classic::getInitialState()
*	\brief Get initial state in the FSM based on this FA
*	\return Initial State value or null
*	\warning If the FA is Concurrent_States one, use getInitials method
*/
FSM_State* FA_Classic::getInitialState()
{
	return initial;
}

/*
*	\fn UGKS_String FA_Classic::getFAtype()
*	\brief Get FA type (virtual, the other FAs override this method)
*	\return The name of the FA type
*/
UGKS_String FA_Classic::getFAtype()
{
	return FAtype;
}

/*
*	\fn UGKS_String FA_Classic::getFAid()
*	\brief Get FA id (virtual, the other FAs override this method)
*	\return The name of the FSM based on this FA
*/
UGKS_String FA_Classic::getFAid()
{
	return ID;
}

/*
*	\fn bool FA_Classic::isProbabilistic()
*	\brief Get if the FSM based on this FA is probabilistic or not
*	\return True or false
*/
bool FA_Classic::isProbabilistic()
{
	return FlagProbabilistic;
}

/*
*	\fn void FA_Classic::setCallback(UGKS_String newCallback)
*	\brief
*	\param newCallback Name of the new Callback routine
*	\return This new Callback must be implemented
*/
void FA_Classic::setCallback(UGKS_String newCallback)
{
	CallbackName = newCallback;
}
