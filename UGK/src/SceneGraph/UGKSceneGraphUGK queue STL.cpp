/**	Declaration of the UGK generic Scene graph
	This file is only loaded if the UGKSG_UGK constant is defined
	So, there is no reason to check for a conditional compilation

*	Prefix: UGKSGUGK_

*	@author Jaime Juan y Daniel Diosdado
*	@version 2018-12
*/

#include <UGKSceneGraph.h>

#ifdef UGKSG_UGK
using namespace UGK;

/**
* @fn: void CSceneGraphUGK::ChangeRenderMode(CHAR_RENDER_MODE RenderMode)
* Se recorre el grafo de escena modificando el RenderMode
* Se crea una cola auxiliar para modificar el RenderMode de los distintos Characters
* Con front() accedemos al primer elemento de la cola y con pop() lo eliminamos para dejar en front al siguiente 
*/
void CSceneGraphUGK::ChangeRenderMode(CHAR_RENDER_MODE RenderMode)
{

	std::queue<CCharacter*> aux = RootNode;	///Creamos una cola auxiliar 
	while (!aux.empty())				
	{
		aux.front()->ChangeRenderMode(RenderMode);		///Acceso primer elemnto cola
		aux.pop();										///Eliminacion primer elemento cola

	}

}

/**
* @fn: void CSceneGraphUGK::Reset()
* Reinicio del grafo de escena
* Se recorre la cola guardando los elementos en el Pool y eliminandolos de esta, gracias la combinacion de front() y pop()
*/
void CSceneGraphUGK::Reset()
{

	while (!RootNode.empty());
	{
		//Save character into the pool for later reuse
		Pool->save(RootNode.front());		///Guardamos el puntero con front()
		//Erase the first element
		RootNode.pop();						///Eliminamos el puntero de la cola con pop()
	}
}

/**
* @fn: bool CSceneGraphUGK::RemoveCharacter(CCharacter* Char)
* Eliminacion de un personaje del grafo de escena
* Se recorre el grafo hasta encontrar el personaje, para posteriormente guardarlo en el Pool y eliminarlo
* Para realizar la funcionalidad se han utilizado dos colas:
* La primera nos permite buscar sobre los distintos character para eliminar el deseado
* La segunda guarda aquellos personajes de la primera que no deben de ser eliminados, permitiendo reconstruir la cola sin el personaje eliminado (esta cola pasara a ser la actual RootNode)
*/
bool CSceneGraphUGK::RemoveCharacter(CCharacter* Char)
{
	unsigned int size = RootNode.size();	
	bool removed = false;								///Boolean que controla la eliminacion del personaje
	std::queue<CCharacter*> aux = RootNode;				///Cola auxiliar para buscar el elemento a eliminar
	std::queue<CCharacter*> newQueue;		///Cola que contendra los elemento sin el personaje a borrar (RootNode copiara a esta)
	for (int i = 0; i < size; i++)
		if(aux.front() != Char)				///Si el personaje no es el que tenemos que eliminar lo introducimos en la nueva cola
		{
			newQueue.push(aux.front());
			aux.pop();
		}else
		{
			aux.front() = NULL;
			aux.pop();
			Pool->save(Char);
			removed = true;
		}

	RootNode = newQueue;			///Actualizamos RootNode con la nueva cola
	return removed;					///Devolvemos si se ha eliminado el personaje

};

/**
* @fn: void CSceneGraphUGK::Render()
* Renderizado de los character
* Se crea una cola auxiliar y se recorre con front y pop para renderizar los character
*/
void CSceneGraphUGK::Render()
{

	std::queue<CCharacter*> aux = RootNode;	///Cola auxiliar
	while (!aux.empty())				///Mientras queden elementos en la cola los vamos renderizando
	{
		aux.front()->Render();
		aux.pop();

	}
}

/**
* @fn: void CSceneGraphUGK::Update()
* Update de los character
* Se crea una cola auxiliar y se recorre con front y pop para actualizar los character
*/
void CSceneGraphUGK::Update()
{
	std::queue<CCharacter*> aux = RootNode;	///Creamos una cola auxiliar 
	while (!aux.empty())				///Mientras queden elementos en la cola los vamos renderizando
	{
		aux.front()->Update();
		aux.pop();

	}
}
#endif