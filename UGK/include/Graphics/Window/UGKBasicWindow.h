/**
 *	Definition of the class Basic Window
 *
 *	Prefix: UGKCBW_
 *
 *	@file UGKBasicWindow.h
 *	@brief Base class for windows
 *	@author Ramón Mollá
 *	@author Sergio Laguna
 *	@version 2015-11
 */

#ifndef UGKCBW_CLASS_WINDOW
#define UGKCBW_CLASS_WINDOW

#include <UGKGraphicsCard.h>

/// Antialiasing types
enum { AAx2, AAx2QUINQUX, AAx4, AAx4S };

class UGK_API CBWindow
{
public:
	int				FullScreen;			///< FullScreen active
	int				quickFullScreen;	///< quickFullScreen active

	int				Visible;			///< Window Visible
	unsigned int	Lang;

	int				bitsPerPixel;		///< Bits Per Pixel

	bool			Stream;
	bool			MipMap;				///< MipMap available
	bool			Vsync;				///< Vsync available
	bool			VsyncActive;		///< Vsync active
	bool			Billboard;			///< Billboards 

	int				Width,				///< Width of the basic window
					Height,				///< Height of the basic window
					LeftUpX,			///< X Position of the left-up corner
					LeftUpY;			///< Y Position of the left-up corner
	
	UGKS_String		Title;				///< Name of the window title
	UGKS_String		Name;				///< Application ClassName
										
	// Antialiasing
	bool			Antialiasing;				///< Anti-aliasing available
	bool			Antialiasing_active;		///< Anti-aliasing active
	int				AntialiasingMode;			///< Anti-aliasing mode
	bool			AntialiasingModeOver;

	/**
	 *	@fn SetTitle
	 *	Assigns a title to the basic window
	 *	@param UGKS_String T Title to be set
	 */
	inline void	SetTitle(UGKS_String T)		{ Title = T; };
	/**
	*	@fn SetName
	*	Assigns a name to the basic window
	*	@param UGKS_String N Name to be set
	*/
	inline void	SetName(UGKS_String N)		{ Name = N; };
	/**
	*	@fn GetTitle
	*	Gets the title of the basic window
	*/
	inline UGKS_String	GetTitle()			{ return Title; }
	/**
	*	@fn GetName
	*	Gets the name of the basic window
	*/
	inline UGKS_String	GetName()			{ return Name; }
	/**
	*	@fn TitleInitialized
	*	Checks if the title of the basic window is initialized
	*/
	inline bool	TitleInitialized()			{ return Title.empty(); }
	/**
	*	@fn TitleExist
	*	Checks if the title of the basic window exists
	*/
	inline bool	TitleExist()				{ return !Title.empty(); }
	/**
	*	@fn DeleteTitle
	*	Deletes the title of the basic window
	*/
	inline void	DeleteTitle()				{ Title.clear(); }
	/**
	*	@fn DeleteTitle
	*	Deletes the name of the basic window
	*/
	inline void	DeleteName()				{ Name.clear(); }

	CBWindow()	{ Init(); }				///< Constructor of the class
	~CBWindow()	{ DeleteTitle(); }		///< Destructor of the class

	/**
	 *	@fn setWindowMetadata
	 *	Sets the metadata of a basic window
	 *	@param UGKS_String title		Title of the basic window
	 *	@param int width				Default window width
	 *	@param int height				Default window height
	 *	@param int bitsperpixel			Default bits per pixel
	 *	@param bool fullScreen			Default fullscreen
	 *	@param bool quickfullscreen		Default quick fullscreen
	 */
	void setWindowMetadata(UGKS_String title, int width, int height, int bitsperpixel, bool fullScreen, bool quickfullscreen)
	{
		SetTitle(title);
		Width	= width;					// Default Window Width (modified by startup screen)
		Height	= height;					// Default Window Height (modified by startup screen)

		bitsPerPixel	= bitsperpixel;		// Default Bits Per Pixel (modified by startup screen)
		FullScreen		= fullScreen;		// Default Fullscreen? (Set To TRUE)
		quickFullScreen = quickfullscreen;	// Default quickFullscreen? (Set To TRUE)
	}

	/**
	 *	@fn Init
	 *	Initializes the window at VGA resolution and default bits per pixel
	 */
	inline void Init() { DeleteTitle(); DeleteName(); Width = UGKCGC_VGA_HOR_RES; Height = UGKCGC_VGA_VER_RES; bitsPerPixel = UGKCGC_DEFAULT_DEPTH; }
};

#endif	//Window class
