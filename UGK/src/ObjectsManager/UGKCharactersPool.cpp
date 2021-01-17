/**
*	@file	 UGKCharactersPool.cpp
*	@author  Santiago Jim&eacute;nez Serrano [sanjiser@gmail.com]
*			 Refactoring and adaptation: Ramón Mollá
			 Subtypes support
*   @refactored 2017-02
			Character states managed including Default, Stored and Quarantine
			Some improvements are included
*   @version 1.1
*	@brief	 Implementation of class CCharactersPool
*			 Represents a Pool of objects of type CCharacter
*            Provide methods to easily create new CCharacters, or get those ones stored before
*            It needs a CCharactersFactory to create news CCharacters
*
There are two kinds of storage and the correspondent character states:
a.- STORED. The character is stored at the front end. The pool manager can use them as required. No restriction
b.- QUARANTINE. The character has to remain stored until a time out happens: current time surpasses the time stamped into the character

*	Prefix: UGKOBJM_
**/

#include <iostream>
#include <UGKCharactersPool.h>
#include <stack>
#include <vector>

using namespace std;
using namespace UGK;


// Constructor

/**
* @fn     CCharactersPool
* @param  CCharactersFactory* charactersFactory The CCharacters factory needed to create new CCharacters objects.
* @brief  CCharactersPool constructor.
*/
CCharactersPool::CCharactersPool()
{
	CharactersAmount       = 0;
	Factory				   = NULL;
	CurrentTime			   = NULL;
	Pool.resize(0); // Empty Stack for that Type of CCharacter
}

/**
* @fn     CCharactersPool
* @param  CCharactersFactory* charactersFactory The CCharacters factory needed to create new CCharacters objects.
* @brief  CCharactersPool constructor.
*/
CCharactersPool::CCharactersPool(CCharactersFactory* charactersFactory)
{
	setFactory(charactersFactory);
}

// Destructor

/**
* @fn     ~CCharactersPool
* @brief  CCharactersPool destructor.
*/
CCharactersPool::~CCharactersPool()
{
	/// Amount of different types of CCharacters that the Factory can produce.
	int	Types = Factory->getNumDistinctCharacterTypes(); 

	//t for types and s for subtypes
	for (int t = 0; t < Types; t++)
		for (unsigned int s = 0; s < Pool[t].size(); s++)	//Sub types
		{
			while (!Pool[t][s].empty())
			{
				delete Pool[t][s].front();
				Pool[t][s].pop_front();
			}
			Pool[t].clear();
		}
	Pool.clear();
}

// Public Functions

/**
* @fn     getFactory
* @return The CharactersFactory of this Pool.
* @brief  Gets the CharactersFactory of this Pool, used to create new CCharacters.
*/
CCharactersFactory* CCharactersPool::getFactory()
{
	return Factory;
}

void CCharactersPool::SetTimer(cHRTimer * T) { CurrentTime = T; }

/**
* @fn     setFactory
* @param  a pointer to a CCharactersFactory to be set to the pool.
* @return Void.
* @brief  Sets the CharactersFactory of this Pool, used to create new CCharacters.
*/
void CCharactersPool::setFactory(CCharactersFactory* fact)
{
	CharactersAmount = 0;
	Factory = fact;

	Pool.resize(Factory->getNumDistinctCharacterTypes()); // Resize the pool to support the different kinds of characters

	for (unsigned int i = 0; i < Pool.size(); i++)
	{
		Pool[i].resize(1);	//At least the object to made has one subtype. 
		Pool[i][0].clear(); //Removes all elements from the deque (which are destroyed), leaving the container with a size of 0.
	}
}

