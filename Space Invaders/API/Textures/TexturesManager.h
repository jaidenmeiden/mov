/**	
*	@file UGKMesh3D.h
*	Definition of the class CTexturesManager. Base class for all textures in the system

*	Prefix: CTM_

* 	@author: Vicente Broseta Toribio
*	@refactoring Ramon Molla
*	@version 1.1
*	@updated 2017-02
*/

#ifndef TEXTURESMANAGERV_H
#define TEXTURESMANAGERV_H

#include"Texture.h"
#include <UGKCharacter.h>
//#include <vector>

#define CTM_NO_TEXTURE -1

class CTexturesManager: public UGK::CCharacter
{
public:
	
	vector <CTexture*> Textures;
	UGKS_String FilesPath;
	unsigned int LogIndex;

	CTexturesManager();
	~CTexturesManager();
	
	inline void SetFilesPath(UGKS_String path) { FilesPath = path; }

	void CreateTexture(UGKS_String filename, unsigned int indexList);		//Creates one new Texture, assing position and load.
	int CreateTexture(UGKS_String filename);								//Creates one new Texture at the end position.
	void FreePositionOfTexture(unsigned int indexList);
	void ReserveTexturePosition(unsigned int indexList);			//Creates one new Texture and assing position (without load).
	void AssignFile2Texture(UGKS_String path, UGKS_String filename, unsigned int indexList);			//Assign a file to texture already created in reserved position.	

	/**
	* @fn void LoadTextures(UGKS_String fileName[], unsigned int amount)
	* Loads the list of Textures to manage during the whole game
	* @Param [in] fileName[]	Name of the every texture to load. The order matters since it is the number used to call it later
	* @Param [in] amount		Quantity of textures to load
	*/
	void LoadTextures(UGKS_String fileName[], unsigned int amount);

};

#endif // TEXTURESMANAGERV.H