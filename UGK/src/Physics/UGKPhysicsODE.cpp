/**	Physics declarations
*	@author Ignacio Pérez & Jesús Ibañez
*	@version 2015-05
*/




#include <stdio.h>
#include <ctime>
#include <iostream>
#include <UGKPhysics.h>

#if defined(UGKPHY_ODE)  
#include <UGKPhysicsODE.h>
#include <deque>

using namespace UGK;
using namespace std;

  /**
  * Initialize ODE static attributes
  */
	dWorldID CPhysicsEngineODE::world = dWorldCreate();
	dSpaceID CPhysicsEngineODE::space = dHashSpaceCreate (0); // Collision space
	dJointGroupID CPhysicsEngineODE::contactgroup = dJointGroupCreate (0); // Groups of contact


/**
*
* @brief Constructor of CPhysics object
*
* This class returns a instance of a Physics object depending of the
* choosen engine
* @param choice enum of the physics engine you want to instantiate.
*/
CPhysicsEngine * CPhysicsEngineODE::getInstance()
{
	return new CPhysicsEngineODE();
}

/**
  * Initialize CPhysics class
  */
CPhysicsEngineODE::CPhysicsEngineODE() {
  enabled = true;
}

/**
  * Initialize physics object
  */
void CPhysicsEngineODE::initialize() {

	///Obligatory function to start ODE
	dInitODE();
	///Error correctinos, use typical values
	dWorldSetCFM (world,1e-5);
	dWorldSetERP(world, 0.2);
	///Autodisable when a body isn't use for a long time.
	dWorldSetAutoDisableFlag (world,1);
	///Value use to solving "popping"
	dWorldSetContactMaxCorrectingVel (world,0.9);
	///use to define the dpeth to the contact
	dWorldSetContactSurfaceLayer (world,0.001);

}

/**
  * Add object to the scene
  */
void CPhysicsEngineODE::addObject(CPhyObject* object) {
  ///two types of implementations
  switch (object->aabb)
  {
  /// if it is a plane...
  case UGKPHY_PLANE:
    {
		///dCreatePlane (space,0,1,0,0);
		dCreatePlane (space,object->position[0],object->position[1]+1,object->position[2],0);
    }
    break;
  /// if it is a box...
  case UGKPHY_BOX:
    {
	CPhyObjectODE* object2= dynamic_cast<CPhyObjectODE*>(object);
    dMass m;
	
	object2->shape = new ODE_Shape();

	object2->shape->body = dBodyCreate (world);
	dBodySetPosition(object2->shape->body, object->position[0],object->position[1],object->position[2]);

	dMatrix3 R;
	dRFromAxisAndAngle(R,object->plane[0],object->plane[1],object->plane[2],object->angleAxis);
	dBodySetRotation (object2->shape->body,R);
 
	dMassSetBoxTotal (&m, object->mass,object->dimension[0], object->dimension[1],object->dimension[2]);
	dBodySetMass (object2->shape->body,&m);

	object2->shape->geom = dCreateBox (space,object->dimension[0],object->dimension[1],object->dimension[2]);

	dBodySetLinearVel(object2->shape->body, object->linearVelocity[0], object->linearVelocity[1], object->linearVelocity[2]);

	dBodySetAngularDamping (object2->shape->body, object->angularDamping);

    ///define what geometry with what body.
    dGeomSetBody (object2->shape->geom, object2->shape->body);
    }
    break;
  }

}

/**
  * Set the gravity to the world
  */
void CPhysicsEngineODE::setGravity(float x, float y, float z) {
  ///Change ODE Gravitity
  dWorldSetGravity (world,x,y,z);
}


/**
  * Set the time step in Hz
  */
void CPhysicsEngineODE::nextStep(double time) {
  ///add our colliction function
  dSpaceCollide (space,0,&nearCallback);
  ///Do a physic simulation
  dWorldStep(world, time);
  ///Delete all join creates.
  dJointGroupEmpty (contactgroup);

}

/**
  * Finalize physics object
  */
void CPhysicsEngineODE::finalize() {

  /// Destroy all joints in our joint group
  dJointGroupDestroy(contactgroup);
  /// Destroy the collision space. 
  dSpaceDestroy(space);
  /// Destroy the world
  dWorldDestroy(world);

}


/**
  * Create new physics object
  */
CPhyObjectODE::CPhyObjectODE(CPhyMaterial* m, UGKPHY_AABB a)
{
  material = m;
  aabb = a;
}


void CPhyObjectODE::setDimension(float x, float y, float z)
{
  dimension[0] = x;
  dimension[1] = y;
  dimension[2] = z;
}

float CPhyObjectODE::getDimension() {
  return dimension[0];
}

void CPhyObjectODE::setLinearVelocity(float x, float y, float z)
{
  linearVelocity[0] = x;
  linearVelocity[1] = y;
  linearVelocity[2] = z;
}

void CPhyObjectODE::setTurnPlane(float angle, float x, float y, float z)
{
  angleAxis = angle;
  plane[0] = x;
  plane[1] = y;
  plane[2] = z;
}

void CPhyObjectODE::SetPosition(float x, float y, float z)
{
  position[0] = x;
  position[1] = y;
  position[2] = z;
}

float* CPhyObjectODE::getPosition() {
	return (float*)dGeomGetPosition (shape->geom);
  
}

float* CPhyObjectODE::getRotation() {
  return (float*) dGeomGetRotation(shape->geom);;
}

/**
* Get the transformation matrix needed to synchronize 
* physics objects with visual objects
*/
void CPhyObjectODE::getTransformationMatrix(float* matrix) {
  const dReal* pos = dGeomGetPosition (shape->geom);
  const dReal* r = dGeomGetRotation(shape->geom);

  ///matrix content the transformation matrix
  matrix[0]  = r[0]; matrix[1]  = r[4]; matrix[2]  = r[8]; matrix[3]  = 0;
  matrix[4]  = r[1]; matrix[5]  = r[5]; matrix[6]  = r[9]; matrix[7]  = 0;
  matrix[8]  = r[2]; matrix[9]  = r[6]; matrix[10] = r[10];matrix[11] = 0;
  matrix[12] = pos[0]; matrix[13] = pos[1]; matrix[14] = pos[2]; matrix[15] = 1;

}

///function that check collition into two bodies
void CPhysicsEngineODE::nearCallback (void *data, dGeomID o1, dGeomID o2) {
  int i;
 
  ///recover the bodies
  dBodyID b1 = dGeomGetBody(o1);
  dBodyID b2 = dGeomGetBody(o2);

  ///If they has a join yet, do nothing.
  if (b1 && b2 && dAreConnectedExcluding (b1,b2,dJointTypeContact)) return;
 
  ///create a contact struct 
  dContact contact[MAX_CONTACTS]; 
  for (i=0; i<MAX_CONTACTS; i++) {
    contact[i].surface.mode = dContactBounce | dContactSoftCFM;
	contact[i].surface.mu = 5.0;
    //contact[i].surface.mu2 = 0;
    contact[i].surface.bounce = 1;
    //contact[i].surface.bounce_vel = 0.1;
    contact[i].surface.soft_cfm = 0.01;
	/*contact[i].surface.rho = 0.5;
	contact[i].surface.rho2 = 0.5;*/
  }

  ///recover contact points
  int numc = dCollide (o1,o2,MAX_CONTACTS,&contact[0].geom, sizeof(dContact));

  ///If one or more contact point...create a join
  if (numc!=0) {
    for (i=0; i<numc; i++) {
      dJointID c = dJointCreateContact (world,contactgroup,&contact[i]);
      dJointAttach (c,b1,b2);
    }
  }
}

#endif