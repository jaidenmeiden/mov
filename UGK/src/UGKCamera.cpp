/**
*
*	Camera class declarations
*
*	Prefix: CC_
*	@author Ramon Molla
*	@version 2007-09-11
*
*	Modified: 2015-2016 by Lorenzo Quiros D.
*	Last modified: 04-2017 by Clara Luzón & Zayda Ferrer
*/

#include <UGKCamera.h>

#define CC_OGL
//#define CC_DX

//Template to use everywhere needed a discrimination depending on a OpenGL o DX implementation
#ifdef	CC_OGL
#elif	defined CC_DX
#endif

using namespace UGK;

/**
* @fn CCamera:: Init
* Constructor for the object CCamera
*/
void CCamera::Init(void)
{
	RenderMode = CHAR_NO_RENDER;
	PhysicMode = UGKPHY_PHANTOM;		//No render, No touchable. No AABB initialization is required

	zoom = zoom_total = zoom_total_bonus = 0; //Variables zoom, zoom_total, zoom_total_bonus initialized to zero
	SubType = UGKCC_PERSPECTIVE; // Camera Type initialized to Perspective camera by default.
	winID = -1;
	Position.Set(0.0, 0.5, 0.0);
	Up.Set(0.0, 1.0, 0.0);
	Type = UGK_CAMERA;
}

/**
* @fn CCamera::SetType
* Define function to set camera Type, allowed values: UGKCC_CAMERA_TYPE
* @param type: Type of camera (Perspective, Orthographic, Orthographic 2D)
*/
inline void CCamera::SetType(UGKCC_CAMERA_TYPE type)
{
	SubType = type;
}

/**
* Define function LookAt line that starts the camera position and objectives, in addition to the top of the camera
*/
inline void CCamera::SetLook()
{
#ifdef	CC_OGL
	gluLookAt(Position.v[XDIM], Position.v[YDIM], Position.v[ZDIM],	/// From the position of the camera
			  PointsTo.v[XDIM], PointsTo.v[YDIM], PointsTo.v[ZDIM],	/// Objetive
			  Up.v[XDIM], Up.v[YDIM], Up.v[ZDIM]);					/// Height
#elif	defined CC_DX
#endif
}

/**
* Sets the position coordinates x, y, z of the camera, where it is looking at and vertical orientation
* @param float x: Coordinate x of the position of the camera
* @param float y: Coordinate y of the position of the camera
* @param float z: Coordinate z of the position of the camera
*
* @param float lx: Coordinate x where the camera is looking at 
* @param float ly: Coordinate y where the camera is looking at 
* @param float lz: Coordinate z where the camera is looking at 
*
* @param float ux: Up vector coordinate x
* @param float uy: Up vector coordinate y
* @param float uz: Up vector coordinate z
*/
void CCamera::LookAt(float x, float y, float z, float lx, float ly, float lz, float ux, float uy, float uz)
{
	MoveTo(x, y, z);
	PointsTo.Set(lx, ly, lz);
	Up.Set(ux, uy, uz);
	SetLook();
}

/**
* Sets the coordinates x, y, z where the camera is looking at
* @param float x: Coordinate x where the camera is looking at
* @param float y: Coordinate y where the camera is looking at
* @param float z: Coordinate z where the camera is looking at
*/
void CCamera::LookAt(float x, float y, float z)
{
	PointsTo.Set(x, y, z);
	SetLook();
}

/**
* @fn CCamera::LookFrom
* Define function LookFrom for the position of the camera with the coordinates x, y, z
* @param x: coordinate x in space
* @param y: coordinate y in space
* @param z: coordinate z in space
*/
void CCamera::LookFrom(float x, float y, float z)
{
	MoveTo(x, y, z);
	SetLook();
}

/**
* @fn CCamera::LookFrom
* Reshape function is defined that changes the shape of the window when you move or resize with the z coordinate
* @param z: coordinate z in space
*/
void CCamera::Reshape(float Z)
{
	Position.Set(0.0f, 0.0f, Z); // updates positions x,y,z
	PointsTo.Reset(); /// updates objectives x,y,z
	Rotation.Reset(); /// updates the rotation of the coordinates

	zoom = zoom_total = 0.0f; /// updates the zoom

	Up.v[YDIM] = 1.0;
	SetLook();
	///There is no need for upadating the AABB since the camera does not collide to any object in the scene
}


