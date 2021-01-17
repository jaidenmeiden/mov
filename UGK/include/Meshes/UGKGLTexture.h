/**	General Texture class that manages general functions of any given image

*	Prefix CT_: Class Texture

*	@Author: Vicente Broseta Toribio: 2013-06
*	@Refactored to Ctring and insertinto UGK by Ramon Molla
*	@version 11-2015
*/

#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#ifndef WINDOWS_LOADED
#define WINDOWS_LOADED
#include <windows.h>
#endif

#include <glaux.h>		// Header File For The Glaux Library
#include <UGKString.h>

#define CT_BMP_EXT ".bmp"
#define CT_TGA_EXT ".tga"

class UGK_API GLTextureV
{
protected:

	UGKS_String FilePath;
	UGKS_String FileName;

public:
	unsigned int texture[1];						// OpenGL's number for the texture
	int width;										// Texture's width
	int height;										// Texture's height
	void Use();										// Binds the texture for use
	void BuildColorTexture	(unsigned char r, unsigned char g, unsigned char b);	// Sometimes we want a texture of uniform color
	void LoadTGAResource	(UGKS_String name);		// Load a targa from the resources
	void LoadBMPResource	(UGKS_String name);		// Load a bitmap from the resources
	void LoadFromResource	(UGKS_String name);		// Load the texture from a resource
	void LoadTGA			(UGKS_String name);		// Loads a targa file
	void LoadBMP			(UGKS_String name);		// Loads a bitmap file
	void Load				(UGKS_String name);		// Load the texture

	GLTextureV();									// Constructor
	virtual ~GLTextureV();							// Destructor

	void			SetPathFile(UGKS_String filename);
};

#endif GLTEXTURE_H