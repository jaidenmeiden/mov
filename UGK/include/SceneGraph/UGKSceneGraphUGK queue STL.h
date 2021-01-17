/**	Definition of the UGK generic Scene graph
*	There is no reason for loading the UGKCharacter.h header since this header is only loaded from  UGKSceneGraph.h
*	only when the generic UGK scene graph is selected. This UGKCharacter.h is loaded there

*	Prefix: UGKSGUGK_

*	@file UGKSceneGraphUGK.h
*	@author Jaime Juan y Daniel Diosdado
*	@version 2018-12
*/
#include <queue>

#ifndef UGKSG_SCENE_GRAPH_UGK
#define UGKSG_SCENE_GRAPH_UGK

#ifdef UGKSG_UGK

#define UGKSGUGK_NO_CHARACTER -1

namespace UGK
{
	typedef std::queue<CCharacter*> UGKSG_RootNode;			///Modificacion de la deque por una queue normal

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
		* Funcion Init() la cual vacia la cola si no esta llena haciendo uso de pop()
		*/
		inline void Init() 
		{ 
			//RootNode.clear();
			while (!RootNode.empty()) {			///Mientras la cola no este vacia hacemos pop()
				RootNode.pop();
			}
			currentCharacter = UGKSGUGK_NO_CHARACTER; 
		}
		inline void SetPool(CCharactersPool* P) { Pool = P; }

		inline void AddCharacter(CCharacter* Char) { RootNode.push(Char); };	///Añadimos un personaje con push
		bool RemoveCharacter(CCharacter* Char);
		void Render();
		void Update();
		/**
		* @fn: bool Empty()
		* Returns if the scene graph length is null. That is, there is no other character into the queue
		*/
		inline bool Empty() { return RootNode.empty(); }		///Comprobamos si la cola esta vacia
		void Reset();
		/**
		* @fn: unsigned int Size()
		* Returns the amount of elements the scene graph has
		*/
		inline unsigned int Size() { return RootNode.size(); }		///Obtenemos la talla de la cola
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
			currentCharacter = RootNode.size() - 1;
			if (UGKSGUGK_NO_CHARACTER == currentCharacter)
				return NULL;
			else return RootNode.back();	///Accedemos al ultimo elemento de la cola 
		}
		/**
		* @fn: CCharacter*  Next()
		* Devuelve el siguiente personaje utilizando una cola auxiliar (copia de RootNode) y un entero
		* Mientras el entero no coincida con la variable currentCharacter iremos haciendo pop() 
		* Una vez detectado el personaje se devuelve el front de la cola auxiliar
		*/
		inline CCharacter* Next()
		{
			
			currentCharacter++;
			if (currentCharacter >= RootNode.size())
			{
				currentCharacter = RootNode.size() - 1;
				return NULL;
			}
			else if (UGKSGUGK_NO_CHARACTER >= currentCharacter) return NULL;
			else {
				std::queue<CCharacter*> aux = RootNode;		///Cola auxiliar (copia de RootNode) 
				int i = 0;									///Entero para controlar el personaje
				while (i != currentCharacter)				
				{
					aux.pop();
					i++;
				}
				return aux.front();
			} 
		}

		/**
		* @fn: CCharacter* Object(int index)
		* Devuelve el elemento en la posicion index, en caso de no encontrarse en el rango delimitado por el tamaño se devuelve null
		* Se opera de forma similar a la funcion next, controlando la posicion con un entero e iterando sobre una cola auxiliar
		* Cuando se llega al elemento en la posicion index se devuelve el front de la cola auxiliar
		*/
		inline CCharacter* Object(int index) { if (index<0 || index > Size()) return NULL; else {
			std::queue<CCharacter*> aux = RootNode;		///Cola auxiliar (copia de RootNode) 
			int i = 0;									///Entero para controlar el personaje
			while (i != index)
			{
				aux.pop();
				i++;
			}
			return aux.front();
		}  }

	};
}

#define CSceneGraph CSceneGraphTemplate<CSceneGraphUGK>
#endif
#endif