/**
* @fn CCamera::SetUpPerspective
* Set-Up Perspective Camera Projection Matrix
* @param fovy: Field of View angle, in degrees, in the Y direction
* @param width, height: Aspect ratio that determines the field of view in the x direction.
* @param zNear: Distance from the viewer to the near clipping plane (always positive)
* @param zFar: Distance from the viewer to the far clipping plane (always positive)
*/
void CCamera::SetUpPerspective(GLfloat x, GLfloat y, GLfloat fovy, GLfloat width, GLfloat height, GLfloat zNear, GLfloat zFar)
{
	SetType(UGKCC_PERSPECTIVE);
	GLfloat aspect = 1.0f * width / height;
#ifdef	CC_OGL
	glMatrixMode(GL_PROJECTION); //--- Reset the coordinate system before any modification.
	glLoadIdentity();
	glViewport(x, y, width, height);
	gluPerspective(fovy,		///<Field of View angle, in degrees, in the Y direction 
		aspect,					///<Aspect ratio that determines the field of view in the x direction.
		zNear,					///<Distance from the viewer to the near clipping plane (always positive)
		zFar);					///<Distance from the viewer to the far clipping plane (always positive)
	glMatrixMode(GL_MODELVIEW);
#elif	defined CC_DX
#endif
}


/**
* @fn CCamera::SetUpOrtho
* Set-Up Orthographic Camera Projection Matrix
* @param left: Distance to the left clipping plane
* @param right: Distance to the right clipping plane
* @param bottom: Distance to the bottom clipping plane
* @param top: Distance to the top clipping plane
* @param zNear: Distance from the viewer to the near clipping plane (always positive)
* @param zFar: Distance from the viewer to the far clipping plane (always positive)
*/
void CCamera::SetUpOrtho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
	SetType(UGKCC_ORTHOGRAPHIC);
#ifdef	CC_OGL
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(left,				///<Distance to the left clipping plane
		right,					///<Distance to the right clipping plane
		bottom,					///<Distance to the top clipping plane
		top,					///<Distance to the bottom clipping plane
		zNear,					///<Distance from the viewer to the near clipping plane (always positive)
		zFar);					///<Distance from the viewer to the far clipping plane (always positive)
	glMatrixMode(GL_MODELVIEW);
#elif	defined CC_DX
#endif
}

