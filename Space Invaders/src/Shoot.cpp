/*/////////////////////////////////////////////////////////////////////////////////////
//
// Shoot 
//
// These values are by default. They have to be overwritten in the initializatio phase
// when reading the default values from the "initialization.html" file

	@author Ramon Molla
	@version 2011-09-11
*/
#include <SITexturesResources.h>
#include <Shoot.h>
#include <GameCharacters.h>
#include <SIMessage.h>
#include <GlobalDefs.h>

#define CSH__XSIZE .05f
#define CSH__YSIZE .3f
#define CSH__ZSIZE .0f

/**   
	* @fn void CShoot::Init (void)
	* Used when all the values are initialized by default
	* when reading the global initialization game file.
 */
void CShoot::Init (void)
{
	SubType			=	CSH_DEFAULT;
	Type			=	CHARS_SHOOT;
	SetDefault();	///The very first time, when created at the beginning of the game, this device is not available
	
	Mesh = NULL;
	ResetRotation();
	ResetScale();
	MoveTo(0.0f, 0.0f, 0.05f);

	//Space position and AABB							
	AABB[CHAR_BBSIZE][XDIM].Value	= CSH__XSIZE;	///Update by default the AABB relative to local coordinates
	AABB[CHAR_BBSIZE][YDIM].Value	= CSH__YSIZE;
	AABB[CHAR_BBSIZE][ZDIM].Value	= CSH__ZSIZE;
	
#ifdef CHAR_USE_AABB
	UpdateAABB();
#endif

	SetLocalTimers(CSH_MAX_TIMERS);

	Speed.v[YDIM] = CSH_DEFAULT_SPEED;
	Health=100;
}


/**
* @fn CShoot::CShoot()
* Constructor of the class CShoot
*/
CShoot::CShoot()
{
	Mesh = NULL;

#ifdef CHAR_USE_AABB
	InitializeAABB();
#endif

	Init();

	msgUpd = new RTDESK_CMsg;
	msgUpd->Type = UMSG_MSG_BASIC_TYPE;
	msgUpd->Propietary = true;
}

/**   
	* @fn void CShoot::SubtypeChange(CSH_SHOOT_TYPE	ShootType)
	* Any subtype change changes AABB and size
    * @ Param [in] ShootType Type of shoot
*/
void CShoot::SubtypeChange(CSH_SHOOT_TYPE	ShootType)
{
	SubType = ShootType;

	if (CHAR_2D == RenderMode)
	{
		AABB[CHAR_BBSIZE][XDIM].Value = 0.05f;
		AABB[CHAR_BBSIZE][YDIM].Value = 0.3f;
		AABB[CHAR_BBSIZE][ZDIM].Value = 0.0f;
	}
	else switch (SubType)
		{
			case CSH_PLAYER:
				Health = 4;	//Amount of power a player shoot may substract from the enemy
				AABB[CHAR_BBSIZE][XDIM].Value = 0.1f; 
				AABB[CHAR_BBSIZE][YDIM].Value = 0.25f;
				AABB[CHAR_BBSIZE][ZDIM].Value = 0.0f;
				break;
			case CSH_PLAYER3D:
				Health = 20;	//Amount of power a player shoot on 3D mode may substract from the enemy
				AABB[CHAR_BBSIZE][XDIM].Value = 0.05f; //5.05	.1
				AABB[CHAR_BBSIZE][YDIM].Value = 0.3f;	//.3	.25
				AABB[CHAR_BBSIZE][ZDIM].Value = 0.0f;
			break;
			case CSH_PLAYER3D_CHEVRON:
				Health = 50;	//Amount of power a player shoot on 3D mode Chevron may substract from the enemy
				AABB[CHAR_BBSIZE][XDIM].Value = 0.5f; //5.05 
				AABB[CHAR_BBSIZE][YDIM].Value = 0.3f;  //.3
				AABB[CHAR_BBSIZE][ZDIM].Value = 0.0f;
			break;
			case CSH_AUX_LASER:
				Health = 30;	//Amount of power a auxiliar player laser shoot on 3D mode may substract from the enemy
				AABB[CHAR_BBSIZE][XDIM].Value = 0.03f;
				AABB[CHAR_BBSIZE][YDIM].Value = 0.8f;
				AABB[CHAR_BBSIZE][ZDIM].Value = 0.0f;
				break;
			case CSH_AUX_LASER_CHEVRON:
				Health = 50;	//Amount of power a auxiliar player laser shoot on 3D mode may substract from the enemy
				AABB[CHAR_BBSIZE][XDIM].Value = 0.1f;
				AABB[CHAR_BBSIZE][YDIM].Value = 0.8f;
				AABB[CHAR_BBSIZE][ZDIM].Value = 0.0f;
			break;
			case CSH_SHIP:
				Health = 3;	//Amount of power an enemy shoot may substract from the player
				AABB[CHAR_BBSIZE][XDIM].Value = .033f;
				AABB[CHAR_BBSIZE][YDIM].Value = 0.3f;
				AABB[CHAR_BBSIZE][ZDIM].Value = 0.0f;				
			break;
			case CSH_CIRCLE_SHIP:
				Health = 10;	//Amount of power an enemy shoot may substract from the player
				AABB[CHAR_BBSIZE][XDIM].Value = .035f;
				AABB[CHAR_BBSIZE][YDIM].Value = 0.3f;
				AABB[CHAR_BBSIZE][ZDIM].Value = 0.0f;				
			break;
			case CSH_SUPPLY_SHIP:
				Health = 10;	//Amount of power an enemy shoot may substract from the player
				AABB[CHAR_BBSIZE][XDIM].Value = .035f;
				AABB[CHAR_BBSIZE][YDIM].Value = 0.3f;
				AABB[CHAR_BBSIZE][ZDIM].Value = 0.0f;				
			break;
			default:;
		}
#ifdef CHAR_USE_AABB
	UpdateAABB();
#endif
}

