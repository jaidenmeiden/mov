/** Definition of concurrent states FSM methods

*	Prephix = UGKFACS_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#include "UGKFA_Concurrent_States.h"

using namespace UGK;
using namespace std;

/*
*	\fn FA_Concurrent_States::FA_Concurrent_States(UGKS_String ID, int tag, int num, UGKS_String CallbackName, bool FlagProbability)
*	\brief Initializes a new instance of the FA_Concurrent_States class.
*	\param
*	\return
*	\warning
*/
FA_Concurrent_States::FA_Concurrent_States(UGKS_String ID, int tag, int num, UGKS_String CallbackName, bool FlagProbability) :
FA_Classic(ID, tag, CallbackName, FlagProbability)
{
	this->ID = ID;
	FAtype = "Concurrent_States";
	FA_tag = tag;
	n_MAX_Concurrent = num;
	this->CallbackName = CallbackName;
}

/*
*	\fn void FA_Concurrent_States::Start()
*	\brief This method allows the starting of the FSM based on this FA
*	\warning It must be called when the FA is complete
*/
void FA_Concurrent_States::Start()
{
	{
		int index = 0;

		for (UGKFAC_StateList::iterator it = StatesList.begin(); it != StatesList.end(); ++it)
		{
			FSM_State* aux = *it;
			if (aux->isInitial())
			{
				existInitial = true;
				initiallyEnabled.push_back(aux);
				positionInGraph = index;
			}

			StatesCredits.insert(pair<int, int>(aux->getTag(), (int)(aux->getCredits())));

			if (aux->getSubFA() != nullptr)
				aux->getSubFA()->Start();

			index++;
		}
	}
}

/*
*	\fn UGKS_String FA_Concurrent_States::getFAtype()
*	\brief Get FA type (virtual, the other FAs override this method)
*	\return The name of the FA type
*/
UGKS_String FA_Concurrent_States::getFAtype()
{
	return FAtype;
}

/*
*	\fn UGKS_String FA_Concurrent_States::getFAid()
*	\brief Get FA id (virtual, the other FAs override this method)
*	\return The name of the FSM based on this FA
*/
UGKS_String FA_Concurrent_States::getFAid()
{
	return ID;
}

/*
*	\fn map<int, int> FA_Concurrent_States::getCreditsDic()
*	\brief Get the dictionary that controls execution credits
*	\return Dictionary collection
*	\warning Used internally
*/
map<int, int> FA_Concurrent_States::getCreditsDic()
{
	return StatesCredits;
}

/*
*	\fn UGKFAC_StateList FA_Concurrent_States::getInitials()
*	\brief Get initial states of the FSM based on this FA
*	\return List of initial states
*	\warning It could be void if there are not any initial state
*/
UGKFAC_StateList FA_Concurrent_States::getInitials()
{
	return initiallyEnabled;
}

/*
*	\fn int FA_Concurrent_States::getMaxConcurrent()
*	\brief Get Max number of concurrent states
*	\return An int value
*/
int FA_Concurrent_States::getMaxConcurrent()
{
	return n_MAX_Concurrent;
}