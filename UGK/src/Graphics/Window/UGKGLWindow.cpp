/**
 *	Definition of the class GL Window
 *
 *	Prefix: UGKCGLW_
 *
 *	@author Ramón Mollá
 *	@author Sergio Laguna
 *	@version 2015-11
 */

#include <Graphics/Window/UGKGLWindow.h>
#include <GL.h>
#include <GLUT.h>
#include <glext.h>
#include <wglext.h>
#include <UGKglError.h>
#include <cstdio>


CGLWindow::~CGLWindow(void)
{
}

/**
* @fn CGLWindow::Create()
* This function creates a OpenGL window
*/
bool CGLWindow::Create()
{
	bool Result = CWindow::Create(arbMultisampleFormat, arbMultisampleSupported);
	// For text in loading screen
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_FASTEST);
	glDrawBuffer(GL_BACK);	//By default, always draw on back buffer only
	return Result;
}

/**
* @fn CGLWindow::Reshape()
* This function changes the shape of the window when you move or resize
* Depending on the Apect ratio of the window
* @param float fov: representation of the Apect Ratio of the window
*/
void CGLWindow::Reshape(float fov)			/// Reshape The Window When It's Moved Or Resized
{
	glViewport(0, 0, (GLsizei)(Width), (GLsizei)(Height));				// Reset The Current Viewport
	CGL_ResetProjection();
	gluPerspective(fov, (GLfloat)(Width) / (GLfloat)(Height),			// Calculate The Aspect Ratio Of The Window
		0.1f, 500.0f);

	CGL_ResetModelView();
}

/**
* @fn Refresh
* This function refresh the window
*/
void CGLWindow::Refresh(void)	/// glFlush and swapbuffers
{
	glFlush();				// Flush The GL Rendering Pipeline
	glFinish();				// Obligues to finish all the rendering commands before doing the buffers swap
	SwapBuffers(hDC);
}


#ifdef	UGKOS_WINDOWS
/**
* @fn CGLWindow::InitMultisample
* Used To Query The Multisample Frequencies
*/
bool CGLWindow::InitMultiSample(int AntialiasingMode)
{

	bool arbMultisampleSupported = false;
	char * Ext = NULL;

	// See If The String Exists In WGL!
	if (!WGLExtensionSupported(Ext))
	{
		arbMultisampleSupported = false;
		return false;
	}

	// Get Our Pixel Format
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if (NULL == wglChoosePixelFormatARB)
	{
		arbMultisampleSupported = false;
		return false;
	}

	// Get Our Current Device Context
	HDC hDC = GetDC(hWnd);

	int		pixelFormat;
	int		valid;
	UINT	numFormats;
	float	fAttributes[] = { 0, 0 };

	// These Attributes Are The Bits We Want To Test For In Our Sample
	// Everything Is Pretty Standard, The Only One We Want To 
	// Really Focus On Is The SAMPLE BUFFERS ARB And WGL SAMPLES
	// These Two Are Going To Do The Main Testing For Whether Or Not
	// We Support Multisampling On This Hardware.
	int iAttributes[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 32,	//24, 32 work
		WGL_ALPHA_BITS_ARB, 8,	//8
		WGL_DEPTH_BITS_ARB, 16,	//8, 16 work
		WGL_STENCIL_BITS_ARB, 0,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		UGKCMSW_SAMPLE_BUFFERS_ARB, GL_TRUE,
		UGKCMSW_SAMPLES_ARB, 4,
		0, 0
	};

	// samples
	if (AAx2 == AntialiasingMode || AAx2QUINQUX == AntialiasingMode)
		iAttributes[19] = 2;
	else if (AAx4 == AntialiasingMode || AAx4S == AntialiasingMode)
		iAttributes[19] = 4;

	// First We Check To See If We Can Get A Pixel Format For 4 Samples
	valid = wglChoosePixelFormatARB(hDC, iAttributes, fAttributes, 1, &pixelFormat, &numFormats);

	// If We Returned True, And Our Format Count Is Greater Than 1
	if (valid && numFormats >= 1)
	{
		arbMultisampleSupported = true;
		int arbMultisampleFormat = pixelFormat;
		//		Log.Add("Anti-aliasing")
		//		add_log("blblbl", false);
		return arbMultisampleSupported;
	}

	// Our Pixel Format With 4 Samples Failed, Test For 2 Samples
	iAttributes[19] = 2;
	valid = wglChoosePixelFormatARB(hDC, iAttributes, fAttributes, 1, &pixelFormat, &numFormats);
	if (valid && numFormats >= 1)
	{
		arbMultisampleSupported = true;
		int arbMultisampleFormat = pixelFormat;
		return arbMultisampleSupported;
	}

	// Return The Valid Format
	return  arbMultisampleSupported;
}
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif


bool CGLWindow::SetRenderingContext()
{
	bool Result;
	// Make The Rendering Context Our Current Rendering Context
	UGKGLE_glResetError();
	Result = wglMakeCurrent(hDC, hRC);
	UGK::UGKGLE_glError();

	return Result;
}

bool CGLWindow::WGLExtensionSupported(const UGKS_String extension)
{
	char *supported = NULL;

#ifdef UGKOS_WINDOWS
	// Try To Use wglGetExtensionStringARB On Current DC, If Possible
	PROC wglGetExtString = wglGetProcAddress("wglGetExtensionsStringARB");

	if (wglGetExtString)
		supported = ((char*(__stdcall*)(HDC))wglGetExtString)(wglGetCurrentDC());

	// If that failed, try standard Opengl extensions string
	if (supported == NULL)
		supported = (char*)glGetString(GL_EXTENSIONS);

#elif	defined UGKOS_LINUX
#elif	defined UGKOS_OSX
#elif	defined UGKOS_ANDROID
#endif

	UGKS_String Supported = supported;
	return -1 != Supported.find(extension);
}

void CGLWindow::Init()
{
	arbMultisampleSupported = false;	// Extension "arbMultisample" unavailable
	arbMultisampleFormat = 0;			// Pixel format used if the extension is available

	// Devices Input
	DevOption = 0;						// Devices Option
}