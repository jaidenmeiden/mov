/**	@file Character.cpp
	Clases, types, definitions, constants,..
	related with any kind of characters that may appear in the game

	@author Ramon Molla
	@version 2011-09
*/

#include <UGKCharactersPool.h>
#include <CollisionDetect.h>
#include <float.h>

using namespace UGK;

CCollisionDetection CollisionDetector;	/// The collision detector used to verify collisions between objects. Singleton

/**
	* Artificial Intelligence starts
	* It starts the game map checking that there is no collision with the ship and call CCharacter :: Init function to start the Ship
*/
CCharacter::CCharacter()
{
	ID = 0;
	collided = false;

	///Initializes the AABB
#ifdef CHAR_USE_AABB
	for (unsigned int i=XDIM;i<WDIM;i++)
	{
		///Initially there is no collision detector position assigned
		AABB[CHAR_BBMIN][i].Position = CHAR_NO_AABB;
		AABB[CHAR_BBMAX][i].Position = CHAR_NO_AABB;

		AABB[CHAR_BBMIN][i].Value = 0.0;
		AABB[CHAR_BBMAX][i].Value = 0.0;

		AABB[CHAR_BBMIN][i].Character	= this;
		AABB[CHAR_BBMAX][i].Character	= this;
	}
#elif defined CHAR_USE_SPHERE
#elif defined CHAR_USE_ELLIPSOID
#elif defined CHAR_USE_OBB	
	for (int j = 0; j < CHAR_BBMAXCOORDS; j++)
		for (unsigned int i = XDIM; i<WDIM; i++)
		{
			///Initially there is no collision detector position assigned
			OBB[j][i].Position = CHAR_NO_OBB;
			OBB[j][i].Value = 0.0;
			OBB[j][i].Character = this;
		}

#endif

	Init(); /// It starts the player's ship
}	


CCharacter::CCharacter(int ID, int MinVal[WDIM], int MaxVal[WDIM])
{
	CCharacter();
	this->ID = ID;
#ifdef CHAR_USE_AABB
	for (unsigned int i = XDIM; i<WDIM; i++)
	{
		///Initially there is no collision detector position assigned
		AABB[CHAR_BBMIN][i].Value = MinVal[i];
		AABB[CHAR_BBMAX][i].Value = MaxVal[i];
	}
#elif defined CHAR_USE_SPHERE
#elif defined CHAR_USE_ELLIPSOID
#elif defined CHAR_USE_OBB	
	for (int j = 0; j < CHAR_BBMAXCOORDS; j++)
		for (unsigned int i = XDIM; i<WDIM; i++)
		{
			///Initially there is no collision detector position assigned
			OBB[j][i].Position = CHAR_NO_OBB;
			OBB[j][i].Value = 0.0;
			OBB[j][i].Character = this;
		}
#endif
}

