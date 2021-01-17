/**
*
*	Camera Manager class declarations
*
*	Prefix: UGKC
*	@author Lorenzo Quiros D.
*	@version 2015-2016
*
*/

#include <list>
#include <glut.h>
#include <UGKCameraManager.h>
#include<iostream>
#define CC_OGL
//#define CC_DX

#ifdef	CC_OGL
#elif	defined CC_DX
#endif


using namespace UGK;

/**
* @fn UGKCCameraManager::InitWindow
* Define function to create Main window
* @param argc, argv: main program inputs
* @param w: Window Width
* @param h: Window height
* @param postX: Initial window position on X axes
* @param postY: Initial window position on Y axes
* @param name: Window name (label)
*/
int UGKCCameraManager::InitWindow(int argc, char **argv, int w, int h, int postX, int postY, const char* name) {
	int newWindowID2 = 1;
#ifdef	CC_OGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA| GLUT_STENCIL);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO);
	glutInitWindowPosition(postX, postY);
	glutInitWindowSize(w, h);
	newWindowID2 = glutCreateWindow(name);

#elif defined CC_DX
#endif
	return newWindowID2;
}

/**
* @fn UGKCCameraManager::AddWindow
* Add new window to a parent window (ie a sub-window)
* @param parent: Parent window ID
* @param borderX: distance between subWindows in X border
* @param borderY: distance between subWindows in Y border
* @param w: Window width
* @param h: Window height
*/
int UGKCCameraManager::AddWindow(int parent, int borderX, int borderY, int w, int h)
{
	int newSubWindowID;
#ifdef	CC_OGL
	newSubWindowID = glutCreateSubWindow(parent, borderX, borderY, w, h);
	CCamera* newCamera = new CCamera();
	newCamera->SetType(UGKCC_PERSPECTIVE);
	newCamera->SetWindow(newSubWindowID);
	_AllCameras.insert(_AllCameras.begin(), *newCamera);
#elif	defined CC_DX
#endif
	return newSubWindowID;
}

/**
* @fn UGKCCameraManager::SetWindow
* Define function to set current program scope to specific window
* @param windowID: Window identifier
*/
void UGKCCameraManager::SetWindow(int windowID)
{
#ifdef CC_OGL
	glutSetWindow(windowID);
#elif defined CC_DX
#endif
}

/**
* @fn UGKCCameraManager::GetCamera
* Define function to return camera associated to specific window
* @param windowID: Window identifier
*/
CCamera UGKCCameraManager::GetCamera(int windowID)
{
	std::list<CCamera>::iterator it;

	for (it = _AllCameras.begin(); it != _AllCameras.end(); it++)
	{
		if (it->winID == windowID) {
			return *it;
		}
	}
	//--- Error must be handled here if no winID match windowID..
	return *it;
}
