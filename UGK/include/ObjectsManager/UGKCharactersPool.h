/**
*	@file	 UGKCharactersPool.h
*	@author  Original work Santiago Jim&eacute;nez Serrano [sanjiser@gmail.com]
			 Refactoring and adaptation: Ramón Mollá
			 Subtypes support
*	@date	 2017-02
*   @version 1.1
*
*	@brief	 Definition of class CCharactersPool.\n
*			 Represents matrix of a Pool of CCharacter classified by type and subtype. \n
*            Provide methods to easily create news CCharacters, or get those ones stored before.\n
*            It needs a CCharactersFactory to create news CCharacters..\n
*
*	Prefix: UGKOBJM_
**/


#ifndef UGKOBJM_CHARACTERSPOOL
#define UGKOBJM_CHARACTERSPOOL

#include <deque>
#include <vector>
#include <UGKCharactersFactory.h>

#define UGKOBJM_INVALID_CHARACTER -1

namespace UGK
{
	#define UGKOBJM_NO_SUBTYPE 0

	typedef deque<CCharacter*>				UGKOBJM_CharacterPool;
	typedef vector<UGKOBJM_CharacterPool>	UGKOBJM_PoolVector;
	typedef vector<UGKOBJM_PoolVector>		UGKOBJM_TypeVector;

	/**
	* @brief CCharactersPool \n	
	* Class that represents a Pool of CCharacters.
	*/
	class UGK_API CCharactersPool
	{

	private:
		CCharactersFactory*			Factory;			 ///< Factory of CCharacters needed to create new ones.
		
		UGKOBJM_TypeVector			Pool;                ///< Pool. Vector of size mDistinctTypes containing Stacks of CCharacters. Each type has one Stack.
		int							CharactersAmount;       ///< Total number of characters stored at this Pool.

		cHRTimer *					CurrentTime;

		/**
		* @fn     freeCharacter
		* @param  CCharacter* c Pointer to the CCharacter to free its memory.		
		* @brief  Calls the destructor of the specified CCharacter.		
		*/
		inline void freeCharacter(CCharacter* c){delete c;}

		/**
		* @fn     characterTypeIsValid
		* @param  int Type Type of the CCharacter to be validated.
		* @return True if the type is correct. I.e. Belongs to [0, distinctTypes-1]. False otherwise.
		* @brief  Test if the specified characterType is valid.
		*/
		bool characterTypeIsValid(int Type){return Type >= 0 && Type < Factory->getNumDistinctCharacterTypes();}
		void DeleteCharacter(int Type, int subType);

	public:

		void SetTimer(cHRTimer * T);

		/**
		* @fn     CCharactersPool();
		* @brief  CCharactersPool constructor.
		*/
		CCharactersPool();
		
		/**
		* @fn     CCharactersPool(CCharactersFactory* charactersFactory);
		* @param  CCharactersFactory* charactersFactory The CCharacters factory needed to create new CCharacters objects.
		* @brief  CCharactersPool constructor.
		*/
		CCharactersPool(CCharactersFactory* charactersFactory);

		/**
		* @fn     ~CCharactersPool
		* @brief  CCharactersPool destructor.
		*/
		~CCharactersPool();

		/**
		* @fn     getFactory
		* @return The CharactersFactory of this Pool.
		* @brief  Gets the CharactersFactory of this Pool, used to create new CCharacters.
		*/
		CCharactersFactory* getFactory();
		void setFactory(CCharactersFactory* factory);


		/**
		* @fn     get
		* @param  int Type Type of the CCharacter to get.
		* @param  int subType sub class of the CCharacter to get. An specialization of the character
		* @return A pointer to a CCharacter of the specified type that existed at this Pool, or if not, a new one created with the Factory.
		* @brief  Gets a pointer to a CCharacter of the specified type.\n
		*         If this pool does not contain any object of that type create a new one with the Factory and will return it.\n
		*         If this pool contains an object of the specified type, it will be removed from this pool and returned.\n
		*/
		CCharacter* get(int Type, int subType);

		/**
		* @fn     setSubTypes
		* @param  int Type Type of the CCharacter to set the amount of subtypes it has.
		* @param  int subTypes amount of CCharacter sub classes to set. An specialization of the character
		* @brief  Sets the amount of CCharacters sub classes to set.\n
		*         If this pool has the same amount of sub classes, nothing is done.\n
		*         If this pool has lower amount of sub classes, new ones are created.\n
		*         If this pool has higher amount of sub classes, the excess is deleted.\n
		*/
		void setSubTypes(int Type, int subTypes);

		/**
		* @fn     void save(CCharacter* c)
		* @param  CCharacter* c     Pointer to the CCharacter to be saved at this Pool.
		* @brief  Save the specified CCharacter in this pool
		*/
		bool save(CCharacter* c);

		/**
		* @fn     void Quarantine(CCharacter* c);
		* @param  CCharacter* c     Pointer to the CCharacter to be saved at this Pool.
		* @brief  Save the specified CCharacter in this pool under quarantine guard
		*/
		bool Quarantine(CCharacter* c, HRT_Time T);

		/**
		* @fn     getNumCharacters		
		* @return The total number of CCharacters contained at this Pool.
		* @brief  Gets the total number of CCharacters contained at this Pool.
		*/
		int getNumCharacters();

		/**
		* @fn     getNumCharacters(int characterType)
		* @param  int characterType Type of the CCharacters to count at this Pool.
		* @return The number of CCharacters of the specified type contained at this Pool.
		* @brief  Gets the number of CCharacters of the specified type contained at this Pool.
		*/
		int getNumCharacters(int Type, int subType);

		/**
		* @fn     containsCharacter
		* @return A value indicating if this Pool contains any CCharacter.
		* @brief  Gets a value indicating if this Pool contains any CCharacter.
		*/
		bool containsCharacter();

			/**
		* @fn     containsCharacter
		* @param  int characterType Type of the CCharacters to test at this Pool.
		* @return A value indicating if this Pool contains any CCharacter of the specified Type.
		* @brief  Gets a value indicating if this Pool contains any CCharacter of the specified Type.
		*/
		inline bool containsCharacter(int Type, int subType){return getNumCharacters(Type, subType) > 0;}


		/*All freMemory methods do not destroy any object in quarantine state.
		Only the class destructor does*/

		/**
		* @fn     freeMemory
		* @brief  Free all the memory of the CCharacters at this Pool.
		*/
		void freeMemory();

		/**
		* @fn     freeMemory(int numObjects)
		* @param  int numObjects    Maximum number of CCharacters to delete from memory.
		* @brief  Free the memory of the CCharacters at this Pool.
		*/
		void freeMemory(int numObjects); 

		/**
		* @fn     freeMemoryByType(int characterType)
		* @param  int characterType Type of the CCharacters to delete from memory.
		* @brief  Free the memory of the CCharacters at this Pool corresponding to a specified Type of CCharacter.
		* @return The amount of objects really deleted
		*/
		int freeMemoryByType(int characterType);

		/**
		* @fn     freeMemoryByType(int characterType, int numObjects)
		* @param  int characterType Type of the CCharacters to delete from memory.
		* @param  int numObjects    Maximum number of CCharacters to delete from memory.
		* @brief  Free the memory of the CCharacters at this Pool corresponding to a specified Type of CCharacter.
		* @return The amount of objects really deleted
		*/
		int freeMemoryByType(int characterType, int numObjects);		
	};
}
#endif