/**	
 *	Definition of the class Micro Soft Window
 *
 *	Prefix: UGKCMSW_
 *
 *	@author Ramón Mollá
 *	@author Sergio Laguna
 *	@version 2015-11
 */

#include <UGKMSWindow.h>
#include <cstdio>
#include <commctrl.h>		// Header File For Windows XP Common Controls
#include <UGKLog.h>
#include <atlstr.h>

//Internal temporary varaibles
#define MAX_LOADSTRING 100

TCHAR AppTitle[MAX_LOADSTRING];			// Main bar title for the Window
TCHAR AppWindowClass[MAX_LOADSTRING];	// Name of the main window class

CMSWindow::~CMSWindow(void)
{
}

bool CMSWindow::SetRenderingContext(){ return wglMakeCurrent(hDC, hRC); }

bool CMSWindow::GetRenderingContext()
{
	hRC = wglGetCurrentContext();		// Gets the current context

	if (NULL == hRC)
	{
		int pixelFormat = ChoosePixelFormat(hDC, &PFD);
		// If ChoosePixelFormat() fails, returns an error message
		if (0 == pixelFormat)
		{
			MessageBox(hWnd, LPCWSTR("ChoosePixelFormat() failed"), LPCWSTR("Error"), MB_ICONERROR | MB_OK);
			exit(UGK_CHOOSE_PIXEL_FORMAT_ERROR);
		}

		if (!SetPixelFormat(hDC, pixelFormat, &PFD))
		{
			// If ChoosePixelFormat() fails, returns an error message
			MessageBox(hWnd, LPCWSTR("SetPixelFormat() failed"), LPCWSTR("Error"), MB_ICONERROR | MB_OK);
			exit(UGK_SET_PIXEL_FORMAT_ERROR);
		}

		hRC = wglCreateContext(hDC);		// Try To Get A Rendering Context

		if (!hRC)							// If wglCreateContext() fails, returns an error message
			MessageBox(hWnd, LPCWSTR("wglCreateContext() failed"), LPCWSTR("Error"), MB_ICONERROR | MB_OK);

		if (!wglMakeCurrent(hDC, hRC))		// If wglMakeCurrent() fails, returns an error message
			MessageBox(hWnd, LPCWSTR("wglMakeCurrent() failed"), LPCWSTR("Error"), MB_ICONERROR | MB_OK);
	}

	DWORD Error = GetLastError();

	return NULL != hRC;					// Did We Get A Rendering Context?
}

bool CMSWindow::Destroy()
{
	if (hWnd != NULL)								// If the Window has a handle
	{
		if (hDC != NULL)							// if the Window has a device context
		{
			wglMakeCurrent(hDC, 0);					// Set The Current Active Rendering Context To Zero
			if (hRC != NULL)						// if The Window Have A Rendering Context
			{
				wglDeleteContext(hRC);				// Release The Rendering Context
				hRC = 0;							// Zero The Rendering Context
			}
			ReleaseDC(hWnd, hDC);					// Release The Device Context
			hDC = 0;								// Zero The Device Context
		}
		DestroyWindow(hWnd);						// Destroy The Window
		hWnd = 0;									// Zero The Window Handle
	}

	if (FullScreen)									// If the Window is in fullscreen mode
	{
		ChangeDisplaySettings(NULL, 0);				// Switch Back To Desktop Resolution
		ShowCursor(TRUE);							// Show The Cursor
	}
	return TRUE;
}


bool CMSWindow::Init()
{

	ZeroMemory(this, sizeof(CMSWindow));
	FullScreen = false;
	quickFullScreen = false;

	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),		// Size Of This Pixel Format Descriptor
		1,									// Version Number
		PFD_DRAW_TO_WINDOW |				// Format Must Support Window
		PFD_SUPPORT_OPENGL |				// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,					// Must Support Double Buffering
		PFD_TYPE_RGBA,						// Request An RGBA Format
		bitsPerPixel,						// Select Our Color Depth
		0, 0, 0, 0, 0, 0,					// Color Bits Ignored
		0,									// No Alpha Buffer
		0,									// Shift Bit Ignored
		0,									// No Accumulation Buffer
		0, 0, 0, 0,							// Accumulation Bits Ignored
		UGKCGC_DEFAULT_DEPTH,				// 24Bit Z-Buffer (Depth Buffer)  
		0,									// No Stencil Buffer
		0,									// No Auxiliary Buffer
		PFD_MAIN_PLANE,						// Main Drawing Layer
		0,									// Reserved
		0, 0, 0								// Layer Masks Ignored
	};

	PFD = pfd;

	return true;
}


