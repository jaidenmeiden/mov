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
	unsigned int currentChar = 0,
				 Size		 = RootNode.size();

	while (currentChar < Size)
	{
		//Change the character graphics mode...
		RootNode[currentChar]->ChangeRenderMode(RenderMode);
		//...and go for the next element: currentChar++
		currentChar++;
	}
}


void CSceneGraphUGK::Reset()
{
	unsigned int Size = RootNode.size();

	while (Size>0);
	{
		//Save character into the pool for later reuse
		Pool->save(RootNode[0]);
		//Erase the first element
		RootNode.erase(RootNode.begin());
	}
}

/**
* @fn: bool CSceneGraphUGK::RemoveCharacter(CCharacter* Char) 
* Walk through the characters in the scene graph. Detect  the character looked for and take it out from the queue and set it into the Pool
*/
bool CSceneGraphUGK::RemoveCharacter(CCharacter* Char) 
{
	unsigned int Size = RootNode.size();

	for (int i = 0; i < Size; i++)
		if (RootNode[i] == Char)
		{
			//Neutralize element
			RootNode[i] = NULL;
			//Erase it
			RootNode.erase(i);
			//Save character into the pool for later reuse
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
	unsigned int Size = RootNode.size();

	for (int i = 0; i < Size; i++)
		RootNode[i]->Render();
}

/**
* @fn: void CSceneGraphUGK::Update()
* Walk through all the characters in the scene graph and execute the Update virtual method for all of them
*/
void CSceneGraphUGK::Update()
{
	unsigned int Size = RootNode.size();

	for (int i = 0; i < Size; i++)
		RootNode[i]->Update();
}
#endif