/**
* @fn     get
* @param  int characterType Type of the CCharacter to get.
* @return A pointer to a CCharacter of the specified type that existed at this Pool, or if not, a new one created with the Factory.
* @brief  Gets a pointer to a CCharacter of the specified type.\n
*         If this pool does not contain any object of that type create a new one with the Factory and will return it.\n
*         If this pool contains an object of the specified type, it will be removed from this pool and returned.\n
*/
UGK::CCharacter* CCharactersPool::get(int Type, int subType)
{
	CCharacter* c;

	if (!characterTypeIsValid(Type))
		return NULL;

	if (Pool[Type][subType].empty())
	{
		c = Factory->GeneralCreateNewCharacter(Type, subType);
		c->SetCemetery(this);
		return c;
	}
	else
	{
		c = Pool[Type][subType].front();
		if (c->Quarantined())
			if (c->GetQuarantine() > CurrentTime->GetRealTime())	//Is quarantine active yet?
			{
				c = Factory->GeneralCreateNewCharacter(Type, subType);
				c->SetCemetery(this);
				return c;
			}

		Pool[Type][subType].pop_front();
		CharactersAmount--;
		c->Store();	//If character comes from a pool, indicate it the requester that is was stored
		return c;
	}
}

/**
* @fn     setSubTypes
* @param  int Type Type of the CCharacter to set the amount of subtypes it has.
* @param  int subTypes amount of CCharacter sub classes to set. An specialization of the character
* @brief  Sets the amount of CCharacters sub classes to set.\n
*         If this pool has the same amount of sub classes, nothing is done.\n
*         If this pool has lower amount of sub classes, new ones are created.\n
*         If this pool has higher amount of sub classes, the excess is deleted.\n
*/
void CCharactersPool::setSubTypes(int Type, int subTypes)
{
	if (subTypes < Pool[Type].size() || subTypes > Pool[Type].size())
	{
		//If this pool has lower amount of sub classes, new ones are created.
		//If this pool has higher amount of sub classes, the excess is deleted.
		Pool[Type].resize(subTypes);
		for (int i = 0; i < subTypes; i++)
			Pool[Type][i].clear();
	}
	//If this pool has the same amount of sub classes, nothing is done.\n
}

/**
* @fn     save
* @param  CCharacter* c     Pointer to the CCharacter to be saved at this Pool.
* @param  int characterType Type of the CCharacter to save.
* @brief  Save the specified CCharacter in this pool, with the specified characterType key.
*/
bool CCharactersPool::save(CCharacter* c)
{
	int characterType = c->Type;

	if (!characterTypeIsValid(characterType))
	{
		delete c;
		return false;
	}

	Pool[characterType][c->SubType].push_front(c);
	CharactersAmount++;
	c->Store();
	return true;
}

/**
		* @fn     void Quarantine(CCharacter* c);
		* @param  CCharacter* c     Pointer to the CCharacter to be saved at this Pool.
		* @brief  Save the specified CCharacter in this pool under quarantine guard
		* @return True if it is set into quarantine. Otherwise false.
		*/
bool CCharactersPool::Quarantine(CCharacter* c, HRT_Time T)
{
	int characterType = c->Type;

	if (!characterTypeIsValid(characterType))
	{
		delete c;
		return false;
	}

	Pool[characterType][c->SubType].push_back(c);
	CharactersAmount++;
	c->SetQuarantine(T);
	return true;
}

/**
* @fn     getNumCharacters
* @brief  Gets the total number of CCharacters contained at this Pool.
* @return The total number of CCharacters contained at this Pool.
*/
int CCharactersPool::getNumCharacters()
{
	return CharactersAmount;
}


/**
* @fn     getNumCharacters
* @param  int Type Type of the CCharacters to count at this Pool.
* @param  int subType Type of the CCharacters to count at this Pool.
* @return The number of CCharacters of the specified type contained at this Pool.
* @brief  Gets the number of CCharacters of the specified type contained at this Pool.
*/
int CCharactersPool::getNumCharacters(int Type, int subType)
{
	if (!characterTypeIsValid(Type))
		return UGKOBJM_INVALID_CHARACTER;

	return Pool[Type][subType].size();
}


/**
* @fn     containsCharacter
* @return A value indicating if this Pool contains any CCharacter.
* @brief  Gets a value indicating if this Pool contains any CCharacter.
*/
bool CCharactersPool::containsCharacter()
{
	return CharactersAmount > 0;
}