/**
	* Constructor for the object or the Game CCharacter
	* Start the type of ship you choose, the size and position the living state
	* Starts the ship in 2D
*/
void CCharacter::Init ()
{
	//Different character that may be loaded during the parsing
	///During the character initialization, the type of character is not known
	Type	=	CHAR_TYPE_UNKNOWN;
	SubType =	CHAR_TYPE_UNKNOWN;

	/// By default when a character is created, is not active but it is alive
	Revive();
	//The caracter is always set at a neutral position (0,0,0) and with no size
	Position.Reset();
	AABB[CHAR_BBSIZE][XDIM].Value = 0.0;
	AABB[CHAR_BBSIZE][YDIM].Value = 0.0;
	AABB[CHAR_BBSIZE][ZDIM].Value = 0.0;


	///Do not perform action MoveTo (0.0f, 0.0f, 0.0f);	at this very moment because no insertion of character AABB has been performed in the collision detector
	///A move will call updateAABB which will produce an error
	Speed.Reset();
	Acceleration.Reset();

	///By default, render is always in 2D
	RenderMode	=	CHAR_2D;
	///By default, it is a normal object, so it can be rendered and touched
	PhysicMode	=	UGKPHY_PHYSICAL;

	///Default values for Bounding Box. Every inherited class manages if it has AABB.
#ifdef CHAR_USE_QUADTREE
	AABB[CHAR_BBMIN][XDIM].Value=FLT_MAX;
	AABB[CHAR_BBMIN][YDIM].Value=FLT_MAX;
	AABB[CHAR_BBMIN][ZDIM].Value=FLT_MAX;
	AABB[CHAR_BBMAX][XDIM].Value=FLT_MIN;
	AABB[CHAR_BBMAX][YDIM].Value=FLT_MIN;
	AABB[CHAR_BBMAX][ZDIM].Value=FLT_MIN;
	Position.v[XDIM]=0;
	Position.v[YDIM]=0;
	Position.v[ZDIM]=0;
#endif

	IndTexture2D	= CHAR_NO_TEXTURE;
	IndTexture3D	= CHAR_NO_TEXTURE;
	IndMesh			= CM3D_NO_MESH;
	IndAnimation2D	= CHAR_DEFAULT_INDEXES;

	AI				= NULL;
	AIInitialized	= false;
}

void CCharacter::EntombMe() { Cemetery->save(this); }	//Set me into the characters pool for later rebirth or use

void CCharacter::ChangeSF(HRTM_SF *SF)		///< Changes the sampling frequency (S.F.) of all the timers used by the character. All the timers have the same S.F.
{
	unsigned int i;
	for (i = 0; i < Timer.size(); i++)
		Timer[i].ResetSamplingFrequency(SF);
}

void CCharacter::AI_Init (void)
{

}

///Removes any behaviour from the character. No matter which one may be. It is the same for all characters in the game
void CCharacter::AI_Reset (void)
{
	if (NULL != AI)
		AI->Init();

	AI = NULL;
	AIInitialized = false;
}

/**
	* Disables the character
*/
void CCharacter::AI_Die (void)
{
	SetDefault();
	EntombMe();
}

void CCharacter::Update (void)	///What the character has to do on every time tick 
{
		//By the moment, nothing to do on every time tick. Every character type has to implement it 
	

}

void CCharacter::ManageEvent (unsigned int Event)	//Manages all the events received
{
}

/**
* Recalculates the minimum and maximum values of the absolute coordinates of the bounding box
*/
void CCharacter::CalculateAABB(UGKALG_NUMERIC_TYPE x, UGKALG_NUMERIC_TYPE y, UGKALG_NUMERIC_TYPE z)
{
#ifdef CHAR_USE_AABB
	unsigned int i;
	UGKALG_SimpleVector HalfSize, size;

	HalfSize.x = x;
	HalfSize.y = y;
	HalfSize.z = z;
	size = HalfSize;
	HalfSize *= 0.5f;

	//Current implementation does not support rotation applied to the AABB. Only scale and translation
	for (i = XDIM; i < WDIM; i++)
		if (size.v[i] > 0.0)
		{
			HalfSize.v[i] *= Scale.v[i];
			AABB[CHAR_BBSIZE][i].Value = size.v[i];
			CurrentAABB[CHAR_BBMIN][i].Value = Position.v[i] - HalfSize.v[i];
			CurrentAABB[CHAR_BBMAX][i].Value = Position.v[i] + HalfSize.v[i];
		}
#endif
}
/**
	* Recalculates the minimum and maximum values of the absolute coordinates of the bounding box
*/
void CCharacter::CalculateAABB ()
{
#ifdef CHAR_USE_AABB
	unsigned int i;
	float HalfSize;

	for (i=XDIM;i<WDIM;i++)
	{
		//Current implementation does not support rotation applied to the AABB. Only scale and translation
		HalfSize = AABB[CHAR_BBSIZE][i].Value * 0.5f * Scale.v[i];

		CurrentAABB[CHAR_BBMIN][i].Value = Position.v[i] - HalfSize;
		CurrentAABB[CHAR_BBMAX][i].Value = Position.v[i] + HalfSize;
		//Attribute Position is given by the collision detector
	}
#elif defined CHAR_USE_OBB
	/// Initialization of the OBB
	unsigned int i, j;
	float Fragsize;

	for (i = XDIM; i<WDIM; i++)
	{
		Fragsize = Size / CHAR_BBMAXCOORDS -1;
		/// Fragment the Bounding Box in to 8 Subparts (Tree structure)
		for (j = CHAR_BBMIN; j < CHAR_BBMAXCOORDS; j++) {
			
			OBB[j][i].Value = Position.v[i] - ((CHAR_BBMAXCOORDS - 1 - j)*FragSize);

		}
		///Attribute Position is given by the collision detector
	}
#elif defined CHAR_USE_QUADTREE
#endif
}