/**   
	* @fn void CShoot::Render()
	* Lets the object to be visualized depending on the render mode
*/
void CShoot::Render()
{
	float	top = 0;

	CTexturesManager * TextMngr = (CTexturesManager *)Directory[CHARS_TEXTURES_MNGR_REF];

	GLboolean Blending = glIsEnabled(GL_BLEND);

	if (!Blending)
		glEnable(GL_BLEND);

	///Render the shoot on the screen
	if(Active()){
		switch(SubType)
		{
		case CSH_PLAYER:	/// Player Shoot 2D Render Mode
			if (CHAR_2D == RenderMode)
				TextMngr->Textures[CTM_PLAYER_SHOOT]->SetTexture();
			break;
		case CSH_SHIP:		/// Ship shoot
			switch (RenderMode)
			{
			case CHAR_2D:
				top = 0.3;
				TextMngr->Textures[CTM_SHIP_SHOOT]->SetTexture();
				break;
			case CHAR_LINES3D:
			case CHAR_3D:
				top = 0.6;
				TextMngr->Textures[CTM_SHIP_SHOOT]->SetTexture();
				break;
			}
			break;
		case CSH_SUPPLY_SHIP:   //SupplyShip shoot
			switch (RenderMode)
			{
			case CHAR_2D:
				top = 0.3;
				TextMngr->Textures[CTM_SUPPLYSHIP_SHOOT]->SetTexture();
				break;
			case CHAR_LINES3D:
			case CHAR_3D:
				top = 0.6;
				TextMngr->Textures[CTM_SUPPLYSHIP_SHOOT]->SetTexture();
				break;
			}
			break;
		case CSH_PLAYER3D_CHEVRON:	// Shoot 3D "chevron"
			switch (RenderMode)
			{
			case CHAR_LINES3D:
				TextMngr->Textures[CTM_PLAYER_SHOOT3D_DARK_BCKG]->SetTexture();
				break;
			case CHAR_3D:
				TextMngr->Textures[CTM_PLAYER_SHOOT3D_DARK_BCKG]->SetTexture();
				break;
			case CHAR_2D:
				TextMngr->Textures[CTM_PLAYER_SHOOT]->SetTexture();
				return;
			default: //No render at all
				return;
			}			
			break;
		case CSH_PLAYER3D:	// Shoot 3D in particles
			switch (RenderMode)
			{
				case CHAR_LINES3D:
					glColor4f (1.0f, 1.0f, 1.0f, 0.7f);
					break;
				case CHAR_3D:
					TextMngr->Textures[CTM_PLAYER_SHOOT3D]->SetTexture();
					break;
				case CHAR_2D:
					return;
				default: //No render at all
					return;
			}
			break;
		case CSH_AUX_LASER:            // Shoot of a player auxiliar right or left laser
			switch (RenderMode)
			{
			case CHAR_LINES3D:
				top = 0.6;
				TextMngr->Textures[CTM_PLAYER_SHOOT3D]->SetTexture();
				break;
			case CHAR_3D:
				top = 0.6;
				TextMngr->Textures[CTM_PLAYER_SHOOT3D]->SetTexture();
				break;
			case CHAR_2D:
				return;
			default: //No render at all
				return;
			}
			break;
		case CSH_CIRCLE_SHIP:            // Shoot of a player auxiliar right or left laser
			switch (RenderMode)
			{
			case CHAR_LINES3D:
			case CHAR_3D:
				top = 0.6;
				TextMngr->Textures[CTM_SUPPLYSHIP_SHOOT]->SetTexture();
				break;
			case CHAR_2D:
				top = 0.3;
				TextMngr->Textures[CTM_SUPPLYSHIP_SHOOT]->SetTexture();
				break;
			}
			break;
		
		}	// Switch
		Render2D();
	}

	if (!Blending)
		glDisable(GL_BLEND);
}	// Method