/**
 *	@fn InitInstance
 *	Saves the instance ID and creates and shows the main window
 */
BOOL CMSWindow::InitInstance()
{
	RECT	windowRect = { 0, 0, Width, Height };			// Define Our Window Coordinates
	DWORD	windowStyle = WS_OVERLAPPEDWINDOW;				// Define Our Window Style
	DWORD	windowExtendedStyle = WS_EX_APPWINDOW;			// Define The Window's Extended Style
	CString NameAux, TitleAux;
	UGKS_String	tempString;

	// Quick fullscreen mode
	if (quickFullScreen)
	{
		ShowCursor(TRUE);									// Turn Off The Cursor
		windowStyle = WS_POPUP;								// Set The WindowStyle To WS_POPUP (Popup Window)
		windowExtendedStyle |= WS_EX_TOPMOST;				// Set The Extended Window Style To WS_EX_TOPMOST
	}														// (Top Window Covering Everything Else)
	// Fullscreen mode
	else if (FullScreen)									// Fullscreen Requested, Try Changing Video Modes
	{
		SetFullScreen();
		ShowCursor(TRUE);									// Turn On The Cursor
		windowStyle = WS_POPUP;								// Set The WindowStyle To WS_POPUP (Popup Window)
		windowExtendedStyle |= WS_EX_TOPMOST;				// Set The Extended Window Style To WS_EX_TOPMOST
	}
	// Window mode
	else													// If Fullscreen Was Not Selected
		AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExtendedStyle); // Adjust Window, Account For Window Borders

	NameAux = UGKS_string2CString(GetName());
	TitleAux = UGKS_string2CString(GetTitle());

	hWnd = CreateWindowEx(windowExtendedStyle,		// Extended Style
		NameAux,									// Class Name
		TitleAux,									// Window Title
		windowStyle,								// Window Style
		LeftUpX, LeftUpY,							// Window X,Y Position
		windowRect.right - windowRect.left,			// Window Width
		windowRect.bottom - windowRect.top,			// Window Height
		HWND_DESKTOP,								// Desktop Is Window's Parent
		0,											// No Menu
		hInstance,									// Pass The Window Instance
		NULL);

	if (!hWnd)
	{
		LPWSTR pMessage = L"%1!*.*s! %4 %5!*s!";
		DWORD_PTR pArgs[] = { (DWORD_PTR)4, (DWORD_PTR)2, (DWORD_PTR)L"Bill",  // %1!*.*s! refers back to the first insertion string in pMessage
			(DWORD_PTR)L"Bob",                                                // %4 refers back to the second insertion string in pMessage
			(DWORD_PTR)6, (DWORD_PTR)L"Bill" };                               // %5!*s! refers back to the third insertion string in pMessage
		const DWORD size = 100 + 1;
		WCHAR buffer[size];

		if (!FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
			NULL,
			0,
			0,
			buffer,
			size,
			(va_list*)NULL))
		{
			wprintf(L"Format message failed with 0x%x\n", GetLastError());
			return FALSE;
		}

		// Buffer contains "  Bi Bob   Bill".
		wprintf(L"Formatted message: %s\n", buffer);
		return FALSE;
	}

	return TRUE;
}

