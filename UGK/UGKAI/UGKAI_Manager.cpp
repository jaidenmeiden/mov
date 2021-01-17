/**
//
// AI declarations
//
@author Ramon Molla
@version 2012-01
*/

#include <UGKAI_Manager.h>
#include <UGKHTMLReader.h>

using namespace UGK;

//Internal local reader
CHTMLReader				HTMLReader;		//The real HTML reader. This is charge of every parsing whatever it is for

void CAIManager::Init() { AI.clear(); }
/**
* Destroys all the behaviors of the game and their states lists.
*/
CAIManager::~CAIManager() { AI.clear(); }

/**
* A copied 'FSM' is returned.
* The 'cStateList' points to the one the AI Manager has for this type of AI.
* The 'cCurrentState' is the initial.
*/
FSM_Machine* CAIManager::getAI(UGKS_String AIname)
{
	for (list<FSM_Machine*>::iterator it = AI.begin(); it != AI.end(); it++)
	{
		if ((*it)->getFSM()->getFAid() == AIname)
			return *it;
	}
}

void CAIManager::loadAI(char filename[], char foldername[], char title[], char version[]) 
{
	AIParser.SetTitle(title);
	AIParser.SetVersion(version);
	AIParser.Start();

	HTMLReader.ParseFile(filename, foldername, &AIParser);

	FSM_Machine* FSM = new FSM_Machine(AIParser.getFA());
	AI.push_back(FSM);
}