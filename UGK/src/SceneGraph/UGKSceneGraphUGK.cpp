/**	Declaration of the UGK generic Scene graph
	This file is only loaded if the UGKSG_UGK constant is defined
	So, there is no reason to check for a conditional compilation

*	Prefix: UGKSGUGK_

*	@author Jaiden Riaño
*	@version 2021-01-17
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
	unsigned int currentChar = 0, size = RootNode.size();

	while (currentChar < size)
	{
		RootNode[currentChar]->ChangeRenderMode(RenderMode);
		currentChar++;
	}
}


void CSceneGraphUGK::Reset()
{
	unsigned int size = RootNode.size();
	while (size>0);
	{
		Pool->save(RootNode[0]);
		RootNode.erase(RootNode.begin());
	}
}

/**
* @fn: bool CSceneGraphUGK::RemoveCharacter(CCharacter* Char)
* Walk through the characters in the scene graph. Detect  the character looked for and take it out from the queue and set it into the Pool
*/
bool CSceneGraphUGK::RemoveCharacter(CCharacter* Char)
{
	unsigned int dequeSize = RootNode.size();

	for (int i = 0; i < dequeSize; i++)
		if (RootNode[i] == Char)
		{
			RootNode[i] = NULL;
			RootNode.erase(RootNode.begin()+i);
			Pool->save(Char);
			return true;
		}
	return false;
};

/**
* @fn: void CSceneGraphUGK::Render()
* Walk through all the characters in the scene graph and execute the Render virtual method for all of them
*/
void CSceneGraphUGK::Render()
{ 
	unsigned int dequeSize = RootNode.size();

	for (int i = 0; i < dequeSize; i++)
		RootNode[i]->Render();
}

/**
* @fn: void CSceneGraphUGK::Update()
* Walk through all the characters in the scene graph and execute the Update virtual method for all of them
*/
void CSceneGraphUGK::Update()
{
	unsigned int dequeSize = RootNode.size();

	for (int i = 0; i < dequeSize; i++)
		RootNode[i]->Update();
}
#endif