/**
* @fn CCamera::SetUpOrtho2D
* Set-Up 2D Orthographic Camera Projection Matrix
* @param left: Distance to the left clipping plane
* @param right: Distance to the right clipping plane
* @param bottom: Distance to the bottom clipping plane
* @param top: Distance to the top clipping plane
*/
void CCamera::SetUpOrtho2D(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
{
#ifdef CC_OGL
	SetUpOrtho(left, right, bottom, top, -1, 1);
	SetType(UGKCC_ORTHOGRAPHIC_2D);
#elif defined CC_DX
#endif
}

void CCamera::RestoreProjection()
{
#ifdef CC_OGL
	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
#elif defined CC_DX
#endif
}

/**
* @fn CCamera::SetBezierControlPoints
* Define Control Points, so Camera could follow Bezier curve generated by
* @param *p: N-Dimensional Vector of Bezier curve control points
*/
void CCamera::SetBezierControlPoints(Vector *p)
{
	ControlPoints = p;
}


/**
* @fn CCamera::GetBezierControlPoints
* Return Control Points actually used by the camera Bazier curve.
*/
Vector *CCamera::GetBezierControlPoints()
{
	return ControlPoints;
}

/**
* @fn CCamera::GetBezierPosition
* Return position of the camera Bezier curve on step "n"
* @param n: The amount of control points to be taken into account
* @param mu: The time elapsed in normalized coordinates between [0,1]
*/
Vector CCamera::GetBezierPosition(int n, UGKALG_NUMERIC_TYPE mu)
{
	return Bezier(ControlPoints, n, mu);
}


/**
* @fn CCamera::setupStereoscopic
* Set up Stereoscopic view
* @param fovy: Field of View angle, in degrees, in the Y direction
* @param width: Width of the window.
* @param height: Height of the window
* @param nearz: Distance from the viewer to the near clipping plane (always positive)
* @param farz: Distance from the viewer to the far clipping plane (always positive)
* @param screenz: Distance from the viewer to the screen, in the Z direcction
* @param depthz: Distance where the 3D is create, in the Z direction
* @param funcA: Function used to draw the scene.
*/
void CCamera::setupStereoscopic( GLfloat fovy,  GLfloat width, GLfloat height, GLfloat nearz, GLfloat farz, GLfloat screenz, GLfloat depthz, void funcA())
{

	SetType(UGKCC_STEREOSCOPIC);
	
	
	/*-----------------------------*
	*      SET UP FRUSTUM          *
	*------------------------------*/
	///MAIN CAMERA PROPERIES
	double aspect = width / height; ///aspect ratio 
	double top = nearz * tan((fovy *0.5)*M_PI / 180.0); ///Distance to the top clipping plane
	double right = aspect*top; ///Distance to the right clipping plane
	double fshift = EyeDistance / 2 * (nearz / screenz); ///Displacement of the frustum
	/// LEFT CAMERA PROPERIES
	double L_top = top;///Distance to the top clipping plane
	double L_bottom = -top;///Distance to the botoom clipping plane
	double L_left = -right + fshift;///Distance to the left clipping plane
	double L_right = right + fshift;/// Distance to the right clipping plane
	double L_mtrans = EyeDistance / 2; ///Displacement from the main camera using to cancel parallax
	Vector eyePOs; //Auxiliar vector to calculate the left eye position
	Vector centerPos; //Auxiliar vector to the objetive point of the camera.

	/// RIGHT CAMERA PROPERTIES
	double R_top = top;///Distance to the top clipping plane
	double R_bottom = -top;///Distance to the botoom clipping plane
	double R_left = -right - fshift;///Distance to the left clipping plane
	double R_right = right - fshift;/// Distance to the right clipping plane
	double R_mtrans = -EyeDistance / 2;///Displacement from the main camera using to cancel parallax
	Vector eyePOsD; //Auxiliar vector to calculate the right eye position
	Vector centerPosD;  //Auxiliar vector to the objetive point of the camera.

	/*******************
	* CAMERAS POSITION *
	********************/

	
	///Calculate the Focus Point (only using when Rotation Focus Method)
	Vector vd = PointsTo.operator-(Position); //Direction vector from camera position to objetive point (PointsTo)
	vd.Normalize();
	
	Vector focus;
	focus.v[XDIM] = Position.v[XDIM] + vd.v[XDIM]* FocusDistance;
	focus.v[YDIM] = Position.v[YDIM] + vd.v[YDIM]* FocusDistance;
	focus.v[ZDIM] = Position.v[ZDIM] + vd.v[ZDIM]* FocusDistance;

	///LEFT EYE CAMERA AND RIGHT EYE CAMERA POSITION

	if (OculusShift == UGKCC_SHIFT_BOTH) /// UGKCC_SHIFT_BOTH : Both cameras are shifting
	{
		
		eyePOs = Position.operator-(Vector(0, 0, -1));
		eyePOs.operator+=(Vector(-1 * EyeDistance / 2, 0, 0)); ///the left camera move EyeDistance/2 in the -X direction
		eyePOsD = Position.operator-(Vector(0, 0, -1));
		eyePOsD.operator+=(Vector(1 * EyeDistance / 2, 0, 0));///the right camera move EyeDistance/2 in the X direction
		
		//FOCUS METHOD
		if (FocusMethod == UGKCC_IN_FRONT_FOCUS) 
		{
			centerPos = PointsTo.operator+(Vector(-1 * EyeDistance / 2, 0, 0));
			centerPosD = PointsTo.operator+(Vector(1 * EyeDistance / 2, 0, 0));
		}
		else if (FocusMethod == UGKCC_ROTATION_FOCUS) 
		{
			centerPos = focus;
			centerPosD = focus;
		}
	}
	else if (OculusShift == UGKCC_SHIFT_LEFT)/// UGKCC_SHIFT_LEFT: The right camera is placed in the main camera position and the left one is moved EyeDistance in the -X direction
	{
		eyePOs = Position.operator-(Vector(0, 0, -1));
		eyePOs.operator+=(Vector(-1 * EyeDistance, 0, 0));
		eyePOsD = Position.operator-(Vector(0, 0, -1));
		
		//FOCUS METHOD
		if (FocusMethod == UGKCC_IN_FRONT_FOCUS) {
			centerPos = PointsTo.operator+(Vector(-1 * EyeDistance, 0, 0));
			centerPosD = PointsTo;
		}
		else if (FocusMethod == UGKCC_ROTATION_FOCUS) {
			centerPos = focus;
			centerPosD = focus;
		}
	}

	else if (OculusShift == UGKCC_SHIFT_RIGHT)///UGKCC_SHIFT_RIGHT: The left camera is placed in the main camera position and the right one is moved EyeDistance in the X direction
	{
		eyePOs = Position.operator-(Vector(0, 0, -1));
		eyePOsD = Position.operator-(Vector(0, 0, -1));
		eyePOsD.operator+=(Vector(1 * EyeDistance, 0, 0));
		//FOCUS METHOD
		if (FocusMethod == UGKCC_IN_FRONT_FOCUS) {
			centerPos = PointsTo;
			centerPosD = PointsTo.operator+(Vector(1 * EyeDistance, 0, 0));
		}
		else if (FocusMethod == UGKCC_ROTATION_FOCUS) {
			centerPos = focus;
			centerPosD = focus;
		}
	}
	
	/*---------------------------------*
	*		DRAW SCENES				   *
	*----------------------------------*/
	///VIEWPORT POSITIONS. Calculated depending of STEREO_LAYOUT and UGKCC_EYES_SELECTION
	//LEFT CAMERA VIEWPORT POSITION

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(L_left, L_right, L_bottom, L_top, nearz, farz);

	if (EyeSelected == UGKCC_BOTH_EYE) ///UGKCC_BOTH_EYE: BOTH CAMERAS ARE RENDER
	{
		if (StereoLayout == UGKCC_LEFT_RIGHT)///UGKCC_LEFT_RIGHT: The screen is divided in two parts, left and right
		{
			if (EyesFlipped)
				glViewport(width / 2, 0, width / 2, height);
			else
				glViewport(0, 0, width / 2, height);
		}
		else if (StereoLayout == UGKCC_TOP_DOWN)///UGKCC_TOP_DOWN: The screen is divided in two parts top for right eye and bottom for left eye
		{
			if (EyesFlipped)
				glViewport(0, 0, width, height / 2);
			else
				
			glViewport(0, height / 2, width, height / 2);
		}
	}
	else if (EyeSelected == UGKCC_LEFT_EYE)///UGKCC_LEFT_EYE: Only the left eye is render
	{

		glViewport(0, 0, width, height);
	}
	else if (EyeSelected == UGKCC_RIGHT_EYE) ///UGKCC_RIGHT_EYE: Only the right eye is render
	{

		glViewport(0, 0, 0, 0);
	}
	// update the view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyePOs.v[XDIM], eyePOs.v[YDIM], eyePOs.v[ZDIM],//eye position
			centerPos.v[XDIM], centerPos.v[YDIM], centerPos.v[ZDIM],//center position
			Up.v[XDIM], Up.v[YDIM], Up.v[ZDIM]);//up direction

	glDrawBuffer(GL_BACK_LEFT); //draw into back left buffer    
	//glTranslatef(L_mtrans, 0.0, 0.0);  //translate to cancel parallax      
	glPushMatrix();
	{
		glTranslatef(0.0, 0.2, depthz);           //translate to screenplane
		funcA();
	}
	glPopMatrix();

	//RIGHT CAMERA VIEWPORT POSITION
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(L_left, L_right, L_bottom, L_top, nearz, farz);
	//viewport position
	if (EyeSelected == UGKCC_BOTH_EYE)
	{
		if (StereoLayout == UGKCC_LEFT_RIGHT) {
			if (EyesFlipped)
				glViewport(0, 0, width / 2, height);
			else
				glViewport(width / 2, 0, width / 2, height);
		}
		else if (StereoLayout == UGKCC_TOP_DOWN) {
			if (EyesFlipped)
				glViewport(0, height / 2, width, height / 2);
			else
				glViewport(0, 0, width, height / 2);
		}
	}
	else if (EyeSelected == UGKCC_RIGHT_EYE) {

		glViewport(0, 0, width, height);
	}
	else if (EyeSelected == UGKCC_LEFT_EYE) {

		glViewport(0, 0, 0, 0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyePOsD.v[XDIM], eyePOsD.v[YDIM], eyePOsD.v[ZDIM],//eye position
		centerPosD.v[XDIM], centerPosD.v[YDIM], centerPosD.v[ZDIM],//centre position
		Up.v[XDIM], Up.v[YDIM], Up.v[ZDIM]);//up direction

	glDrawBuffer(GL_BACK_RIGHT);                             //draw into back right buffer
	//glTranslatef(R_mtrans, 0.0, 0.0);

	glPushMatrix();
	{
		glTranslatef(0.0, 0.2, depthz);                        //translate to screenplane
		funcA();
	}
	glPopMatrix();
}

