/** Header with definitions needed for the management of the characters

*	Prephix = UGKCHAR_

*	@author Ramon Molla
*	@version 2011-10
*/

#ifndef CHAR_INITIALIZATION /// Macro character is erased
#define CHAR_INITIALIZATION /// Macro character is defined

#include <UGKSound.h>
#include <FSM.h>
#include <UGKPhysics.h>
#include <UGKAlgebra.h>
#include <RTDeskEntity.h>
#include <UGKMesh3D.h>

#ifndef DEQUE_LOADED 
#define DEQUE_LOADED 
#include <deque>		// Uses Standard Template Library Double Ended Queue
using namespace std;
#endif

#define CHAR_HEALTH_INFINITE	CHAR_DEFAULT_INDEXES
#define CHAR_NO_TEXTURE			CHAR_DEFAULT_INDEXES
#define CHAR_TEXTUREID			int
/**
	* Define new types of variable for the 2d and 3d animation
*/
typedef enum {
	CHAR_NO_RENDER,			//No render for this character: camera, collision objects,...
	CHAR_2D,
	CHAR_LINES3D,
	CHAR_3D,
	CHAR_MAX_RENDER_MODE	//For management purpouses only. Always at the end of the enumeration
} CHAR_RENDER_MODE;

/**
*	\typedef CHAR_INTERPOLATION_STATE
*	The amount of samples used for interpolation
*/
typedef enum {
	CHAR_CURRENT,			///<Current state. t0
	CHAR_LAST,				///<Previous state. t-1
	CHAR_LAST_LAST,				///<The state previous to the previous state. t-2
	CHAR_MAX_INTERPOLATION_STATES	///<For management purpouses only. Always at the end of the enumeration
} CHAR_INTERPOLATION_STATE;

/**
* Define types for calculation of the AABB 
*/
typedef enum {
	CHAR_AABB_CENTERED,		//Position is set at the very geometric center of the the AABB
	CHAR_AABB_LL,			//Position is set at the left lower corner
	CHAR_AABB_LU,			//Position is set at the left upper corner
	CHAR_AABB_RL,			//Position is set at the right lower corner
	CHAR_AABB_RU,			//Position is set at the right upper corner
	CHAR_MAX_AABB_REL_POS	//For management purpouses only. Always at the end of the enumeration
} CHAR_AABB_REL_POS;

/**
	* We define new types of variable to the sound of the game
*/
typedef enum{
	CHAR_SOUND_HIT,			// Sound emitted when the character has collided with something: bullet, another object
	CHAR_SOUND_EXPLOIDING,	// Sound emitted when the character is exploiding
	CHAR_SOUND_NORMAL,		// Sound emitted when the character by default during its common life
	CHAR_SOUND_MAX_SOUNDS
}CHAR_SoundType;

/**
	* Define the states of a given character while in the system
*/
typedef enum {
	CHAR_DEFAULT_STATE,		///< Not defined. Tipically the object is just created but not stored yet and cannot interact with anything else
	CHAR_QUARANTINE_STATE,	///< When an object is removed from the simulation, any event related with it has to die also as the object does
							///< A good method to do it is to maintain the object "Stored" into the pool while there might be some messages attached to it still scheduled 
							///< If an object may have some remaining messages scheduled for it and it is got alived again before those messages are received, an improper behaviour may be produced.
							///< So a new state has to be performed in order to avoid the object to be rescheduled again before a security time has passed. This is A.K.A. quarantine
	CHAR_STORED_STATE,		///< The character is stored into the characters pool
	CHAR_ALIVE_STATE,		///< If a character has life, it is alive. Alive state means that that it is not active
	CHAR_ACTIVE_STATE,		///< If a character is Active, then it is implicitly Alive
	CHAR_MAX_STATES			///< For management purpouses only. Always at the end of the enumeration
} CHAR_LIFE_STATES;

#define CHAR_NO_AABB			-1
#define CHAR_NO_OBB				-1
#define CHAR_TYPE_UNKNOWN		-1
#define CHAR_DEFAULT_INDEXES	-1

//Collision detection algorithms selection
#define CHAR_USE_QUADTREE			1
//#define CHAR_USE_SWEEP_AND_PRUNE	2

#define CHAR_USE_AABB			2
//#define CHAR_USE_OBB			3
//#define CHAR_USE_SPHERE		4
//#define CHAR_USE_ELLIPSOID	5

