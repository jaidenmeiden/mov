/* 
	Author: Vicente Broseta Toribio
	Last update: 2013-06
*/

#include"TexturesManager.h"
#include <sstream>

CTexturesManager::CTexturesManager(){FilesPath.clear();}

CTexturesManager::~CTexturesManager(){
	for(unsigned int i=0;i<Textures.size();i++)
		delete(Textures[i]);
}

void CTexturesManager::CreateTexture(UGKS_String filename, unsigned int indexList){
	
	stringstream ss, ss1;
	string strg;

	CTexture *texAux;
	texAux = new (CTexture);

	texAux->SetFilePath(FilesPath);
	texAux->Load(filename);
	texAux->IndexInList = indexList;
	
	if(indexList < Textures.size()){	
		Textures[indexList] = texAux;
	}else if(indexList == Textures.size()){
		Textures.push_back(texAux);
	}else{
		Textures.resize(indexList);
		Textures.push_back(texAux);
	}
}

int CTexturesManager::CreateTexture(UGKS_String filename)
{
	CTexture *texAux;

	for(unsigned int i = 0; i<Textures.size();i++)
		if (0 == filename.compare(Textures[i]->GetFileName()))
			return i;

	//This texture has not been stored before
	texAux = new (CTexture);

	texAux->IndexInList = Textures.size();
	texAux->SetFilePath(FilesPath);
	texAux->Load(filename);
	
	Textures.push_back(texAux);
	return texAux->IndexInList;
}

void CTexturesManager::FreePositionOfTexture(unsigned int indexList){
	Textures[indexList]->FreeTexture();
}

void CTexturesManager::ReserveTexturePosition(unsigned int indexList){
	CTexture *texAux;
	texAux = new (CTexture);
	texAux->IndexInList = indexList;
	Textures.insert(Textures.begin()+indexList, texAux);
}

void CTexturesManager::AssignFile2Texture(UGKS_String path, UGKS_String filename, unsigned int indexList)
{
	if(Textures[indexList]->IndexInList == indexList)
	{
		Textures[indexList]->SetFilePath(path);
		Textures[indexList]->Load(filename);
	}
}

/**
* @fn void LoadTextures(UGKS_String fileName[], unsigned int amount)
* Loads the list of Textures to manage during the whole game
* @Param [in] fileName[]	Name of the every texture to load. The order matters since it is the number used to call it later
* @Param [in] amount		Quantity of textures to load
*/
void CTexturesManager::LoadTextures(UGKS_String fileName[], unsigned int amount)
{
	Textures.resize(amount);
	for (unsigned int i = 0; i < amount; i++)
	{
		if (NULL == Textures[i])
			Textures[i] = new CTexture();
		Textures[i]->SetFilePath(FilesPath);
		Textures[i]->SetFileName(fileName[i]);
		Textures[i]->Load();
	}
}