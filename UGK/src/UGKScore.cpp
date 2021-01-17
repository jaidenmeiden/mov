/** Definition of the class Score 
*  General class to manage all a given score
*  Prefix: UGKSC_

	@author Ramon Molla
	@author Nuria Martinez
	@version 2012-06
*/

#include <UGKScore.h>

using namespace UGK;

void CScore::Init()
{
	//No points, no name
	points = 0;
	name.clear();
}

/**
* Destroys the object
*/
CScore::~CScore()
{
}