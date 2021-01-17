/**	Physics declarations
*   @autor Conrad Bernath V
*	@version 2017-02
*/

#include <stdio.h>
#include <ctime>
#include <iostream>
#include <UGKPhysics.h>
#include <deque>

#if defined(UGKPHY_ODE)  
#include <UGKPhysicsODE.h>
#elif defined(UGKPHY_PHYSX)  
#include <UGKPhysicsPhysx.h>
#elif defined(UGKPHY_NEWTON)    
#include <UGKPhysicsNewton.h>
#endif 

using namespace UGK;

/**
*
* @brief Constructor of CPhyMaterial object
*
* This class returns a instance of a Physicas object depending of the
* choosen engine
* @param sf property staticFriction of material.
* @param df property dynamicFriction of material.
* @param r property restitution of material.

*/
CPhyMaterial::CPhyMaterial(float sf, float df, float r) {
	staticFriction = sf;
	dynamicFriction = df;
	restitution = r;
}


/**
* Creates a physics object of type CPhyObjectODE
*/
CPhyObject * CPhyObject::createPhysicsObject(CPhyMaterial * material, UGKPHY_AABB aabb)
{
	#if defined(UGKPHY_ODE)  
		return new CPhyObjectODE(material, aabb);
	#elif defined(UGKPHY_PHYSX)  
	//#include <UGKPhysicsPhysx.h>
	#elif defined(UGKPHY_NEWTON)    
	#include <UGKPhysicsNewton.h>
	#endif 
	return NULL;
}


CPhysicsEngine * CPhysicsEngine::getInstance()
{
#if defined(UGKPHY_ODE)  
	return CPhysicsEngineODE::getInstance();
#elif defined(UGKPHY_PHYSX)  
	//#include <UGKPhysicsPhysx.h>
#elif defined(UGKPHY_NEWTON)    
#include <UGKPhysicsNewton.h>
#endif 
	return NULL;
}