/** Header with definitions needed for the management of any 3D mesh
*      Prefix: CM3D_   for class graphic card

*      @author Vicente Broseta Toribio
       First update: 2013-06
*      @Mofified: Ramón Mollá
*      @version 01-2015

       @mofified: Ernesto Muñoz
       @version: 04-2015
 */

//#include"Mesh3D.h"
#include <UGKMesh3D.h>
#include <UGKOS.h>

using namespace UGK;

/**
   * @fn CMesh3d::CMesh3d
   * Constructor Mesh3d
*/
CMesh3d::CMesh3d()
{
	IndexInList = CM3D_NO_MESH;
	FilePath.clear();
	FileName.clear();
	Loaded = false;
#ifdef UGKSG_OGRE
#elif defined (UGKSG_UGK)
#elif defined (UGKSG_CRY)
#elif defined (UGKSG_IRL)
#elif defined (UGKSG_TORQUE)
#elif defined (UGKSG_OSG)
#endif
}

/** 
   * @fn CMesh3d::LoadMesh
   * @param[in] Modelname Name of the file to be loaded.
   * Load the model from the filename.
*/
int CMesh3d::LoadMesh(UGKS_String Modelname)
{
	SetFileName(Modelname);
#ifdef UGKSG_OGRE
#elif defined (UGKSG_UGK)
	modelo.SetPath(FilePath);
	modelo.SetModelName(FileName);
	modelo.Load();
	Loaded = true;
#elif defined (UGKSG_CRY)
#elif defined (UGKSG_IRL)
#elif defined (UGKSG_TORQUE)
#elif defined (UGKSG_OSG)
	modelo = osgDB::readNodeFile(Modelname);
#endif
	return 0;
}

