/**	Definition of the UGK OSG Scene graph

*	Prefix: UGKSGOSG_

*	@file UGKSceneGraphOSG.h
*	@author Ramón Mollá
*	@version 2017-09
*
*	Modified: 2017-08 by David Ochando
*/

#ifndef UGKSG_SCENE_GRAPH_OSG
#define UGKSG_SCENE_GRAPH_OSG

#include <osgViewer/Viewer>
#include <osg/node>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include "UGKSGCNode.h"

#ifdef UGKSG_OSG

namespace UGK
{
#define UGKSG_CNode			OSGCNode
#define UGKSG_SceneNode		osg::Node
#define UGKSG_RootNode		osg::ref_ptr<osg::Group>
#define UGKSG_SceneViewer	osgViewer::Viewer
#define UGKSG_Transform		osg::PositionAttitudeTransform
#define UGKSG_Texture2D		osg::Texture2D
#define UGKSGOSG_NO_CHARACTER -1

	class CSceneGraphOSG
	{
		UGKSG_RootNode RootNode;
		UGKSG_SceneViewer	viewer;
		CCharactersPool* Pool;
		int currentCharacter;

	public:

		CSceneGraphOSG() { Init(); };

		void ChangeRenderMode(CHAR_RENDER_MODE RenderMode);

		/**
		* Initiator for the object Scene Graph
		*/
		inline void Init() { 
			if (RootNode.get() != NULL && RootNode.get()->getNumChildren() > 0)	{
				RootNode->removeChildren(0, RootNode->getNumChildren());
			} else {
				RootNode = new osg::Group();
			}
			currentCharacter = UGKSGOSG_NO_CHARACTER;
			viewer.setSceneData(RootNode.get());
			viewer.setCameraManipulator(new osgGA::TrackballManipulator);
			viewer.realize();
		}
		inline void SetPool(CCharactersPool* P) { Pool = P; }

		inline void AddCharacter(CCharacter* Char) 
		{ 
			osg::ref_ptr<UGKSG_CNode> osgNode = new UGKSG_CNode(Char);
			RootNode->addChild(osgNode);
		};

		inline void addNode(osg::Node* osgNode) { 
			RootNode->addChild(osgNode);
		}

		bool RemoveCharacter(CCharacter* Char);
		void Render();
		void Update();
		/**
		* @fn: bool Empty()
		* Returns if the scene graph length is null. That is, there is no other character into the queue
		*/
		inline bool Empty() { 
			return RootNode->getNumChildren() == 0;
		}
		void Reset();
		/**
		* @fn: unsigned int Size()
		* Returns the amount of elements the scene graph has
		*/
		inline unsigned int Size() { 
			return RootNode->getNumChildren();
		}
		/**
		* @fn: CCharacter*  First()
		* Returns the first element of the scene graph
		*/
		inline CCharacter* First() { currentCharacter = UGKSGOSG_NO_CHARACTER; return Next(); }
		/**
		* @fn: CCharacter*  Last()
		* Returns the last element of the scene graph
		*/
		inline CCharacter* Last()
		{
			currentCharacter = RootNode->getNumChildren() - 1;
			if (UGKSGOSG_NO_CHARACTER == currentCharacter)
				return NULL;
			else {
				osg::Node* osgNode = RootNode->getChild(currentCharacter);
				UGKSG_CNode* cNode = dynamic_cast<UGKSG_CNode*>(osgNode);
				return cNode->getCharacter();
			}
		}
		/**
		* @fn: CCharacter* Next()
		* Returns the next element the scene graph. If it is at the end of the scenegraph, null is returned
		*/
		inline CCharacter* Next()
		{
			currentCharacter++;
			if (currentCharacter >= RootNode->getNumChildren())
			{
				currentCharacter = RootNode->getNumChildren() - 1;
				return NULL;
			}
			osg::Node* osgNode = RootNode->getChild(currentCharacter);
			UGKSG_CNode* cNode = dynamic_cast<UGKSG_CNode*>(osgNode);
			return cNode->getCharacter();
		}

		/**
		* @fn: CCharacter* Object(int index)
		* Returns the element number "index" from the scene graph. If it is past the end of the scenegraph or previous to the beginning, null is returned
		*/
		inline CCharacter* Object(int index) {
			if (index<0 || index > RootNode->getNumChildren())
				return NULL;
			else {
				osg::Node* osgNode = RootNode->getChild(index);
				UGKSG_CNode* cNode = dynamic_cast<UGKSG_CNode*>(osgNode);
				return cNode->getCharacter();
			}
		}

		/**
		* @fn: bool isViewerDone()
		* Returns if the viewer has finished
		*/
		inline bool isViewerDone() { return viewer.done(); }
	};
}

#define CSceneGraph CSceneGraphTemplate<CSceneGraphOSG>
#endif
#endif