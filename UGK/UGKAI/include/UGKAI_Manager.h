/** Header with definitions needed for the management of all types of FSM

*	Prephix = UGKAIM_

*	@author Joan Sancho

*	@version 2016-02
*/

#ifndef UGKAI_MANAGER
#define UGKAI_MANAGER

#define UGK_USE_FSM_EXPORTS
#include "UGKFSMParser.h"
#include "UGKFA_Concurrent_States.h"
#include "UGKFA_Inertial.h"
#include "UGKFA_Stack.h"
#include "UGKFSM_Machine.h"
#include <vector>

namespace UGK
{
	class UGK_API CAIManager
	{
	protected:
		//Atributes

		///ACHTUNG: For future versions, use STL vector type in order to allow behaviour changes on the fly
		std::list<FSM_Machine*> AI;		///< Character Artificial Intelligence supported by a Finite State Machine (FSM)
		CFSMReader AIParser;			///< Parser to load all diferent AIs managed

	public:
		//Methods
		void Init();
		
		CAIManager() { Init(); };		///< Constructor of the class
		~CAIManager();					///< Destructor of the class

		FSM_Machine* getAI(UGKS_String AIname);											///< Give a typefied predefined behaviour
		void loadAI(char filename[], char foldername[], char title[], char version[]);	///< Uses the parser for loading the FSM in the argument file
	};
}
#endif