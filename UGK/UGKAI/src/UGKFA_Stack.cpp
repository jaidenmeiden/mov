/** Definition of stack-based FSM methods

*	Prephix = UGKFAS_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#include "UGKFA_Stack.h"

using namespace UGK;
/*
*	\fn FA_Stack::FA_Stack(UGKS_String ID, bool FlagProbability)
*	\brief Initializes a new instance of the FA_Stack class.
*	\param ID Name of the FSM based on this FA
*	\param FlagProbability If set to, then, it is a probabilistic FA_Stack ; otherwise, it is a deterministic FA_Stack
*/
FA_Stack::FA_Stack(UGKS_String ID, bool FlagProbability) :
	FA_Classic(ID, FlagProbability)
{
	this->ID = ID;
	FAtype = "Stack-based";
}

/*
*	\fn FA_Stack::FA_Stack(UGKS_String ID, int tag, UGKS_String CallbackName, bool FlagProbability)
*	\brief Initializes a new instance of the FA_Stack class.
*	\param ID Name of the FSM based on this FA
*	\param tag Token identifier for the FSM based on this FA
*	\param CallbackName This events routine must be implemented
*	\param FlagProbability If set to, then, it is a probabilistic FA_Stack ; otherwise, it is a deterministic FA_Stack
*/
FA_Stack::FA_Stack(UGKS_String ID, int tag, UGKS_String CallbackName, bool FlagProbability) :
FA_Classic(ID, tag, CallbackName, FlagProbability)
{
	this->ID = ID;
	FAtype = "Stack-based";
	FA_tag = tag;
	this->CallbackName = CallbackName;
}

/*
*	\fn void FA_Stack::Start()
*	\brief This method allows the starting of the FSM based on this FA
*	\warning It must be called when the FA is complete
*/
void FA_Stack::Start()
{
	int index = 0;
	//Iterar sobre List
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
*	\fn UGKS_String FA_Stack::getFAtype()
*	\brief Get FA type
*	\return The name of the FA type
*/
UGKS_String FA_Stack::getFAtype()
{
	return FAtype;
}

/*
*	\fn UGKS_String FA_Stack::getFAid()
*	\brief Get FA id
*	\return The name of the FSM based on this FA
*/
UGKS_String FA_Stack::getFAid()
{
	return ID;
}