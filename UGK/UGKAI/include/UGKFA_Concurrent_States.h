/** Header with definitions needed for the management of concurrent states FSM

*	Prephix = UGKFACS_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#ifndef UGKFA_CONCURRENT_STATES
#define UGKFA_CONCURRENT_STATES

#include "UGKFA_Classic.h"
#include <map>

namespace UGK{

	/// Concurrent_States Finite Automaton based on FA_Classic
	class UGK_API FA_Concurrent_States : public FA_Classic
	{
	private:
		int n_MAX_Concurrent; ///< Max number of concurrent states
		UGKFAC_StateList initiallyEnabled; ///< Collection that stores initial enabled states
		std::map<int, int> StatesCredits; ///< Dictionary of execution credits. Used and handled internally
	public:
		/// Initializes a new instance of the FA_Concurrent_States
		FA_Concurrent_States(UGKS_String ID, int tag, int num, UGKS_String CallbackName, bool FlagProbability);
		/// This method allows the starting of the FSM based on this FA
		virtual void Start() override;
		/// Get FA type (virtual, the other FAs override this method)
		virtual UGKS_String getFAtype() override;
		/// Get FA id (virtual, the other FAs override this method)
		virtual UGKS_String getFAid() override;
		/// Get the dictionary that controls execution credits
		std::map<int, int> getCreditsDic();
		/// Get initial states of the FSM based on this FA
		UGKFAC_StateList getInitials();
		/// Get Max number of concurrent states
		int getMaxConcurrent();
	};

}

#endif

