/**	Definition of the class Mesh Manager

*Prefix: CMM_

	@Author: Vicente Broseta Toribio
	@Last update: 2013-06
*/

#ifndef CMM_MESHMANAGER //se borra la macro Manegador de Malla
#define CMM_MESHMANAGER //se define la macro Manegador de Malla

//#include "Copyright.h"
#include <UGKMesh3D.h>
#include <vector>

/**   
   * Defines the class MeshManager
   * Where are the constructor, destructor and start
   * The characters or ships the same type have the same geometry, anyone have their mesh
   * Defines one Mesh array on base 3DS.h
*/
namespace UGK
{
	class UGK_API CMeshesManager
	{
	protected:
		//Private Atributes
		UGKS_String FilesPath;
	
		/// All the characters of the same type, use the same geometry. So there is no reason to replicate
		/// the same mesh for everyone. Every character has a pointer to a given mesh type.
		/// There is a need to have a common repository for every possible character mesh
		std::vector<CMesh3d*> Meshes;	///<An array of 3DS meshes
	
	public:
		unsigned int LogIndex;
    
		///Constructor of the class
		CMeshesManager	();

		///Destructor of the class
		~CMeshesManager	();

		void AddModel			(UGKS_String filename, unsigned int indexList);
		int  AddModel			(UGKS_String filename);
		
		inline CMesh3d*	GetMesh(unsigned int M){ if (CM3D_NO_MESH == M) return NULL; else if (Meshes.size() <= M) return NULL; else return Meshes[M]; }
		
		/**
		* CMeshesManager::SetFilesPath
		* @param[in] path Files path
		* Set the Mesh Manager path.
		* Set the Mesh Manager path. All loaded files must be inside this path.
		*/
		inline void		SetFilesPath	(UGKS_String path)	{ FilesPath = path; }
		inline UGKS_String	GetFilesPath	()				{ return FilesPath; }

		void ReserveMeshPosition(unsigned int indexList);
		void AssignFile2Mesh	(UGKS_String path, UGKS_String filename, unsigned int indexList);

		inline void			ClearAllMeshes(){ Meshes.clear(); }
		inline unsigned int	MeshesAmount()	{ return Meshes.size(); }

	};
}
#endif