#define CHAR_2D_AABB_THICKNESS	0.1		 //Characters are not really and completely flat
#define CHAR_AABB_THICKNESS_DEFAULT	-1.0 //Do not touch the value

#if defined CHAR_USE_AABB || defined CHAR_USE_OBB || defined CHAR_USE_SPHERE || defined CHAR_USE_ELLIPSOID
/**
	* We define new types of variable coordinate ranges
*/

#include <CBBPoint.h>

typedef enum {
	CHAR_BBMIN,	///<Minimum value of Bounding Box
	CHAR_BBMAX, ///<Maximum value of Bounding Box
	CHAR_BBCENTER, ///<Value of the center of the Bounding Box
	CHAR_BBSIZE, ///<Value of the length from center to max or min value
	CHAR_BBMAXCOORDS,
} CHAR_BBCOORD;
#endif

#if defined CHAR_USE_QUADTREE
#include <QuadtreeRoot.h>
#endif

/**
	* Define the class for which the start of the game
	* States of the player dead, alive
	* Game Graphics 2D, 3D
	* Video Game
	* Weapons told in the Game
	* Enemies Artificial Intelligence
	* Moves player
*/

namespace UGK
{
	class CCharactersPool;

	typedef std::vector <CSound*>		CHAR_SOUND_VECTOR;
	typedef std::vector <cHRTimer>		CHAR_TIMER_VECTOR;
	typedef CBBPoint					AABBType[CHAR_BBMAXCOORDS][UGKALG_DIMENSIONS];


	class UGK_API CCharacter :public RTDESK_CEntity
	{
	protected:
		//Attributes
		/// Collection of sounds performed during character's life cycle	
		/// Normally one sound per different state available in the AI FSM
		CHAR_SOUND_VECTOR	Sound;

		/// Name of the file mesh associated to the character's mesh. It does not hold the path to the file.
		UGKS_String			MeshName;
		CHAR_LIFE_STATES	LState;
		HRT_Time			EndQuarantine;

#ifdef CHAR_USE_QUADTREE
		QuadtreeRoot		*QTRoot;
#elif defined CHAR_USE_SWEEP_AND_PRUNE
#endif
		CCharactersPool *Cemetery;

	public:

		/// List of other characters needed to communicate to: a team, mates, managers, singletons to signal or require information from,...
		CharacterList		Directory;
		CHAR_TIMER_VECTOR	Timer;

		//State methods
		inline bool Alive()			{ return CHAR_ALIVE_STATE  == LState || CHAR_ACTIVE_STATE == LState; }
		inline bool Active()		{ return CHAR_ACTIVE_STATE == LState; }
		inline bool Stored()		{ return CHAR_STORED_STATE == LState; }
		inline bool Quarantined()	{ return CHAR_QUARANTINE_STATE == LState; }
		void		EntombMe();		//Set me into the characters pool for later rebirth or use

		//Life Setters and Getters
		inline void Revive		()		{ LState = CHAR_ALIVE_STATE; }
		inline void Deactivate	()		{ LState = CHAR_ALIVE_STATE; }
		inline void Activate	()		{ LState = CHAR_ACTIVE_STATE; }
		inline void SetDefault	()		{ LState = CHAR_DEFAULT_STATE; }
		inline void Store		()		{ LState = CHAR_STORED_STATE; }
		inline void SetCemetery(CCharactersPool *CP) { Cemetery = CP; }
		inline void SetQuarantine(HRT_Time	Quarantine)	{ LState = CHAR_QUARANTINE_STATE; EndQuarantine = Quarantine; }
		inline HRT_Time GetQuarantine()	{ return EndQuarantine; }
#ifdef UGKSG_OSG
		inline CMesh3d* getMesh() { return Mesh; }
#endif

		/// Type of character: bunker, ship, supplyship,...
		int Type,
			SubType;

		/// Amount of time when the character is touched
		float			Hit_duration;

		/// Character's health. How far it is from the death
		float			Health,
		/// Top health a character can have anytime
						MaxHealth;
		/// Character cannot die
		bool			Immortal;

		///The way the character is rendered on the screen
		CHAR_RENDER_MODE RenderMode;
		///The way the character interacts to the rest of the world
		UGKPHY_PHYSIC_MODE PhysicMode;

