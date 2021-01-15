/**	Definition of the class Bonus

*	Prefix: CBN_

*	HISTORY

*	@author Ramon Molla
*	@version 2016-02
*/

#include <SITexturesResources.h>
#include <TexturesManager.h>
#include <GameSounds.h>
#include <GameCharacters.h>
#include <BonusManager.h>
#include <SIMessage.h>
#include <GlobalTiming.h>

#if defined(XM_UPD_TIME_DISC) || defined(XM_UPD_TIME_CONT) || defined(DEF_RTD_TIME)
#include <GlobalTiming.h>
#endif


/**
*	@fn CBonus::CBonus()
*	Constructor of the class
*/
CBonus::CBonus()
{
	Mesh = NULL;
	//Since Bonus PhysicMode is UGKPHY_PHYSICAL... it has to initialize its AABB
#ifdef CHAR_USE_AABB
	InitializeAABB();
#endif

	Init();

	msgUpd = new RTDESK_CMsg;
	msgUpd->Type = UMSG_MSG_BASIC_TYPE;
	msgUpd->Propietary = true;
}

/**
*	@fn CBonus::Init()
*	Initializer of the class
*/
void CBonus::Init()
{
	Explosion.Health	= 4;
	SetDefault();

	//Initial position
	Position.v[XDIM] = float (rand()%10) - 5.0f;
	Position.v[YDIM] = CBN_YPOS;
	Position.v[ZDIM] = CBN_ZPOS;

	//Initial size
	CalculateAABB(CBN_WIDTH_2D, CBN_HEIGTH_2D, CBN_LENGTH_2D);

	//Speed is reset in the CCharacter class constructor
	Speed.v[YDIM] = -0.003f;	//Units per milisecond

	//Do not use Moveto method to avoid to be inserted in the collision detection facilities
	Shake1 = 1;
	Shake2 = 0;

	Alpha		=  CBN_MAX_ALPHA;
	FadingSpeed = -CBN_FADING_SPEED;

	Type		=	CHARS_BONUS;	///<Class of character is a Bonus
	SubType		=	CBN_BONUS_3D;	///<When initializing the type of bonus, the first time is 3D
}

