/**	Declaration of the UGK OSG Scene graph
This file is only loaded if the UGKSG_OSG constant is defined
So, there is no reason to check for a conditional compilation

*	Prefix: UGKSGOSG_

*	@author David Ochando
*	@version 2017-09
*/

#include <UGKSceneGraph.h>

#ifdef UGKSG_OSG
using namespace UGK;

/**
* @fn: void CSceneGraphOSG::ChangeRenderMode(CHAR_RENDER_MODE RenderMode)
* TODO
*/
void CSceneGraphOSG::ChangeRenderMode(CHAR_RENDER_MODE RenderMode)
{	
}

/**
* @fn: void CSceneGraphOSG::Reset()
* Gets empty the whole scene graph by sending out from the queue all the objects back into the Pool
*/
void CSceneGraphOSG::Reset()
{
	osg::Group* root = RootNode.get();
	unsigned int size = root->getNumChildren();

	while (size>0);
	{
		//Save character into the pool for later reuse
		osg::Node* osgNode = root->getChild(0);
		UGKSG_CNode* cNode = dynamic_cast<UGKSG_CNode*>(osgNode);
		Pool->save(cNode->getCharacter());
		//Erase the first element
		root->removeChildren(0, 1);
		size = root->getNumChildren();
	}
}

/**
* @fn: bool CSceneGraphOSG::RemoveCharacter(CCharacter* Char)
* Walk through the characters in the scene graph. Detect  the character looked for and take it out from the queue and set it into the Pool
*/
bool CSceneGraphOSG::RemoveCharacter(CCharacter* Char)
{
	osg::Group* root = RootNode.get();
	osg::Node* osgNode;
	unsigned int dequeSize = root->getNumChildren();

	for (int i = 0; i < dequeSize; i++)
	{
		osgNode = root->getChild(i);
		UGKSG_CNode* cNode = dynamic_cast<UGKSG_CNode*>(osgNode);
		CCharacter* character = cNode->getCharacter();
		if (character == Char)
		{
			//Neutralize element
			character = NULL;
			//Erase it
			root->removeChildren(i, i+1);
			//Save character into the pool for later reuse
			Pool->save(Char);
			return true;
		}
	}
	return false;
};

/**
* @fn: void CSceneGraphOSG::Render()
* Render one frame
*/
void CSceneGraphOSG::Render()
{
	viewer.frame();
}

/**
* @fn: void CSceneGraphOSG::Update()
*/
void CSceneGraphOSG::Update()
{
}
#endif