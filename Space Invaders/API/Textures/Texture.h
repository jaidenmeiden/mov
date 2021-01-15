/**	General Texture class that manages general functions of any given image

*	Prefix CT_: Class Texture

*	@Author: Vicente Broseta Toribio: 2013-06
*	@author Ramon Molla
*	@version 01-2015
*/

#ifndef TEXTUREV_H
#define TEXTUREV_H

#include <glaux.h>
#include <UGKString.h>

using namespace std;

#define CT_NOT_INDEXED -1
#define CT_ERROR -1
#define CT_NO_ERROR 0

typedef struct {
	GLint tmode, // Modo de aplicación de la textura
		minMode, // Modo de minimización de textura
		maxMode, // Modo de maximización de textura
		wrap_s,  // Modos de extensión de la textura
		wrap_t;
	unsigned int width, height; // Tamaño de la textura
	GLuint gl_id;
} Ttexture;

class CTexture
{
private:
	int LoadBMP(UGKS_String name);						// Loads a bitmap file
	int LoadTGA(UGKS_String name);						// Loads a targa file
	
	UGKS_String FilePath;
	UGKS_String FileName;

public:
	Ttexture Texture;
	unsigned int IndexInList;
	bool Loaded;

	CTexture();
	~CTexture(){}

	inline UGKS_String	SetPathFile(UGKS_String filename){ FileName = filename; };
	UGKS_String			GetPathFile(UGKS_String filename);
	UGKS_String			GetPathFile();

	void	SetTexture	(void);
	void	FreeTexture	(void);

	int			Load(UGKS_String filename, Ttexture *dest);
	int			Load(UGKS_String filename);
	inline int	Load(void)	{return Load(FileName,&Texture);}

	inline void SetFileName(UGKS_String filename) { FileName = filename; }
	inline void SetFilePath(UGKS_String filepath) { FilePath = filepath; }

	inline UGKS_String GetFileName(){ return FileName; };
	inline UGKS_String GetFilePath(){ return FilePath; };
};

#endif // TEXTUREV.H