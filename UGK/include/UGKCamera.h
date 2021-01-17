/*	Definition of the class Camera
*
*	Prefix: UGKCC_
*
*	@author Ramon Molla
*	@version 2016-07
*	modified: 2015-2016 by Lorenzo Quiros D.
*	last modified: 04-2017 by Clara Luzón & Zayda Ferrer
*	Specification for Stero R. Mollá 06-2016
*/

#ifndef UGKCC_CAMERA //Removes camera macro
#define UGKCC_CAMERA //Defines camera macro
#include<iostream>
#include <UGKSceneGraph.h>
#include <UGKLog.h>
#include <QuadtreeRoot.h>
#include <glut.h>
#ifdef UGKSG_OGRE
#elif defined (UGKSG_UDK)
#elif defined (UGKSG_CRY)
#elif defined (UGKSG_IRL)
#elif defined (UGKSG_TORQUE)
#elif defined (UGKSG_OSG)
#include <osg/Camera>
#include <osgGA/FirstPersonManipulator>

#define UGKInternalCamera	osg::Camera

#endif

namespace UGK
{
#define UGKCC_NO_FOCUS -1.0
/**
How the view is going to be projected onto the window
*/
typedef enum {
	UGKCC_ORTHOGRAPHIC,
	UGKCC_ORTHOGRAPHIC_2D,
	UGKCC_PERSPECTIVE,
	UGKCC_STEREOSCOPIC,		///< Stereo cámera. By default it is perspective
	UGKCC_MAX_CAMERA_TYPE
} UGKCC_CAMERA_TYPE;

/**
How the focus is performed by the camera
*/
typedef enum {
	UGKCC_IN_FRONT_FOCUS,	///< Both cameras have their focus points directly in front of them
	UGKCC_ROTATION_FOCUS,	///< Achieves the stereoscopic effect by rotating the left and right views so that their focus points coincide at the distance from the eyes where the lines of sight for each eye converge(known as fusion distance).
	UGKCC_SHEAR_FOCUS,		///< The orientation of both views remains the same, but each eye's view is sheared along the Z axis so that the two frustums converge at the fusion distance.
	UGKCC_MAX_FOCUS
} UGKCC_FOCUS_METHODS;

/**
Which of the eyes is moved from the camera main position
*/
typedef enum {
	UGKCC_SHIFT_BOTH,	///< Both virtual cameras will be shifted in opposite directions at a distance equal to half of the eye distance.
	UGKCC_SHIFT_LEFT,	///< The virtual cameras are shifted to the left so that the right camera takes the position of the original camera.The left camera is shifted to the left at a distance equal to the eye distance.
	UGKCC_SHIFT_RIGHT,	///< The virtual cameras are shifted to the right so that the left camera takes the position of the original camera.The right camera is shifted to the right at a distance equal to the eye distance.
	UGKCC_MAX_SHIFT
} UGKCC_OCULUS_SHIFT;

/**
Which of the eyes is projected on the window
*/
typedef enum {
	UGKCC_BOTH_EYE,		///< Both virtual cameras will be projected on the screen.
	UGKCC_LEFT_EYE,		///< Only the left view will be rendered.
	UGKCC_RIGHT_EYE,	///< Only the right view will be rendered.
	UGKCC_MAX_EYES_MODES
} UGKCC_EYES_SELECTION;


/**
Which of the eyes is projected on the window
*/
typedef enum {
	UGKCC_LEFT_RIGHT,	///< Side - by - Side – Arranges the rendered images for each eye side by side. Left eye on the left half screen and right eye on the right half screen
	UGKCC_TOP_DOWN,		///< Top - Bottom Arranges the rendered images for each eye one on top of another
	UGKCC_TIME_MUX,		///< Time multiplexed. Using a 120Hz display, odd frames correspond to left frames and even frames correspond to right or viceversa depending on "EyesFlipped" attribute value
	UGKCC_INTERLACED,	///< Space multiplexed. Odd lines on the same screen correspond to left frames and even lines correspond to right or viceversa depending on "EyesFlipped" attribute value
	UGKCC_ANAGLYPH,		///< Anaglyph (red-blue) overlapping images
	UGKCC_MAX_LAYOUTS_MODES
} STEREO_LAYOUT;

	/**
	Class is defined CCamera also derive or inherit from class CCharacter
	*/
	class UGK_API CCamera : public CCharacter
	{
		//Attributes
	#ifdef UGKSG_OGRE
	#elif defined (UGKSG_UDK)
	#elif defined (UGKSG_CRY)
	#elif defined (UGKSG_IRL)
	#elif defined (UGKSG_TORQUE)
	#elif defined (UGKSG_OSG)
		UGKInternalCamera	*Camera;
	#endif
		
