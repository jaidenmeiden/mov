/**
*
*	Camera Manager class header
*
*	Prefix: UGKC
*	@author Lorenzo Quiros D.
*	@version 2015-2016
*
*/


#ifndef UGK_CAMERAMNG
#define UGK_CAMERAMNG

#include <list>
#include <UGKCamera.h>

namespace UGK
{
	class UGKCCameraManager : public CCharacter
	{
	public:
		//Constructor of the class
		UGKCCameraManager() {};

		int InitWindow(int argc, char **argv, int w, int h, int postX, int postY, const char* name); ///<Build new Window

		int AddWindow(int parent, int borderX, int borderY, int w, int h); ///<Add new subWindow to "parent" window
		void SetWindow(int windowID); ///<Set Window as current window to draw objects.
		//void setupStereoscopic(int windowID, UGKCC_FOCUS_METHODS FocusMethod, UGKCC_OCULUS_SHIFT shift, UGKCC_EYES_SELECTION eyes, STEREO_LAYOUT type, bool eyesflipped, GLfloat fovy, GLfloat EyeDistance, GLfloat width, GLfloat height, GLfloat nearz, GLfloat farz, GLfloat screenz, GLfloat depthz, void());
		
		CCamera GetCamera(int windowID); ///<Return camera associated to the windowID
	private:
		std::list<CCamera> _AllCameras; ///<A list to store all cameras
	};
}

#endif