/**	Collision detection classes

*	Prefix: CD_

*	@author Ramon Molla
*	@version 2011-07
*/

#ifndef CD_COLLISION_DETECT
#define CD_COLLISION_DETECT

#include <UGKCharacter.h>

typedef enum {
	CD_POSITION_OUTRANGE,
	CD_ERROR_MAX_LOGMSG
} CD_PhysicsMsg;

typedef enum {
	CD_CURRENT_CHARACTER,
	CD_CHARACTER_COLLIDED,
	CD_MAX_CHARACTERS_COLLIDED
} CD_CHARACTERS_COLLIDED;

/**
*	\class CCollisionDetection
*
*/
namespace UGK
{
	class UGK_API CCollisionDetection
	{
	public:
#if defined CHAR_USE_AABB || defined CHAR_USE_SPHERE
#elif defined CHAR_USE_OBB
#endif

		deque<CBBPoint*> CharactersCollided[CD_MAX_CHARACTERS_COLLIDED];	///<List of pairs of characters collided one another
		bool CheckCollided(deque<CBBPoint*> CollidedCharacters);

#ifdef CHAR_USE_QUADTREE
		QuadtreeRoot QTRoot;
#elif defined CHAR_USE_SWEEP_AND_PRUNE
		deque<CBBPoint*> Axis[UGKALG_DIMENSIONS];	///<List of characters ordered by position on every axis dimension
		CharacterList SweepAndPrune(CharacterList characters);

		void inline UpdateMax(CCharacter *C, SpaceCoords Dim) { UpdateBBPoint(C->AABB[CHAR_BBMAX][Dim].Position, Dim); }
		void inline UpdateMin(CCharacter *C, SpaceCoords Dim) { UpdateBBPoint(C->AABB[CHAR_BBMIN][Dim].Position, Dim); }
		void		UpdateBBPoint(unsigned int i, SpaceCoords Dim);
		void		Renumber(UGK::SpaceCoords Dim, unsigned int p);
#endif

		///<The first one of [0] with the first one of [1], the second one of [0] with the second one of [1] and so on

		void Insert(CCharacter *C);			///<Inserts a new object into the structure
		void Remove(CCharacter *C);			///<Deletes an object from the structure

		void Update(CCharacter *C);			///<Updates an object AABB inside the structure.

		void Init(void);

		CCollisionDetection() { Init(); }

		void DetectCollisions(void);	///<Performs a general collision detection for all the virtual world

		bool Collided(CCharacter *C1, CCharacter *C2);	///<Returns if both objects have collided one another. If no collision detected between them, false is returned
		bool Collided(CCharacter *C, UGK::SpaceCoords Dim);	///<Returns if any object has collided with object C on dimension Dim. If no one has collided, false is returned
		bool Collided(CCharacter *C);	///<Returns if any object has collided with object C. If no one has collided, false is returned

		void Reset();	///<Frees all deques and extracts all characters from the collision detector
	};
}

#endif