bool CMSWindow::Create(int LeftUpX, int LeftUpY, int Width, int Height, int bitsPerPixel, UGKS_String title, int arbMultisampleFormat, bool arbMultisampleSupported, bool Antialiasing, int AntialiasingMode)
{
	// Initializing global strings
	LoadString(hInstance, IdTitle, AppTitle, MAX_LOADSTRING);
	LoadString(hInstance, IdApp, AppWindowClass, MAX_LOADSTRING);
	Register();

	// Realizar la inicialización de la aplicación:
	if (!InitInstance())
		return FALSE;

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IdApp));

	// Initialize Common Controls
	INITCOMMONCONTROLSEX icex;					// Initialize Windows Common Controls

	// Load the ToolTip class from the DLL
	icex.dwSize = sizeof(icex);
	icex.dwICC = ICC_BAR_CLASSES;				// For Tooltips

	if (!InitCommonControlsEx(&icex))
		BOX(LPCWSTR("InitCommonControlEx() failed."));

	CreateRenderingContext();
	if (!IsDeviceContextOK() || !IsRenderingContextOK())
	{
		Destroy();
		return FALSE;
	}

	Visible = TRUE;						// Set Visible To True

	return TRUE;						// Window Creating Was A Success
}

void CMSWindow::SetFullScreen()
{
	// fullscreen
	DWORD windowStyle = WS_POPUP;				// Set The WindowStyle To WS_POPUP (Popup Window)
	DWORD windowExtendedStyle = WS_EX_TOPMOST;	// Set The Extended Window Style To WS_EX_TOPMOST

	// change style
	DWORD dwStyle, dwNewStyle;

	dwStyle = GetWindowLong(hWnd, (TRUE ? GWL_EXSTYLE : GWL_STYLE));

	dwNewStyle = (dwStyle & (~NULL)) | windowExtendedStyle;

	SetWindowLong(hWnd, (TRUE ? GWL_EXSTYLE : GWL_STYLE), dwNewStyle);

	SetWindowPos(hWnd, NULL, 0, 0, DeskTop->Width, DeskTop->Height, SWP_NOZORDER);
}

void CMSWindow::CreateRenderingContext()
{
	// No DC is available for this hWnd, so create a new one
	if (GetDeviceContext())
		// In case the DC is new, so a new RC has to be created ans associated to it 
		if (GetRenderingContext())
			if (!SetRenderingContext())	// Get the one associated to this OpenGL Window
			{
				LPVOID lpMsgBuf;
				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
				//MessageBox(NULL, "Current window context lost. No way to device context.", "Error", MB_OK | MB_ICONINFORMATION);
				LocalFree(lpMsgBuf);

				OutputDebugString(LPCWSTR("Failed in CreateRenderingContext()"));
			}
}

bool CMSWindow::GetDeviceContext()
{
	hDC = wglGetCurrentDC();
	if (NULL == hDC)
		// Get a Device Context for this Window
		hDC = GetDC(hWnd);				// Grab A Device Context

	return NULL != hDC;					// Did We Get A Device Context?
}

/// Register A Window Class
bool CMSWindow::Register()
{
	CString NameAux = UGKS_string2CString(GetName());

	WNDCLASSEX windowClass;												// Window Class
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));						// Make Sure Memory Is Cleared

	windowClass.cbSize			= sizeof(WNDCLASSEX);					// Size Of The windowClass Structure
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraws The Window For Any Movement / Resizing
	windowClass.lpfnWndProc		= WndProc;								// WindowProc Handles Messages
	windowClass.hInstance		= hInstance;							// Set The Instance
	windowClass.hbrBackground	= static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));// Class Background Brush Color
	//windowClass.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	windowClass.hCursor			= LoadCursor(hInstance, IDC_ARROW);		// Load The Arrow Pointer
	windowClass.lpszClassName	= NameAux;								// Sets The Applications Classname
	windowClass.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IdApp));
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.lpszMenuName	= MAKEINTRESOURCE(IdApp);
	windowClass.hIconSm			= LoadIcon(windowClass.hInstance, MAKEINTRESOURCE(IdIcon));

	if (0 == RegisterClassEx(&windowClass))								// Did Registering The Class Fail?
	{
		// NOTE: Failure, Should Never Happen
		MessageBox(HWND_DESKTOP, LPCWSTR("RegisterClassEx Failed!"), LPCWSTR("Error"), MB_OK | MB_ICONEXCLAMATION);
		return false;													// Return False (Failure)
	}

	return true;														// Return True (Success)
}