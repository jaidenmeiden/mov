/** Definition of inertial FSM methods

*	Prephix = UGKFAI_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#include "UGKFA_Inertial.h"

using namespace UGK;

/*
*	\fn FA_Inertial::FA_Inertial(UGKS_String ID, int tag, UGKS_String CallbackName, bool FlagProbability)
*	\brief Initializes a new instance of the FA_Inertial class.
*	\param ID Name of the FSM based on this FA
*	\param FlagProbability If set to true, then, it is a probabilistic FA_Inertial ; otherwise, it is a deterministic FA_Inertial
*/
FA_Inertial::FA_Inertial(UGKS_String ID, bool FlagProbability) :
	FA_Classic(ID, FlagProbability)
{
	this->ID = ID;
	FAtype = "Inertial";
}

/*
*	\fn FA_Inertial::FA_Inertial(UGKS_String ID, int tag, UGKS_String CallbackName, bool FlagProbability)
*	\brief Initializes a new instance of the FA_Inertial class.
*	\param ID Name of the FSM based on this FA
*	\param tag Token identifier for the FSM based on this FA
*	\param CallbackName This events routine must be implemented
*	\param FlagProbability If set to true, then, it is a probabilistic FA_Inertial ; otherwise, it is a deterministic FA_Inertial
*/
FA_Inertial::FA_Inertial(UGKS_String ID, int tag, UGKS_String CallbackName, bool FlagProbability) :
FA_Classic(ID, tag, CallbackName, FlagProbability)
{
	this->ID = ID;
	FAtype = "Inertial";
	FA_tag = tag;
	this->CallbackName = CallbackName;
}

/*
*	\fn void FA_Inertial::Start()
*	\brief This method allows the starting of the FSM based on this FA
*	\warning It must be called when the FA is complete
*/
void FA_Inertial::Start()
{
	int index = 0;
	//Iterar sobre std::List
	for (UGK::UGKFAC_StateList::iterator it = StatesList.begin(); it != StatesList.end(); ++it)
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
*	\fn UGKS_String FA_Inertial::getFAtype()
*	\brief Get FA type
*	\return The name of the FA type
*/
UGKS_String FA_Inertial::getFAtype()
{
	return FAtype;
}

/*
*	\fn UGKS_String FA_Inertial::getFAid()
*	\brief Get FA id
*	\return The name of the FSM based on this FA
*/
UGKS_String FA_Inertial::getFAid()
{
	return ID;
}