		///Physical object 
		CPhyObject		*Physical;

		///TODO: Quitar las caracteristicas siguentes por ser redundantes
		UGK::Vector		Position,	///< 3D space coordinates where the character is NOW. It is the center of th AABB
						/// 3D space coordinates where the character was just a main loop before. For PHY_VERLET numeric integrator purpouses. Not used on PHY_EULER numeric integrators.
						PositionPrev,
						/// 3D speed coordinates where the character is going to
						Speed,
						/// 3D acceleration coordinates where the character is speeding up to
						Acceleration,
						/// 3D space orientation in radians
						Rotation,
						/// 3D space proportions
						Scale;

		bool			AIInitialized;
		/// Character Artificial Intelligence is supported by a Finite State Machine (FSM)
		FSM				*AI;
		/// Meshe for the character
		CMesh3d			*Mesh;
		/// Possible Meshes to use
		int				IndMesh;
		/// Textures for the character
		CHAR_TEXTUREID	IndTexture2D,
						IndTexture3D;
		/// Animations for the character
		int				IndAnimation2D;	

		int				ID;
		bool			collided;

	CHAR_AABB_REL_POS	AABBRelPos;	///<Relative position of the AABB respect to the character position

	float		BBRADIUS[UGKALG_DIMENSIONS];
	#ifdef CHAR_USE_QUADTREE
	virtual void SetQTRoot(QuadtreeRoot *QTR) { QTRoot = QTR; };
		void IncQTAmount() { QTRoot->IncCharAmount(Type); }
		void DecQTAmount() { QTRoot->DecCharAmount(Type); }
		inline QuadtreeRoot * GetQTRoot() { return QTRoot; }
	#elif defined CHAR_USE_SWEEP_AND_PRUNE
	#endif
	
	#ifdef CHAR_USE_AABB 
		AABBType			AABB,			//Minimum AABB before transforming the object
							CurrentAABB;	//AABB after TRS transformation
	#elif defined CHAR_USE_OBB 
		Change OBB by an AABB and its quaternion
			AABBType		OBB;
	#endif

		//Methods
		void Init ();

		///Constructor of the class
		CCharacter();
		CCharacter(int Id);
		CCharacter(int Id, int MinVal[WDIM], int MaxVal[WDIM]);
		CCharacter(int Id, int MinVal[WDIM], int MaxVal[WDIM], int Center[WDIM], float Radius[WDIM]);
		
		///Destructor of the class
		//CCharacter::~CCharacter(){}

		//Timer size is always higher than T size since normally T means the global list of timers and Timer includes T plus some local timers
		inline void SetTimers	(CHAR_TIMER_VECTOR T)	{ if (Timer.size() < T.size()) Timer.resize(T.size()); for (unsigned int i = 0; i < T.size(); i++) Timer[i] = T[i]; }
		inline void UpdateSF	(HRTM_SF * SF) { for (unsigned int i = 0; i < Timer.size(); i++) Timer[i].SetSF(SF); }

		inline void			SetMeshName(UGKS_String MN)	{ MeshName = MN; }
		inline UGKS_String	GetMeshName()				{ return MeshName; }
		inline void			SetMesh(CMesh3d * mesh)		{ Mesh = mesh; }

		/**
		@fn virtual void SetLocalTimers();
		*	Creates the local timers the object requires
		*/
		virtual void SetLocalTimers	(unsigned int){};
		void		 ChangeSF(HRTM_SF *SF);		///< Changes the sampling frequency (S.F.) of all the timers used by the character. All the timers have the same S.F.
		inline void  SetSounds		(CHAR_SOUND_VECTOR sound)				{ Sound = sound; }

		inline void		SetSound		(CSound * sound, unsigned int Index)	{ Sound[Index] = sound; }
		inline CSound * GetSound	(unsigned int Index)					{ return Sound[Index]; }
		inline void		SetSoundsAmount	(unsigned int Amount)					{ Sound.resize(Amount); }

		///AI
		inline void OutEvent(STT_EventType Event) { AI->outEvent(Event, NULL, this); }

		void			AI_Reset(void);
		///Default Artificial Intelligence character initialization
		virtual void	AI_Init	(void);
		virtual void	AI_Die	(void);

		///What the character has to do on every time tick 
		virtual void Update (void);
		///Manages all the events received
		virtual void ManageEvent (unsigned int Event);