/**   
	* @fn void CShoot::AI_Explode (void)
	* 
*/
void CShoot::AI_Explode (void)
{
	Sound[CSH_EXPLOSION_SND]->Play(UGKSND_LOW_VOLUME);
	Sound[CSH_TOUCH_SND]->SetPosition(UGKSND_STRD_POSITION);
	Sound[CSH_TOUCH_SND]->SetVolume(UGKSND_ULTRA_LOW_VOLUME);
	Sound[CSH_TOUCH_SND]->Play(UGKSND_LOW_VOLUME);
	AI_Die();
}	

/**   
	* @fn void CShoot::Collided (CCharacter *CollidedChar)
	* What to do when a collision has happened
    * @ Param [in] CollidedChar Character collided to the shoot
*/
void CShoot::Collided (CCharacter *CollidedChar)
{
	bool Burnup = false;

	if (Alive() && CHARS_COLLISION_TABLE[CHARS_SHOOT][CollidedChar->Type])
		switch (CollidedChar->Type)
		{
		case CHARS_SHIP:
		case CHARS_SUPPLYSHIP:
		case CHARS_CIRCLESHIP:
			Burnup = CSH_PLAYER == SubType || CSH_PLAYER3D == SubType || CSH_AUX_LASER == SubType || CSH_PLAYER3D_CHEVRON == SubType;
			break;
		case CHARS_PLAYER:
		case CHARS_LASER:
		case CHARS_REACTOR:
			Burnup = CSH_SHIP == SubType|| CSH_SUPPLY_SHIP == SubType || CSH_CIRCLE_SHIP == SubType;
			break;
		case CHARS_BUNKER:
			Burnup = Burnup;
			break;
		case CHARS_BRICK:
			Burnup = true;
			break;
		}

	if (Burnup)
	{
		AI_Explode();
	}
}

