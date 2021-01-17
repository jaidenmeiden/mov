/**	
 *	@file	 UGKCharactersFactory.h
 *	@author  Santiago Jim&eacute;nez Serrano [sanjiser@gmail.com]
 *			 Refactoring and adaptation: Ramón Mollá
			 Subtypes support
*	@date	 2017-02
*   @version 1.1
 *
 *	@brief	 Definition of interface CCharactersFactory.\n
 *			 Provide methods to create new CCharacters objects. \n
 *           Its methods must be implemented on a child class to provide fully functionallity.\n
 *           Used in CCharactersPool.\n
 *			 Its behaviour corresponds to an Objects Factory of type CCharacter.\n
 *
 *	Prefix: UGKOBJM_
 **/


#ifndef UGKOBJM_CHARACTERSFACTORY
#define UGKOBJM_CHARACTERSFACTORY

#include <map>
#include <UGKCharacter.h>

namespace UGK
{

	typedef enum
	{
		UGK_NO_CHARACTER,
		UGK_CHARACTER_UNKNOWN, ///<For management purpouses only
		UGK_CAMERA,
		UGK_CAMERA_MNGR,
		UGK_PARTICLE,
		UGK_PARTICLE_SYSTEM,
		UGK_MAX_RESERVED_CHARS
	}UGKOBJM_UGK_CHARS;

	typedef unsigned int UGKOBJM_CharacterType;

	/**
	 * @brief CCharactersFactory \n
	 * Interface to provide methods to create new CCharacters objects.\n
	 * Represents a Factory of CCharacters objects.
	 */
	class UGK_API CCharactersFactory
	{
	protected:
		map<UGKS_String, UGKOBJM_CharacterType> CharacterDict;

	#ifdef CHAR_USE_QUADTREE
		QuadtreeRoot		*QTRoot;
	#elif defined CHAR_USE_AABB
	#endif

	public:

		CCharactersFactory()
		{
#ifdef CHAR_USE_QUADTREE
			QTRoot = NULL;
#elif defined CHAR_USE_AABB
#endif
		}

		~CCharactersFactory()
		{
#ifdef CHAR_USE_QUADTREE
			if (NULL != QTRoot) delete QTRoot;
#elif defined CHAR_USE_AABB
#endif
		}

		///Initializes the name dictionary that allows to convert a lexeme to a token when parsing. Lexic analyzer
		inline void InitDict(const UGKS_String CHARS_Tags[], unsigned int Size){for (unsigned int i = 0; i < Size; i++) CharacterDict[CHARS_Tags[i]] = i;}
		inline void InitDict(const UGKS_String CHARS_Tags[], unsigned int First, unsigned int Last){ for (unsigned int i = 0; i <= Last-First; i++) CharacterDict[CHARS_Tags[i]] = i+First; }
		inline UGKOBJM_CharacterType Lexeme2Token(UGKS_String Name) { return CharacterDict[Name]; }

#ifdef CHAR_USE_QUADTREE
		inline void SetQTRoot(QuadtreeRoot *QTR) { QTRoot = QTR; }
#elif defined CHAR_USE_AABB
#endif
		
		/**
		 * @fn     CCharacter* GeneralCreateNewCharacter(int characterType)
		 * @param  int characterType Type of CCharacter to be created.
		 * @return Pointer to the new CCharacter created.
		 * @brief  Creates a new CCharacter of the specified type.\n
		 */
		CCharacter* GeneralCreateNewCharacter(int Type, int subType);

		/**
		 * @fn     createNewCharacter
		 * @param  int Type Type of CCharacter to be created.
		 * @return Pointer to the new CCharacter created.
		 * @brief  Creates a new CCharacter of the specified type.\n
		 *         Pure Virtual Function. It must be redefined in the child class.		 
		 */
		virtual CCharacter* createNewCharacter(int Type, int subType) = 0; // adding = 0 makes the function pure virtual. Otherwise it is necessary to implement it.

		/**
		 * @fn     getNumDistinctCharacterTypes
		 * @return The number of different types of Characters that this factory can produce.
		 * @brief  Gets the total number of different types of Characters that this factory can produce. \n
		 *         Pure Virtual Function. It must be redefined in the child class.
		 */
		inline int getNumDistinctCharacterTypes()
		{
			return CharacterDict.size();
		}
	};
}

#endif