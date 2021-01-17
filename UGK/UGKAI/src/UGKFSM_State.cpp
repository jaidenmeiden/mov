/** Definition of FSM states methods

*	Prephix = UGKFSMS_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#include "UGKFSM_State.h"

using namespace UGK;

FSM_State::FSM_State(){}

/*
*	\fn FSM_State::FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG)
*	\brief Initializes a new instance of the FSM_State class.
*	\param ID Name of this State
*	\param FlagInitial Flag that determines if it is initial ("YES") or it is not ("NO")
*	\warning It can be used in every FA
*/
FSM_State::FSM_State(UGKS_String ID, UGKS_String FlagInitial, int lat) 
{
	stateName = ID;
	initial = FlagInitial;

	/* Null init */
	latency = lat;
	priority = NULLSTATE;
	State_credits = NULLSTATE;
	subFA = nullptr;
}

/*
*	\fn FSM_State::FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG)
*	\brief Initializes a new instance of the FSM_State class.
*	\param ID Name of this State
*	\param FlagInitial Flag that determines if it is initial ("YES") or it is not ("NO")
*	\param state_tag State tag identifier
*	\param action_tag Action tag identifier of this state
*	\param in_action_TAG IN action tag identifier of this state
*	\param out_action_TAG OUT action tag identifier of this state
*	\warning It can be used in every FA
*/
FSM_State::FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG)
{
	stateName = ID;
	initial = FlagInitial;
	state_TAG = state_tag;
	action_TAG = action_tag;
	this->in_action_TAG = in_action_TAG;
	this->out_action_TAG = out_action_TAG;

	/* Null init */
	latency = NULLSTATE;
	priority = NULLSTATE;
	State_credits = NULLSTATE;
	subFA = nullptr;
}


/*
*	\fn FSM_State::FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG, unsigned int priority)
*	\brief Initializes a new instance of the FSM_State class.
*	\param ID Name of this State
*	\param FlagInitial Flag that determines if it is initial ("YES") or it is not ("NO")
*	\param state_tag State tag identifier
*	\param action_tag Action tag identifier of this state
*	\param in_action_TAG IN action tag identifier of this state
*	\param out_action_TAG OUT action tag identifier of this state
*	\param priority Priority of this State. It has to be >=0
*	\warning It can be used in every FA
*/
FSM_State::FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG, unsigned int priority)
{
	stateName = ID;
	initial = FlagInitial;
	state_TAG = state_tag;
	action_TAG = action_tag;
	this->in_action_TAG = in_action_TAG;
	this->out_action_TAG = out_action_TAG;
	this->priority = priority;

	/* Null init */
	latency = NULLSTATE;
	State_credits = NULLSTATE;
	subFA = nullptr;
}

/*
*	\fn FSM_State::FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG, int latency)
*	\brief Initializes a new instance of the FSM_State class.
*	\param ID Name of this State
*	\param FlagInitial Flag that determines if it is initial ("YES") or it is not ("NO")
*	\param state_tag State tag identifier
*	\param action_tag Action tag identifier of this state
*	\param in_action_TAG IN action tag identifier of this state
*	\param out_action_TAG OUT action tag identifier of this state
*	\param latency Latency of this state
*	\warning It can be used in every FA
*/
FSM_State::FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG, int latency)
{
	stateName = ID;
	initial = FlagInitial;
	state_TAG = state_tag;
	action_TAG = action_tag;
	this->in_action_TAG = in_action_TAG;
	this->out_action_TAG = out_action_TAG;
	this->latency = latency;

	/* Null init */
	//latency = NULLSTATE;
	priority = NULLSTATE;
	State_credits = NULLSTATE;
	subFA = nullptr;
}

/*
*	\fn FSM_State::FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG, short credits)
*	\brief Initializes a new instance of the FSM_State class.
*	\param ID Name of this State
*	\param FlagInitial Flag that determines if it is initial ("YES") or it is not ("NO")
*	\param state_tag State tag identifier
*	\param action_tag Action tag identifier of this state
*	\param in_action_TAG IN action tag identifier of this state
*	\param out_action_TAG OUT action tag identifier of this state
*	\param credits Credits of execution of this state
*	\warning It can be used in every FA
*/
FSM_State::FSM_State(UGKS_String ID, UGKS_String FlagInitial, int state_tag, int action_tag, int in_action_TAG, int out_action_TAG, short credits)
{
	stateName = ID;
	initial = FlagInitial;
	state_TAG = state_tag;
	action_TAG = action_tag;
	this->in_action_TAG = in_action_TAG;
	this->out_action_TAG = out_action_TAG;
	State_credits = credits;

	/* Null init */
	latency = NULLSTATE;
	priority = NULLSTATE;
	subFA = nullptr;
}

