/**
 *	Definition of the class Window
 *
 *	Prefix: UGKCW_
 *
 *	@file UGKWindow.h
 *	@brief Class for windows depending on the platform
 *	@author Ramón Mollá
 *	@author Sergio Laguna
 *	@version 2015-11
 */

#ifndef UGKCW_CLASS_WINDOW
#define UGKCW_CLASS_WINDOW

#include <UGKOS.h>

#ifdef UGKOS_WINDOWS
#include <Graphics/Window/UGKMSWindow.h>

/** Pixel format descriptor */
typedef struct
{
	WORD  nSize;
	WORD  nVersion;
	DWORD dwFlags;
	BYTE  iPixelType;
	BYTE  cColorBits;
	BYTE  cRedBits;
	BYTE  cRedShift;
	BYTE  cGreenBits;
	BYTE  cGreenShift;
	BYTE  cBlueBits;
	BYTE  cBlueShift;
	BYTE  cAlphaBits;
	BYTE  cAlphaShift;
	BYTE  cAccumBits;
	BYTE  cAccumRedBits;
	BYTE  cAccumGreenBits;
	BYTE  cAccumBlueBits;
	BYTE  cAccumAlphaBits;
	BYTE  cDepthBits;
	BYTE  cStencilBits;
	BYTE  cAuxBuffers;
	BYTE  iLayerType;
	BYTE  bReserved;
	DWORD dwLayerMask;
	DWORD dwVisibleMask;
	DWORD dwDamageMask;
} UGKCW_PIXELFORMATDESCRIPTOR;

class UGK_API CWindow : public CMSWindow
#elif defined UGKOS_LINUX
class UGK_API CWindow : public CLinuxWindow
#elif defined UGKOS_OSX
class UGK_API CWindow : public COSXWindow
#elif defined UGKOS_ANDROID
class UGK_API CWindow : public CAndWindow
#endif	//OS type
{
public:

	CWindow()	{}	///< Constructor of the class
	~CWindow()	{}	///< Destructor of the class

#ifdef UGKOS_WINDOWS
	inline bool Init() { DeleteTitle(); return CMSWindow::Init(); }
	inline void	SetPixelFormat(PIXELFORMATDESCRIPTOR *pfd){ CMSWindow::PFD = *pfd; };
	inline bool Create(int arbMultisampleFormat, bool arbMultisampleSupported){ return CMSWindow::Create(LeftUpX, LeftUpY, Width, Height, bitsPerPixel, GetTitle(), arbMultisampleFormat, arbMultisampleSupported, Antialiasing, AntialiasingMode); }
#elif defined UGKOS_LINUX
#elif defined UGKOS_OSX
#elif defined UGKOS_ANDROID
#endif	//OS type

};

#endif	//Window class