void CCharacter::CalculateAABB (CMesh3d *model)
{
#ifdef UGKSG_OSG

#elif defined CHAR_USE_AABB || defined CHAR_USE_QUADTREE

	//unsigned int quantity=0;
	//
	//for (int i = XDIM; i < WDIM; i++)
	//	AABB[CHAR_BBCENTER][i].Value = 0.0;

	//for(int i=0;i<model->modelo.numObjects;i++){
	//	for(int j=0;j<model->modelo.Objects[i].numVerts*3;j++){
	//
	//		switch (j%3)
	//		{
	//		case 0:
	//			//X
	//			AABB[CHAR_BBCENTER][XDIM].Value +=model->modelo.Objects[i].Vertexes[j];
	//			break;
	//		case 1:
	//			//Y
	//			AABB[CHAR_BBCENTER][YDIM].Value +=model->modelo.Objects[i].Vertexes[j];
	//			
	//			break;
	//		case 2:
	//			//Z
	//			AABB[CHAR_BBCENTER][ZDIM].Value +=model->modelo.Objects[i].Vertexes[j];
	//			
	//			break;
	//		}
	//		quantity++;
	//	}
	//
	//}

	//quantity/=3;

	//AABB[CHAR_BBCENTER][XDIM].Value /=quantity;
	//AABB[CHAR_BBCENTER][YDIM].Value /=quantity;
	//AABB[CHAR_BBCENTER][ZDIM].Value /=quantity;
	
	if (NULL != model)
	{
		for (int i = 0; i < model->modelo.numObjects; i++) {
			for (int j = 0; j < model->modelo.Objects[i].numVerts * 3; j++) {

				switch (j % 3)
				{
				case 0:
					//X
					if (model->modelo.Objects[i].Vertexes[j] > AABB[CHAR_BBMAX][XDIM].Value) AABB[CHAR_BBMAX][XDIM].Value = model->modelo.Objects[i].Vertexes[j];
					if (model->modelo.Objects[i].Vertexes[j] < AABB[CHAR_BBMIN][XDIM].Value) AABB[CHAR_BBMIN][XDIM].Value = model->modelo.Objects[i].Vertexes[j];
					break;
				case 1:
					//Y
					if (model->modelo.Objects[i].Vertexes[j] > AABB[CHAR_BBMAX][YDIM].Value) AABB[CHAR_BBMAX][YDIM].Value = model->modelo.Objects[i].Vertexes[j];
					if (model->modelo.Objects[i].Vertexes[j] < AABB[CHAR_BBMIN][YDIM].Value) AABB[CHAR_BBMIN][YDIM].Value = model->modelo.Objects[i].Vertexes[j];

					break;
				case 2:
					//Z
					if (model->modelo.Objects[i].Vertexes[j] > AABB[CHAR_BBMAX][ZDIM].Value) AABB[CHAR_BBMAX][ZDIM].Value = model->modelo.Objects[i].Vertexes[j];
					if (model->modelo.Objects[i].Vertexes[j] < AABB[CHAR_BBMIN][ZDIM].Value) AABB[CHAR_BBMIN][ZDIM].Value = model->modelo.Objects[i].Vertexes[j];


					break;
				}
			}
		}
		//X Horizontal
		//Y Profundidad
		//Z Vertical
		/// Axis Aligned Bounding Box Width, Height and deep. Bounding box in local coordinates.
		AABB[CHAR_BBSIZE][XDIM].Value = AABB[CHAR_BBMAX][XDIM].Value - AABB[CHAR_BBMIN][XDIM].Value;
		AABB[CHAR_BBSIZE][YDIM].Value = AABB[CHAR_BBMAX][YDIM].Value - AABB[CHAR_BBMIN][YDIM].Value;
		AABB[CHAR_BBSIZE][ZDIM].Value = AABB[CHAR_BBMAX][ZDIM].Value - AABB[CHAR_BBMIN][ZDIM].Value;

		AABB[CHAR_BBCENTER][XDIM].Value = AABB[CHAR_BBSIZE][XDIM].Value * 0.5f;
		AABB[CHAR_BBCENTER][YDIM].Value = AABB[CHAR_BBSIZE][YDIM].Value * 0.5f;
		AABB[CHAR_BBCENTER][ZDIM].Value = AABB[CHAR_BBSIZE][ZDIM].Value * 0.5f;
	}
	else
	{
		AABB[CHAR_BBSIZE][XDIM].Value = 0.0;
		AABB[CHAR_BBSIZE][YDIM].Value = 0.0;
		AABB[CHAR_BBSIZE][ZDIM].Value = 0.0;

		AABB[CHAR_BBCENTER][XDIM].Value = 0.0;
		AABB[CHAR_BBCENTER][YDIM].Value = 0.0;
		AABB[CHAR_BBCENTER][ZDIM].Value = 0.0;
	}

	//Update Current AABB for coherence
	CalculateAABB();

#endif
}

