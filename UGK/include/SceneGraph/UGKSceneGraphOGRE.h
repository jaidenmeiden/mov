/**	Declaration of the OGRE generic Scene graph
*	This file is only loaded if the UGKSG_OGRE constant is defined
*	There is no reason for loading the UGKCharacter.h header since this header is only loaded from  UGKSceneGraph.h
*	only when the generic UGK scene graph is selected. This UGKCharacter.h is loaded there

*	Prefix: UGKSGOSG_

*	@file UGKSceneGraphOGRE.h
*	@author Ramón Mollá
*	@version 2017-09
*/

#ifndef UGKSG_SCENE_GRAPH_OGRE
#define UGKSG_SCENE_GRAPH_OGRE

	#ifdef UGKSG_OGRE
	namespace UGK
	{
	#include <OgreSceneManager.h>

	#define UGKSG_Entity		OGRE::Entity
	#define UGKSG_SceneNode		OGRE::SceneNode

	class CSceneGraphOGRE:: public CSceneGraph
		{

		public:

			CSceneGraph();
			inline void AddCharacter(CCharacter* Char) {RootNode.push_back(Char);};
			void Render();
			void Update();
		};
	}
	#endif
#endif