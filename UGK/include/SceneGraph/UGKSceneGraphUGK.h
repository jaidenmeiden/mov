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

#define UGKSGUGK_NO_CHARACTER -1

#include <vector>

	namespace UGK
	{
		//CHANGE THE NEXT CODE TO USE YOUR STL DATA STRUCTURE
		typedef CCharacter* UGKSG_RootNode;

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
			inline void Init		()					{ /*CLEAR THE RootNode DATA STRUCTURE*/; currentCharacter = UGKSGUGK_NO_CHARACTER; }
			inline void SetPool		(CCharactersPool* P){ Pool = P; }

			inline void AddCharacter(CCharacter* Char)	{ /*ADD THE CHARACTER TO THE RootNode DATA STRUCTURE*/ };
			bool RemoveCharacter	(CCharacter* Char);
			void Render();
			void Update();
			/**
			* @fn: bool Empty()
			* Returns if the scene graph length is null. That is, there is no other character into the queue
			*/
			inline bool Empty() { return true;  /*RETURN IF THE RootNode DATA STRUCTURE IS EMPTY OR IF IT HAS ANY CHARACTER INSIDE*/}
			void Reset		 ();
			/**
			* @fn: unsigned int Size()
			* Returns the amount of elements the scene graph has
			*/
			inline unsigned int Size() { return true; /*RETURN THE RootNode DATA STRUCTURE SIZE*/}
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
				return nullptr;
			}
			
			//It returns the next character in the data structure
			inline CCharacter* Next()
			{ 
			}

			/**
			* @fn: CCharacter* Object(int index)
			* Returns the element number "index" from the scene graph. If it is past the end of the scenegraph or previous to the beginning, null is returned
			*/
			inline CCharacter* Object(int index) { return nullptr;}

		};
	}

#define CSceneGraph CSceneGraphTemplate<CSceneGraphUGK>
	#endif
#endif