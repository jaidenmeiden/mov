/**	
 *	Definition of the class MicroSoft Window
 *
 *	Prefix: UGKCMSW_
 *
 *	@file UGKMSWindow.h
 *	@brief Class for windows in MS platforms
 *	@author Ramón Mollá
 *	@author Sergio Laguna
 *	@version 2015-11
 */

#ifndef UGKCMSW_WIN
#define UGKCMSW_WIN
#include <UGKBasicWindow.h>

#define UGKCMSW_NO_HWND NULL
#define UGKCMSW_NO_HDC  NULL
#define UGKCMSW_NO_HRC  NULL

#define UGKCMSW_OGL
//#define UGKCMSW_DX

#ifdef UGKCMSW_OGL
#define UGKCMSW_SAMPLE_BUFFERS_ARB	 0x2041      ///< Define the buffer size
#define UGKCMSW_SAMPLES_ARB			 0x2042      ///< Define a sample size
#elif defined UGKCMSW_DX
#endif

class UGK_API CMSWindow : public CBWindow
{
	bool	Register();
	BOOL	InitInstance();

	int		IdApp,
			IdIcon,
			IdTitle;		// For MS Windows internal management purposes only
	WNDPROC	WndProc;		// Call back to manage the window
	int		CmdShow;		// For initialization purposes
	HACCEL	hAccelTable;	// Acceleration Table handle
	CDeskTop *DeskTop;		// Desktop reference

public:

	UGKCGC_WINDOW_HANDLE			hWnd;	///< Window Handle
	UGKCGC_DEVICE_CONTEXT_HANDLE	hDC;	///< Device Context
	HGLRC							hRC;	///< Rendering Context
	UGKCGC_PIXEL_FORMAT				PFD;

	//Application attributes
	HINSTANCE		hInstance;				///< Application Instance

	bool Init();							///< Initializes the MS window

	CMSWindow()		{ Init(); };			///< Constructor of the class
	~CMSWindow(void);						///< Destructor of the class

	inline bool IsDeviceContextOK()		{ return NULL != hDC; };
	inline bool IsRenderingContextOK()	{ return NULL != hRC; };

	/**
	* @fn bool CGLWindow::IsCreated()
	* This function verifies if the OpenGL window is created
	*/
	inline bool IsCreated() { return NULL != hWnd; }

	bool		Destroy();
	bool		Create(int LeftUpX, int LeftUpY, int Width, int Height, int bitsPerPixel, UGKS_String title, int arbMultisampleFormat, bool arbMultisampleSupported, bool Antialiasing, int AntialiasingMode);
	inline void Show()								{ ShowWindow(hWnd, CmdShow); UpdateWindow(hWnd); }

	inline void	SetId(int App, int Icon, int Title)	{ IdApp = App; IdIcon = Icon;	IdTitle = Title; }
	inline void SetWndProc(WNDPROC Proc)			{ WndProc = Proc; }
	inline void SetCmdShow(int CommandShow)			{ CmdShow = CommandShow; }
	inline void SetDeskTop(CDeskTop *DT)			{ DeskTop = DT; }
	inline int	TranslateAcc(MSG *msg)				{ return TranslateAccelerator(msg->hwnd, hAccelTable, msg); }

	void		SetFullScreen();
	void		CreateRenderingContext();
	bool		GetDeviceContext();
	bool		SetRenderingContext();
	bool		GetRenderingContext();		///< Determines if the GL context is available and gets it if possible
};

#endif