#ifdef CHAR_USE_AABB
/**
	* Updates the collision detection deques
*/
void CCharacter::UpdateAABB (void)
{	
	switch (PhysicMode)
	{
		case UGKPHY_INVISIBLE:	//No render, touchable: collidable
		case UGKPHY_PHYSICAL:		//Renderable, touchable: collidable
			///Recalculates the min and max values of the absolute coordinates of the bounding box
			CalculateAABB();
			break;
	}
	CollisionDetector.Update(this);
}

void CCharacter::UpdateAABB(UGKALG_NUMERIC_TYPE x, UGKALG_NUMERIC_TYPE y, UGKALG_NUMERIC_TYPE z)
{
	AABB[CHAR_BBSIZE][XDIM].Value = x;
	AABB[CHAR_BBSIZE][YDIM].Value = y;
	AABB[CHAR_BBSIZE][ZDIM].Value = z;
	UpdateAABB();
}

/**
	* Updates the collision detection deques
*/
void CCharacter::UpdateAABB (UGK::SpaceCoords Coord)
{	
	float HalfSize;

	switch (PhysicMode)
	{
		case UGKPHY_INVISIBLE:	//No render, touchable: collidable
		case UGKPHY_PHYSICAL:		//Renderable, touchable: collidable
			///Recalculates the min and max values of the absolute coordinates of the bounding box
			//Current implementation does not support rotation applied to the AABB. Only scale and translation
			HalfSize = AABB[CHAR_BBSIZE][Coord].Value * 0.5f * Scale.v[Coord];

			CurrentAABB[CHAR_BBMIN][Coord].Value = Position.v[Coord] - HalfSize;
			CurrentAABB[CHAR_BBMAX][Coord].Value = Position.v[Coord] + HalfSize;
	
		CollisionDetector.Update(this);
	}
}

