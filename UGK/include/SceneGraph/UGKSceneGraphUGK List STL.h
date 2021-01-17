/**	Definition of the UGK generic Scene graph
*	There is no reason for loading the UGKCharacter.h header since this header is only loaded from  UGKSceneGraph.h
*	only when the generic UGK scene graph is selected. This UGKCharacter.h is loaded there

*	Prefix: UGKSGUGK_

*	@file UGKSceneGraphUGK.h
*	@authors Jose Manuel Fuentes López, David Páramo Alonso
*	@version 2018-12
*/


#ifndef UGKSG_SCENE_GRAPH_UGK
#define UGKSG_SCENE_GRAPH_UGK

#ifdef UGKSG_UGK

#define UGKSGUGK_NO_CHARACTER -1
#include <list>

	namespace UGK
	{

		typedef std::list<CCharacter*> UGKSG_RootNode;

		class UGKSG_SceneNode {};
		class UGKSG_SceneViewer {};

		class CSceneGraphUGK
		{
			UGKSG_RootNode RootNode;
			CCharactersPool* Pool;
			UGKSG_RootNode::iterator currentCharacter;

		public:

			/**
			* Constructor for the object Scene Graph
			*/
			CSceneGraphUGK() { Init(); };

			void ChangeRenderMode(CHAR_RENDER_MODE RenderMode);

			/**
			* Initiator for the object Scene Graph
			*/
			inline void Init		()					{ RootNode.clear(); currentCharacter = RootNode.end(); }
			inline void SetPool		(CCharactersPool* P){ Pool = P; }

			inline void AddCharacter(CCharacter* Char)	{RootNode.push_back(Char);};
			bool RemoveCharacter	(CCharacter* Char);
			void Render();
			void Update();
			/**
			* @fn: bool Empty()
			* Returns if the scene graph length is null. That is, there is no other character into the queue
			*/
			inline bool Empty() {return RootNode.empty();}
			void Reset		 ();
			/**
			* @fn: unsigned int Size()
			* Returns the amount of elements the scene graph has
			*/
			inline unsigned int Size() { return RootNode.size(); }
			/**
			* @fn: CCharacter*  First()
			* Returns the first element of the scene graph
			*/
			inline CCharacter* First() { 
				currentCharacter = RootNode.begin();
				if (currentCharacter == RootNode.end())
					return NULL;
				else
					return *currentCharacter;
			}
			/**
			* @fn: CCharacter*  Last()
			* Returns the last element of the scene graph
			*/
			inline CCharacter* Last() 
			{
				currentCharacter = std::prev(RootNode.end());
				if (currentCharacter == RootNode.end())
					 return NULL; 
				else {
					return *currentCharacter;
				}
			}
			
			inline CCharacter* Next()
			{ 
				currentCharacter = std::next(currentCharacter);
				if (currentCharacter == RootNode.end())
				{
					currentCharacter = std::prev(currentCharacter);
					return NULL;
				}
				else{
					return *currentCharacter;
				}
			}

			/**
			* @fn: CCharacter* Object(int index)
			* Returns the element number "index" from the scene graph. If it is past the end of the scenegraph or previous to the beginning, null is returned
			*/
			inline CCharacter* Object(int index) { 
				if (index<0 || index >= Size()) return NULL; 
				else {
					currentCharacter = RootNode.begin();
					std::advance(currentCharacter, index);
					return *currentCharacter;
				}
			}

			inline void Remove() {
				RootNode.erase(currentCharacter);
			}

		};
	}

#define CSceneGraph CSceneGraphTemplate<CSceneGraphUGK>
	#endif
#endif