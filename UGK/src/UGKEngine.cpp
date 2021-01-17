/**	Definition of the main entity of the UPV Game Kernel - UGK
*	This class in in charge of starting all the internal structures, data and active entitites
*	that are neccesary in order to manage internally the game kernel

*	Prefix: UGKE_

*	@author Ramon Molla
*	@modified
*	@version 2015-11
*/

#include <UGKEngine.h>

using namespace UGK;

CUGKEngine::CUGKEngine()
{

	HRTimerManager.ResetSamplingFrequency(HRTM_FAST);
	HRTimerManager.CreateTimers(UGKE_TOTAL_TIMERS);

	//Generic facilities activation methods
	CharactersPool.SetTimer(HRTimerManager.GetTimer(UGKE_GLOBAL_TIMER));

	/*
		Generate:
			scene graph
			hw manager
			AI manager
			Fixed Point arithmetic
			Internationalization
			anything else...
	*/
};