/**
	* Recalculates the min and max values of the absolute coordinates of the bounding box and inserts the character into the the collision detector
*/
void CCharacter::InitializeAABB	(void)
{
	///Updates the collision detection deques
	switch (PhysicMode)
	{
		case UGKPHY_INVISIBLE:	//No render, touchable: collidable
		case UGKPHY_PHYSICAL:		//Renderable, touchable: collidable
			///Recalculates the min and max values of the absolute coordinates of the bounding box

			CalculateAABB(Mesh);
			CollisionDetector.Insert(this);
	}
}


bool CCharacter::CollidedAABB(CCharacter *C)
{
	//Check for non colliding cases
	for (int i = XDIM; i < WDIM; i++)
	{
		if (CurrentAABB[CHAR_BBMIN][i].Value >= C->CurrentAABB[CHAR_BBMAX][i].Value)
			return false;

		if (CurrentAABB[CHAR_BBMAX][i].Value <= C->CurrentAABB[CHAR_BBMIN][i].Value)
			return false;
	}
	return true;
}

#endif

#ifdef CHAR_USE_OBB
/**
* Updates the collision detection deques
*/
void CCharacter::UpdateAABB(void)
{
	switch (PhysicMode)
	{
	case UGKPHY_INVISIBLE:		//No render, touchable: collidable
	case UGKPHY_PHYSICAL:		//Renderable, touchable: collidable
							///Recalculates the min and max values of the absolute coordinates of the Oriented bounding box
		CalculateAABB();
		break;
	}
	CollisionDetector.Update(this);
}

/**
* Updates the collision detection deques
*/
void CCharacter::UpdateAABB(UGK::SpaceCoords Coord)
{
	switch (PhysicMode)
	{
	case UGKPHY_INVISIBLE:	//No render, touchable: collidable
	case UGKPHY_PHYSICAL:		//Renderable, touchable: collidable
							///Recalculates the min and max values of the absolute coordinates of the OBB 
		unsigned int i, j;
		float FragSize;

		for (i = XDIM; i<WDIM; i++)
		{
			FragSize = Size / CHAR_BBMAXCOORDS - 1;
			/// Fragment the Bounding Box in to 8 Subparts (Tree structure)
			for (j = CHAR_BBMIN; j < CHAR_BBMAXCOORDS; j++) {

				OBB[j][i].Value = Position.v[i] - ((CHAR_BBMAXCOORDS - 1 - j)*FragSize);

			}
			//Attribute Position is given by the collision detector
		}
		CollisionDetector.Update(this);
	}
}

/**
* Recalculates the min and max values of the absolute coordinates of the oriented bounding box and inserts the character into the the collision detector
*/
void CCharacter::InitializeAABB(void)
{
	///Updates the collision detection deques
	switch (PhysicMode)
	{
	case UGKPHY_INVISIBLE:	//No render, touchable: collidable
	case UGKPHY_PHYSICAL:		//Renderable, touchable: collidable
							///Recalculates the min and max values of the absolute coordinates of the bounding box

		CalculateAABB();
		CollisionDetector.Insert(this);
	}
}

#endif

/**
	* Executed when the collision detection system detects a collison with this object although this objectmay not be calculating any collision
*/
void CCharacter::Collided (CCharacter *CollidedChar)
{
	//By default, substract health and test if the object has enough amount of heatlh to become alive
	Health -= CollidedChar->Health;
	if (Health < 0)
		SetDefault();

	//printf("Character %d collided with character %d .\n", CollidedChar->ID, this->ID);
}

void CCharacter::FitMeshIntoBoundingBox(CMesh3d *model)
{
#ifdef UGKSG_OSG
#elif CHAR_USE_QUADTREE
	if (NULL == model)
		model->modelo.scale = { 1.0, 1.0, 1.0 };
	else
	{
		CalculateAABB(model);
		model->modelo.scale.x = AABB[CHAR_BBSIZE][XDIM].Value / (AABB[CHAR_BBMAX][XDIM].Value - AABB[CHAR_BBMIN][XDIM].Value);
		model->modelo.scale.y = 0.1f / (AABB[CHAR_BBMAX][YDIM].Value - AABB[CHAR_BBMIN][YDIM].Value);
		model->modelo.scale.z = AABB[CHAR_BBSIZE][YDIM].Value / (AABB[CHAR_BBMAX][ZDIM].Value - AABB[CHAR_BBMIN][ZDIM].Value);
	}
#elif defined CHAR_USE_AABB
#elif defined CHAR_USE_OBB
#endif
}