/**   
	* @fn void CShoot::Update ()
	* What the character has to do on every time tick 
*/
void CShoot::Update ()	///What the character has to do on every time tick 
 {
	 CCharacter * Neighbour;

	//if (Timer[CSH_UPD_PERIOD].IsSounding())
	{
#ifndef XM_CONTINUOUS_WITH_SIMULATE_TIME
		Timer[CSH_UPD_PERIOD]->ResetAlarm();

		CharacterList v= GetNearestObjectsTo(1.0);

		for(unsigned int i=0;i<v.size();i++){	 
			if( ((v.at(i)->Position.v[XDIM]-(v.at(i)->AABB[CHAR_BBSIZE][XDIM].Value*0.5f)	<	Position.v[XDIM]/*+(AABB[CHAR_BBSIZE][XDIM].Value*0.5f)*/	)&&
				(v.at(i)->Position.v[XDIM]+(v.at(i)->AABB[CHAR_BBSIZE][XDIM].Value*0.5f)	>	Position.v[XDIM]/*-(AABB[CHAR_BBSIZE][XDIM].Value*0.5f)*/	)&&
				(v.at(i)->Position.v[YDIM]-(v.at(i)->AABB[CHAR_BBSIZE][YDIM].Value*0.5f)	<	Position.v[YDIM]/*+(AABB[CHAR_BBSIZE][YDIM].Value*0.5f)*/	)&&
				(v.at(i)->Position.v[YDIM]+(v.at(i)->AABB[CHAR_BBSIZE][YDIM].Value*0.5f)	>	Position.v[YDIM]/*-(AABB[CHAR_BBSIZE][YDIM].Value*0.5f)*/	) 
				) && Active
				){
					if((SubType==CSH_PLAYER || SubType==CSH_PLAYER3D || SubType==CSH_PLAYER3D_CHEVRON || SubType==CSH_AUX_LASER) && CHARS_COLLISION_TABLE[CHARS_PLAYER_SHOOT][v.at(i)->Type])
					{
						v.at(i)->Collided(this);
						Collided(v.at(i));
					}else if(CHARS_COLLISION_TABLE[CHARS_MISSIL][v.at(i)->Type])
					{
						v.at(i)->Collided(this);
						Collided(v.at(i));
					}
			}
		}

		switch (SubType)
		{
			case CSH_PLAYER:			///Shoot sent by the player
			case CSH_PLAYER3D:			///Shoot sent by the player in 3D mode
			case CSH_PLAYER3D_CHEVRON:	///Shoot sent by the player
			case CSH_AUX_LASER:		///Shoot sent by the right and left laser auxiliar player ships
				if (Position.v[YDIM] > SIGLBD_PG_CEILING/*4.5f*/){		// Frustrum collection. Player's shoot is too much far away from the camera
					AI_Die();}
				break;
			case CSH_SHIP:
			case CSH_SUPPLY_SHIP:
			case CSH_CIRCLE_SHIP:
				if (Position.v[YDIM] < SIGLBD_PG_BOTTOM/*-6.5f*/)	// If the Shoot exits from the playground downwards ...
				{
					AI_Die();
				}
				break;
			
		}	//Switch

		PositionPrev=Position;
		//Move upwards or downwards depending on the original speed. No change in speed since the battle is in space
		MoveRelTo(Speed * msUpdMsg);	// Integrates space delta from its speed

		UpdateCollisionDetection();
#else
		//Timer[CSH_UPD_PERIOD].AdvanceOneAlarmPeriod();

#ifdef CHAR_USE_QUADTREE
		CharacterList v = GetNearestObjectsTo(1.0);

		for (unsigned int i = 0; i<v.size(); i++)
		{
			Neighbour = v.at(i);
			if (CollidedAABB(Neighbour) && Active())
			{
				Neighbour->Collided(this);
				Collided(Neighbour);
			}
		}
#elif defined CHAR_USE_AABB 
#elif defined CHAR_USE_OBB 
#endif

		//Destroy shoot if it is out of gameplay
		switch (SubType)
		{
			case CSH_PLAYER:			///Shoot sent by the player
			case CSH_PLAYER3D:			///Shoot sent by the player in 3D mode
			case CSH_PLAYER3D_CHEVRON:	///Shoot sent by the player
			case CSH_AUX_LASER:		///Shoot sent by the right and left laser auxiliar player ships
				if (Position.v[YDIM] > SIGLBD_PG_CEILING){		// Frustrum collection. Player's shoot is too much far away from the camera
					AI_Die();}
				break;
			case CSH_SHIP:
			case CSH_SUPPLY_SHIP:
			case CSH_CIRCLE_SHIP:
				if (Position.v[YDIM] < SIGLBD_PG_BOTTOM)	// If the Shoot exits from the playground downwards ...
					AI_Die();
				break;
			
		}	//Switch

		PositionPrev=Position;
		//Move upwards or downwards depending on the original speed. No change in speed since the battle is in space
		float DeltaTime = Timer[CSH_UPD_PERIOD].GetAlarmPeriodms();
		Vector aux = Speed * DeltaTime;
		MoveRelTo(Speed * Timer[CSH_UPD_PERIOD].GetAlarmPeriodms());	// Integrates space delta from its speed

		UpdateCollisionDetection();
#endif
	}
}

