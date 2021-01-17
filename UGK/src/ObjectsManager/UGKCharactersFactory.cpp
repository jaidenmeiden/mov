/**	
 *	@file	 UGKCharactersFactory.cpp
 *	@author  Ramón Mollá
 *	@date	 2016-06-25
 *  @version 1.0
 *
 *	@brief	 Provide methods to create new by default CCharacters objects. \n
 *
 *	Prefix: UGKOBJM_
 **/

#include <UGKCharactersFactory.h>
#include <UGKCameraManager.h>
#include <UGKParticleSystem.h>
#include <map>

using namespace UGK;

CCharacter* CCharactersFactory::GeneralCreateNewCharacter(int Type, int subType)
{
	CCharacter *CAux;

	if (Type >= UGK_MAX_RESERVED_CHARS)
		//This is a user type character generation
		return createNewCharacter(Type, subType);
	else
	{
		switch (Type)
		{
		case UGK_CHARACTER_UNKNOWN:
			CAux = new CCharacter();
			break;
		case UGK_CAMERA:
			CAux = new CCamera();
			break;
		case UGK_CAMERA_MNGR:
			CAux = new UGKCCameraManager();
			break;
		case UGK_PARTICLE:
//			CAux = new CParticle();
			break;
		case UGK_PARTICLE_SYSTEM:
			//CAux = new CParticleSystem();
			break;
		}

		CAux->SetDefault();	//Indicate to the requester that this character was made from scratch
#ifdef CHAR_USE_QUADTREE
		CAux->SetQTRoot(QTRoot);
#elif defined CHAR_USE_AABB
#endif
		
		return CAux;
	}
}