void CCharacter::FitMeshIntoBoundingBox()
{
#ifdef CHAR_USE_QUADTREE
	FitMeshIntoBoundingBox(Mesh);
#elif defined CHAR_USE_AABB
	CalculateAABB();
	for (unsigned int i=XDIM;i<WDIM;i++)
		Scale.v[i] = AABB[CHAR_BBMAX][i].Value - AABB[CHAR_BBMIN][i].Value;
#elif defined CHAR_USE_OBB
	CalculateAABB();
	for (unsigned int j = CHAR_BBMIN; j < CHAR_BBMAXCOORDS-1; j+=2)
		for (unsigned int i = XDIM; i<WDIM; i++)
			Scale.v[i] = OBB[j+1][i].Value - OBB[j][i].Value;
#endif
}

#ifdef CHAR_USE_QUADTREE
void CCharacter::FitBoundingBoxArroundMesh(CMesh3d *model){
	unsigned int i;
	if (NULL != model)
	{
		CalculateAABB(model);

		for (i = XDIM; i < WDIM; i++)
			AABB[CHAR_BBSIZE][i].Value = AABB[CHAR_BBMAX][i].Value - AABB[CHAR_BBMIN][i].Value;
	}
	else
	{
		for (i = XDIM; i < WDIM; i++)
			AABB[CHAR_BBSIZE][i].Value = 0.0;
		CalculateAABB();
	}
}
#endif

/**
	* Function to render
*/ 
void CCharacter::Render(void)
{
	switch(RenderMode)
	{
	case CHAR_NO_RENDER:		 //No render for this character: camera, collision objects,...
		return;
	case CHAR_2D:                //Render 2D the character
		Render2D();
		break;
	case CHAR_LINES3D:           //Render Lines 3D
		break;
		case CHAR_3D:            //Render 3D the character
		break;
	default: return;
	}
}

/**
* Function to render
*/
void CCharacter::Render2D(void)
{
	glPushMatrix();

		//glTranslatef(Position.v[XDIM], Position.v[YDIM], Position.v[ZDIM]);
		glRotatef(0.0, Rotation.v[XDIM], Rotation.v[YDIM], Rotation.v[ZDIM]);
		glScalef(Scale.v[XDIM], Scale.v[YDIM], Scale.v[ZDIM]);

		glBegin(GL_QUADS);
			glTexCoord2f(0, 1);	glVertex2f(AABB[CHAR_BBMIN][XDIM].Value, AABB[CHAR_BBMIN][YDIM].Value);
			glTexCoord2f(0, 0);	glVertex2f(AABB[CHAR_BBMIN][XDIM].Value, AABB[CHAR_BBMAX][YDIM].Value);
			glTexCoord2f(1, 0);	glVertex2f(AABB[CHAR_BBMAX][XDIM].Value, AABB[CHAR_BBMAX][YDIM].Value);
			glTexCoord2f(1, 1);	glVertex2f(AABB[CHAR_BBMAX][XDIM].Value, AABB[CHAR_BBMIN][YDIM].Value);
		glEnd();

	glPopMatrix();
}

/**
	* Function to change the render mode
*/
void CCharacter::ChangeRenderMode(CHAR_RENDER_MODE Mode)
{
	RenderMode = Mode;

	switch(RenderMode)
	{
	case CHAR_NO_RENDER:	//No render for this character: camera, collision objects,...
		return;
	case CHAR_2D:			//Render 2D the character
		break;
	case CHAR_LINES3D:		//Render Lines 3D
		break;
	case CHAR_3D:			//Render 3D the character
		break;
	default: return;
	}
}