		UGKSG_SceneViewer	*SceneViewer;

	public:

		int winID;  ///<Camera Window ID where the camera paints its frame

		//Legacy. Must pass to Space Invaders Camera object
		GLfloat zoom,				///<ZOOM
				zoom_total,			///<Camera Camera.zoom
				zoom_total_bonus;	///<ZOOM TOTAL while passing to 3D mode


		Vector	PointsTo,			///<Objective point of the camera
				Rotation,			///<Angle.	Up vector orientation
				Up,					///<Vertical vector
				*ControlPoints;		///<Bezier Curve control Points

	//Post process effects
		GLfloat	FocusDistance; ///<When enabled, allows a point of focus to be defined. It is corelated to the depth of view postporcess effects
		UGKCC_FOCUS_METHODS FocusMethod;	///< Specifies the focus method for the two views

		//Stereoscopic camera attributes
		GLfloat					EyeDistance;	///< Specifies the eye distance for which the stereoscopic image will be rendered
		UGKCC_OCULUS_SHIFT		OculusShift;	///< Specifies how the two virtual cameras will be placed in relation to the camera position attribute in the scene
		UGKCC_EYES_SELECTION	EyeSelected;	///< Specifies which of the stereoscopic views will be rendered
		STEREO_LAYOUT			StereoLayout;	///< Specifies the format in which the Stereoscopic renders are output
		bool					EyesFlipped;	///< Change right view to left one and viceversa

		//Methods
		void Init(void);

		inline CCamera() { Init(); }	///<Constructor of the class

		inline void SetLook(); ///<Overwrite LookAt where the camera is called
		inline void SetType(UGKCC_CAMERA_TYPE type); ///<Set camera type
		/**
		* @fn CCamera::SetWindow
		* Define function to set camera Window, ie window were camera image is going to be projected
		* @param windowID: Window identifier
		*/
		inline void SetWindow(int windowID){winID = windowID;}

		void SetUpPerspective(GLfloat x, GLfloat y, GLfloat fovy, GLfloat width, GLfloat heigh, GLfloat zNear, GLfloat zFar);	///<Set-Up Perspective camera projection matrix
		void SetUpOrtho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);	///<Set-Up Orthographic camera projection matrix
		void SetUpOrtho2D(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);	///<Set-Up 2D Orthographic camera projection matrix
		void setupStereoscopic( GLfloat fovy,  GLfloat width, GLfloat height, GLfloat nearz, GLfloat farz, GLfloat screenz, GLfloat depthz, void funcA());///< Set-Up Stereoscopic camera 
		void LookAt(float x, float y, float z, float lx, float ly, float lz, float ux, float uy, float uz);
		void LookAt(float x, float y, float z);
		void LookFrom(float x, float y, float z);
		void RestoreProjection();
		void SetBezierControlPoints(Vector *p);	///<Define Bezier curve Control Points
		inline void SetSceneViewer(UGKSG_SceneViewer	*SV)
		{
			SceneViewer = SV;
			#ifdef UGKSG_OGRE
			#elif defined (UGKSG_UDK)
			#elif defined (UGKSG_CRY)
			#elif defined (UGKSG_IRL)
			#elif defined (UGKSG_TORQUE)
			#elif defined (UGKSG_OSG)
				Camera = SceneViewer->getCamera();
			#else
			#endif
		}

		//Getters
		inline UGKSG_SceneViewer	*GetSceneViewer() { return SceneViewer; }
		Vector *GetBezierControlPoints();	///<Return Currently defined Bezier Curve Control Points
		Vector GetBezierPosition(int n, UGKALG_NUMERIC_TYPE mu); ///<Return camera position, based on pre-defined control_points

		/// Updates the camera settings when the Window is reshaped or moved
		void Reshape(float Z);

		inline void setPerspectiveProj(double fov, double aspectRatio, double _near, double _far)
		{
		#ifdef UGKSG_OGRE
		#elif defined (UGKSG_UDK)
		#elif defined (UGKSG_CRY)
		#elif defined (UGKSG_IRL)
		#elif defined (UGKSG_TORQUE)
		#elif defined (UGKSG_OSG)
			Camera->setProjectionMatrixAsPerspective(fov, aspectRatio, _near, _far);
		#else
		#endif
		}
		inline void setOrthoProj(double left, double right, double bottom, double top, double _near, double _far)
		{
		#ifdef UGKSG_OGRE
		#elif defined (UGKSG_UDK)
		#elif defined (UGKSG_CRY)
		#elif defined (UGKSG_IRL)
		#elif defined (UGKSG_TORQUE)
		#elif defined (UGKSG_OSG)
			Camera->setProjectionMatrixAsOrtho(left, right, bottom, top, _near, _far);
		#else
		#endif
		}
		
	};
	

}
#endif
