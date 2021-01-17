/**	Definition of the main entity of the UPV Game Kernel - UGK
*	This class in in charge of starting all the internal structures, data and active entitites
*	that are neccesary in order to manage internally the game kernel

*	Prefix: UGKE_

*	@author Ramon Molla
*	@modified
*	@version 2015-11
*/

#ifndef UGKE_UGKENGINE
#define UGKE_UGKENGINE

#include <UGKCharactersPool.h>

namespace UGK
{
	typedef enum
	{
		UGKE_GLOBAL_TIMER,
		UGKE_TOTAL_TIMERS
	} UGKE_TIMERS;

	class UGK_API CUGKEngine
	{
		cHRTimerManager HRTimerManager;		///<HR counters for delaying the sensitiveness of the device
		CCharactersPool	CharactersPool;

	public:

		CUGKEngine();

		//Generic facilities activation methods
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
}	//namespace UGK
#endif