/**
	* function to move to an absolute position to the character or ship depending on the acceleration
*/
///Geometric transformation methods
void CCharacter::Move		(UGKALG_NUMERIC_TYPE ms)	///Moves depending on the speed and acceleration
{
	Vector Aux;

	#ifdef CHAR_USE_QUADTREE	
	Vector PositionPrev(Position);
	#endif

#ifdef PHY_EULER
	Speed	 += Acceleration*ms;
	Position += Speed*ms;

#elif defined PHY_VERLET
	// Recalculate the new position of the character
	Aux = Position;

	//P(t+At) = 2*P(t)
	Position += Position;

	//P(t+At) = 2*P(t) - P(t-At)
	Position -= PositionPrev;
	PositionPrev = Aux;

	Aux = Acceleration*ms;
	Speed += Aux;

	//P(t+At) = 2*P(t) - P(t-At) + P''(t)*At*At
	Aux *= ms;
	Position += Aux;
#endif
}

/**
	* function to move to an absolute position to the character or ship to a position x, y, z
*/
void CCharacter::MoveTo		(UGKALG_NUMERIC_TYPE x, UGKALG_NUMERIC_TYPE y, UGKALG_NUMERIC_TYPE z)	///Moves to the absolute coordinate x,y,z
{
	Position.Set(x, y, z); //actualizar la posicion del caracter

	//Updating the bounding box
#ifdef CHAR_USE_AABB
	UpdateAABB ();
#elif defined CHAR_USE_OBB
	UpdateOBB();
#endif
}

/**
	* function to move the character or ship to an absolute position from the current position
*/
void CCharacter::MoveTo		(Vector &Move)				///Moving to an absolute position. It does not matter where the character is
{
	Position = Move; // Update position vector based on the Move[x,y,z]

	#ifdef CHAR_USE_AABB
		UpdateAABB (); //Updating the bounding box
	#elif defined CHAR_USE_OBB
		UpdateAABB(); //Updating the bounding box
	#endif
}

/**
* function to move to an absolute position to the character to a given position x or y or z
*/
void CCharacter::MoveTo(SpaceCoords Dim, UGKALG_NUMERIC_TYPE Value)
{
	Position.v[Dim] = Value;
	
	//Updating the bounding box
#ifdef CHAR_USE_AABB
	UpdateAABB();
#elif defined CHAR_USE_OBB
	UpdateOBB();
#endif
}

/**
	* function to move the character or ship to a position based on x, y, z units from the current position
*/
void CCharacter::MoveRelTo	(float x, float y, float z)	///Moves x,y,z units from the to the current position
{
	// update the position x, y and z by increasing the values given
	Position.v[XDIM] += x;
	Position.v[YDIM] += y;
	Position.v[ZDIM] += z; 

	// Updating the bounding box
	#ifdef CHAR_USE_AABB
		UpdateAABB ();
	#elif defined CHAR_USE_OBB
		UpdateAABB(); ///Updating the bounding box
	#endif
}

/**
	* function to move the character or ship to a relative position from the current position 
*/
void UGK::CCharacter::MoveRelTo (Vector &Move)	///Moving relative to the character current Position
{
	// Adding relative movement
	Position += Move; 

	// Updating the bounding box
	#ifdef CHAR_USE_AABB
		UpdateAABB ();
	#elif defined CHAR_USE_OBB
		UpdateAABB(); ///Updating the bounding box
	#endif
}

/**
* function to move to an absolute position to the character to a given position x or y or z
*/
void CCharacter::MoveRelTo(SpaceCoords Dim, UGKALG_NUMERIC_TYPE Value)
{
	Position.v[Dim] += Value;

	//Updating the bounding box
#ifdef CHAR_USE_AABB
	UpdateAABB();
#elif defined CHAR_USE_OBB
	UpdateOBB();
#endif
}

void UGK::CCharacter::ReceiveMessage(RTDESK_CMsg *pMsg){
}
