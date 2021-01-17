/** 
	@author Vicente Broseta
	@version 2013-06
       * Version: 01-2015^M
       * Refactored: Ramón Mollá

       @mofified: Ernesto Muñoz
       @version: 04-2015

*/

//#include "MeshManager.h"
#include <UGKMeshManager.h>

using namespace UGK;


/**   
   * @fn CMeshesManager::CMeshesManager
   * constructor Mesh Manager
   * Initialices the Mesh Manager without filespath.
*/
CMeshesManager::CMeshesManager()
{
	FilesPath.clear();
}

/**   
   * @fn CMeshManager::~CMeshManager
   * destroyer Mesh Manager
   * Destroys all meshes stored in the list.
*/
CMeshesManager::~CMeshesManager()
{
	for(unsigned int i=0;i<Meshes.size();i++)
		delete(Meshes[i]);
}

/**   
   * @fn void CMeshesManager::AddModel(UGKS_String filename, unsigned int indexList)
   * @param[in] filename Name of the file that cointains the model inside the file path of the manager.
   * @param[in] indexList Position where the model will be placed in the models list.
   * Add a model in the desired position of the models list
   * Create and loads a new model. The new model will be placed in the position suggested.
   * If this position is to big to fit in the list, the list will be resized.
*/

void CMeshesManager::AddModel(UGKS_String filename, unsigned int indexList)
{
	CMesh3d *modAux;

	modAux = new (CMesh3d);

	modAux->SetFilePath(FilesPath);
	modAux->LoadMesh(filename);
	modAux->Loaded = true;
	modAux->IndexInList = indexList;
	
	if(indexList < Meshes.size()){	
		Meshes[indexList] = modAux;
	}else if(indexList == Meshes.size()){
		Meshes.push_back(modAux);
	}else{
		Meshes.resize(indexList);
		Meshes.push_back(modAux);
	}	
}

/**   
   * @fn int CMeshesManager::AddModel(UGKS_String filename)
   * @param[in] filename Name of the file that cointains the model inside the file path of the manager.
   * Add a model to the meshes list.
   * Create and loads a new model. The new model will be placed in the list if there is not 
   * a model loaded from the same file.
*/

int CMeshesManager::AddModel(UGKS_String filename)
{
	CMesh3d *modAux;

	for(unsigned int i = 0; i<Meshes.size();i++)
               if (0 == filename.compare(Meshes[i]->GetFileName()))
                       return i;

	//This mesh has not been stored before^M
    modAux = new (CMesh3d);

	modAux->IndexInList = Meshes.size();
	modAux->SetFilePath(FilesPath);
	modAux->LoadMesh(filename);
	modAux->Loaded = true;
	
	Meshes.push_back(modAux);
	return Meshes.size() - 1;
}

/**   
   * @fn void CMeshesManager::ReserveMeshPosition(unsigned int indexList)
   * @param[in] indexList Index in the list to be reserved.
   * Reserves a position in the models list.
   * Creates a Mesh in the position indicated but no file is loaded for that mesh.
*/
void CMeshesManager::ReserveMeshPosition(unsigned int indexList)
{
	CMesh3d *meshAux;
	meshAux = new (CMesh3d);
	meshAux->IndexInList = indexList;
	Meshes.insert(Meshes.begin()+indexList, meshAux);
}

/**   
   * @fn void CMeshesManager::AssignFile2Mesh(UGKS_String path, UGKS_String filename, unsigned int indexList)
   * @param[in] path Path where the filename is located.
   * @param[in] filename File where the model is saved.
   * @param[in] indexList Index in the models list where the model is going to be placed.
   * Assign a model to a reserved location.
*/
void CMeshesManager::AssignFile2Mesh(UGKS_String path, UGKS_String filename, unsigned int indexList)
{
	if(Meshes[indexList]->IndexInList == indexList){
		Meshes[indexList]->SetFilePath(path);
        Meshes[indexList]->LoadMesh(filename);
	}
 }


