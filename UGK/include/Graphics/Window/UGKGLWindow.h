/**
 *	Definition of the class GL Window
 *
 *	Prefix: UGKCGLW_
 *
 *	@file UGKGLWindow.h
 *	@brief Class for windows using OpenGL
 *	@author Ramón Mollá
 *	@author Sergio Laguna
 *	@version 2015-11
 */

#ifndef UGKCGLW_GLWINDOW
#define UGKCGLW_GLWINDOW

#include <UGKWindow.h>

#define CGL_SAMPLE_BUFFERS_ARB	0x2041      ///< Define a buffer size
#define CGL_SAMPLES_ARB			0x2042      ///< Define a sample size

#define UGKCGLW_NO_HWND			NULL
#define UGKCGLW_NO_HDC			NULL
#define UGKCGLW_NO_HRC			NULL

#define CGL_ResetModelView() 	{glMatrixMode(GL_MODELVIEW);glLoadIdentity();}
#define CGL_ResetProjection() 	{glMatrixMode(GL_PROJECTION);glLoadIdentity();}

/**
 * It defines the class Window (Screen)
 * Where is the constructor, destructor and refresh the screen
 * In addition to the configuration of the screen as well as the resolution and the size of the screen
 */
class UGK_API CGLWindow : public CWindow
{

public:
	// ARB-MULTISAMPLE Anti-aliasing (OpenGL extension)
	bool				arbMultisampleSupported;	///< Extension "arbMultisample" available
	int					arbMultisampleFormat;		///< Pixel format used if the extension is available

	//Devices Input
	int					DevOption;					///< Devices Option

	void Init(void);

	CGLWindow()			{ Init(); }					///< Constructor of the class
	~CGLWindow(void);								///< Destructor of the class

	bool Create();									///< Creates a OpenGL Window
	void Refresh(void);								///< glFlush and swapbuffers

	bool SetRenderingContext();

	bool WGLExtensionSupported(const UGKS_String extension);

#ifdef	UGKOS_WINDOWS
	bool InitMultiSample(int AntialiasingMode);
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

	void Reshape(float);				///< Updates the Window settings when it is resahaped or moved
};
#endif