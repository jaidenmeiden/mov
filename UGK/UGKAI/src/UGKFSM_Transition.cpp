/** Definition of FSM transitions methods

*	Prephix = UGKFSMT_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#include "UGKFSM_Transition.h"

using namespace UGK;

FSM_Transition::FSM_Transition(){}

/*
*	\fn FSM_Transition::FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int transition_tag, int action_tag, UGKFSMT_EventList EventsList)
*	\brief Initializes a new instance of the Transition class.
*	\param ID Transition's identifier name
*	\param A State origin
*	\param B State destination
*	\return Used in all FAs
*/
FSM_Transition::FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int Probability, UGKFSMT_EventList EventsList)
{
	transitionName = ID;
	origin = A;
	final = B;

	if (Probability > 100)
		probability = 100;
	else if (Probability < 0)
		probability = 0;
	else
		probability = Probability;

	this->EventsList = EventsList;
}

/*
*	\fn FSM_Transition::FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int transition_tag, int action_tag, UGKFSMT_EventList EventsList)
*	\brief Initializes a new instance of the Transition class.
*	\param ID Transition's identifier name
*	\param A State origin
*	\param B State destination
*	\param transition_tag Transition's tag identifier
*	\param action_tag Transition's action tag identifier
*	\param EventsList List of events that enable this transition
*	\return Used in all FAs
*/
FSM_Transition::FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int transition_tag, int action_tag, UGKFSMT_EventList EventsList)
{
	transitionName = ID;
	origin = A;
	final = B;
	transition_TAG = transition_tag;
	action_TAG = action_tag;
	this->EventsList = EventsList;
}

/*
*	\fn FSM_Transition::FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int transition_tag, int action_tag, UGKFSMT_EventList EventsList, int probability)
*	\brief Initializes a new instance of the Transition class.
*	\param ID Transition's identifier name
*	\param A State origin
*	\param B State destination
*	\param transition_tag Transition's tag identifier
*	\param action_tag Transition's action tag identifier
*	\param EventsList List of events that enable this transition
*	\param probability Probability between 0 and 100. Only used if the FA is probabilistic
*	\return Used in all FAs
*/
FSM_Transition::FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int transition_tag, int action_tag, UGKFSMT_EventList EventsList, int Probability)
{
	transitionName = ID;
	origin = A;
	final = B;
	transition_TAG = transition_tag;
	action_TAG = action_tag;
	this->EventsList = EventsList;

	if (Probability > 100)
		probability = 100;
	else if (Probability < 0)
		probability = 0;
	else
		probability = Probability;
}

FSM_Transition::FSM_Transition(UGKS_String ID, FSM_State* A, FSM_State* B, int transition_tag, int action_tag, int Probability)
{
	transitionName = ID;
	origin = A;
	final = B;
	transition_TAG = transition_tag;
	action_TAG = action_tag;

	if (Probability > 100)
		probability = 100;
	else if (Probability < 0)
		probability = 0;
	else
		probability = Probability;
}

/*
*	\fn double FSM_Transition::getProbability()
*	\brief Get probability attached to this transition. 100% default value
*	\return Double number
*/
double FSM_Transition::getProbability()
{
	if (&probability != nullptr)
		return probability;
	else
		return 100;
}

/*
*	\fn int FSM_Transition::setProbability(double newProbability)
*	\brief Set this transition's probability value
*	\param newProbability
*	\return 1 OK, -1 if ERROR
*	\warning
*/
int FSM_Transition::setProbability(double newProbability)
{
	if (&probability != nullptr)
	{
		probability = newProbability;
		return 1;
	}
	else
		return -1;
}
