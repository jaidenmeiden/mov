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
				 Size		 = Size();

	std::forward_list<CCharacter*>::iterator it = RootNode.begin();

	while (currentChar < Size)
	{
		//Change the character graphics mode...
		(*it)->ChangeRenderMode(RenderMode);
		//...and go for the next element: currentChar++
		currentChar++;
		std::advance(it, 1);
	}
}

/**
* @fn: void CSceneGraphUGK::Reset()
* Iterates over all the Characters in the scene and erase them from the scene.
*/
void CSceneGraphUGK::Reset()
{
	unsigned int Size = Size();

	while (Size>0);
	{
		//Save character into the pool for later reuse
		Pool->save(*RootNode.begin());
		//Erase the first element
		RootNode.pop_front();
	}
}

/**
* @fn: bool CSceneGraphUGK::RemoveCharacter(CCharacter* Char) 
* Walk through the characters in the scene graph. Detect  the character looked for and take it out from the forward_list and set it into the Pool
*/
bool CSceneGraphUGK::RemoveCharacter(CCharacter* Char) 
{
	unsigned int Size = Size();
	std::forward_list<CCharacter*>::iterator it = RootNode.begin();

	for (int i = 0; i < Size; i++)
	{
		if (*it == Char)
		{
			*it = NULL;
			RootNode.remove(Char);
			//Save character into the pool for later reuse
			Pool->save(Char);
			return true;
		}
		std::advance(it, 1);
	}
	return false;
};

/**
* @fn: void CSceneGraphUGK::Render()
* Walk through all the characters in the scene graph and execute the Render virtual method for all of them
*/
void CSceneGraphUGK::Render()
{ 
	unsigned int Size = Size();
	std::forward_list<CCharacter*>::iterator it = RootNode.begin();

	for (int i = 0; i < Size; i++)
	{
		(*it)->Render();
		std::advance(it, 1);
	}
}

/**
* @fn: void CSceneGraphUGK::Update()
* Walk through all the characters in the scene graph and execute the Update virtual method for all of them
*/
void CSceneGraphUGK::Update()
{
	unsigned int Size = Size();
	std::forward_list<CCharacter*>::iterator it = RootNode.begin();

	for (int i = 0; i < Size; i++)
	{
		(*it)->Update();
		std::advance(it, 1);
	}
}
#endif