void CBonus::Render(void)
{
	CTexturesManager * TextMngr = (CTexturesManager *) Directory[CHARS_TEXTURES_MNGR_REF];
	
	GLboolean	Blending = glIsEnabled(GL_BLEND),
				AlphaT	 = glIsEnabled(GL_ALPHA_TEST);

	if (!Blending)	glEnable(GL_BLEND);
	if (!AlphaT)	glEnable(GL_ALPHA_TEST);									// for TGA alpha test

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	switch(RenderMode)
	{
	case CHAR_NO_RENDER:			//No render for this character. Nothing to do
		return;
	case CHAR_2D:
		if (CBN_BONUS_3D != SubType)
		{
			//Not possible to render in 2D mode a non CBN_BONUS_3D Bonus
			//Bonus not allowed. Destroy bonus
			SetDefault();
			return;
		}

		TextMngr->Textures[CTM_POWERUP]->SetTexture();
		break;
	case CHAR_LINES3D:
		//Nothing to do at this version
		break;
	case CHAR_3D:
		switch (SubType)
		{
		case CBN_BONUS_3D:
			//Not possible to render in 3D mode a CBN_BONUS_3D Bonus
			//Bonus not allowed. Destroy bonus
			SetDefault();
			return;
		case CBN_BONUS_LASER:
			TextMngr->Textures[CTM_TEXT_BONUS]->SetTexture();
			break;
		case CBN_BONUS_WEAPON:
			TextMngr->Textures[CTM_TEXT_WEAPON]->SetTexture();
		}

		//Fading in and out of the Bonus
		Alpha += FadingSpeed * msUpdMsg;
		if (Alpha <= 0)
			if (FadingSpeed <=0 ) FadingSpeed = -FadingSpeed;
		else if (Alpha >= CBN_MAX_ALPHA)
			if (FadingSpeed >=0 ) FadingSpeed = -FadingSpeed;

		glColor4f (1.0f, 1.0f, 1.0f, Alpha);
		break;
	default: return;
	}

	Render2D();

	if (!Blending)	glDisable(GL_BLEND);
	if (!AlphaT)	glDisable(GL_ALPHA_TEST);									// for TGA alpha test
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

void CBonus::ChangeRenderMode(CHAR_RENDER_MODE Mode)
{
	RenderMode = Mode;

	switch(Mode)
	{
	case CHAR_NO_RENDER:			//No render for this character: camera, collision objects,...
		break;
	case CHAR_2D:
		CalculateAABB(CBN_WIDTH_2D, CBN_HEIGTH_2D, CHAR_2D_AABB_THICKNESS);
		break;
	case CHAR_LINES3D:
	case CHAR_3D:
		CalculateAABB(CBN_WIDTH_3D, CBN_HEIGTH_3D, CHAR_AABB_THICKNESS_DEFAULT);
		break;
	default: return;
	}	
}

void CBonus::Update (void)	///What the character has to do on every time tick 
{
	Vector DeltaPos;

	if (Timer[CBN_UPD_PERIOD].IsSounding())
	{
#ifndef XM_CONTINUOUS_WITH_SIMULATE_TIME
		Timer[CBN_UPD_PERIOD].ResetAlarm();
		//Move downwards one step
		DeltaPos = Speed * msUpdMsg;
		MoveRelTo(DeltaPos);// Move On The X Axis By X Speed

		if (Position.v[YDIM] < Bottom)						//Out of game playground
			AI_Die();

		#ifdef CHAR_USE_AABB
		UpdateAABB();
		#endif
#else
		if (Timer[CBN_UPD_PERIOD].IsSounding()) Timer[CBN_UPD_PERIOD].AdvanceOneAlarmPeriod();

		//Move downwards one step
		MoveRelTo(0.0f, Speed.v[YDIM] * msUpdMsg, 0.0f);
#endif
	}
}

void CBonus::DiscreteUpdate (void)	///What the character has to do on every time tick 
{
	Vector DeltaPos;

	#ifdef XM_UPD_TIME_DISC
	TimerManager.GetTimer(SIGLBT_UPDATE_TIMING)->InitCounting();
	#endif

	//Move downwards one step
	DeltaPos = Speed * msUpdMsg;
	MoveRelTo(DeltaPos);// Move On The X Axis By X Speed

	if (Position.v[YDIM] < Bottom)						//Out of game playground
		AI_Die();

	#ifdef XM_UPD_TIME_DISC
	TimerManager.EndAccCounting(SIGLBT_UPDATE_TIMING);
	#endif


	if(Alive() && !EndByTime && !EndByFrame){
		#ifdef DEF_RTD_TIME
		TimerManager.GetTimer(SIGLBT_RTDSKMM_TIMING].InitCounting();
		#endif

		SendSelfMsg(msgUpd, Timer[CBN_UPD_PERIOD].GetAlarmPeriod());

		#ifdef DEF_RTD_TIME
		TimerManager.EndAccCounting(SIGLBT_RTDSKMM_TIMING);
		#endif
	}
}

void CBonus::AI_Explode (void)	//What to do when exploding a Bonus
{
	Explosion.Init(this, Explosion.Timer[CBN_UPD_PERIOD].GetAlarmPeriodms());
	Activate();
	AI_Die();
}

//Physics
void CBonus::Collided (CCharacter *CollidedChar)
{
	if (CHARS_COLLISION_TABLE[CHARS_BONUS][CollidedChar->Type])
		PlayerCollided();
}

void CBonus::PlayerCollided ()
{
	if (Alive() && !Explosion.Alive())
		AI_Explode();
	RTDESK_CMsg *Msg = GetMsgToFill(UMSG_MSG_BASIC_TYPE);
	SendMsg(Msg, Game, RTDESKT_INMEDIATELY);

	//Make sound
	switch(SubType)
	{
	case CBN_BONUS_3D:
		GetSound(CBN_SHIELD_SND)->Play(UGKSND_VOLUME_80);
		GetSound(CBN_SHIELD_SND)->SetPosition(UGKSND_STRD_POSITION);
		break;
	case CBN_BONUS_LASER:
	case CBN_BONUS_WEAPON:
		GetSound(CBN_BONUS_SND)->Play(UGKSND_MAX_VOLUME);
		GetSound(CBN_BONUS_SND)->SetPosition(UGKSND_STRD_POSITION);
		break;
	}
}

void CBonus::ReceiveMessage(RTDESK_CMsg *pMsg){
	DiscreteUpdate();
}
