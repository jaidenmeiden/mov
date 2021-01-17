/**	Definition of the UGK generic Scene graph

*	Prefix: UGKSG_

*	@file UGKSceneGraph.h
*	@author Ramón Mollá
*	@version 2017-09
*/

#ifndef UGKSG_SCENE_GRAPH
#define UGKSG_SCENE_GRAPH

#include <UGKCharactersPool.h>
#include <UGKSGType.h>

namespace UGK
{
	template <class C>	
	class CSceneGraphTemplate
	{
	protected:
		C*				 SceneGraph;

	public:
		CSceneGraphTemplate()					{ SceneGraph = new C(); }
		
		inline void ChangeRenderMode(CHAR_RENDER_MODE RenderMode) { SceneGraph->ChangeRenderMode(RenderMode); }
		inline void Init			()					{ SceneGraph->Init(); }
		inline void SetPool			(CCharactersPool* P){ SceneGraph->SetPool(P); }
		inline void AddCharacter	(CCharacter* Char)	{ SceneGraph->AddCharacter(Char); }
		inline void RemoveCharacter	(CCharacter* Char)	{ SceneGraph->RemoveCharacter(Char); }
		inline void Render			()					{ SceneGraph->Render(); }
		inline void Update			()					{ SceneGraph->Update(); }
		inline bool Empty			()					{ return SceneGraph->Empty(); }
		/**
		* @fn: void Reset()
		* Gets empty the whole scene graph by sending out from the queue all the objects back into the Pool
		*/
		inline void Reset			()					{ SceneGraph->Reset(); }
		inline unsigned int Size	()					{ return SceneGraph->Size(); }
		/**
		* @fn: CCharacter* First()
		* Always returns the first available element of the scene graph, if it exists
		  If it does not exist, it returns null.
		*/
		inline CCharacter* First	()					{ return SceneGraph->First(); }
		
		/**
		* @fn: CCharacter* Last()
		* Always returns the last available element of the scene graph, if it exists
		  If it does not exist (size == 0), it returns null.
		*/
		inline CCharacter* Last		()					{ return SceneGraph->Last(); }

		/**
		* @fn: CCharacter* Next()
		* Returns the next element the scene graph. If it is at the end of the scenegraph or there is no element inside, null is returned
		*/
		inline CCharacter* Next		()					{ return SceneGraph->Next();}
		inline CCharacter* Object	(int index)			{ return SceneGraph->Object(index); }
#ifdef UGKSG_OSG
		inline bool isViewerDone	()					{ return SceneGraph->isViewerDone(); }
		inline void addNode			(osg::Node* osgNode) { SceneGraph->addNode(osgNode); }
#endif
	};
}

	//Stencil to discriminate from one scene graph api to another
	#ifdef UGKSG_OGRE
	#include <UGKSceneGraphOGRE.h>
	#elif defined (UGKSG_UGK)
	#include <UGKSceneGraphUGK.h>
	#elif defined (UGKSG_CRY)
	#elif defined (UGKSG_IRL)
	#elif defined (UGKSG_TORQUE)
	#elif defined (UGKSG_OSG)
	#include <UGKSceneGraphOSG.h>
	#endif

#endif