void CShoot::DiscreteUpdate ()	///What the character has to do on every time tick 
 {
	double msUpdMsg;

	#ifdef XM_UPD_TIME_DISC
	TimerManager.GetTimer(SIGLBT_UPDATE_TIMING)->InitCounting();
	#endif

#ifdef CHAR_USE_QUADTREE
	CharacterList v = GetNearestObjectsTo(1.0);
	for (unsigned int i = 0; i<v.size(); i++) {
		if (((v.at(i)->Position.v[XDIM] - (v.at(i)->AABB[CHAR_BBSIZE][XDIM].Value / 2.f)	<	Position.v[XDIM]/*+(AABB[CHAR_BBSIZE][XDIM].Value*0.5f)*/) &&
			(v.at(i)->Position.v[XDIM] + (v.at(i)->AABB[CHAR_BBSIZE][XDIM].Value / 2.f)	>	Position.v[XDIM]/*-(AABB[CHAR_BBSIZE][XDIM].Value*0.5f)*/) &&
			(v.at(i)->Position.v[YDIM] - (v.at(i)->AABB[CHAR_BBSIZE][YDIM].Value / 2.f)	<	Position.v[YDIM]/*+(AABB[CHAR_BBSIZE][YDIM].Value*0.5f)*/) &&
			(v.at(i)->Position.v[YDIM] + (v.at(i)->AABB[CHAR_BBSIZE][YDIM].Value / 2.f)	>	Position.v[YDIM]/*-(AABB[CHAR_BBSIZE][YDIM].Value*0.5f)*/)
			) && Active()
			){	v.at(i)->Collided(this);
		Collided(v.at(i));
		}
	}
#elif defined CHAR_USE_AABB 
#elif defined CHAR_USE_OBB 
#endif

	switch (SubType)
	{
		case CSH_PLAYER:			///Shoot sent by the player
		case CSH_PLAYER3D:			///Shoot sent by the player in 3D mode
		case CSH_PLAYER3D_CHEVRON:	///Shoot sent by the player
		case CSH_AUX_LASER:		///Shoot sent by the right and left laser auxiliar player ships
			if (Position.v[YDIM] > SIGLBD_PG_CEILING/*4.5f*/){		// Frustrum collection. Player's shoot is too much far away from the camera
				AI_Die();}
			break;
		case CSH_SHIP:
		case CSH_SUPPLY_SHIP:
		case CSH_CIRCLE_SHIP:
			if (Position.v[YDIM] < SIGLBD_PG_BOTTOM/*-6.5f*/)	// If the Shoot exits from the playground downwards ...
			{
				AI_Die();
			}
			break;
			
	}	//Switch

	PositionPrev=Position;
	msUpdMsg = Timer[CSH_UPD_PERIOD].GetAlarmPeriodms();

	//Move upwards or downwards depending on the original speed. No change in speed since the battle is in space
	MoveRelTo(Speed * msUpdMsg);	// Integrates space delta from its speed

	UpdateCollisionDetection();

	#ifdef XM_UPD_TIME_DISC
	TimerManager.EndAccCounting(SIGLBT_UPDATE_TIMING);
	#endif

	if(Active() && !EndByTime && !EndByFrame){
		#ifdef DEF_RTD_TIME
		TimerManager.GetTimer(SIGLBT_RTDSKMM_TIMING].InitCounting();
		#endif

		SendSelfMsg(msgUpd, msUpdMsg);

		#ifdef DEF_RTD_TIME
		TimerManager.EndAccCounting(SIGLBT_RTDSKMM_TIMING);
		#endif 
	}
}

void CShoot::ReceiveMessage(RTDESK_CMsg *pMsg){
	DiscreteUpdate();
}


CShoot::~CShoot()
{
	Collisionable(UGKPHY_NON_COLLISIONABLE);
	DeleteMsg(msgUpd);
	DeleteMsg(msg);
}