/**
 * @file	src\UGKParticlePivotCamera.cpp
 *
 * @brief	Implements the ugk particle pivot camera class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#include "UGKParticleInclude.h"
#include "UGKParticlePivotCamera.h"
#include <algorithm>

/**
 * @fn	UGKParticlePivotCamera::UGKParticlePivotCamera()
 *
 * @brief	Default constructor.
 */

UGKParticlePivotCamera::UGKParticlePivotCamera()
: m_PivotPoint(0,0, 0 )
{

}

/**
 * @fn	glm::vec3 UGKParticlePivotCamera::ProjectOntoUnitSphere( glm::vec2 screenPos )
 *
 * @brief	Project onto unit sphere.
 *
 * @param	screenPos	The screen position.
 *
 * @return	A glm::vec3.
 */

Vector UGKParticlePivotCamera::ProjectOntoUnitSphere( Vector screenPos )
{
    float x, y, z;
    float radius = std::min( m_ViewportWidth, m_ViewportHeight );

    x = ( screenPos.v[XDIM] / radius ) * 2.0f;    // range [0 .. 2]
    y = ( screenPos.v[YDIM] / radius ) * 2.0f;   // range [0 .. 2]
    x -= 1.0f;                                       // range [-1 .. 1]
    y -= 1.0f; //  - result.v[YDIM];                             // range [
    z = 1.0f - ( x * x ) + ( y * y );
 
    z = ( z > 0.0f ) ? sqrtf( z ) : 0.0f;

    return Vector( x, y, z );
}

/**
 * @fn	void UGKParticlePivotCamera::Update( float fDeltaTime )
 *
 * @brief	Updates the given fDeltaTime.
 *
 * @param	fDeltaTime	The delta time.
 */

void UGKParticlePivotCamera::Update( float fDeltaTime )
{
    base::Update(fDeltaTime);

}

/**
 * @fn	void UGKParticlePivotCamera::TranslatePivotX( float x )
 *
 * @brief	Translate pivot x coordinate.
 *
 * @param	x	The x coordinate.
 */

void UGKParticlePivotCamera::TranslatePivotX( float x )
{
	Quaternion rot;//ALGEBRA = Quaternion(glm::radians(m_Rotate));
    m_PivotPoint += rot*Vector( x, 0, 0 );
}

/**
 * @fn	void UGKParticlePivotCamera::TranslatePivotY( float y )
 *
 * @brief	Translate pivot y coordinate.
 *
 * @param	y	The y coordinate.
 */

void UGKParticlePivotCamera::TranslatePivotY( float y )
{
	Quaternion rot;//ALGEBRA  = Quaternion(glm::radians(m_Rotate));
    m_PivotPoint += rot*Vector( 0, y, 0 );
}

/**
 * @fn	void UGKParticlePivotCamera::TranslatePivotZ( float z )
 *
 * @brief	Translate pivot z coordinate.
 *
 * @param	z	The z coordinate.
 */

void UGKParticlePivotCamera::TranslatePivotZ( float z )
{
	Quaternion rot;//ALGEBRA = Quaternion(glm::radians(m_Rotate));
    m_PivotPoint += rot*Vector( 0, 0, z );
}

/**
 * @fn	void UGKParticlePivotCamera::SetPivot( const Vector& pivot )
 *
 * @brief	Sets a pivot.
 *
 * @param	pivot	The pivot.
 */

void UGKParticlePivotCamera::SetPivot(  const Vector& pivot )
{
    m_PivotPoint = pivot;
}

/**
 * @fn	Vector UGKParticlePivotCamera::GetPivot() const
 *
 * @brief	Gets the pivot.
 *
 * @return	The pivot.
 */

Vector UGKParticlePivotCamera::GetPivot() const
{
    return m_PivotPoint;
}

/**
 * @fn	void UGKParticlePivotCamera::ApplyViewTransform()
 *
 * @brief	Applies the view transform.
 */

void UGKParticlePivotCamera::ApplyViewTransform()
{
    glTranslatef( 0.0f, 0.0f, -m_Translate.v[ZDIM] );
    glRotatef( m_Rotate.v[ZDIM], 0.0f, 0.0f, 1.0f );
    glRotatef( m_Rotate.v[YDIM], 0.0f, 1.0f, 0.0f );
    glRotatef( m_Rotate.v[XDIM], 1.0f, 0.0f, 0.0f );
    glTranslatef( -m_PivotPoint.v[XDIM], -m_PivotPoint.v[YDIM], -m_PivotPoint.v[ZDIM]);
}

