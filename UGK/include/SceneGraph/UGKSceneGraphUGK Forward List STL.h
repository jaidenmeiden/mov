/**	Definition of the UGK generic Scene graph
*	There is no reason for loading the UGKCharacter.h header since this header is only loaded from  UGKSceneGraph.h
*	only when the generic UGK scene graph is selected. This UGKCharacter.h is loaded there

*	Prefix: UGKSGUGK_

*	@file UGKSceneGraphUGK.h
*	@author Ramón Mollá
*	@version 2017-09
*/

#ifndef UGKSG_SCENE_GRAPH_UGK
#define UGKSG_SCENE_GRAPH_UGK

#ifdef UGKSG_UGK

#include <forward_list>
#define UGKSGUGK_NO_CHARACTER -1

	namespace UGK
	{
		//! Forward List containing all the Characters in a scene. Transformed from Deque to Forward List.
		typedef std::forward_list<CCharacter*> UGKSG_RootNode;

		class UGKSG_SceneNode {};
		class UGKSG_SceneViewer {};

		class CSceneGraphUGK
		{
			UGKSG_RootNode RootNode;
			CCharactersPool* Pool;
			int currentCharacter;

		public:

			/**
			* Constructor for the object Scene Graph
			*/
			CSceneGraphUGK() { Init(); };

			void ChangeRenderMode(CHAR_RENDER_MODE RenderMode);

			/**
			* Initiator for the object Scene Graph
			*/
			inline void Init		()					{ RootNode.clear(); currentCharacter = UGKSGUGK_NO_CHARACTER; }
			inline void SetPool		(CCharactersPool* P){ Pool = P; }

			/**
			* @fn: void AddCharacter(CCharacter* Char)
			* Adds a new Character at the beginning of the forward_list, before its current 
			* first element.
			*/
			inline void AddCharacter(CCharacter* Char)	{RootNode.push_front( Char);};
			
			bool RemoveCharacter	(CCharacter* Char);
			void Render();
			void Update();

			/**
			* @fn: bool Empty()
			* Returns if the scene graph length is null. That is, there is no other character into the forward_list
			*/
			inline bool Empty() {return RootNode.empty();}
			
			void Reset		 ();

			/**
			* @fn: unsigned int Size()
			* Returns the amount of elements the scene graph has
			*/
			inline unsigned int Size() { return std::distance(RootNode.begin(), RootNode.end()); }

			/**
			* @fn: CCharacter*  First()
			* Returns the first element of the scene graph
			*/
			inline CCharacter* First() { currentCharacter = UGKSGUGK_NO_CHARACTER; return Next(); }
			
			/**
			* @fn: CCharacter*  Last()
			* Returns the last element of the scene graph
			*/
			inline CCharacter* Last() 
			{ 
				currentCharacter = std::distance(RootNode.begin(), RootNode.end()) - 1;
				if (UGKSGUGK_NO_CHARACTER == currentCharacter) 
					 return NULL; 
				else
				{
					std::forward_list<CCharacter*>::iterator it = RootNode.begin();
					std::advance(it, currentCharacter);
					return *it;
				}
			}
			
			/**
			* @fn: CCharacter*  Next()
			* Returns the next element of the scene graph
			*/
			inline CCharacter* Next()
			{ 
				currentCharacter++; 
				if (currentCharacter >= std::distance(RootNode.begin(), RootNode.end()))
				{
					currentCharacter = std::distance(RootNode.begin(), RootNode.end()) - 1;
					return NULL;
				}
				else if (UGKSGUGK_NO_CHARACTER >= currentCharacter)
				{
					return NULL;
				} 
				else
				{
					std::forward_list<CCharacter*>::iterator it = RootNode.begin();
					std::advance(it, currentCharacter);
					return *it;
				}
			}

			/**
			* @fn: CCharacter* Object(int index)
			* Returns the element number "index" from the scene graph. If it is past the end of the scenegraph or previous to the beginning, null is returned
			*/
			inline CCharacter* Object(int index) 
			{ 
				if (index<0 || index > Size())
				{
					return NULL;
				}
				else
				{
					std::forward_list<CCharacter*>::iterator it = RootNode.begin();
					std::advance(it, index);
					return *it;
				}
			}

		};
	}

#define CSceneGraph CSceneGraphTemplate<CSceneGraphUGK>
	#endif
#endif