/**
* @fn     freeMemory
* @brief  Free all the memory of the CCharacters at this Pool.
*/
void CCharactersPool::freeMemory()
{
	int Types = Factory->getNumDistinctCharacterTypes();

	for (int t = 0; t < Types; t++)
	{
		freeMemoryByType(t);
	}
	CharactersAmount = 0;
}


/**
* @fn     freeMemory
* @param  int numObjects    Maximum number of CCharacters to delete from memory.
* @brief  Free the memory of the CCharacters at this Pool.
*/
void CCharactersPool::freeMemory(int Objects)
{
	if (Objects < 0)
		return;

	CCharacter *c;

	unsigned int type		= 0,
				 subType	= 0,
				 Deleted	= 0;

	int CharsStartLoop	 = CharactersAmount;	//To check if nothing has been deleted in a loop

	while (containsCharacter() && Deleted < Objects)
	{
		if (!Pool[type][subType].empty())
		{
			c = Pool[type][subType].front();
			if (c->Quarantined())
			{
				if (c->GetQuarantine() <= CurrentTime->GetRealTime())	//Has quarantine passed?
				{
					Pool[type][subType].pop_front();
					CharactersAmount--;
					freeCharacter(c);
					Deleted++;
				}
			}
			else
			{
				Pool[type][subType].pop_front();
				CharactersAmount--;
				freeCharacter(c);
				Deleted++;
			}
		}

		subType++;
		if (subType >= Pool[type].size())
		{
			subType = 0;
			type++;
		}

		if (type >= Pool.size())
			if (CharsStartLoop != CharactersAmount)	//If at least one object has been deleted
			{
				CharsStartLoop = CharactersAmount;
				type = 0;	//Take an object from all types. Once every type has an object less, start again
			}
			else return;
	}
}

void CCharactersPool::DeleteCharacter(int Type, int subType)
{
	freeCharacter((CCharacter*) Pool[Type][subType].front());
	Pool[Type][subType].pop_front();
	CharactersAmount--;
}

/**
* @fn     freeMemoryByType
* @param  int Type Type of the CCharacters to delete from memory.
* @brief  Free the memory of the CCharacters at this Pool corresponding to a specified Type of CCharacter.
*/
int CCharactersPool::freeMemoryByType(int Type)
{
	CCharacter *c;
	int deleted = 0;

	if (characterTypeIsValid(Type))
		for (unsigned int i = 0; i<Pool[Type].size();i++)
			while (!Pool[Type][i].empty())
			{
				c = Pool[Type][i].front();
				if (!c->Quarantined())
				{
					DeleteCharacter(Type, i);
					deleted++;
				}
				else if (c->GetQuarantine() <= CurrentTime->GetRealTime())	//Has quarantine passed?
				{
					DeleteCharacter(Type, i);
					deleted++;
				}
			}
	return deleted;
}


/**
* @fn     freeMemoryByType
* @param  int Type Type of the CCharacters to delete from memory.
* @param  int numObjects    Maximum number of CCharacters to delete from memory.
* @brief  Free the memory of the CCharacters at this Pool corresponding to a specified Type of CCharacter.
*/
int CCharactersPool::freeMemoryByType(int Type, int numObjects)
{
	CCharacter *c;
	int Deleted = 0;

	if (characterTypeIsValid(Type))
		if (numObjects > 0)
			for (unsigned int i = 0; i<Pool[Type].size(); i++)
				while (containsCharacter(Type, i) && Deleted < numObjects)
				{
					c = Pool[Type][i].front();
					if (!c->Quarantined())
					{
						DeleteCharacter(Type, i);
						Deleted++;
					}
					else if (c->GetQuarantine() <= CurrentTime->GetRealTime())	//Has quarantine passed?
					{
						DeleteCharacter(Type, i);
						Deleted++;
					}
				}
	return Deleted;
}
