/*/////////////////////////////////////////////////////////////////////////////////////
//
// Shoots manager
//

	@author Ramon Molla
	@version 2011-11

	Last modified: 2014-2015 by Miguel Domingo
	Previous modified: 2012-2013 by Vicente Perez
*/

#include <GameCharacters.h>
#include <ShootsManager.h>
#include "Quadtree.h"
#include <SIGame.h>

///Shoots manager Initilization
void CShootsManager::Init() //Used when all the values are initialized by default
{
	RenderMode = CHAR_2D;

	defaultMessageType = 0;

	msgUpd = new RTDESK_CMsg;
	msgUpd->Type = defaultMessageType;
	msgUpd->Propietary = true;
	msg = RTDM_NO_MSG;							//RTDESK Message Time

	ShootsAct.clear();

	Timer.resize(CSH_MAX_TIMERS);
	UpdateSF(TimerManager.GetSF());
}

void CShootsManager::AssignSounds2Shoots()
{
	unsigned int i, s;

	for (i = 0; i < ShootsAct.size(); i++)
	{
		ShootsAct[i]->SetSoundsAmount(Sound.size());
		//Navys sound assignment
		for (s = 0; s < Sound.size(); s++)
			ShootsAct[i]->SetSound(Sound[s], s);
	}
}

///Generates a new shoot
void CShootsManager::NewShoot(CSH_SHOOT_TYPE SType, Vector &Pos, Vector &Spd)
{
	CShoot *shootTmp;
	unsigned int i;

	switch (SType)
	{
	case CSH_PLAYER:			//Shoot sent by the player by default in 2D mode
	case CSH_PLAYER3D:			//Shoot sent by the player in 3D mode
	case CSH_PLAYER3D_CHEVRON:	//Shoot sent by the player
	case CSH_AUX_LASER:			//Shoot sent by the right and left laser auxiliar player ships
	case CSH_AUX_LASER_CHEVRON:	//Shoot sent by the right and left laser auxiliar player ships when the player has a Chevron shooting
		shootTmp = (CShoot *)Pool->get(CHARS_SHOOT, SType);		//Player shoots
		break;
	case CSH_SHIP:				//Shoot sent by a enemy ship. This kind of shoot has to be always after all player's shootings
	case CSH_SUPPLY_SHIP:		//Shoot sent by a enemy Supply Ship. This kind of shoot has to be always after all player's shootings
	case CSH_CIRCLE_SHIP:		//Shoot sent by a enemy Circle Ship. This kind of shoot has to be always after all player's shootings
		shootTmp = (CShoot *)Pool->get(CHARS_SHOOT, SType);
			break;
	case CSH_BULLET:
	default:
		break;
	}

	//Assing sounds references to the new shoot created from scratch
	if (!shootTmp->Stored())
	{
		shootTmp->SetSounds(Sound);
		//Generate the internal timers for the shoot
		shootTmp->Timer.resize(Timer.size());
		//Assign timers
		for (i = 0; i < Timer.size(); i++)
			shootTmp->Timer[i] = Timer[i];

		//Assign the msg dispatcher
		shootTmp->SetMsgDispatcher(GetMsgDispatcher());
	}

	shootTmp->ResetScale();
	shootTmp->Speed = Spd;
	shootTmp->Activate();
	shootTmp->MoveTo(Pos);	
	shootTmp->ChangeRenderMode(RenderMode);	shootTmp->SubtypeChange(SType);

	msUpdShoot = abs(shootTmp->AABB[CHAR_BBSIZE][YDIM].Value/shootTmp->Speed.v[YDIM]);
	if(msUpdShoot > UPDATE_SHOOT) msUpdShoot = UPDATE_SHOOT;
	shootTmp->msUpdMsg		= msUpdShoot;
	shootTmp->ticksUpdMsg	= TimeUpdShoot;

	ShootsAct.push_back(shootTmp);

	if (((CSIGame*)Directory[CHARS_GAME_REF])->DiscreteSimulation)
	{
		msg = GetMsgToFill(defaultMessageType);
		msg->Type = defaultMessageType;
		SendMsg(msg, ShootsAct.back(), TimeUpdShoot);
	}
}

/**
*	@fn void CBonusManager::SetEndingCriteria(bool ByTime, bool ByFrame)
*	Set the conditions to finish the game
*/
void CShootsManager::SetEndingCriteria(bool ByTime, bool ByFrame)
{
	unsigned int i;

	EndByTime	= ByTime;
	EndByFrame	= ByFrame;

	//Cross all the active shoots
	for (i = 0; i < ShootsAct.size(); i++)
	{
		ShootsAct[i]->EndByTime		= ByTime;
		ShootsAct[i]->EndByFrame	= ByFrame;
	}
}

///Render shoots on the screen
void CShootsManager::Render(void)
{
	unsigned int i;
	glEnable(GL_LIGHTING);			// activate lights on
									//Disable the players lighting
	glDisable(SIGLB_PLAYER_LIGHT);
	//Enable the navy ships lighting
	glEnable(SIGLB_SHIP_LIGHT);
	glEnable(SIGLB_SHIP2_LIGHT);

	//Draw active shoots
	for (i = 0; i < ShootsAct.size(); i++)
		if(ShootsAct[i]->Active())
			ShootsAct[i]->Render();
}

/// Change the mode the shoots are rendered
void CShootsManager::ChangeRenderMode(CHAR_RENDER_MODE Mode)
{
	RenderMode = Mode;

	unsigned int i;

	//Change Render Mode of all active shoots
	for (i = 0; i < ShootsAct.size(); i++)
		ShootsAct[i]->ChangeRenderMode(Mode);
}

/// Shoots list Maintenance
void CShootsManager::Maintenance()
{
	unsigned int i;
	CShoot *Shoot;

	//Delete inactive shoots
	for (i = 0; i < ShootsAct.size();)
	{
		Shoot = ShootsAct[i];
		if (!Shoot->Active()) //Inactive shoots are passed to the inactive list
		{
			Pool->save((CCharacter*)Shoot);
			ShootsAct.erase(ShootsAct.begin() + i);
		}
		else i++;
	}
}

void CShootsManager::ReleaseAllShoots()
{
	CShoot *Shoot; 
	
	while (ShootsAct.size())
	{
		Shoot = ShootsAct[0];
		Pool->save(Shoot);
		ShootsAct.pop_front();
	}
}

void CShootsManager::Update(void)
{
	unsigned int	i;
	CShoot		*Shoot;

	for(i=0;i<ShootsAct.size();i++)
	{
		Shoot = ShootsAct[i];
		if (Shoot->Active())
			Shoot->Update();
		else
		{
			Pool->save((CCharacter*)Shoot);
			ShootsAct.erase(ShootsAct.begin()+i);
		}
	}
}

void CShootsManager::ReceiveMessage(RTDESK_CMsg *pMsg){
	Maintenance();	 
}


/**
*	@fn void CShootsManager::SetLocalTimers()
*	Set the global timers to every bonus available and start up local ones
*/
void CShootsManager::SetLocalTimers()
{
	unsigned int i;

	CExplosiveChar::SetLocalTimers(CSH_MAX_TIMERS);
}
