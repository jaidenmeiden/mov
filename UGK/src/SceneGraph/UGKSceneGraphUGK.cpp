/**	Declaration of the UGK generic Scene graph
	This file is only loaded if the UGKSG_UGK constant is defined
	So, there is no reason to check for a conditional compilation

*	Prefix: UGKSGUGK_

*	@author Ramón Mollá
*	@version 2017-09
*/

#include <UGKSceneGraph.h>

#ifdef UGKSG_UGK
using namespace UGK;

/**
* @fn: void CSceneGraphUGK::ChangeRenderMode(CHAR_RENDER_MODE RenderMode) 
* Crosses the whole scene graph and changes the graphics mode for all characters
*/
void CSceneGraphUGK::ChangeRenderMode(CHAR_RENDER_MODE RenderMode) 
{ 
	//INSERT YOUR CODE HERE
}


void CSceneGraphUGK::Reset()
{
	//INSERT YOUR CODE HERE
}

/**
* @fn: bool CSceneGraphUGK::RemoveCharacter(CCharacter* Char) 
* Walk through the characters in the scene graph. Detect  the character looked for and take it out from the queue and set it into the Pool
*/
bool CSceneGraphUGK::RemoveCharacter(CCharacter* Char) 
{
	//INSERT YOUR CODE HERE
	return nullptr;
};

/**
* @fn: void CSceneGraphUGK::Render()
* Walk through all the characters in the scene graph and execute the Render virtual method for all of them
*/
void CSceneGraphUGK::Render()
{ 
	//INSERT YOUR CODE HERE
}

/**
* @fn: void CSceneGraphUGK::Update()
* Walk through all the characters in the scene graph and execute the Update virtual method for all of them
*/
void CSceneGraphUGK::Update()
{
	//INSERT YOUR CODE HERE
}
#endif