/**
 *	Definition of the class Direct X Window
 *
 *	Prefix: UGKCDXW_
 *
 *	@file UGKDXWindow.h
 *	@brief Class for windows using DirectX
 *	@author Ramón Mollá
 *	@author Sergio Laguna
 *	@version 2015-11
 */

#ifndef UGKCDXW_GLWINDOW 
#define UGKCDXW_GLWINDOW

#include <Graphics/Window/UGKWindow.h>

/**
 * It defines the class Window (Screen)
 * Where is the constructor, destructor and refresh the screen
 * In addition to the configuration of the screen as well as the resolution and the size of the screen
 */
class UGK_API CDXWindow : public CWindow
{
public:
	//Devices Input
	int				DevOption;		///< Devices Option

	void Init(void);

	CDXWindow()		{ Init(); }		///< Constructor of the class
	~CDXWindow(void);				///< Destructor of the class

	bool Create();					///< Creates a DirectX Window
	void Refresh(void);				///< glFlush and swapbuffers

	bool InitMultiSample(int AntialiasingMode);

	void Reshape(float);			///< Updates the Window settings when it is resahaped or moved
};
#endif