		//Physics

		inline void SetPhysicalObject(CPhyObject * physical) { Physical = physical; }
		inline CPhyObject * GetPhysicalObject(void) { return Physical; }

		///Recalculates the min and max values of the absolute coordinates of the bounding box
		void CalculateAABB	();
		void CalculateAABB(UGKALG_NUMERIC_TYPE x, UGKALG_NUMERIC_TYPE y, UGKALG_NUMERIC_TYPE z);
		void CalculateAABB(UGK::SpaceCoords Coord);
		///Recalculates the min and max values of the absolute coordinates of the bounding box and inserts the character into the the collision detector
		void InitializeAABB	(void);
		///Recalculates the min and max values of the absolute coordinates of the bounding box and updates the character in the the collision detector
		void UpdateAABB		(void);
		void UpdateAABB		(UGK::SpaceCoords Coord);	///< The same only on a given coord
		void UpdateAABB		(UGKALG_NUMERIC_TYPE x, UGKALG_NUMERIC_TYPE y, UGKALG_NUMERIC_TYPE z);

		void CalculateAABB	(CMesh3d *model);

		bool CollidedAABB	(CCharacter * Character);
		/**Executed when the collision detection system detects a collison with this object although 
		   this object may not be calculating any collision. Every object has to rewrite it in order to perform its proper treatment*/
		virtual void Collided (CCharacter *CollidedChar);

		void	FitMeshIntoBoundingBox		();
		void	FitMeshIntoBoundingBox(CMesh3d *model);
		void	FitBoundingBoxArroundMesh	();
		void	FitBoundingBoxArroundMesh(CMesh3d *model);

		///Removes or insert the object into the collision detection structrues
		void Collisionable(bool Mode)
		{
			if (Mode)
#ifdef CHAR_USE_QUADTREE
				QTRoot->AddCharacter(this);
			else
				QTRoot->RemoveCharacter(this);
#elif defined CHAR_USE_SWEEP_AND_PRUNE
#endif
		}

		inline bool	UpdateCollisionDetection()
		{
#ifdef CHAR_USE_QUADTREE
			return QTRoot->UpdateCharacter(this);
#elif defined CHAR_USE_SWEEP_AND_PRUNE
#endif
		}

		inline CharacterList GetNearestObjectsTo(float Radius)
		{
#ifdef CHAR_USE_QUADTREE
			return QTRoot->GetNearestObjectsTo(Position.v[XDIM], Position.v[YDIM], Radius);
#elif defined CHAR_USE_SWEEP_AND_PRUNE
#endif
		}

		///Shows the character on the screen
		virtual void Render				(void);
		///Change the way the character is going to be rendered on the screen
		virtual void ChangeRenderMode	(CHAR_RENDER_MODE);

		///Generic render method to show on the screen a quad using by default the chosen texture and the position of the caracter as the geometric center of the quad
		void Render2D();

		//Transformation methods
		///Moving by default depending on the miliseconds passed by
		void		 Move		(UGKALG_NUMERIC_TYPE ms);
		///Moves to the absolute coordinate x,y,z
		virtual void MoveTo		(UGKALG_NUMERIC_TYPE x, UGKALG_NUMERIC_TYPE y, UGKALG_NUMERIC_TYPE z);
		///Moving to an absolute position. It does not matter where the character is
		virtual void MoveTo		(Vector &Move);
		virtual void MoveTo(SpaceCoords Dim, UGKALG_NUMERIC_TYPE Value);

		///Moves x,y,z units from the to the current position
		virtual void MoveRelTo	(float x, float y, float z);
		virtual void MoveRelTo	(SpaceCoords Dim, UGKALG_NUMERIC_TYPE Value);

		///Moving relative to the character current Position
		virtual void MoveRelTo	(Vector &Move);

		void ResetTranslation() { Position.v.x = 0.0; Position.v.y = 0.0; Position.v.z = 0.0; }
		void ResetRotation() { Rotation.v.x = 0.0; Rotation.v.y = 0.0; Rotation.v.z = 0.0; }
		void ResetScale() { Scale.v.x = 1.0; Scale.v.y = 1.0; Scale.v.z = 1.0; }

		//RTDesk virtual Function redefinition
		void ReceiveMessage(RTDESK_CMsg *pMsg);
	};
};	//namespace

#endif