/*
*	\fn int FSM_State::addFA(FA_Classic* subFA)
*	\brief Adds a submachine to this State or changes the one that is already attached
*	\param subFA FA_Classic object (any FA is valid)
*	\return 1 if OK, -1 if ERROR
*/
int FSM_State::addFA(FA_Classic* subFA)
{
	try
	{
		this->subFA = subFA;
		return 1;
	}
	catch (std::exception e)
	{
		return -1;
	}
}

/*
*	\fn int FSM_State::addTransition(FSM_Transition* newTransition)
*	\brief Adds a transition to this state if It is possible
*	\param newTransition Transition object
*	\return  1 if OK, -1 if ERROR (Transition has already been added to this State or wrong parameter)
*/
int FSM_State::addTransition(FSM_Transition* newTransition)
{
	if (count(stateTransitions.begin(), stateTransitions.end(), newTransition) > 0)
	{
		return STATUS_ERROR;
	}
	else
	{
		stateTransitions.push_back(newTransition);
		return STATUS_OK;
	}
	return STATUS_OK;
}

/*
*	\fn int FSM_State::getTag()
*	\brief Get the tag assigned to this state
*	\return int value
*/
int FSM_State::getTag()
{
	return state_TAG;
}

/*
*	\fn UGKS_String FSM_State::getID()
*	\brief Get the ID that identifies this state
*	\return UGKS_String value
*/
UGKS_String FSM_State::getID()
{
	return stateName;
}

/*
*	\fn int FSM_State::getLatency()
*	\brief Get latency if it exists
*	\return Latency value if OK -1 if error (This State has not got latency)
*/
double FSM_State::getLatency()
{
	return latency;
}

/*
*	\fn int FSM_State::getPriority()
*	\brief Get priority if it exists
*	\return Priority value if OK. -1 if error. This State has not got priority
*/
int FSM_State::getPriority()
{
	return priority;
}

/*
*	\fn short FSM_State::getCredits()
*	\brief Get credits if they exist
*	\return Credits value if OK. -1 if error. This State has not got execution credits
*/
short FSM_State::getCredits()
{
	return State_credits;
}

/*
*	\fn FA_Classic* FSM_State::getSubFA()
*	\brief Get subFA if they exist
*	\return SubFA value if OK. Null value if error. There is not a subFA attached to this State
*/
FA_Classic* FSM_State::getSubFA()
{
	if (&subFA != nullptr)
		return subFA;
	else
		return nullptr;
}

/*
*	\fn bool FSM_State::isInitial()
*	\brief Get if this State is initial or not
*	\return True or false
*/
bool FSM_State::isInitial()
{
	if (initial.compare("YES") == 0)
		return true;
	else if (initial.compare("NO") == 0)
		return false;
	else
	{
		return false;
	}
}

/*
*	\fn UGKFAC_TransitionList FSM_State::getTransitions()
*	\brief Get the list of transitions of this state
*	\return List of transitions
*/
UGKFSMS_TransitionList FSM_State::getTransitions()
{
	return stateTransitions;
}

/*
*	\fn int FSM_State::getAction()
*	\brief Get the action tag assigned to this state
*	\return tag value
*/
int FSM_State::getAction()
{
	return action_TAG;
}

/*
*	\fn int FSM_State::getInAction()
*	\brief Get the IN action tag assigned to this state
*	\return IN tag value
*/
int FSM_State::getInAction()
{
	return in_action_TAG;
}

/*
*	\fn int FSM_State::getOutAction()
*	\brief Get the OUT action tag assigned to this state
*	\return OUT tag value
*/
int FSM_State::getOutAction()
{
	return out_action_TAG;
}

/*
*	\fn void FSM_State::setLatency(int latency)
*	\brief Get the OUT action tag assigned to this state
*	\return OUT tag value
*/
void FSM_State::setLatency(double latency)
{
	this->latency = latency;
}