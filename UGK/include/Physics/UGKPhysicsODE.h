/**	Definition physics structures and types for ODE engine

*	Prefix: UGKPHY_

*	@author Conrad Bernath
*	@version 2017-02
*/


#include "UGKPhysics.h"

#ifndef __UGKPHYSICSODE_H_
#define __UGKPHYSICSODE_H_



#include <ode\ode.h>
#pragma comment(lib, "ode_doubled.lib")


struct ODE_Shape {
	dBodyID body;       /// Body
	dGeomID geom;       /// GeometricElement
};


namespace UGK
{

  /**
  * Define the class with the information of an physics object of ODE type:
  * Geometry, material, linear velocity, angular damping 
  * and the transformations
  */
  class CPhyObjectODE : public CPhyObject
  {
  public:
	
	ODE_Shape* shape;
	
	CPhyObjectODE(CPhyMaterial* material, UGKPHY_AABB aabb);
    float* getPosition() override;
	float* getRotation() override;
	void getTransformationMatrix(float* matrix) override;
    void setDimension(float x, float y, float z) override;
    float getDimension() override;
    void SetPosition(float x, float y, float z) override;
    void setLinearVelocity(float x, float y, float z) override;
    void setTurnPlane(float angle, float x, float y, float z) override;


  };

  /**
  * Define the class with the information of a ODE physics engine:
  * world, space, contactgroup, besides the ones inhereted from the 
  * the parent class CPhysics
  */
  //class UGK_API CPhysics
  class CPhysicsEngineODE: public CPhysicsEngine
  {
  private:
		/// Main ODE variable
		static dWorldID world; //mundoODE
		static dSpaceID space; //espacio de colisiones
		static dJointGroupID contactgroup; // grupos de contacto


  public:
	    static CPhysicsEngine * getInstance();
		bool enabled;

		void initialize() override;
		void addObject(CPhyObject* object) override;
		void setGravity(float x, float y, float z) override;
		void nextStep(double time) override;
		void finalize() override;

  private:
		///Internal function to collision detection
		static void nearCallback (void *data, dGeomID o1, dGeomID o2);
		CPhysicsEngineODE();
  };
}

#endif