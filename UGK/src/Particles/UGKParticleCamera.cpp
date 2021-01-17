/**
 * @file	src\UGKParticleCamera.cpp
 *
 * @brief	Implements the ugk particle camera class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#include "UGKParticleInclude.h"
#include "UGKParticleCamera.h"
#include <algorithm>

using namespace UGK;

/**
 * @fn	void UGKParticleCamera::Update( float fDeltaTime )
 *
 * @brief	Updates the given fDeltaTime.
 *
 * @param	fDeltaTime	The delta time.
 */

void UGKParticleCamera::Update( float fDeltaTime )
{

}

/**
 * @fn	void UGKParticleCamera::SetViewport( int x, int y, int width, int height )
 *
 * @brief	Sets a viewport.
 *
 * @param	x	  	The x coordinate.
 * @param	y	  	The y coordinate.
 * @param	width 	The width.
 * @param	height	The height.
 */

void UGKParticleCamera::SetViewport( int x, int y, int width, int height )
{
    m_ViewportX = x;
    m_ViewportY = y;
    m_ViewportWidth = width;
    m_ViewportHeight = std::max( height, 1 );
}

/**
 * @fn	void UGKParticleCamera::SetProjection( float fovy, float aspect, float zNear, float zFar )
 *
 * @brief	Sets a projection.
 *
 * @param	fovy  	The fovy.
 * @param	aspect	The aspect.
 * @param	zNear 	The near.
 * @param	zFar  	The far.
 */

void UGKParticleCamera::SetProjection( float fovy, float aspect, float zNear, float zFar )
{
    m_fVFOV = fovy;
    m_fAspect = aspect;
    m_fNear = zNear;
    m_fFar = zFar;
}

/**
 * @fn	void UGKParticleCamera::AddPitch( float fPitch )
 *
 * @brief	Adds a pitch.
 *
 * @param	fPitch	The pitch.
 */

void UGKParticleCamera::AddPitch( float fPitch )
{
    m_Rotate.v[XDIM] += fPitch;
}

/**
 * @fn	void UGKParticleCamera::AddYaw( float fYaw )
 *
 * @brief	Adds a yaw.
 *
 * @param	fYaw	The yaw.
 */

void UGKParticleCamera::AddYaw( float fYaw )
{
    m_Rotate.v[YDIM] += fYaw;
}

/**
 * @fn	void UGKParticleCamera::AddRoll( float fRoll )
 *
 * @brief	Adds a roll.
 *
 * @param	fRoll	The roll.
 */

void UGKParticleCamera::AddRoll( float fRoll )
{
    m_Rotate.v[ZDIM] += fRoll;
}

/**
 * @fn	void UGKParticleCamera::AddRotation( const Quaternion& rot )
 *
 * @brief	Adds a rotation.
 *
 * @param	rot	The rot.
 */

void UGKParticleCamera::AddRotation( const Quaternion& rot )
{
    //ALGEBRA Quaternion finalRotate = rot * Quaternion( m_Rotate );
	//ALGEBRA m_Rotate = glm::eularAngles( finalRotate );
}

/**
 * @fn	void UGKParticleCamera::TranslateX( float x )
 *
 * @brief	Translate x coordinate.
 *
 * @param	x	The x coordinate.
 */

void UGKParticleCamera::TranslateX( float x )
{
    m_Translate.v[XDIM] += x;
}

/**
 * @fn	void UGKParticleCamera::TranslateY( float y )
 *
 * @brief	Translate y coordinate.
 *
 * @param	y	The y coordinate.
 */

void UGKParticleCamera::TranslateY( float y )
{
    m_Translate.v[YDIM] += y;
}

/**
 * @fn	void UGKParticleCamera::TranslateZ( float z )
 *
 * @brief	Translate z coordinate.
 *
 * @param	z	The z coordinate.
 */

void UGKParticleCamera::TranslateZ( float z )
{
    m_Translate.v[ZDIM] += z;
}

/**
 * @fn	void UGKParticleCamera::SetTranslate( const glm::vec3& translate )
 *
 * @brief	Sets a translate.
 *
 * @param	translate	The translate.
 */

void UGKParticleCamera::SetTranslate( const Vector& translate )
{
    m_Translate = translate;
}

/**
 * @fn	void UGKParticleCamera::SetRotate( float pitch, float yaw, float roll )
 *
 * @brief	Sets a rotate.
 *
 * @param	pitch	The pitch.
 * @param	yaw  	The yaw.
 * @param	roll 	The roll.
 */

void UGKParticleCamera::SetRotate( float pitch, float yaw, float roll )
{
    m_Rotate = Vector( pitch, yaw, roll );
}

/**
 * @fn	void UGKParticleCamera::SetRotate( const glm::vec3& rotate )
 *
 * @brief	Sets a rotate.
 *
 * @param	rotate	The rotate.
 */

void UGKParticleCamera::SetRotate( const Vector& rotate )
{
    m_Rotate = rotate;
}

/**
 * @fn	glm::vec3 UGKParticleCamera::GetTranslation() const
 *
 * @brief	Gets the translation.
 *
 * @return	The translation.
 */

Vector UGKParticleCamera::GetTranslation() const
{
    return m_Translate;
}

/**
 * @fn	glm::vec3 UGKParticleCamera::GetRotation() const
 *
 * @brief	Gets the rotation.
 *
 * @return	The rotation.
 */

Vector UGKParticleCamera::GetRotation() const
{
    return m_Rotate;
}

/**
 * @fn	void UGKParticleCamera::ApplyViewport()
 *
 * @brief	Applies the viewport.
 */

void UGKParticleCamera::ApplyViewport()
{
    glViewport( m_ViewportX, m_ViewportY, m_ViewportWidth, m_ViewportHeight );
}

/**
 * @fn	void UGKParticleCamera::ApplyProjectionTransform()
 *
 * @brief	Applies the projection transform.
 */

void UGKParticleCamera::ApplyProjectionTransform()
{
    glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
    gluPerspective( m_fVFOV, m_fAspect, m_fNear, m_fFar );
}

/**
 * @fn	void UGKParticleCamera::ApplyViewTransform()
 *
 * @brief	Applies the view transform.
 */

void UGKParticleCamera::ApplyViewTransform()
{
    glMatrixMode( GL_MODELVIEW );
    glTranslatef( m_Translate.v[XDIM], m_Translate.v[YDIM], m_Translate.v[ZDIM] );
    glRotatef( m_Rotate.v[XDIM], 1.0f, 0.0f, 0.0f );
    glRotatef( m_Rotate.v[YDIM], 0.0f, 1.0f, 0.0f );
    glRotatef( m_Rotate.v[ZDIM], 0.0f, 0.0f, 1.0f );
}
