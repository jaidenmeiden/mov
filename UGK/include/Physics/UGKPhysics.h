/**	Definition physical structures and types
*	@file UGKPhysics.h
*	Prefix: UGKPHY_
*	@author Ramon Molla
*	@version 2013-05
*	@author Ignacio Pérez & Jesús Ibañez
*	@version 2015-05
*	@author Conrad Bernath
*	@version 2017-01
*/

#ifndef __UGKPHYSICS_H_
#define __UGKPHYSICS_H_

///A continuacion se define cual motor de fisica se va a compilar.
//#define UGKPHY_PHYSX
#define UGKPHY_ODE
//#define UGKPHY_HAVOK
//#define UGKPHY_NEWTON
//#define UGKPHY_UGK

//Pattern fo conditional definitions to use everywhere
#ifdef UGKPHY_PHYSX
#elif defined UGKPHY_ODE
#elif defined UGKPHY_HAVOK
#elif defined UGKPHY_NEWTON
#elif defined UGKPHY_UGK
#endif

#ifndef UGKPHY_PHYSICS
#define UGKPHY_PHYSICS
#endif

///definimos la precisión del motor grafico simple o double
#define dDOUBLE
//#define dSIMPLE ///necesario añadir las lib y dll correspondientes
//máximos puntos de contacto.
#define MAX_CONTACTS 100

//For removing or inserting a character into the collision detection internal structures
#define UGKPHY_COLLISIONABLE true
#define UGKPHY_NON_COLLISIONABLE false

///Determines the way the numerical integration is going to be performed
#define UGKPHY_EULER
//#define UGKPHY_VERLET
//#define UGKPHY_MIDDLEPOINT
//#define UGKPHY_RK4




/**
*	\typedef UGKPHY_DIRECTION
*	Different types of variable direction movements
*	during the development of the game
*/
typedef enum {
	UGKPHY_NO_DIRECTION,
	UGKPHY_UP,
	UGKPHY_DOWN,
	UGKPHY_RIGHT,
	UGKPHY_LEFT,
	UGKPHY_FRONT,
	UGKPHY_BACK,
	UGKPHY_MAX_DIRECTIONS
} UGKPHY_DIRECTION;

/**
*	\typedef UGKPHY_CINEMATIC_ACTION
*	Different types of cinematic actions that can be peformed by the characters
*	during the development of the game
*/
typedef enum {
	UGKPHY_TRASLATION,				///<Moving
	UGKPHY_ROTATION,				///<Rotating
	UGKPHY_SCALE,					///<Scaling
	UGKPHY_SIZE,
	UGKPHY_SPEED,					///<Change Speed value
	UGKPHY_ACCELERATION,			///<Change acceleration value
	UGKPHY_CENTER,
	UGKPHY_MAX_CINEMATIC_ACTION		///<For management purpouses only
} UGKPHY_CINEMATIC_ACTION;


/**
*	\typedef UGKPHY_AABB
*	 Define the different types of bouncing box availables
*	 for the objects
*/
typedef enum {
	UGKPHY_BOX,
	UGKPHY_PLANE,
	UGKPHY_SPHERE,
	UGKPHY_CAPSULE
} UGKPHY_AABB;


/**
*	\typedef UGKPHY_PHYSIC_MODE
*	Define the different types of physics modes supported
*	by UGK
*/
typedef enum {
	UGKPHY_PHANTOM,				///<No render, No touchable: camera
	UGKPHY_INVISIBLE,			///<No render, touchable: collision objects,...
	UGKPHY_LIGHT,				///<Visible but not touchable
	UGKPHY_PHYSICAL,			///<Normal objects: can be rendered and touched
	UGKPHY_MAX_PHYSIC_MODE		///<For management purpouses only. Always at the end of the enumeration
} UGKPHY_PHYSIC_MODE;


namespace UGK
{
	
	/**
	* Define the class which have the information
	* about the material of a physics object
	*/
	class CPhyMaterial
	{
	public:
		float staticFriction;
		float dynamicFriction;
		float restitution;
		CPhyMaterial(float staticFriction, float dynamicFriction, float restitution);
	};

	/**
	* Define the class with the information of a physics object:
	* Geometry, material, linear velocity, angular damping
	* and the transformations
	*/
	class CPhyObject
	{
	public:
		CPhyMaterial* material;
		UGKPHY_AABB aabb;
		float mass;
		float dimension[3];
		float position[3];
		float angularDamping;
		float linearVelocity[3];
		/// Angle to turn around the plane
		float angleAxis;
		/// plane for turn
		float plane[3];


		/// Create a CPhyObject instance of the type define by the physics engine selected.
		static CPhyObject *createPhysicsObject(CPhyMaterial* material, UGKPHY_AABB aabb);
		/// Get the position of the physical object
		virtual float* getPosition() = 0; 
		/// Get the rotation matrix of the physical object
		virtual float* getRotation() = 0;
		/// Get the trasnformation Matrix of the physical object
		virtual void getTransformationMatrix(float* matrix) = 0;
		/// Set the dimension of the object
		virtual void setDimension(float x, float y, float z) = 0;
		/// Get the dimension of the object
		virtual float getDimension() = 0;
		/// Set the position of the object
		virtual void SetPosition(float x, float y, float z) = 0;
		/// Set the linear velocity of the object
		virtual void setLinearVelocity(float x, float y, float z) = 0;
		/// Turns the Plane
		virtual void setTurnPlane(float angle, float x, float y, float z) {};
	};

	/**
	* Defines the class to the physics engine
	*/
	//class UGK_API CPhysicsEngine
	class CPhysicsEngine
	{
	private:

	public:
		/// Tells whether the object is enable
		bool enabled;
		/// Initialize physics object
		virtual void initialize() = 0;
		/// Add object to the scene
		virtual void addObject(CPhyObject* object)=0;
		/// Set the gravity of the physics world
		virtual void setGravity(float x, float y, float z) = 0;
		/// Do a physic simulation, the time step in Hz
		virtual void nextStep(double time) = 0;
		/// Finalize physics object
		virtual void finalize() = 0;
		/// Return a instance of a physics engine selected.
		static CPhysicsEngine *getInstance();

	private:
		///Internal function to collision detection
	};
}

#endif


