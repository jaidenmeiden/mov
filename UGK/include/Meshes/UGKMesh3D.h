/* 
	Author: Vicente Broseta Toribio
	Last update: 2013-06
*/

#ifndef MODELO3D_H
#define MODELO3D_H

#include <UGKSGType.h>

#ifdef UGKSG_OGRE
#elif defined (UGKSG_UGK)
#include <UGKModel_3DS.h>
#include<sstream>
#elif defined (UGKSG_CRY)
#elif defined (UGKSG_IRL)
#elif defined (UGKSG_TORQUE)
#elif defined (UGKSG_OSG)
#include <UGKString.h>
#include <osg/node>
#include <osgDB/ReadFile>
#endif

#define CM3D_NO_MESH -1

using namespace std;

namespace UGK
{
#ifdef UGKSG_OGRE
#elif defined (UGKSG_UGK)
	class UGK_API CMesh3d
	{
	protected:
		UGKS_String FilePath;
		UGKS_String FileName;

	public:
		Model_3DS modelo;
		int IndexInList;
		bool Loaded;

		CMesh3d();
		~CMesh3d() {};

		int LoadMesh(UGKS_String filename);
		int LoadMesh();

		//Setters
		/**
		* @fn void CMesh3d::SetFilePath(UGKS_String filepath)
		* @param[in] filepath New path for the model.
		* Saves a new path for the model.
		* Deletes the ol path an sets the new path to the model.
		*/
		inline void SetFilePath(UGKS_String filepath) { FilePath = filepath; }

		/**
		* @fn void CMesh3d::SetFileName(UGKS_String filename)
		* @param[in] filename New name of the model.
		* Saves a new name for the model.
		* Deletes the old name and sets the new name to the model.
		*/
		inline void SetFileName(UGKS_String filename) { FileName = filename; }

		//Getters
		inline UGKS_String GetFilePath() { return FilePath; };
		inline UGKS_String GetFileName() { return FileName; };
};
#elif defined (UGKSG_CRY)
#elif defined (UGKSG_IRL)
#elif defined (UGKSG_TORQUE)
#elif defined (UGKSG_OSG)
	class CMesh3d
	{
	protected:
		UGKS_String FilePath;
		UGKS_String FileName;

	public:
		osg::Node* modelo;
		int IndexInList;
		bool Loaded;

		CMesh3d();
		~CMesh3d() {};

		int LoadMesh(UGKS_String filename);

		//Setters
		/**
		* @fn void CMesh3d::SetFilePath(UGKS_String filepath)
		* @param[in] filepath New path for the model.
		* Saves a new path for the model.
		* Deletes the ol path an sets the new path to the model.
		*/
		inline void SetFilePath(UGKS_String filepath) { FilePath = filepath; }

		/**
		* @fn void CMesh3d::SetFileName(UGKS_String filename)
		* @param[in] filename New name of the model.
		* Saves a new name for the model.
		* Deletes the old name and sets the new name to the model.
		*/
		inline void SetFileName(UGKS_String filename) { FileName = filename; }

		//Getters
		inline UGKS_String GetFilePath() { return FilePath; };
		inline UGKS_String GetFileName() { return FileName; };
		inline osg::Node* getMesh() { return modelo; };
	};
#endif

	
}
#endif // MODELO3D.H