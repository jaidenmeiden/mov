/** Header with definitions needed for the management of stack-based FSM

*	Prephix = UGKFAS_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#ifndef UGKFA_STACK
#define UGKFA_STACK

#include "UGKFA_Classic.h"

namespace UGK{

	/// Stack-based Finite Automaton based on FA_Classic
	class UGK_API FA_Stack : public FA_Classic
	{
	public:
		/// Initializes a new instance of the FA_Stack class. 
		FA_Stack(UGKS_String ID, bool FlagProbability);
		/// Initializes a new instance of the FA_Stack class. 
		FA_Stack(UGKS_String ID, int tag, UGKS_String CallbackName, bool FlagProbability);
		/// This method allows the starting of the FSM based on this FA
		virtual void Start() override;
		/// Get FA type 
		virtual UGKS_String getFAtype() override;
		/// Get FA id 
		virtual UGKS_String getFAid() override;
	};

}

#endif